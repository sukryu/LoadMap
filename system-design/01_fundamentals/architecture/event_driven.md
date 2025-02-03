# Event-Driven Architecture

이 문서에서는 **이벤트 드리븐 아키텍처**의 개념과 특징, 발생할 수 있는 문제 상황 및 해결 방안, 실제 구현 방법과 베스트 프랙티스, 그리고 추가 고려 사항을 다룹니다.

---

## 1. 개념 개요

이벤트 드리븐 아키텍처는 애플리케이션 구성 요소들이 **이벤트(사건)**를 통해 느슨하게 결합되어 상호작용하는 설계 방식입니다.

- **정의:**  
  - 시스템의 구성 요소들이 특정 이벤트가 발생할 때마다 이를 감지(Subscribe)하고, 이벤트 발생 후 처리(Publish)하는 방식으로 동작합니다.
  - 이벤트는 데이터 변경, 사용자 액션, 시스템 상태 변화 등을 의미하며, 비동기적으로 전달됩니다.

- **특징:**  
  - **비동기 통신:**  
    - 이벤트를 통해 구성 요소 간 통신이 이루어지므로, 요청-응답 방식보다 느슨한 결합(loose coupling)이 가능하며, 시스템 확장성과 유연성이 높습니다.
  - **확장성:**  
    - 이벤트 큐나 메시지 브로커(예: Kafka, RabbitMQ)를 활용하여, 대량의 이벤트를 효율적으로 처리할 수 있습니다.
  - **실시간 처리:**  
    - 이벤트를 즉각적으로 처리하거나, 배치 처리하는 방식으로 실시간 데이터 분석, 알림 서비스 등에 활용됩니다.
  - **내결함성:**  
    - 구성 요소가 독립적으로 동작하므로, 한 서비스의 장애가 전체 시스템에 미치는 영향을 최소화할 수 있습니다.

---

## 2. 문제 상황과 해결 방안

### 2.1. 문제 상황

- **동기화와 일관성 문제:**  
  - 구성 요소들이 비동기적으로 작동함에 따라, 이벤트 순서 보장과 데이터 일관성 유지에 어려움이 발생할 수 있습니다.
  
- **복잡한 이벤트 흐름:**  
  - 이벤트의 생성, 전파, 처리 경로가 복잡해지면 시스템의 흐름을 추적하고 디버깅하는 데 어려움이 있습니다.
  
- **장애 처리:**  
  - 메시지 큐나 브로커 장애, 이벤트 처리 실패 등이 발생할 경우 재시도 및 복구 메커니즘이 필요합니다.

### 2.2. 해결 방안

- **이벤트 순서 보장 메커니즘:**  
  - 메시지 브로커의 파티셔닝 및 키 기반 라우팅을 활용하여, 관련 이벤트의 순서를 보장합니다.
  
- **내결함성 설계:**  
  - 장애 발생 시 재시도 로직, 데드레터 큐(dead-letter queue) 등을 도입하여, 이벤트 손실 없이 안정적인 처리를 보장합니다.
  
- **관찰성과 모니터링 강화:**  
  - 이벤트 흐름과 처리 상태를 추적할 수 있는 로깅 및 모니터링 시스템(예: ELK, Prometheus, Grafana)을 구축하여 문제 상황을 빠르게 인지하고 대응합니다.

---

## 3. 구체적 구현 방법 및 베스트 프랙티스

### 3.1. 기본 디렉토리 구조 예시

아래는 Node.js를 기반으로 이벤트 드리븐 아키텍처를 구현한 간단한 서비스 예시입니다.

```plaintext
event-driven-app/
├── events/                 # 이벤트 메시지 정의 및 이벤트 처리 로직
│   ├── eventTypes.js       # 이벤트 타입 상수 정의
│   └── eventHandler.js     # 이벤트 처리 함수들
├── publishers/             # 이벤트를 발생시키는 모듈
│   └── userPublisher.js    # 사용자 관련 이벤트 발행 로직
├── subscribers/            # 이벤트를 구독하는 모듈
│   └── userSubscriber.js   # 사용자 관련 이벤트 구독 및 처리
├── utils/                  # 메시지 브로커 유틸리티 (예: Kafka/RabbitMQ 클라이언트)
├── app.js                  # 애플리케이션 초기화 및 이벤트 브로커 연결 설정
└── package.json
```

### 3.2. 코드 예시

#### events/eventTypes.js

```javascript
// 이벤트 타입 상수 정의
module.exports = {
  USER_CREATED: 'USER_CREATED',
  USER_UPDATED: 'USER_UPDATED',
  // 추가 이벤트 타입 정의...
};
```

#### publishers/userPublisher.js

```javascript
const eventTypes = require('../events/eventTypes');
const broker = require('../utils/messageBroker');

// 사용자 생성 이벤트 발행 예시
const publishUserCreated = async (userData) => {
  const event = {
    type: eventTypes.USER_CREATED,
    payload: userData,
    timestamp: new Date(),
  };

  await broker.publish(event);
  console.log('User created event published:', event);
};

module.exports = { publishUserCreated };
```

#### subscribers/userSubscriber.js

```javascript
const eventTypes = require('../events/eventTypes');

// 사용자 생성 이벤트 처리 함수
const handleUserCreated = (event) => {
  console.log('Handling user created event:', event);
  // 이벤트 처리 로직 구현...
};

const subscribeToUserEvents = (broker) => {
  broker.subscribe(eventTypes.USER_CREATED, handleUserCreated);
};

module.exports = { subscribeToUserEvents };
```

#### utils/messageBroker.js

```javascript
// 단순화된 메시지 브로커 모의 구현 (실제 환경에서는 Kafka, RabbitMQ 등 사용)
class MessageBroker {
  constructor() {
    this.subscribers = {};
  }

  async publish(event) {
    const handlers = this.subscribers[event.type] || [];
    handlers.forEach(handler => handler(event));
  }

  subscribe(eventType, handler) {
    if (!this.subscribers[eventType]) {
      this.subscribers[eventType] = [];
    }
    this.subscribers[eventType].push(handler);
    console.log(`Subscribed to event type: ${eventType}`);
  }
}

module.exports = new MessageBroker();
```

#### app.js

```javascript
const broker = require('./utils/messageBroker');
const { subscribeToUserEvents } = require('./subscribers/userSubscriber');
const { publishUserCreated } = require('./publishers/userPublisher');

// 애플리케이션 초기화
const startApp = () => {
  // 이벤트 구독 설정
  subscribeToUserEvents(broker);

  // 예시: 사용자 생성 이벤트 발행
  const sampleUser = { id: '1', name: 'Alice', email: 'alice@example.com' };
  publishUserCreated(sampleUser);
};

startApp();
```

### 베스트 프랙티스

- **이벤트 스키마 정의 및 버전 관리:**  
  - 이벤트 메시지의 구조를 명확히 정의하고, 변경 시 버전 관리를 통해 하위 호환성을 유지합니다.
  
- **내결함성 및 재시도 로직 도입:**  
  - 이벤트 처리 실패 시 재시도 로직과 데드레터 큐를 활용하여, 데이터 손실 없이 안정적인 이벤트 처리를 구현합니다.
  
- **관찰성 강화:**  
  - 이벤트 흐름, 처리 상태, 실패 이벤트를 모니터링할 수 있는 로깅 및 대시보드 시스템을 구축합니다.
  
- **확장성과 독립성 유지:**  
  - 각 이벤트 핸들러는 독립적으로 동작하도록 설계하여, 특정 핸들러의 장애가 전체 시스템에 영향을 주지 않도록 합니다.

---

## 4. 추가 고려 사항

- **이벤트 순서 및 일관성:**  
  - 파티셔닝, 키 기반 라우팅 등으로 이벤트 순서를 보장할 필요가 있으며, 최종적 일관성(eventual consistency) 메커니즘을 도입합니다.
  
- **서비스 간 결합도 관리:**  
  - 이벤트 기반 통신은 구성 요소 간 결합을 낮추지만, 이벤트 스키마에 대한 의존성이 발생할 수 있으므로, 이를 문서화하고 버전 관리를 철저히 합니다.
  
- **보안:**  
  - 이벤트 메시지 암호화, 인증, 권한 관리를 통해, 민감한 데이터가 외부로 노출되지 않도록 합니다.
  
- **모니터링 및 로깅:**  
  - 전체 이벤트 흐름을 추적할 수 있는 관찰성 도구를 도입하여, 장애 발생 시 신속하게 대응할 수 있도록 합니다.

---

## 5. 결론

이벤트 드리븐 아키텍처는 **비동기 통신**과 **느슨한 결합**을 통해 확장성, 유연성, 내결함성을 극대화할 수 있는 설계 방식입니다.

- **장점:**  
  - 구성 요소 간의 느슨한 결합으로 독립적 배포 및 확장이 용이합니다.
  - 비동기 처리로 높은 처리량과 실시간 데이터 분석, 이벤트 기반 알림 서비스 등 다양한 응용 분야에 적합합니다.
  - 장애 격리 및 복구 전략 도입 시, 내결함성이 향상됩니다.

- **단점:**  
  - 이벤트 순서 보장, 데이터 일관성 유지, 복잡한 이벤트 흐름 관리 등 추가적인 설계 및 운영 부담이 발생할 수 있습니다.
  - 장애 발생 시 이벤트 재처리 및 복구 메커니즘이 필요하여 구현 복잡도가 증가할 수 있습니다.

따라서, 이벤트 드리븐 아키텍처를 도입할 때는 위에서 언급한 베스트 프랙티스와 추가 고려 사항을 종합적으로 반영하여, 시스템의 요구사항과 특성에 맞는 설계를 진행하는 것이 중요합니다.