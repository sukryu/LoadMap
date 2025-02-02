# 데코레이터 패턴

> **목표:**  
> - 기존 객체의 기능을 동적으로 확장하면서도, 원래의 객체 구조를 변경하지 않는다.  
> - 기능 추가 시 서브클래스의 폭발적 증가를 막고, 개별 기능들을 독립적으로 관리할 수 있도록 한다.  
> - 객체의 행동을 런타임에 조합하여 유연한 기능 확장을 가능하게 한다.

---

## 1. 개념 개요

- **정의:**  
  데코레이터 패턴은 객체에 추가적인 책임(기능)을 동적으로 부여할 수 있는 패턴입니다.  
  기본 객체(ConcreteComponent)를 감싸는(wrapper) 형태로 데코레이터(Decorator) 객체를 사용하여, 클라이언트 코드에는 동일한 인터페이스를 유지하면서 기능을 확장할 수 있습니다.

- **왜 중요한가?**  
  - **동적 확장:** 런타임에 객체의 기능을 변경하거나 확장할 수 있어, 유연한 설계가 가능합니다.  
  - **단일 책임 원칙 준수:** 각 데코레이터는 하나의 추가 기능만을 담당하여, 클래스의 복잡도를 낮추고 관리하기 쉽게 만듭니다.  
  - **상속의 한계 극복:** 기능 확장이 필요한 경우 다중 상속 대신 데코레이터를 사용하여 객체 조합으로 문제를 해결합니다.

- **해결하는 문제:**  
  - 기존 클래스를 수정하지 않고 기능을 추가할 수 있으므로, 코드 변경의 위험성을 줄입니다.  
  - 객체의 역할을 동적으로 변경함으로써, 다양한 요구사항에 유연하게 대응할 수 있습니다.

---

## 2. 실무 적용 사례

- **UI 컴포넌트:**  
  - 기본 UI 컴포넌트에 스크롤, 테두리, 그림자 등의 추가 효과를 동적으로 부여할 때 사용합니다.
  
- **로깅 및 인증:**  
  - 특정 기능(예: 데이터 접근, 네트워크 호출)에 대해 로깅, 캐싱, 인증 등의 부가 기능을 추가할 때 활용됩니다.
  
- **스트림 처리:**  
  - Java의 I/O 스트림에서, 기본 스트림에 버퍼링, 압축, 암호화 등의 기능을 추가하는 방식이 대표적인 예입니다.

---

## 3. 구현 방법

아래 예제는 TypeScript를 사용하여 **Component** 인터페이스를 정의하고, 기본 컴포넌트와 데코레이터를 구현한 후, 동적으로 기능을 확장하는 방법을 보여줍니다.

### 3.1 TypeScript 예제

#### **1) 공통 인터페이스 (Component) 정의**

```typescript
// component.ts
export interface Component {
  operation(): void;
}
```

#### **2) 기본 컴포넌트 (ConcreteComponent) 구현**

```typescript
// concreteComponent.ts
import { Component } from './component';

export class ConcreteComponent implements Component {
  public operation(): void {
    console.log("ConcreteComponent: 기본 기능 수행");
  }
}
```

#### **3) 데코레이터 추상 클래스 (Decorator) 구현**

```typescript
// decorator.ts
import { Component } from './component';

/**
 * Decorator는 Component 인터페이스를 구현하고, 내부에 Component 인스턴스를 보유합니다.
 * 이를 통해 기본 기능에 추가적인 책임을 부여할 수 있습니다.
 */
export abstract class Decorator implements Component {
  protected component: Component;

  constructor(component: Component) {
    this.component = component;
  }

  public operation(): void {
    this.component.operation();
  }
}
```

#### **4) 구체적인 데코레이터 (ConcreteDecorator) 구현**

예를 들어, 기능을 확장하여 실행 전후로 로그를 남기는 데코레이터를 구현합니다.

```typescript
// loggingDecorator.ts
import { Decorator } from './decorator';
import { Component } from './component';

export class LoggingDecorator extends Decorator {
  constructor(component: Component) {
    super(component);
  }

  public operation(): void {
    console.log("LoggingDecorator: 기능 실행 전 로깅");
    super.operation();
    console.log("LoggingDecorator: 기능 실행 후 로깅");
  }
}
```

#### **5) 클라이언트 코드 예시**

```typescript
// client.ts
import { ConcreteComponent } from './concreteComponent';
import { LoggingDecorator } from './loggingDecorator';
import { Component } from './component';

// 기본 컴포넌트 생성
const simpleComponent: Component = new ConcreteComponent();

// 데코레이터를 통해 기능 확장 (동적 조합)
const decoratedComponent: Component = new LoggingDecorator(simpleComponent);

// 클라이언트는 동일한 인터페이스를 사용하여 호출
decoratedComponent.operation();

// 출력 결과:
// LoggingDecorator: 기능 실행 전 로깅
// ConcreteComponent: 기본 기능 수행
// LoggingDecorator: 기능 실행 후 로깅
```

- **구현 포인트:**  
  - **구성(composition):** 데코레이터는 내부에 Component 인스턴스를 보유하여, 기존 기능을 감싸고 확장합니다.  
  - **동적 확장:** 클라이언트는 기본 컴포넌트를 데코레이터로 감싸서 추가 기능을 부여할 수 있으며, 여러 데코레이터를 중첩하여 사용할 수도 있습니다.

---

## 4. 장단점 및 고려 사항

### 장점
- **동적 기능 확장:**  
  - 객체의 기능을 런타임에 조합하여 동적으로 확장할 수 있어, 유연한 설계가 가능합니다.
  
- **단일 책임 원칙 준수:**  
  - 각 데코레이터가 하나의 기능만을 담당하므로, 코드의 유지보수성이 향상됩니다.
  
- **기존 코드 변경 최소화:**  
  - 기존 컴포넌트를 수정하지 않고, 데코레이터를 통해 기능을 추가할 수 있으므로 안정성이 높습니다.

### 단점
- **설계 복잡성 증가:**  
  - 데코레이터 클래스를 여러 개 생성하고 중첩할 경우, 전체 구조가 복잡해질 수 있습니다.
  
- **디버깅 어려움:**  
  - 여러 데코레이터가 중첩되면, 문제 발생 시 디버깅이 어려워질 수 있습니다.

### 추가 고려 사항
- **성능 최적화:**  
  - 데코레이터를 통한 호출 계층이 깊어지면, 호출 오버헤드가 발생할 수 있으므로 성능에 주의해야 합니다.
  
- **테스트 전략:**  
  - 각 데코레이터의 단위 테스트와, 여러 데코레이터가 결합된 경우의 통합 테스트를 통해 올바른 동작을 검증합니다.
  
- **유지보수:**  
  - 데코레이터 패턴을 사용할 경우, 전체 객체 구성도를 명확하게 문서화하고 코드 리뷰를 통해 구조를 주기적으로 점검하는 것이 좋습니다.

---

## 5. 참고 자료

- [Refactoring Guru - Decorator Pattern](https://refactoring.guru/design-patterns/decorator)  
- _Design Patterns: Elements of Reusable Object-Oriented Software_ - Erich Gamma 외  
- _Head First Design Patterns_ - Eric Freeman

---

## 마무리

데코레이터 패턴은 기본 객체에 동적으로 추가 기능을 부여함으로써, 상속의 한계를 극복하고 객체의 역할을 유연하게 확장할 수 있는 강력한 설계 기법입니다.  
실제 프로젝트에서는 UI 컴포넌트, 로깅, 인증, 데이터 처리 등 다양한 분야에서 데코레이터 패턴을 활용하여 코드의 재사용성과 유지보수성을 크게 향상시킬 수 있습니다.