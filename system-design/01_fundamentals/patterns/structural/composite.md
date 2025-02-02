# 컴포지트 패턴

> **목표:**  
> - 개별 객체(Leaf)와 객체들의 집합(Composite)을 동일한 인터페이스로 다룰 수 있도록 하여, 계층 구조를 단순화한다.  
> - 클라이언트 코드가 단일 객체와 복합 객체를 동일하게 처리할 수 있게 함으로써, 재귀적 구조(트리 구조 등)를 유연하게 구성한다.

---

## 1. 개념 개요

- **정의:**  
  컴포지트 패턴은 객체들을 트리 구조로 구성하여, 부분-전체 계층을 표현하고, 클라이언트가 개별 객체와 복합 객체를 동일하게 다룰 수 있도록 하는 디자인 패턴입니다.  
  즉, 복합 객체(Composite)와 단일 객체(Leaf)를 동일한 인터페이스(Component)를 구현하게 하여, 재귀적으로 구조를 구성할 수 있습니다.

- **왜 중요한가?**  
  - **계층적 구조 표현:** 파일 시스템, UI 구성 요소 등 계층 구조를 가진 시스템에서 각 요소를 일관된 방식으로 다룰 수 있습니다.  
  - **클라이언트 단순화:** 클라이언트는 개별 객체와 복합 객체를 구분하지 않고 동일한 인터페이스를 사용하여 작업할 수 있습니다.  
  - **유연한 확장:** 새로운 복합 객체나 단일 객체를 추가할 때 기존 클라이언트 코드를 수정할 필요 없이 확장이 용이합니다.

- **해결하는 문제:**  
  - 객체 간의 부분-전체 계층 구조를 명확하게 표현하여, 복잡한 구조 내의 구성 요소를 효율적으로 관리합니다.
  - 클라이언트가 개별 객체와 복합 객체를 구분할 필요 없이 동일한 메서드 호출을 통해 처리할 수 있도록 합니다.

---

## 2. 실무 적용 사례

- **파일 시스템:**  
  - 디렉터리(Composite)와 파일(Leaf)을 동일한 인터페이스로 관리하여, 디렉터리 내의 파일 및 하위 디렉터리를 일관되게 탐색 및 처리할 수 있습니다.

- **UI 구성 요소:**  
  - 버튼, 텍스트 박스 등 개별 위젯(Leaf)과 컨테이너(Composite)를 동일한 방식으로 처리하여, 복잡한 UI 계층 구조를 구성합니다.

- **조직 구조:**  
  - 조직의 부서(Composite)와 개별 직원(Leaf)을 동일한 인터페이스로 관리하여, 전체 조직 구조를 트리 형태로 표현할 수 있습니다.

---

## 3. 구현 방법

아래 예제는 TypeScript를 사용하여 컴포지트 패턴을 구현하는 예시입니다.  
예제에서는 **Component** 인터페이스를 정의하고, **Leaf**와 **Composite** 클래스를 구현하여, 트리 구조를 구성하는 방법을 보여줍니다.

### 3.1 TypeScript 예제

#### **1) 공통 인터페이스 (Component) 정의**

```typescript
// component.ts
export interface Component {
  operation(): void;
}
```

#### **2) 단일 객체 (Leaf) 구현**

```typescript
// leaf.ts
import { Component } from './component';

export class Leaf implements Component {
  private name: string;

  constructor(name: string) {
    this.name = name;
  }

  public operation(): void {
    console.log(`Leaf [${this.name}] operation 수행`);
  }
}
```

#### **3) 복합 객체 (Composite) 구현**

```typescript
// composite.ts
import { Component } from './component';

export class Composite implements Component {
  private name: string;
  private children: Component[] = [];

  constructor(name: string) {
    this.name = name;
  }

  public add(component: Component): void {
    this.children.push(component);
  }

  public remove(component: Component): void {
    this.children = this.children.filter(child => child !== component);
  }

  public operation(): void {
    console.log(`Composite [${this.name}] operation 시작`);
    for (const child of this.children) {
      child.operation();
    }
    console.log(`Composite [${this.name}] operation 종료`);
  }
}
```

#### **4) 클라이언트 코드 예시**

```typescript
// client.ts
import { Leaf } from './leaf';
import { Composite } from './composite';

// 단일 Leaf 객체 생성
const leaf1 = new Leaf("A");
const leaf2 = new Leaf("B");
const leaf3 = new Leaf("C");

// Composite 객체 생성 및 Leaf 추가
const composite1 = new Composite("X");
composite1.add(leaf1);
composite1.add(leaf2);

// 다른 Composite 객체 생성 및 Composite와 Leaf 추가
const composite2 = new Composite("Y");
composite2.add(composite1);
composite2.add(leaf3);

// 클라이언트는 Composite와 Leaf 모두 동일한 인터페이스로 처리
composite2.operation();

// 출력 예시:
// Composite [Y] operation 시작
// Composite [X] operation 시작
// Leaf [A] operation 수행
// Leaf [B] operation 수행
// Composite [X] operation 종료
// Leaf [C] operation 수행
// Composite [Y] operation 종료
```

- **구현 포인트:**  
  - **Component 인터페이스:** 단일 객체와 복합 객체가 공통으로 구현해야 하는 메서드(`operation()`)를 정의합니다.  
  - **Leaf 클래스:** 실제 작업을 수행하는 단일 객체로, Component 인터페이스를 직접 구현합니다.  
  - **Composite 클래스:** 자식 구성 요소들을 관리하며, 자신의 `operation()` 메서드에서 자식들의 `operation()`을 재귀적으로 호출합니다.

---

## 4. 장단점 및 고려 사항

### 장점
- **클라이언트 단순화:**  
  - 클라이언트는 단일 객체와 복합 객체를 구분하지 않고 동일한 방식으로 처리할 수 있으므로, 사용이 간편합니다.
  
- **유연한 계층 구조:**  
  - 복합 구조를 재귀적으로 구성할 수 있어, 복잡한 계층적 구조를 명확하게 표현할 수 있습니다.
  
- **확장성:**  
  - 새로운 Leaf 또는 Composite 객체를 추가할 때, 기존 클라이언트 코드 변경 없이 확장이 가능합니다.

### 단점
- **추가적인 추상화 계층:**  
  - 단순한 구조에 비해, 인터페이스와 클래스를 추가함으로써 초기 설계와 구현이 복잡해질 수 있습니다.
  
- **성능 이슈:**  
  - 매우 깊은 트리 구조를 구성할 경우, 재귀 호출에 따른 성능 저하 및 스택 오버플로우 위험이 있을 수 있습니다.

### 추가 고려 사항
- **테스트 전략:**  
  - 각 컴포넌트(Leaf, Composite)의 `operation()` 메서드가 올바르게 동작하는지 단위 테스트를 작성하여 검증합니다.
  
- **유지보수:**  
  - 복합 구조의 계층이 복잡해질 경우, 문서화 및 코드 리뷰를 통해 각 계층의 역할과 인터페이스를 명확히 하는 것이 중요합니다.
  
- **동시성 이슈:**  
  - 멀티스레드 환경에서 Composite 객체의 자식 목록을 변경하는 경우, 동기화 처리(락 등)를 고려해야 합니다.

---

## 5. 참고 자료

- [Refactoring Guru - Composite Pattern](https://refactoring.guru/design-patterns/composite)  
- _Design Patterns: Elements of Reusable Object-Oriented Software_ - Erich Gamma 외  
- _Head First Design Patterns_ - Eric Freeman

---

## 마무리

컴포지트 패턴은 개별 객체와 객체들의 집합을 동일한 인터페이스로 다루어, 계층적 구조를 효과적으로 구성하고 관리할 수 있도록 하는 강력한 설계 기법입니다.  
실제 프로젝트에서는 파일 시스템, UI 구성 요소, 조직 구조 등 다양한 분야에서 컴포지트 패턴을 적용하여 코드의 재사용성과 유지보수성을 크게 향상시킬 수 있습니다.