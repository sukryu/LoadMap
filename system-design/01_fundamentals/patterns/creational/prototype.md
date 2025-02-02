# 프로토타입 패턴

> **목표:**  
> - 기존 객체를 복제하여 새로운 객체를 생성함으로써, 복잡한 초기화 과정을 반복하지 않고 객체 생성 비용을 줄인다.  
> - 객체의 복제(cloning)를 통해 런타임 시 동적으로 객체를 생성할 수 있도록 지원한다.  
> - 얕은 복사(Shallow Copy)와 깊은 복사(Deep Copy)를 활용하여, 객체의 상태를 효율적으로 관리한다.

---

## 1. 개념 개요

- **정의:**  
  프로토타입 패턴은 이미 존재하는 객체(프로토타입)를 복제(clone)하여 새로운 객체를 생성하는 디자인 패턴입니다.  
  복잡한 객체 생성 과정이나 초기화 비용이 높은 경우, 기존 객체의 복제본을 통해 효율적으로 객체를 생성할 수 있습니다.

- **왜 중요한가?**  
  - **객체 생성 비용 절감:** 동일한 초기화 작업을 반복하지 않고, 기존 객체를 복제하여 빠르게 새로운 객체를 만들 수 있습니다.  
  - **동적 객체 생성:** 런타임 시에 객체 복제를 통해 필요한 인스턴스를 생성하므로, 유연한 시스템 설계가 가능합니다.  
  - **캡슐화:** 복제 로직을 클래스 내부에 캡슐화하여, 클라이언트 코드에서는 단순히 복제된 객체를 사용하도록 할 수 있습니다.

- **해결하는 문제:**  
  - 복잡한 초기화 과정을 가진 객체를 효율적으로 생성할 수 있도록 하여, 시스템의 성능을 최적화합니다.  
  - 새로운 객체를 생성할 때 동일한 상태를 갖는 객체를 손쉽게 복제하여, 객체 구성의 일관성을 유지합니다.

---

## 2. 실무 적용 사례

- **게임 개발:**  
  - 캐릭터나 몬스터 등 복잡한 상태를 가진 객체를 다수 생성할 때, 프로토타입 패턴을 통해 빠르게 복제하여 사용합니다.

- **문서 편집기:**  
  - 동일한 스타일이나 서식을 가진 문서 요소를 복제하여, 효율적인 복사/붙여넣기 기능을 구현할 수 있습니다.

- **네트워크 통신:**  
  - 클라이언트별로 동일한 초기화 설정을 가진 객체(예: 프로토콜 설정)를 복제하여 사용함으로써, 설정 과정을 단순화할 수 있습니다.

---

## 3. 구현 방법

아래 예시는 TypeScript를 사용하여 **ConcretePrototype** 클래스를 구현하고, 해당 객체를 복제하여 새로운 객체를 생성하는 방법을 보여줍니다.

### 3.1 TypeScript를 이용한 기본 구현 예시

```typescript
// Prototype 인터페이스 선언
interface Prototype<T> {
  clone(): T;
}

// 구체적인 프로토타입 클래스 구현
class ConcretePrototype implements Prototype<ConcretePrototype> {
  public field: string;
  public values: number[];

  constructor(field: string, values: number[]) {
    this.field = field;
    this.values = values;
  }

  // clone 메서드: 현재 객체의 상태를 복제하여 새로운 인스턴스를 생성합니다.
  public clone(): ConcretePrototype {
    // 배열과 같은 참조 타입 필드는 깊은 복사를 수행합니다.
    const clonedValues = [...this.values];
    return new ConcretePrototype(this.field, clonedValues);
  }

  public toString(): string {
    return `ConcretePrototype [field: ${this.field}, values: ${this.values.join(", ")}]`;
  }
}

// 사용 예시
const original = new ConcretePrototype("Original", [1, 2, 3]);
const copy = original.clone();

console.log(original.toString());
// 출력: ConcretePrototype [field: Original, values: 1, 2, 3]

console.log(copy.toString());
// 출력: ConcretePrototype [field: Original, values: 1, 2, 3]

// 객체 상태 수정 후, 원본과 복사본이 독립적으로 동작하는지 확인
copy.field = "Copy";
copy.values.push(4);

console.log("원본:", original.toString());
// 원본: ConcretePrototype [field: Original, values: 1, 2, 3]
console.log("복사본:", copy.toString());
// 복사본: ConcretePrototype [field: Copy, values: 1, 2, 3, 4]
```

- **구현 포인트:**  
  - `Prototype<T>` 인터페이스를 정의하여 `clone()` 메서드를 선언하고, 이를 구현하는 클래스에서 객체 복제 로직을 작성합니다.  
  - `clone()` 메서드 내에서는 참조형 멤버(예: 배열)를 깊은 복사하여 원본 객체와 복제 객체가 독립적인 상태를 유지하도록 합니다.

---

## 4. 장단점 및 고려 사항

### 장점
- **객체 생성 비용 절감:**  
  - 복잡한 초기화 과정을 거치지 않고 기존 객체를 복제함으로써, 객체 생성에 소요되는 비용을 줄일 수 있습니다.
  
- **유연한 객체 복제:**  
  - 런타임 시 객체의 상태를 복제하여 새로운 인스턴스를 생성할 수 있으므로, 동적인 객체 생성 요구사항에 효과적입니다.
  
- **캡슐화된 복제 로직:**  
  - 복제 과정을 클래스 내부에 캡슐화함으로써, 클라이언트 코드는 단순히 `clone()` 메서드를 호출하기만 하면 됩니다.

### 단점
- **복제 비용:**  
  - 복제 과정에서 객체의 모든 필드를 복사해야 하므로, 복잡한 객체의 경우 오히려 비용이 증가할 수 있습니다.
  
- **클래스별 복제 로직:**  
  - 각 클래스마다 별도의 `clone()` 메서드를 구현해야 하므로, 코드 중복이 발생할 수 있습니다.
  
- **깊은 복사와 얕은 복사의 관리:**  
  - 참조형 데이터에 대해 깊은 복사가 필요한 경우, 별도의 처리 로직이 필요하여 구현이 복잡해질 수 있습니다.

### 추가 고려 사항
- **성능 최적화:**  
  - 객체 복제 시 불필요한 연산을 최소화하도록 구현하며, 필요하다면 캐싱 전략을 적용할 수 있습니다.
  
- **보안 및 안정성:**  
  - 복제된 객체가 원본 객체와 완전히 독립적으로 동작하는지 확인하고, 의도치 않은 부작용이 발생하지 않도록 검증합니다.
  
- **테스트 전략:**  
  - 각 클래스의 `clone()` 메서드에 대해 단위 테스트를 작성하여, 복제된 객체와 원본 객체가 독립적인 상태를 유지하는지 확인합니다.

---

## 5. 참고 자료

- [Refactoring Guru - Prototype Pattern](https://refactoring.guru/design-patterns/prototype)  
- _Design Patterns: Elements of Reusable Object-Oriented Software_ - Erich Gamma 외  
- _Head First Design Patterns_ - Eric Freeman

---

## 마무리

프로토타입 패턴은 기존 객체를 복제하여 새로운 객체를 생성함으로써, 복잡한 초기화 과정을 반복하지 않고 효율적인 객체 생성을 가능하게 합니다.  
실제 프로젝트에서는 객체 복제 시의 비용, 참조형 필드의 복제 방식 등을 세밀하게 관리하여, 객체의 독립성과 일관성을 확보하는 것이 중요합니다.