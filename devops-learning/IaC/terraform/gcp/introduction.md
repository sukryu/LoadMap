# GCP에서의 Terraform 활용 개요

> **목표:**  
> - Google Cloud Platform 인프라를 코드로 관리하는 방법을 이해한다.
> - Terraform을 사용하여 GCP 리소스를 자동으로 생성하고 관리하는 방법을 습득한다.
> - 실무에서 자주 사용되는 GCP 리소스 관리 패턴을 학습한다.
> - 비용 효율적이고 안전한 클라우드 인프라 관리 방법을 익힌다.

---

## 1. Terraform과 GCP 통합이란?

### 정의
Terraform은 GCP 인프라를 코드로 정의하고 관리할 수 있게 해주는 Infrastructure as Code(IaC) 도구입니다. GCP Console에서 수동으로 리소스를 생성하는 대신, Terraform을 사용하면 Compute Engine, Cloud Storage, Cloud SQL 등의 GCP 리소스를 코드로 작성하고 관리할 수 있습니다.

### 왜 필요한가?
GCP 환경에서 Terraform을 사용하면 다음과 같은 이점이 있습니다:

- **프로젝트 표준화:** 여러 GCP 프로젝트에서 동일한 인프라 구성을 쉽게 복제할 수 있습니다.
- **변경 관리:** 인프라 변경 사항을 코드로 추적하고 버전 관리할 수 있습니다.
- **자동화:** 반복적인 인프라 구성 작업을 자동화하여 운영 효율성을 높일 수 있습니다.
- **리소스 종속성 관리:** GCP 리소스 간의 복잡한 종속성을 자동으로 처리합니다.

---

## 2. 핵심 구성 요소

### 2.1 Provider 설정
GCP와 Terraform을 연결하기 위한 기본 설정입니다.

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
  project = "your-project-id"
  region  = "asia-northeast3"  # 서울 리전
}
```

### 2.2 프로젝트 구성
GCP의 모든 리소스는 프로젝트 내에서 관리됩니다.

```hcl
resource "google_project" "my_project" {
  name       = "My Project"
  project_id = "my-project-id"
  org_id     = "1234567890"
  
  labels = {
    environment = "production"
  }
}
```

### 2.3 상태 관리
Terraform 상태를 GCS(Google Cloud Storage)에 저장하여 팀 협업을 가능하게 합니다.

```hcl
terraform {
  backend "gcs" {
    bucket = "terraform-state-bucket"
    prefix = "terraform/state"
  }
}
```

---

## 3. GCP 특화 기능

### 3.1 Cloud Identity and Access Management (IAM)
GCP의 강력한 IAM 시스템을 Terraform으로 관리합니다.

```hcl
resource "google_project_iam_member" "project" {
  project = "your-project-id"
  role    = "roles/editor"
  member  = "user:jane@example.com"
}
```

### 3.2 VPC 네트워크 설정
GCP의 네트워크 리소스를 효율적으로 관리합니다.

```hcl
resource "google_compute_network" "vpc_network" {
  name                    = "my-custom-network"
  auto_create_subnetworks = false
}

resource "google_compute_subnetwork" "subnet" {
  name          = "my-custom-subnet"
  ip_cidr_range = "10.0.1.0/24"
  region        = "asia-northeast3"
  network       = google_compute_network.vpc_network.id
}
```

---

## 4. GCP 리소스 관리

### 4.1 Compute Engine 관리
가상 머신 인스턴스의 생성과 관리를 자동화합니다.

```hcl
resource "google_compute_instance" "default" {
  name         = "web-server"
  machine_type = "e2-medium"
  zone         = "asia-northeast3-a"

  boot_disk {
    initialize_params {
      image = "debian-cloud/debian-10"
    }
  }

  network_interface {
    network = "default"
    access_config {
      // Ephemeral public IP
    }
  }
}
```

### 4.2 Cloud Storage 관리
데이터 저장소를 효율적으로 구성합니다.

```hcl
resource "google_storage_bucket" "static_website" {
  name          = "my-static-website-bucket"
  location      = "ASIA"
  force_destroy = true

  website {
    main_page_suffix = "index.html"
    not_found_page   = "404.html"
  }

  uniform_bucket_level_access = true
}
```

---

## 5. 보안 및 모범 사례

### 5.1 보안 설정
GCP 환경에서의 보안 강화 방안입니다.

- 서비스 계정 키의 안전한 관리
- 최소 권한 원칙 적용
- VPC Service Controls 구성
- Secret Manager 활용

### 5.2 비용 최적화
비용 효율적인 리소스 관리 방안입니다.

- 적절한 인스턴스 타입 선택
- 자동 스케일링 구성
- 예약 인스턴스 활용
- 리소스 태깅을 통한 비용 추적

---

## 6. 모니터링 및 로깅

### 6.1 Cloud Monitoring 설정
```hcl
resource "google_monitoring_notification_channel" "basic" {
  display_name = "Team Email"
  type         = "email"
  labels = {
    email_address = "team@example.com"
  }
}
```

### 6.2 Cloud Logging 구성
```hcl
resource "google_logging_project_sink" "my_sink" {
  name        = "my-sink"
  destination = "storage.googleapis.com/${google_storage_bucket.log_bucket.name}"
  filter      = "severity >= WARNING"
}
```

---

## 7. 문제 해결 가이드

### 7.1 일반적인 문제
- 인증 및 권한 문제
- 리소스 할당량 초과
- 네트워크 구성 오류
- 상태 파일 관리 문제

### 7.2 해결 방안
- GCP Console에서 권한 확인
- 할당량 증가 요청
- VPC 설정 검증
- 백엔드 구성 확인

---

## 참고 자료

- [Google Cloud Provider 공식 문서](https://registry.terraform.io/providers/hashicorp/google/latest/docs)
- [GCP 아키텍처 센터](https://cloud.google.com/architecture)
- [Terraform GCP 예제](https://github.com/terraform-google-modules)

---

## 마무리

GCP에서 Terraform을 활용하면 클라우드 인프라를 효율적으로 관리할 수 있습니다. 이 문서에서 다룬 기본 개념과 예제를 바탕으로 실제 프로젝트에 적용하면서, 점진적으로 더 복잡한 인프라 관리 방법을 익힐 수 있습니다. GCP의 강력한 기능들을 Terraform으로 활용하면, 안정적이고 확장 가능한 클라우드 환경을 구축할 수 있습니다.