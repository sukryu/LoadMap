# Jenkins를 활용한 실무 CI/CD 배포 전략

> **목표:**  
> - 다양한 배포 전략의 개념과 특징을 이해한다.
> - Jenkins를 사용한 배포 파이프라인 구현 방법을 학습한다.
> - 각 배포 전략의 장단점을 파악하고 적절한 상황에 적용한다.
> - 실무에서 발생할 수 있는 배포 문제에 대한 대응 방안을 습득한다.

---

## 1. CI/CD 배포 전략 개요

현대 소프트웨어 개발에서 지속적 통합(CI)과 지속적 배포(CD)는 필수적입니다. 
효과적인 배포 전략은 서비스의 안정성을 유지하면서 새로운 기능을 신속하게 제공할 수 있게 해줍니다.

주요 배포 전략:
- 블루-그린 배포 (Blue-Green Deployment)
- 카나리 배포 (Canary Deployment)
- 롤링 업데이트 (Rolling Update)
- A/B 테스팅 배포

---

## 2. 블루-그린 배포

### 2.1 개념과 특징

블루-그린 배포는 두 개의 동일한 프로덕션 환경을 운영하며, 한 환경에서 새 버전을 테스트하고 검증이 완료되면 트래픽을 전환하는 방식입니다.

### 2.2 Jenkins 파이프라인 구현

```groovy
pipeline {
    agent any
    environment {
        DOCKER_IMAGE = 'myapp'
        GREEN_PORT = '8080'
        BLUE_PORT = '8081'
        DEPLOY_PORT = '80'
    }
    
    stages {
        stage('Determine Active Environment') {
            steps {
                script {
                    def activePort = sh(
                        script: "curl -s http://localhost:${DEPLOY_PORT}/info | grep 'port' | cut -d':' -f2",
                        returnStdout: true
                    ).trim()
                    
                    env.CURRENT_ENV = activePort == env.BLUE_PORT ? 'BLUE' : 'GREEN'
                    env.DEPLOY_ENV = activePort == env.BLUE_PORT ? 'GREEN' : 'BLUE'
                    env.DEPLOY_PORT = env.DEPLOY_ENV == 'BLUE' ? env.BLUE_PORT : env.GREEN_PORT
                }
            }
        }
        
        stage('Deploy New Version') {
            steps {
                script {
                    // 새 버전 배포
                    sh """
                        docker run -d --name myapp-${env.DEPLOY_ENV.toLowerCase()} \
                        -p ${env.DEPLOY_PORT}:8080 ${DOCKER_IMAGE}:${BUILD_NUMBER}
                    """
                    
                    // 헬스 체크
                    sh "sleep 30" // 애플리케이션 시작 대기
                    sh "curl -f http://localhost:${env.DEPLOY_PORT}/health"
                }
            }
        }
        
        stage('Switch Traffic') {
            steps {
                script {
                    // nginx 설정 업데이트
                    sh """
                        sed -i 's/proxy_pass http:\\/\\/localhost:.*$/proxy_pass http:\\/\\/localhost:${env.DEPLOY_PORT};/' \
                        /etc/nginx/conf.d/default.conf
                    """
                    sh "nginx -s reload"
                }
            }
        }
        
        stage('Cleanup Old Version') {
            steps {
                script {
                    // 이전 버전 컨테이너 제거
                    sh "docker rm -f myapp-${env.CURRENT_ENV.toLowerCase()}"
                }
            }
        }
    }
    
    post {
        failure {
            // 배포 실패 시 롤백
            script {
                sh """
                    sed -i 's/proxy_pass http:\\/\\/localhost:.*$/proxy_pass http:\\/\\/localhost:${env.CURRENT_ENV == 'BLUE' ? env.BLUE_PORT : env.GREEN_PORT};/' \
                    /etc/nginx/conf.d/default.conf
                """
                sh "nginx -s reload"
            }
        }
    }
}
```

---

## 3. 카나리 배포

### 3.1 개념과 특징

카나리 배포는 새 버전을 일부 사용자에게만 점진적으로 노출하면서 위험을 최소화하는 전략입니다.

### 3.2 Jenkins 파이프라인 구현

```groovy
pipeline {
    agent any
    environment {
        DOCKER_IMAGE = 'myapp'
        CANARY_WEIGHT = '20'  // 카나리 버전으로 보낼 트래픽 비율 (%)
    }
    
    stages {
        stage('Deploy Canary') {
            steps {
                script {
                    // 카나리 버전 배포
                    sh """
                        docker run -d --name myapp-canary \
                        -l version=canary ${DOCKER_IMAGE}:${BUILD_NUMBER}
                    """
                    
                    // nginx 설정 업데이트 - 가중치 기반 라우팅
                    sh """
                        cat > /etc/nginx/conf.d/split.conf << EOF
                        split_clients "\${request_id}" \$variant {
                            ${CANARY_WEIGHT}% canary;
                            *         production;
                        }
                        EOF
                    """
                    
                    sh "nginx -s reload"
                }
            }
        }
        
        stage('Monitor Canary') {
            steps {
                script {
                    // 모니터링 및 메트릭 수집
                    sh """
                        for i in {1..5}; do
                            curl -f http://localhost/health
                            sleep 60
                        done
                    """
                }
            }
        }
        
        stage('Promote to Production') {
            when {
                expression { 
                    // 카나리 버전 메트릭이 정상인 경우
                    return true  // 실제로는 메트릭 기반 판단 로직 구현
                }
            }
            steps {
                script {
                    // 기존 프로덕션 버전을 새 버전으로 교체
                    sh """
                        docker rm -f myapp-production
                        docker run -d --name myapp-production \
                        -l version=production ${DOCKER_IMAGE}:${BUILD_NUMBER}
                    """
                }
            }
        }
    }
    
    post {
        failure {
            // 카나리 배포 실패 시 롤백
            script {
                sh "docker rm -f myapp-canary"
                sh "sed -i '/split_clients/d' /etc/nginx/conf.d/split.conf"
                sh "nginx -s reload"
            }
        }
        success {
            // 배포 성공 시 카나리 설정 제거
            script {
                sh "rm /etc/nginx/conf.d/split.conf"
                sh "nginx -s reload"
            }
        }
    }
}
```

---

## 4. 롤링 업데이트

### 4.1 개념과 특징

롤링 업데이트는 서버를 순차적으로 업데이트하면서 서비스의 가용성을 유지하는 전략입니다.

### 4.2 Jenkins 파이프라인 구현

```groovy
pipeline {
    agent any
    environment {
        DOCKER_IMAGE = 'myapp'
        REPLICAS = 4  // 총 서버 수
        BATCH_SIZE = 1  // 한 번에 업데이트할 서버 수
    }
    
    stages {
        stage('Rolling Update') {
            steps {
                script {
                    def totalBatches = REPLICAS.toInteger() / BATCH_SIZE.toInteger()
                    
                    for (int batch = 0; batch < totalBatches; batch++) {
                        // 배치 단위로 서버 업데이트
                        def startIndex = batch * BATCH_SIZE.toInteger()
                        def endIndex = startIndex + BATCH_SIZE.toInteger() - 1
                        
                        // 이전 버전 서버 제거
                        sh """
                            for i in {${startIndex}..${endIndex}}; do
                                docker rm -f myapp-\$i
                            done
                        """
                        
                        // 새 버전 서버 배포
                        sh """
                            for i in {${startIndex}..${endIndex}}; do
                                docker run -d --name myapp-\$i \
                                ${DOCKER_IMAGE}:${BUILD_NUMBER}
                            done
                        """
                        
                        // 헬스 체크
                        sh """
                            for i in {${startIndex}..${endIndex}}; do
                                until curl -f http://localhost:\$(docker port myapp-\$i 8080/tcp | cut -d ':' -f2)/health; do
                                    sleep 5
                                done
                            done
                        """
                    }
                }
            }
        }
    }
    
    post {
        failure {
            // 업데이트 실패 시 롤백
            script {
                sh """
                    for i in {0..${REPLICAS.toInteger()-1}}; do
                        docker rm -f myapp-\$i
                        docker run -d --name myapp-\$i ${DOCKER_IMAGE}:stable
                    done
                """
            }
        }
    }
}
```

---

## 5. 배포 전략 선택 가이드

각 배포 전략의 적합한 사용 상황:

### 5.1 블루-그린 배포
- 제로 다운타임이 필요한 경우
- 빠른 롤백이 필요한 경우
- 충분한 인프라 리소스가 있는 경우

### 5.2 카나리 배포
- 새로운 기능의 위험을 최소화하고 싶은 경우
- 실제 사용자 피드백이 중요한 경우
- A/B 테스팅이 필요한 경우

### 5.3 롤링 업데이트
- 리소스가 제한적인 경우
- 점진적인 업데이트가 허용되는 경우
- 간단한 배포 과정이 필요한 경우

---

## 6. 배포 모니터링과 롤백

### 6.1 모니터링 지표

```groovy
pipeline {
    agent any
    
    stages {
        stage('Monitor Deployment') {
            steps {
                script {
                    parallel(
                        "Error Rate": {
                            // 에러율 모니터링
                            sh "curl -s http://prometheus:9090/api/v1/query?query=rate(http_errors_total[5m])"
                        },
                        "Response Time": {
                            // 응답 시간 모니터링
                            sh "curl -s http://prometheus:9090/api/v1/query?query=histogram_quantile(0.95, http_request_duration_seconds)"
                        },
                        "CPU Usage": {
                            // CPU 사용률 모니터링
                            sh "curl -s http://prometheus:9090/api/v1/query?query=container_cpu_usage_seconds_total"
                        }
                    )
                }
            }
        }
    }
}
```

### 6.2 자동 롤백 조건

```groovy
def shouldRollback() {
    def errorRate = sh(
        script: "curl -s http://prometheus:9090/api/v1/query?query=rate(http_errors_total[5m])",
        returnStdout: true
    ).trim()
    
    def responseTime = sh(
        script: "curl -s http://prometheus:9090/api/v1/query?query=histogram_quantile(0.95, http_request_duration_seconds)",
        returnStdout: true
    ).trim()
    
    return errorRate.toFloat() > 0.1 || responseTime.toFloat() > 2.0
}
```

---

## 7. 실무 적용 시 고려사항

### 7.1 데이터베이스 마이그레이션

```groovy
stage('Database Migration') {
    steps {
        script {
            // 백업 생성
            sh "pg_dump -h db-host -U user -d mydb > backup.sql"
            
            // 마이그레이션 실행
            sh "flyway migrate -url=jdbc:postgresql://db-host:5432/mydb"
            
            // 마이그레이션 검증
            sh "flyway validate"
        }
    }
}
```

### 7.2 네트워크 구성

```nginx
# nginx.conf
upstream backend {
    server blue-backend:8080;
    server green-backend:8080 backup;
}

server {
    listen 80;
    location / {
        proxy_pass http://backend;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
    }
}
```

---

## 8. 문제 해결과 디버깅

### 8.1 일반적인 문제와 해결 방법

- 배포 타임아웃
- 리소스 부족
- 설정 불일치
- 네트워크 문제

### 8.2 디버깅 전략

```groovy
pipeline {
    agent any
    
    options {
        timestamps()
        ansiColor('xterm')
    }
    
    stages {
        stage('Debug Info') {
            steps {
                script {
                    // 시스템 상태 정보 수집
                    sh """
                        echo "=== System Info ==="
                        df -h
                        free -m
                        docker ps
                        docker stats --no-stream
                        
                        echo "=== Network Info ==="
                        netstat -tulpn
                        
                        echo "=== Application Logs ==="
                        docker logs --tail=100 \${APP_CONTAINER}
                    """
                    
                    // 배포 관련 설정 확인
                    sh """
                        echo "=== Configuration ==="
                        cat /etc/nginx/nginx.conf
                        docker inspect \${APP_CONTAINER}
                    """
                }
            }
        }
        
        stage('Verify Dependencies') {
            steps {
                script {
                    // 의존성 및 연결 상태 확인
                    sh """
                        echo "=== Database Connection ==="
                        nc -zv \${DB_HOST} \${DB_PORT}
                        
                        echo "=== External Services ==="
                        for service in \${EXTERNAL_SERVICES}; do
                            curl -f http://\${service}/health || echo "Service \${service} is down"
                        done
                    """
                }
            }
        }
    }
    
    post {
        failure {
            // 디버그 정보 아카이브
            archiveArtifacts artifacts: 'debug-info/**/*'
            
            // 알림 발송
            emailext (
                subject: "배포 실패: 디버그 정보 필요",
                body: "디버그 정보가 아카이브되었습니다. Jenkins에서 확인해주세요.",
                recipientProviders: [culprits(), requestor()]
            )
        }
    }
}
```

---

## 9. 배포 자동화와 최적화

### 9.1 자동화 도구 통합

Jenkins와 다양한 도구들을 통합하여 배포 자동화를 구현할 수 있습니다:

```groovy
pipeline {
    agent any
    
    tools {
        terraform 'terraform-1.0.0'
        kubectl 'kubectl-1.20.0'
    }
    
    stages {
        stage('Infrastructure') {
            steps {
                // Terraform을 사용한 인프라 프로비저닝
                sh """
                    terraform init
                    terraform plan
                    terraform apply -auto-approve
                """
            }
        }
        
        stage('Deploy to Kubernetes') {
            steps {
                // Kubernetes 배포
                sh """
                    kubectl apply -f k8s/
                    kubectl rollout status deployment/myapp
                """
            }
        }
        
        stage('Service Mesh Configuration') {
            steps {
                // Istio 설정 적용
                sh """
                    istioctl apply -f istio/
                    kubectl apply -f istio/virtual-service.yaml
                """
            }
        }
    }
}
```

### 9.2 성능 최적화

배포 파이프라인의 성능을 최적화하는 방법:

```groovy
pipeline {
    agent any
    
    options {
        // 병렬 실행 설정
        parallel {
            // 동시 실행 가능한 스테이지 그룹화
            stage('Tests') {
                parallel {
                    stage('Unit Tests') {
                        steps {
                            sh 'npm test'
                        }
                    }
                    stage('Integration Tests') {
                        steps {
                            sh 'npm run integration'
                        }
                    }
                }
            }
        }
    }
    
    // 캐시 활용
    stages {
        stage('Build') {
            steps {
                cache(maxCacheSize: 250, caches: [
                    arbitraryFileCache(path: 'node_modules'),
                    arbitraryFileCache(path: '.npm')
                ]) {
                    sh 'npm ci'
                    sh 'npm run build'
                }
            }
        }
    }
}
```

---

## 10. 참고 자료

- [Jenkins 파이프라인 모범 사례](https://www.jenkins.io/doc/book/pipeline/pipeline-best-practices/)
- [Kubernetes 배포 전략](https://kubernetes.io/docs/concepts/workloads/controllers/deployment/)
- [배포 자동화 패턴](https://martinfowler.com/bliki/DeploymentPattern.html)
- [Docker 컨테이너 배포 가이드](https://docs.docker.com/engine/swarm/stack-deploy/)

---

## 마무리

효과적인 배포 전략은 현대 소프트웨어 개발에서 핵심적인 요소입니다.
Jenkins를 활용한 다양한 배포 전략을 이해하고 적절히 활용함으로써,
안정적이고 효율적인 소프트웨어 배포 프로세스를 구축할 수 있습니다.
각 조직의 특성과 요구사항에 맞는 최적의 배포 전략을 선택하고,
지속적인 모니터링과 개선을 통해 배포 프로세스를 발전시켜 나가는 것이 중요합니다.