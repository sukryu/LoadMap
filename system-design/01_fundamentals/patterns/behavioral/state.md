# 상태 패턴

> **목표:**  
> - 객체의 내부 상태에 따라 행동을 변경할 수 있도록 하여, 복잡한 조건문 없이 상태 전환에 따른 동작을 캡슐화한다.  
> - 각 상태를 별도의 클래스(또는 객체)로 분리하여 코드의 가독성과 유지보수성을 향상시킨다.  
> - 상태 변화에 따른 동적 행동 변경을 손쉽게 구현할 수 있도록 한다.

---

## 1. 개념 개요

- **정의:**  
  상태 패턴은 객체의 내부 상태를 캡슐화하여, 상태가 변화할 때마다 해당 상태에 맞는 행동(메서드)을 실행하도록 하는 디자인 패턴입니다.  
  즉, 객체의 행동을 상태 객체에 위임함으로써, 조건문(if/else, switch 등)을 줄이고 각 상태별로 독립적인 로직을 구현할 수 있습니다.

- **왜 중요한가?**  
  - **조건문 제거:** 상태에 따른 복잡한 조건문 대신, 각 상태를 별도의 클래스로 분리하여 관리하면 코드가 간결해지고 유지보수가 쉬워집니다.  
  - **유연한 확장:** 새로운 상태를 추가하거나 기존 상태를 수정할 때, 다른 상태에 영향을 주지 않고 독립적으로 변경할 수 있습니다.  
  - **행동 캡슐화:** 상태에 따른 행동을 각 상태 클래스 내부에 구현하여, 객체의 동작을 명확하게 분리할 수 있습니다.

- **해결하는 문제:**  
  - 객체가 여러 상태를 가지며, 각 상태마다 수행해야 할 행동이 다를 때, 이를 조건문으로 처리하면 코드가 복잡해집니다.  
  - 상태 전환 로직을 독립된 클래스로 분리하여, 상태 변화에 따른 행동 변경을 보다 명확하게 관리할 수 있습니다.

---

## 2. 실무 적용 사례

- **TCP 연결 관리:**  
  - TCP 연결 객체는 연결, 종료, 대기 등 여러 상태를 가지며, 각 상태에 따라 데이터 전송, 연결 재시도 등의 행동이 달라집니다.
  
- **UI 컴포넌트 상태:**  
  - 버튼이나 폼 등 UI 컴포넌트는 활성화, 비활성화, 로딩 등의 상태를 가지며, 상태에 따라 이벤트 처리나 스타일 변경이 이루어집니다.
  
- **게임 캐릭터 행동:**  
  - 게임 캐릭터는 평상시, 공격, 방어, 대기 등 여러 상태를 가지며, 각 상태에서 수행하는 애니메이션이나 스킬이 달라집니다.

---

## 3. 구현 방법

아래 예제는 TypeScript를 사용하여 상태 패턴을 구현하는 방법을 보여줍니다.  
예제에서는 간단한 게임 캐릭터가 "Idle(대기)" 상태와 "Attack(공격)" 상태를 가지며, 상태 전환에 따라 행동이 변화하는 구조를 구현합니다.

### 3.1 상태 인터페이스 정의

```typescript
// State.ts
export interface State {
  // 해당 상태에서 수행할 행동을 정의하는 메서드
  handle(context: Context): void;
}
```

### 3.2 컨텍스트 클래스 정의

컨텍스트(Context) 클래스는 현재 상태를 보유하며, 상태에 따른 요청을 상태 객체로 위임합니다.

```typescript
// Context.ts
import { State } from './State';

export class Context {
  private state: State;

  constructor(state: State) {
    this.state = state;
  }

  public setState(state: State): void {
    console.log(`상태 전환: ${this.state.constructor.name} -> ${state.constructor.name}`);
    this.state = state;
  }

  // 상태 객체의 handle() 메서드에 요청을 위임
  public request(): void {
    this.state.handle(this);
  }
}
```

### 3.3 구체적인 상태 클래스 구현

예제로 게임 캐릭터가 "Idle(대기)" 상태와 "Attack(공격)" 상태를 가지는 경우를 구현합니다.

```typescript
// IdleState.ts
import { State } from './State';
import { Context } from './Context';
import { AttackState } from './AttackState';

export class IdleState implements State {
  public handle(context: Context): void {
    console.log("캐릭터가 대기 상태입니다.");
    // 단순 예시로, 대기 상태에서 특정 조건(예: 타이머 만료) 이후 공격 상태로 전환
    context.setState(new AttackState());
  }
}
```

```typescript
// AttackState.ts
import { State } from './State';
import { Context } from './Context';
import { IdleState } from './IdleState';

export class AttackState implements State {
  public handle(context: Context): void {
    console.log("캐릭터가 공격 상태입니다.");
    // 공격 후 다시 대기 상태로 전환하는 간단한 예시
    context.setState(new IdleState());
  }
}
```

### 3.4 클라이언트 코드 예시

```typescript
// client.ts
import { Context } from './Context';
import { IdleState } from './IdleState';

const character = new Context(new IdleState());

// 상태 전환을 여러 번 반복하여 시연
for (let i = 0; i < 4; i++) {
  character.request();
}

// 예상 출력 예시:
// 캐릭터가 대기 상태입니다.
// 상태 전환: IdleState -> AttackState
// 캐릭터가 공격 상태입니다.
// 상태 전환: AttackState -> IdleState
// 캐릭터가 대기 상태입니다.
// 상태 전환: IdleState -> AttackState
// 캐릭터가 공격 상태입니다.
// 상태 전환: AttackState -> IdleState
```

- **구현 포인트:**  
  - **상태 캡슐화:** 각 상태는 독립적인 클래스로 구현되어, 해당 상태에서 수행할 행동(handle 메서드)을 정의합니다.  
  - **컨텍스트와 상태의 분리:** Context 클래스는 현재 상태를 관리하며, 요청(request)이 들어오면 현재 상태의 handle() 메서드에 위임하여 행동을 결정합니다.  
  - **동적 상태 전환:** 상태 클래스 내에서 조건에 따라 다른 상태로 전환하는 로직을 구현하여, 객체의 행동이 자동으로 변화합니다.

---

## 4. 장단점 및 고려 사항

### 장점
- **조건문 제거:**  
  - 복잡한 if/else 문 없이 각 상태를 별도의 클래스로 분리하여 관리할 수 있어 코드가 깔끔해집니다.
- **유연한 확장:**  
  - 새로운 상태 추가나 기존 상태 변경 시, 다른 상태에 영향을 주지 않고 독립적으로 관리할 수 있습니다.
- **행동 캡슐화:**  
  - 각 상태별로 특정 행동을 구현하여, 상태 변화에 따른 객체 동작을 명확하게 분리할 수 있습니다.

### 단점
- **클래스 수 증가:**  
  - 상태마다 별도의 클래스를 생성해야 하므로, 클래스 수가 많아져 초기 설계가 복잡해질 수 있습니다.
- **상태 전환 관리:**  
  - 복잡한 상태 전환 조건을 처리할 경우, 상태 간의 전환 로직 관리가 어려워질 수 있습니다.

### 추가 고려 사항
- **동기화:**  
  - 멀티스레드 환경에서는 상태 전환 시 동기화 처리가 필요할 수 있습니다.
- **테스트:**  
  - 각 상태와 컨텍스트의 동작을 단위 테스트로 철저히 검증하여, 예상치 못한 상태 전환이나 로직 오류를 방지해야 합니다.
- **설계 문서화:**  
  - 상태 전환 다이어그램 등을 통해 각 상태와 전환 조건을 명확히 문서화하여, 팀 내 이해를 높이는 것이 중요합니다.

---

## 5. 참고 자료

- [Refactoring Guru - State Pattern](https://refactoring.guru/design-patterns/state)  
- _Design Patterns: Elements of Reusable Object-Oriented Software_ - Erich Gamma 외  
- _Head First Design Patterns_ - Eric Freeman

---

## 마무리

상태 패턴은 객체의 상태 변화에 따라 동적으로 행동을 변경할 수 있도록 하는 강력한 설계 기법입니다.  
실제 프로젝트에서는 TCP 연결 관리, UI 컴포넌트 상태 관리, 게임 캐릭터 행동 등 다양한 분야에서 상태 패턴을 활용하여 코드의 유연성과 유지보수성을 크게 향상시킬 수 있습니다.