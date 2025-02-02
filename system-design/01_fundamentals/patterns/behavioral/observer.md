# 옵저버 패턴

> **목표:**  
> - 한 객체(Subject)의 상태 변화에 따라, 이를 구독(Subscribe)한 여러 객체(Observer)에게 자동으로 알림을 전달하여, 동기화된 업데이트를 가능하게 한다.  
> - 객체 간의 결합도를 낮추고, 상태 변화에 따른 이벤트 처리 로직을 분리함으로써 유지보수성을 향상시킨다.  
> - 다양한 컴포넌트들이 서로 독립적으로 동작하면서도, 필요한 경우에만 상호작용할 수 있도록 한다.

---

## 1. 개념 개요

- **정의:**  
  옵저버 패턴은 한 객체(Subject)의 상태 변화가 있을 때, 해당 변화를 관심 있는 여러 옵저버(Observer)에게 자동으로 통지하여 업데이트하도록 하는 디자인 패턴입니다.  
  Subject는 자신에게 등록된 옵저버들을 관리하며, 상태가 변경될 때마다 옵저버들에게 알림을 전달합니다.

- **왜 중요한가?**  
  - **결합도 감소:** Subject와 Observer가 직접적으로 의존하지 않고, 인터페이스를 통해 상호작용하므로 서로의 변경에 유연하게 대응할 수 있습니다.  
  - **동적 업데이트:** Subject의 상태 변화에 따라 Observer들이 자동으로 업데이트되므로, 실시간 데이터 갱신, 이벤트 기반 시스템 등에서 효과적입니다.  
  - **유연성:** 새로운 옵저버를 추가하거나 제거하는 것이 용이하여, 시스템 확장 및 변경에 유연합니다.

- **해결하는 문제:**  
  - 한 객체의 상태 변화가 다른 객체들에 자동으로 반영되지 않아 발생하는 데이터 불일치 문제를 해결합니다.  
  - 이벤트 처리 및 통지 로직을 Subject 내부에 집중시키지 않고, Observer에 위임함으로써 코드의 모듈화와 유지보수성을 향상시킵니다.

---

## 2. 실무 적용 사례

- **UI 이벤트 처리:**  
  - 버튼 클릭, 입력값 변경 등 사용자 이벤트가 발생할 때, 관련된 여러 컴포넌트(UI 업데이트, 데이터 바인딩 등)에 자동으로 알림을 전달하여 화면을 갱신합니다.

- **실시간 데이터 업데이트:**  
  - 주식 시세, 날씨 정보, 채팅 애플리케이션 등에서 데이터 변경 시 옵저버에게 자동으로 알림을 전달해 최신 정보를 반영합니다.

- **퍼블리셔-서브스크라이버(Pub/Sub) 모델:**  
  - 메시지 브로커를 통해 여러 클라이언트에게 이벤트를 전파하는 시스템에서 옵저버 패턴을 응용할 수 있습니다.

---

## 3. 구현 방법

아래 예제는 TypeScript를 사용하여 옵저버 패턴을 구현하는 방법을 보여줍니다.  
예제에서는 Subject 인터페이스를 통해 옵저버를 등록, 제거, 알림 전파하는 기능을 제공하며, 구체적인 Observer가 업데이트 로직을 구현합니다.

### 3.1 옵저버와 서브젝트 인터페이스 정의

```typescript
// Observer.ts
export interface Observer {
  // Subject의 상태가 변경되었을 때 호출되는 메서드
  update(state: any): void;
}
```

```typescript
// Subject.ts
import { Observer } from './Observer';

export interface Subject {
  // 옵저버 등록
  registerObserver(observer: Observer): void;
  // 옵저버 제거
  removeObserver(observer: Observer): void;
  // 옵저버에게 알림 전달
  notifyObservers(): void;
}
```

### 3.2 구체적인 Subject 구현

```typescript
// ConcreteSubject.ts
import { Subject } from './Subject';
import { Observer } from './Observer';

export class ConcreteSubject implements Subject {
  private observers: Observer[] = [];
  private state: any;

  // 상태 변경 시 옵저버들에게 알림
  public setState(state: any): void {
    this.state = state;
    console.log(`ConcreteSubject: 상태가 변경됨 -> ${this.state}`);
    this.notifyObservers();
  }

  public getState(): any {
    return this.state;
  }

  public registerObserver(observer: Observer): void {
    this.observers.push(observer);
  }

  public removeObserver(observer: Observer): void {
    this.observers = this.observers.filter(obs => obs !== observer);
  }

  public notifyObservers(): void {
    for (const observer of this.observers) {
      observer.update(this.state);
    }
  }
}
```

### 3.3 구체적인 Observer 구현

```typescript
// ConcreteObserver.ts
import { Observer } from './Observer';

export class ConcreteObserver implements Observer {
  private name: string;

  constructor(name: string) {
    this.name = name;
  }

  public update(state: any): void {
    console.log(`${this.name} 옵저버가 업데이트 받음: 새로운 상태 -> ${state}`);
  }
}
```

### 3.4 클라이언트 코드 예시

```typescript
// client.ts
import { ConcreteSubject } from './ConcreteSubject';
import { ConcreteObserver } from './ConcreteObserver';

const subject = new ConcreteSubject();

// 옵저버 생성 및 등록
const observer1 = new ConcreteObserver("Observer1");
const observer2 = new ConcreteObserver("Observer2");

subject.registerObserver(observer1);
subject.registerObserver(observer2);

// Subject의 상태 변경
subject.setState("상태 A");

// Observer2 제거 후 상태 변경
subject.removeObserver(observer2);
subject.setState("상태 B");

// 출력 예시:
// ConcreteSubject: 상태가 변경됨 -> 상태 A
// Observer1 옵저버가 업데이트 받음: 새로운 상태 -> 상태 A
// Observer2 옵저버가 업데이트 받음: 새로운 상태 -> 상태 A
// ConcreteSubject: 상태가 변경됨 -> 상태 B
// Observer1 옵저버가 업데이트 받음: 새로운 상태 -> 상태 B
```

- **구현 포인트:**  
  - **Subject 관리:** ConcreteSubject는 내부에 옵저버 리스트를 관리하며, 상태 변화 시 모든 옵저버에게 알림을 전달합니다.  
  - **Observer 역할:** ConcreteObserver는 Subject의 상태 변화에 대해 자신의 update() 메서드 내에서 필요한 동작(예: 화면 업데이트, 로그 출력 등)을 수행합니다.  
  - **유연성:** 옵저버는 언제든지 등록 및 제거할 수 있어, 동적인 이벤트 처리 시스템 구축에 유리합니다.

---

## 4. 장단점 및 고려 사항

### 장점
- **결합도 감소:**  
  - Subject와 Observer가 서로 직접 참조하지 않고 인터페이스를 통해 통신하므로, 한쪽의 변경이 다른 쪽에 미치는 영향을 최소화합니다.
  
- **확장성:**  
  - 새로운 옵저버를 손쉽게 추가하거나 제거할 수 있어, 시스템 확장이 용이합니다.
  
- **동적 업데이트:**  
  - Subject의 상태 변화가 자동으로 모든 옵저버에게 전파되어, 실시간 데이터 반영 및 이벤트 처리에 효과적입니다.

### 단점
- **성능 문제:**  
  - 옵저버가 매우 많을 경우, 상태 변경 시 모든 옵저버에게 알림을 전달하는 과정에서 성능 오버헤드가 발생할 수 있습니다.
  
- **순서 제어 어려움:**  
  - 옵저버에게 전달되는 알림의 순서가 보장되지 않을 수 있으므로, 순서에 민감한 로직에는 주의가 필요합니다.
  
- **의존성 관리:**  
  - 옵저버와 Subject 간의 관계가 복잡해질 경우, 이벤트의 흐름을 추적하고 디버깅하는 데 어려움이 있을 수 있습니다.

### 추가 고려 사항
- **메모리 관리:**  
  - 옵저버가 Subject에 등록되어 있을 경우, Subject가 해제되지 않으면 옵저버 객체도 메모리에서 해제되지 않을 수 있으므로, 적절한 옵저버 제거 로직이 필요합니다.
  
- **동시성:**  
  - 멀티스레드 환경에서는 옵저버 목록 관리와 알림 전달 시 동기화 처리가 필요할 수 있습니다.
  
- **테스트:**  
  - Subject와 Observer 간의 상호작용을 단위 테스트와 통합 테스트를 통해 철저히 검증하여, 예상치 못한 업데이트 누락이나 중복 알림을 방지해야 합니다.

---

## 5. 참고 자료

- [Refactoring Guru - Observer Pattern](https://refactoring.guru/design-patterns/observer)  
- _Design Patterns: Elements of Reusable Object-Oriented Software_ - Erich Gamma 외  
- _Head First Design Patterns_ - Eric Freeman

---

## 마무리

옵저버 패턴은 객체의 상태 변화를 효과적으로 전달하여, 이벤트 기반 시스템 및 실시간 데이터 업데이트 등 다양한 분야에서 활용할 수 있는 강력한 설계 기법입니다.  
Subject와 Observer 간의 결합도를 낮추고, 동적 업데이트를 가능하게 함으로써, 유지보수성과 확장성이 높은 시스템을 구축할 수 있습니다.