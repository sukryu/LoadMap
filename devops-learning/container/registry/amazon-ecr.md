# AWS Elastic Container Registry 활용 가이드

> **목표:**  
> - AWS ECR의 기본 개념과 주요 기능을 이해한다.
> - ECR 리포지토리 생성 및 관리 방법을 습득한다.
> - 보안 설정과 접근 제어 방법을 익힌다.
> - CI/CD 파이프라인과의 통합 방법을 학습한다.

---

## 1. AWS ECR 개요

AWS Elastic Container Registry(ECR)는 AWS에서 제공하는 완전관리형 Docker 컨테이너 레지스트리입니다. ECR은 Amazon ECS, EKS와 완벽하게 통합되며, IAM을 통한 세밀한 접근 제어를 제공합니다. 또한 컨테이너 이미지를 암호화하여 저장하고, 이미지 취약점 스캐닝 기능을 제공합니다.

### 주요 특징
- AWS 서비스들과의 원활한 통합
- IAM 기반의 세밀한 접근 제어
- 이미지 암호화 및 보안 스캐닝
- 비용 효율적인 스토리지
- 높은 가용성과 확장성

---

## 2. ECR 환경 설정

### 2.1 AWS CLI 설정

AWS CLI를 통한 ECR 접근 설정:

```bash
# AWS CLI 설치 확인
aws --version

# AWS 자격 증명 구성
aws configure

# ECR 로그인
aws ecr get-login-password --region ap-northeast-2 | \
docker login --username AWS \
--password-stdin ${AWS_ACCOUNT_ID}.dkr.ecr.ap-northeast-2.amazonaws.com
```

### 2.2 리포지토리 생성

```bash
# ECR 리포지토리 생성
aws ecr create-repository \
    --repository-name my-application \
    --image-scanning-configuration scanOnPush=true \
    --encryption-configuration encryptionType=KMS \
    --region ap-northeast-2
```

---

## 3. 이미지 관리

### 3.1 이미지 푸시

로컬 이미지를 ECR에 푸시하는 프로세스:

```bash
# 이미지 태깅
docker tag my-application:latest \
${AWS_ACCOUNT_ID}.dkr.ecr.ap-northeast-2.amazonaws.com/my-application:latest

# 이미지 푸시
docker push \
${AWS_ACCOUNT_ID}.dkr.ecr.ap-northeast-2.amazonaws.com/my-application:latest
```

### 3.2 이미지 수명 주기 정책

이미지 관리를 위한 수명 주기 정책 설정:

```json
{
    "rules": [
        {
            "rulePriority": 1,
            "description": "Keep last 30 days images",
            "selection": {
                "tagStatus": "untagged",
                "countType": "sinceImagePushed",
                "countUnit": "days",
                "countNumber": 30
            },
            "action": {
                "type": "expire"
            }
        }
    ]
}
```

---

## 4. 보안 설정

### 4.1 IAM 정책 설정

ECR 접근을 위한 IAM 정책 예시:

```json
{
    "Version": "2012-10-17",
    "Statement": [
        {
            "Sid": "ECRAccess",
            "Effect": "Allow",
            "Action": [
                "ecr:GetAuthorizationToken",
                "ecr:BatchCheckLayerAvailability",
                "ecr:GetDownloadUrlForLayer",
                "ecr:GetRepositoryPolicy",
                "ecr:DescribeRepositories",
                "ecr:ListImages",
                "ecr:DescribeImages",
                "ecr:BatchGetImage",
                "ecr:PutImage",
                "ecr:InitiateLayerUpload",
                "ecr:UploadLayerPart",
                "ecr:CompleteLayerUpload"
            ],
            "Resource": "arn:aws:ecr:region:account-id:repository/repository-name"
        }
    ]
}
```

### 4.2 리포지토리 정책

리포지토리 수준의 접근 제어 정책:

```json
{
    "Version": "2012-10-17",
    "Statement": [
        {
            "Sid": "AllowPull",
            "Effect": "Allow",
            "Principal": {
                "AWS": "arn:aws:iam::account-id:role/service-role"
            },
            "Action": [
                "ecr:BatchGetImage",
                "ecr:GetDownloadUrlForLayer"
            ]
        }
    ]
}
```

---

## 5. CI/CD 통합

### 5.1 GitHub Actions 통합

GitHub Actions를 통한 자동화된 빌드 및 푸시:

```yaml
name: Build and Push to ECR

on:
  push:
    branches: [ main ]

jobs:
  build:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v2
    
    - name: Configure AWS credentials
      uses: aws-actions/configure-aws-credentials@v1
      with:
        aws-access-key-id: ${{ secrets.AWS_ACCESS_KEY_ID }}
        aws-secret-access-key: ${{ secrets.AWS_SECRET_ACCESS_KEY }}
        aws-region: ap-northeast-2
    
    - name: Login to Amazon ECR
      id: login-ecr
      uses: aws-actions/amazon-ecr-login@v1
    
    - name: Build and push
      env:
        ECR_REGISTRY: ${{ steps.login-ecr.outputs.registry }}
        ECR_REPOSITORY: my-application
        IMAGE_TAG: ${{ github.sha }}
      run: |
        docker build -t $ECR_REGISTRY/$ECR_REPOSITORY:$IMAGE_TAG .
        docker push $ECR_REGISTRY/$ECR_REPOSITORY:$IMAGE_TAG
```

### 5.2 AWS CodeBuild 통합

buildspec.yml 설정 예시:

```yaml
version: 0.2

phases:
  pre_build:
    commands:
      - aws ecr get-login-password --region ap-northeast-2 | docker login --username AWS --password-stdin ${AWS_ACCOUNT_ID}.dkr.ecr.ap-northeast-2.amazonaws.com
      - REPOSITORY_URI=${AWS_ACCOUNT_ID}.dkr.ecr.ap-northeast-2.amazonaws.com/my-application
      - IMAGE_TAG=$(echo $CODEBUILD_RESOLVED_SOURCE_VERSION | cut -c 1-7)
  
  build:
    commands:
      - docker build -t $REPOSITORY_URI:$IMAGE_TAG .
  
  post_build:
    commands:
      - docker push $REPOSITORY_URI:$IMAGE_TAG
      - printf '{"ImageURI":"%s"}' $REPOSITORY_URI:$IMAGE_TAG > imageDefinitions.json

artifacts:
  files:
    - imageDefinitions.json
```

---

## 6. 모니터링 및 관리

### 6.1 CloudWatch 통합

ECR 이벤트 모니터링:

```bash
# CloudWatch 로그 그룹 생성
aws logs create-log-group --log-group-name /aws/ecr/repository

# 로그 스트림 생성
aws logs create-log-stream \
    --log-group-name /aws/ecr/repository \
    --log-stream-name repository-events
```

### 6.2 비용 최적화

이미지 관리 및 비용 최적화 전략:

1. 불필요한 이미지 정리를 위한 수명 주기 정책 설정
2. 이미지 레이어 재사용 최적화
3. 이미지 크기 최소화
4. 태그 전략 수립

---

## 7. 문제 해결

### 7.1 일반적인 문제 해결

자주 발생하는 문제들의 해결 방법:

1. 인증 오류
```bash
# 인증 토큰 갱신
aws ecr get-login-password --region region | docker login --username AWS --password-stdin aws_account_id.dkr.ecr.region.amazonaws.com
```

2. 푸시 실패
```bash
# 이미지 태그 확인
docker images

# 리포지토리 권한 확인
aws ecr get-repository-policy --repository-name repository-name
```

### 7.2 로깅 및 디버깅

```bash
# ECR API 호출 로그 확인
aws cloudtrail lookup-events --lookup-attributes AttributeKey=EventSource,AttributeValue=ecr.amazonaws.com
```

---

## 참고 자료

- [AWS ECR 공식 문서](https://docs.aws.amazon.com/ecr/)
- [AWS ECR API 레퍼런스](https://docs.aws.amazon.com/ecr/latest/APIReference/)
- [AWS ECR 모범 사례](https://docs.aws.amazon.com/ecr/latest/userguide/best-practices.html)

---

## 마무리

AWS ECR은 안전하고 확장 가능한 컨테이너 레지스트리 서비스를 제공합니다. 이 문서에서 다룬 내용을 바탕으로 ECR을 효과적으로 활용하여 컨테이너 이미지를 관리하고, CI/CD 파이프라인을 구축할 수 있습니다. 특히 AWS의 다른 서비스들과의 통합을 통해 완벽한 컨테이너 기반 애플리케이션 환경을 구성할 수 있습니다.