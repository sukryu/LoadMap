# Serverless Architecture

이 문서에서는 **서버리스 아키텍처**의 기본 개념과 특징, 발생할 수 있는 문제 상황 및 해결 방안, 실제 구현 방법과 베스트 프랙티스, 추가 고려 사항에 대해 다룹니다.

---

## 1. 개념 개요

서버리스 아키텍처는 애플리케이션의 인프라 관리 부담을 클라우드 서비스 제공자에게 위임하여, 개발자가 코드와 비즈니스 로직에 집중할 수 있도록 하는 설계 방식입니다.

- **정의:**  
  - 서버 관리 없이 클라우드 환경에서 함수를 기반으로 애플리케이션을 실행합니다.  
  - AWS Lambda, Google Cloud Functions, Azure Functions 등과 같이 이벤트 기반으로 동작하는 FaaS(Function as a Service)를 주로 활용합니다.

- **특징:**  
  - **자동 확장:**  
    - 트래픽에 따라 함수가 자동으로 확장되며, 리소스 할당을 클라우드 제공자가 관리합니다.
  - **비용 효율성:**  
    - 사용한 만큼만 비용을 지불하는 페이-퍼-유즈(pay-per-use) 모델로, 사용하지 않을 때는 비용이 발생하지 않습니다.
  - **인프라 관리 최소화:**  
    - 서버 운영, 패치, 스케일링 등의 인프라 관리를 클라우드 플랫폼에 맡기므로 개발자는 코드 작성에 집중할 수 있습니다.
  - **빠른 배포:**  
    - 함수 단위로 배포가 가능하여, 작은 기능 변경에도 전체 시스템 재배포 없이 빠르게 업데이트할 수 있습니다.

---

## 2. 문제 상황과 해결 방안

### 2.1. 문제 상황

- **콜드 스타트:**  
  - 함수가 처음 실행될 때 초기화 시간이 길어져 응답 지연이 발생할 수 있습니다.
  
- **상태 관리 어려움:**  
  - 서버리스 환경은 기본적으로 무상태(stateless)로 동작하므로, 상태를 유지해야 하는 애플리케이션에서는 별도의 상태 관리(예: 외부 데이터베이스, 캐시 등)가 필요합니다.
  
- **복잡한 모니터링 및 디버깅:**  
  - 분산된 함수 기반 구조로 인해 로그, 트레이싱, 오류 디버깅이 어려워질 수 있습니다.
  
- **제한된 실행 시간 및 리소스:**  
  - 각 함수는 실행 시간이나 메모리, CPU 등의 자원 제한이 있어, 장기 실행 작업에는 부적합할 수 있습니다.

### 2.2. 해결 방안

- **콜드 스타트 최적화:**  
  - 함수 크기를 최소화하고, 프로비저닝된 동시 실행(Provisioned Concurrency) 옵션을 활용하여 콜드 스타트 문제를 완화합니다.
  
- **상태 관리 전략:**  
  - 외부 데이터베이스, 캐시 서비스(Redis 등) 또는 이벤트 소싱 패턴을 통해 상태를 관리합니다.
  
- **관찰성과 모니터링 강화:**  
  - 클라우드 제공자의 로그, 트레이싱 서비스(예: AWS CloudWatch, X-Ray)와 통합하여 분산 환경에서의 모니터링과 디버깅 체계를 구축합니다.
  
- **작업 분할 및 함수 최적화:**  
  - 실행 시간이 긴 작업은 여러 개의 짧은 함수로 분할하거나, 비동기 작업 큐(예: AWS SQS, SNS)를 활용하여 처리합니다.

---

## 3. 구체적 구현 방법 및 베스트 프랙티스

### 3.1. 기본 디렉토리 구조 예시

아래는 Node.js와 AWS Lambda를 활용한 서버리스 애플리케이션의 예시 디렉토리 구조입니다.

```plaintext
serverless-app/
├── functions/                  # 각 기능별 Lambda 함수
│   ├── user/                  
│   │   ├── createUser.js       # 사용자 생성 함수
│   │   └── getUser.js          # 사용자 조회 함수
├── events/                     # 이벤트 트리거 정의 (예: API Gateway, S3 이벤트)
│   └── userEvent.json         
├── utils/                      # 공통 유틸리티 및 헬퍼 함수
│   └── dbClient.js             # 데이터베이스 클라이언트 (예: DynamoDB)
├── serverless.yml              # 서버리스 프레임워크 설정 파일
└── package.json
```

### 3.2. 코드 예시

#### functions/user/createUser.js

```javascript
const { v4: uuidv4 } = require('uuid');
const dbClient = require('../../utils/dbClient');

exports.handler = async (event) => {
  try {
    const body = JSON.parse(event.body);
    if (!body.name || !body.email) {
      return {
        statusCode: 400,
        body: JSON.stringify({ message: 'Invalid input data' }),
      };
    }
    const user = {
      id: uuidv4(),
      name: body.name,
      email: body.email,
      createdAt: new Date().toISOString(),
    };
    // 데이터베이스에 사용자 저장 (예: DynamoDB)
    await dbClient.put({
      TableName: process.env.USER_TABLE,
      Item: user,
    }).promise();
    
    return {
      statusCode: 201,
      body: JSON.stringify(user),
    };
  } catch (error) {
    return {
      statusCode: 500,
      body: JSON.stringify({ message: error.message }),
    };
  }
};
```

#### utils/dbClient.js

```javascript
const AWS = require('aws-sdk');
AWS.config.update({ region: process.env.AWS_REGION });

module.exports = new AWS.DynamoDB.DocumentClient();
```

#### serverless.yml (부분 예시)

```yaml
service: serverless-app

provider:
  name: aws
  runtime: nodejs14.x
  region: ap-northeast-2
  environment:
    USER_TABLE: UserTable

functions:
  createUser:
    handler: functions/user/createUser.handler
    events:
      - http:
          path: users
          method: post
```

### 베스트 프랙티스

- **함수 크기 최소화:**  
  - 각 Lambda 함수는 단일 책임을 갖도록 설계하여 코드 크기를 최소화하고, 초기화 시간을 단축합니다.
  
- **프로비저닝된 동시 실행 활용:**  
  - 콜드 스타트 문제를 완화하기 위해, 자주 호출되는 함수는 프로비저닝된 동시 실행 옵션을 사용합니다.
  
- **관찰성 도구 통합:**  
  - AWS CloudWatch, X-Ray 등의 모니터링 도구와 연동하여, 함수 실행 상태 및 오류를 실시간으로 추적합니다.
  
- **환경 변수 및 IAM 역할 관리:**  
  - 함수 간 보안과 권한 관리를 위해, 환경 변수와 최소 권한 원칙을 준수하는 IAM 역할을 사용합니다.
  
- **비동기 작업 큐 활용:**  
  - 장기 실행 작업이나 배치 처리의 경우, SQS/SNS와 같은 비동기 큐를 도입하여 처리 부하를 분산합니다.

---

## 4. 추가 고려 사항

- **보안:**  
  - API Gateway, Lambda 함수, 데이터베이스 등 각 컴포넌트에 대해 적절한 인증, 권한 부여, 암호화, 입력 검증 등의 보안 메커니즘을 적용합니다.
  
- **비용 관리:**  
  - 사용량 기반 과금 모델이므로, 함수 호출 빈도, 실행 시간, 리소스 사용량을 지속적으로 모니터링하여 비용 최적화를 진행합니다.
  
- **데이터 일관성:**  
  - 서버리스 환경은 무상태(stateless)로 동작하므로, 외부 스토어를 통한 상태 관리와 eventual consistency에 유의합니다.
  
- **서비스 통합:**  
  - 서버리스 아키텍처 내 다양한 서비스(API Gateway, Lambda, DynamoDB 등) 간의 통합을 원활하게 하기 위한 설계와 테스트가 필요합니다.

---

## 5. 결론

서버리스 아키텍처는 **인프라 관리 부담을 줄이고, 비용 효율성과 자동 확장을 실현**할 수 있는 설계 방식입니다.

- **장점:**  
  - 서버 관리 없이 코드를 실행할 수 있어 개발 생산성이 향상됩니다.  
  - 사용량에 따라 비용이 발생하므로, 비정기적인 트래픽에도 경제적입니다.  
  - 자동 확장 및 배포가 용이하여 빠른 개발 및 업데이트가 가능합니다.

- **단점:**  
  - 콜드 스타트, 무상태 처리, 모니터링 복잡성 등 새로운 문제 상황이 발생할 수 있습니다.  
  - 특정 실행 시간 및 리소스 제한으로 인해 장기 실행 작업에 적합하지 않을 수 있습니다.

따라서, 서버리스 아키텍처를 도입할 때는 위에서 언급한 베스트 프랙티스와 추가 고려 사항을 종합적으로 반영하여, 애플리케이션의 특성과 요구사항에 맞는 최적의 설계를 진행하는 것이 중요합니다.