# 방문자 패턴

> **목표:**  
> - 객체 구조(예: 복합 객체 계층)에 새로운 연산(방문자 로직)을 추가할 때, 기존 클래스들을 수정하지 않고 확장할 수 있도록 한다.  
> - 객체 구조와 연산을 분리하여, 새로운 연산을 쉽게 추가하고, 객체 구조와 관련된 코드의 결합도를 낮춘다.  
> - 복잡한 객체 구조에 대해 다양한 작업(예: 데이터 수집, 보고서 생성, 검증 등)을 수행할 수 있도록 지원한다.

---

## 1. 개념 개요

- **정의:**  
  방문자 패턴은 객체 구조(예: 복합 객체 계층)의 각 원소(Element)를 순회하며, 각 원소에 대해 서로 다른 연산을 수행할 수 있는 "방문자(Visitor)" 객체를 정의하는 디자인 패턴입니다.  
  각 원소는 자신을 방문한 방문자에게 자신의 타입을 알려주고, 방문자는 이를 기반으로 적절한 처리를 수행합니다.

- **왜 중요한가?**  
  - **연산의 분리:** 객체 구조 자체를 수정하지 않고, 새로운 연산을 추가할 수 있어 객체의 역할과 책임을 명확하게 분리할 수 있습니다.  
  - **확장성:** 새로운 연산이 필요할 때, 방문자 인터페이스를 구현하는 새로운 클래스를 추가하기만 하면 되므로, 기존의 객체 구조에 영향을 주지 않습니다.  
  - **유지보수성 향상:** 객체의 각 요소에 대해 반복적으로 조건문을 작성하지 않고, 방문자 패턴을 통해 처리할 수 있어 코드의 가독성과 유지보수성이 향상됩니다.

- **해결하는 문제:**  
  - 복합 객체 구조 내에서 여러 다른 연산을 추가해야 하는 경우, 각 객체에 기능을 추가하면 클래스가 비대해지고 수정하기 어려워집니다.  
  - 객체 구조와 연산 로직을 분리하여, 새로운 연산 추가 시 기존 클래스의 변경 없이 확장이 가능하도록 합니다.

---

## 2. 실무 적용 사례

- **컴파일러:**  
  - 소스 코드의 구문 트리(AST) 각 노드에 대해 다양한 분석(예: 타입 검사, 최적화, 코드 생성) 작업을 수행할 때 방문자 패턴을 사용하여 각 노드 타입에 따른 처리를 구현할 수 있습니다.
  
- **문서 처리 시스템:**  
  - 문서의 각 요소(텍스트, 이미지, 표 등)에 대해 통계, 포맷 변환, 렌더링 등의 작업을 수행할 때, 방문자를 이용하여 각 요소에 대해 별도의 연산을 적용할 수 있습니다.
  
- **UI 렌더링 및 이벤트 처리:**  
  - 복잡한 UI 컴포넌트 트리 내의 각 컴포넌트에 대해 상태 업데이트, 이벤트 처리, 레이아웃 계산 등의 작업을 수행할 때 방문자 패턴을 활용할 수 있습니다.

---

## 3. 구현 방법

아래 예제는 TypeScript를 사용하여 방문자 패턴을 구현하는 방법을 보여줍니다.  
예제에서는 간단한 요소(Element) 구조와 두 종류의 구체적인 요소(ConcreteElementA, ConcreteElementB)를 정의하고, 각 요소를 방문하는 방문자(Visitor)가 수행할 연산을 구현합니다.

### 3.1 인터페이스 및 추상 클래스 정의

#### **1) Visitable 인터페이스 (Element) 정의**

```typescript
// Element.ts
export interface Element {
  // 방문자에게 자신을 전달하여, 해당 타입에 맞는 연산을 수행하도록 함.
  accept(visitor: Visitor): void;
}
```

#### **2) Visitor 인터페이스 정의**

```typescript
// Visitor.ts
import { ConcreteElementA } from './ConcreteElementA';
import { ConcreteElementB } from './ConcreteElementB';

export interface Visitor {
  visitConcreteElementA(element: ConcreteElementA): void;
  visitConcreteElementB(element: ConcreteElementB): void;
}
```

### 3.2 구체적인 요소 클래스 구현

#### **1) ConcreteElementA**

```typescript
// ConcreteElementA.ts
import { Element } from './Element';
import { Visitor } from './Visitor';

export class ConcreteElementA implements Element {
  public operationA(): void {
    console.log("ConcreteElementA: 고유 연산 수행");
  }

  public accept(visitor: Visitor): void {
    visitor.visitConcreteElementA(this);
  }
}
```

#### **2) ConcreteElementB**

```typescript
// ConcreteElementB.ts
import { Element } from './Element';
import { Visitor } from './Visitor';

export class ConcreteElementB implements Element {
  public operationB(): void {
    console.log("ConcreteElementB: 고유 연산 수행");
  }

  public accept(visitor: Visitor): void {
    visitor.visitConcreteElementB(this);
  }
}
```

### 3.3 구체적인 방문자 클래스 구현

```typescript
// ConcreteVisitor.ts
import { Visitor } from './Visitor';
import { ConcreteElementA } from './ConcreteElementA';
import { ConcreteElementB } from './ConcreteElementB';

export class ConcreteVisitor implements Visitor {
  public visitConcreteElementA(element: ConcreteElementA): void {
    console.log("ConcreteVisitor: ConcreteElementA 방문");
    element.operationA();
  }

  public visitConcreteElementB(element: ConcreteElementB): void {
    console.log("ConcreteVisitor: ConcreteElementB 방문");
    element.operationB();
  }
}
```

### 3.4 클라이언트 코드 예시

```typescript
// client.ts
import { ConcreteElementA } from './ConcreteElementA';
import { ConcreteElementB } from './ConcreteElementB';
import { ConcreteVisitor } from './ConcreteVisitor';
import { Element } from './Element';

const elements: Element[] = [
  new ConcreteElementA(),
  new ConcreteElementB()
];

const visitor = new ConcreteVisitor();

// 각 요소에 대해 방문자를 통해 연산 수행
for (const element of elements) {
  element.accept(visitor);
}

// 예상 출력 예시:
// ConcreteVisitor: ConcreteElementA 방문
// ConcreteElementA: 고유 연산 수행
// ConcreteVisitor: ConcreteElementB 방문
// ConcreteElementB: 고유 연산 수행
```

- **구현 포인트:**  
  - **Element 인터페이스:** 각 요소는 `accept()` 메서드를 구현하여, 방문자에게 자신을 전달합니다.  
  - **Visitor 인터페이스:** 방문자는 각 구체 요소에 대해 별도의 `visit` 메서드를 제공하여, 해당 요소에 대한 연산을 수행합니다.  
  - **클라이언트:** 요소 목록에 대해 반복적으로 `accept()`를 호출함으로써, 방문자가 각 요소를 방문하고 적절한 처리를 수행합니다.

---

## 4. 장단점 및 고려 사항

### 장점
- **연산의 분리:**  
  - 객체 구조(요소)와 연산(방문자)을 분리하여, 새로운 연산을 추가할 때 기존 요소 클래스를 수정하지 않아도 됩니다.
  
- **유연한 확장:**  
  - 새로운 방문자 클래스를 추가함으로써, 동일한 객체 구조에 대해 다양한 연산을 쉽게 적용할 수 있습니다.
  
- **클래스 간 결합도 감소:**  
  - 요소 클래스들은 자신의 핵심 역할에 집중하고, 연산은 방문자에게 위임하여 코드의 응집도를 높입니다.

### 단점
- **방문자 인터페이스 수정:**  
  - 새로운 요소 클래스가 추가될 경우, 모든 기존 방문자 인터페이스와 구현체를 수정해야 할 수 있습니다.
  
- **객체 구조 노출:**  
  - 방문자가 요소의 내부 구조에 접근할 수 있으므로, 캡슐화 원칙이 약해질 위험이 있습니다.
  
- **이중 디스패치:**  
  - 방문자 패턴은 이중 디스패치(double dispatch)를 사용하므로, 일부 언어에서는 구현이 다소 복잡해질 수 있습니다.

### 추가 고려 사항
- **설계 문서화:**  
  - 요소와 방문자 간의 관계 및 책임을 명확히 문서화하여, 향후 확장 및 유지보수 시 혼선을 방지해야 합니다.
  
- **테스트:**  
  - 각 방문자와 요소에 대해 단위 테스트를 수행하여, 다양한 방문자가 올바르게 동작하는지 확인해야 합니다.
  
- **유연성 확보:**  
  - 요소 클래스의 변경이 방문자에게 미치는 영향을 최소화하기 위해, 가능한 한 인터페이스와 추상 클래스를 통해 의존성을 관리합니다.

---

## 5. 참고 자료

- [Refactoring Guru - Visitor Pattern](https://refactoring.guru/design-patterns/visitor)  
- _Design Patterns: Elements of Reusable Object-Oriented Software_ - Erich Gamma 외  
- _Head First Design Patterns_ - Eric Freeman

---

## 마무리

방문자 패턴은 객체 구조에 새로운 연산을 추가할 때, 기존 클래스들을 수정하지 않고도 기능을 확장할 수 있는 강력한 설계 기법입니다.  
실제 프로젝트에서는 복합 객체 구조(예: 컴파일러, 문서 처리 시스템, UI 트리 등)에서 다양한 연산을 효율적으로 수행하기 위해 방문자 패턴을 활용할 수 있습니다.