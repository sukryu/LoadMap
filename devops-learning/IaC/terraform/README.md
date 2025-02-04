# 📂 Terraform 학습 개요

> **목표:**  
> - **Terraform의 개념과 실무 적용 방법을 학습**한다.  
> - **Infrastructure as Code(IaC)를 활용하여 클라우드 리소스를 자동으로 프로비저닝하는 방법을 익힌다.**  
> - **기본 개념과 명령어를 학습한 후, 고급 기능 및 실무 활용 전략을 학습한다.**  
> - **이론 → 도구 실습 → 프로젝트 적용 → 최적화의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **Terraform 학습을 AWS, Azure, GCP별로 나누어 진행합니다.**  

```
terraform/
├── aws
│   ├── introduction.md  # AWS에서 Terraform 활용 개요
│   ├── setup.md         # AWS Terraform 환경 설정
│   ├── examples.md      # AWS 인프라 코드 예제
│   └── README.md
│
├── azure
│   ├── introduction.md  # Azure에서 Terraform 활용 개요
│   ├── setup.md         # Azure Terraform 환경 설정
│   ├── examples.md      # Azure 인프라 코드 예제
│   └── README.md
│
├── gcp
│   ├── introduction.md  # GCP에서 Terraform 활용 개요
│   ├── setup.md         # GCP Terraform 환경 설정
│   ├── examples.md      # GCP 인프라 코드 예제
│   └── README.md
└── README.md
```

---

## 📖 **1. 기본 개념 개요**
> **Terraform은 코드로 인프라를 정의하고 프로비저닝할 수 있는 오픈소스 IaC(Infrastructure as Code) 도구입니다.**

- ✅ **Declarative Configuration:** 원하는 상태를 코드로 정의하여 자동으로 적용  
- ✅ **Providers:** AWS, Azure, GCP 등 다양한 클라우드 서비스 제공자 지원  
- ✅ **State Management:** Terraform 상태 파일을 사용하여 인프라 변경을 추적  
- ✅ **Modules:** 재사용 가능한 코드 블록을 활용하여 인프라 관리 효율성 증가  
- ✅ **Plan & Apply:** 변경 사항을 미리 확인하고 적용하는 단계적 배포 방식  

---

## 🏗 **2. 학습 내용**
### 📌 Terraform Basics (기본 개념 및 활용)
- **Terraform 설치 및 환경 설정**
- **기본 Terraform 명령어 (`terraform init`, `terraform plan`, `terraform apply`)**
- **Terraform Provider 및 리소스 정의 방법**

### 📌 Advanced Terraform (고급 개념 및 실무 적용)
- **Terraform Modules을 활용한 코드 재사용**
- **Terraform State 및 원격 상태 저장소 관리**
- **Terraform Workspaces 및 다중 환경 관리**
- **Terraform과 CI/CD 파이프라인 연동**

---

## 🚀 **3. 실전 예제**
> **Terraform을 활용하여 AWS EC2 인스턴스를 생성하는 예제**

```hcl
provider "aws" {
  region = "us-east-1"
}

resource "aws_instance" "example" {
  ami           = "ami-12345678"
  instance_type = "t2.micro"
  tags = {
    Name = "Terraform-Instance"
  }
}
```

```sh
# Terraform 실행 절차
terraform init      # Terraform 초기화
target=terraform plan   # 변경 사항 미리보기
target=terraform apply  # 인프라 적용
```

---

## 🎯 **4. 학습 방법**
1. **이론 학습** → Terraform 개념과 구조 이해  
2. **도구 실습** → 기본 및 고급 Terraform 활용 실습  
3. **프로젝트 적용** → 실제 프로젝트에서 Terraform 활용  
4. **최적화 연구** → 성능, 보안, 자동화 최적화  

---

## 📚 **5. 추천 리소스**
- **Terraform 공식 문서:**  
  - [Terraform Docs](https://developer.hashicorp.com/terraform/docs)  

- **Terraform 예제 및 템플릿:**  
  - [Awesome Terraform](https://github.com/shuaibiyy/awesome-terraform)  
  - [Terraform Examples](https://github.com/hashicorp/terraform-guides)  

---

## ✅ **마무리**
이 문서는 **Terraform의 기본 개념부터 실무 활용까지 학습하기 위한 로드맵**입니다.  
각 개념을 **이론 → 도구 실습 → 프로젝트 적용 → 최적화**의 단계로 학습하며, **실무에서 Terraform을 효과적으로 활용하는 방법**을 다룹니다. 🚀