# 퍼사드 패턴

> **목표:**  
> - 복잡한 서브시스템에 단순한 인터페이스를 제공하여 클라이언트와의 상호작용을 쉽게 한다.  
> - 클라이언트 코드가 내부의 복잡한 구성 요소를 직접 다루지 않고, 단일 진입점을 통해 시스템을 이용하도록 한다.  
> - 유지보수성과 확장성을 높이기 위해 서브시스템의 복잡성을 감춘다.

---

## 1. 개념 개요

- **정의:**  
  퍼사드 패턴은 여러 개의 복잡한 서브시스템 클래스를 하나의 단순화된 인터페이스(퍼사드)를 통해 감싸서, 클라이언트가 쉽게 서브시스템을 사용할 수 있도록 하는 구조 패턴입니다.

- **왜 중요한가?**  
  - **복잡성 감추기:** 서브시스템 내부의 복잡한 구현을 감추어 클라이언트는 단순한 인터페이스만 사용하면 됩니다.  
  - **결합도 감소:** 클라이언트와 서브시스템 간의 의존성을 낮춰, 서브시스템 변경 시 클라이언트에 미치는 영향을 최소화합니다.  
  - **사용성 향상:** 통합된 인터페이스를 제공하여 사용자가 시스템을 쉽게 이해하고 활용할 수 있도록 도와줍니다.

- **해결하는 문제:**  
  - 다양한 기능을 가진 서브시스템을 직접 제어할 경우 발생하는 높은 학습 곡선과 유지보수 어려움을 해결합니다.  
  - 서로 다른 모듈 간의 복잡한 상호작용을 단일 진입점으로 단순화하여 관리합니다.

---

## 2. 실무 적용 사례

- **라이브러리 통합:**  
  - 복잡한 미디어 라이브러리나 그래픽 엔진에서 여러 모듈의 기능을 하나의 인터페이스로 제공하여, 클라이언트가 손쉽게 사용할 수 있도록 합니다.

- **UI 프레임워크:**  
  - 여러 UI 컴포넌트나 모듈을 하나의 퍼사드로 감싸, 클라이언트가 복잡한 내부 구성 요소를 신경쓰지 않고 기능을 호출할 수 있습니다.

- **시스템 초기화:**  
  - 다수의 하위 시스템 초기화 과정을 단일 퍼사드 인터페이스를 통해 처리하여, 전체 초기화 로직을 단순화합니다.

---

## 3. 구현 방법

### 3.1 TypeScript를 이용한 퍼사드 패턴 예제

이번 예제에서는 복잡한 서브시스템으로 구성된 `SubsystemA`, `SubsystemB`, `SubsystemC` 클래스를 단순화된 인터페이스를 제공하는 `Facade` 클래스로 감싸는 예제를 보여줍니다.

#### **1) 서브시스템 클래스 구현**

```typescript
// subsystemA.ts
export class SubsystemA {
  public operationA1(): void {
    console.log("SubsystemA: Operation A1 수행");
  }
  
  public operationA2(): void {
    console.log("SubsystemA: Operation A2 수행");
  }
}
```

```typescript
// subsystemB.ts
export class SubsystemB {
  public operationB1(): void {
    console.log("SubsystemB: Operation B1 수행");
  }
  
  public operationB2(): void {
    console.log("SubsystemB: Operation B2 수행");
  }
}
```

```typescript
// subsystemC.ts
export class SubsystemC {
  public operationC1(): void {
    console.log("SubsystemC: Operation C1 수행");
  }
}
```

#### **2) 퍼사드 클래스 구현**

```typescript
// facade.ts
import { SubsystemA } from './subsystemA';
import { SubsystemB } from './subsystemB';
import { SubsystemC } from './subsystemC';

export class Facade {
  private subsystemA: SubsystemA;
  private subsystemB: SubsystemB;
  private subsystemC: SubsystemC;

  constructor() {
    this.subsystemA = new SubsystemA();
    this.subsystemB = new SubsystemB();
    this.subsystemC = new SubsystemC();
  }

  // 단일 인터페이스를 통해 서브시스템의 여러 작업을 한 번에 수행합니다.
  public operation(): void {
    console.log("Facade: 복합 작업 시작");
    this.subsystemA.operationA1();
    this.subsystemA.operationA2();
    this.subsystemB.operationB1();
    this.subsystemB.operationB2();
    this.subsystemC.operationC1();
    console.log("Facade: 복합 작업 종료");
  }
}
```

#### **3) 클라이언트 코드 예시**

```typescript
// client.ts
import { Facade } from './facade';

const facade = new Facade();
facade.operation();

// 출력 결과:
// Facade: 복합 작업 시작
// SubsystemA: Operation A1 수행
// SubsystemA: Operation A2 수행
// SubsystemB: Operation B1 수행
// SubsystemB: Operation B2 수행
// SubsystemC: Operation C1 수행
// Facade: 복합 작업 종료
```

- **구현 포인트:**  
  - **서브시스템 캡슐화:** 퍼사드는 내부에 여러 서브시스템 객체를 생성하고 관리하며, 클라이언트에게 단일한 메서드(`operation()`)를 제공합니다.  
  - **클라이언트 단순화:** 클라이언트는 퍼사드 객체의 간단한 인터페이스만 사용하면 되므로, 서브시스템의 복잡한 구성 요소를 신경쓰지 않아도 됩니다.  
  - **유연성:** 서브시스템의 내부 구현이 변경되더라도, 퍼사드 인터페이스만 유지하면 클라이언트 코드에 영향을 주지 않습니다.

---

## 4. 장단점 및 고려 사항

### 장점
- **사용자 친화적 인터페이스 제공:**  
  클라이언트가 복잡한 서브시스템을 직접 다루지 않고 단일 인터페이스를 사용하여 쉽게 작업할 수 있습니다.
  
- **시스템 결합도 감소:**  
  클라이언트와 서브시스템 간의 의존성을 낮추어, 서브시스템 변경 시 클라이언트 코드에 미치는 영향을 최소화합니다.
  
- **내부 구조 변경에 유연함:**  
  서브시스템의 내부 구현 변경에도 퍼사드 인터페이스를 유지함으로써 클라이언트에 대한 영향을 최소화합니다.

### 단점
- **추가적인 구조 복잡성:**  
  퍼사드를 도입함으로써 시스템 내 클래스 수가 증가하고, 인터페이스 계층이 추가되어 전체 설계가 복잡해질 수 있습니다.
  
- **기능 제한:**  
  퍼사드가 제공하는 기능에 한정되므로, 세부 기능이 필요한 경우 클라이언트가 직접 서브시스템을 호출해야 할 수도 있습니다.

### 추가 고려 사항
- **성능 최적화:**  
  퍼사드가 서브시스템의 여러 기능을 한 번에 호출할 경우 발생할 수 있는 오버헤드를 고려하여 최적화해야 합니다.
  
- **보안 및 접근 제어:**  
  퍼사드를 통해 외부에 노출되는 인터페이스에 대해 인증 및 권한 검사를 추가하여, 보안 문제를 예방합니다.
  
- **테스트 전략:**  
  퍼사드 및 내부 서브시스템의 동작이 올바르게 통합되는지 단위 테스트와 통합 테스트를 통해 철저히 검증해야 합니다.

---

## 5. 참고 자료

- [Refactoring Guru - Facade Pattern](https://refactoring.guru/design-patterns/facade)  
- _Design Patterns: Elements of Reusable Object-Oriented Software_ - Erich Gamma 외  
- _Head First Design Patterns_ - Eric Freeman

---

## 마무리

퍼사드 패턴은 복잡한 서브시스템을 단순화된 인터페이스로 감싸, 클라이언트가 쉽게 사용할 수 있도록 하는 강력한 설계 기법입니다.  
실제 프로젝트에서는 서브시스템의 복잡성을 감추어 사용성을 개선하고, 유지보수성을 향상시키며, 시스템의 결합도를 낮추는 데 유용하게 활용됩니다.