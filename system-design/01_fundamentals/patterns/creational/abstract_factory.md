# 추상 팩토리 패턴

> **목표:**  
> - 관련 객체(제품군)를 생성하는 인터페이스를 제공하여, 객체 생성 로직의 추상화와 일관성을 보장한다.  
> - 클라이언트 코드가 구체적인 클래스에 의존하지 않고, 운영체제나 환경에 따른 제품군을 유연하게 교체할 수 있도록 한다.

---

## 1. 개념 개요

- **정의:**  
  추상 팩토리 패턴은 서로 관련 있는 객체들의 집합(제품군)을 생성하기 위한 인터페이스를 제공하며, 구체적인 팩토리 클래스가 실제 객체들을 생성하는 디자인 패턴입니다.

- **왜 중요한가?**  
  - **제품군 일관성:** 관련된 여러 객체(Button, Checkbox 등)을 동시에 생성하여, 제품군 간의 일관성을 유지합니다.  
  - **캡슐화:** 객체 생성 로직을 팩토리 내부로 감추어 클라이언트 코드가 구체적인 클래스에 의존하지 않도록 합니다.  
  - **유연성 및 확장성:** 새로운 제품군이 필요할 때 클라이언트 코드를 수정하지 않고도, 새로운 팩토리 클래스를 추가하여 확장이 용이합니다.

- **해결하는 문제:**  
  - 제품군에 속하는 객체들의 생성 방법을 통일하여, 시스템 내의 다양한 환경(예: Windows vs. MacOS)에 맞게 객체들을 일관되게 생성합니다.
  - 클라이언트 코드에서 구체적인 클래스에 직접 의존하는 문제를 제거함으로써, 유지보수성과 확장성을 개선합니다.

---

## 2. 실무 적용 사례

- **UI 컴포넌트 라이브러리:**  
  서로 다른 운영체제(예: Windows, MacOS 등)에 맞는 버튼, 체크박스 등 UI 컴포넌트를 생성할 때, 추상 팩토리 패턴을 활용하여 일관된 UI를 제공할 수 있습니다.

- **데이터베이스 연결:**  
  다양한 데이터베이스(MySQL, PostgreSQL 등)에 맞는 커넥션 객체들을 생성하는데 적용하여, 데이터베이스 종류에 따른 차이를 추상화할 수 있습니다.

- **문서 생성 시스템:**  
  여러 종류의 문서 포맷(PDF, DOCX 등)에 맞는 객체들을 생성할 때, 각 제품군 별 생성 로직을 추상 팩토리로 관리하여 코드 변경 없이 새로운 포맷을 도입할 수 있습니다.

---

## 3. 구현 방법

### 3.1 TypeScript를 이용한 기본 구현

아래 예시는 Windows와 MacOS 환경에 맞는 **버튼(Button)**과 **체크박스(Checkbox)**를 생성하는 추상 팩토리 패턴의 예제입니다.

#### **1) 제품(Product) 인터페이스 및 구체 클래스 구현**

```typescript
// products.ts

// 버튼 인터페이스
export interface Button {
  render(): void;
}

// 체크박스 인터페이스
export interface Checkbox {
  render(): void;
}

// Windows용 버튼
export class WindowsButton implements Button {
  public render(): void {
    console.log("Windows 버튼 렌더링");
  }
}

// MacOS용 버튼
export class MacOSButton implements Button {
  public render(): void {
    console.log("MacOS 버튼 렌더링");
  }
}

// Windows용 체크박스
export class WindowsCheckbox implements Checkbox {
  public render(): void {
    console.log("Windows 체크박스 렌더링");
  }
}

// MacOS용 체크박스
export class MacOSCheckbox implements Checkbox {
  public render(): void {
    console.log("MacOS 체크박스 렌더링");
  }
}
```

#### **2) 추상 팩토리 인터페이스 및 구체 팩토리 클래스 구현**

```typescript
// abstractFactory.ts
import { Button, Checkbox, WindowsButton, MacOSButton, WindowsCheckbox, MacOSCheckbox } from './products';

// 추상 팩토리 인터페이스: 관련 객체들을 생성하는 메서드를 선언
export interface GUIFactory {
  createButton(): Button;
  createCheckbox(): Checkbox;
}

// Windows용 구체 팩토리
export class WindowsFactory implements GUIFactory {
  public createButton(): Button {
    return new WindowsButton();
  }
  public createCheckbox(): Checkbox {
    return new WindowsCheckbox();
  }
}

// MacOS용 구체 팩토리
export class MacOSFactory implements GUIFactory {
  public createButton(): Button {
    return new MacOSButton();
  }
  public createCheckbox(): Checkbox {
    return new MacOSCheckbox();
  }
}
```

#### **3) 클라이언트 코드 예시**

```typescript
// client.ts
import { GUIFactory, WindowsFactory, MacOSFactory } from './abstractFactory';

function renderUI(factory: GUIFactory): void {
  const button = factory.createButton();
  const checkbox = factory.createCheckbox();

  button.render();
  checkbox.render();
}

// 예시: 현재 운영체제에 따라 적절한 팩토리 선택
const currentOS = 'MacOS';  // (예시: 현재 운영체제가 MacOS인 경우)

let factory: GUIFactory;

if (currentOS === 'Windows') {
  factory = new WindowsFactory();
} else {
  factory = new MacOSFactory();
}

renderUI(factory);
```

- **구현 포인트:**  
  - **제품군 인터페이스 정의:** 버튼과 체크박스 같은 관련 객체들을 인터페이스로 정의하고, 각 운영체제별 구체 클래스를 구현합니다.  
  - **추상 팩토리 인터페이스:** `GUIFactory`를 통해 제품군 객체들을 생성하는 메서드를 선언합니다.  
  - **구체 팩토리 클래스:** `WindowsFactory`와 `MacOSFactory`가 추상 팩토리 인터페이스를 구현하여, 해당 환경에 맞는 구체 객체들을 생성합니다.  
  - **클라이언트 코드:** 클라이언트는 구체적인 클래스에 의존하지 않고, 추상 팩토리 인터페이스를 통해 객체를 생성함으로써, 환경에 따라 유연하게 전환할 수 있습니다.

---

## 4. 장단점 및 고려 사항

### 장점
- **제품군의 일관성:**  
  관련 객체들을 함께 생성하므로, 제품군 간의 일관된 구성과 호환성을 보장합니다.

- **캡슐화:**  
  객체 생성 로직을 팩토리 내부로 감추어 클라이언트 코드가 구체적인 구현에 의존하지 않게 합니다.

- **유연한 확장:**  
  새로운 제품군이 추가되어도 클라이언트 코드는 변경하지 않고, 새로운 구체 팩토리 클래스를 추가함으로써 확장이 용이합니다.

### 단점
- **구조 복잡성 증가:**  
  제품군의 수가 많아질수록 팩토리 클래스 및 관련 제품 클래스의 수가 증가하여 전체 시스템 구조가 복잡해질 수 있습니다.

- **구현 난이도:**  
  초기 설계 시 여러 제품군과 팩토리를 고려해야 하므로, 설계 부담이 다소 증가할 수 있습니다.

### 추가 고려 사항
- **성능 최적화:**  
  팩토리 메서드 호출에 따른 오버헤드가 문제가 되지 않도록, 필요 시 캐싱이나 lazy 초기화 등의 기법을 적용합니다.
  
- **보안 및 안정성:**  
  팩토리 내부에서 민감한 데이터나 설정 값을 다룰 경우, 적절한 검증 로직과 예외 처리를 추가합니다.
  
- **테스트 전략:**  
  단위 테스트 시, 추상 팩토리와 구체 팩토리의 동작을 모킹(Mock)하여 독립적으로 테스트할 수 있도록 설계합니다.

---

## 5. 참고 자료

- [Refactoring Guru - Abstract Factory Pattern](https://refactoring.guru/design-patterns/abstract-factory)  
- _Design Patterns: Elements of Reusable Object-Oriented Software_ - Erich Gamma 외  
- _Head First Design Patterns_ - Eric Freeman

---

## 마무리

추상 팩토리 패턴은 관련 객체들을 한 번에 생성하여 제품군 간의 일관성을 유지하고, 클라이언트 코드가 구체적인 클래스에 의존하지 않도록 하는 강력한 설계 기법입니다.  
실제 프로젝트에서는 운영체제, 데이터베이스, 문서 포맷 등 서로 관련 있는 객체들을 유연하게 관리할 때 유용하게 활용할 수 있습니다.