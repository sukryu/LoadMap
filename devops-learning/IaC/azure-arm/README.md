# 📂 Azure Resource Manager (ARM) Templates 학습 개요

> **목표:**  
> - **Azure Resource Manager (ARM) Templates을 활용하여 Azure 인프라를 자동화하는 방법을 학습**한다.  
> - **Infrastructure as Code(IaC) 개념을 적용하여 Azure 리소스를 코드로 정의하고 관리한다.**  
> - **기본 개념과 명령어를 학습한 후, 고급 기능 및 실무 활용 전략을 익힌다.**  
> - **이론 → 도구 실습 → 프로젝트 적용 → 최적화의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **Azure ARM Templates 학습을 기본(Basic)과 고급(Advanced)으로 나누어 진행합니다.**  

```
azure-arm/
├── introduction.md  # Azure ARM Templates 개요 및 기본 개념
├── setup.md         # ARM Templates 개발 환경 설정
├── examples.md      # Azure 인프라 코드 예제
└── README.md
```

---

## 📖 **1. 기본 개념 개요**
> **Azure Resource Manager (ARM) Templates는 JSON 기반으로 Azure 리소스를 정의하고 배포할 수 있는 Infrastructure as Code(IaC) 솔루션입니다.**

- ✅ **Declarative Syntax:** 리소스 상태를 JSON 파일로 정의하여 자동 배포  
- ✅ **Resource Group:** Azure 리소스를 그룹화하여 효율적으로 관리  
- ✅ **Parameterization:** 다양한 환경을 지원하기 위한 템플릿 매개변수 설정  
- ✅ **Modularity:** 재사용 가능한 템플릿을 활용한 구조화된 코드 관리  
- ✅ **Security & Compliance:** RBAC 및 정책을 통해 보안 및 거버넌스 강화  

---

## 🏗 **2. 학습 내용**
### 📌 ARM Templates Setup (환경 설정)
- **Azure CLI 및 ARM Template 배포 도구 설치**
- **ARM Templates 기본 JSON 구조 이해**
- **템플릿 매개변수 및 변수 활용법 학습**

### 📌 Azure 리소스 배포 예제
- **Azure Virtual Machine (VM) 배포 및 관리**
- **Azure Storage 계정 및 Blob 컨테이너 생성**
- **Azure Virtual Network 및 서브넷 구성**
- **Azure SQL Database 및 백업 설정**

### 📌 ARM Templates 고급 활용법
- **Nested Templates를 활용한 복잡한 배포 자동화**
- **ARM Templates와 Azure DevOps를 이용한 CI/CD 구축**
- **Bicep을 활용한 ARM Templates 코드 최적화**

---

## 🚀 **3. 실전 예제**
> **ARM Templates를 활용하여 Azure Virtual Machine을 배포하는 예제**

```json
{
  "$schema": "https://schema.management.azure.com/schemas/2019-04-01/deploymentTemplate.json#",
  "contentVersion": "1.0.0.0",
  "resources": [
    {
      "type": "Microsoft.Compute/virtualMachines",
      "apiVersion": "2021-03-01",
      "name": "example-vm",
      "location": "eastus",
      "properties": {
        "hardwareProfile": {
          "vmSize": "Standard_DS1_v2"
        },
        "osProfile": {
          "computerName": "examplevm",
          "adminUsername": "azureuser",
          "adminPassword": "P@ssw0rd123!"
        }
      }
    }
  ]
}
```

```sh
# ARM Templates 배포 절차
az deployment group create --resource-group myResourceGroup --template-file template.json
```

---

## 🎯 **4. 학습 방법**
1. **이론 학습** → ARM Templates 개념과 JSON 구조 이해  
2. **도구 실습** → Azure CLI 및 ARM Templates 활용하여 리소스 배포  
3. **프로젝트 적용** → 실제 프로젝트에서 ARM Templates 활용한 Azure 인프라 자동화  
4. **최적화 연구** → 성능, 보안, 비용 최적화 전략 연구  

---

## 📚 **5. 추천 리소스**
- **ARM Templates 공식 문서:**  
  - [ARM Templates Docs](https://learn.microsoft.com/en-us/azure/azure-resource-manager/templates/overview)  
  - [Azure CLI Docs](https://learn.microsoft.com/en-us/cli/azure/)  

- **ARM Templates 예제 및 템플릿:**  
  - [Azure Quickstart Templates](https://github.com/Azure/azure-quickstart-templates)  
  - [Awesome ARM Templates](https://github.com/Azure/awesome-azure-templates)  

---

## ✅ **마무리**
이 문서는 **Azure Resource Manager (ARM) Templates을 활용한 인프라 자동화의 기본 개념부터 실무 활용까지 학습하기 위한 로드맵**입니다.  
각 개념을 **이론 → 도구 실습 → 프로젝트 적용 → 최적화**의 단계로 학습하며, **실무에서 ARM Templates을 효과적으로 활용하는 방법**을 다룹니다. 🚀