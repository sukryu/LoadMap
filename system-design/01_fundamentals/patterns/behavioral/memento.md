# 메멘토 패턴

> **목표:**  
> - 객체의 내부 상태를 캡슐화하여 저장하고, 필요 시 복원할 수 있도록 한다.  
> - 실행 취소(Undo) 및 재실행(Redo) 기능과 같이, 상태 이력을 관리하는 기능을 효과적으로 구현한다.  
> - 객체의 내부 구조를 외부에 노출하지 않으면서 상태 변경 기록을 보관하여, 안정적인 복구 메커니즘을 제공한다.

---

## 1. 개념 개요

- **정의:**  
  메멘토 패턴은 객체(Originator)의 내부 상태를 별도의 메멘토(Memento) 객체에 저장하고, 필요할 때 해당 상태로 복원할 수 있도록 하는 디자인 패턴입니다.  
  이때, 메멘토 객체는 내부 상태를 캡슐화하여 외부에서 직접 수정하지 못하도록 하며, 객체의 상태 관리와 복원을 용이하게 합니다.

- **왜 중요한가?**  
  - **실행 취소 및 복구 기능 구현:**  
    사용자의 작업 이력을 저장해 두고, 언제든지 이전 상태로 복원할 수 있어, 특히 편집기나 게임 등에서 유용합니다.
  - **내부 캡슐화 유지:**  
    객체의 세부 구현을 외부에 노출하지 않고도 상태를 저장하고 복원할 수 있어, 객체의 응집도를 높입니다.
  - **상태 관리 단순화:**  
    복잡한 상태 변경 로직을 단순화하고, 상태 변경 이력을 관리할 수 있습니다.

- **해결하는 문제:**  
  - 객체의 변경 이력을 관리하여, 필요 시 실행 취소(undo)나 이전 상태로의 복원을 가능하게 합니다.  
  - 내부 상태를 외부에 노출하지 않고 안전하게 저장함으로써, 객체의 안정성을 보장합니다.

---

## 2. 실무 적용 사례

- **문서 편집기:**  
  - 사용자가 작성한 내용을 실행 취소(undo) 및 재실행(redo) 기능을 구현할 때, 메멘토 패턴을 통해 각 단계의 상태를 저장하고 복원할 수 있습니다.
  
- **게임 상태 관리:**  
  - 게임 내 플레이어의 상태나 진행 상황을 저장하고, 필요할 때 이전 상태로 복원하는 기능(예: 세이브/로드 시스템) 구현에 활용됩니다.
  
- **설정 복원:**  
  - 애플리케이션 설정 변경 이력을 저장하여, 잘못된 변경이 발생했을 때 이전 설정으로 복원하는 기능에 사용할 수 있습니다.

---

## 3. 구현 방법

아래 예제는 TypeScript를 사용하여 메멘토 패턴을 구현하는 방법을 보여줍니다.  
예제에서는 `Originator` 객체가 자신의 상태를 `Memento` 객체에 저장하고, 필요할 때 복원하는 간단한 예제를 구현합니다.

### 3.1 메멘토 클래스 정의

```typescript
// Memento.ts
export class Memento {
  // 내부 상태를 저장하는 멤버 (여기서는 단순한 문자열 상태)
  private state: string;

  constructor(state: string) {
    this.state = state;
  }

  public getState(): string {
    return this.state;
  }
}
```

### 3.2 Originator 클래스 구현

```typescript
// Originator.ts
import { Memento } from './Memento';

export class Originator {
  private state: string;

  constructor(state: string) {
    this.state = state;
  }

  // 현재 상태 설정
  public setState(state: string): void {
    this.state = state;
    console.log(`Originator: 상태가 변경됨 -> ${this.state}`);
  }

  // 현재 상태를 메멘토 객체에 저장
  public saveStateToMemento(): Memento {
    console.log(`Originator: 현재 상태를 메멘토에 저장 -> ${this.state}`);
    return new Memento(this.state);
  }

  // 메멘토 객체로부터 상태를 복원
  public getStateFromMemento(memento: Memento): void {
    this.state = memento.getState();
    console.log(`Originator: 메멘토에서 상태 복원 -> ${this.state}`);
  }
}
```

### 3.3 Caretaker 클래스 구현

```typescript
// Caretaker.ts
import { Memento } from './Memento';

export class Caretaker {
  private mementoList: Memento[] = [];

  public add(memento: Memento): void {
    this.mementoList.push(memento);
  }

  public get(index: number): Memento {
    return this.mementoList[index];
  }
}
```

### 3.4 클라이언트 코드 예시

```typescript
// client.ts
import { Originator } from './Originator';
import { Caretaker } from './Caretaker';

const originator = new Originator("상태1");
const caretaker = new Caretaker();

originator.setState("상태2");
caretaker.add(originator.saveStateToMemento());

originator.setState("상태3");
caretaker.add(originator.saveStateToMemento());

originator.setState("상태4");

// 이전 상태로 복원
originator.getStateFromMemento(caretaker.get(0)); // 상태2 복원
originator.getStateFromMemento(caretaker.get(1)); // 상태3 복원
```

- **구현 포인트:**  
  - **Originator:** 자신의 현재 상태를 관리하며, `saveStateToMemento()` 메서드를 통해 메멘토 객체로 상태를 저장하고, `getStateFromMemento()` 메서드로 메멘토로부터 상태를 복원합니다.
  - **Memento:** 내부 상태를 안전하게 캡슐화하여 저장하며, 외부에서는 상태를 직접 변경할 수 없도록 합니다.
  - **Caretaker:** 메멘토 객체들을 관리하며, 필요할 때 적절한 메멘토를 제공하여 Originator가 상태를 복원할 수 있도록 합니다.

---

## 4. 장단점 및 고려 사항

### 장점
- **실행 취소 기능:**  
  - 객체의 상태를 이전 시점으로 복원할 수 있어, 실행 취소(undo) 및 재실행(redo) 기능 구현에 유용합니다.
  
- **캡슐화 유지:**  
  - 객체의 내부 상태를 외부에 노출하지 않고 안전하게 저장하고 복원할 수 있습니다.
  
- **상태 관리 단순화:**  
  - 복잡한 상태 변경 로직을 단순화하고, 상태 이력을 체계적으로 관리할 수 있습니다.

### 단점
- **메모리 사용:**  
  - 객체의 상태를 메멘토 객체로 저장할 때, 상태 저장 빈도와 메멘토 개수에 따라 메모리 사용량이 증가할 수 있습니다.
  
- **과도한 저장:**  
  - 불필요한 상태 저장이 발생할 경우, 관리와 성능 측면에서 부담이 될 수 있습니다.

### 추가 고려 사항
- **효율적인 메멘토 관리:**  
  - 상태 저장 빈도와 저장 주기를 조절하여, 메모리 사용량을 최적화해야 합니다.
  
- **동시성:**  
  - 멀티스레드 환경에서는 상태 저장 및 복원 시 동기화 처리가 필요할 수 있습니다.
  
- **테스트:**  
  - Originator, Memento, Caretaker 각 컴포넌트에 대해 단위 테스트를 수행하여, 상태 저장 및 복원 기능이 올바르게 동작하는지 검증해야 합니다.

---

## 5. 참고 자료

- [Refactoring Guru - Memento Pattern](https://refactoring.guru/design-patterns/memento)  
- _Design Patterns: Elements of Reusable Object-Oriented Software_ - Erich Gamma 외  
- _Head First Design Patterns_ - Eric Freeman

---

## 마무리

메멘토 패턴은 객체의 내부 상태를 캡슐화하여 저장하고, 필요할 때 복원할 수 있도록 하는 유용한 설계 기법입니다.  
실제 프로젝트에서는 실행 취소(Undo) 기능, 게임 상태 관리, 설정 복원 등 다양한 분야에서 메멘토 패턴을 활용하여 코드의 안정성과 유지보수성을 크게 향상시킬 수 있습니다.