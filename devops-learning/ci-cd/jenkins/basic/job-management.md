# Jenkins Job 관리

> **목표:**  
> - Jenkins Job의 개념과 유형을 이해한다.
> - Job의 생성, 설정, 실행, 모니터링 방법을 학습한다.
> - Job의 효율적인 관리와 문제 해결 방법을 익힌다.
> - 실무에서 자주 사용되는 Job 관리 기법을 습득한다.

---

## 1. Job 개요

- **정의:**  
  Jenkins Job은 프로젝트의 빌드, 테스트, 배포 등 특정 작업을 수행하는 실행 단위입니다.
  각 Job은 독립적인 작업 공간(workspace)을 가지며, 특정 조건이나 트리거에 의해 실행됩니다.

- **Job의 중요성:**  
  Jenkins에서 Job은 자동화의 기본 단위로, 개발 프로세스의 각 단계를 자동화하고 관리하는 핵심 요소입니다.
  체계적인 Job 관리는 안정적인 CI/CD 파이프라인 운영의 기초가 됩니다.

---

## 2. Job의 유형

### 2.1 Freestyle Project
가장 기본적인 Job 유형으로, GUI를 통해 쉽게 설정할 수 있습니다. 
빌드 단계를 순차적으로 구성하며, 다양한 플러그인을 활용할 수 있습니다.

주요 설정 항목:
- 소스 코드 관리
- 빌드 트리거
- 빌드 환경
- 빌드 단계
- 빌드 후 조치

### 2.2 Pipeline Project
코드로 정의하는 Job 유형으로, 복잡한 빌드 프로세스를 체계적으로 관리할 수 있습니다.
버전 관리가 가능하고 재사용성이 높습니다.

### 2.3 Multibranch Pipeline
Git 저장소의 여러 브랜치에 대해 자동으로 파이프라인을 생성하고 관리합니다.
각 브랜치별로 독립적인 파이프라인을 운영할 수 있습니다.

### 2.4 Organization Folder
GitHub Organization이나 Bitbucket Team/Project의 모든 저장소를 자동으로 스캔하여 파이프라인을 생성합니다.

---

## 3. Job 생성과 설정

### 3.1 Freestyle Project 생성

1. Jenkins 대시보드에서 "새로운 Item" 선택
2. 프로젝트 이름 입력 및 Freestyle project 선택
3. 기본 설정
   ```plaintext
   General
   ├── 프로젝트 설명
   ├── 빌드 이력 보관 설정
   └── 동시 빌드 허용 여부

   소스 코드 관리
   ├── Git 저장소 URL
   └── 인증 정보 설정

   빌드 트리거
   ├── 주기적 실행
   ├── GitHub webhook
   └── 다른 Job 완료 후 실행

   빌드 환경
   ├── 타임아웃 설정
   └── 환경 변수 설정

   빌드 단계
   ├── Shell 명령어 실행
   ├── Maven 빌드
   └── Gradle 빌드

   빌드 후 조치
   ├── 이메일 통보
   ├── 결과물 아카이브
   └── 다른 Job 실행
   ```

### 3.2 파이프라인 Job 생성

1. "새로운 Item" 선택 후 Pipeline 프로젝트 생성
2. Pipeline 스크립트 작성
   ```groovy
   pipeline {
       agent any
       
       stages {
           stage('Preparation') {
               steps {
                   git 'https://github.com/example/repo.git'
               }
           }
           
           stage('Build') {
               steps {
                   sh 'mvn clean package'
               }
           }
           
           stage('Results') {
               steps {
                   archiveArtifacts 'target/*.jar'
               }
           }
       }
   }
   ```

---

## 4. Job 관리와 모니터링

### 4.1 Job 상태 모니터링

Jenkins는 각 Job의 상태를 다음과 같이 표시합니다:
- 파란색: 성공
- 노란색: 불안정 (테스트 실패 등)
- 빨간색: 실패
- 회색: 비활성화 또는 미실행

### 4.2 Job 이력 관리

빌드 이력은 다음 정보를 포함합니다:
- 빌드 번호와 시간
- 실행 시간
- 변경된 소스 코드
- 빌드 파라미터
- 콘솔 로그

### 4.3 Workspace 관리

Workspace는 Job이 실행되는 작업 공간입니다:
- 정기적인 정리가 필요합니다
- 디스크 공간 모니터링이 중요합니다
- 필요한 파일만 보관하도록 설정합니다

---

## 5. Job 최적화와 문제 해결

### 5.1 성능 최적화

빌드 성능 향상을 위한 방법:
- 불필요한 빌드 단계 제거
- 병렬 실행 활용
- 캐시 활용 (Maven, Gradle)
- 적절한 타임아웃 설정

### 5.2 일반적인 문제와 해결 방법

1. 빌드 실패
   - 콘솔 로그 확인
   - 환경 변수 검증
   - 권한 설정 확인
   - 네트워크 연결 확인

2. 성능 저하
   - 리소스 사용량 모니터링
   - 동시 실행 Job 수 조정
   - Workspace 정리
   - 로그 로테이션 설정

3. 디스크 공간 부족
   - 오래된 빌드 정리
   - 아티팩트 보관 정책 설정
   - Workspace 정리 자동화

---

## 6. 실무 활용 전략

### 6.1 Job 구성 전략

효율적인 Job 관리를 위한 구성 방법:
- 논리적 단위로 Job 분리
- 공통 설정의 템플릿화
- 환경별 Job 구성 (개발/스테이징/운영)
- 적절한 명명 규칙 적용

### 6.2 자동화 전략

반복 작업의 자동화:
- 주기적인 Workspace 정리
- 오래된 빌드 자동 삭제
- 빌드 결과 자동 통보
- 배포 자동화 구성

---

## 7. 보안과 권한 관리

### 7.1 Job 수준 권한 설정

프로젝트별 접근 권한 관리:
- 조회 권한
- 실행 권한
- 설정 변경 권한
- 삭제 권한

### 7.2 민감 정보 관리

보안 정보 처리 방법:
- Credentials Plugin 활용
- 환경 변수 암호화
- 보안 정보 분리 관리

---

## 8. 모니터링과 알림 설정

### 8.1 모니터링 구성

- 빌드 상태 대시보드
- 리소스 사용량 모니터링
- 빌드 시간 추이 분석
- 실패율 모니터링

### 8.2 알림 설정

- 이메일 통보
- 슬랙 연동
- MS Teams 연동
- 빌드 결과 리포트 생성

---

## 9. 참고 자료

- [Jenkins Job 관리 가이드](https://www.jenkins.io/doc/book/managing/)
- [Jenkins 보안 설정](https://www.jenkins.io/doc/book/security/)
- [Jenkins 모니터링](https://www.jenkins.io/doc/book/system-administration/monitoring/)
- [Jenkins 우수 사례](https://www.jenkins.io/doc/book/best-practices/)

---

## 마무리

Jenkins Job은 CI/CD 파이프라인의 기본 구성 요소입니다.
체계적인 Job 관리는 안정적인 빌드/배포 환경 운영의 기초가 되며, 
지속적인 모니터링과 최적화를 통해 효율적인 개발 프로세스를 구축할 수 있습니다.
실무에서는 프로젝트의 특성과 요구사항에 맞게 Job을 구성하고 관리하는 것이 중요합니다.