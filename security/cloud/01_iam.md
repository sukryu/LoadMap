# 클라우드 IAM (Identity and Access Management)

클라우드 환경에서 **IAM(Identity and Access Management)**은 보안의 핵심 요소입니다. 이 문서에서는 주요 클라우드 서비스 제공업체(AWS, GCP, Azure)의 IAM 시스템에 대한 개념, 모범 사례 및 구체적인 구현 방법을 다룹니다.

> 최근 업데이트: 2025-02-22

## 1. 들어가기 (Introduction)

### 1.1 문서의 목적

클라우드 환경에서의 IAM은 "누가 어떤 리소스에 어떤 조건에서 접근할 수 있는지"를 제어하는 핵심 보안 메커니즘입니다. 이 문서는 다음을 목표로 합니다:

- 클라우드 IAM의 **기본 개념과 원리** 이해
- 주요 클라우드 제공업체(AWS, GCP, Azure)의 **IAM 시스템 비교**
- **최소 권한 원칙**을 적용한 안전한 설계 방법론
- 실제 프로젝트에 적용 가능한 **구체적인 구현 예시**
- 자격 증명 관리, 임시 자격 증명, MFA 등 **고급 보안 기능**

### 1.2 왜 IAM이 중요한가?

클라우드 환경에서 IAM의 중요성은 다음과 같은 이유로 더욱 부각됩니다:

- **분산된 리소스**: 다양한 서비스와 리전에 걸쳐 리소스가 분산됨
- **동적 환경**: 자원이 동적으로 생성, 수정, 삭제됨
- **다양한 접근 주체**: 사용자, 서비스, 애플리케이션 등 다양한 주체가 접근
- **복잡한 권한 관계**: 리소스 간 상호 의존성과 접근 패턴이 복잡함
- **잠재적 비용 영향**: 잘못된 접근 제어는 무단 사용으로 인한 비용 증가로 이어질 수 있음

잘못 구성된 IAM 설정은 데이터 유출, 권한 상승, 리소스 무단 사용 등 심각한 보안 위협의 원인이 됩니다.

### 1.3 주요 클라우드 IAM 비교

**AWS IAM**
- 사용자, 그룹, 역할, 정책 기반 시스템
- 세분화된 리소스 수준 권한 제어
- 정책 조건을 통한 컨텍스트 기반 접근 제어
- AWS 서비스 간 높은 통합성

**Google Cloud IAM**
- 주 구성원(Principal), 역할(Role), 정책(Policy) 기반 시스템
- 사전 정의된 역할과 커스텀 역할 지원
- 계층적 리소스 구조(조직 → 폴더 → 프로젝트 → 리소스)
- 서비스 계정에 대한 강력한 지원

**Azure RBAC (Role-Based Access Control)**
- Azure Active Directory와 통합
- 역할 할당, 역할 정의, 범위 기반 시스템
- 관리 그룹 → 구독 → 리소스 그룹 → 리소스의 계층 구조
- Microsoft 생태계와의 강력한 통합

> 💡 **알아두세요**  
> 클라우드 IAM 설정은 보안의 기초이자 가장 중요한 방어선입니다. 잘못된 구성은 다른 모든 보안 조치를 무력화할 수 있습니다.

---

## 2. IAM 기본 개념 (Core Concepts)

### 2.1 IAM 공통 요소

클라우드 제공업체마다 IAM 구현 방식이 다르지만, 공통적인 핵심 요소들이 있습니다:

#### 2.1.1 주요 구성 요소

**1. 식별(Identity) 관련 요소**
- **사용자(User)**: 개별 인간 사용자 또는 서비스 계정
- **그룹(Group)**: 사용자들의 집합 (관리 단순화)
- **역할(Role)**: 특정 작업 수행에 필요한 권한 집합

**2. 접근 제어(Access Control) 관련 요소**
- **권한(Permission)**: 특정 리소스에 대한 특정 작업 수행 권리
- **정책(Policy)**: 권한들의 집합 (허용/거부 규칙)
- **리소스(Resource)**: 접근을 제어할 대상 (VM, 데이터베이스, 스토리지 등)

**3. 관리 및 감사 요소**
- **신뢰 관계(Trust Relationship)**: 어떤 주체가 특정 역할을 맡을 수 있는지 정의
- **자격 증명(Credential)**: 신원을 증명하는 데 사용되는 정보 (비밀번호, 키 등)
- **감사 로그(Audit Log)**: 누가, 언제, 무엇에 접근했는지 기록

#### 2.1.2 작동 원리

IAM은 일반적으로 다음과 같은 단계로 작동합니다:

1. **인증(Authentication)**: 사용자가 자신의 신원을 증명
2. **인가(Authorization)**: 권한 부여 정책에 따라 요청 평가
3. **접근 제어(Access Control)**: 권한에 따라 리소스 접근 허용/거부
4. **감사(Auditing)**: 활동 기록 및 모니터링

### 2.2 최소 권한 원칙 (Principle of Least Privilege)

최소 권한 원칙은 IAM 설계의 기본 원칙으로, 다음을 의미합니다:

- 사용자/서비스에 **필요한 최소한의 권한만** 부여
- 업무 수행에 **필요한 리소스에만** 접근 허용
- 필요한 **기간 동안만** 접근 권한 유지
- 정기적인 **권한 검토 및 회수**

#### 2.2.1 최소 권한 구현 전략

1. **기본 거부(Default Deny)**: 명시적으로 허용되지 않은 접근은 모두 거부
2. **Just-In-Time 접근**: 필요할 때만 임시 권한 부여
3. **직무 분리(Separation of Duties)**: 중요 작업은 여러 사람이 나누어 수행
4. **권한 에스컬레이션 방지**: 사용자가 자신의 권한을 상승시킬 수 없도록 설계

#### 2.2.2 권한 정의 모범 사례

```json
// 예시: AWS IAM 정책 - 특정 S3 버킷에 대한 최소 권한
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Effect": "Allow",
      "Action": [
        "s3:GetObject",
        "s3:ListBucket"
      ],
      "Resource": [
        "arn:aws:s3:::example-bucket",
        "arn:aws:s3:::example-bucket/*"
      ],
      "Condition": {
        "IpAddress": {
          "aws:SourceIp": "192.0.2.0/24"
        },
        "DateGreaterThan": {
          "aws:CurrentTime": "2025-01-01T00:00:00Z"
        },
        "DateLessThan": {
          "aws:CurrentTime": "2025-12-31T23:59:59Z"
        }
      }
    }
  ]
}
```

### 2.3 자격 증명 관리 (Credential Management)

안전한 자격 증명 관리는 클라우드 보안의 핵심입니다.

#### 2.3.1 자격 증명 유형

**단기 자격 증명**
- 일시적으로 유효한 액세스 토큰
- 보안 위험 감소, 정기적 교체 자동화 용이
- 도용 시 피해 제한적

**장기 자격 증명**
- API 키, 액세스 키 등 오랜 기간 유효한 자격 증명
- 편의성은 높지만 보안 위험도 높음
- 유출 시 광범위한 피해 가능

#### 2.3.2 자격 증명 관리 모범 사례

1. **정기적 교체**:
   ```bash
   # AWS CLI를 이용한 액세스 키 교체
   aws iam create-access-key --user-name example-user
   # 새 키 구성 및 테스트 후
   aws iam delete-access-key --user-name example-user --access-key-id OLD_KEY_ID
   ```

2. **비밀 저장**:
   ```yaml
   # Kubernetes Secret 예시
   apiVersion: v1
   kind: Secret
   metadata:
     name: cloud-credentials
   type: Opaque
   data:
     aws_access_key_id: BASE64_ENCODED_KEY
     aws_secret_access_key: BASE64_ENCODED_SECRET
   ```

3. **자격 증명 스캐닝**:
   ```bash
   # git-secrets를 이용한 코드 저장소 스캐닝
   git secrets --scan
   
   # AWS 키 서명 패턴 등록
   git secrets --add 'AWS_ACCESS_KEY_ID[A-Z0-9]{20}'
   ```

### 2.4 다중 인증(MFA)

다중 인증은 단일 인증 방식의 취약점을 보완하는 필수적인 보안 계층입니다.

#### 2.4.1 MFA 유형

- **하드웨어 토큰**: 물리적 장치(USB 키, 스마트카드 등)
- **소프트웨어 토큰**: 인증 앱(Google Authenticator, Authy 등)
- **SMS/이메일 기반**: 문자 메시지나 이메일로 코드 전송
- **생체 인식**: 지문, 얼굴 인식 등

#### 2.4.2 MFA 구현 예시

**AWS MFA 설정**
```bash
# IAM 사용자에 MFA 디바이스 등록
aws iam create-virtual-mfa-device --virtual-mfa-device-name MyMFA \
  --outfile /tmp/QRCode.png --bootstrap-method QRCodePNG

# 사용자와 MFA 디바이스 연결
aws iam enable-mfa-device --user-name example-user \
  --serial-number arn:aws:iam::123456789012:mfa/MyMFA \
  --authentication-code-1 123456 --authentication-code-2 789012
```

**GCP MFA 정책 설정**
```bash
# 조직 수준에서 MFA 정책 설정
gcloud organizations add-iam-policy-binding ORGANIZATION_ID \
  --member="domain:example.com" \
  --role="roles/iam.securityAdmin" \
  --condition="expression=resource.type == 'organizations' && 
  request.auth.claims.google.has_mfa == true"
```

> 💡 **베스트 프랙티스**  
> 관리자 계정과 권한 있는 서비스 계정에는 항상 MFA를 적용하고, 가능하다면 일반 사용자 계정에도 MFA를 적용하세요.

---

## 3. AWS IAM 심층 분석

### 3.1 AWS IAM 구성 요소

AWS IAM은 다음과 같은 핵심 구성 요소로 이루어져 있습니다:

#### 3.1.1 사용자, 그룹, 역할

**사용자(User)**
- AWS 리소스에 접근하는 개별 인물 또는 서비스
- 장기 자격 증명(AccessKey/SecretKey) 또는 콘솔 비밀번호 사용
- 직접적인 권한 또는 그룹 멤버십을 통한 권한 부여

**그룹(Group)**
- 사용자 집합에 공통 권한 적용을 위한 메커니즘
- 그룹에 정책을 연결하여 모든 멤버에게 일괄 권한 부여
- 사용자는 여러 그룹에 속할 수 있음

**역할(Role)**
- 특정 권한을 가진 신원
- AWS 서비스, 외부 사용자, 다른 AWS 계정 등이 일시적으로 맡을 수 있음
- 신뢰 관계와 권한 정책으로 구성

```json
// AWS 역할 신뢰 정책 예시
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Effect": "Allow",
      "Principal": {
        "Service": "ec2.amazonaws.com"
      },
      "Action": "sts:AssumeRole"
    }
  ]
}
```

#### 3.1.2 정책(Policies)

AWS IAM 정책은 권한을 정의하는 JSON 문서입니다:

**정책 유형**
- **자격 증명 기반 정책**: 사용자, 그룹, 역할에 직접 연결
- **리소스 기반 정책**: S3 버킷, SQS 큐 등 리소스에 직접 연결
- **권한 경계**: 자격 증명이 가질 수 있는 최대 권한 정의
- **SCP(Service Control Policy)**: 조직 전체에 적용되는 제한 정책
- **세션 정책**: 임시 세션에 대한 권한 제한

**정책 구조**
```json
// AWS IAM 정책 구조
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Sid": "AllowEC2AndS3",
      "Effect": "Allow",
      "Action": [
        "ec2:Describe*",
        "s3:List*",
        "s3:Get*"
      ],
      "Resource": "*",
      "Condition": {
        "IpAddress": {
          "aws:SourceIp": "203.0.113.0/24"
        }
      }
    }
  ]
}
```

#### 3.1.3 권한 평가 로직

AWS에서 요청이 허용되는지 여부는 다음과 같은 로직으로 평가됩니다:

1. **기본 거부**: 명시적으로 허용되지 않은 모든 것은 거부
2. **명시적 거부 우선**: 하나라도 거부 정책이 있으면 즉시 거부
3. **정책 통합**: 적용 가능한 모든 정책 고려
4. **계정 경계 고려**: 리소스 정책, 권한 경계, SCP 등 모두 평가

```
평가 로직:
IF (요청이 SCP에 의해 거부됨) THEN 거부
ELSE IF (요청이 권한 경계에 의해 거부됨) THEN 거부
ELSE IF (요청이 리소스 정책에 의해 거부됨) THEN 거부
ELSE IF (요청이 자격 증명 정책에 의해 거부됨) THEN 거부
ELSE IF (요청이 명시적으로 허용됨) THEN 허용
ELSE 거부
```

### 3.2 AWS IAM 구현 예시

#### 3.2.1 사용자 및 그룹 관리

**CLI를 통한 관리**
```bash
# 사용자 생성
aws iam create-user --user-name developer1

# 그룹 생성
aws iam create-group --group-name Developers

# 사용자를 그룹에 추가
aws iam add-user-to-group --user-name developer1 --group-name Developers

# 정책을 그룹에 연결
aws iam attach-group-policy --group-name Developers \
  --policy-arn arn:aws:iam::aws:policy/AmazonS3ReadOnlyAccess
```

**Terraform을 통한 관리**
```hcl
# IAM 사용자 정의
resource "aws_iam_user" "developer" {
  name = "developer1"
  tags = {
    Department = "Engineering"
    Role       = "Backend Developer"
  }
}

# IAM 그룹 정의
resource "aws_iam_group" "developers" {
  name = "Developers"
}

# 사용자를 그룹에 할당
resource "aws_iam_user_group_membership" "dev_membership" {
  user   = aws_iam_user.developer.name
  groups = [aws_iam_group.developers.name]
}

# 정책 연결
resource "aws_iam_group_policy_attachment" "dev_policy" {
  group      = aws_iam_group.developers.name
  policy_arn = "arn:aws:iam::aws:policy/AmazonS3ReadOnlyAccess"
}
```

#### 3.2.2 역할 및 신뢰 관계

**EC2 인스턴스 프로필 설정**
```bash
# 역할 생성
aws iam create-role --role-name ec2-app-role \
  --assume-role-policy-document file://ec2-trust-policy.json

# 정책 연결
aws iam attach-role-policy --role-name ec2-app-role \
  --policy-arn arn:aws:iam::aws:policy/AmazonS3ReadOnlyAccess

# 인스턴스 프로필 생성 및 연결
aws iam create-instance-profile --instance-profile-name ec2-app-profile
aws iam add-role-to-instance-profile --role-name ec2-app-role \
  --instance-profile-name ec2-app-profile
```

**크로스 계정 접근 설정**
```json
// 크로스 계정 신뢰 정책
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Effect": "Allow",
      "Principal": {
        "AWS": "arn:aws:iam::ACCOUNT-B-ID:root"
      },
      "Action": "sts:AssumeRole",
      "Condition": {
        "StringEquals": {
          "aws:PrincipalOrgID": "o-organizationID"
        }
      }
    }
  ]
}
```

#### 3.2.3 권한 경계 및 SCP

**권한 경계 설정**
```bash
# 권한 경계 연결
aws iam put-user-permissions-boundary \
  --user-name developer1 \
  --permissions-boundary arn:aws:iam::aws:policy/PowerUserAccess
```

**SCP 구현**
```json
// 조직 제어 정책 - 특정 리전만 허용
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Effect": "Deny",
      "Action": "*",
      "Resource": "*",
      "Condition": {
        "StringNotEquals": {
          "aws:RequestedRegion": [
            "ap-northeast-2",
            "ap-northeast-1"
          ]
        }
      }
    }
  ]
}
```

### 3.3 AWS Security Token Service(STS)

AWS STS는 AWS 리소스에 대한 임시 자격 증명을 제공하는 서비스입니다.

#### 3.3.1 임시 자격 증명의 장점

- 유효 기간이 제한되어 있어 보안 위험 감소
- 필요할 때만 권한을 부여할 수 있음
- 자격 증명 순환이 자동으로 이루어짐
- 외부 자격 증명 제공자와 통합 가능

#### 3.3.2 주요 STS 작업

**AssumeRole**
```bash
# 역할 수임
aws sts assume-role \
  --role-arn arn:aws:iam::123456789012:role/demo-role \
  --role-session-name AWSCLI-Session
```

**AssumeRoleWithWebIdentity**
```bash
# OIDC 공급자를 통한 역할 수임
aws sts assume-role-with-web-identity \
  --role-arn arn:aws:iam::123456789012:role/demo-role \
  --role-session-name web-identity-session \
  --web-identity-token file://token.txt \
  --provider-id sts.amazonaws.com
```

**GetSessionToken**
```bash
# MFA를 사용한 임시 세션 토큰 발급
aws sts get-session-token \
  --serial-number arn:aws:iam::123456789012:mfa/user \
  --token-code 123456
```

#### 3.3.3 외부 자격 증명 제공자 통합

**CI/CD 파이프라인에서의 GitHub Actions 통합**
```yaml
# GitHub Actions에서 OIDC를 이용한 AWS 인증
name: AWS Deployment

on:
  push:
    branches: [ main ]

jobs:
  deploy:
    runs-on: ubuntu-latest
    permissions:
      id-token: write
      contents: read
    
    steps:
    - name: Checkout code
      uses: actions/checkout@v3
      
    - name: Configure AWS credentials
      uses: aws-actions/configure-aws-credentials@v1
      with:
        role-to-assume: arn:aws:iam::123456789012:role/GitHubActionsRole
        aws-region: ap-northeast-2
        
    - name: Deploy to AWS
      run: aws s3 sync ./build s3://my-app-bucket/
```

**OIDC 제공자 설정 (Terraform)**
```hcl
# AWS IAM OIDC 공급자 정의
resource "aws_iam_openid_connect_provider" "github" {
  url = "https://token.actions.githubusercontent.com"
  
  client_id_list = [
    "sts.amazonaws.com",
  ]
  
  thumbprint_list = [
    "6938fd4d98bab03faadb97b34396831e3780aea1"
  ]
}

# GitHub Actions용 IAM 역할
resource "aws_iam_role" "github_actions" {
  name = "GitHubActionsRole"
  
  assume_role_policy = jsonencode({
    Version = "2012-10-17"
    Statement = [
      {
        Action = "sts:AssumeRoleWithWebIdentity"
        Effect = "Allow"
        Principal = {
          Federated = aws_iam_openid_connect_provider.github.arn
        }
        Condition = {
          StringEquals = {
            "token.actions.githubusercontent.com:aud" = "sts.amazonaws.com"
          }
          StringLike = {
            "token.actions.githubusercontent.com:sub" = "repo:organization/repository:*"
          }
        }
      }
    ]
  })
}
```

---

## 4. Google Cloud IAM

### 4.1 GCP IAM 구성 요소

Google Cloud IAM은 "누가(주 구성원), 무엇을(역할), 어디에(리소스)"에 대한 액세스 권한을 갖는지 정의합니다.

#### 4.1.1 주 구성원(Principal)

GCP IAM의 주 구성원 유형:

- **Google 계정**: 개인 사용자 (예: user@gmail.com)
- **서비스 계정**: 애플리케이션 및 워크로드용 계정
- **Google 그룹**: 사용자 및 서비스 계정의 집합
- **G Suite 도메인**: 조직의 모든 사용자
- **Cloud Identity 도메인**: G Suite 없이 GCP만 사용하는 조직
- **allAuthenticatedUsers**: 모든 인증된 Google 계정
- **allUsers**: 인터넷의 모든 사용자 (공개 액세스)

#### 4.1.2 역할(Role)

GCP에서 역할은 권한의 모음입니다:

**1. 사전 정의된 역할**
- 기본 역할: Owner, Editor, Viewer
- 서비스별 역할: Compute Admin, Storage Admin 등

**2. 커스텀 역할**
- 특정 요구사항에 맞게 정의한 권한 집합
- 조직 또는 프로젝트 수준에서 정의 가능

```yaml
# 커스텀 역할 정의 예시 (YAML)
title: "Custom Storage Auditor"
description: "Custom role for storage audit permissions"
stage: "GA"
includedPermissions:
- storage.buckets.get
- storage.buckets.list
- storage.objects.list
- monitoring.timeSeries.list
```

#### 4.1.3 리소스 계층구조

GCP 리소스 계층구조는 상속 모델의 기반입니다:

```
Organization
   ↓
Folders
   ↓
Projects
   ↓
Resources (buckets, instances, etc.)
```

- 상위 수준에서 설정된 권한은 하위 리소스로 상속됨
- 각 수준에서 허용 정책 추가 가능
- 상속된 정책과 직접 설정된 정책이 통합됨

### 4.2 GCP IAM 구현 예시

#### 4.2.1 서비스 계정 관리

**서비스 계정 생성 및 관리**
```bash
# 서비스 계정 생성
gcloud iam service-accounts create my-service-account \
  --display-name "My Service Account"

# 서비스 계정에 역할 부여
gcloud projects add-iam-policy-binding my-project-id \
  --member="serviceAccount:my-service-account@my-project-id.iam.gserviceaccount.com" \
  --role="roles/storage.objectViewer"

# 서비스 계정 키 생성
gcloud iam service-accounts keys create key.json \
  --iam-account=my-service-account@my-project-id.iam.gserviceaccount.com
```

**Terraform을 통한 서비스 계정 관리**
```hcl
# 서비스 계정 생성
resource "google_service_account" "app_service_account" {
  account_id   = "app-service-account"
  display_name = "Application Service Account"
  project      = "my-project-id"
}

# 역할 부여
resource "google_project_iam_binding" "app_service_account_roles" {
  project = "my-project-id"
  role    = "roles/storage.objectViewer"
  
  members = [
    "serviceAccount:${google_service_account.app_service_account.email}",
  ]
}
```

#### 4.2.2 커스텀 역할 정의

**CLI를 통한 커스텀 역할 생성**
```bash
# YAML 파일로 커스텀 역할 생성
gcloud iam roles create storageAuditor --project=my-project-id \
  --file=role-definition.yaml

# 권한 목록으로 커스텀 역할 생성
gcloud iam roles create networkViewer --project=my-project-id \
  --title="Network Viewer" \
  --description="Custom role for viewing network resources" \
  --permissions=compute.networks.get,compute.networks.list,compute.subnetworks.get,compute.subnetworks.list \
  --stage=ALPHA
```

**Terraform을 통한 커스텀 역할 관리**
```hcl
# 프로젝트 수준 커스텀 역할
resource "google_project_iam_custom_role" "storage_auditor" {
  role_id     = "storageAuditor"
  title       = "Storage Auditor"
  description = "Role for auditing storage resources"
  permissions = [
    "storage.buckets.get",
    "storage.buckets.list",
    "storage.objects.list",
    "logging.logEntries.list"
  ]
}

# 조직 수준 커스텀 역할
resource "google_organization_iam_custom_role" "network_manager" {
  org_id      = "123456789012"
  role_id     = "networkManager"
  title       = "Network Manager"
  description = "Manage network configurations across organization"
  permissions = [
    "compute.networks.create",
    "compute.networks.delete",
    "compute.networks.update",
    "compute.subnetworks.create",
    "compute.subnetworks.delete",
    "compute.firewalls.create",
    "compute.firewalls.delete"
  ]
}
```

#### 4.2.3 조건부 역할 바인딩

GCP IAM은 조건부 역할 바인딩을 지원하여 액세스를 더 세밀하게 제어할 수 있습니다.

**조건부 역할 바인딩 예시**
```bash
# 특정 태그가 있는 리소스만 액세스 허용
gcloud projects add-iam-policy-binding my-project-id \
  --member="user:developer@example.com" \
  --role="roles/compute.admin" \
  --condition="expression=resource.matchTag('env', 'dev'),title=DevOnly,description=Access to dev resources only"

# 시간 기반 액세스 제어
gcloud projects add-iam-policy-binding my-project-id \
  --member="user:ops@example.com" \
  --role="roles/compute.instanceAdmin" \
  --condition="expression=request.time.getHours('Asia/Seoul') >= 9 && request.time.getHours('Asia/Seoul') < 18,title=BusinessHours,description=Access during business hours only"
```

**Terraform으로 조건부 역할 정의**
```hcl
resource "google_project_iam_binding" "conditional_access" {
  project = "my-project-id"
  role    = "roles/storage.admin"
  
  members = [
    "user:admin@example.com",
  ]
  
  condition {
    title       = "AccessFromCorporateIP"
    description = "Access only from corporate IP range"
    expression  = "request.ip.matches('192.168.0.0/16')"
  }
}
```

### 4.3 GCP 워크로드 아이덴티티

GCP 워크로드 아이덴티티는 서비스 계정 키 없이 GCP 리소스와 안전하게 상호 작용할 수 있는 방법을 제공합니다.

#### 4.3.1 GKE 워크로드 아이덴티티

Kubernetes 서비스 계정을 GCP 서비스 계정에 연결하여 안전하게 인증합니다.

```bash
# 클러스터에 워크로드 아이덴티티 활성화
gcloud container clusters update my-cluster \
  --workload-pool=my-project-id.svc.id.goog

# Kubernetes 네임스페이스와 GCP 서비스 계정 연결
kubectl create namespace my-app
kubectl annotate serviceaccount default \
  --namespace my-app \
  iam.gke.io/gcp-service-account=my-service-account@my-project-id.iam.gserviceaccount.com

# IAM 정책 바인딩 설정
gcloud iam service-accounts add-iam-policy-binding \
  --role roles/iam.workloadIdentityUser \
  --member "serviceAccount:my-project-id.svc.id.goog[my-app/default]" \
  my-service-account@my-project-id.iam.gserviceaccount.com
```

**Terraform으로 워크로드 아이덴티티 구성**
```hcl
# GKE 클러스터 구성
resource "google_container_cluster" "my_cluster" {
  name     = "my-cluster"
  location = "us-central1"
  
  workload_identity_config {
    workload_pool = "${google_project.my_project.project_id}.svc.id.goog"
  }
}

# Kubernetes 서비스 계정을 위한 IAM 바인딩
resource "google_service_account_iam_binding" "workload_identity_binding" {
  service_account_id = google_service_account.app_service_account.name
  role               = "roles/iam.workloadIdentityUser"
  
  members = [
    "serviceAccount:${google_project.my_project.project_id}.svc.id.goog[my-app/default]",
  ]
}
```

#### 4.3.2 Cloud Run/Cloud Functions 아이덴티티

서버리스 환경에서의 아이덴티티 관리:

```bash
# Cloud Run 서비스에 서비스 계정 연결
gcloud run services update my-service \
  --service-account=my-service-account@my-project-id.iam.gserviceaccount.com

# Cloud Function에 서비스 계정 연결
gcloud functions deploy my-function \
  --service-account=my-service-account@my-project-id.iam.gserviceaccount.com \
  --runtime nodejs14 \
  --trigger-http
```

### 4.4 GCP 조직 정책

조직 정책은 전체 조직 또는 프로젝트에 걸쳐 리소스 사용을 제한하는 규칙을 설정합니다.

#### 4.4.1 주요 조직 정책 예시

**리소스 위치 제한**
```bash
# 리소스 위치 제한 정책 설정
gcloud resource-manager org-policies set-policy \
  --organization=123456789012 location-policy.yaml

# location-policy.yaml 내용
name: organizations/123456789012/policies/gcp.resourceLocations
spec:
  rules:
  - values:
      allowedValues:
      - in:asia-locations
      - in:eu-locations
```

**도메인 제한 공유**
```bash
# 특정 도메인에만 리소스 공유 허용
gcloud resource-manager org-policies set-policy \
  --organization=123456789012 domain-policy.yaml

# domain-policy.yaml 내용
name: organizations/123456789012/policies/iam.allowedPolicyMemberDomains
spec:
  rules:
  - values:
      allowedValues:
      - example.com
```

**Terraform을 통한 조직 정책 설정**
```hcl
# 리소스 위치 제한 정책
resource "google_organization_policy" "resource_locations" {
  org_id     = "123456789012"
  constraint = "gcp.resourceLocations"

  list_policy {
    allow {
      values = [
        "in:asia-locations",
        "in:eu-locations",
      ]
    }
  }
}

# VM 인스턴스에 외부 IP 비활성화
resource "google_organization_policy" "disable_vm_external_ip" {
  org_id     = "123456789012"
  constraint = "compute.vmExternalIpAccess"

  boolean_policy {
    enforced = true
  }
}
```

---

## 5. Microsoft Azure RBAC

Azure RBAC(Role-Based Access Control)는 Azure 리소스에 대한 세밀한 액세스 관리를 제공합니다.

### 5.1 Azure RBAC 구성 요소

Azure RBAC의 핵심 구성 요소는 다음과 같습니다:

#### 5.1.1 보안 주체(Security Principal)

- **사용자**: Azure AD의 개인 계정
- **그룹**: Azure AD의 사용자 집합
- **서비스 주체**: 애플리케이션 및 자동화에 사용
- **관리 ID**: Azure 서비스에서 사용하는 자동 관리 ID

#### 5.1.2 역할 정의(Role Definition)

역할 정의는 권한 집합으로, 다음을 지정합니다:
- **작업(Actions)**: 허용하는 작업
- **NotActions**: 제외할 작업
- **DataActions**: 데이터에 대한 작업
- **NotDataActions**: 제외할 데이터 작업

**내장 역할 유형**
- **소유자(Owner)**: 모든 리소스 관리 및 액세스 부여
- **기여자(Contributor)**: 모든 리소스 관리(액세스 부여 제외)
- **읽기 권한자(Reader)**: 모든 리소스 보기
- **사용자 액세스 관리자**: 사용자 액세스 관리 가능

#### 5.1.3 범위(Scope)

액세스가 적용되는 수준:
- **관리 그룹**: 여러 구독을 포함하는 컨테이너
- **구독(Subscription)**: 결제 단위 및 리소스 그룹 모음
- **리소스 그룹**: 관련 리소스의 논리적 그룹
- **리소스**: 개별 서비스 인스턴스

### 5.2 Azure RBAC 구현 예시

#### 5.2.1 역할 할당

**Azure CLI를 통한 역할 할당**
```bash
# 구독 수준에서 역할 할당
az role assignment create \
  --assignee user@example.com \
  --role "Virtual Machine Contributor" \
  --subscription "subscription-id"

# 리소스 그룹 수준에서 역할 할당
az role assignment create \
  --assignee serviceprincipal@example.com \
  --role "SQL DB Contributor" \
  --resource-group "database-rg"
```

**Azure PowerShell을 통한 역할 할당**
```powershell
# 사용자에게 역할 할당
New-AzRoleAssignment -SignInName user@example.com `
  -RoleDefinitionName "Storage Blob Data Reader" `
  -ResourceGroupName "storage-rg"

# 서비스 주체에게 역할 할당
New-AzRoleAssignment -ApplicationId "00000000-0000-0000-0000-000000000000" `
  -RoleDefinitionName "Network Contributor" `
  -ResourceGroupName "network-rg"
```

**Terraform으로 역할 할당 관리**
```hcl
# 구독 수준 역할 할당
resource "azurerm_role_assignment" "example" {
  scope                = "/subscriptions/00000000-0000-0000-0000-000000000000"
  role_definition_name = "Reader"
  principal_id         = "00000000-0000-0000-0000-000000000000"
}

# 리소스 그룹 수준 역할 할당
resource "azurerm_role_assignment" "rg_assignment" {
  scope                = azurerm_resource_group.example.id
  role_definition_name = "Contributor"
  principal_id         = azurerm_user_assigned_identity.example.principal_id
}
```

#### 5.2.2 커스텀 역할 정의

**Azure CLI를 통한 커스텀 역할 생성**
```bash
# JSON 파일로 커스텀 역할 정의
az role definition create --role-definition @custom-role.json

# custom-role.json 내용
{
  "Name": "Virtual Machine Operator",
  "Description": "Can monitor and restart virtual machines.",
  "Actions": [
    "Microsoft.Storage/*/read",
    "Microsoft.Network/*/read",
    "Microsoft.Compute/*/read",
    "Microsoft.Compute/virtualMachines/start/action",
    "Microsoft.Compute/virtualMachines/restart/action"
  ],
  "NotActions": [],
  "AssignableScopes": [
    "/subscriptions/00000000-0000-0000-0000-000000000000"
  ]
}
```

**Azure PowerShell을 통한 커스텀 역할**
```powershell
# 기존 역할을 기반으로 새 역할 생성
$role = Get-AzRoleDefinition -Name "Virtual Machine Contributor"
$role.Id = $null
$role.Name = "Virtual Machine Operator"
$role.Description = "Can monitor and restart virtual machines."
$role.Actions.Clear()
$role.Actions.Add("Microsoft.Storage/*/read")
$role.Actions.Add("Microsoft.Network/*/read")
$role.Actions.Add("Microsoft.Compute/*/read")
$role.Actions.Add("Microsoft.Compute/virtualMachines/start/action")
$role.Actions.Add("Microsoft.Compute/virtualMachines/restart/action")
$role.AssignableScopes.Clear()
$role.AssignableScopes.Add("/subscriptions/00000000-0000-0000-0000-000000000000")
New-AzRoleDefinition -Role $role
```

**Terraform을 통한 커스텀 역할 정의**
```hcl
resource "azurerm_role_definition" "vm_operator" {
  name        = "Virtual Machine Operator"
  scope       = data.azurerm_subscription.primary.id
  description = "Can monitor and restart virtual machines."
  
  permissions {
    actions = [
      "Microsoft.Storage/*/read",
      "Microsoft.Network/*/read",
      "Microsoft.Compute/*/read",
      "Microsoft.Compute/virtualMachines/start/action",
      "Microsoft.Compute/virtualMachines/restart/action"
    ]
    not_actions = []
  }
  
  assignable_scopes = [
    data.azurerm_subscription.primary.id
  ]
}
```

### 5.3 Azure 관리 ID

관리 ID는 Azure 리소스에 Azure AD 신원을 제공하여 서비스 계정 대신 사용할 수 있습니다.

#### 5.3.1 시스템 할당 관리 ID

리소스에 직접 연결된 관리 ID로, 리소스 수명 주기와 함께 관리됩니다.

```bash
# VM에 시스템 할당 관리 ID 활성화
az vm identity assign --name my-vm --resource-group my-rg

# 앱 서비스에 시스템 할당 관리 ID 활성화
az webapp identity assign --name my-app --resource-group my-rg
```

**Terraform으로 시스템 할당 관리 ID 구성**
```hcl
resource "azurerm_virtual_machine" "example" {
  name                  = "my-vm"
  location              = azurerm_resource_group.example.location
  resource_group_name   = azurerm_resource_group.example.name
  # ... 다른 VM 설정 ...
  
  identity {
    type = "SystemAssigned"
  }
}
```

#### 5.3.2 사용자 할당 관리 ID

여러 리소스에서 공유할 수 있는 독립적인 Azure 리소스입니다.

```bash
# 사용자 할당 관리 ID 생성
az identity create --name my-identity --resource-group my-rg

# VM에 사용자 할당 관리 ID 연결
az vm identity assign --name my-vm --resource-group my-rg \
  --identities /subscriptions/subscription-id/resourcegroups/my-rg/providers/Microsoft.ManagedIdentity/userAssignedIdentities/my-identity
```

**Terraform으로 사용자 할당 관리 ID 관리**
```hcl
# 사용자 할당 관리 ID 생성
resource "azurerm_user_assigned_identity" "example" {
  name                = "my-identity"
  resource_group_name = azurerm_resource_group.example.name
  location            = azurerm_resource_group.example.location
}

# 관리 ID를 VM에 할당
resource "azurerm_virtual_machine" "example" {
  name                  = "my-vm"
  # ... 다른 VM 설정 ...
  
  identity {
    type = "UserAssigned"
    identity_ids = [
      azurerm_user_assigned_identity.example.id
    ]
  }
}
```

#### 5.3.3 관리 ID를 통한 Azure 키 자격 증명 모음 액세스

관리 ID를 사용하여 키 자격 증명 모음의 비밀에 액세스하는 예시:

```csharp
// C# 코드: 관리 ID를 사용한 키 자격 증명 모음 액세스
using Azure.Identity;
using Azure.Security.KeyVault.Secrets;

// 관리 ID를 사용하여 인증
var credential = new DefaultAzureCredential();

// 키 자격 증명 모음 클라이언트 생성
var client = new SecretClient(
    new Uri("https://myvault.vault.azure.net/"), 
    credential);

// 비밀 가져오기
KeyVaultSecret secret = await client.GetSecretAsync("mySecret");
string secretValue = secret.Value;
```

```javascript
// Node.js: 관리 ID를 사용한 키 자격 증명 모음 액세스
const { DefaultAzureCredential } = require("@azure/identity");
const { SecretClient } = require("@azure/keyvault-secrets");

async function getSecret() {
  // 관리 ID를 사용하여 인증
  const credential = new DefaultAzureCredential();
  
  // 키 자격 증명 모음 클라이언트 생성
  const client = new SecretClient(
    "https://myvault.vault.azure.net/",
    credential
  );
  
  // 비밀 가져오기
  const secret = await client.getSecret("mySecret");
  return secret.value;
}
```

---

## 6. IAM 모범 사례 및 보안 강화

### 6.1 최소 권한 원칙 적용

최소 권한 원칙을 효과적으로 적용하기 위한 전략:

#### 6.1.1 권한 정책 설계

**정책 설계 모범 사례**
1. **리소스 제한**: 특정 리소스에만 권한 부여
2. **작업 제한**: 필요한 작업만 허용
3. **조건 활용**: 특정 조건에서만 접근 허용
4. **임시 권한 활용**: 필요한 기간 동안만 권한 부여

**AWS 정책 예시: 특정 S3 버킷 접근 제한**
```json
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Effect": "Allow",
      "Action": "s3:*",
      "Resource": [
        "arn:aws:s3:::example-bucket",
        "arn:aws:s3:::example-bucket/*"
      ]
    }
  ]
}
```

**GCP 정책 예시: 특정 VM 인스턴스만 관리**
```yaml
title: "VM Instance Operator"
description: "Can start/stop specific VM instances"
stage: "GA"
includedPermissions:
- compute.instances.get
- compute.instances.list
- compute.instances.start
- compute.instances.stop
- compute.instances.reset
```

#### 6.1.2 권한 경계 및 가드레일

권한을 제한하는 추가 메커니즘:

**AWS 권한 경계**
```json
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Effect": "Allow",
      "Action": [
        "s3:*",
        "cloudwatch:*",
        "ec2:Describe*"
      ],
      "Resource": "*"
    },
    {
      "Effect": "Deny",
      "Action": [
        "iam:*",
        "organizations:*"
      ],
      "Resource": "*"
    }
  ]
}
```

**Azure 정책을 사용한 제한**
```json
{
  "properties": {
    "displayName": "Allowed locations",
    "description": "This policy enables you to restrict the locations your organization can create resources in.",
    "mode": "Indexed",
    "parameters": {
      "allowedLocations": {
        "type": "Array",
        "metadata": {
          "description": "The list of allowed locations for resources.",
          "displayName": "Allowed locations",
          "strongType": "location"
        }
      }
    },
    "policyRule": {
      "if": {
        "not": {
          "field": "location",
          "in": "[parameters('allowedLocations')]"
        }
      },
      "then": {
        "effect": "deny"
      }
    }
  }
}
```

### 6.2 자격 증명 및 비밀 관리

#### 6.2.1 비밀 저장소 활용

**AWS Secrets Manager**
```bash
# 비밀 생성
aws secretsmanager create-secret \
  --name production/db-credentials \
  --description "Database credentials for production" \
  --secret-string '{"username":"admin","password":"t0p-s3cr3t"}'

# 자동 교체 설정
aws secretsmanager rotate-secret \
  --secret-id production/db-credentials \
  --rotation-lambda-arn arn:aws:lambda:region:account:function:rotate-db-creds \
  --rotation-rules '{"AutomaticallyAfterDays": 30}'
```

**Azure Key Vault**
```bash
# 키 자격 증명 모음 생성
az keyvault create --name MyVault --resource-group MyResourceGroup --location eastus

# 비밀 추가
az keyvault secret set --vault-name MyVault --name DBPassword --value "t0p-s3cr3t"

# 비밀 가져오기
az keyvault secret show --vault-name MyVault --name DBPassword
```

**GCP Secret Manager**
```bash
# 비밀 생성
echo -n "t0p-s3cr3t" | gcloud secrets create db-password --data-file=-

# 비밀 버전 추가 (교체)
echo -n "n3w-s3cr3t" | gcloud secrets versions add db-password --data-file=-

# 비밀 접근
gcloud secrets versions access latest --secret=db-password
```

#### 6.2.2 자격 증명 순환

**자동 자격 증명 순환 구현**
```python
import boto3
import json
import os
from datetime import datetime, timedelta

def lambda_handler(event, context):
    # 90일보다 오래된 액세스 키 식별
    iam = boto3.client('iam')
    users = iam.list_users()['Users']
    
    for user in users:
        username = user['UserName']
        keys = iam.list_access_keys(UserName=username)['AccessKeyMetadata']
        
        for key in keys:
            key_id = key['AccessKeyId']
            create_date = key['CreateDate']
            
            # 키 생성일이 90일 이상 지났는지 확인
            if datetime.now().replace(tzinfo=create_date.tzinfo) - create_date > timedelta(days=90):
                print(f"Rotating access key for user: {username}, key: {key_id}")
                
                # 새 키 생성
                new_key = iam.create_access_key(UserName=username)
                new_key_id = new_key['AccessKey']['AccessKeyId']
                new_secret = new_key['AccessKey']['SecretAccessKey']
                
                # 새 키 정보 저장 (예: Secrets Manager)
                store_new_credentials(username, new_key_id, new_secret)
                
                # 필요한 시스템 업데이트 (예: CI/CD 구성 등)
                update_systems_with_new_key(username, new_key_id, new_secret)
                
                # 이전 키 비활성화 (유예 기간 부여)
                iam.update_access_key(
                    UserName=username,
                    AccessKeyId=key_id,
                    Status='Inactive'
                )
                
                # 나중에 삭제하기 위해 표시
                mark_for_deletion(username, key_id)
```

### 6.3 다중 계정 전략

대규모 환경에서는 다중 계정 접근 방식을 사용하여 보안을 강화합니다.

#### 6.3.1 AWS Organizations

**AWS Organizations 구조**
```
Root
├── Security OU
│   ├── Audit Account
│   └── Security Tooling Account
├── Infrastructure OU
│   ├── Shared Services Account
│   └── Network Account
├── Workloads OU
│   ├── Development OU
│   │   ├── Dev Account 1
│   │   └── Dev Account 2
│   ├── Test OU
│   │   └── Test Account
│   └── Production OU
│       ├── Prod Account 1
│       └── Prod Account 2
└── Sandbox OU
    └── Sandbox Account
```

**SCP(서비스 제어 정책)로 계정 제한**
```json
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Effect": "Deny",
      "Action": [
        "iam:CreateUser",
        "iam:CreateAccessKey"
      ],
      "Resource": "*",
      "Condition": {
        "StringNotEquals": {
          "aws:PrincipalTag/Department": "IT-Security"
        }
      }
    }
  ]
}
```

#### 6.3.2 Azure 관리 그룹

**Azure 관리 그룹 계층 구조**
```
Root Management Group
├── Platform Management Group
│   ├── Identity Subscription
│   ├── Management Subscription
│   └── Connectivity Subscription
├── Landing Zones Management Group
│   ├── Development Management Group
│   │   └── Dev Subscriptions
│   ├── Test Management Group
│   │   └── Test Subscriptions
│   └── Production Management Group
│       └── Production Subscriptions
└── Sandbox Management Group
    └── Sandbox Subscriptions
```

**Azure 정책을 사용한 규정 준수 적용**
```json
{
  "properties": {
    "displayName": "Allowed resource types",
    "description": "This policy restricts the resource types that can be deployed",
    "mode": "Indexed",
    "parameters": {},
    "policyRule": {
      "if": {
        "not": {
          "field": "type",
          "in": [
            "Microsoft.Compute/virtualMachines",
            "Microsoft.Network/virtualNetworks",
            "Microsoft.Storage/storageAccounts"
          ]
        }
      },
      "then": {
        "effect": "deny"
      }
    }
  }
}
```

#### 6.3.3 GCP 조직 구조

**GCP 조직 계층 구조**
```
Organization
├── Security Folder
│   ├── Security Project
│   └── Audit Project
├── Infrastructure Folder
│   ├── Shared VPC Project
│   └── CI/CD Project
├── Development Folder
│   ├── Team A Dev Project
│   └── Team B Dev Project
├── Testing Folder
│   └── QA Projects
└── Production Folder
    ├── Service A Project
    └── Service B Project
```

### 6.4 권한 검토 및 감사

#### 6.4.1 접근 분석 도구

**AWS Access Analyzer**
```bash
# 분석기 생성
aws accessanalyzer create-analyzer \
  --analyzer-name OrganizationAnalyzer \
  --type ORGANIZATION

# 조사 결과 목록 가져오기
aws accessanalyzer list-findings \
  --analyzer-arn arn:aws:access-analyzer:region:account-id:analyzer/OrganizationAnalyzer

# 조사 결과 아카이브
aws accessanalyzer update-findings \
  --analyzer-arn arn:aws:access-analyzer:region:account-id:analyzer/OrganizationAnalyzer \
  --ids finding-id \
  --status ARCHIVED
```

**Azure Policy Insights**
```bash
# 정책 준수 상태 확인
az policy state list --resource-group MyResourceGroup

# 비준수 리소스 찾기
az policy state list --filter "complianceState eq 'NonCompliant'"

# 특정 정책에 대한 준수 상태 확인
az policy state list --policy-definition-name "allowed-locations"
```

**GCP IAM 권한 감사**
```bash
# 프로젝트 내 역할 할당 검토
gcloud projects get-iam-policy my-project-id

# 과도한 권한을 가진 사용자 식별
gcloud asset search-all-resources \
  --scope=projects/my-project-id \
  --asset-types="iam.googleapis.com/Role" \
  --query="name:Owner OR name:Editor"

# 조직 전체 IAM 정책 검색
gcloud asset search-all-iam-policies \
  --scope=organizations/organization-id \
  --query="policy.binding.role:roles/owner"
```

#### 6.4.2 지속적인 모니터링 및 자동화

**AWS CloudTrail + CloudWatch + Lambda 조합**
```python
# Lambda 함수: 민감한 IAM 작업 모니터링
import boto3
import json
import os

def lambda_handler(event, context):
    # CloudTrail 이벤트 파싱
    detail = event.get('detail', {})
    event_name = detail.get('eventName', '')
    user_identity = detail.get('userIdentity', {})
    user_name = user_identity.get('userName', 'Unknown')
    
    # 민감한 IAM 작업 목록
    sensitive_actions = [
        'CreateUser', 'DeleteUser', 'AttachUserPolicy', 'AttachRolePolicy',
        'CreateAccessKey', 'PutUserPolicy', 'PutRolePolicy'
    ]
    
    # 민감한 IAM 작업 감지 시 알림
    if event_name in sensitive_actions:
        sns = boto3.client('sns')
        message = f"민감한 IAM 작업 감지: {event_name} by {user_name}"
        sns.publish(
            TopicArn=os.environ['SNS_TOPIC_ARN'],
            Message=message,
            Subject='IAM 보안 알림'
        )
        
        # 추가 조치 (예: 자동 조사, 자동 교정 등)
        if event_name == 'AttachUserPolicy':
            policy_arn = detail.get('requestParameters', {}).get('policyArn', '')
            if 'AdministratorAccess' in policy_arn:
                # 관리자 권한 부여 추가 검증
                initiate_admin_access_review(user_name, policy_arn)
```

**GCP Cloud Asset Inventory + Cloud Functions 조합**
```python
# Cloud Functions: IAM 정책 변경 모니터링
from google.cloud import asset_v1
from google.cloud import pubsub_v1
import json
import os

def monitor_iam_changes(event, context):
    """Cloud Pub/Sub 트리거 함수, IAM 정책 변경 모니터링."""
    pubsub_message = json.loads(event['data'])
    asset_name = pubsub_message.get('asset_name', '')
    
    # 자산 데이터 가져오기
    client = asset_v1.AssetServiceClient()
    response = client.get_asset(
        request={
            "name": asset_name
        }
    )
    
    # IAM 정책 변경 분석
    if response.iam_policy:
        bindings = response.iam_policy.bindings
        for binding in bindings:
            role = binding.role
            members = binding.members
            
            # 고권한 역할 확인
            if role in ['roles/owner', 'roles/editor']:
                for member in members:
                    # 외부 이메일 도메인 확인
                    if member.startswith('user:') and not member.endswith('@company.com'):
                        send_alert(asset_name, role, member)
```

**Azure Monitor + Logic Apps**
```json
{
  "definition": {
    "$schema": "https://schema.management.azure.com/providers/Microsoft.Logic/schemas/2016-06-01/workflowdefinition.json#",
    "actions": {
      "Parse_Activity_Log_Alert": {
        "inputs": {
          "content": "@triggerBody()",
          "schema": {
            "properties": {
              "data": {
                "properties": {
                  "context": {
                    "properties": {
                      "authorization": {},
                      "caller": {},
                      "claims": {},
                      "eventSource": {},
                      "eventTimestamp": {},
                      "eventVersion": {},
                      "level": {},
                      "operationId": {},
                      "operationName": {},
                      "status": {}
                    },
                    "type": "object"
                  }
                },
                "type": "object"
              }
            },
            "type": "object"
          }
        },
        "runAfter": {},
        "type": "ParseJson"
      },
      "Condition_-_Check_for_IAM_Changes": {
        "actions": {
          "Send_an_email_(V2)": {
            "inputs": {
              "body": {
                "Body": "<p>중요한 IAM 변경이 감지되었습니다:<br>\n<br>\n작업: @{body('Parse_Activity_Log_Alert')?['data']?['context']?['operationName']}<br>\n수행자: @{body('Parse_Activity_Log_Alert')?['data']?['context']?['caller']}<br>\n타임스탬프: @{body('Parse_Activity_Log_Alert')?['data']?['context']?['eventTimestamp']}<br>\n<br>\n작업 상태: @{body('Parse_Activity_Log_Alert')?['data']?['context']?['status']?['value']}</p>",
                "Subject": "Azure IAM 변경 알림",
                "To": "security@company.com"
              },
              "host": {
                "connection": {
                  "name": "@parameters('$connections')['office365']['connectionId']"
                }
              },
              "method": "post",
              "path": "/v2/Mail"
            },
            "runAfter": {},
            "type": "ApiConnection"
          }
        },
        "expression": {
          "and": [
            {
              "contains": [
                "@body('Parse_Activity_Log_Alert')?['data']?['context']?['operationName']",
                "Microsoft.Authorization/roleAssignments"
              ]
            }
          ]
        },
        "runAfter": {
          "Parse_Activity_Log_Alert": [
            "Succeeded"
          ]
        },
        "type": "If"
      }
    },
    "contentVersion": "1.0.0.0",
    "outputs": {},
    "parameters": {
      "$connections": {
        "defaultValue": {},
        "type": "Object"
      }
    },
    "triggers": {
      "manual": {
        "inputs": {
          "schema": {}
        },
        "kind": "Http",
        "type": "Request"
      }
    }
  }
}
```

#### 6.4.3 권한 분석 및 최적화

**AWS CloudTrail Access Analyzer**
```bash
# 지난 90일 동안 사용하지 않은 IAM 정책 권한 분석
aws accessanalyzer start-policy-generation \
  --policy-generation-details '{"principalArn":"arn:aws:iam::123456789012:role/RoleToAnalyze"}' \
  --cloud-trail-details '{"startTime":"2023-04-15T00:00:00Z", "endTime":"2023-07-15T00:00:00Z"}'

# 생성된 권장 IAM 정책 보기
aws accessanalyzer get-generated-policy \
  --job-id d909fdda-132a-3d32-b5e3-12345EXAMPLE
```

**스크립트를 사용한 미사용 권한 식별**
```python
import boto3
import datetime

def analyze_iam_usage():
    # CloudTrail에서 지난 90일 이벤트 검색
    cloudtrail = boto3.client('cloudtrail')
    iam = boto3.client('iam')
    
    # 모든 사용자 및 역할 가져오기
    users = iam.list_users()['Users']
    roles = iam.list_roles()['Roles']
    
    # 분석 결과 저장
    unused_permissions = {}
    
    # 각 사용자에 대해 분석
    for user in users:
        user_arn = user['Arn']
        unused_permissions[user_arn] = analyze_entity_permissions(cloudtrail, iam, user_arn, 'user')
    
    # 각 역할에 대해 분석
    for role in roles:
        role_arn = role['Arn']
        unused_permissions[role_arn] = analyze_entity_permissions(cloudtrail, iam, role_arn, 'role')
    
    return unused_permissions

def analyze_entity_permissions(cloudtrail, iam, entity_arn, entity_type):
    # 엔티티의 권한 목록 가져오기
    permissions = get_entity_permissions(iam, entity_arn, entity_type)
    
    # 지난 90일 동안의 CloudTrail 이벤트 검색
    ninety_days_ago = datetime.datetime.now() - datetime.timedelta(days=90)
    
    used_permissions = set()
    
    # CloudTrail 이벤트 조회
    if entity_type == 'user':
        entity_name = entity_arn.split('/')[-1]
        attribute = 'Username'
    else:
        entity_name = entity_arn.split('/')[-1]
        attribute = 'AssumedRoleUser.Arn'
        
    paginator = cloudtrail.get_paginator('lookup_events')
    for page in paginator.paginate(
        LookupAttributes=[{
            'AttributeKey': attribute,
            'AttributeValue': entity_name
        }],
        StartTime=ninety_days_ago
    ):
        for event in page['Events']:
            event_name = event.get('EventName', '')
            event_source = event.get('EventSource', '')
            
            # 사용된 API 호출 추적
            if event_source and event_name:
                service = event_source.split('.')[0]
                used_permissions.add(f"{service}:{event_name.lower()}")
    
    # 미사용 권한 식별
    unused = permissions - used_permissions
    return list(unused)
```

### 6.5 권한 통제 자동화

#### 6.5.1 Infrastructure as Code를 통한 IAM 관리

**Terraform을 사용한 IAM 관리 자동화**
```hcl
# AWS IAM 모듈
module "iam_roles" {
  source = "./modules/iam_roles"
  
  admin_users = ["admin1", "admin2"]
  developer_users = ["dev1", "dev2", "dev3"]
  operator_users = ["op1", "op2"]
  
  admin_policy_arns = [
    "arn:aws:iam::aws:policy/AdministratorAccess"
  ]
  
  developer_policy_arns = [
    "arn:aws:iam::aws:policy/AmazonS3ReadOnlyAccess",
    "arn:aws:iam::aws:policy/AmazonDynamoDBReadOnlyAccess"
  ]
  
  operator_policy_arns = [
    "arn:aws:iam::aws:policy/AmazonEC2ReadOnlyAccess",
    "arn:aws:iam::aws:policy/CloudWatchReadOnlyAccess"
  ]
}

# Azure RBAC 모듈
module "azure_rbac" {
  source = "./modules/azure_rbac"
  
  subscription_id = var.subscription_id
  
  role_assignments = [
    {
      principal_id = "00000000-0000-0000-0000-000000000001"
      role_definition_name = "Contributor"
      scope = "/subscriptions/${var.subscription_id}/resourceGroups/app-rg"
    },
    {
      principal_id = "00000000-0000-0000-0000-000000000002"
      role_definition_name = "Reader"
      scope = "/subscriptions/${var.subscription_id}"
    }
  ]
}
```

**AWS CDK를 사용한 IAM 정의**
```typescript
import * as cdk from 'aws-cdk-lib';
import { Construct } from 'constructs';
import * as iam from 'aws-cdk-lib/aws-iam';

export class IamStack extends cdk.Stack {
  constructor(scope: Construct, id: string, props?: cdk.StackProps) {
    super(scope, id, props);

    // 개발자 그룹 생성
    const developersGroup = new iam.Group(this, 'Developers', {
      groupName: 'Developers',
      managedPolicies: [
        iam.ManagedPolicy.fromAwsManagedPolicyName('AmazonS3ReadOnlyAccess'),
        iam.ManagedPolicy.fromAwsManagedPolicyName('AmazonDynamoDBReadOnlyAccess')
      ]
    });
    
    // 개발자 그룹을 위한 커스텀 정책
    const developerCustomPolicy = new iam.Policy(this, 'DeveloperCustomPolicy', {
      statements: [
        new iam.PolicyStatement({
          effect: iam.Effect.ALLOW,
          actions: [
            'cloudwatch:GetMetricData',
            'cloudwatch:ListMetrics'
          ],
          resources: ['*']
        }),
        new iam.PolicyStatement({
          effect: iam.Effect.ALLOW,
          actions: [
            'logs:GetLogEvents',
            'logs:FilterLogEvents'
          ],
          resources: ['arn:aws:logs:*:*:log-group:/aws/lambda/*']
        })
      ]
    });
    
    developerCustomPolicy.attachToGroup(developersGroup);
    
    // 람다 실행 역할 생성
    const lambdaExecutionRole = new iam.Role(this, 'LambdaExecutionRole', {
      assumedBy: new iam.ServicePrincipal('lambda.amazonaws.com'),
      description: 'Role for Lambda functions to access required resources',
      managedPolicies: [
        iam.ManagedPolicy.fromAwsManagedPolicyName('service-role/AWSLambdaBasicExecutionRole')
      ]
    });
    
    // 람다 역할에 추가 권한 부여
    lambdaExecutionRole.addToPolicy(new iam.PolicyStatement({
      effect: iam.Effect.ALLOW,
      actions: [
        's3:GetObject',
        's3:PutObject'
      ],
      resources: [
        'arn:aws:s3:::app-data-bucket/*'
      ]
    }));
  }
}
```

#### 6.5.2 CI/CD 파이프라인에서의 IAM 검증

**GitHub Actions에서 IAM 정책 검증**
```yaml
name: IAM Policy Validation

on:
  pull_request:
    paths:
      - 'iam/**'
      - 'terraform/iam/**'

jobs:
  validate:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      
      - name: Setup Terraform
        uses: hashicorp/setup-terraform@v2
        with:
          terraform_version: 1.5.0
      
      - name: Terraform Init
        run: |
          cd terraform
          terraform init
      
      - name: Terraform Plan
        run: |
          cd terraform
          terraform plan -out=tfplan
      
      - name: Analyze IAM Changes
        run: |
          cd terraform
          terraform show -json tfplan > tfplan.json
          python ../scripts/analyze_iam_changes.py
          
      - name: Check for High-Risk IAM Changes
        run: |
          if grep -q "HIGH_RISK" iam_analysis_results.txt; then
            echo "::error::High-risk IAM changes detected! Please review."
            exit 1
          fi
```

**IAM 정책 분석 스크립트 예시**
```python
#!/usr/bin/env python3
import json
import sys

# 고위험 작업 목록
HIGH_RISK_ACTIONS = [
    "iam:*",
    "organizations:*",
    "s3:*",
    "ec2:*",
    "lambda:*",
    "dynamodb:*",
    "kms:*"
]

# 특히 위험한 와일드카드 패턴
DANGEROUS_WILDCARDS = [
    "*:*",
    "iam:*",
    "s3:*",
    "ec2:*"
]

def analyze_plan(plan_file):
    with open(plan_file, 'r') as f:
        plan = json.load(f)
    
    if 'resource_changes' not in plan:
        return False
    
    high_risk_found = False
    
    for change in plan['resource_changes']:
        if 'change' not in change or 'actions' not in change['change']:
            continue
        
        resource_type = change.get('type', '')
        
        # IAM 관련 리소스 변경 검사
        if 'iam_' in resource_type or 'iam.' in resource_type:
            if 'create' in change['change']['actions'] or 'update' in change['change']['actions']:
                if 'after' in change['change']:
                    after = change['change']['after']
                    
                    # 정책 문서 검사
                    if 'policy' in after or 'policy_document' in after or 'inline_policy' in after:
                        policy_doc = after.get('policy', after.get('policy_document', after.get('inline_policy', {})))
                        
                        if type(policy_doc) is str:
                            try:
                                policy_doc = json.loads(policy_doc)
                            except:
                                print(f"Warning: Could not parse policy document for {resource_type}.{change.get('name', '')}")
                                continue
                        
                        # 고위험 정책 검사
                        if check_policy_for_high_risk(policy_doc):
                            high_risk_found = True
                            print(f"HIGH_RISK: {resource_type}.{change.get('name', '')} contains high-risk permissions")
    
    return high_risk_found

def check_policy_for_high_risk(policy):
    if not policy:
        return False
    
    # 정책 문 확인
    statements = policy.get('Statement', [])
    if isinstance(statements, dict):
        statements = [statements]
    
    for stmt in statements:
        effect = stmt.get('Effect', '')
        if effect.lower() != 'allow':
            continue
        
        actions = stmt.get('Action', [])
        if isinstance(actions, str):
            actions = [actions]
        
        # 리소스 확인
        resources = stmt.get('Resource', [])
        if isinstance(resources, str):
            resources = [resources]
        
        # 모든 리소스에 대한 권한인지 확인
        has_all_resources = '*' in resources
        
        # 고위험 작업 확인
        for action in actions:
            # 위험한 와일드카드 확인
            for dangerous_wildcard in DANGEROUS_WILDCARDS:
                if action == dangerous_wildcard and has_all_resources:
                    return True
            
            # 특정 고위험 작업 확인
            for high_risk_action in HIGH_RISK_ACTIONS:
                if action == high_risk_action or (high_risk_action.endswith('*') and action.startswith(high_risk_action[:-1])):
                    # 모든 리소스에 적용되는 경우 특히 위험
                    if has_all_resources:
                        return True
    
    return False

if __name__ == "__main__":
    plan_file = 'tfplan.json'
    result = analyze_plan(plan_file)
    
    with open('iam_analysis_results.txt', 'w') as f:
        if result:
            f.write("HIGH_RISK IAM changes detected.\n")
        else:
            f.write("No high-risk IAM changes detected.\n")
    
    sys.exit(0)
```

---

## 7. 실제 배포 시나리오 및 모범 사례

### 7.1 시나리오: 다중 환경 IAM 설계

다중 환경(개발, 테스트, 생산)을 위한 IAM 설계 패턴:

#### 7.1.1 환경 분리 전략

**AWS 계정 분리 모델**
```
Corporate AWS Organization
├── Management Account (조직 관리)
├── Security Account (중앙 감사 및 보안)
├── Shared Services Account (공통 서비스)
├── Development Account (개발 환경)
├── Testing Account (테스트/QA 환경)
└── Production Account (생산 환경)
```

**AWS 환경별 IAM 구성 예시**
```hcl
# 샌드박스/개발 환경 IAM 구성
module "sandbox_iam" {
  source = "./modules/environment_iam"
  
  environment = "sandbox"
  
  # 개발자에게 넓은 권한 부여
  developer_role_policies = [
    "arn:aws:iam::aws:policy/PowerUserAccess"
  ]
  
  # 리소스 생성 제한 없음
  enable_resource_constraints = false
  
  # 민감한 작업 허용
  allow_sensitive_actions = true
}

# 테스트 환경 IAM 구성
module "test_iam" {
  source = "./modules/environment_iam"
  
  environment = "test"
  
  # 개발자에게 제한된 권한 부여
  developer_role_policies = [
    "arn:aws:iam::aws:policy/ReadOnlyAccess",
    "arn:aws:iam::${var.aws_account_id}:policy/TestEnvironmentAccess"
  ]
  
  # 일부 리소스 제한
  enable_resource_constraints = true
  max_instance_size = "t3.medium"
  
  # 민감한 작업 제한
  allow_sensitive_actions = false
}

# 생산 환경 IAM 구성
module "prod_iam" {
  source = "./modules/environment_iam"
  
  environment = "production"
  
  # 개발자에게 매우 제한된 권한 부여
  developer_role_policies = [
    "arn:aws:iam::aws:policy/ReadOnlyAccess"
  ]
  
  # 엄격한 리소스 제한
  enable_resource_constraints = true
  max_instance_size = "t3.small"
  
  # 민감한 작업 금지
  allow_sensitive_actions = false
  
  # 변경 승인 워크플로우 필요
  require_change_approval = true
}
```

#### 7.1.2 환경 간 IAM 역할 체인

**AWS 크로스 계정 역할 체인**
```bash
# 첫 번째 역할 수임
initial_credentials=$(aws sts assume-role \
  --role-arn arn:aws:iam::DEV_ACCOUNT:role/DeveloperRole \
  --role-session-name InitialSession)

# 환경 변수 설정
export AWS_ACCESS_KEY_ID=$(echo $initial_credentials | jq -r '.Credentials.AccessKeyId')
export AWS_SECRET_ACCESS_KEY=$(echo $initial_credentials | jq -r '.Credentials.SecretAccessKey')
export AWS_SESSION_TOKEN=$(echo $initial_credentials | jq -r '.Credentials.SessionToken')

# 두 번째 역할 수임 (프로덕션 계정의 제한된 역할)
prod_credentials=$(aws sts assume-role \
  --role-arn arn:aws:iam::PROD_ACCOUNT:role/ReadOnlyRole \
  --role-session-name ProdSession)

# 새 환경 변수 설정
export AWS_ACCESS_KEY_ID=$(echo $prod_credentials | jq -r '.Credentials.AccessKeyId')
export AWS_SECRET_ACCESS_KEY=$(echo $prod_credentials | jq -r '.Credentials.SecretAccessKey')
export AWS_SESSION_TOKEN=$(echo $prod_credentials | jq -r '.Credentials.SessionToken')
```

**GCP 서비스 계정 임패션**
```bash
# 서비스 계정 임패션 권한 부여
gcloud iam service-accounts add-iam-policy-binding \
  --role="roles/iam.serviceAccountTokenCreator" \
  --member="user:developer@example.com" \
  dev-service-account@project-id.iam.gserviceaccount.com

# 서비스 계정으로 임시 토큰 생성
gcloud auth print-access-token \
  --impersonate-service-account=dev-service-account@project-id.iam.gserviceaccount.com
```

### 7.2 시나리오: CI/CD 파이프라인 IAM

CI/CD 파이프라인에 대한 안전한 IAM 구성:

#### 7.2.1 CI/CD 서비스 역할 모델

**AWS CodePipeline 역할 구성**
```json
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Effect": "Allow",
      "Action": [
        "s3:GetObject",
        "s3:GetObjectVersion",
        "s3:PutObject"
      ],
      "Resource": "arn:aws:s3:::codepipeline-artifact-bucket/*"
    },
    {
      "Effect": "Allow",
      "Action": [
        "codebuild:StartBuild",
        "codebuild:BatchGetBuilds"
      ],
      "Resource": "arn:aws:codebuild:region:account:project/build-project-name"
    },
    {
      "Effect": "Allow",
      "Action": [
        "cloudformation:CreateStack",
        "cloudformation:UpdateStack",
        "cloudformation:DescribeStacks",
        "cloudformation:DescribeStackEvents"
      ],
      "Resource": "arn:aws:cloudformation:region:account:stack/deployment-stack/*"
    }
  ]
}
```

**GitHub Actions OIDC 연동**
```yaml
name: Deploy to AWS

on:
  push:
    branches: [ main ]

permissions:
  id-token: write
  contents: read

jobs:
  deploy:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout repository
        uses: actions/checkout@v3
      
      - name: Configure AWS credentials
        uses: aws-actions/configure-aws-credentials@v2
        with:
          role-to-assume: arn:aws:iam::123456789012:role/GitHubActionsDeployRole
          aws-region: us-east-1
      
      - name: Deploy to AWS
        run: |
          # 스테이징 배포
          aws cloudformation deploy \
            --template-file infrastructure/staging.yaml \
            --stack-name my-app-staging \
            --parameter-overrides Environment=staging
      
      - name: Verify deployment
        run: |
          # 배포 검증
          aws cloudformation describe-stacks \
            --stack-name my-app-staging \
            --query "Stacks[0].Outputs"
      
      - name: Deploy to production
        if: success() && github.ref == 'refs/heads/main'
        run: |
          # 프로덕션 배포
          aws cloudformation deploy \
            --template-file infrastructure/production.yaml \
            --stack-name my-app-production \
            --parameter-overrides Environment=production
```

#### 7.2.2 단계별 권한 분리

CI/CD 파이프라인에서는 각 단계별로 필요한 최소한의 권한만 부여하는 것이 중요합니다.

**AWS SAM 배포 파이프라인**
```yaml
# template.yaml
AWSTemplateFormatVersion: '2010-09-09'
Transform: AWS::Serverless-2016-10-31
Description: CI/CD Pipeline with least privilege

Resources:
  # 빌드 단계 역할
  BuildRole:
    Type: AWS::IAM::Role
    Properties:
      AssumeRolePolicyDocument:
        Version: '2012-10-17'
        Statement:
          - Effect: Allow
            Principal:
              Service: codebuild.amazonaws.com
            Action: 'sts:AssumeRole'
      ManagedPolicyArns:
        - 'arn:aws:iam::aws:policy/AmazonS3ReadOnlyAccess'
      Policies:
        - PolicyName: BuildPermissions
          PolicyDocument:
            Version: '2012-10-17'
            Statement:
              - Effect: Allow
                Action:
                  - 'logs:CreateLogGroup'
                  - 'logs:CreateLogStream'
                  - 'logs:PutLogEvents'
                Resource: '*'
              - Effect: Allow
                Action:
                  - 's3:PutObject'
                Resource: !Sub 'arn:aws:s3:::${ArtifactBucket}/*'
  
  # 테스트 단계 역할
  TestRole:
    Type: AWS::IAM::Role
    Properties:
      AssumeRolePolicyDocument:
        Version: '2012-10-17'
        Statement:
          - Effect: Allow
            Principal:
              Service: codebuild.amazonaws.com
            Action: 'sts:AssumeRole'
      Policies:
        - PolicyName: TestPermissions
          PolicyDocument:
            Version: '2012-10-17'
            Statement:
              - Effect: Allow
                Action:
                  - 'logs:CreateLogGroup'
                  - 'logs:CreateLogStream'
                  - 'logs:PutLogEvents'
                Resource: '*'
              - Effect: Allow
                Action:
                  - 's3:GetObject'
                Resource: !Sub 'arn:aws:s3:::${ArtifactBucket}/*'
              - Effect: Allow
                Action:
                  - 'cloudformation:ValidateTemplate'
                Resource: '*'
  
  # 배포 단계 역할
  DeployRole:
    Type: AWS::IAM::Role
    Properties:
      AssumeRolePolicyDocument:
        Version: '2012-10-17'
        Statement:
          - Effect: Allow
            Principal:
              Service: cloudformation.amazonaws.com
            Action: 'sts:AssumeRole'
      ManagedPolicyArns:
        - 'arn:aws:iam::aws:policy/AWSCloudFormationFullAccess'
      Policies:
        - PolicyName: DeployPermissions
          PolicyDocument:
            Version: '2012-10-17'
            Statement:
              - Effect: Allow
                Action:
                  - 'lambda:*'
                  - 'apigateway:*'
                  - 's3:GetObject'
                  - 's3:GetObjectVersion'
                Resource: '*'
```

**Azure DevOps 단계별 서비스 연결**
```yaml
# azure-pipelines.yml
stages:
- stage: Build
  jobs:
  - job: BuildJob
    pool:
      vmImage: 'ubuntu-latest'
    steps:
    - task: NodeTool@0
      inputs:
        versionSpec: '14.x'
    - script: npm install && npm run build
    - task: PublishBuildArtifacts@1
      inputs:
        pathToPublish: 'dist'
        artifactName: 'drop'
    # 빌드 단계는 최소 권한으로 코드 빌드만 수행

- stage: Test
  dependsOn: Build
  jobs:
  - job: TestJob
    pool:
      vmImage: 'ubuntu-latest'
    steps:
    - task: DownloadBuildArtifacts@0
      inputs:
        buildType: 'current'
        artifactName: 'drop'
    - task: AzureCLI@2
      inputs:
        azureSubscription: 'TestEnvironmentConnection'  # 테스트 환경 전용 서비스 연결
        scriptType: 'bash'
        scriptLocation: 'inlineScript'
        inlineScript: |
          # 테스트 환경에 필요한 리소스 검증
          az group list --query "[?contains(name, 'test')]"
    # 테스트 단계는 테스트 환경 접근 권한만 가짐

- stage: Deploy
  dependsOn: Test
  jobs:
  - job: DeployJob
    pool:
      vmImage: 'ubuntu-latest'
    steps:
    - task: DownloadBuildArtifacts@0
      inputs:
        buildType: 'current'
        artifactName: 'drop'
    - task: AzureFunctionApp@1
      inputs:
        azureSubscription: 'ProductionDeployConnection'  # 배포 전용 서비스 연결
        appType: 'functionApp'
        appName: '$(functionAppName)'
        package: '$(System.ArtifactsDirectory)/drop'
    # 배포 단계는 프로덕션 배포 권한만 가짐
```

#### 7.2.3 CI/CD 보안 모범 사례

**1. 비밀 관리**
```bash
# AWS Secrets Manager에서 CI/CD 비밀 저장
aws secretsmanager create-secret \
  --name CI/DatabaseCredentials \
  --description "CI/CD 파이프라인용 데이터베이스 자격 증명" \
  --secret-string '{"username":"ci-user", "password":"[PASSWORD]"}'

# CI/CD 시스템에서의 비밀 사용
DB_CREDS=$(aws secretsmanager get-secret-value \
  --secret-id CI/DatabaseCredentials \
  --query SecretString \
  --output text)

DB_USER=$(echo $DB_CREDS | jq -r .username)
DB_PASS=$(echo $DB_CREDS | jq -r .password)
```

**2. 일시적 승격 권한**
```python
# 배포 중 일시적 권한 상승을 위한 Lambda 함수
import boto3
import os
import json
import time

def lambda_handler(event, context):
    # 승인자 확인
    approver_arn = event['userIdentity']['arn']
    allowed_approvers = os.environ['ALLOWED_APPROVERS'].split(',')
    
    if not any(approver in approver_arn for approver in allowed_approvers):
        return {
            'statusCode': 403,
            'body': json.dumps('Unauthorized approver')
        }
    
    # 파이프라인 서비스 역할 권한 일시적 확장
    iam = boto3.client('iam')
    
    # 정책 문서
    elevated_policy = {
        "Version": "2012-10-17",
        "Statement": [
            {
                "Effect": "Allow",
                "Action": [
                    "cloudformation:*Stack*",
                    "lambda:*Function*",
                    "apigateway:*"
                ],
                "Resource": "*",
                "Condition": {
                    "DateLessThan": {
                        "aws:CurrentTime": (time.time() + 3600) * 1000  # 1시간 후
                    }
                }
            }
        ]
    }
    
    # 임시 인라인 정책 추가
    response = iam.put_role_policy(
        RoleName='DeployPipelineServiceRole',
        PolicyName='TemporaryElevatedPermissions',
        PolicyDocument=json.dumps(elevated_policy)
    )
    
    # 승인 로그 기록
    cloudtrail = boto3.client('cloudtrail')
    cloudtrail.create_trail(
        Name='DeploymentApprovalTrail',
        S3BucketName='deployment-audit-logs'
    )
    
    return {
        'statusCode': 200,
        'body': json.dumps('Temporary permissions granted for 1 hour')
    }
```

**3. CI/CD 감사 로깅**
```yaml
# AWS CloudTrail 구성
Resources:
  DeploymentAuditTrail:
    Type: AWS::CloudTrail::Trail
    Properties:
      S3BucketName: !Ref AuditLogBucket
      IsLogging: true
      EventSelectors:
        - ReadWriteType: WriteOnly
          IncludeManagementEvents: true
          DataResources:
            - Type: AWS::S3::Object
              Values:
                - !Sub 'arn:aws:s3:::${ArtifactBucket}/'
            - Type: AWS::Lambda::Function
              Values:
                - !Sub 'arn:aws:lambda:${AWS::Region}:${AWS::AccountId}:function:*'
      IsMultiRegionTrail: true
      EnableLogFileValidation: true
```

### 7.3 시나리오: 마이크로서비스 아키텍처 IAM

마이크로서비스 환경에서의 IAM 구성:

#### 7.3.1 서비스 간 인증

**AWS IAM 역할 기반 인증**
```json
// 서비스 A의 역할 신뢰 정책
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Effect": "Allow",
      "Principal": {
        "Service": "lambda.amazonaws.com"
      },
      "Action": "sts:AssumeRole"
    }
  ]
}

// 서비스 A의 권한 정책
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Effect": "Allow",
      "Action": [
        "dynamodb:GetItem",
        "dynamodb:Query"
      ],
      "Resource": "arn:aws:dynamodb:region:account-id:table/ServiceA-Table"
    },
    {
      "Effect": "Allow",
      "Action": "sqs:SendMessage",
      "Resource": "arn:aws:sqs:region:account-id:ServiceB-Queue"
    }
  ]
}

// 서비스 B의 역할 신뢰 정책
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Effect": "Allow",
      "Principal": {
        "Service": "lambda.amazonaws.com"
      },
      "Action": "sts:AssumeRole"
    }
  ]
}

// 서비스 B의 권한 정책
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Effect": "Allow",
      "Action": [
        "sqs:ReceiveMessage",
        "sqs:DeleteMessage"
      ],
      "Resource": "arn:aws:sqs:region:account-id:ServiceB-Queue"
    },
    {
      "Effect": "Allow",
      "Action": [
        "dynamodb:PutItem",
        "dynamodb:UpdateItem"
      ],
      "Resource": "arn:aws:dynamodb:region:account-id:table/ServiceB-Table"
    }
  ]
}
```

**Kubernetes 서비스 계정 JWT 토큰 인증**
```yaml
# 서비스 A의 서비스 계정
apiVersion: v1
kind: ServiceAccount
metadata:
  name: service-a
  namespace: microservices
---
# 서비스 A의 역할
apiVersion: rbac.authorization.k8s.io/v1
kind: Role
metadata:
  name: service-a-role
  namespace: microservices
rules:
- apiGroups: [""]
  resources: ["configmaps", "secrets"]
  verbs: ["get", "list"]
---
# 서비스 A 역할 바인딩
apiVersion: rbac.authorization.k8s.io/v1
kind: RoleBinding
metadata:
  name: service-a-binding
  namespace: microservices
subjects:
- kind: ServiceAccount
  name: service-a
  namespace: microservices
roleRef:
  kind: Role
  name: service-a-role
  apiGroup: rbac.authorization.k8s.io
---
# 서비스 A의 디플로이먼트
apiVersion: apps/v1
kind: Deployment
metadata:
  name: service-a
  namespace: microservices
spec:
  replicas: 2
  selector:
    matchLabels:
      app: service-a
  template:
    metadata:
      labels:
        app: service-a
    spec:
      serviceAccountName: service-a
      containers:
      - name: service-a
        image: service-a:latest
        ports:
        - containerPort: 8080
```

**서비스 간 통신에서 JWT 사용**
```javascript
// 서비스 A에서 서비스 B에 요청
const axios = require('axios');
const fs = require('fs');

// Kubernetes 서비스 계정 토큰 읽기
const serviceAccountToken = fs.readFileSync('/var/run/secrets/kubernetes.io/serviceaccount/token', 'utf8');

async function callServiceB() {
  try {
    const response = await axios.get('http://service-b.microservices.svc.cluster.local/api/data', {
      headers: {
        'Authorization': `Bearer ${serviceAccountToken}`
      }
    });
    return response.data;
  } catch (error) {
    console.error('Service B 호출 실패:', error);
    throw error;
  }
}
```

#### 7.3.2 API 게이트웨이 인증/인가

**AWS API Gateway 권한 부여자**
```javascript
// Lambda 권한 부여자
exports.handler = async (event) => {
  console.log('Event:', JSON.stringify(event, null, 2));
  
  // 헤더에서 토큰 추출
  const authHeader = event.headers.Authorization || event.headers.authorization;
  if (!authHeader || !authHeader.startsWith('Bearer ')) {
    return generatePolicy('user', 'Deny', event.methodArn);
  }
  
  const token = authHeader.split(' ')[1];
  
  try {
    // 토큰 검증 (예: JWT 검증)
    const decodedToken = verifyToken(token);
    
    // 사용자 권한 확인
    const userScopes = decodedToken.scope.split(' ');
    
    // 요청한 리소스와 메서드에 대한 권한 확인
    const resource = event.resource;
    const method = event.httpMethod;
    
    if (hasPermission(userScopes, resource, method)) {
      // 권한 있음
      return generatePolicy(decodedToken.sub, 'Allow', event.methodArn, {
        'x-user-id': decodedToken.sub,
        'x-user-scopes': decodedToken.scope
      });
    } else {
      // 권한 없음
      return generatePolicy(decodedToken.sub, 'Deny', event.methodArn);
    }
  } catch (error) {
    console.error('Token verification failed:', error);
    return generatePolicy('user', 'Deny', event.methodArn);
  }
};

// 정책 생성 헬퍼 함수
function generatePolicy(principalId, effect, resource, context) {
  const authResponse = {
    principalId: principalId
  };
  
  if (effect && resource) {
    authResponse.policyDocument = {
      Version: '2012-10-17',
      Statement: [{
        Action: 'execute-api:Invoke',
        Effect: effect,
        Resource: resource
      }]
    };
  }
  
  if (context) {
    authResponse.context = context;
  }
  
  return authResponse;
}

// 토큰 검증 및 사용자 권한 확인 함수
function verifyToken(token) {
  // 실제 구현에서는 JWT 라이브러리 사용
  // ...
}

function hasPermission(scopes, resource, method) {
  // 스코프 기반 권한 검사 로직
  // ...
}
```

**Kong API Gateway 플러그인**
```yaml
# Kong API Gateway 구성
apiVersion: configuration.konghq.com/v1
kind: KongPlugin
metadata:
  name: jwt-auth
  namespace: microservices
plugin: jwt
config:
  secret_is_base64: false
  claims_to_verify:
  - exp
  - nbf
---
apiVersion: configuration.konghq.com/v1
kind: KongPlugin
metadata:
  name: acl
  namespace: microservices
plugin: acl
config:
  allow:
  - service-a-group
  - admin-group
  hide_groups_header: true
---
apiVersion: networking.k8s.io/v1
kind: Ingress
metadata:
  name: service-b-api
  namespace: microservices
  annotations:
    konghq.com/plugins: jwt-auth, acl
spec:
  ingressClassName: kong
  rules:
  - host: api.example.com
    http:
      paths:
      - path: /service-b
        pathType: Prefix
        backend:
          service:
            name: service-b
            port:
              number: 80
```

#### 7.3.3 서비스 메시(Service Mesh) 인증

**Istio 인증 정책**
```yaml
# 서비스 메시 인증 정책
apiVersion: security.istio.io/v1beta1
kind: PeerAuthentication
metadata:
  name: default
  namespace: microservices
spec:
  mtls:
    mode: STRICT
---
# 서비스별 인증 정책 (예외 적용)
apiVersion: security.istio.io/v1beta1
kind: PeerAuthentication
metadata:
  name: service-legacy
  namespace: microservices
spec:
  selector:
    matchLabels:
      app: service-legacy
  mtls:
    mode: PERMISSIVE
---
# 권한 부여 정책
apiVersion: security.istio.io/v1beta1
kind: AuthorizationPolicy
metadata:
  name: service-b-policy
  namespace: microservices
spec:
  selector:
    matchLabels:
      app: service-b
  rules:
  - from:
    - source:
        principals: ["cluster.local/ns/microservices/sa/service-a"]
    to:
    - operation:
        methods: ["GET"]
        paths: ["/api/data"]
  - from:
    - source:
        namespaces: ["monitoring"]
    to:
    - operation:
        methods: ["GET"]
        paths: ["/metrics"]
```

**Linkerd 정책**
```yaml
# Linkerd mTLS 적용
apiVersion: linkerd.io/v1alpha2
kind: ServiceProfile
metadata:
  name: service-b.microservices.svc.cluster.local
  namespace: microservices
spec:
  routes:
  - name: get-data
    condition:
      method: GET
      pathRegex: /api/data
    metrics:
      successRate: true
      latencyDistribution:
        successRate: true
  - name: health
    condition:
      method: GET
      pathRegex: /health
    isRetryable: true
---
# Linkerd 권한 부여 정책 (Server 측)
apiVersion: policy.linkerd.io/v1beta1
kind: Server
metadata:
  name: service-b
  namespace: microservices
spec:
  podSelector:
    matchLabels:
      app: service-b
  port: 8080
  proxyProtocol: HTTP/1
---
# Linkerd 권한 부여 정책 (ServerAuthorization 측)
apiVersion: policy.linkerd.io/v1beta1
kind: ServerAuthorization
metadata:
  name: service-b-auth
  namespace: microservices
spec:
  server:
    name: service-b
    namespace: microservices
  client:
    # service-a만 접근 가능
    meshTLS:
      serviceAccounts:
        - name: service-a
          namespace: microservices
        - name: prometheus
          namespace: monitoring
```

### 7.4 시나리오: 멀티클라우드 IAM 전략

여러 클라우드 제공업체에 걸친 일관된 IAM 관리:

#### 7.4.1 중앙 집중식 ID 관리

**Azure AD(Entra ID)를 통한 통합 인증**
```json
// Azure AD 애플리케이션 설정
{
  "appId": "11111111-1111-1111-1111-111111111111",
  "displayName": "Multi-Cloud Federation",
  "identifierUris": [
    "https://federation.example.com"
  ],
  "sign-in audience": "AzureADMyOrg",
  "web": {
    "redirectUris": [
      "https://aws-console.example.com/saml",
      "https://console.cloud.google.com/_oauth"
    ]
  }
}
```

**AWS IAM SAML 통합**
```json
// AWS IAM SAML 제공자
{
  "Version": "2012-10-17",
  "Statement": [{
    "Effect": "Allow",
    "Principal": {"Federated": "arn:aws:iam::123456789012:saml-provider/AzureAD"},
    "Action": "sts:AssumeRoleWithSAML",
    "Condition": {
      "StringEquals": {
        "SAML:aud": "https://signin.aws.amazon.com/saml"
      }
    }
  }]
}

// AWS IAM 역할 매핑
{
  "Version": "2012-10-17",
  "Statement": [{
    "Effect": "Allow",
    "Principal": {"Federated": "arn:aws:iam::123456789012:saml-provider/AzureAD"},
    "Action": "sts:AssumeRoleWithSAML",
    "Condition": {
      "StringEquals": {
        "SAML:aud": "https://signin.aws.amazon.com/saml"
      },
      "ForAnyValue:StringLike": {
        "SAML:groups": "AWS-Administrators"
      }
    }
  }]
}
```

**GCP Workforce Identity Federation**
```yaml
# GCP Workforce Identity Pool 생성
gcloud iam workforce-pools create azure-federation \
  --location=global \
  --display-name="Azure AD Federation"

# Azure AD 제공자 구성
gcloud iam workforce-pools providers create-saml azure-ad \
  --workforce-pool=azure-federation \
  --location=global \
  --display-name="Azure AD" \
  --idp-metadata-path=azure-ad-metadata.xml \
  --attribute-mapping="google.subject=assertion.sub,google.groups=assertion.groups"

# 관리자 액세스 구성
cat > azure-admin-binding.yaml << EOF
principalSet: "principalSet://iam.googleapis.com/locations/global/workforcePools/azure-federation/attribute.groups/AWS-Administrators"
role: roles/editor
EOF

gcloud projects add-iam-policy-binding my-project \
  --member="principalSet://iam.googleapis.com/locations/global/workforcePools/azure-federation/attribute.groups/GCP-Administrators" \
  --role="roles/editor"
```

#### 7.4.2 통합 권한 관리

**Terraform을 통한 멀티클라우드 IAM 관리**
```hcl
# AWS 제공자 구성
provider "aws" {
  region = "us-east-1"
}

# GCP 제공자 구성
provider "google" {
  project = "my-gcp-project"
  region  = "us-central1"
}

# Azure 제공자 구성
provider "azurerm" {
  features {}
}

# 공통 로컬 변수
locals {
  # 공통 태그
  common_tags = {
    Environment = var.environment
    ManagedBy   = "Terraform"
    Owner       = "InfraTeam"
  }
  
  # 환경별 접근 매핑
  env_access = {
    dev = {
      aws_policies = ["ReadOnlyAccess", "AmazonS3FullAccess"]
      gcp_roles    = ["roles/viewer", "roles/storage.admin"]
      azure_roles  = ["Reader", "Storage Blob Data Owner"]
    }
    prod = {
      aws_policies = ["ReadOnlyAccess"]
      gcp_roles    = ["roles/viewer"]
      azure_roles  = ["Reader"]
    }
  }
  
  # 팀 구성
  team_members = {
    infrastructure = ["user1@example.com", "user2@example.com"]
    developers     = ["dev1@example.com", "dev2@example.com"]
    security       = ["sec1@example.com"]
  }
}

# AWS IAM 그룹 및 정책
resource "aws_iam_group" "teams" {
  for_each = local.team_members
  name     = each.key
}

resource "aws_iam_group_policy_attachment" "team_policies" {
  for_each   = { for idx, team in keys(local.team_members) : idx => team }
  group      = aws_iam_group.teams[each.value].name
  policy_arn = contains(keys(local.team_members), "infrastructure") ? "arn:aws:iam::aws:policy/AdministratorAccess" : "arn:aws:iam::aws:policy/ReadOnlyAccess"
}

# GCP IAM 바인딩
resource "google_project_iam_binding" "team_bindings" {
  for_each = local.team_members
  project  = var.gcp_project_id
  role     = each.key == "infrastructure" ? "roles/owner" : "roles/viewer"
  
  members = [for user in each.value : "user:${user}"]
}

# Azure RBAC 할당
resource "azurerm_role_assignment" "team_assignments" {
  for_each = { for idx, user in flatten([for team, users in local.team_members : [for u in users : { team = team, email = u }]]) : idx => user }
  
  scope                = azurerm_resource_group.main.id
  role_definition_name = each.value.team == "infrastructure" ? "Owner" : "Reader"
  principal_id         = data.azuread_user.users[each.value.email].id
}
```
#### 7.4.3 크로스 클라우드 정책 시행

다양한 클라우드 환경에 걸쳐 일관된 보안 정책을 시행하는 것은 멀티클라우드 전략의 핵심입니다.

**멀티클라우드 권한 감사 스크립트**
```python
# 멀티클라우드 권한 감사 스크립트
import boto3
import google.auth
import google.auth.transport.requests
from google.cloud import resourcemanager_v3
from azure.identity import DefaultAzureCredential
from azure.mgmt.authorization import AuthorizationManagementClient
import csv
import datetime

def audit_cross_cloud_permissions():
    # 결과 저장 파일
    output_file = f"cross_cloud_audit_{datetime.datetime.now().strftime('%Y%m%d')}.csv"
    
    # CSV 헤더
    headers = ['Cloud', 'Resource', 'Principal', 'Permission', 'Allowed', 'Risk Level']
    
    with open(output_file, 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(headers)
        
        # AWS IAM 권한 감사
        aws_results = audit_aws_permissions()
        writer.writerows(aws_results)
        
        # GCP IAM 권한 감사
        gcp_results = audit_gcp_permissions()
        writer.writerows(gcp_results)
        
        # Azure RBAC 권한 감사
        azure_results = audit_azure_permissions()
        writer.writerows(azure_results)
    
    print(f"감사가 완료되었습니다. 결과가 {output_file}에 저장되었습니다.")

def audit_aws_permissions():
    results = []
    session = boto3.Session()
    iam = session.client('iam')
    
    # 사용자 권한 검사
    users = iam.list_users()['Users']
    for user in users:
        username = user['UserName']
        
        # 인라인 정책 검사
        inline_policies = iam.list_user_policies(UserName=username)['PolicyNames']
        for policy_name in inline_policies:
            policy = iam.get_user_policy(UserName=username, PolicyName=policy_name)
            analyze_aws_policy(results, 'User', username, policy['PolicyDocument'])
        
        # 관리형 정책 검사
        attached_policies = iam.list_attached_user_policies(UserName=username)['AttachedPolicies']
        for policy in attached_policies:
            policy_arn = policy['PolicyArn']
            policy_version = iam.get_policy(PolicyArn=policy_arn)['Policy']['DefaultVersionId']
            policy_doc = iam.get_policy_version(PolicyArn=policy_arn, VersionId=policy_version)
            analyze_aws_policy(results, 'User', username, policy_doc['PolicyVersion']['Document'])
    
    # 역할 권한 검사
    roles = iam.list_roles()['Roles']
    for role in roles:
        role_name = role['RoleName']
        analyze_aws_policy(results, 'Role', role_name, role['AssumeRolePolicyDocument'])
        
        # 역할에 연결된 정책 검사
        attached_policies = iam.list_attached_role_policies(RoleName=role_name)['AttachedPolicies']
        for policy in attached_policies:
            policy_arn = policy['PolicyArn']
            policy_version = iam.get_policy(PolicyArn=policy_arn)['Policy']['DefaultVersionId']
            policy_doc = iam.get_policy_version(PolicyArn=policy_arn, VersionId=policy_version)
            analyze_aws_policy(results, 'Role', role_name, policy_doc['PolicyVersion']['Document'])
    
    return results

def analyze_aws_policy(results, principal_type, principal_name, policy_document):
    high_risk_actions = [
        "iam:*", "organizations:*", "kms:*", "s3:*", "ec2:*", 
        "rds:*", "lambda:*", "dynamodb:*"
    ]
    
    for statement in policy_document.get('Statement', []):
        effect = statement.get('Effect', '')
        actions = statement.get('Action', [])
        
        if isinstance(actions, str):
            actions = [actions]
        
        for action in actions:
            risk_level = 'Low'
            
            # 고위험 작업 검사
            if any(action.startswith(high_risk.replace('*', '')) for high_risk in high_risk_actions):
                risk_level = 'High'
            
            # 모든 리소스에 대한 권한인지 확인
            resources = statement.get('Resource', [])
            if isinstance(resources, str):
                resources = [resources]
            
            if '*' in resources:
                risk_level = 'High'
            
            results.append([
                'AWS',
                ', '.join(resources),
                f"{principal_type}: {principal_name}",
                action,
                effect,
                risk_level
            ])

def audit_gcp_permissions():
    results = []
    credentials, project = google.auth.default()
    client = resourcemanager_v3.ProjectsClient()
    
    # 프로젝트 IAM 정책 가져오기
    request = resourcemanager_v3.GetIamPolicyRequest(
        resource=f"projects/{project}"
    )
    policy = client.get_iam_policy(request=request)
    
    high_risk_roles = [
        "roles/owner", "roles/editor", "roles/iam.", "roles/securityadmin",
        "roles/storage.", "roles/compute.", "roles/container."
    ]
    
    for binding in policy.bindings:
        role = binding.role
        risk_level = 'Low'
        
        # 고위험 역할 검사
        if any(role.startswith(high_risk.replace('.', '')) for high_risk in high_risk_roles):
            risk_level = 'High'
        
        for member in binding.members:
            results.append([
                'GCP',
                project,
                member,
                role,
                'Allow',
                risk_level
            ])
    
    return results

def audit_azure_permissions():
    results = []
    credential = DefaultAzureCredential()
    
    # 구독 ID 목록
    subscription_ids = []  # 여기에 감사할 구독 ID 목록 추가
    
    for subscription_id in subscription_ids:
        authorization_client = AuthorizationManagementClient(credential, subscription_id)
        
        # 역할 할당 가져오기
        role_assignments = authorization_client.role_assignments.list_for_subscription()
        
        for assignment in role_assignments:
            # 역할 정의 가져오기
            role_definition = authorization_client.role_definitions.get_by_id(assignment.role_definition_id)
            
            risk_level = 'Low'
            role_name = role_definition.role_name
            
            # 고위험 역할 검사
            high_risk_roles = ['Owner', 'Contributor', 'User Access Administrator']
            if role_name in high_risk_roles:
                risk_level = 'High'
            
            results.append([
                'Azure',
                assignment.scope,
                assignment.principal_id,
                role_name,
                'Allow',
                risk_level
            ])
    
    return results

if __name__ == "__main__":
    audit_cross_cloud_permissions()
```

**중앙 집중식 정책 시행 시스템**

멀티클라우드 환경에서 일관된 정책을 시행하기 위해서는 중앙 집중식 정책 시행 시스템을 구축하는 것이 효과적입니다. 다음은 HashiCorp Terraform Cloud와 AWS Organizations, Azure Policy, GCP Organization Policy를 통합하는 접근 방식입니다.

```hcl
# main.tf - 중앙 집중식 정책 관리 시스템

# AWS 조직 정책 설정
module "aws_organization_policies" {
  source = "./modules/aws_policies"
  
  org_id            = var.aws_org_id
  enable_scp        = true
  enforce_mfa       = true
  restrict_regions  = true
  allowed_regions   = ["us-east-1", "eu-west-1", "ap-northeast-2"]
  
  # 공통 보안 정책
  common_policies = {
    prevent_public_access = true
    enforce_encryption    = true
    restrict_root_access  = true
    log_all_actions       = true
  }
}

# GCP 조직 정책 설정
module "gcp_organization_policies" {
  source = "./modules/gcp_policies"
  
  org_id            = var.gcp_org_id
  enforce_security  = true
  
  # 허용된 리소스 위치
  allowed_locations = [
    "us-central1", "europe-west1", "asia-northeast3"
  ]
  
  # 공통 제약 조건
  constraints = {
    "constraints/compute.disableSerialPortAccess"     = true
    "constraints/compute.requireOsLogin"              = true
    "constraints/compute.restrictSharedVpcHostProjects" = true
    "constraints/compute.vmExternalIpAccess"          = true
    "constraints/iam.disableServiceAccountKeyCreation" = true
    "constraints/storage.uniformBucketLevelAccess"    = true
  }
}

# Azure 정책 설정
module "azure_policies" {
  source = "./modules/azure_policies"
  
  management_group_id = var.azure_mg_id
  
  # Azure 정책 이니셔티브 정의
  policy_set_definitions = [
    {
      name         = "security-baseline"
      display_name = "Security Baseline"
      description  = "Security baseline for all resources"
      policy_ids   = [
        "/providers/Microsoft.Authorization/policyDefinitions/2a0e14a6-b0a6-4fab-991a-187a9097f5b4", # 보안 로깅 활성화
        "/providers/Microsoft.Authorization/policyDefinitions/1f314764-cb73-4fc9-b863-8eca98ac36e9", # 디스크 암호화 필요
        "/providers/Microsoft.Authorization/policyDefinitions/013e242c-8828-4970-87b3-ab247555486d"  # 웹앱 HTTPS 요구
      ]
    }
  ]
  
  # 허용된 위치 정책
  allowed_locations = [
    "koreacentral", 
    "westeurope", 
    "eastus"
  ]
}

# 중앙 집중식 감사 및 모니터링
module "centralized_audit" {
  source = "./modules/audit"
  
  aws_accounts      = var.aws_accounts
  gcp_projects      = var.gcp_projects
  azure_subscriptions = var.azure_subscriptions
  
  # 중앙 로깅 설정
  log_destination = {
    type    = "s3"  # 또는 "gcs", "azure_storage" 등
    bucket  = "centralized-audit-logs"
    region  = "us-east-1"
    encryption_key = var.kms_key_arn
  }
  
  # 알림 설정
  alerts = {
    email_recipients   = ["security@example.com"]
    webhook_endpoints  = ["https://alert-handler.example.com/webhook"]
    severity_threshold = "medium"
  }
}
```

**권한 요청 및 승인 워크플로우**

멀티클라우드 환경에서 권한을 일관되게 관리하기 위한 권한 요청 및 승인 워크플로우 시스템:

```python
# access_request_handler.py - AWS Lambda 함수
import boto3
import json
import os
import requests
from datetime import datetime, timedelta

def lambda_handler(event, context):
    # API Gateway를 통해 전달된 이벤트
    request_body = json.loads(event['body'])
    
    # 요청 정보 파싱
    requester = request_body.get('requester')
    cloud_provider = request_body.get('cloud_provider')
    resource_type = request_body.get('resource_type')
    resource_id = request_body.get('resource_id')
    permissions = request_body.get('permissions')
    justification = request_body.get('justification')
    duration = request_body.get('duration', 24)  # 기본값: 24시간
    
    # 요청 ID 생성
    request_id = f"access-{datetime.now().strftime('%Y%m%d%H%M%S')}-{requester.split('@')[0]}"
    
    # 요청 저장
    dynamodb = boto3.resource('dynamodb')
    table = dynamodb.Table(os.environ['ACCESS_REQUESTS_TABLE'])
    
    expires_at = (datetime.now() + timedelta(hours=duration)).isoformat()
    
    item = {
        'RequestId': request_id,
        'Requester': requester,
        'CloudProvider': cloud_provider,
        'ResourceType': resource_type,
        'ResourceId': resource_id,
        'Permissions': permissions,
        'Justification': justification,
        'Status': 'PENDING',
        'RequestedAt': datetime.now().isoformat(),
        'ExpiresAt': expires_at,
        'ApprovedBy': None,
        'ApprovedAt': None
    }
    
    table.put_item(Item=item)
    
    # 승인자에게 알림 전송
    send_approval_notification(request_id, requester, cloud_provider, resource_type, permissions, justification)
    
    return {
        'statusCode': 200,
        'body': json.dumps({
            'message': '권한 요청이 제출되었습니다',
            'requestId': request_id
        })
    }

def send_approval_notification(request_id, requester, cloud, resource_type, permissions, justification):
    # 슬랙 또는 이메일로 알림 전송
    if os.environ.get('SLACK_WEBHOOK_URL'):
        slack_message = {
            'blocks': [
                {
                    'type': 'section',
                    'text': {
                        'type': 'mrkdwn',
                        'text': f'*새로운 권한 요청이 접수되었습니다*\nRequest ID: {request_id}'
                    }
                },
                {
                    'type': 'section',
                    'fields': [
                        {'type': 'mrkdwn', 'text': f'*요청자:*\n{requester}'},
                        {'type': 'mrkdwn', 'text': f'*클라우드:*\n{cloud}'},
                        {'type': 'mrkdwn', 'text': f'*리소스 유형:*\n{resource_type}'},
                        {'type': 'mrkdwn', 'text': f'*권한:*\n{", ".join(permissions)}'}
                    ]
                },
                {
                    'type': 'section',
                    'text': {
                        'type': 'mrkdwn',
                        'text': f'*요청 사유:*\n{justification}'
                    }
                },
                {
                    'type': 'actions',
                    'elements': [
                        {
                            'type': 'button',
                            'text': {'type': 'plain_text', 'text': '승인'},
                            'style': 'primary',
                            'url': f'https://access-portal.example.com/approve?id={request_id}'
                        },
                        {
                            'type': 'button',
                            'text': {'type': 'plain_text', 'text': '거부'},
                            'style': 'danger',
                            'url': f'https://access-portal.example.com/deny?id={request_id}'
                        }
                    ]
                }
            ]
        }
        
        requests.post(os.environ['SLACK_WEBHOOK_URL'], json=slack_message)
```

**AWS Lambda를 통한, 승인 시 클라우드별 권한 부여**

```python
# access_approval_handler.py - AWS Lambda 함수
import boto3
import json
import os
import google.auth
from google.auth.transport.requests import AuthorizedSession
from google.cloud import resourcemanager_v3
from azure.identity import DefaultAzureCredential
from azure.mgmt.authorization import AuthorizationManagementClient
from azure.mgmt.authorization.models import RoleAssignmentCreateParameters
from datetime import datetime

def lambda_handler(event, context):
    # API Gateway를 통해 전달된 이벤트
    request_body = json.loads(event['body'])
    
    request_id = request_body.get('request_id')
    approver = request_body.get('approver')
    action = request_body.get('action')  # 'approve' 또는 'deny'
    
    # 요청 정보 가져오기
    dynamodb = boto3.resource('dynamodb')
    table = dynamodb.Table(os.environ['ACCESS_REQUESTS_TABLE'])
    
    response = table.get_item(Key={'RequestId': request_id})
    if 'Item' not in response:
        return {
            'statusCode': 404,
            'body': json.dumps({'message': '요청을 찾을 수 없습니다'})
        }
    
    request_item = response['Item']
    
    # 이미 처리된 요청인지 확인
    if request_item['Status'] != 'PENDING':
        return {
            'statusCode': 400,
            'body': json.dumps({'message': f"이 요청은 이미 {request_item['Status']} 상태입니다"})
        }
    
    if action == 'deny':
        # 요청 거부 처리
        update_request_status(table, request_id, 'DENIED', approver)
        notify_requester(request_item['Requester'], request_id, 'DENIED', approver)
        
        return {
            'statusCode': 200,
            'body': json.dumps({'message': '요청이 거부되었습니다'})
        }
    
    elif action == 'approve':
        # 클라우드별 권한 부여
        cloud_provider = request_item['CloudProvider']
        
        try:
            if cloud_provider == 'AWS':
                grant_aws_permissions(request_item)
            elif cloud_provider == 'GCP':
                grant_gcp_permissions(request_item)
            elif cloud_provider == 'Azure':
                grant_azure_permissions(request_item)
            else:
                return {
                    'statusCode': 400,
                    'body': json.dumps({'message': f"지원되지 않는 클라우드 제공자: {cloud_provider}"})
                }
            
            # 요청 승인 처리
            update_request_status(table, request_id, 'APPROVED', approver)
            notify_requester(request_item['Requester'], request_id, 'APPROVED', approver)
            
            return {
                'statusCode': 200,
                'body': json.dumps({'message': '요청이 승인되고 권한이 부여되었습니다'})
            }
        
        except Exception as e:
            # 권한 부여 실패
            update_request_status(table, request_id, 'FAILED', approver, str(e))
            notify_requester(request_item['Requester'], request_id, 'FAILED', approver, str(e))
            
            return {
                'statusCode': 500,
                'body': json.dumps({'message': f"권한 부여 실패: {str(e)}"})
            }
    
    else:
        return {
            'statusCode': 400,
            'body': json.dumps({'message': '잘못된 작업입니다. "approve" 또는 "deny"를 지정하세요.'})
        }

def update_request_status(table, request_id, status, approver, reason=None):
    update_expression = "SET #status = :status, ApprovedBy = :approver, ApprovedAt = :time"
    expression_attrs = {
        '#status': 'Status'
    }
    expression_values = {
        ':status': status,
        ':approver': approver,
        ':time': datetime.now().isoformat()
    }
    
    if reason:
        update_expression += ", FailureReason = :reason"
        expression_values[':reason'] = reason
    
    table.update_item(
        Key={'RequestId': request_id},
        UpdateExpression=update_expression,
        ExpressionAttributeNames=expression_attrs,
        ExpressionAttributeValues=expression_values
    )

def grant_aws_permissions(request_item):
    # AWS 권한 부여 로직
    iam = boto3.client('iam')
    
    resource_type = request_item['ResourceType']
    resource_id = request_item['ResourceId']
    permissions = request_item['Permissions']
    expires_at = request_item['ExpiresAt']
    
    if resource_type == 'role':
        # 기존 역할에 인라인 정책 추가
        policy_name = f"TempAccess-{request_item['RequestId']}"
        
        policy_document = {
            "Version": "2012-10-17",
            "Statement": [
                {
                    "Effect": "Allow",
                    "Action": permissions,
                    "Resource": "*",
                    "Condition": {
                        "DateLessThan": {
                            "aws:CurrentTime": expires_at
                        }
                    }
                }
            ]
        }
        
        iam.put_role_policy(
            RoleName=resource_id,
            PolicyName=policy_name,
            PolicyDocument=json.dumps(policy_document)
        )
    
    elif resource_type == 'user':
        # 사용자에게 인라인 정책 추가
        policy_name = f"TempAccess-{request_item['RequestId']}"
        
        policy_document = {
            "Version": "2012-10-17",
            "Statement": [
                {
                    "Effect": "Allow",
                    "Action": permissions,
                    "Resource": "*",
                    "Condition": {
                        "DateLessThan": {
                            "aws:CurrentTime": expires_at
                        }
                    }
                }
            ]
        }
        
        iam.put_user_policy(
            UserName=resource_id,
            PolicyName=policy_name,
            PolicyDocument=json.dumps(policy_document)
        )

def grant_gcp_permissions(request_item):
    # GCP 권한 부여 로직
    credentials, project = google.auth.default()
    authed_session = AuthorizedSession(credentials)
    
    resource_type = request_item['ResourceType']
    resource_id = request_item['ResourceId']
    member = request_item['Requester']
    roles = request_item['Permissions']
    
    # 프로젝트 IAM 정책 가져오기
    client = resourcemanager_v3.ProjectsClient()
    request = resourcemanager_v3.GetIamPolicyRequest(
        resource=f"projects/{resource_id}"
    )
    policy = client.get_iam_policy(request=request)
    
    # 각 역할에 대해 바인딩 추가
    for role in roles:
        # 기존 바인딩 확인
        found = False
        for binding in policy.bindings:
            if binding.role == role:
                binding.members.append(f"user:{member}")
                found = True
                break
        
        # 바인딩이 없으면 새로 추가
        if not found:
            new_binding = policy.bindings.add()
            new_binding.role = role
            new_binding.members.append(f"user:{member}")
    
    # 정책 업데이트
    set_request = resourcemanager_v3.SetIamPolicyRequest(
        resource=f"projects/{resource_id}",
        policy=policy
    )
    client.set_iam_policy(request=set_request)

def grant_azure_permissions(request_item):
    # Azure 권한 부여 로직
    credential = DefaultAzureCredential()
    
    resource_type = request_item['ResourceType']
    resource_id = request_item['ResourceId']
    principal_id = request_item['Requester']
    role_definition_id = request_item['Permissions'][0]  # Azure는 단일 역할 정의 ID 사용
    
    # 구독 ID 추출 (리소스 ID 형식: /subscriptions/{subscription-id}/...)
    subscription_id = resource_id.split('/')[2]
    
    # 권한 부여 클라이언트 생성
    auth_client = AuthorizationManagementClient(credential, subscription_id)
    
    # 역할 할당 생성
    role_assignment_name = f"{principal_id}-{role_definition_id}"
    
    role_assignment_params = RoleAssignmentCreateParameters(
        role_definition_id=role_definition_id,
        principal_id=principal_id
    )
    
    auth_client.role_assignments.create(
        scope=resource_id,
        role_assignment_name=role_assignment_name,
        parameters=role_assignment_params
    )

def notify_requester(requester_email, request_id, status, approver, reason=None):
    # 이메일 또는 슬랙으로 요청자에게 알림
    # 구현은 필요에 따라 추가
    pass
```

### 7.5 시나리오: 클라우드 DevSecOps 파이프라인 IAM

DevSecOps 파이프라인에서 IAM 보안을 자동화하는 방법:

#### 7.5.1 IaC 코드 스캐닝

**Terraform 코드 보안 스캐닝**
```yaml
# GitHub Actions 워크플로우 - IAM 코드 검사
name: IaC Security Scan

on:
  pull_request:
    paths:
      - '**/*.tf'
      - '**/*.tfvars'

jobs:
  tfsec:
    name: TFSec 스캔
    runs-on: ubuntu-latest
    
    steps:
      - name: 코드 체크아웃
        uses: actions/checkout@v3
      
      - name: tfsec 실행
        uses: aquasecurity/tfsec-action@v1.0.0
        with:
          soft_fail: false
          format: sarif
          github_token: ${{ secrets.GITHUB_TOKEN }}
      
  iam-validator:
    name: IAM 정책 검증
    runs-on: ubuntu-latest
    
    steps:
      - name: 코드 체크아웃
        uses: actions/checkout@v3
      
      - name: Terraform 초기화
        uses: hashicorp/setup-terraform@v2
        with:
          terraform_version: 1.5.0
      
      - name: Terraform 플랜 생성
        run: |
          cd terraform
          terraform init -backend=false
          terraform plan -out=tfplan.binary
          terraform show -json tfplan.binary > tfplan.json
      
      - name: IAM 정책 분석
        uses: aws-actions/evaluate-iam-policies@v1
        with:
          tfplan_file: terraform/tfplan.json
          github_token: ${{ secrets.GITHUB_TOKEN }}
      
      - name: 고위험 권한 확인
        run: |
          cd terraform
          python ../scripts/check_high_risk_permissions.py
          if [ $? -ne 0 ]; then
            echo "::error::고위험 IAM 권한이 감지되었습니다!"
            exit 1
          fi
```

**IAM 정책 분석 스크립트**
```python
#!/usr/bin/env python3
# check_high_risk_permissions.py

import json
import sys
import re
from datetime import datetime
import os
import csv

def load_plan(plan_file):
    """Terraform 계획 파일을 로드합니다."""
    try:
        with open(plan_file, 'r') as f:
            return json.load(f)
    except (FileNotFoundError, json.JSONDecodeError) as e:
        print(f"오류: Terraform 계획 파일을 로드할 수 없습니다 - {e}")
        sys.exit(1)

def check_high_risk_permissions(plan):
    """Terraform 계획에서 고위험 IAM 권한을 식별합니다."""
    # 고위험 패턴 정의
    high_risk_patterns = [
        r"iam:.*Admin",           # 관리자 IAM 권한
        r"iam:\*",                # 모든 IAM 권한
        r"s3:\*",                 # 모든 S3 권한
        r"ec2:\*",                # 모든 EC2 권한
        r"kms:\*",                # 모든 KMS 권한
        r"dynamodb:\*",           # 모든 DynamoDB 권한
        r"lambda:\*",             # 모든 Lambda 권한
        r"cloudformation:\*",     # 모든 CloudFormation 권한
        r".*:DeleteAccount",      # 계정 삭제 권한
        r".*:FullAccess",         # 모든 풀 액세스 권한
        r"\*:\*"                  # 모든 권한
    ]
    
    high_risk_findings = []
    resource_changes = plan.get('resource_changes', [])
    
    for change in resource_changes:
        # IAM 관련 리소스만 확인
        if any(change.get('type', '').startswith(prefix) for prefix in ['aws_iam_', 'google_iam_', 'azurerm_role_']):
            resource_name = f"{change.get('type')}.{change.get('name')}"
            actions = []
            
            # 변경 사항 가져오기 (생성 또는 업데이트)
            if 'after' in change.get('change', {}):
                after = change['change']['after']
                
                # AWS IAM 정책 분석
                if 'policy' in after:
                    try:
                        # 문자열로 된 정책을 파싱
                        if isinstance(after['policy'], str):
                            policy = json.loads(after['policy'])
                        else:
                            policy = after['policy']
                        
                        statements = policy.get('Statement', [])
                        
                        # 단일 Statement 객체인 경우 리스트로 변환
                        if isinstance(statements, dict):
                            statements = [statements]
                        
                        for stmt in statements:
                            if stmt.get('Effect') == 'Allow':
                                stmt_actions = stmt.get('Action', [])
                                if isinstance(stmt_actions, str):
                                    stmt_actions = [stmt_actions]
                                
                                resources = stmt.get('Resource', '*')
                                if isinstance(resources, str):
                                    resources = [resources]
                                
                                # 와일드카드 리소스에 대한 권한은 더 위험함
                                has_wildcard_resource = '*' in resources or any('*' in r for r in resources)
                                
                                for action in stmt_actions:
                                    # 고위험 패턴 확인
                                    risk_level = "Medium"
                                    matched_pattern = None
                                    
                                    for pattern in high_risk_patterns:
                                        if re.match(pattern, action):
                                            risk_level = "High"
                                            matched_pattern = pattern
                                            break
                                    
                                    # 와일드카드 리소스가 있으면 위험도 상승
                                    if has_wildcard_resource and risk_level == "Medium":
                                        risk_level = "High"
                                    
                                    finding = {
                                        "resource": resource_name,
                                        "action": action,
                                        "risk_level": risk_level,
                                        "pattern": matched_pattern,
                                        "resource_pattern": "Wildcard" if has_wildcard_resource else "Specific"
                                    }
                                    
                                    high_risk_findings.append(finding)
                    except (json.JSONDecodeError, TypeError) as e:
                        print(f"경고: {resource_name}의 정책을 파싱할 수 없습니다 - {e}")
                
                # GCP IAM 역할 분석
                elif 'role' in after and isinstance(after.get('role'), str):
                    role = after.get('role')
                    if role.startswith('roles/'):
                        high_risk_gcp_roles = [
                            'roles/owner', 'roles/editor', 'roles/admin',
                            'roles/iam.', 'roles/storage.admin', 'roles/compute.admin'
                        ]
                        
                        for risk_role in high_risk_gcp_roles:
                            if role.startswith(risk_role):
                                finding = {
                                    "resource": resource_name,
                                    "action": role,
                                    "risk_level": "High",
                                    "pattern": risk_role,
                                    "resource_pattern": "GCP Role"
                                }
                                high_risk_findings.append(finding)
                
                # Azure 역할 정의 분석
                elif change.get('type') == 'azurerm_role_assignment':
                    role_definition_id = after.get('role_definition_id', '')
                    role_definition_name = after.get('role_definition_name', '')
                    
                    high_risk_azure_roles = [
                        'Owner', 'Contributor', 'Administrator', 'Admin',
                        '/providers/Microsoft.Authorization/roleDefinitions/'
                    ]
                    
                    for risk_role in high_risk_azure_roles:
                        if (role_definition_name and risk_role in role_definition_name) or \
                           (role_definition_id and risk_role in role_definition_id):
                            finding = {
                                "resource": resource_name,
                                "action": role_definition_name or role_definition_id,
                                "risk_level": "High",
                                "pattern": risk_role,
                                "resource_pattern": "Azure Role"
                            }
                            high_risk_findings.append(finding)
    
    return high_risk_findings

def generate_report(findings, output_file=None):
    """분석 결과에 대한 보고서를 생성합니다."""
    high_risk_count = sum(1 for f in findings if f['risk_level'] == 'High')
    medium_risk_count = sum(1 for f in findings if f['risk_level'] == 'Medium')
    
    # 기본 출력 파일명 생성
    if output_file is None:
        timestamp = datetime.now().strftime('%Y%m%d_%H%M%S')
        output_file = f"iam_risk_analysis_{timestamp}.csv"
    
    # CSV 보고서 생성
    with open(output_file, 'w', newline='') as csvfile:
        fieldnames = ['Resource', 'Action', 'Risk Level', 'Matched Pattern', 'Resource Pattern']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        
        writer.writeheader()
        for finding in findings:
            writer.writerow({
                'Resource': finding['resource'],
                'Action': finding['action'],
                'Risk Level': finding['risk_level'],
                'Matched Pattern': finding['pattern'] or 'N/A',
                'Resource Pattern': finding['resource_pattern']
            })
    
    print(f"\n{len(findings)} 개의 IAM 권한이 분석되었습니다.")
    print(f"위험 수준 요약: 높음({high_risk_count}), 중간({medium_risk_count})")
    print(f"보고서가 '{output_file}'에 저장되었습니다.")
    
    # 고위험 권한 요약 출력
    if high_risk_count > 0:
        print("\n⚠️ 고위험 IAM 권한:")
        for finding in findings:
            if finding['risk_level'] == 'High':
                print(f"  - {finding['resource']}: {finding['action']} ({finding['resource_pattern']})")
    
    return high_risk_count

def main():
    if len(sys.argv) < 2:
        print(f"사용법: {sys.argv[0]} <terraform_plan.json> [output_file.csv]")
        sys.exit(1)
    
    plan_file = sys.argv[1]
    output_file = sys.argv[2] if len(sys.argv) > 2 else None
    
    plan = load_plan(plan_file)
    findings = check_high_risk_permissions(plan)
    high_risk_count = generate_report(findings, output_file)
    
    # CI/CD 파이프라인을 위한 종료 코드 반환
    if high_risk_count > 0:
        print("\n고위험 IAM 권한이 발견되었습니다. 검토가 필요합니다.")
        sys.exit(1)
    else:
        print("\n고위험 IAM 권한이 발견되지 않았습니다.")
        sys.exit(0)

if __name__ == "__main__":
    main()
```

위 스크립트는 Terraform 계획 파일을 분석하여 고위험 IAM 권한을 식별합니다. CI/CD 파이프라인에서 사용할 수 있도록 설계되었으며, AWS, GCP, Azure 클라우드 환경의 IAM 관련 리소스를 검사합니다.

스크립트는 다음과 같은 기능을 제공합니다:

1. 고위험 IAM 권한 패턴 검사 (예: 와일드카드 권한, 관리자 권한)
2. 클라우드별 IAM 권한 분석 (AWS, GCP, Azure)
3. CSV 형식의 상세 보고서 생성
4. 고위험 권한 발견 시 CI/CD 파이프라인 실패를 위한 종료 코드 반환

#### 7.5.2 CI/CD 파이프라인 보안 통합

DevSecOps 파이프라인에 IAM 코드 보안 검사를 통합하는 방법:

**GitHub Actions 워크플로우**
```yaml
# .github/workflows/iam-security-checks.yml
name: IAM Security Checks

on:
  pull_request:
    paths:
      - '**/*.tf'
      - '**/*.tfvars'
      - 'iam/**'
      - 'roles/**'
      - 'policies/**'

jobs:
  terraform-plan:
    name: Terraform 계획 생성
    runs-on: ubuntu-latest
    outputs:
      plan_path: ${{ steps.plan.outputs.plan_path }}
    
    steps:
      - name: 코드 체크아웃
        uses: actions/checkout@v3
      
      - name: 테라폼 설정
        uses: hashicorp/setup-terraform@v2
        with:
          terraform_version: 1.5.0
      
      - name: 테라폼 초기화
        id: init
        run: |
          cd terraform
          terraform init -backend=false
      
      - name: 테라폼 계획
        id: plan
        run: |
          cd terraform
          terraform plan -out=tfplan.binary
          terraform show -json tfplan.binary > tfplan.json
          echo "plan_path=$(pwd)/tfplan.json" >> $GITHUB_OUTPUT
  
  tfsec:
    name: TFSec 보안 검사
    runs-on: ubuntu-latest
    
    steps:
      - name: 코드 체크아웃
        uses: actions/checkout@v3
      
      - name: tfsec 실행
        uses: aquasecurity/tfsec-action@v1.0.0
        with:
          soft_fail: false
          format: sarif
          github_token: ${{ secrets.GITHUB_TOKEN }}

  checkov:
    name: Checkov 정책 검사
    runs-on: ubuntu-latest
    
    steps:
      - name: 코드 체크아웃
        uses: actions/checkout@v3
      
      - name: Checkov 실행
        id: checkov
        uses: bridgecrewio/checkov-action@master
        with:
          directory: terraform/
          soft_fail: true
          framework: terraform
          output_format: sarif
          output_file: checkov-results.sarif
      
      - name: 결과 업로드
        uses: github/codeql-action/upload-sarif@v2
        with:
          sarif_file: checkov-results.sarif

  iam-analyzer:
    name: IAM 권한 분석
    runs-on: ubuntu-latest
    needs: terraform-plan
    
    steps:
      - name: 코드 체크아웃
        uses: actions/checkout@v3
      
      - name: 계획 파일 다운로드
        uses: actions/download-artifact@v3
        with:
          name: terraform-plan
          path: ./
      
      - name: IAM 정책 분석
        id: iam-analysis
        run: |
          python ./scripts/check_high_risk_permissions.py ${{ needs.terraform-plan.outputs.plan_path }} iam_risks.csv
          exit_code=$?
          
          # 분석 결과가 고위험 권한을 포함하는 경우 이슈 생성
          if [ $exit_code -ne 0 ]; then
            echo "iam_risks=true" >> $GITHUB_OUTPUT
          else
            echo "iam_risks=false" >> $GITHUB_OUTPUT
          fi
      
      - name: PR 코멘트 작성
        if: steps.iam-analysis.outputs.iam_risks == 'true'
        uses: actions/github-script@v6
        with:
          github-token: ${{ secrets.GITHUB_TOKEN }}
          script: |
            const fs = require('fs');
            const csv = fs.readFileSync('iam_risks.csv', 'utf8');
            const lines = csv.split('\n');
            const highRisks = lines.filter(line => line.includes('High'));
            
            let comment = '## 🚨 고위험 IAM 권한이 감지되었습니다!\n\n';
            comment += '다음 IAM 권한이 잠재적으로 위험한 것으로 식별되었습니다:\n\n';
            comment += '| 리소스 | 액션 | 위험 수준 | 패턴 |\n';
            comment += '|--------|------|-----------|--------|\n';
            
            highRisks.forEach(risk => {
              if (risk && !risk.startsWith('Resource')) {
                const parts = risk.split(',');
                if (parts.length >= 3) {
                  comment += `| ${parts[0]} | ${parts[1]} | ${parts[2]} | ${parts[3] || 'N/A'} |\n`;
                }
              }
            });
            
            comment += '\n👉 이러한 고위험 권한은 최소 권한 원칙에 위배될 수 있습니다. 검토 후 필요한 경우 더 제한된 권한으로 수정해주세요.';
            
            github.rest.issues.createComment({
              issue_number: context.issue.number,
              owner: context.repo.owner,
              repo: context.repo.repo,
              body: comment
            });
      
      - name: 분석 결과 업로드
        uses: actions/upload-artifact@v3
        with:
          name: iam-analysis-results
          path: iam_risks.csv
```

**CI/CD 파이프라인을 위한 권한 휴리스틱 검사기**
```python
#!/usr/bin/env python3
# iam_permissions_analyzer.py

import json
import os
import re
from dataclasses import dataclass
from typing import List, Dict, Set, Optional

@dataclass
class RiskAssessment:
    action: str
    permission: str
    risk_level: str
    resource: str
    reason: str
    recommendation: str

class IAMPermissionAnalyzer:
    def __init__(self):
        # 고위험 권한 패턴
        self.high_risk_patterns = {
            'admin': r'.*:.*Admin.*|.*:.*admin.*',
            'all_actions': r'.*:\*',
            'iam_write': r'iam:(Create|Delete|Put|Add|Remove|Update|Set).*',
            'dangerous_services': r'(kms|organizations|cloudtrail|config|guardduty|securityhub):\*',
            'sensitive_data': r'(s3|dynamodb|rds):\*',
            'compute_control': r'(ec2|ecs|eks|lambda):\*',
            'network_control': r'(ec2:CreateVpc|ec2:DeleteVpc|ec2:CreateSubnet|ec2:DeleteSubnet)',
            'policy_attachment': r'iam:.*Attach.*Policy.*',
        }
        
        # 권장 대안 매핑
        self.recommendations = {
            'admin': '필요한 특정 작업만 허용하도록 권한을 제한하세요',
            'all_actions': '와일드카드(*) 대신 필요한 특정 작업을 명시적으로 나열하세요',
            'iam_write': 'IAM 쓰기 작업을 특정 리소스와 조건으로 제한하세요',
            'dangerous_services': '보안 관련 서비스에 대한 권한을 세분화하고 제한하세요',
            'sensitive_data': '데이터 서비스에 대한 읽기/쓰기 권한을 분리하고 특정 리소스로 제한하세요',
            'compute_control': '컴퓨팅 리소스에 대한 관리 작업을 필요한 것으로만 제한하세요',
            'network_control': '네트워크 구성 변경은 특정 VPC/서브넷으로 제한하세요',
            'policy_attachment': '정책 연결 작업은 특정 정책과 대상으로 제한하세요',
        }
    
    def analyze_permission(self, action: str, resource: str = '*') -> RiskAssessment:
        """단일 IAM 권한에 대한 위험 평가"""
        risk_level = "낮음"
        reason = "표준 작업"
        category = None
        
        # 서비스 및 작업 식별
        if ':' in action:
            service, permission = action.split(':', 1)
        else:
            service, permission = action, '*'
        
        # 와일드카드 리소스 확인
        has_wildcard_resource = resource == '*' or '*' in resource
        
        # 패턴별 위험 평가
        for cat, pattern in self.high_risk_patterns.items():
            if re.match(pattern, action):
                risk_level = "높음"
                reason = f"{cat} 패턴 일치"
                category = cat
                break
        
        # 위험도가 아직 높지 않지만 와일드카드 리소스가 있는 경우
        if risk_level != "높음" and has_wildcard_resource and ':List' not in action and ':Get' not in action:
            risk_level = "중간"
            reason = "와일드카드 리소스에 대한 권한"
        
        # 추천 사항
        recommendation = "최소 권한 원칙을 적용하세요"
        if category and category in self.recommendations:
            recommendation = self.recommendations[category]
        
        return RiskAssessment(
            action=action,
            permission=permission,
            risk_level=risk_level,
            resource=resource,
            reason=reason,
            recommendation=recommendation
        )
    
    def analyze_policy_document(self, policy_doc: Dict) -> List[RiskAssessment]:
        """IAM 정책 문서 전체 분석"""
        results = []
        
        statements = policy_doc.get('Statement', [])
        if isinstance(statements, dict):
            statements = [statements]
        
        for stmt in statements:
            effect = stmt.get('Effect', '')
            if effect != 'Allow':
                continue
            
            actions = stmt.get('Action', [])
            if isinstance(actions, str):
                actions = [actions]
            
            resources = stmt.get('Resource', '*')
            if isinstance(resources, str):
                resources = [resources]
            
            for action in actions:
                for resource in resources:
                    assessment = self.analyze_permission(action, resource)
                    results.append(assessment)
        
        return results
    
    def analyze_terraform_plan(self, plan_json: Dict) -> Dict[str, List[RiskAssessment]]:
        """Terraform 계획에서 IAM 관련 리소스 분석"""
        results = {}
        
        for resource_change in plan_json.get('resource_changes', []):
            resource_type = resource_change.get('type', '')
            resource_name = resource_change.get('name', '')
            resource_address = f"{resource_type}.{resource_name}"
            
            # AWS IAM 리소스 확인
            if resource_type.startswith('aws_iam_'):
                after = resource_change.get('change', {}).get('after', {})
                
                # 정책 문서 처리
                policy_str = after.get('policy', after.get('inline_policy', ''))
                if policy_str:
                    try:
                        if isinstance(policy_str, str):
                            policy_doc = json.loads(policy_str)
                        else:
                            policy_doc = policy_str
                        
                        resource_results = self.analyze_policy_document(policy_doc)
                        if resource_results:
                            results[resource_address] = resource_results
                    except (json.JSONDecodeError, TypeError):
                        pass
            
            # GCP IAM 리소스 확인
            elif resource_type.startswith('google_'):
                after = resource_change.get('change', {}).get('after', {})
                
                # GCP 역할 처리
                role = after.get('role', '')
                if role and isinstance(role, str):
                    if role.startswith('roles/') and any(risk_role in role for risk_role in ['admin', 'owner', 'editor']):
                        assessment = RiskAssessment(
                            action=role,
                            permission=role,
                            risk_level="높음",
                            resource="*",
                            reason="GCP 고권한 역할",
                            recommendation="보다 제한적인 사용자 지정 역할 사용을 고려하세요"
                        )
                        results[resource_address] = [assessment]
            
            # Azure RBAC 리소스 확인
            elif resource_type.startswith('azurerm_role_'):
                after = resource_change.get('change', {}).get('after', {})
                
                # Azure 역할 처리
                role_name = after.get('role_definition_name', '')
                if role_name and any(risk_role in role_name.lower() for risk_role in ['owner', 'contributor', 'admin']):
                    assessment = RiskAssessment(
                        action=role_name,
                        permission=role_name,
                        risk_level="높음",
                        resource=after.get('scope', '*'),
                        reason="Azure 고권한 역할",
                        recommendation="보다 제한적인 내장 역할이나 사용자 지정 역할 사용을 고려하세요"
                    )
                    results[resource_address] = [assessment]
        
        return results

# 사용 예시
if __name__ == "__main__":
    import sys
    import csv
    
    if len(sys.argv) < 2:
        print(f"사용법: {sys.argv[0]} <terraform_plan.json> [output.csv]")
        sys.exit(1)
    
    # 계획 파일 로드
    plan_file = sys.argv[1]
    with open(plan_file, 'r') as f:
        plan = json.load(f)
    
    # 분석 실행
    analyzer = IAMPermissionAnalyzer()
    analysis_results = analyzer.analyze_terraform_plan(plan)
    
    # 결과 출력
    high_risk_count = 0
    
    # CSV 파일로 결과 저장
    output_file = sys.argv[2] if len(sys.argv) > 2 else "iam_analysis_results.csv"
    with open(output_file, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(['리소스', '권한', '위험 수준', '리소스 패턴', '이유', '권장 사항'])
        
        for resource, assessments in analysis_results.items():
            for assessment in assessments:
                writer.writerow([
                    resource,
                    assessment.action,
                    assessment.risk_level,
                    assessment.resource,
                    assessment.reason,
                    assessment.recommendation
                ])
                
                if assessment.risk_level == "높음":
                    high_risk_count += 1
    
    print(f"분석 완료: {sum(len(assessments) for assessments in analysis_results.values())} 권한 검사, {high_risk_count}개 고위험 발견")
    print(f"결과가 {output_file}에 저장되었습니다")
    
    # 고위험 권한이 있으면 종료 코드 1 반환
    if high_risk_count > 0:
        sys.exit(1)
    else:
        sys.exit(0)
```

이 스크립트를 GitHub Actions나 Jenkins 같은 CI/CD 파이프라인에 통합하면 고위험 IAM 권한을 자동으로 감지하고 보고할 수 있습니다. 분석 결과는 CSV 파일로 출력되며, 고위험 권한이 발견되면 파이프라인을 실패시킵니다.

#### 7.5.3 지속적인 IAM 정책 검사

효과적인 클라우드 보안을 위해서는 운영 환경에서의 IAM 정책을 지속적으로 감사하고 검증하는 것이 필수적입니다. 이를 통해 정책 드리프트를 감지하고 의도하지 않은 권한 확장을 방지할 수 있습니다.

**AWS Config를 활용한 IAM 정책 모니터링**

AWS Config는 계정 내 리소스 구성을 지속적으로 모니터링하고, 구성이 원하는 설정에서 벗어날 경우 알림을 제공합니다.

```json
// AWS Config 규칙 - IAM 정책 제한
{
  "ConfigRuleName": "IAM-PolicyNoStatementsWithAdminAccess",
  "Description": "관리자 권한이 포함된 IAM 정책 탐지",
  "Scope": {
    "ComplianceResourceTypes": [
      "AWS::IAM::Policy",
      "AWS::IAM::Role"
    ]
  },
  "Source": {
    "Owner": "AWS",
    "SourceIdentifier": "IAM_POLICY_NO_STATEMENTS_WITH_ADMIN_ACCESS"
  },
  "InputParameters": {}
}
```

**GCP Security Command Center 통합**

Google Cloud의 Security Command Center는 IAM 구성 취약점을 지속적으로 모니터링하고 보고합니다.

```yaml
# Security Command Center 취약점 탐지 설정
service: securitycenter.googleapis.com
name: organizations/ORGANIZATION_ID/sources/SOURCE_ID
displayName: "IAM 정책 감사"
findings:
  - name: "광범위한 IAM 권한"
    category: "IAM_OVERLY_PERMISSIVE_ROLE"
    sourceProperties:
      resource_type: "PROJECT"
      resource_name: "${PROJECT_ID}"
      severity: "HIGH"
```

**Azure Policy를 통한 IAM 통제**

Azure Policy는, 지정된 IAM 구성을 지속적으로 검증하고 비준수 리소스를 식별합니다.

```json
// Azure Policy - 권한 있는 역할 제한
{
  "properties": {
    "displayName": "권한 있는 역할 제한",
    "description": "Owner, Contributor 등의 고권한 역할이 할당된 사용자 감사",
    "mode": "All",
    "metadata": {
      "category": "Security Center"
    },
    "parameters": {
      "listOfAllowedRoles": {
        "type": "Array",
        "metadata": {
          "displayName": "허용된 역할",
          "description": "명시적으로 허용된 역할 목록"
        },
        "defaultValue": [
          "Reader",
          "Backup Operator",
          "Network Contributor"
        ]
      }
    },
    "policyRule": {
      "if": {
        "allOf": [
          {
            "field": "type",
            "equals": "Microsoft.Authorization/roleAssignments"
          },
          {
            "field": "Microsoft.Authorization/roleAssignments/roleDefinitionId",
            "notIn": "[parameters('listOfAllowedRoles')]"
          }
        ]
      },
      "then": {
        "effect": "audit"
      }
    }
  }
}
```

**자동화된 IAM 감사 스크립트**

다음 Python 스크립트는 AWS 계정의 IAM 구성을 감사하고 위험한 정책을 식별하는 예시입니다:

```python
#!/usr/bin/env python3
# aws_iam_auditor.py

import boto3
import json
import csv
from datetime import datetime
import re

def audit_iam_policies():
    """AWS IAM 정책 감사 수행"""
    # AWS 클라이언트 설정
    iam = boto3.client('iam')
    
    # 감사 결과를 저장할 리스트
    findings = []
    
    # 고위험 패턴 정의
    high_risk_patterns = [
        r"iam:.*",
        r".*:\*",
        r".*Admin.*",
        r".*FullAccess.*"
    ]
    
    # 모든 역할 검사
    for role in iam.list_roles()['Roles']:
        role_name = role['RoleName']
        
        # 관리형 정책 검사
        attached_policies = iam.list_attached_role_policies(RoleName=role_name)['AttachedPolicies']
        for policy in attached_policies:
            policy_arn = policy['PolicyArn']
            policy_version = iam.get_policy(PolicyArn=policy_arn)['Policy']['DefaultVersionId']
            policy_doc = iam.get_policy_version(PolicyArn=policy_arn, VersionId=policy_version)['PolicyVersion']['Document']
            
            check_policy_statements(policy_doc, role_name, policy['PolicyName'], findings, high_risk_patterns, "관리형")
        
        # 인라인 정책 검사
        inline_policies = iam.list_role_policies(RoleName=role_name)['PolicyNames']
        for policy_name in inline_policies:
            policy_doc = iam.get_role_policy(RoleName=role_name, PolicyName=policy_name)['PolicyDocument']
            
            check_policy_statements(policy_doc, role_name, policy_name, findings, high_risk_patterns, "인라인")
    
    # 모든 사용자 검사
    for user in iam.list_users()['Users']:
        user_name = user['UserName']
        
        # 관리형 정책 검사
        attached_policies = iam.list_attached_user_policies(UserName=user_name)['AttachedPolicies']
        for policy in attached_policies:
            policy_arn = policy['PolicyArn']
            policy_version = iam.get_policy(PolicyArn=policy_arn)['Policy']['DefaultVersionId']
            policy_doc = iam.get_policy_version(PolicyArn=policy_arn, VersionId=policy_version)['PolicyVersion']['Document']
            
            check_policy_statements(policy_doc, user_name, policy['PolicyName'], findings, high_risk_patterns, "관리형")
        
        # 인라인 정책 검사
        inline_policies = iam.list_user_policies(UserName=user_name)['PolicyNames']
        for policy_name in inline_policies:
            policy_doc = iam.get_user_policy(UserName=user_name, PolicyName=policy_name)['PolicyDocument']
            
            check_policy_statements(policy_doc, user_name, policy_name, findings, high_risk_patterns, "인라인")
    
    # CSV 파일로 결과 출력
    timestamp = datetime.now().strftime('%Y%m%d_%H%M%S')
    output_file = f"iam_audit_{timestamp}.csv"
    
    with open(output_file, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(['개체 유형', '개체 이름', '정책 이름', '정책 유형', '작업', '리소스', '위험 수준', '위험 패턴'])
        
        for finding in findings:
            writer.writerow([
                finding['principal_type'],
                finding['principal_name'],
                finding['policy_name'],
                finding['policy_type'],
                finding['action'],
                finding['resource'],
                finding['risk_level'],
                finding['risk_pattern']
            ])
    
    print(f"감사가 완료되었습니다. {len(findings)}개의 잠재적 위험이 발견되었습니다.")
    print(f"결과가 {output_file}에 저장되었습니다.")

def check_policy_statements(policy_doc, principal_name, policy_name, findings, high_risk_patterns, policy_type):
    """정책 문서의 문장을 검사하여 위험한 권한을 식별"""
    principal_type = "역할" if policy_type.startswith("역할") else "사용자"
    
    statements = policy_doc.get('Statement', [])
    if not isinstance(statements, list):
        statements = [statements]
    
    for stmt in statements:
        if stmt.get('Effect') != 'Allow':
            continue
        
        actions = stmt.get('Action', [])
        if not isinstance(actions, list):
            actions = [actions]
        
        resources = stmt.get('Resource', '*')
        if not isinstance(resources, list):
            resources = [resources]
        
        for action in actions:
            # 위험 수준 평가
            risk_level = "낮음"
            matching_pattern = None
            
            for pattern in high_risk_patterns:
                if re.match(pattern, action):
                    risk_level = "높음"
                    matching_pattern = pattern
                    break
            
            # 와일드카드 리소스인 경우 위험도 상승
            if any(r == '*' for r in resources) and risk_level != "높음":
                risk_level = "중간"
            
            if risk_level != "낮음":
                for resource in resources:
                    findings.append({
                        'principal_type': principal_type,
                        'principal_name': principal_name,
                        'policy_name': policy_name,
                        'policy_type': policy_type,
                        'action': action,
                        'resource': resource,
                        'risk_level': risk_level,
                        'risk_pattern': matching_pattern
                    })

if __name__ == "__main__":
    audit_iam_policies()
```

**크론잡을 이용한 정기적 IAM 감사**

Kubernetes 환경에서 정기적으로 IAM 감사를 수행하는 크론잡 설정 예시:

```yaml
# iam-audit-cronjob.yaml
apiVersion: batch/v1
kind: CronJob
metadata:
  name: iam-audit
  namespace: security
spec:
  schedule: "0 1 * * *"  # 매일 새벽 1시
  concurrencyPolicy: Forbid
  jobTemplate:
    spec:
      template:
        spec:
          serviceAccountName: security-auditor
          containers:
          - name: iam-auditor
            image: security-tools:latest
            command:
            - /bin/sh
            - -c
            - |
              python3 /scripts/aws_iam_auditor.py
              aws s3 cp iam_audit_*.csv s3://security-audit-logs/iam/
              
              # 고위험 발견 시 알림 전송
              if grep -q "높음" iam_audit_*.csv; then
                python3 /scripts/send_alert.py "고위험 IAM 구성이 발견되었습니다"
              fi
            volumeMounts:
            - name: scripts
              mountPath: /scripts
            env:
            - name: AWS_PROFILE
              value: security-audit
          volumes:
          - name: scripts
            configMap:
              name: audit-scripts
          restartPolicy: OnFailure
```

이러한 지속적인 모니터링 및 감사 메커니즘을 통해 클라우드 환경에서 IAM 정책 관리의 투명성을 확보하고, 위험한 구성을 신속하게 식별하여 대응할 수 있습니다.

### 7.6 클라우드 IAM 모범 사례 요약

클라우드 환경에서 IAM을 효과적으로 관리하기 위한 핵심 모범 사례를 요약합니다:

#### 7.6.1 최소 권한 원칙 적용

1. **세분화된 권한 정의**
   - "모든 것 허용"이 아닌 작업별, 리소스별로 필요한 권한만 부여
   - 리소스 수준의 정책(ARN, 경로, 이름 등) 활용
   - 작업에 필요한 최소한의 권한만 포함하는 사용자 정의 역할 생성

2. **조건부 접근 제어**
   ```json
   // AWS 조건부 IAM 정책 예시
   {
     "Version": "2012-10-17",
     "Statement": [
       {
         "Effect": "Allow",
         "Action": "s3:*",
         "Resource": "arn:aws:s3:::app-logs-*",
         "Condition": {
           "IpAddress": {
             "aws:SourceIp": "192.0.2.0/24"
           },
           "StringEquals": {
             "aws:RequestedRegion": "ap-northeast-2"
           }
         }
       }
     ]
   }
   ```

3. **임시 자격 증명 활용**
   - 장기 API 키 대신 임시 자격 증명 사용
   - STS, 토큰 기반 인증으로 권한 유효 시간 제한
   - 필요 시에만 권한 상승(Just-in-time 액세스)

#### 7.6.2 자격 증명 관리 강화

1. **MFA 필수화**
   ```bash
   # AWS 사용자 액세스를 MFA 필수로 제한하는 SCP
   aws organizations create-policy \
     --name RequireMFA \
     --description "MFA 필수화" \
     --content '{
       "Version": "2012-10-17",
       "Statement": [
         {
           "Sid": "DenyAllExceptListedIfNoMFA",
           "Effect": "Deny",
           "NotAction": [
             "iam:CreateVirtualMFADevice",
             "iam:EnableMFADevice",
             "iam:GetUser",
             "iam:ListMFADevices",
             "iam:ListVirtualMFADevices",
             "iam:ResyncMFADevice",
             "sts:GetSessionToken"
           ],
           "Resource": "*",
           "Condition": {
             "BoolIfExists": {
               "aws:MultiFactorAuthPresent": "false"
             }
           }
         }
       ]
     }' \
     --type SERVICE_CONTROL_POLICY
   ```

2. **자격 증명 수명 주기 관리**
   - 미사용 자격 증명 제거
   - 정기적인 자격 증명 순환
   - 직원 이직/퇴사 시 즉시 접근 권한 취소

3. **중앙 집중식 ID 관리**
   - 클라우드 ID 페더레이션 설정
   - 다중 클라우드 환경에서 단일 ID 소스 활용
   - 기업 AD/SSO와 클라우드 서비스 통합

#### 7.6.3 안전한 리소스 액세스 패턴

1. **점프 서버/배스천 호스트 활용**
   ```yaml
   # Terraform을 통한 배스천 호스트 구성
   resource "aws_instance" "bastion" {
     ami           = "ami-0c55b159cbfafe1f0"
     instance_type = "t3.micro"
     key_name      = aws_key_pair.bastion_key.key_name
     vpc_security_group_ids = [aws_security_group.bastion_sg.id]
     subnet_id     = aws_subnet.public_subnet.id
     
     tags = {
       Name = "Bastion-Host"
     }
     
     # 사용자 데이터로 배스천 강화
     user_data = <<-EOF
       #!/bin/bash
       # 유휴 타임아웃 설정
       echo "ClientAliveInterval 300" >> /etc/ssh/sshd_config
       echo "ClientAliveCountMax 0" >> /etc/ssh/sshd_config
       
       # 로그인 감사 활성화
       echo "LogLevel VERBOSE" >> /etc/ssh/sshd_config
       
       service sshd restart
       
       # CloudWatch 로그 에이전트 설치
       yum install -y awslogs
       
       # 로그 설정
       cat <<'EOT' > /etc/awslogs/config/ssh-logs.conf
       [/var/log/secure]
       datetime_format = %b %d %H:%M:%S
       file = /var/log/secure
       buffer_duration = 5000
       log_stream_name = {instance_id}/var/log/secure
       initial_position = start_of_file
       log_group_name = /var/log/secure
       EOT
       
       systemctl start awslogsd
       systemctl enable awslogsd
     EOF
   }
   
   resource "aws_security_group" "bastion_sg" {
     name        = "bastion-security-group"
     description = "Security group for bastion host"
     vpc_id      = aws_vpc.main.id
     
     ingress {
       from_port   = 22
       to_port     = 22
       protocol    = "tcp"
       cidr_blocks = ["10.0.0.0/8"] # 회사 네트워크만 허용
     }
     
     egress {
       from_port   = 0
       to_port     = 0
       protocol    = "-1"
       cidr_blocks = ["0.0.0.0/0"]
     }
   }
   ```

2. **프라이빗 엔드포인트 활용**
   ```yaml
   # AWS PrivateLink 구성
   resource "aws_vpc_endpoint" "s3" {
     vpc_id            = aws_vpc.main.id
     service_name      = "com.amazonaws.${var.region}.s3"
     vpc_endpoint_type = "Gateway"
     route_table_ids   = [aws_route_table.private.id]
     
     policy = jsonencode({
       Version = "2012-10-17"
       Statement = [
         {
           Effect    = "Allow"
           Principal = "*"
           Action    = [
             "s3:GetObject",
             "s3:ListBucket"
           ]
           Resource  = [
             "arn:aws:s3:::${var.bucket_name}",
             "arn:aws:s3:::${var.bucket_name}/*"
           ]
         }
       ]
     })
   }
   ```

3. **서비스 계정 권한 제한**
   ```yaml
   # GCP 워크로드 아이덴티티 구성
   resource "google_service_account" "app_service_account" {
     account_id   = "app-service-account"
     display_name = "Application Service Account"
   }
   
   resource "google_project_iam_member" "app_service_account_roles" {
     project = var.project_id
     role    = "roles/storage.objectViewer"
     member  = "serviceAccount:${google_service_account.app_service_account.email}"
   }
   
   resource "google_service_account_iam_binding" "workload_identity_binding" {
     service_account_id = google_service_account.app_service_account.name
     role               = "roles/iam.workloadIdentityUser"
     members = [
       "serviceAccount:${var.project_id}.svc.id.goog[${var.namespace}/${var.k8s_service_account}]"
     ]
   }
   ```

#### 7.6.4 지속적인 검증 및 자동화

1. **IaC를 통한 IAM 정책 관리**
   - 인프라 코드로 IAM 정책 관리
   - 버전 관리 시스템을 통한 변경 추적
   - 코드 리뷰 프로세스로 정책 품질 관리

2. **권한 요청 워크플로우 구축**
   - 자동화된 승인 프로세스
   - 시간 제한 권한 부여
   - 권한 요청 사유 문서화

3. **지속적 보안 모니터링**
   - 이상 징후 탐지 시스템 구축
   - 권한 사용 패턴 분석
   - 자동화된 정책 검증 파이프라인

## 8. 결론 및 고려사항

### 8.1 클라우드 IAM 고려 사항

#### 8.1.1 멀티클라우드 전략과 IAM

멀티클라우드 환경에서 일관된 IAM 정책을 유지하는 것은 복잡하지만 중요한 과제입니다. 이를 위해 다음 사항을 고려해야 합니다:

1. **중앙 집중식 ID 관리**
   - 기업 디렉터리 서비스(AD, Okta, Auth0 등)를 통한 통합 관리
   - 클라우드 간 공통 ID 체계 수립
   - 사용자 라이프사이클 관리 일원화

2. **크로스 클라우드 권한 매핑**
   - 클라우드 서비스 간 권한 매핑 표준화
   - 역할 기반 액세스 제어 모델 일관성 유지
   - 벤더 중립적 권한 정의 시스템 구축

3. **통합 감사 및 모니터링**
   - 클라우드 간 통합 로그 분석
   - 크로스 클라우드 액세스 패턴 모니터링
   - 집중화된 보안 알림 시스템

#### 8.1.2 확장성과 복잡성 관리

엔터프라이즈 규모의 클라우드 환경에서는 IAM 복잡성 관리가 중요합니다:

1. **정책 표준화**
   - 재사용 가능한 IAM 정책 템플릿 개발
   - 역할 및 권한의 체계적 분류 시스템
   - 조직 구조를 반영한 권한 모델

2. **권한 분석 및 최적화**
   - 미사용 권한 식별 및 제거
   - 권한 중복 분석
   - 권한 관계 그래프 모델링

3. **자동화된 관리 도구**
   - IAM 정책 생성 자동화
   - 사용 기반 권한 추천 시스템
   - 권한 드리프트 감지 및 교정

#### 8.1.3 규제 준수 및 감사

규제 환경에서 클라우드 IAM은 컴플라이언스의 핵심 요소입니다:

1. **규제 매핑**
   - IAM 정책과 규제 요구사항 매핑
   - 업종별 컴플라이언스 지원(PCI DSS, HIPAA, GDPR 등)
   - 증거 수집 및 보고 자동화

2. **권한 분리(Separation of Duties)**
   - 핵심 기능에 대한 권한 분리 구현
   - 중요 작업에 다중 승인 요구
   - 모니터링과 실행 권한의 분리

3. **감사 추적**
   - 변경 불가능한 감사 로그 저장
   - 권한 변경 사유 문서화
   - 장기간 감사 데이터 보존

### 8.2 미래 동향 및 발전 방향

클라우드 IAM은 빠르게 발전하고 있으며, 다음과 같은 동향에 주목할 필요가 있습니다:

#### 8.2.1 제로 트러스트 모델

1. **지속적 검증**
   - 세션 중 지속적인 인증 및 권한 재검증
   - 컨텍스트 기반 접근 제어 강화
   - 위험 기반 인증 결정

2. **마이크로 세분화**
   - 보다 세분화된 권한 정의
   - 워크로드 수준의 ID 및 권한 관리
   - 리소스 간 통신에 대한 세밀한 제어

3. **네트워크 독립적 인증**
   - 네트워크 위치에 의존하지 않는 모델
   - 디바이스 상태 및 컨텍스트 기반 접근
   - 서비스 메시와 통합된 ID 기반 통신

#### 8.2.2 AI/ML 기반 IAM

1. **이상 탐지**
   - 행동 기반 액세스 패턴 분석
   - 비정상적인 권한 사용 실시간 탐지
   - 사용자/서비스별 기준선 학습

2. **권한 추천**
   - 사용 패턴 기반 최소 권한 자동 제안
   - 유사 역할 패턴 분석
   - 역할 최적화 추천

3. **동적 권한 조정**
   - 위험 수준에 따른 자동 권한 조정
   - 컨텍스트 인식 접근 제어 결정
   - 시간/위치 기반 권한 자동 조정

#### 8.2.3 분산형 ID 및 Web3

1. **자기 주권 ID(Self-Sovereign Identity)**
   - 사용자 중심 ID 관리
   - 분산형 ID 시스템과 클라우드 통합
   - 검증 가능한 자격 증명 활용

2. **블록체인 기반 접근 제어**
   - 분산화된 권한 관리
   - 감사 가능한 권한 변경 이력
   - 스마트 계약을 통한 자동화된 권한 관리

3. **암호화 기반 인증**
   - 제로 지식 증명 기술 활용
   - 멀티파티 계산을 통한 안전한 인증
   - 양자 내성 암호화 준비

### 8.3 실용적 로드맵

클라우드 IAM 구현을 위한 단계별 접근 방식:

1. **기초 단계 (0-3개월)**
   - IAM 현황 평가 및 격차 분석
   - 최소 권한 정책 문서화
   - 기존 높은 권한 계정 인벤토리 및 재구성

2. **강화 단계 (3-6개월)**
   - 자동화된 IAM 정책 검증 파이프라인 구축
   - 중앙 집중식 인증/인가 시스템 구현
   - 정기적인 권한 검토 프로세스 확립

3. **최적화 단계 (6-12개월)**
   - 권한 사용 분석 및 최적화
   - 멀티클라우드 ID 전략 구현
   - 지속적 검증 및 개선 체계 구축

4. **혁신 단계 (12개월 이후)**
   - AI 기반 이상 감지 시스템 통합
   - 제로 트러스트 아키텍처 전환
   - 위험 기반 동적 권한 시스템 구현

## 9. 참고 자료

### 9.1 클라우드 공급자 IAM 문서

1. **AWS IAM**
   - [AWS IAM 사용 설명서](https://docs.aws.amazon.com/IAM/latest/UserGuide/)
   - [AWS IAM 정책 참조](https://docs.aws.amazon.com/IAM/latest/UserGuide/reference_policies.html)
   - [AWS STS 문서](https://docs.aws.amazon.com/STS/latest/APIReference/)
   - [AWS 보안 모범 사례](https://docs.aws.amazon.com/wellarchitected/latest/security-pillar/welcome.html)

2. **GCP IAM**
   - [Google Cloud IAM 문서](https://cloud.google.com/iam/docs)
   - [GCP IAM 역할 목록](https://cloud.google.com/iam/docs/understanding-roles)
   - [Workload Identity Federation](https://cloud.google.com/iam/docs/workload-identity-federation)
   - [GCP 보안 설계 가이드](https://cloud.google.com/security/overview)

3. **Azure RBAC**
   - [Azure RBAC 문서](https://docs.microsoft.com/azure/role-based-access-control/)
   - [Azure ID 관리 모범 사례](https://docs.microsoft.com/azure/security/fundamentals/identity-management-best-practices)
   - [Azure Entra ID 문서](https://docs.microsoft.com/azure/active-directory/)
   - [Azure 보안 기준](https://docs.microsoft.com/azure/security/benchmarks/introduction)

### 9.2 표준 및 프레임워크

1. **보안 표준**
   - [NIST Cybersecurity Framework](https://www.nist.gov/cyberframework)
   - [ISO/IEC 27001](https://www.iso.org/isoiec-27001-information-security.html)
   - [CIS Controls](https://www.cisecurity.org/controls/)
   - [CSA Cloud Controls Matrix](https://cloudsecurityalliance.org/research/cloud-controls-matrix/)

2. **클라우드 보안 가이드라인**
   - [NIST SP 800-204 클라우드 컴퓨팅을 위한 마이크로서비스 보안](https://csrc.nist.gov/publications/detail/sp/800-204/final)
   - [NIST SP 800-210 클라우드 컴퓨팅 일반 액세스 제어 지침](https://csrc.nist.gov/publications/detail/sp/800-210/final)
   - [ENISA 클라우드 보안 가이드](https://www.enisa.europa.eu/topics/cloud-and-big-data/cloud-security)

3. **규제 준수 프레임워크**
   - [GDPR(일반 데이터 보호 규정)](https://gdpr.eu/)
   - [HIPAA(건강보험 양도 및 책임에 관한 법)](https://www.hhs.gov/hipaa/index.html)
   - [PCI DSS(지불 카드 산업 데이터 보안 표준)](https://www.pcisecuritystandards.org/)
   - [SOC 2(서비스 조직 제어)](https://www.aicpa.org/interestareas/frc/assuranceadvisoryservices/sorhome.html)

### 9.3 도구 및 유틸리티

1. **IAM 보안 스캐닝 도구**
   - [AWS IAM Access Analyzer](https://aws.amazon.com/iam/features/analyze-access/)
   - [CloudSploit](https://cloudsploit.com/) (Aqua Security)
   - [ScoutSuite](https://github.com/nccgroup/ScoutSuite)
   - [Prowler](https://github.com/toniblyx/prowler)
   - [Principal Mapper](https://github.com/nccgroup/PMapper)

2. **정책 관리 도구**
   - [Cloudsplaining](https://github.com/salesforce/cloudsplaining)
   - [Policyscan](https://github.com/Azure/Policyscan)
   - [IAM Floyd](https://github.com/udondan/iam-floyd)
   - [AWS Policy Generator](https://awspolicygen.s3.amazonaws.com/policygen.html)
   - [Google Policy Troubleshooter](https://cloud.google.com/policy-troubleshooter)

3. **IaC 보안 도구**
   - [Checkov](https://www.checkov.io/)
   - [tfsec](https://github.com/aquasecurity/tfsec)
   - [Terrascan](https://github.com/accurics/terrascan)
   - [CloudFormation Guard](https://github.com/aws-cloudformation/cloudformation-guard)
   - [Snyk Infrastructure as Code](https://snyk.io/product/infrastructure-as-code-security/)

### 9.4 서적 및 출판물

1. **클라우드 보안 전문 서적**
   - "AWS 보안 모범 사례" by Scott Piper
   - "Google Cloud Platform 보안 가이드" by Google Cloud Team
   - "Microsoft Azure 보안 엔지니어링" by Yuri Diogenes
   - "클라우드 환경에서의 ID 및 액세스 관리" by Abhishek Gupta

2. **IAM 관련 백서**
   - ["Zero Trust Architecture"](https://nvlpubs.nist.gov/nistpubs/SpecialPublications/NIST.SP.800-207.pdf) by NIST
   - ["최소 권한의 기술적 구현"](https://www.sans.org/reading-room/whitepapers/bestprac/paper/38962) by SANS Institute
   - ["AWS에서 IAM 보안 강화"](https://d1.awsstatic.com/whitepapers/aws-security-best-practices.pdf) by AWS
   - ["클라우드의 ID 관리 로드맵"](https://cloudsecurityalliance.org/artifacts/identity-and-access-management-roadmap/) by CSA

3. **보안 블로그 및 아티클**
   - [AWS 보안 블로그](https://aws.amazon.com/blogs/security/)
   - [Google Cloud 보안 블로그](https://cloud.google.com/blog/products/identity-security)
   - [Azure 보안 블로그](https://azure.microsoft.com/blog/topics/security/)
   - [Wiz 블로그](https://www.wiz.io/blog)
   - [LastWeekInAWS](https://www.lastweekinaws.com/)

### 9.5 커뮤니티 및 학습 리소스

1. **온라인 커뮤니티**
   - [AWS Heroes](https://aws.amazon.com/developer/community/heroes/?community-heroes-all.sort-by=item.additionalFields.sortPosition&community-heroes-all.sort-order=asc&awsf.filter-hero-category=*all&awsf.filter-hero-location=*all&awsf.filter-hero-expertise=expertise%23security)
   - [Reddit r/aws, r/googlecloud, r/AZURE](https://www.reddit.com/r/aws+googlecloud+AZURE/)
   - [Stack Overflow - Cloud Security 태그](https://stackoverflow.com/questions/tagged/cloud-security)
   - [Cloud Security Alliance](https://cloudsecurityalliance.org/)

2. **컨퍼런스 및 이벤트**
   - [AWS re:Inforce](https://reinforce.awsevents.com/)
   - [Google Cloud Security Summits](https://cloud.google.com/security/summit)
   - [Microsoft Ignite](https://myignite.microsoft.com/)
   - [RSA Conference](https://www.rsaconference.com/)
   - [Black Hat](https://www.blackhat.com/)

3. **온라인 학습 플랫폼**
   - [A Cloud Guru](https://acloudguru.com/)
   - [Cloud Academy](https://cloudacademy.com/)
   - [Pluralsight](https://www.pluralsight.com/)
   - [AWS Training and Certification](https://aws.amazon.com/training/)
   - [Google Cloud Training](https://cloud.google.com/training)
   - [Microsoft Learn](https://docs.microsoft.com/learn/)

### 9.6 오픈소스 IAM 솔루션

1. **오픈소스 IAM 프로젝트**
   - [Keycloak](https://www.keycloak.org/)
   - [OpenIAM](https://www.openiam.com/)
   - [Gluu](https://www.gluu.org/)
   - [WSO2 Identity Server](https://wso2.com/identity-and-access-management/)
   - [OpenID Connect](https://openid.net/connect/)

2. **ID 페더레이션 솔루션**
   - [Dex](https://github.com/dexidp/dex)
   - [OAuth2 Proxy](https://github.com/oauth2-proxy/oauth2-proxy)
   - [SAML](https://github.com/onelogin/python-saml)
   - [SPIFFE/SPIRE](https://spiffe.io/)
   - [Kerberos](https://web.mit.edu/kerberos/)

3. **접근 제어 및 권한 관리**
   - [Open Policy Agent (OPA)](https://www.openpolicyagent.org/)
   - [LDAP](https://www.openldap.org/)
   - [Casbin](https://github.com/casbin/casbin)
   - [AuthZed](https://authzed.com/)
   - [Zanzibar](https://research.google/pubs/pub48190/)

---

이 문서는 클라우드 IAM(Identity and Access Management)에 관한 포괄적인 가이드로, AWS, GCP, Azure 등 주요 클라우드 제공업체의 IAM 시스템에 대한 개념부터 실제 구현까지 다루었습니다. 최소 권한 원칙, 자격 증명 관리, 멀티클라우드 전략, 자동화된 감사 등 클라우드 환경에서 성공적인 IAM 구현을 위한 모범 사례도 포함하고 있습니다. 또한 제로 트러스트 모델, AI/ML 기반 IAM, 분산형 ID 등 미래 동향도 살펴보았습니다.

클라우드 IAM은 지속적으로 발전하는 분야이므로, 최신 모범 사례와 보안 권장사항을 계속 참고하시기 바랍니다. 보안은 단일 솔루션이 아닌 지속적인 여정입니다. 이 문서가 여러분의 클라우드 보안 여정에 도움이 되기를 바랍니다.