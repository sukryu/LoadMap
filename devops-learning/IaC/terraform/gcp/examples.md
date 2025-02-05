# GCP Terraform 인프라 코드 예제

> **목표:**  
> - 실무에서 자주 사용되는 GCP 인프라 구성 예제를 제공한다.
> - 각 예제의 목적과 동작 방식을 상세히 설명한다.
> - 실제 프로젝트에 적용할 수 있는 모범 사례를 소개한다.
> - 초보자도 이해하고 활용할 수 있는 기본 예제부터 시작한다.

---

## 1. 기본 네트워크 인프라 구성

### VPC 네트워크 및 서브넷 생성
기업 환경에서 필요한 기본적인 네트워크 인프라를 구성하는 예제입니다.

```hcl
# VPC 네트워크 생성
resource "google_compute_network" "vpc_network" {
  name                    = "main-vpc"
  auto_create_subnetworks = false
  routing_mode           = "GLOBAL"

  delete_default_routes_on_create = false

  depends_on = [google_project_service.compute]
}

# 서브넷 생성
resource "google_compute_subnetwork" "subnet" {
  name          = "main-subnet"
  ip_cidr_range = "10.0.0.0/24"
  region        = "asia-northeast3"
  network       = google_compute_network.vpc_network.id

  private_ip_google_access = true

  secondary_ip_range {
    range_name    = "pod-range"
    ip_cidr_range = "10.1.0.0/16"
  }

  secondary_ip_range {
    range_name    = "service-range"
    ip_cidr_range = "10.2.0.0/16"
  }
}

# 방화벽 규칙 생성
resource "google_compute_firewall" "allow_internal" {
  name    = "allow-internal"
  network = google_compute_network.vpc_network.name

  allow {
    protocol = "tcp"
    ports    = ["0-65535"]
  }
  allow {
    protocol = "udp"
    ports    = ["0-65535"]
  }
  allow {
    protocol = "icmp"
  }

  source_ranges = ["10.0.0.0/8"]
}
```

---

## 2. Compute Engine 인스턴스 배포

### 기본 VM 인스턴스 생성

```hcl
# 서비스 계정 생성
resource "google_service_account" "instance_sa" {
  account_id   = "instance-sa"
  display_name = "Service Account for VM instances"
}

# VM 인스턴스 생성
resource "google_compute_instance" "web_server" {
  name         = "web-server"
  machine_type = "e2-medium"
  zone         = "asia-northeast3-a"

  boot_disk {
    initialize_params {
      image = "debian-cloud/debian-11"
      size  = 50
      type  = "pd-ssd"
    }
  }

  network_interface {
    network    = google_compute_network.vpc_network.name
    subnetwork = google_compute_subnetwork.subnet.name

    access_config {
      // 외부 IP 자동 할당
    }
  }

  service_account {
    email  = google_service_account.instance_sa.email
    scopes = ["cloud-platform"]
  }

  metadata_startup_script = <<-EOF
              #!/bin/bash
              apt-get update
              apt-get install -y nginx
              systemctl enable nginx
              systemctl start nginx
              EOF

  tags = ["web-server", "http-server"]

  labels = {
    environment = "production"
    application = "web"
  }
}
```

---

## 3. Cloud Storage 구성

### 보안이 강화된 스토리지 버킷 생성

```hcl
# Cloud Storage 버킷 생성
resource "google_storage_bucket" "secure_bucket" {
  name          = "secure-storage-bucket-${random_id.suffix.hex}"
  location      = "ASIA-NORTHEAST3"
  force_destroy = true

  uniform_bucket_level_access = true
  
  versioning {
    enabled = true
  }

  lifecycle_rule {
    condition {
      age = 90
    }
    action {
      type = "Delete"
    }
  }

  encryption {
    default_kms_key_name = google_kms_crypto_key.crypto_key.id
  }
}

# KMS 키 링 및 키 생성
resource "google_kms_key_ring" "key_ring" {
  name     = "storage-keyring"
  location = "asia-northeast3"
}

resource "google_kms_crypto_key" "crypto_key" {
  name     = "storage-key"
  key_ring = google_kms_key_ring.key_ring.id

  rotation_period = "7776000s" # 90일
}
```

---

## 4. Cloud SQL 데이터베이스 구성

### 고가용성 PostgreSQL 인스턴스 생성

```hcl
# Cloud SQL 인스턴스 생성
resource "google_sql_database_instance" "postgres" {
  name             = "postgres-instance"
  database_version = "POSTGRES_14"
  region           = "asia-northeast3"

  settings {
    tier = "db-f1-micro"
    
    availability_type = "REGIONAL"  # 고가용성 설정
    
    backup_configuration {
      enabled                        = true
      start_time                     = "03:00"
      point_in_time_recovery_enabled = true
    }

    ip_configuration {
      ipv4_enabled    = false
      private_network = google_compute_network.vpc_network.id
    }

    insights_config {
      query_insights_enabled  = true
      query_string_length    = 1024
      record_application_tags = true
      record_client_address  = true
    }
  }

  deletion_protection = true
}

# 데이터베이스 생성
resource "google_sql_database" "database" {
  name     = "application-db"
  instance = google_sql_database_instance.postgres.name
}

# 데이터베이스 사용자 생성
resource "google_sql_user" "users" {
  name     = "application-user"
  instance = google_sql_database_instance.postgres.name
  password = "your-password-here"  # 실제 환경에서는 변수나 Secret Manager 사용
}
```

---

## 5. Kubernetes Engine (GKE) 클러스터 구성

### 프로덕션 레벨 GKE 클러스터 생성

```hcl
# GKE 클러스터 생성
resource "google_container_cluster" "primary" {
  name     = "primary-cluster"
  location = "asia-northeast3"

  # 기본 노드풀 제거
  remove_default_node_pool = true
  initial_node_count       = 1

  network    = google_compute_network.vpc_network.name
  subnetwork = google_compute_subnetwork.subnet.name

  ip_allocation_policy {
    cluster_secondary_range_name  = "pod-range"
    services_secondary_range_name = "service-range"
  }

  private_cluster_config {
    enable_private_nodes    = true
    enable_private_endpoint = false
    master_ipv4_cidr_block = "172.16.0.0/28"
  }

  master_authorized_networks_config {
    cidr_blocks {
      cidr_block   = "10.0.0.0/24"
      display_name = "VPC"
    }
  }
}

# 노드풀 생성
resource "google_container_node_pool" "primary_nodes" {
  name       = "primary-node-pool"
  location   = "asia-northeast3"
  cluster    = google_container_cluster.primary.name
  node_count = 3

  node_config {
    preemptible  = false
    machine_type = "e2-standard-2"

    service_account = google_service_account.gke_sa.email
    oauth_scopes    = [
      "https://www.googleapis.com/auth/cloud-platform"
    ]

    labels = {
      environment = "production"
    }

    metadata = {
      disable-legacy-endpoints = "true"
    }
  }

  management {
    auto_repair  = true
    auto_upgrade = true
  }

  autoscaling {
    min_node_count = 3
    max_node_count = 10
  }
}
```

---

## 6. Cloud Load Balancing 구성

### HTTPS 로드 밸런서 설정

```hcl
# 인스턴스 그룹 생성
resource "google_compute_instance_group" "webservers" {
  name        = "webserver-group"
  description = "Webserver instance group"
  zone        = "asia-northeast3-a"

  named_port {
    name = "http"
    port = 80
  }
}

# 헬스 체크 구성
resource "google_compute_health_check" "default" {
  name               = "http-health-check"
  check_interval_sec = 5
  timeout_sec        = 5

  http_health_check {
    port = 80
  }
}

# 백엔드 서비스 구성
resource "google_compute_backend_service" "default" {
  name          = "backend-service"
  port_name     = "http"
  protocol      = "HTTP"
  timeout_sec   = 10
  health_checks = [google_compute_health_check.default.id]

  backend {
    group = google_compute_instance_group.webservers.id
  }
}

# URL 맵 생성
resource "google_compute_url_map" "default" {
  name            = "url-map"
  default_service = google_compute_backend_service.default.id
}

# HTTPS 프록시 구성
resource "google_compute_target_https_proxy" "default" {
  name             = "https-proxy"
  url_map          = google_compute_url_map.default.id
  ssl_certificates = [google_compute_managed_ssl_certificate.default.id]
}

# SSL 인증서 생성
resource "google_compute_managed_ssl_certificate" "default" {
  name = "ssl-cert"

  managed {
    domains = ["example.com"]
  }
}

# 글로벌 포워딩 규칙 생성
resource "google_compute_global_forwarding_rule" "default" {
  name       = "https-forwarding-rule"
  target     = google_compute_target_https_proxy.default.id
  port_range = "443"
}
```

---

## 7. IAM 및 보안 구성

### 세분화된 IAM 권한 설정

```hcl
# 커스텀 역할 생성
resource "google_project_iam_custom_role" "app_role" {
  role_id     = "appCustomRole"
  title       = "Application Custom Role"
  description = "Custom role for application-specific permissions"
  permissions = [
    "storage.buckets.get",
    "storage.objects.list",
    "storage.objects.get",
    "storage.objects.create"
  ]
}

# 서비스 계정에 역할 할당
resource "google_project_iam_binding" "app_iam" {
  project = var.project_id
  role    = google_project_iam_custom_role.app_role.id

  members = [
    "serviceAccount:${google_service_account.app_sa.email}",
  ]
}

# Secret Manager 구성
resource "google_secret_manager_secret" "app_secret" {
  secret_id = "app-secret"
  
  replication {
    automatic = true
  }
}

resource "google_secret_manager_secret_version" "app_secret_version" {
  secret      = google_secret_manager_secret.app_secret.id
  secret_data = "your-secret-data"
}
```

---

## 참고 사항

1. 모든 예제는 실제 환경에 맞게 수정이 필요합니다.
2. 보안 관련 설정(비밀번호, 키 등)은 반드시 Secret Manager나 환경 변수를 통해 관리해야 합니다.
3. 네트워크 보안 규칙은 최소 권한 원칙에 따라 구성해야 합니다.
4. 태그와 레이블을 적절히 사용하여 리소스 관리와 비용 추적을 용이하게 해야 합니다.

---

## 마무리

이 문서에서 제공하는 예제들은 GCP 인프라 구성을 위한 기본적인 템플릿입니다. 실제 프로젝트에서는 보안, 확장성, 가용성 등을 고려한 추가적인 설정이 필요할 수 있습니다. 각 예제를 기반으로 필요에 맞게 수정하고 확장하여 사용하시기 바랍니다.