# Factory Method 패턴

> **목표:**  
> - 객체 생성 로직을 서브 클래스에 위임하여 클라이언트 코드와 구체 클래스 간의 결합도를 낮춘다.  
> - 객체 생성 과정을 추상화하여 확장성과 유지보수성을 향상시킨다.

---

## 1. 개념 개요

- **정의:**  
  팩토리 메서드 패턴은 객체 생성에 관한 인터페이스를 정의하고, 어떤 클래스의 인스턴스를 생성할지는 서브 클래스가 결정하도록 위임하는 디자인 패턴입니다.

- **왜 중요한가?**  
  - **결합도 감소:** 클라이언트 코드가 구체적인 클래스를 직접 호출하지 않고 추상화된 인터페이스에 의존함으로써, 코드의 의존성을 줄일 수 있습니다.  
  - **확장성:** 새로운 객체가 추가될 때 기존 코드를 크게 변경하지 않고, 새로운 Creator 서브 클래스를 통해 손쉽게 확장할 수 있습니다.

- **해결하는 문제:**  
  - 객체 생성 로직의 중복 및 복잡성 문제  
  - 클라이언트 코드가 구체적인 클래스에 직접 의존하는 문제를 해결하여, 변경에 유연한 설계를 도모

---

## 2. 실무 적용 사례

- **UI 컴포넌트 생성:**  
  다양한 테마나 플랫폼에 따라 다른 UI 컴포넌트(Button, Checkbox 등)를 생성할 때 팩토리 메서드를 활용하여 확장이 용이하도록 구현

- **데이터 파서(Parser) 생성:**  
  JSON, XML 등 다양한 데이터 포맷에 대응하는 파서 객체를 팩토리 메서드를 통해 생성하여, 새로운 포맷이 추가되어도 기존 클라이언트 코드를 수정하지 않음

- **문서 생성 시스템:**  
  여러 종류의 문서(예: PDF, DOCX 등)를 생성할 때, 팩토리 메서드를 이용해 문서 유형에 따른 구체적인 객체를 생성

---

## 3. 구현 방법

### 3.1 TypeScript를 이용한 기본 구현

아래 예시는 제품(Product) 인터페이스와 구체 제품, 그리고 객체 생성을 위한 추상 Creator와 이를 구현한 서브 클래스를 통해 팩토리 메서드 패턴을 구현한 예제입니다.

#### **Product 인터페이스 및 구체 클래스 정의**

```typescript
// product.ts
export interface Product {
  operation(): void;
}

export class ConcreteProductA implements Product {
  public operation(): void {
    console.log("ConcreteProductA의 operation 실행");
  }
}

export class ConcreteProductB implements Product {
  public operation(): void {
    console.log("ConcreteProductB의 operation 실행");
  }
}
```

#### **Creator 추상 클래스 및 구체 Creator 구현**

```typescript
// creator.ts
import { Product, ConcreteProductA, ConcreteProductB } from './product';

/**
 * Creator 클래스는 객체 생성을 위한 팩토리 메서드를 선언합니다.
 * 클라이언트는 팩토리 메서드를 통해 생성된 객체를 사용하며, 구체적인 클래스에 의존하지 않습니다.
 */
export abstract class Creator {
  // 팩토리 메서드: 서브 클래스에서 구체적인 객체 생성 로직을 구현합니다.
  public abstract factoryMethod(): Product;

  // 템플릿 메서드: 팩토리 메서드를 호출하여 생성된 객체를 이용해 공통 작업을 수행합니다.
  public someOperation(): void {
    const product = this.factoryMethod();
    product.operation();
  }
}

/**
 * ConcreteCreatorA는 구체 제품인 ConcreteProductA를 생성하는 팩토리 메서드를 구현합니다.
 */
export class ConcreteCreatorA extends Creator {
  public factoryMethod(): Product {
    return new ConcreteProductA();
  }
}

/**
 * ConcreteCreatorB는 구체 제품인 ConcreteProductB를 생성하는 팩토리 메서드를 구현합니다.
 */
export class ConcreteCreatorB extends Creator {
  public factoryMethod(): Product {
    return new ConcreteProductB();
  }
}
```

#### **사용 예시**

```typescript
// index.ts
import { ConcreteCreatorA, ConcreteCreatorB } from './creator';

// ConcreteCreatorA를 통해 ConcreteProductA 생성 및 작업 실행
const creatorA = new ConcreteCreatorA();
creatorA.someOperation(); // 출력: "ConcreteProductA의 operation 실행"

// ConcreteCreatorB를 통해 ConcreteProductB 생성 및 작업 실행
const creatorB = new ConcreteCreatorB();
creatorB.someOperation(); // 출력: "ConcreteProductB의 operation 실행"
```

- **구현 포인트:**  
  - **추상화:** `Creator` 클래스에서 팩토리 메서드를 선언하고, 이를 호출하는 공통 작업(`someOperation`)을 제공하여 클라이언트의 복잡성을 줄입니다.  
  - **유연성:** 서브 클래스(`ConcreteCreatorA`, `ConcreteCreatorB`)가 각기 다른 제품을 생성함으로써, 객체 생성 로직을 손쉽게 확장할 수 있습니다.

### 3.2 고려 사항

- **확장성:**  
  새로운 제품(Product)이 필요할 경우, 해당 제품을 생성하는 새로운 Creator 서브 클래스를 추가하면 되므로, 기존 코드의 변경 없이 확장이 가능합니다.

- **테스트 용이성:**  
  팩토리 메서드를 모킹(Mock)하거나 스텁(Stub)으로 대체하여 단위 테스트를 진행할 수 있습니다.

---

## 4. 장단점 및 고려 사항

### 장점
- **결합도 감소:**  
  클라이언트는 구체적인 클래스에 의존하지 않고, 추상 Creator를 통해 객체를 생성할 수 있어 결합도가 낮아집니다.
  
- **유연한 확장:**  
  새로운 제품이 추가되어도 기존 Creator 인터페이스를 유지하면서 서브 클래스를 추가하는 방식으로 확장이 용이합니다.

### 단점
- **클래스 수 증가:**  
  각 제품마다 별도의 Creator 서브 클래스를 작성해야 하므로 클래스의 수가 증가하여 복잡성이 높아질 수 있습니다.
  
- **초기 설계 부담:**  
  추상화 계층을 도입함에 따라 초기 설계 단계에서 추가적인 고민과 설계 작업이 필요합니다.

### 추가 고려 사항
- **성능 최적화:**  
  팩토리 메서드 호출에 따른 오버헤드가 문제가 되지 않도록 설계
- **보안 및 안정성:**  
  생성 로직에 민감한 정보가 포함되는 경우, 추가적인 검증 및 예외 처리를 도입
- **운영 환경 모니터링:**  
  객체 생성 시 로깅을 통해 문제 발생 시 디버깅에 활용

---

## 5. 참고 자료

- [Refactoring Guru - Factory Method Pattern](https://refactoring.guru/design-patterns/factory-method)  
- _Design Patterns: Elements of Reusable Object-Oriented Software_ - Erich Gamma 외  
- _Head First Design Patterns_ - Eric Freeman

---

## 마무리

팩토리 메서드 패턴은 객체 생성 로직을 추상화하여 클라이언트 코드와 구체 클래스 간의 결합도를 줄이고, 확장성과 유지보수성을 높이는 효과적인 설계 기법입니다.  
실제 프로젝트에서 다양한 객체 생성 요구사항에 맞게 팩토리 메서드 패턴을 적용하면, 코드의 재사용성과 확장성을 크게 향상시킬 수 있습니다.