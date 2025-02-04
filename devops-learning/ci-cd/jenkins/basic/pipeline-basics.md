# Jenkins 파이프라인 기초

> **목표:**  
> - Jenkins 파이프라인의 개념과 기본 구조를 이해한다.
> - 선언적 파이프라인과 스크립트 파이프라인의 차이점을 학습한다.
> - 실제 파이프라인 작성 방법과 기본적인 구성 요소를 익힌다.
> - 파이프라인 문법과 주요 명령어를 실습을 통해 학습한다.

---

## 1. 파이프라인 개요

- **정의:**  
  Jenkins 파이프라인은 CI/CD 워크플로우를 코드로 정의하는 방식입니다.
  여러 빌드 단계를 순차적 또는 병렬로 실행할 수 있으며, 각 단계의 실행 조건과 오류 처리 방법을 정의할 수 있습니다.

- **왜 파이프라인을 사용하는가?**  
  - **코드화:** 빌드 프로세스를 코드로 관리하여 버전 관리가 가능합니다.
  - **재사용성:** 공통 로직을 여러 프로젝트에서 재사용할 수 있습니다.
  - **가시성:** 전체 빌드 프로세스를 시각적으로 확인할 수 있습니다.
  - **유지보수:** 파이프라인 수정과 관리가 용이합니다.

---

## 2. 파이프라인 기본 구조

### 2.1 핵심 구성 요소

```groovy
pipeline {
    agent any  // 실행할 에이전트 지정
    
    stages {   // 실행할 스테이지들을 정의
        stage('Build') {  // 각 스테이지는 논리적 실행 단위
            steps {       // 실제 실행할 명령어들
                echo 'Building the application...'
                sh 'mvn clean package'
            }
        }
        
        stage('Test') {
            steps {
                echo 'Running tests...'
                sh 'mvn test'
            }
        }
        
        stage('Deploy') {
            steps {
                echo 'Deploying the application...'
                sh './deploy.sh'
            }
        }
    }
    
    post {  // 파이프라인 실행 후 추가 작업
        always {
            echo 'Pipeline finished'
        }
        success {
            echo 'Successfully completed'
        }
        failure {
            echo 'Failed'
        }
    }
}
```

### 2.2 주요 섹션 설명

- **agent:** 파이프라인을 실행할 Jenkins 에이전트를 지정
- **stages:** 실행할 스테이지들을 포함하는 블록
- **stage:** 개별 스테이지를 정의하는 블록
- **steps:** 실제 실행할 명령어들을 정의
- **post:** 파이프라인 실행 완료 후의 작업 정의

---

## 3. 파이프라인 타입

### 3.1 선언적 파이프라인 (Declarative Pipeline)

```groovy
pipeline {
    agent any
    
    environment {
        MAVEN_HOME = '/usr/local/maven'
    }
    
    stages {
        stage('Build') {
            steps {
                sh "${MAVEN_HOME}/bin/mvn clean package"
            }
        }
    }
}
```

- 더 구조화된 문법 제공
- 사전 정의된 구조를 따라야 함
- 초보자가 이해하기 쉬움
- IDE 지원이 좋음

### 3.2 스크립트 파이프라인 (Scripted Pipeline)

```groovy
node {
    stage('Build') {
        try {
            sh 'mvn clean package'
        } catch (err) {
            echo "Build failed: ${err}"
            throw err
        }
    }
}
```

- Groovy 스크립트 기반
- 더 유연한 프로그래밍 가능
- 복잡한 로직 구현에 적합
- 학습 곡선이 더 가파름

---

## 4. 실전 파이프라인 예제

### 4.1 Spring Boot 애플리케이션 빌드 파이프라인

```groovy
pipeline {
    agent any
    
    environment {
        JAVA_HOME = '/usr/local/java11'
        MAVEN_HOME = '/usr/local/maven'
    }
    
    stages {
        stage('Checkout') {
            steps {
                // Git 저장소에서 코드 가져오기
                git 'https://github.com/example/spring-app.git'
            }
        }
        
        stage('Build') {
            steps {
                // Maven으로 빌드
                sh "${MAVEN_HOME}/bin/mvn clean package"
            }
        }
        
        stage('Test') {
            steps {
                // 테스트 실행
                sh "${MAVEN_HOME}/bin/mvn test"
            }
            post {
                always {
                    // 테스트 결과 보고서 저장
                    junit '**/target/surefire-reports/*.xml'
                }
            }
        }
        
        stage('Deploy') {
            when {
                // master 브랜치일 때만 배포
                branch 'master'
            }
            steps {
                sh '''
                    docker build -t myapp .
                    docker push myapp:latest
                    kubectl apply -f deployment.yaml
                '''
            }
        }
    }
    
    post {
        success {
            // 슬랙으로 성공 메시지 전송
            slackSend channel: '#deploy',
                      color: 'good',
                      message: "배포 성공: ${env.JOB_NAME} #${env.BUILD_NUMBER}"
        }
        failure {
            // 실패시 이메일 발송
            emailext to: 'team@example.com',
                     subject: "빌드 실패: ${env.JOB_NAME}",
                     body: "빌드 상세: ${env.BUILD_URL}"
        }
    }
}
```

---

## 5. 주요 기능과 문법

### 5.1 환경 변수 설정
```groovy
environment {
    DATABASE_URL = 'jdbc:mysql://localhost:3306/mydb'
    CREDENTIALS = credentials('db-credentials')
}
```

### 5.2 조건부 실행
```groovy
when {
    branch 'master'
    environment name: 'DEPLOY_TARGET', value: 'production'
}
```

### 5.3 병렬 처리
```groovy
parallel {
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
```

### 5.4 오류 처리
```groovy
steps {
    catchError(buildResult: 'SUCCESS', stageResult: 'FAILURE') {
        sh 'make test'
    }
}
```

---

## 6. 모범 사례와 주의사항

### 모범 사례
- 각 스테이지의 목적을 명확히 정의
- 환경 변수를 적절히 활용
- 중요한 정보는 크리덴셜로 관리
- 적절한 타임아웃 설정
- 결과물 아카이빙 구성

### 주의사항
- 파이프라인을 너무 복잡하게 만들지 않기
- 중요한 비밀정보를 직접 코드에 포함시키지 않기
- 너무 긴 실행 시간 피하기
- 적절한 로깅과 모니터링 구성하기

---

## 7. 문제 해결과 디버깅

### 7.1 로그 확인
- Jenkins 웹 인터페이스에서 Console Output 확인
- 각 스테이지별 실행 결과 검토
- 환경 변수 값 출력하여 확인

### 7.2 일반적인 문제 해결
- 권한 문제: 적절한 권한 설정 확인
- 네트워크 문제: 연결성 테스트
- 리소스 부족: 시스템 자원 모니터링
- 타임아웃: 적절한 제한 시간 설정

---

## 8. 참고 자료

- [Jenkins Pipeline 문법 참조](https://www.jenkins.io/doc/book/pipeline/syntax/)
- [Pipeline Steps 레퍼런스](https://www.jenkins.io/doc/pipeline/steps/)
- [Jenkins 파이프라인 예제](https://github.com/jenkinsci/pipeline-examples)
- [Pipeline 모범 사례](https://www.jenkins.io/doc/book/pipeline/pipeline-best-practices/)

---

## 마무리

Jenkins 파이프라인은 현대 CI/CD 환경에서 필수적인 도구입니다.
기본 개념과 문법을 이해하고 나면, 복잡한 빌드 및 배포 프로세스도 효과적으로 자동화할 수 있습니다.
실제 프로젝트에 적용하면서 점진적으로 파이프라인을 개선하고 최적화하는 것이 좋습니다.