# Azure에서의 Terraform 활용 개요

> **목표:**  
> - Azure 인프라를 코드로 관리하는 방법을 이해한다.
> - Terraform을 사용하여 Azure 리소스를 자동으로 생성하고 관리하는 방법을 습득한다.
> - 실무에서 자주 사용되는 Azure 리소스 관리 패턴을 학습한다.
> - 비용 효율적이고 안전한 클라우드 인프라 관리 방법을 익힌다.

---

## 1. Terraform과 Azure 통합이란?

### 정의
Terraform은 Azure 인프라를 코드로 정의하고 관리할 수 있게 해주는 Infrastructure as Code(IaC) 도구입니다. Azure Portal에서 수동으로 리소스를 생성하는 대신, Terraform을 사용하면 가상 머신, 스토리지 계정, 네트워크 등의 Azure 리소스를 코드로 작성하고 관리할 수 있습니다.

### 왜 필요한가?
- **인프라 자동화:** 반복적인 Azure 리소스 생성 및 관리 작업을 자동화하여 시간을 절약합니다.
- **구성 표준화:** 모든 환경에서 동일한 설정과 구성을 유지할 수 있습니다.
- **버전 관리:** Git과 같은 버전 관리 시스템을 통해 인프라 변경 사항을 추적하고 관리할 수 있습니다.
- **비용 최적화:** 필요한 리소스만 정확하게 프로비저닝하여 비용을 효율적으로 관리할 수 있습니다.

---

## 2. 핵심 구성 요소

### 2.1 Provider 설정
Azure와 Terraform을 연결하기 위한 기본 설정입니다.

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

### 2.2 리소스 그룹
Azure의 모든 리소스는 리소스 그룹 내에 존재해야 합니다.

```hcl
resource "azurerm_resource_group" "example" {
  name     = "example-resources"
  location = "Korea Central"
  
  tags = {
    environment = "Production"
    department  = "IT"
  }
}
```

### 2.3 상태 관리
Terraform 상태를 Azure Storage Account에 저장하여 팀 협업을 가능하게 합니다.

```hcl
terraform {
  backend "azurerm" {
    resource_group_name  = "terraform-state-rg"
    storage_account_name = "terraformstate"
    container_name       = "tfstate"
    key                 = "prod.terraform.tfstate"
  }
}
```

---

## 3. Azure 리소스 관리

### 3.1 네트워크 구성
Azure Virtual Network와 서브넷 설정:

```hcl
resource "azurerm_virtual_network" "example" {
  name                = "example-network"
  resource_group_name = azurerm_resource_group.example.name
  location            = azurerm_resource_group.example.location
  address_space       = ["10.0.0.0/16"]
}

resource "azurerm_subnet" "example" {
  name                 = "internal"
  resource_group_name  = azurerm_resource_group.example.name
  virtual_network_name = azurerm_virtual_network.example.name
  address_prefixes     = ["10.0.1.0/24"]
}
```

### 3.2 가상 머신 배포
Azure Virtual Machine 생성:

```hcl
resource "azurerm_virtual_machine" "example" {
  name                  = "example-vm"
  location              = azurerm_resource_group.example.location
  resource_group_name   = azurerm_resource_group.example.name
  network_interface_ids = [azurerm_network_interface.example.id]
  vm_size              = "Standard_B1s"

  storage_image_reference {
    publisher = "Canonical"
    offer     = "UbuntuServer"
    sku       = "18.04-LTS"
    version   = "latest"
  }
}
```

---

## 4. 작업 순서

### 4.1 기본 워크플로우
1. Azure 구독 준비 및 인증 설정
2. Terraform 구성 파일 작성
3. `terraform init`으로 초기화
4. `terraform plan`으로 변경 사항 확인
5. `terraform apply`로 인프라 배포
6. `terraform destroy`로 리소스 정리

### 4.2 모범 사례
- 모든 리소스에 태그 지정
- 리소스 명명 규칙 준수
- 적절한 접근 제어 설정
- 비용 모니터링 구성

---

## 5. Azure 특화 기능

### 5.1 Azure Key Vault 통합
중요한 정보를 안전하게 관리:

```hcl
resource "azurerm_key_vault" "example" {
  name                = "example-keyvault"
  location            = azurerm_resource_group.example.location
  resource_group_name = azurerm_resource_group.example.name
  tenant_id          = data.azurerm_client_config.current.tenant_id
  sku_name           = "standard"
}
```

### 5.2 Managed Identities 활용
Azure 서비스 간 안전한 인증:

```hcl
resource "azurerm_user_assigned_identity" "example" {
  name                = "example-identity"
  location            = azurerm_resource_group.example.location
  resource_group_name = azurerm_resource_group.example.name
}
```

---

## 6. 보안 및 모범 사례

### 6.1 보안 고려사항
- RBAC(Role-Based Access Control) 구현
- 네트워크 보안 그룹 적절히 구성
- 암호화 설정 활성화
- 정기적인 보안 감사 수행

### 6.2 비용 최적화
- 적절한 크기의 리소스 선택
- 자동 스케일링 구현
- 사용하지 않는 리소스 자동 정리
- 예약 인스턴스 활용

---

## 7. 문제 해결

### 7.1 일반적인 문제
- 인증 및 권한 오류
- 리소스 할당량 초과
- 네트워크 구성 문제
- 상태 파일 충돌

### 7.2 해결 방법
- Azure CLI를 사용한 문제 진단
- Terraform 로그 확인
- Azure Portal에서 리소스 상태 확인
- Microsoft 문서 참조

---

## 참고 자료

- [Azure Provider 공식 문서](https://registry.terraform.io/providers/hashicorp/azurerm/latest/docs)
- [Azure Architecture Center](https://docs.microsoft.com/azure/architecture/)
- [Terraform Azure 예제](https://github.com/terraform-providers/terraform-provider-azurerm/tree/main/examples)

---

## 마무리

Azure에서 Terraform을 활용하면 클라우드 인프라를 효율적으로 관리할 수 있습니다. 이 문서에서 다룬 기본 개념과 예제를 바탕으로 실제 프로젝트에 적용하면서, 점진적으로 더 복잡한 인프라 관리 방법을 익힐 수 있습니다. Azure의 특성을 잘 이해하고 Terraform의 기능을 적절히 활용하면, 안정적이고 확장 가능한 클라우드 환경을 구축할 수 있습니다.