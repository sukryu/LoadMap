# AWS Terraform 환경 설정 가이드

> **목표:**  
> - AWS와 Terraform 연동을 위한 환경을 구성한다.
> - 필요한 도구들을 설치하고 기본 설정을 완료한다.
> - 보안을 고려한 AWS 계정 설정 방법을 이해한다.
> - 실제 프로젝트를 시작할 수 있는 기반을 마련한다.

---

## 1. 사전 준비사항

### AWS 계정 준비
AWS 계정이 없는 경우, AWS 공식 웹사이트에서 새로운 계정을 생성해야 합니다. AWS 계정을 생성할 때는 다음 사항에 주의해야 합니다.

1. 루트 계정의 MFA(Multi-Factor Authentication) 설정
2. 결제 알림 설정
3. 예산 설정으로 과도한 비용 발생 방지

### 필수 소프트웨어 설치
환경 구성을 위해 다음 소프트웨어들이 필요합니다.

1. AWS CLI 설치
2. Terraform 설치
3. 텍스트 에디터 (VS Code 권장)

---

## 2. AWS CLI 설치 및 구성

### AWS CLI 설치
운영체제별 설치 방법이 다르므로, 해당하는 방법을 선택하여 진행합니다.

Windows의 경우:
```powershell
# AWS CLI MSI 인스톨러를 다운로드하여 실행
# https://awscli.amazonaws.com/AWSCLIV2.msi
```

macOS의 경우:
```bash
brew install awscli
```

Linux의 경우:
```bash
curl "https://awscli.amazonaws.com/awscli-exe-linux-x86_64.zip" -o "awscliv2.zip"
unzip awscliv2.zip
sudo ./aws/install
```

### AWS CLI 구성
AWS CLI를 설치한 후, 다음 명령어로 초기 설정을 진행합니다.

```bash
aws configure

# 입력해야 할 정보
AWS Access Key ID: [your_access_key]
AWS Secret Access Key: [your_secret_key]
Default region name: ap-northeast-2
Default output format: json
```

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

## 4. AWS IAM 설정

### IAM 사용자 생성
Terraform 사용을 위한 전용 IAM 사용자를 생성합니다.

1. AWS 관리 콘솔에서 IAM 서비스로 이동
2. '사용자 추가' 클릭
3. 프로그래밍 방식 액세스 선택
4. 적절한 권한 정책 연결

### 권한 정책 설정
Terraform이 필요로 하는 최소한의 권한을 설정합니다.

```json
{
    "Version": "2012-10-17",
    "Statement": [
        {
            "Effect": "Allow",
            "Action": [
                "ec2:*",
                "s3:*",
                "vpc:*",
                "iam:*"
                // 필요한 다른 서비스 권한 추가
            ],
            "Resource": "*"
        }
    ]
}
```

---

## 5. 프로젝트 구성

### 기본 디렉토리 구조 생성
```
terraform-aws-project/
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
    aws = {
      source  = "hashicorp/aws"
      version = "~> 4.0"
    }
  }
}

provider "aws" {
  region = "ap-northeast-2"  # 서울 리전
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
resource "aws_s3_bucket" "test" {
  bucket = "my-terraform-test-bucket-${random_string.suffix.result}"
}

resource "random_string" "suffix" {
  length  = 8
  special = false
}
```

---

## 7. 보안 고려사항

### 중요 정보 관리
1. AWS 액세스 키와 시크릿 키는 절대 소스 코드에 포함하지 않습니다.
2. 환경 변수나 AWS 자격 증명 파일을 사용합니다.
3. 민감한 정보는 AWS Secrets Manager나 Parameter Store를 활용합니다.

### 상태 파일 관리
1. 원격 백엔드(예: S3)를 사용하여 상태 파일 관리
2. 상태 파일 암호화 설정
3. 상태 파일에 대한 접근 제어 설정

---

## 8. 문제 해결

### 일반적인 문제와 해결 방법

1. **권한 관련 오류**
   - IAM 정책 확인
   - AWS 자격 증명 설정 확인

2. **초기화 오류**
   - 인터넷 연결 확인
   - 프로바이더 버전 호환성 확인

3. **상태 파일 오류**
   - 로컬 상태 파일 백업 확인
   - 원격 백엔드 접근 권한 확인

---

## 참고 자료

- [Terraform AWS Provider 공식 문서](https://registry.terraform.io/providers/hashicorp/aws/latest)
- [AWS CLI 설치 가이드](https://docs.aws.amazon.com/cli/latest/userguide/cli-chap-install.html)
- [Terraform 설치 가이드](https://learn.hashicorp.com/tutorials/terraform/install-cli)

---

## 마무리

이 환경 설정 가이드를 따라 설정을 완료하면, AWS에서 Terraform을 사용하여 인프라를 관리할 수 있는 기본 환경이 구성됩니다. 보안 설정과 모범 사례를 준수하면서, 필요에 따라 추가적인 도구와 설정을 구성할 수 있습니다. 문제가 발생할 경우, 문제 해결 섹션을 참조하거나 공식 문서를 확인하시기 바랍니다.