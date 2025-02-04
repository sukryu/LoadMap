# Jenkins 분산 빌드 및 에이전트 설정

> **목표:**  
> - Jenkins의 분산 빌드 아키텍처와 동작 원리를 이해한다.
> - 마스터-에이전트 구조의 설정과 관리 방법을 학습한다.
> - 효율적인 빌드 분산과 리소스 활용 전략을 습득한다.
> - 대규모 환경에서의 Jenkins 확장성 확보 방안을 익힌다.

---

## 1. 분산 빌드 개요

- **정의:**  
  Jenkins 분산 빌드는 여러 시스템에 빌드 작업을 분산하여 처리하는 방식입니다.
  마스터 노드가 전체 작업을 관리하고, 에이전트 노드들이 실제 빌드를 수행하는 구조로 동작합니다.

- **분산 빌드의 필요성:**  
  대규모 프로젝트나 복잡한 빌드 환경에서는 단일 서버로 모든 작업을 처리하기 어렵습니다.
  분산 빌드를 통해 시스템 리소스를 효율적으로 활용하고, 빌드 시간을 단축할 수 있습니다.

---

## 2. 마스터-에이전트 아키텍처

### 2.1 마스터 노드

마스터 노드의 주요 역할:
- 전체 시스템 관리 및 모니터링
- 작업 스케줄링 및 분배
- 웹 인터페이스 제공
- 구성 정보 관리
- 결과 수집 및 보고

### 2.2 에이전트 노드

에이전트 노드의 주요 역할:
- 실제 빌드 작업 수행
- 테스트 실행
- 아티팩트 생성
- 배포 작업 수행

### 2.3 통신 구조

```plaintext
[마스터 노드]
     │
     ├── TCP/IP 통신 ──→ [에이전트 1]
     │
     ├── TCP/IP 통신 ──→ [에이전트 2]
     │
     └── TCP/IP 통신 ──→ [에이전트 3]
```

---

## 3. 에이전트 설정 및 관리

### 3.1 에이전트 노드 추가

SSH를 통한 에이전트 설정:
```bash
# 에이전트 노드에서 SSH 키 생성
ssh-keygen -t rsa
cat ~/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys

# Jenkins 마스터에 에이전트 노드 추가
Manage Jenkins > Manage Nodes and Clouds > New Node
```

### 3.2 에이전트 설정 예시

Jenkins UI에서의 노드 설정:
```yaml
노드 이름: agent-01
설명: Linux 빌드 에이전트
동시 빌드 수: 2
원격 작업 디렉토리: /var/jenkins/agent
실행자 수: 2
레이블: linux docker maven
시작 방법: SSH
  호스트: agent01.example.com
  인증: SSH 키
환경 변수:
  JAVA_HOME: /usr/lib/jvm/java-11
  MAVEN_HOME: /usr/share/maven
```

---

## 4. 분산 빌드 구성

### 4.1 노드 레이블 전략

효율적인 레이블 구성:
```groovy
pipeline {
    agent {
        label 'linux && docker && maven'  // 레이블 조합으로 적절한 에이전트 선택
    }
    stages {
        stage('Build') {
            steps {
                sh 'mvn clean package'
            }
        }
    }
}
```

### 4.2 작업 분배 전략

```groovy
pipeline {
    agent none  // 파이프라인 레벨에서는 에이전트를 지정하지 않음
    
    stages {
        stage('Java Build') {
            agent { label 'java-build' }
            steps {
                sh 'mvn clean package'
            }
        }
        
        stage('Docker Build') {
            agent { label 'docker' }
            steps {
                sh 'docker build -t myapp .'
            }
        }
        
        stage('Deploy') {
            agent { label 'deploy' }
            steps {
                sh './deploy.sh'
            }
        }
    }
}
```

---

## 5. 성능 최적화

### 5.1 리소스 관리

시스템 리소스 최적화:
- CPU 코어 할당
- 메모리 제한 설정
- 디스크 공간 관리
- 네트워크 대역폭 고려

### 5.2 빌드 최적화

빌드 성능 향상 전략:
```groovy
pipeline {
    agent { label 'high-cpu' }
    options {
        timestamps()  // 타임스탬프 표시
        timeout(time: 1, unit: 'HOURS')  // 타임아웃 설정
    }
    stages {
        stage('Parallel Build') {
            parallel {  // 병렬 빌드 실행
                stage('Unit Tests') {
                    steps {
                        sh 'mvn test'
                    }
                }
                stage('Integration Tests') {
                    steps {
                        sh 'mvn verify'
                    }
                }
            }
        }
    }
}
```

---

## 6. 고가용성 구성

### 6.1 마스터 노드 이중화

고가용성 확보 방안:
- 마스터 노드 백업
- 데이터 복제
- 자동 장애 조치
- 로드 밸런싱

### 6.2 에이전트 풀 관리

동적 에이전트 관리:
```groovy
pipeline {
    agent {
        kubernetes {  // Kubernetes 동적 에이전트 사용
            yaml '''
                apiVersion: v1
                kind: Pod
                spec:
                    containers:
                    - name: maven
                      image: maven:3.8.1-jdk-11
                    - name: docker
                      image: docker:19.03
            '''
        }
    }
    stages {
        stage('Build') {
            steps {
                container('maven') {
                    sh 'mvn clean package'
                }
            }
        }
    }
}
```

---

## 7. 모니터링 및 유지보수

### 7.1 시스템 모니터링

모니터링 항목:
- 에이전트 상태
- 빌드 큐 상태
- 리소스 사용량
- 네트워크 지연
- 빌드 시간

### 7.2 문제 해결

일반적인 문제와 해결 방법:
- 연결 끊김: 네트워크 및 방화벽 설정 확인
- 빌드 실패: 에이전트 환경 검증
- 성능 저하: 리소스 사용량 분석
- 큐 적체: 작업 분배 전략 조정

---

## 8. 보안 고려사항

### 8.1 에이전트 보안

보안 설정:
- SSH 키 관리
- JNLP 포트 보호
- 네트워크 격리
- 접근 권한 제한

### 8.2 통신 보안

보안 통신 구성:
```yaml
agent:
  protocols:
    - "JNLP4-connect"  # 최신 보안 프로토콜 사용
  port: 50000
  ssl:
    enabled: true
    keyStore: /path/to/keystore
    keyStorePassword: "${KEYSTORE_PASSWORD}"
```

---

## 9. 참고 자료

- [Jenkins 분산 빌드 문서](https://www.jenkins.io/doc/book/scaling/scaling-jenkins/)
- [Jenkins 에이전트 프로토콜](https://www.jenkins.io/doc/book/managing/security/)
- [Jenkins 고가용성 가이드](https://www.jenkins.io/doc/book/scaling/high-availability/)
- [Kubernetes 에이전트 설정](https://www.jenkins.io/doc/book/scaling/kubernetes/)

---

## 마무리

분산 빌드 환경은 Jenkins를 대규모로 운영할 때 필수적인 구성 요소입니다.
마스터-에이전트 구조를 효율적으로 구성하고 관리함으로써 빌드 성능을 최적화하고 시스템의 안정성을 확보할 수 있습니다.
지속적인 모니터링과 최적화를 통해 더욱 효율적인 CI/CD 환경을 구축할 수 있습니다.