# 📂 Terraform on GCP 학습 개요

> **목표:**  
> - **Terraform을 활용하여 Google Cloud Platform(GCP) 인프라를 자동화하는 방법을 학습**한다.  
> - **GCP 리소스를 코드로 관리하고 배포하는 Infrastructure as Code(IaC) 개념을 익힌다.**  
> - **기본 개념과 명령어를 학습한 후, 고급 기능 및 실무 활용 전략을 학습한다.**  
> - **이론 → 도구 실습 → 프로젝트 적용 → 최적화의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **Terraform을 활용한 GCP 인프라 자동화를 기초(Basic)와 고급(Advanced)으로 나누어 학습합니다.**  

```
gcp/
├── introduction.md  # GCP에서 Terraform 활용 개요
├── setup.md         # GCP Terraform 환경 설정
├── examples.md      # GCP 인프라 코드 예제
└── README.md
```

---

## 📖 **1. 기본 개념 개요**
> **Terraform은 코드 기반으로 GCP 리소스를 관리하고 배포할 수 있도록 도와주는 IaC 도구입니다.**

- ✅ **Provider:** GCP API를 사용하여 리소스를 생성하고 관리  
- ✅ **State Management:** Terraform 상태 파일을 활용하여 인프라 변경을 추적  
- ✅ **Resource:** Compute Engine, Cloud Storage, VPC 등 다양한 GCP 리소스 관리  
- ✅ **Modules:** 반복적인 코드 재사용 및 유지보수 간소화  
- ✅ **Plan & Apply:** 변경 사항을 미리 확인하고 적용하는 안전한 배포 방식  

---

## 🏗 **2. 학습 내용**
### 📌 Terraform GCP Setup (환경 설정)
- **GCP Cloud SDK 및 Terraform 설치**
- **GCP 서비스 계정 설정 및 인증 (`gcloud auth application-default login`)**
- **Terraform 초기화 및 환경 구성 (`terraform init`)**

### 📌 GCP 리소스 관리 예제
- **GCP Compute Engine(VM) 생성 및 관리**
- **GCP Cloud Storage 버킷 생성 및 데이터 저장**
- **GCP VPC 및 방화벽 설정**
- **GCP Kubernetes Engine(GKE) 클러스터 배포**

### 📌 Terraform 고급 활용법
- **Terraform Modules을 활용한 코드 재사용**
- **Terraform Remote State를 활용한 협업 환경 구성**
- **Terraform과 GCP Cloud Build를 이용한 CI/CD 구축**

---

## 🚀 **3. 실전 예제**
> **Terraform을 활용하여 GCP Compute Engine을 생성하는 예제**

```hcl
provider "google" {
  project = "my-gcp-project"
  region  = "us-central1"
}

resource "google_compute_instance" "example" {
  name         = "terraform-instance"
  machine_type = "e2-medium"
  zone         = "us-central1-a"

  boot_disk {
    initialize_params {
      image = "debian-cloud/debian-10"
    }
  }

  network_interface {
    network = "default"
    access_config {}
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
1. **이론 학습** → Terraform의 GCP Provider 개념과 기본 설정 이해  
2. **도구 실습** → GCP 리소스 생성 및 관리 실습  
3. **프로젝트 적용** → 실제 프로젝트에서 Terraform을 활용한 GCP 인프라 자동화  
4. **최적화 연구** → 성능, 보안, 비용 최적화 전략 연구  

---

## 📚 **5. 추천 리소스**
- **Terraform GCP 공식 문서:**  
  - [Terraform GCP Provider Docs](https://registry.terraform.io/providers/hashicorp/google/latest/docs)  
  - [GCP Cloud SDK Docs](https://cloud.google.com/sdk/docs)  

- **Terraform GCP 예제 및 템플릿:**  
  - [Awesome Terraform GCP](https://github.com/terraform-google-modules)  
  - [Terraform GCP Examples](https://github.com/hashicorp/terraform-guides)  

---

## ✅ **마무리**
이 문서는 **Terraform을 활용한 GCP 인프라 자동화의 기본 개념부터 실무 활용까지 학습하기 위한 로드맵**입니다.  
각 개념을 **이론 → 도구 실습 → 프로젝트 적용 → 최적화**의 단계로 학습하며, **실무에서 Terraform을 효과적으로 활용하는 방법**을 다룹니다. 🚀