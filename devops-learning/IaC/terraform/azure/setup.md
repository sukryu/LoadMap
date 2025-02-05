# Azure Terraform 환경 설정 가이드

> **목표:**  
> - Azure와 Terraform 연동을 위한 환경을 구성한다.
> - 필요한 도구들을 설치하고 기본 설정을 완료한다.
> - 보안을 고려한 Azure 계정 설정 방법을 이해한다.
> - 실제 프로젝트를 시작할 수 있는 기반을 마련한다.

---

## 1. 사전 준비사항

### Azure 계정 준비
Azure 계정이 없는 경우, Microsoft Azure 공식 웹사이트에서 새로운 계정을 생성해야 합니다. Azure 계정을 생성할 때는 다음 사항에 주의해야 합니다.

1. Azure 구독 활성화
2. 다단계 인증(MFA) 설정
3. 비용 알림 및 예산 설정
4. Resource Group 생성 권한 확인

### 필수 소프트웨어 설치
환경 구성을 위해 다음 소프트웨어들이 필요합니다.

1. Azure CLI 설치
2. Terraform 설치
3. 텍스트 에디터 (VS Code 권장)

---

## 2. Azure CLI 설치 및 구성

### Azure CLI 설치
운영체제별 설치 방법이 다르므로, 해당하는 방법을 선택하여 진행합니다.

Windows의 경우:
```powershell
# MSI 인스톨러를 다운로드하여 실행
# https://aka.ms/installazurecliwindows
```

macOS의 경우:
```bash
brew update && brew install azure-cli
```

Linux의 경우:
```bash
curl -sL https://aka.ms/InstallAzureCLIDeb | sudo bash
```

### Azure CLI 로그인
Azure CLI를 설치한 후, 다음 명령어로 Azure에 로그인합니다.

```bash
az login
```

이 명령어를 실행하면 브라우저가 열리며 Microsoft 계정으로 로그인할 수 있습니다.

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

## 4. Azure Service Principal 설정

### Service Principal 생성
Terraform이 Azure 리소스를 관리하기 위해서는 Service Principal이 필요합니다.

```bash
# Service Principal 생성
az ad sp create-for-rbac --name "terraform-sp" --role="Contributor" --scopes="/subscriptions/SUBSCRIPTION_ID"

# 출력 예시
{
  "appId": "00000000-0000-0000-0000-000000000000",
  "displayName": "terraform-sp",
  "password": "your-client-secret",
  "tenant": "00000000-0000-0000-0000-000000000000"
}
```

### 환경 변수 설정
Service Principal 정보를 환경 변수로 설정합니다.

Windows의 경우:
```powershell
$env:ARM_CLIENT_ID="appId값"
$env:ARM_CLIENT_SECRET="password값"
$env:ARM_SUBSCRIPTION_ID="구독ID"
$env:ARM_TENANT_ID="tenant값"
```

Linux/macOS의 경우:
```bash
export ARM_CLIENT_ID="appId값"
export ARM_CLIENT_SECRET="password값"
export ARM_SUBSCRIPTION_ID="구독ID"
export ARM_TENANT_ID="tenant값"
```

---

## 5. 프로젝트 구성

### 기본 디렉토리 구조 생성
```
terraform-azure-project/
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
    azurerm = {
      source  = "hashicorp/azurerm"
      version = "~> 3.0"
    }
  }
}

provider "azurerm" {
  features {}
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
resource "azurerm_resource_group" "example" {
  name     = "example-resources"
  location = "Korea Central"
}

resource "azurerm_storage_account" "example" {
  name                     = "examplestorageaccount"
  resource_group_name      = azurerm_resource_group.example.name
  location                 = azurerm_resource_group.example.location
  account_tier             = "Standard"
  account_replication_type = "LRS"
}
```

---

## 7. 보안 고려사항

### 중요 정보 관리
1. Service Principal 자격 증명은 안전하게 관리
2. Key Vault 사용 고려
3. RBAC 권한 최소화
4. 정기적인 자격 증명 순환

### 상태 파일 관리
1. Azure Storage Account를 사용한 원격 상태 관리
2. 상태 파일 암호화
3. 접근 제어 설정

---

## 8. 문제 해결

### 일반적인 문제와 해결 방법

1. **인증 관련 오류**
   - Service Principal 자격 증명 확인
   - 권한 설정 검증
   - Azure CLI 로그인 상태 확인

2. **리소스 생성 오류**
   - 리소스 이름 중복 확인
   - 할당량 제한 확인
   - 리전 가용성 확인

3. **상태 파일 오류**
   - Storage Account 접근성 확인
   - 백엔드 구성 검증
   - 상태 파일 잠금 해제 확인

---

## 참고 자료

- [Azure Provider 공식 문서](https://registry.terraform.io/providers/hashicorp/azurerm/latest/docs)
- [Azure CLI 설치 가이드](https://docs.microsoft.com/cli/azure/install-azure-cli)
- [Terraform 설치 가이드](https://learn.hashicorp.com/tutorials/terraform/install-cli)
- [Azure Service Principal 생성 가이드](https://docs.microsoft.com/azure/active-directory/develop/howto-create-service-principal-portal)

---

## 마무리

이 환경 설정 가이드를 따라 설정을 완료하면, Azure에서 Terraform을 사용하여 인프라를 관리할 수 있는 기본 환경이 구성됩니다. Service Principal의 안전한 관리와 적절한 권한 설정이 특히 중요하며, 이를 기반으로 안전하고 효율적인 인프라 관리가 가능해집니다. 문제가 발생할 경우, 문제 해결 섹션을 참조하거나 Azure 공식 문서를 확인하시기 바랍니다.