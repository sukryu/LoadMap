# GitHub Actions for CI/CD in Go 🚀

이 디렉토리는 Go 애플리케이션을 위한 CI/CD 파이프라인을 GitHub Actions를 통해 자동화하는 방법을 다룹니다.  
이 자료를 통해 코드를 빌드, 테스트, 그리고 배포하는 워크플로우를 설정하고, GitHub Actions의 다양한 기능과 Best Practice를 학습할 수 있습니다.

---

## What You'll Learn 🎯

- **GitHub Actions 기본 개념**  
  - 워크플로우, 작업(Job), 스텝(Step) 및 이벤트(trigger)의 이해
- **CI/CD 파이프라인 구성**  
  - 코드 체크아웃, 의존성 설치, 테스트, 빌드, 배포 단계를 자동화하는 방법
- **Go 애플리케이션 테스트 및 빌드**  
  - `go test`를 이용한 단위 테스트 실행, `go build`를 통한 바이너리 생성
- **환경 변수 및 시크릿 관리**  
  - GitHub Secrets를 사용하여 민감 정보를 안전하게 관리하는 방법
- **캐시 활용과 최적화**  
  - 작업 속도를 높이기 위해 의존성 캐싱 등 최적화 기법 적용

---

## Directory Structure 📁

```plaintext
09-ci-cd-devops/
└── github-actions/
    ├── .github/workflows/         # GitHub Actions 워크플로우 YAML 파일들
    │    └── ci.yml                # 예제 CI/CD 워크플로우 파일
    ├── sample-workflow.yml         # 추가 예제 워크플로우 파일 (옵션)
    └── README.md                   # 이 문서
```

- **.github/workflows/**:  
  - GitHub Actions가 인식하는 워크플로우 파일들을 포함합니다.
- **sample-workflow.yml**:  
  - CI/CD 파이프라인 예제(빌드, 테스트, 배포)를 보여주는 추가 파일입니다.

---

## Getting Started 🚀

### 1. Prerequisites
- GitHub 리포지토리와 GitHub Actions 활성화
- 필요한 시크릿(예: 클라우드 인증서, 배포 키 등)을 리포지토리 설정에 등록

### 2. Workflow 예제 설정
1. **워크플로우 파일 생성**:  
   - 리포지토리 내 `.github/workflows/ci.yml` 파일을 생성합니다.
2. **예제 워크플로우 내용**:
   ```yaml
   name: CI/CD Pipeline

   on:
     push:
       branches:
         - main
     pull_request:
       branches:
         - main

   jobs:
     build:
       runs-on: ubuntu-latest

       steps:
       - name: Checkout Code
         uses: actions/checkout@v2

       - name: Set up Go
         uses: actions/setup-go@v2
         with:
           go-version: 1.20

       - name: Cache Go Modules
         uses: actions/cache@v2
         with:
           path: ~/go/pkg/mod
           key: ${{ runner.os }}-go-${{ hashFiles('**/go.sum') }}
           restore-keys: |
             ${{ runner.os }}-go-

       - name: Install Dependencies
         run: go mod download

       - name: Run Tests
         run: go test ./... -v

       - name: Build Application
         run: go build -o myapp .

       # (Optional) 배포 단계
       # - name: Deploy Application
       #   run: ./deploy.sh
   ```

### 3. 실행 및 모니터링
- GitHub에 코드를 푸시하면 자동으로 워크플로우가 실행됩니다.
- Actions 탭에서 빌드, 테스트, 배포 결과와 로그를 확인할 수 있습니다.

---

## Best Practices & Tips 💡

- **모듈화된 워크플로우**:  
  - 각 단계(빌드, 테스트, 배포)를 별도의 잡으로 분리하여 문제를 쉽게 파악하고 관리하세요.
- **캐싱 활용**:  
  - 의존성 캐시를 활용해 빌드 시간을 단축하세요.
- **환경 변수 및 시크릿 관리**:  
  - 민감 정보는 GitHub Secrets를 통해 관리하고, 코드 내에 노출되지 않도록 하세요.
- **자동화된 테스트**:  
  - CI 단계에서 충분한 테스트를 실행하여, 코드 품질을 유지하세요.
- **알림 설정**:  
  - 빌드 실패 시 Slack, 이메일 등의 알림 연동을 통해, 팀원들과 신속하게 소통할 수 있도록 설정하세요.

---

## Next Steps

- **고급 워크플로우 확장**:  
  - 멀티-OS 또는 멀티-버전 테스트를 위한 매트릭스 빌드를 실습해 보세요.
- **배포 자동화**:  
  - Terraform, Helm, ArgoCD 등을 활용한 배포 자동화 단계를 추가해 보세요.
- **모니터링 및 롤백 전략**:  
  - 배포 후 성능 모니터링 및 문제 발생 시 자동 롤백 전략을 수립해 보세요.

---

## References 📚

- [GitHub Actions Documentation](https://docs.github.com/en/actions)
- [Actions Setup-Go](https://github.com/actions/setup-go)
- [Effective CI/CD with GitHub Actions](https://github.com/features/actions)
- [Go Modules Documentation](https://blog.golang.org/using-go-modules)

---

GitHub Actions를 통해 자동화된 CI/CD 파이프라인을 구축하면, 코드의 품질을 높이고 빠른 피드백을 받을 수 있습니다.  
이 자료를 활용하여 Go 애플리케이션의 지속적 통합과 배포를 효율적으로 구현해 보세요! Happy Automating! 🚀