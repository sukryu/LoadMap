# 📂 AWS CloudFormation 학습 개요

> **목표:**  
> - **AWS CloudFormation을 활용하여 AWS 인프라를 자동화하는 방법을 학습**한다.  
> - **Infrastructure as Code(IaC) 개념을 적용하여 AWS 리소스를 코드로 정의하고 관리한다.**  
> - **기본 개념과 명령어를 학습한 후, 고급 기능 및 실무 활용 전략을 익힌다.**  
> - **이론 → 도구 실습 → 프로젝트 적용 → 최적화의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **AWS CloudFormation 학습을 기본(Basic)과 고급(Advanced)으로 나누어 진행합니다.**  

```
cloudformation/
├── introduction.md  # AWS CloudFormation 개요 및 기본 개념
├── setup.md         # CloudFormation 환경 설정
├── examples.md      # AWS 인프라 코드 예제
└── README.md
```

---

## 📖 **1. 기본 개념 개요**
> **AWS CloudFormation은 JSON 또는 YAML을 사용하여 AWS 인프라를 코드로 정의하고 배포할 수 있는 Infrastructure as Code(IaC) 솔루션입니다.**

- ✅ **Declarative Templates:** 리소스 상태를 JSON/YAML 파일로 정의하여 자동 배포  
- ✅ **Stacks:** AWS 리소스를 그룹화하여 효율적으로 관리  
- ✅ **Parameters:** 다양한 환경을 지원하기 위한 템플릿 매개변수 설정  
- ✅ **Change Sets:** 변경 사항을 미리 확인하고 안전하게 배포  
- ✅ **Drift Detection:** 배포된 리소스와 코드 간의 차이를 감지  

---

## 🏗 **2. 학습 내용**
### 📌 CloudFormation Setup (환경 설정)
- **AWS CLI 및 CloudFormation 설정**
- **CloudFormation 템플릿 기본 구조 이해**
- **템플릿 매개변수 및 출력(Output) 활용법 학습**

### 📌 AWS 리소스 배포 예제
- **AWS EC2 인스턴스 생성 및 관리**
- **AWS S3 버킷 생성 및 데이터 저장**
- **AWS VPC 및 서브넷 구성**
- **AWS RDS 데이터베이스 설정**

### 📌 CloudFormation 고급 활용법
- **Nested Stacks을 활용한 복잡한 배포 자동화**
- **CloudFormation과 AWS CodePipeline을 이용한 CI/CD 구축**
- **CloudFormation Drift Detection을 활용한 리소스 변경 감지**

---

## 🚀 **3. 실전 예제**
> **CloudFormation을 활용하여 AWS EC2 인스턴스를 배포하는 예제**

```yaml
AWSTemplateFormatVersion: "2010-09-09"
Resources:
  MyEC2Instance:
    Type: "AWS::EC2::Instance"
    Properties:
      InstanceType: "t2.micro"
      ImageId: "ami-0c55b159cbfafe1f0"
      Tags:
        - Key: "Name"
          Value: "CloudFormation-Instance"
```

```sh
# CloudFormation 스택 생성
aws cloudformation create-stack --stack-name myStack --template-body file://template.yaml

# 스택 상태 확인
aws cloudformation describe-stacks --stack-name myStack
```

---

## 🎯 **4. 학습 방법**
1. **이론 학습** → CloudFormation 개념과 템플릿 구조 이해  
2. **도구 실습** → AWS CLI 및 CloudFormation 활용하여 리소스 배포  
3. **프로젝트 적용** → 실제 프로젝트에서 CloudFormation 활용한 AWS 인프라 자동화  
4. **최적화 연구** → 성능, 보안, 비용 최적화 전략 연구  

---

## 📚 **5. 추천 리소스**
- **CloudFormation 공식 문서:**  
  - [CloudFormation Docs](https://docs.aws.amazon.com/AWSCloudFormation/latest/UserGuide/Welcome.html)  
  - [AWS CLI Docs](https://docs.aws.amazon.com/cli/latest/userguide/)  

- **CloudFormation 예제 및 템플릿:**  
  - [AWS CloudFormation Samples](https://github.com/awslabs/aws-cloudformation-templates)  
  - [Awesome CloudFormation](https://github.com/aws-cloudformation/aws-cloudformation-templates)  

---

## ✅ **마무리**
이 문서는 **AWS CloudFormation을 활용한 인프라 자동화의 기본 개념부터 실무 활용까지 학습하기 위한 로드맵**입니다.  
각 개념을 **이론 → 도구 실습 → 프로젝트 적용 → 최적화**의 단계로 학습하며, **실무에서 CloudFormation을 효과적으로 활용하는 방법**을 다룹니다. 🚀

