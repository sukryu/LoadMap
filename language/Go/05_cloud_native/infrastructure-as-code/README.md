# Infrastructure as Code (IaC) for Cloud-Native Systems ☁️🔧

이 디렉토리는 Go 백엔드 및 클라우드 애플리케이션을 위한 **Infrastructure as Code (IaC)** 접근법을 다룹니다.  
Terraform, Pulumi 등의 도구를 사용하여 클라우드 리소스를 선언적으로 관리하고, 자동화된 인프라 프로비저닝 및 구성 관리를 실무에 적용하는 방법을 학습할 수 있습니다.

---

## What You'll Learn 🎯

- **IaC 기본 개념**:  
  - 인프라를 코드로 관리하는 이유와 주요 장점 (일관성, 재현성, 자동화)
  - 선언적 vs. 명령형 접근 방식

- **Terraform과 Pulumi 사용법**:  
  - Terraform을 사용하여 AWS, GCP, Azure 등의 클라우드 리소스를 선언적으로 프로비저닝하는 방법  
  - Pulumi를 통해 Go 코드로 인프라를 구성하는 방법 및 차별점 이해

- **배포 및 관리 자동화**:  
  - IaC를 통한 지속적 인프라 업데이트, 롤백, 버전 관리 및 테스트 전략  
  - CI/CD 파이프라인에 IaC를 통합하는 모범 사례

- **실무 적용 사례**:  
  - 클러스터, VPC, 서브넷, 보안 그룹 등 주요 인프라 오브젝트의 자동 생성 및 관리
  - 인프라 변경 시 안전한 배포와 모니터링 전략

---

## Directory Structure 📁

```plaintext
05-cloud-native/
└── infrastructure-as-code/
    ├── main.tf          # Terraform 예제 파일 (기본 인프라 구성)
    ├── variables.tf     # 변수 정의 및 환경 설정
    ├── outputs.tf       # 출력값 정의 (생성된 리소스 정보)
    ├── pulumi/          # (선택 사항) Pulumi 기반 Go 코드 예제
    └── README.md        # 이 문서
```

- **main.tf, variables.tf, outputs.tf**:  
  - Terraform 파일들을 통해 클라우드 리소스(VPC, 서브넷, 인스턴스 등)의 기본 인프라를 선언적으로 관리하는 예제를 제공합니다.
- **pulumi/**:  
  - Pulumi를 활용한 Go 코드 기반 인프라 관리 예제 및 템플릿을 포함합니다.

---

## Getting Started 🚀

### 1. Prerequisites
- **Terraform**: [Terraform 설치 가이드](https://www.terraform.io/downloads)
- **Pulumi (선택 사항)**: [Pulumi 설치 가이드](https://www.pulumi.com/docs/get-started/install/)
- **클라우드 계정**: AWS, GCP, 또는 Azure 계정 (사용할 플랫폼에 맞게)
- Go 최신 버전 (Pulumi Go 예제 실행 시 필요)

### 2. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/05-cloud-native/infrastructure-as-code
```

### 3. Terraform 예제 실행
- 초기화, 계획 수립, 그리고 적용 단계:
  ```bash
  terraform init
  terraform plan
  terraform apply
  ```
- 실행 후, 생성된 인프라 리소스(예: VPC, 서브넷, 보안 그룹 등)를 확인하세요.

### 4. (선택 사항) Pulumi 예제 실행
- Pulumi Go 프로젝트 디렉토리로 이동하여:
  ```bash
  cd pulumi
  pulumi up
  ```
- Pulumi가 관리하는 인프라 리소스를 배포하고, 변경 사항을 확인하세요.

---

## Example Snippet 📄

### Terraform 예제: 기본 VPC 생성
```hcl
// main.tf
provider "aws" {
  region = var.aws_region
}

resource "aws_vpc" "main_vpc" {
  cidr_block = "10.0.0.0/16"
  tags = {
    Name = "main-vpc"
  }
}

// variables.tf
variable "aws_region" {
  description = "AWS region to deploy in"
  type        = string
  default     = "us-west-2"
}

// outputs.tf
output "vpc_id" {
  description = "The ID of the created VPC"
  value       = aws_vpc.main_vpc.id
}
```

이 예제는 AWS에서 기본 VPC를 생성하는 Terraform 구성을 보여줍니다.

---

## Best Practices & Tips 💡

- **버전 관리**:  
  - IaC 코드를 Git과 같은 버전 관리 시스템으로 관리하여, 인프라 변경 이력을 추적하세요.
  
- **모듈화**:  
  - 반복되는 인프라 구성 요소는 Terraform 모듈이나 Pulumi 컴포넌트로 분리해 재사용성을 높이세요.
  
- **환경 분리**:  
  - 개발, 스테이징, 프로덕션 환경별로 다른 설정을 적용할 수 있도록 변수 파일과 작업 공간을 관리하세요.
  
- **CI/CD 통합**:  
  - IaC 코드를 CI/CD 파이프라인에 포함시켜, 인프라 변경을 자동화하고 테스트하여 배포 안정성을 높이세요.
  
- **보안 고려**:  
  - 클라우드 자격 증명과 민감 정보는 환경 변수나 비밀 관리 도구(Vault, AWS Secrets Manager 등)로 안전하게 관리하세요.
  
- **리소스 최적화**:  
  - 생성되는 인프라 자원의 비용 및 성능을 고려해, 불필요한 리소스는 제거하고 효율적으로 구성하세요.

---

## Next Steps

- **고급 IaC 전략**:  
  - 인프라 자동화 도구의 고급 기능, 예를 들어 Terraform Enterprise, Pulumi Automation API 등을 추가로 학습해 보세요.
- **멀티 클라우드 배포**:  
  - 여러 클라우드 플랫폼에 걸친 인프라 구성을 실습하여, 멀티 클라우드 전략을 수립해 보세요.
- **테스트 및 롤백 전략**:  
  - 인프라 변경에 따른 테스트 자동화와, 롤백 전략을 마련해, 안전한 운영 환경을 구축하세요.

---

## References 📚

- [Terraform Documentation](https://www.terraform.io/docs)
- [Pulumi Documentation](https://www.pulumi.com/docs/)
- [Infrastructure as Code Best Practices](https://www.hashicorp.com/resources/infrastructure-as-code)
- [AWS, GCP, Azure IaC Guides](https://aws.amazon.com/quickstart/architecture/infrastructure-as-code/)

---

Infrastructure as Code를 활용하면, 클라우드 리소스의 프로비저닝과 관리를 코드로 선언적으로 처리할 수 있어, 인프라의 일관성과 재현성을 크게 향상시킬 수 있습니다.  
이 자료를 통해 효율적이고 안전한 인프라 자동화 환경을 구축해 보세요! Happy IaC Coding! ☁️🔧