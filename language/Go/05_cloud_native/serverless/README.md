# Serverless in Go: Build Scalable, Event-Driven Applications ☁️

이 디렉토리는 **서버리스 아키텍처**를 활용하여 Go 애플리케이션을 함수 단위로 개발, 배포 및 운영하는 방법을 다룹니다.  
AWS Lambda, Google Cloud Functions 등 다양한 서버리스 플랫폼에서 Go 코드를 실행하고, 이벤트 기반 처리 및 비용 효율적인 확장을 구현하는 전략과 실무 적용 사례를 학습할 수 있습니다.

---

## What You'll Learn 🎯

- **서버리스 개념 및 장점**:  
  - 서버리스의 기본 원리와 이벤트 기반 처리 방식 이해  
  - 인프라 관리 부담을 줄이고, 비용 효율성과 자동 확장을 달성하는 방법

- **Go 기반 서버리스 함수 개발**:  
  - Go로 작성한 함수 코드와 핸들러 구현  
  - AWS Lambda 등 주요 플랫폼에서 실행 가능한 서버리스 애플리케이션 작성

- **배포 및 운영 전략**:  
  - Serverless Framework, AWS SAM 또는 Google Cloud Functions CLI를 활용한 배포 자동화  
  - API Gateway 연동, 이벤트 트리거 설정, 모니터링 및 로깅 전략

- **최적화 및 베스트 프랙티스**:  
  - 콜드 스타트 최소화, 환경 변수 관리, 보안 설정 등 실제 운영 시 고려해야 할 사항

---

## Directory Structure 📁

```plaintext
05-cloud-native/
└── serverless/
    ├── main.go           # 간단한 서버리스 함수 예제
    ├── handler.go        # 이벤트 핸들러 및 로직 구현
    ├── template.yaml     # (선택 사항) AWS SAM 또는 Serverless Framework 구성 파일
    └── README.md         # 이 문서
```

- **main.go / handler.go**:  
  - Go로 작성된 서버리스 함수의 기본 코드 예제가 포함되어 있습니다.
- **template.yaml**:  
  - AWS Lambda 배포를 위한 SAM 템플릿 또는 Serverless Framework 설정 파일을 포함할 수 있습니다.

---

## Getting Started 🚀

### 1. 필수 도구 설치
- **Go 최신 버전**: [Download Go](https://go.dev/dl/)
- **서버리스 플랫폼 CLI**:  
  - AWS CLI 및 AWS SAM CLI 또는 Serverless Framework (예: `npm install -g serverless`)
- **Docker** (로컬 테스트 시, 컨테이너 기반 에뮬레이션)

### 2. 프로젝트 클론 및 디렉토리 이동
```bash
git clone https://github.com/your-username/go-backend-roadmap.git
cd go-backend-roadmap/05-cloud-native/serverless
```

### 3. 예제 코드 실행 (로컬 테스트)
- **AWS SAM CLI 사용 예시**:
  ```bash
  sam build
  sam local invoke -e event.json
  ```
- **Serverless Framework 사용 예시**:
  ```bash
  serverless deploy
  ```
  - 배포 후, API Gateway URL을 통해 함수 호출 결과를 확인하세요.

---

## Example Code Snippet 📄

아래는 간단한 AWS Lambda 함수 예제입니다.

**handler.go**
```go
package main

import (
    "context"
    "fmt"
)

// Handler is the entry point for the AWS Lambda function.
func Handler(ctx context.Context, event map[string]interface{}) (string, error) {
    // 예시: 이벤트에서 "name" 값을 읽고 인사 메시지 반환
    name, ok := event["name"].(string)
    if !ok || name == "" {
        name = "Gopher"
    }
    message := fmt.Sprintf("Hello, %s! Welcome to Serverless with Go.", name)
    return message, nil
}
```

**main.go**
```go
package main

import (
    "github.com/aws/aws-lambda-go/lambda"
)

func main() {
    // AWS Lambda에서 실행될 핸들러 등록
    lambda.Start(Handler)
}
```

이 예제는 AWS Lambda 환경에서 동작하며, 이벤트 객체로부터 "name" 값을 받아 인사 메시지를 반환합니다.

---

## Best Practices & Tips 💡

- **콜드 스타트 최적화**:  
  - 함수 크기를 최소화하고, 의존성을 경량화하여 콜드 스타트 시간을 줄이세요.
  
- **환경 변수 관리**:  
  - 민감 정보와 설정 값은 환경 변수를 통해 관리하고, Secrets Manager와 같은 도구로 보안을 강화하세요.
  
- **로깅 및 모니터링**:  
  - CloudWatch, Stackdriver 등 클라우드 모니터링 도구를 연동하여, 함수 실행 상태와 성능을 주기적으로 점검하세요.
  
- **테스트 및 배포 자동화**:  
  - CI/CD 파이프라인에 서버리스 함수의 테스트와 배포 단계를 포함시켜, 지속적인 업데이트와 안정적인 운영을 도모하세요.
  
- **API Gateway 연동**:  
  - REST API와 연동하여, HTTP 요청을 통해 서버리스 함수를 호출하고, 인증/인가, 캐싱 등의 기능을 중앙 집중식으로 관리하세요.

---

## Next Steps

- **고급 기능 학습**:  
  - 이벤트 소싱, 함수 체이닝, 비동기 이벤트 처리, 그리고 다른 트리거(예: S3, DynamoDB Streams)와의 연동을 실습해 보세요.
- **실무 적용**:  
  - Go로 작성한 서버리스 함수를 실제 마이크로서비스 아키텍처에 통합하고, 모니터링 및 로깅 체계를 구성해 보세요.
- **배포 전략**:  
  - Blue/Green 배포나 Canary 배포 전략을 적용하여, 함수 업데이트 시 무중단 배포를 실현해 보세요.

---

## References 📚

- [AWS Lambda Go Documentation](https://docs.aws.amazon.com/lambda/latest/dg/golang-handler.html)
- [Serverless Framework Documentation](https://www.serverless.com/framework/docs/)
- [AWS SAM CLI Documentation](https://docs.aws.amazon.com/serverless-application-model/latest/developerguide/what-is-sam.html)
- [Google Cloud Functions Go Documentation](https://cloud.google.com/functions/docs/writing#go)
- [Go Official Documentation](https://golang.org/doc/)

---

서버리스 아키텍처는 인프라 관리 부담을 줄이고, 비용 효율적이며 확장 가능한 애플리케이션을 구축할 수 있는 강력한 방법입니다.  
이 자료를 통해 Go 기반 서버리스 함수를 작성하고, 실제 환경에 배포하여 운영 자동화를 실현해 보세요! Happy Serverless Coding! ☁️🚀