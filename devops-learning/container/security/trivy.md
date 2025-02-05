# Trivy를 활용한 컨테이너 이미지 보안 검사 가이드

> **목표:**  
> - Trivy의 기본 개념과 설치 방법을 이해한다.
> - 컨테이너 이미지 취약점 검사 방법을 습득한다.
> - CI/CD 파이프라인에 보안 검사를 통합한다.
> - 보안 정책 설정과 관리 방법을 익힌다.

---

## 1. Trivy 개요

Trivy는 컨테이너 이미지, 파일시스템, Git 저장소의 취약점을 검사하는 오픈소스 보안 스캐너입니다. 간단한 사용법과 높은 정확도, 빠른 검사 속도가 특징이며, CI/CD 파이프라인에 쉽게 통합할 수 있습니다.

### 주요 기능
- OS 패키지 취약점 검사
- 애플리케이션 의존성 취약점 검사
- IaC(Infrastructure as Code) 보안 검사
- 기밀 정보 탐지
- 라이선스 컴플라이언스 검사

---

## 2. Trivy 설치 및 설정

### 2.1 설치 방법

운영체제별 설치 명령어:

```bash
# Ubuntu
sudo apt-get install wget apt-transport-https gnupg lsb-release
wget -qO - https://aquasecurity.github.io/trivy-repo/deb/public.key | sudo apt-key add -
echo deb https://aquasecurity.github.io/trivy-repo/deb $(lsb_release -sc) main | sudo tee -a /etc/apt/sources.list.d/trivy.list
sudo apt-get update
sudo apt-get install trivy

# macOS
brew install aquasecurity/trivy/trivy

# Docker
docker pull aquasec/trivy
```

### 2.2 기본 설정

Trivy 설정 파일 예시 (trivy.yaml):

```yaml
# 취약점 데이터베이스 위치 설정
cache:
  dir: ~/.cache/trivy

# 출력 형식 설정
format: table

# 심각도 레벨 설정
severity: ["HIGH", "CRITICAL"]

# 무시할 취약점 설정
ignorefile: .trivyignore
```

---

## 3. 이미지 취약점 검사

### 3.1 기본 검사

컨테이너 이미지 검사 실행:

```bash
# 기본 검사
trivy image nginx:latest

# 심각도 필터링
trivy image --severity HIGH,CRITICAL nginx:latest

# JSON 형식으로 출력
trivy image -f json -o results.json nginx:latest
```

### 3.2 고급 검사 옵션

상세한 검사 설정:

```bash
# 취약점 데이터베이스 업데이트 없이 검사
trivy image --skip-update nginx:latest

# 특정 취약점 무시
trivy image --ignorefile .trivyignore nginx:latest

# 상세 정보 출력
trivy image --debug nginx:latest
```

---

## 4. CI/CD 통합

### 4.1 GitHub Actions 통합

GitHub Actions 워크플로우 예시:

```yaml
name: Security Scan

on: [push]

jobs:
  scan:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout code
        uses: actions/checkout@v2

      - name: Build image
        run: docker build -t app:${{ github.sha }} .

      - name: Run Trivy vulnerability scanner
        uses: aquasecurity/trivy-action@master
        with:
          image-ref: 'app:${{ github.sha }}'
          format: 'table'
          exit-code: '1'
          ignore-unfixed: true
          severity: 'CRITICAL,HIGH'
```

### 4.2 Jenkins 통합

Jenkinsfile 예시:

```groovy
pipeline {
    agent any
    
    stages {
        stage('Build') {
            steps {
                sh 'docker build -t app:${BUILD_NUMBER} .'
            }
        }
        
        stage('Security Scan') {
            steps {
                sh '''
                    trivy image \
                    --exit-code 1 \
                    --severity HIGH,CRITICAL \
                    --no-progress \
                    app:${BUILD_NUMBER}
                '''
            }
        }
    }
}
```

---

## 5. 보안 정책 관리

### 5.1 취약점 관리 정책

.trivyignore 파일을 통한 취약점 예외 처리:

```text
# 특정 취약점 ID 무시
CVE-2021-XXXXX

# 특정 패키지의 취약점 무시
python-requests-2.26.0: CVE-2021-YYYYY
```

### 5.2 보안 기준 설정

Trivy 설정을 통한 보안 기준 정의:

```yaml
# trivy.yaml
vulnerability:
  type:
    - os
    - library
  severity:
    - HIGH
    - CRITICAL
  ignore-unfixed: true
  ignore-file: .trivyignore
```

---

## 6. 모니터링 및 보고

### 6.1 보고서 생성

다양한 형식의 보고서 생성:

```bash
# HTML 보고서
trivy image -f template --template "@html.tpl" -o report.html nginx:latest

# SARIF 형식
trivy image -f sarif -o results.sarif nginx:latest

# JSON 형식의 상세 보고서
trivy image -f json --list-all-pkgs -o detailed-report.json nginx:latest
```

### 6.2 결과 분석

보안 검사 결과 해석 및 조치:

1. 취약점 우선순위화
2. 패치 및 업데이트 계획 수립
3. 지속적인 모니터링 체계 구축

---

## 7. 문제 해결 및 최적화

### 7.1 일반적인 문제 해결

자주 발생하는 문제들의 해결 방법:

```bash
# 데이터베이스 강제 업데이트
trivy image --clear-cache && trivy image --download-db-only

# 디버그 모드로 문제 분석
trivy image --debug nginx:latest

# 캐시 삭제 후 재검사
trivy image --clear-cache nginx:latest
```

### 7.2 성능 최적화

검사 성능 향상을 위한 설정:

```bash
# 경량 데이터베이스 사용
trivy image --light nginx:latest

# 캐시 활용
trivy image --cache-dir /path/to/cache nginx:latest
```

---

## 참고 자료

- [Trivy 공식 문서](https://aquasecurity.github.io/trivy/)
- [Trivy GitHub 저장소](https://github.com/aquasecurity/trivy)
- [Aqua Security 블로그](https://blog.aquasec.com/)

---

## 마무리

Trivy를 활용한 컨테이너 이미지 보안 검사는 현대 DevSecOps 환경에서 필수적인 요소입니다. 이 문서에서 다룬 내용을 바탕으로 효과적인 보안 검사 체계를 구축하고, CI/CD 파이프라인에 통합하여 지속적인 보안 모니터링을 수행할 수 있습니다. 특히 자동화된 검사와 보고 체계를 통해 보안 위험을 사전에 식별하고 대응할 수 있습니다.