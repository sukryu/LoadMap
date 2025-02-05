# GCP Terraform 환경 설정 가이드

> **목표:**  
> - GCP와 Terraform 연동을 위한 환경을 구성한다.
> - 필요한 도구들을 설치하고 기본 설정을 완료한다.
> - 보안을 고려한 GCP 계정 설정 방법을 이해한다.
> - 실제 프로젝트를 시작할 수 있는 기반을 마련한다.

---

## 1. 사전 준비사항

### GCP 계정 준비
GCP 계정이 없는 경우, Google Cloud 공식 웹사이트에서 새로운 계정을 생성해야 합니다. GCP 계정을 생성할 때는 다음 사항에 주의해야 합니다.

1. Google 계정으로 GCP Console 접속
2. 프로젝트 생성 및 결제 계정 연결
3. 비용 알림 설정
4. IAM 권한 설정 확인

### 필수 소프트웨어 설치
환경 구성을 위해 다음 소프트웨어들이 필요합니다.

1. Google Cloud SDK 설치
2. Terraform 설치
3. 텍스트 에디터 (VS Code 권장)

---

## 2. Google Cloud SDK 설치 및 구성

### Google Cloud SDK 설치
운영체제별 설치 방법이 다르므로, 해당하는 방법을 선택하여 진행합니다.

Windows의 경우:
```powershell
# 공식 설치 프로그램 다운로드 및 실행
# https://dl.google.com/dl/cloudsdk/channels/rapid/GoogleCloudSDKInstaller.exe
```

macOS의 경우:
```bash
# Homebrew를 사용하는 경우
brew install --cask google-cloud-sdk
```

Linux의 경우:
```bash
# Debian/Ubuntu
curl https://packages.cloud.google.com/apt/doc/apt-key.gpg | sudo apt-key add -
echo "deb https://packages.cloud.google.com/apt cloud-sdk main" | sudo tee -a /etc/apt/sources.list.d/google-cloud-sdk.list
sudo apt-get update && sudo apt-get install google-cloud-sdk
```

### Google Cloud SDK 초기 설정
설치 후 다음 명령어로 초기 설정을 진행합니다.

```bash
# GCP 로그인
gcloud auth login

# 프로젝트 설정
gcloud config set project [PROJECT_ID]

# 기본 리전 설정
gcloud config set compute/region asia-northeast3
```

---

## 3. Terraform 설치

### 운영체제별 설치 방법

Windows의 경우:
```powershell
# Chocolatey를 사용하는 경우
choco install terraform

# 또는 공식 웹사이트에서 ZIP 파일을 다운로드하여 설치
```

macOS의 경우:
```bash
brew tap hashicorp/tap
brew install hashicorp/tap/terraform
```

Linux의 경우:
```bash
sudo apt-get update && sudo apt-get install -y gnupg software-properties-common curl
curl -fsSL https://apt.releases.hashicorp.com/gpg | sudo apt-key add -
sudo apt-add-repository "deb [arch=amd64] https://apt.releases.hashicorp.com $(lsb_release -cs) main"
sudo apt-get update && sudo apt-get install terraform
```

### 설치 확인
설치가 완료되면 다음 명령어로 버전을 확인합니다.

```bash
terraform version
```

---

## 4. GCP 서비스 계정 설정

### 서비스 계정 생성 및 키 발급
Terraform이 GCP 리소스를 관리하기 위한 서비스 계정을 생성합니다.

```bash
# 서비스 계정 생성
gcloud iam service-accounts create terraform-sa --display-name="Terraform Service Account"

# 서비스 계정에 권한 부여
gcloud projects add-iam-policy-binding [PROJECT_ID] \
  --member="serviceAccount:terraform-sa@[PROJECT_ID].iam.gserviceaccount.com" \
  --role="roles/editor"

# 키 파일 생성
gcloud iam service-accounts keys create terraform-sa-key.json \
  --iam-account=terraform-sa@[PROJECT_ID].iam.gserviceaccount.com
```

### 환경 변수 설정
서비스 계정 키를 환경 변수로 설정합니다.

Windows의 경우:
```powershell
$env:GOOGLE_APPLICATION_CREDENTIALS="path\to\terraform-sa-key.json"
```

Linux/macOS의 경우:
```bash
export GOOGLE_APPLICATION_CREDENTIALS="path/to/terraform-sa-key.json"
```

---

## 5. 프로젝트 구성

### 기본 디렉토리 구조 생성
```
terraform-gcp-project/
├── main.tf           # 주요 리소스 정의
├── variables.tf      # 변수 정의
├── outputs.tf        # 출력 정의
├── providers.tf      # 공급자 설정
└── terraform.tfvars  # 변수값 설정
```

### providers.tf 파일 설정
```hcl
terraform {
  required_providers {
    google = {
      source  = "hashicorp/google"
      version = "~> 4.0"
    }
  }
}

provider "google" {
  project = var.project_id
  region  = var.region
}
```

### .gitignore 파일 설정
```gitignore
# Local .terraform directories
**/.terraform/*

# .tfstate files
*.tfstate
*.tfstate.*

# Crash log files
crash.log

# Exclude sensitive variables files
*.tfvars
terraform-sa-key.json
```

---

## 6. 환경 검증

### 초기화 및 테스트
프로젝트 디렉토리에서 다음 명령어를 실행하여 설정을 검증합니다.

```bash
# Terraform 초기화
terraform init

# 구성 검증
terraform validate

# 실행 계획 확인
terraform plan
```

### 간단한 테스트 리소스 생성
```hcl
# main.tf
resource "google_storage_bucket" "test" {
  name     = "test-bucket-${random_id.suffix.hex}"
  location = "ASIA-NORTHEAST3"
}

resource "random_id" "suffix" {
  byte_length = 4
}
```

---

## 7. 보안 고려사항

### 중요 정보 관리
1. 서비스 계정 키 파일을 안전하게 보관
2. Secret Manager 사용 고려
3. IAM 권한 최소화
4. 정기적인 키 순환

### 상태 파일 관리
1. Google Cloud Storage를 사용한 원격 상태 관리
2. 상태 파일 암호화
3. 접근 제어 설정

---

## 8. 문제 해결

### 일반적인 문제와 해결 방법

1. **인증 관련 오류**
   - 서비스 계정 키 경로 확인
   - IAM 권한 검증
   - gcloud 인증 상태 확인

2. **리소스 생성 오류**
   - 할당량 제한 확인
   - API 활성화 상태 확인
   - 리전 가용성 확인

3. **상태 파일 오류**
   - GCS 버킷 접근성 확인
   - 백엔드 구성 검증
   - 상태 파일 잠금 해제 확인

---

## 참고 자료

- [Google Cloud Provider 공식 문서](https://registry.terraform.io/providers/hashicorp/google/latest/docs)
- [Google Cloud SDK 설치 가이드](https://cloud.google.com/sdk/docs/install)
- [Terraform 설치 가이드](https://learn.hashicorp.com/tutorials/terraform/install-cli)
- [GCP 서비스 계정 문서](https://cloud.google.com/iam/docs/creating-managing-service-accounts)

---

## 마무리

이 환경 설정 가이드를 따라 설정을 완료하면, GCP에서 Terraform을 사용하여 인프라를 관리할 수 있는 기본 환경이 구성됩니다. 서비스 계정의 안전한 관리와 적절한 권한 설정이 특히 중요하며, 이를 기반으로 안전하고 효율적인 인프라 관리가 가능해집니다. 문제가 발생할 경우, 문제 해결 섹션을 참조하거나 GCP 공식 문서를 확인하시기 바랍니다.