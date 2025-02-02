# 미디에이터 패턴

> **목표:**  
> - 여러 객체 간의 직접적인 통신을 피하고, 중앙 집중식 통신 채널(미디에이터)을 제공하여 객체 간 결합도를 낮춘다.  
> - 객체들이 서로를 직접 참조하지 않고, 미디에이터를 통해 상호작용함으로써, 시스템의 유연성과 확장성을 향상시킨다.  
> - 복잡한 상호작용 로직을 한 곳에 집중시켜, 코드의 가독성과 유지보수성을 높인다.

---

## 1. 개념 개요

- **정의:**  
  미디에이터 패턴은 객체들 간의 복잡한 통신을 중앙의 미디에이터 객체로 캡슐화하여, 각 객체들이 서로 직접 통신하지 않고 미디에이터와만 상호작용하도록 만드는 디자인 패턴입니다.  
  이를 통해 객체들 간의 의존 관계를 줄이고, 각 객체의 역할과 책임을 명확하게 분리할 수 있습니다.

- **왜 중요한가?**  
  - **결합도 감소:**  
    객체들이 직접 서로를 참조하는 대신 미디에이터를 통해 통신하므로, 개별 객체의 변경이 다른 객체에 미치는 영향을 최소화합니다.  
  - **중앙 집중식 제어:**  
    복잡한 상호작용 로직을 미디에이터에 집중시켜, 시스템 전체의 동작을 한 눈에 파악하고 관리할 수 있습니다.  
  - **유연한 확장:**  
    새로운 객체가 추가되거나 기존 객체가 변경되어도, 미디에이터만 적절히 수정하면 전체 시스템에 미치는 영향을 줄일 수 있습니다.

- **해결하는 문제:**  
  - 객체들 간의 직접적인 통신으로 인한 강한 결합도를 해소하여, 시스템의 유지보수 및 확장이 용이하게 합니다.  
  - 복잡한 다대다 통신 구조를 단순화하여, 객체들 간의 상호작용을 효율적으로 관리할 수 있도록 돕습니다.

---

## 2. 실무 적용 사례

- **UI 이벤트 처리:**  
  - 다양한 UI 컴포넌트(버튼, 입력 필드, 팝업 등)가 서로 직접 통신하는 대신, 중앙의 미디에이터(예: 이벤트 버스나 컨트롤러)를 통해 상호작용함으로써, 컴포넌트 간 결합도를 낮춥니다.

- **채팅 시스템:**  
  - 사용자(Colleague)들이 직접 서로에게 메시지를 보내지 않고, 채팅 방(미디에이터)을 통해 메시지를 주고받는 구조로, 각 사용자 간의 의존성을 줄입니다.

- **프로세스 조정:**  
  - 여러 독립적인 모듈이나 서비스가 중앙의 조정자(미디에이터)를 통해 협력하여 작업을 수행함으로써, 모듈 간의 복잡한 상호작용을 단순화합니다.

---

## 3. 구현 방법

아래 예제는 TypeScript를 사용하여 미디에이터 패턴을 구현하는 방법을 보여줍니다.  
예제에서는 간단한 채팅 시스템을 통해, 여러 참가자(Colleague)가 중앙 미디에이터(ChatRoom)를 통해 메시지를 주고받는 구조를 구현합니다.

### 3.1 미디에이터 인터페이스 및 구체 클래스

#### **1) 미디에이터 인터페이스 정의**

```typescript
// Mediator.ts
export interface Mediator {
  sendMessage(message: string, sender: Colleague): void;
}
```

#### **2) 동료(Colleague) 인터페이스 및 추상 클래스 정의**

```typescript
// Colleague.ts
import { Mediator } from './Mediator';

export abstract class Colleague {
  protected mediator: Mediator;
  protected name: string;

  constructor(name: string, mediator: Mediator) {
    this.name = name;
    this.mediator = mediator;
  }

  public abstract receive(message: string): void;

  public send(message: string): void {
    console.log(`${this.name}가 메시지 전송: ${message}`);
    this.mediator.sendMessage(message, this);
  }
}
```

#### **3) 구체적인 동료 클래스 구현**

```typescript
// ChatUser.ts
import { Colleague } from './Colleague';

export class ChatUser extends Colleague {
  public receive(message: string): void {
    console.log(`${this.name}가 메시지 수신: ${message}`);
  }
}
```

#### **4) 구체적인 미디에이터 클래스 구현 (채팅 방)**

```typescript
// ChatRoom.ts
import { Mediator } from './Mediator';
import { Colleague } from './Colleague';

export class ChatRoom implements Mediator {
  private participants: Colleague[] = [];

  public register(colleague: Colleague): void {
    this.participants.push(colleague);
    console.log(`${colleague['name']}가 채팅방에 등록되었습니다.`);
  }

  public sendMessage(message: string, sender: Colleague): void {
    for (const participant of this.participants) {
      // 보낸 사람은 메시지를 수신하지 않도록 처리
      if (participant !== sender) {
        participant.receive(message);
      }
    }
  }
}
```

### 3.2 클라이언트 코드 예시

```typescript
// client.ts
import { ChatRoom } from './ChatRoom';
import { ChatUser } from './ChatUser';

const chatRoom = new ChatRoom();

const userAlice = new ChatUser("Alice", chatRoom);
const userBob = new ChatUser("Bob", chatRoom);
const userCharlie = new ChatUser("Charlie", chatRoom);

chatRoom.register(userAlice);
chatRoom.register(userBob);
chatRoom.register(userCharlie);

userAlice.send("안녕하세요, 여러분!");
userBob.send("안녕하세요, Alice!");
userCharlie.send("모두 반갑습니다!");

// 출력 예시:
// Alice가 메시지 전송: 안녕하세요, 여러분!
// Bob가 메시지 수신: 안녕하세요, 여러분!
// Charlie가 메시지 수신: 안녕하세요, 여러분!
// Bob가 메시지 전송: 안녕하세요, Alice!
// Alice가 메시지 수신: 안녕하세요, Alice!
// Charlie가 메시지 수신: 안녕하세요, Alice!
// Charlie가 메시지 전송: 모두 반갑습니다!
// Alice가 메시지 수신: 모두 반갑습니다!
// Bob가 메시지 수신: 모두 반갑습니다!
```

- **구현 포인트:**  
  - **중앙 집중식 통신:** 각 동료(Colleague)는 직접 서로에게 메시지를 보내지 않고, 미디에이터(ChatRoom)를 통해 메시지를 주고받습니다.  
  - **유연한 확장:** 새로운 동료가 추가되어도 미디에이터 인터페이스만 따르므로, 전체 시스템에 미치는 영향을 최소화할 수 있습니다.

---

## 4. 장단점 및 고려 사항

### 장점
- **결합도 감소:**  
  - 동료 객체들끼리 직접 통신하지 않고, 미디에이터를 통해 간접적으로 상호작용하므로, 객체 간 결합도가 크게 낮아집니다.
  
- **중앙 집중식 제어:**  
  - 시스템 내 복잡한 상호작용 로직을 미디에이터에 집중시켜, 전체 흐름을 한눈에 파악하고 관리할 수 있습니다.
  
- **유연한 확장:**  
  - 새로운 객체가 추가되거나 변경되어도 미디에이터만 적절히 수정하면 되므로, 시스템 확장이 용이합니다.

### 단점
- **중앙 집중화에 따른 복잡성:**  
  - 미디에이터가 너무 많은 역할을 맡게 되면, 미디에이터 자체의 구현이 복잡해지고 유지보수가 어려워질 수 있습니다.
  
- **성능 문제:**  
  - 모든 통신이 미디에이터를 거치므로, 동시성이 매우 높은 시스템에서는 성능 오버헤드가 발생할 수 있습니다.

### 추가 고려 사항
- **역할 분리:**  
  - 미디에이터가 시스템 전체의 모든 책임을 지지 않도록, 역할을 적절히 분리하고 서브 미디에이터를 도입하는 방안을 고려할 수 있습니다.
  
- **테스트:**  
  - 미디에이터와 동료 객체들 간의 상호작용을 단위 테스트 및 통합 테스트를 통해 철저히 검증해야 합니다.
  
- **확장성:**  
  - 새로운 동료 객체 추가나 통신 로직 변경 시 미디에이터 인터페이스를 유지하는 것이 중요하며, 이를 통해 시스템의 일관성을 보장할 수 있습니다.

---

## 5. 참고 자료

- [Refactoring Guru - Mediator Pattern](https://refactoring.guru/design-patterns/mediator)  
- _Design Patterns: Elements of Reusable Object-Oriented Software_ - Erich Gamma 외  
- _Head First Design Patterns_ - Eric Freeman

---

## 마무리

미디에이터 패턴은 객체들 간의 복잡한 상호작용을 중앙 집중식 미디에이터를 통해 관리함으로써, 결합도를 낮추고 시스템의 유연성과 확장성을 높이는 강력한 설계 기법입니다.  
실제 프로젝트에서는 UI 이벤트 처리, 채팅 시스템, 모듈 간 협력 등 다양한 시나리오에서 미디에이터 패턴을 활용하여 유지보수성과 확장성이 뛰어난 아키텍처를 구축할 수 있습니다.