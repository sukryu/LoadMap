# 책임 연쇄 패턴

> **목표:**  
> - 요청을 처리할 수 있는 여러 객체들을 연결하여, 클라이언트가 특정 처리자에 직접 의존하지 않고 요청을 전달할 수 있도록 한다.  
> - 요청이 체인 상의 여러 핸들러를 거치면서 적절한 객체가 처리하도록 함으로써, 결합도를 낮추고 확장성을 확보한다.  
> - 각 핸들러는 자신이 처리할 수 있는 요청만 처리하고, 그렇지 않은 경우 다음 핸들러에게 위임함으로써 유연한 요청 처리가 가능하다.

---

## 1. 개념 개요

- **정의:**  
  책임 연쇄 패턴은 요청을 처리할 수 있는 여러 객체(핸들러)를 연결한 체인(Chain)을 구성하고, 클라이언트의 요청을 체인의 시작점에 전달하여 순차적으로 처리하는 디자인 패턴입니다.  
  각 핸들러는 자신이 처리할 수 있는 요청이면 처리하고, 그렇지 않으면 체인의 다음 핸들러에게 요청을 전달합니다.

- **왜 중요한가?**  
  - **결합도 감소:** 클라이언트는 특정 핸들러에 직접 의존하지 않고, 체인을 통해 요청을 전달할 수 있으므로 시스템의 결합도가 낮아집니다.  
  - **유연성:** 새로운 핸들러를 추가하거나 기존 핸들러의 순서를 변경하는 등, 체인의 구성을 동적으로 조정할 수 있어 확장이 용이합니다.  
  - **책임 분산:** 요청 처리 책임을 여러 객체에 분산시켜, 각 객체가 자신의 역할에 집중할 수 있도록 합니다.

- **해결하는 문제:**  
  - 복잡한 조건문이나 if-else 블록을 사용하여 요청을 처리하는 대신, 요청을 적절한 객체에 위임함으로써 코드의 가독성과 유지보수성을 향상시킵니다.

---

## 2. 실무 적용 사례

- **승인 체계:**  
  - 예를 들어, 휴가 요청이나 비용 청구 등의 승인 프로세스에서 요청 금액이나 요청 유형에 따라 팀 리더, 매니저, 부장 등 서로 다른 권한을 가진 관리자가 순차적으로 승인 여부를 결정할 수 있습니다.

- **에러 처리:**  
  - 다양한 오류 상황에 대해 여러 처리 객체(로거, 재시도, 사용자 알림 등)가 순차적으로 오류를 처리하도록 할 때 활용됩니다.

- **이벤트 처리:**  
  - 사용자 인터페이스(UI)나 시스템 이벤트를 처리할 때, 이벤트 발생 후 이를 처리할 수 있는 여러 객체가 순차적으로 이벤트를 처리하도록 구성할 수 있습니다.

---

## 3. 구현 방법

아래 예제는 TypeScript를 사용하여 **휴가 요청 승인** 프로세스를 책임 연쇄 패턴으로 구현한 예시입니다.  
요청 금액에 따라 팀 리더, 매니저, 부장이 순차적으로 요청을 처리하는 구조를 보여줍니다.

### 3.1 인터페이스 및 추상 핸들러 정의

```typescript
// Handler.ts
export interface Handler {
  // 다음 핸들러를 설정하고 반환
  setNext(handler: Handler): Handler;

  // 요청을 처리하는 메서드. 처리할 수 없으면 체인의 다음 핸들러로 전달.
  handle(request: number): string;
}
```

```typescript
// AbstractHandler.ts
import { Handler } from "./Handler";

export abstract class AbstractHandler implements Handler {
  private nextHandler: Handler;

  public setNext(handler: Handler): Handler {
    this.nextHandler = handler;
    return handler;
  }

  public handle(request: number): string {
    if (this.nextHandler) {
      return this.nextHandler.handle(request);
    }
    return `요청 금액 ${request}원에 대해 처리할 핸들러가 없습니다.`;
  }
}
```

### 3.2 구체적인 핸들러 구현

```typescript
// TeamLeader.ts
import { AbstractHandler } from "./AbstractHandler";

export class TeamLeader extends AbstractHandler {
  public handle(request: number): string {
    if (request <= 1000) {
      return `팀 리더가 요청 금액 ${request}원 승인`;
    }
    return super.handle(request);
  }
}
```

```typescript
// Manager.ts
import { AbstractHandler } from "./AbstractHandler";

export class Manager extends AbstractHandler {
  public handle(request: number): string {
    if (request <= 5000) {
      return `매니저가 요청 금액 ${request}원 승인`;
    }
    return super.handle(request);
  }
}
```

```typescript
// Director.ts
import { AbstractHandler } from "./AbstractHandler";

export class Director extends AbstractHandler {
  public handle(request: number): string {
    if (request <= 10000) {
      return `부장이 요청 금액 ${request}원 승인`;
    }
    return super.handle(request);
  }
}
```

### 3.3 클라이언트 코드 예시

```typescript
// client.ts
import { TeamLeader } from "./TeamLeader";
import { Manager } from "./Manager";
import { Director } from "./Director";

// 각 핸들러 생성
const teamLeader = new TeamLeader();
const manager = new Manager();
const director = new Director();

// 체인 구성: 팀 리더 -> 매니저 -> 부장
teamLeader.setNext(manager).setNext(director);

// 다양한 요청에 대해 처리 결과 출력
const requests = [500, 2000, 7000, 15000];
for (const request of requests) {
  console.log(`요청 금액: ${request}원 -> ${teamLeader.handle(request)}`);
}

// 출력 예시:
// 요청 금액: 500원 -> 팀 리더가 요청 금액 500원 승인
// 요청 금액: 2000원 -> 매니저가 요청 금액 2000원 승인
// 요청 금액: 7000원 -> 부장이 요청 금액 7000원 승인
// 요청 금액: 15000원 -> 요청 금액 15000원에 대해 처리할 핸들러가 없습니다.
```

- **구현 포인트:**  
  - **인터페이스와 추상 클래스:** `Handler` 인터페이스와 `AbstractHandler`를 통해 공통 동작(다음 핸들러로 위임)을 정의하여 중복 코드를 줄입니다.  
  - **구체 핸들러:** 각 핸들러는 자신이 처리할 수 있는 조건(여기서는 요청 금액 범위)을 판단한 후, 처리할 수 없으면 체인의 다음 핸들러에게 위임합니다.  
  - **체인 구성:** 클라이언트는 체인 구성(팀 리더 → 매니저 → 부장)을 통해 요청이 적절한 핸들러에 도달하도록 합니다.

---

## 4. 장단점 및 고려 사항

### 장점
- **결합도 감소:**  
  - 클라이언트는 특정 핸들러에 직접 의존하지 않고, 체인 전체에 요청을 전달할 수 있어 결합도가 낮습니다.
  
- **유연한 확장:**  
  - 새로운 핸들러를 체인에 추가하거나 순서를 변경하는 것이 용이하여, 시스템 확장이 쉽습니다.
  
- **책임 분산:**  
  - 각 핸들러가 자신이 처리할 수 있는 범위를 담당함으로써, 단일 클래스에 과도한 책임이 집중되는 것을 방지합니다.

### 단점
- **처리 결과 예측 어려움:**  
  - 요청이 체인의 어디에서 처리될지 명확하지 않아, 디버깅 및 테스트 시 혼란이 발생할 수 있습니다.
  
- **체인 관리 복잡성:**  
  - 체인의 길이가 길어질 경우, 관리 및 유지보수가 어려워질 수 있습니다.
  
- **순서 의존성:**  
  - 핸들러의 순서에 따라 처리 결과가 달라질 수 있으므로, 체인 구성이 신중하게 이루어져야 합니다.

### 추가 고려 사항
- **테스트 전략:**  
  - 각 핸들러의 조건 및 체인 전체 동작을 단위 테스트와 통합 테스트로 검증하여, 예상치 못한 요청 누락이나 중복 처리를 방지합니다.
  
- **동시성:**  
  - 멀티스레드 환경에서는 핸들러 체인의 상태 관리나 요청 전달에 대한 동기화가 필요할 수 있습니다.
  
- **실제 업무 요구사항 반영:**  
  - 요청의 특성과 처리 조건을 실제 업무 로직에 맞게 설계하여, 체인 구조가 복잡해지지 않도록 주의합니다.

---

## 5. 참고 자료

- [Refactoring Guru - Chain of Responsibility Pattern](https://refactoring.guru/design-patterns/chain-of-responsibility)  
- _Design Patterns: Elements of Reusable Object-Oriented Software_ - Erich Gamma 외  
- _Head First Design Patterns_ - Eric Freeman

---

## 마무리

책임 연쇄 패턴은 요청 처리 책임을 여러 핸들러에 분산시켜 결합도를 낮추고 확장성을 높이는 효과적인 설계 기법입니다.  
실제 프로젝트에서는 승인 체계, 에러 처리, 이벤트 처리 등 다양한 시나리오에 적용하여, 복잡한 조건문을 제거하고 유연한 요청 처리를 구현할 수 있습니다.