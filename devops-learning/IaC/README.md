# 📂 Infrastructure as Code (IaC) 학습 개요

> **목표:**  
> - **Infrastructure as Code(IaC)의 개념과 실무 적용 방법을 학습**한다.  
> - **Terraform, CloudFormation, Azure ARM, Ansible을 활용한 인프라 자동화 기법을 익힌다.**  
> - **코드 기반 인프라 구축 및 운영을 효율적으로 관리하는 전략을 학습한다.**  
> - **이론 → 도구 실습 → 프로젝트 적용 → 사례 분석의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **각 디렉토리는 IaC의 핵심 개념과 도구를 포함하며, 하위 디렉토리는 보다 상세한 학습 주제를 다룹니다.**  

```
infrastructure-as-code/
├── terraform
│   ├── aws
│   ├── azure
│   └── gcp
│
├── cloudformation
├── azure-arm
└── ansible
```

---

## 📖 **1. 핵심 개념 개요**
> **Infrastructure as Code(IaC)는 인프라를 코드로 관리하여 일관성과 확장성을 제공하는 DevOps의 핵심 개념입니다.**

- ✅ **IaC의 필요성 및 개념**  
- ✅ **Terraform을 활용한 멀티 클라우드 인프라 관리**  
- ✅ **CloudFormation 및 Azure ARM을 활용한 클라우드 리소스 관리**  
- ✅ **Ansible을 활용한 서버 프로비저닝 및 설정 관리**  

---

## 🏗 **2. 학습 내용**
### 📌 Terraform
- **Terraform 기본 개념 및 HCL(HashiCorp Configuration Language) 문법**
- **AWS, Azure, GCP 인프라 코드화 및 관리**
- **Terraform 모듈화 및 상태 관리**

### 📌 CloudFormation
- **AWS CloudFormation 템플릿 구조 이해**
- **스택(Stack) 및 스택 세트(StackSet) 관리**
- **Infrastructure as Code를 통한 AWS 자동화**

### 📌 Azure Resource Manager (ARM)
- **Azure ARM 템플릿 구조 및 배포 방식 이해**
- **Azure 리소스 프로비저닝 자동화**

### 📌 Ansible
- **Ansible 플레이북 작성 및 실행**
- **구성 관리(Configuration Management) 및 서버 프로비저닝**
- **멀티 서버 환경 자동화 적용**

---

## 🚀 **3. 실전 사례 분석**
> **IaC 도구를 활용한 대규모 인프라 자동화 및 관리 사례를 분석합니다.**

- **Netflix** - Terraform을 활용한 대규모 클라우드 인프라 관리  
- **Airbnb** - Ansible을 통한 자동화된 서버 구성 관리  
- **Microsoft** - Azure ARM을 이용한 엔터프라이즈 클라우드 관리  

---

## 🎯 **4. 학습 방법**
1. **이론 학습** → IaC 개념과 원리 이해  
2. **도구 실습** → Terraform, CloudFormation, Azure ARM, Ansible 실습 진행  
3. **프로젝트 적용** → 실전 환경에서 IaC를 활용한 인프라 구축 및 운영  
4. **사례 분석** → 다양한 기업의 IaC 운영 전략 연구  

---

## 📚 **5. 추천 리소스**
- **책:**  
  - _Terraform Up & Running_ - Yevgeniy Brikman  
  - _Ansible for DevOps_ - Jeff Geerling  

- **GitHub 레포지토리:**  
  - [Awesome Terraform](https://github.com/shuaibiyy/awesome-terraform)  
  - [Awesome Ansible](https://github.com/ansible/ansible)  

- **공식 문서:**  
  - [Terraform Docs](https://developer.hashicorp.com/terraform/docs)  
  - [AWS CloudFormation Docs](https://docs.aws.amazon.com/AWSCloudFormation/latest/UserGuide/)  
  - [Azure ARM Docs](https://learn.microsoft.com/en-us/azure/azure-resource-manager/)  
  - [Ansible Docs](https://docs.ansible.com/)  

---

## ✅ **마무리**
이 문서는 **IaC의 필수 개념과 도구를 효과적으로 학습하기 위한 로드맵**입니다.  
각 개념을 **이론 → 도구 실습 → 프로젝트 적용 → 사례 분석**의 단계로 학습하며, **실무에서 IaC를 효과적으로 운영하는 방법**을 다룹니다. 🚀

