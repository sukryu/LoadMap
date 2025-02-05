# AWS에서의 Terraform 활용 개요

> **목표:**  
> - AWS 인프라를 코드로 관리하는 방법을 이해한다.
> - Terraform을 사용하여 AWS 리소스를 자동으로 생성하고 관리하는 방법을 습득한다.
> - 실무에서 자주 사용되는 AWS 리소스 관리 패턴을 학습한다.
> - 비용 효율적이고 안전한 인프라 관리 방법을 익힌다.

---

## 1. Terraform과 AWS 통합이란?

### 정의
Terraform은 AWS 인프라를 코드로 정의하고 관리할 수 있게 해주는 도구입니다. 마치 프로그래밍 언어로 소프트웨어를 만드는 것처럼, Terraform을 사용하면 AWS의 서버, 네트워크, 데이터베이스 등을 코드로 작성하고 관리할 수 있습니다.

### 왜 필요한가?
- **일관성 보장:** 수동으로 AWS 콘솔에서 작업하는 대신, 코드로 관리하여 실수를 방지합니다.
- **재사용성:** 한번 작성한 코드를 여러 환경(개발, 테스트, 운영)에서 재사용할 수 있습니다.
- **버전 관리:** Git과 같은 버전 관리 시스템으로 인프라 변경 이력을 추적할 수 있습니다.
- **자동화:** 인프라 구축과 변경을 자동화하여 운영 효율성을 높입니다.

---

## 2. 핵심 구성 요소

### 2.1 Provider 설정
AWS와 Terraform을 연결하기 위한 기본 설정입니다.

```hcl
provider "aws" {
  region = "ap-northeast-2"  # 서울 리전
  profile = "default"        # AWS 계정 프로필
}
```

### 2.2 리소스 정의
AWS에서 생성할 리소스를 코드로 정의합니다.

```hcl
# EC2 인스턴스 생성 예시
resource "aws_instance" "web_server" {
  ami           = "ami-12345678"  # Amazon Linux 2 AMI ID
  instance_type = "t2.micro"      # 인스턴스 타입
  
  tags = {
    Name = "웹 서버"
    Environment = "개발"
  }
}
```

### 2.3 변수와 출력
재사용성과 유연성을 높이기 위한 변수 설정과 결과값 출력 방법입니다.

```hcl
# 변수 정의
variable "environment" {
  description = "배포 환경 (개발/스테이징/운영)"
  type        = string
  default     = "개발"
}

# 출력 정의
output "server_ip" {
  description = "생성된 서버의 IP 주소"
  value       = aws_instance.web_server.public_ip
}
```

---

## 3. 실제 활용 예시

### 3.1 기본적인 웹 서버 환경 구성
```hcl
# VPC 생성
resource "aws_vpc" "main" {
  cidr_block = "10.0.0.0/16"
  
  tags = {
    Name = "메인 VPC"
  }
}

# 서브넷 생성
resource "aws_subnet" "public" {
  vpc_id     = aws_vpc.main.id
  cidr_block = "10.0.1.0/24"
  
  tags = {
    Name = "퍼블릭 서브넷"
  }
}

# EC2 인스턴스 생성
resource "aws_instance" "web" {
  ami           = "ami-12345678"
  instance_type = "t2.micro"
  subnet_id     = aws_subnet.public.id
  
  tags = {
    Name = "웹 서버"
  }
}
```

### 3.2 state 관리
Terraform은 생성한 인프라의 상태를 state 파일에 저장합니다.

```hcl
# S3에 state 파일 저장 설정
terraform {
  backend "s3" {
    bucket = "my-terraform-state"
    key    = "prod/terraform.tfstate"
    region = "ap-northeast-2"
  }
}
```

---

## 4. 작업 순서

### 4.1 기본 워크플로우
1. **초기화:** `terraform init` 명령으로 필요한 프로바이더와 모듈을 다운로드
2. **계획:** `terraform plan` 명령으로 변경 사항을 미리 확인
3. **적용:** `terraform apply` 명령으로 실제 인프라에 변경 사항을 적용
4. **삭제:** `terraform destroy` 명령으로 생성된 리소스를 안전하게 제거

### 4.2 실행 예시
```bash
# 프로젝트 초기화
terraform init

# 변경 사항 미리보기
terraform plan

# 변경 사항 적용
terraform apply

# 리소스 제거
terraform destroy
```

---

## 5. 장점과 주의사항

### 장점
- 인프라 구성을 코드로 문서화할 수 있습니다.
- 변경 사항을 미리 확인하고 검증할 수 있습니다.
- 일관된 방식으로 인프라를 관리할 수 있습니다.
- 팀 협업이 용이해집니다.

### 주의사항
- state 파일의 안전한 관리가 필요합니다.
- AWS 리소스 비용에 주의해야 합니다.
- 실수로 중요 리소스가 삭제되지 않도록 주의해야 합니다.
- 보안 관련 설정(예: IAM)을 신중하게 해야 합니다.

---

## 6. 시작하기

### 6.1 준비사항
1. AWS 계정 생성 및 액세스 키 설정
2. Terraform 설치
3. AWS CLI 설치 및 구성
4. 기본 프로젝트 디렉토리 생성

### 6.2 기본 설정 파일 구조
```
project/
├── main.tf      # 주요 리소스 정의
├── variables.tf # 변수 정의
├── outputs.tf   # 출력 정의
└── terraform.tfvars # 변수값 설정
```

---

## 참고 자료

- [Terraform AWS Provider 공식 문서](https://registry.terraform.io/providers/hashicorp/aws/latest/docs)
- [AWS Terraform 시작하기 가이드](https://learn.hashicorp.com/collections/terraform/aws-get-started)
- [Terraform 모범 사례](https://www.terraform-best-practices.com/)

---

## 마무리

Terraform을 사용한 AWS 인프라 관리는 현대적인 인프라 운영에 필수적인 기술입니다. 이 문서에서 설명한 기본 개념과 예제를 바탕으로 실제 프로젝트에 적용해보면서, 점진적으로 더 복잡한 인프라 관리 방법을 익힐 수 있습니다. 특히 초보자는 기본적인 리소스 생성부터 시작하여, 점차 고급 기능과 모범 사례를 학습해 나가는 것이 좋습니다.