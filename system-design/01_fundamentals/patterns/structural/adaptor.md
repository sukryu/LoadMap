# 어댑터 패턴

> **목표:**  
> - 서로 다른 인터페이스를 가진 클래스들을 연결하여, 클라이언트가 일관된 방식으로 사용할 수 있도록 한다.  
> - 기존 클래스(레거시 시스템 또는 외부 라이브러리)의 인터페이스를 클라이언트가 요구하는 인터페이스로 변환하여 재사용성을 높인다.  
> - 코드의 결합도를 낮추어 유지보수와 확장성을 개선한다.

---

## 1. 개념 개요

- **정의:**  
  어댑터 패턴은 서로 호환되지 않는 인터페이스를 가진 클래스들이 함께 동작할 수 있도록, 중간에 어댑터(Adapter)를 두어 인터페이스를 변환하는 디자인 패턴입니다.  
  어댑터는 클라이언트가 기대하는 인터페이스(Target)를 구현하며, 내부적으로 기존 클래스(Adaptee)의 메서드를 호출하여 기능을 수행합니다.

- **왜 중요한가?**  
  - **호환성 제공:** 서로 다른 시스템이나 라이브러리의 인터페이스를 통일시켜, 다양한 구성요소들을 쉽게 통합할 수 있습니다.  
  - **유연한 확장:** 기존 코드를 변경하지 않고도 새로운 인터페이스 요구사항을 수용할 수 있으므로, 시스템 확장에 유리합니다.  
  - **결합도 감소:** 클라이언트는 어댑터를 통해 간접적으로 기능을 사용하게 되어, 구체 구현 클래스에 대한 직접 의존성이 줄어듭니다.

- **해결하는 문제:**  
  - 기존 클래스(Adaptee)의 인터페이스와 클라이언트가 요구하는 인터페이스(Target) 간의 불일치를 해소합니다.  
  - 레거시 시스템이나 외부 라이브러리와의 통합 시, 최소한의 수정으로 인터페이스를 맞출 수 있도록 돕습니다.

---

## 2. 실무 적용 사례

- **API 통합:**  
  서로 다른 API를 사용하는 시스템 간에 데이터 형식이나 메서드 호출 방식이 다를 경우, 어댑터를 통해 일관된 인터페이스를 제공합니다.

- **레거시 시스템 연동:**  
  오래된 시스템의 인터페이스를 새 시스템의 요구사항에 맞게 변환하여, 기존 코드를 변경하지 않고 통합할 수 있습니다.

- **UI 컴포넌트 통합:**  
  다양한 UI 라이브러리나 프레임워크의 컴포넌트를 일관되게 사용하기 위해, 어댑터를 적용하여 인터페이스를 표준화할 수 있습니다.

---

## 3. 구현 방법

### 3.1 TypeScript를 이용한 어댑터 패턴 예제

아래 예제는 클라이언트가 기대하는 `Target` 인터페이스와, 기존 클래스인 `Adaptee`의 인터페이스를 연결하는 어댑터를 구현한 예시입니다.

#### **1) 클라이언트가 기대하는 인터페이스 (Target) 정의**

```typescript
// target.ts
export interface Target {
  request(): void;
}
```

#### **2) 기존 클래스 (Adaptee) 구현**

```typescript
// adaptee.ts
export class Adaptee {
  public specificRequest(): void {
    console.log("Adaptee: 특화된 요청 처리");
  }
}
```

#### **3) 어댑터 클래스 구현**

```typescript
// adapter.ts
import { Target } from './target';
import { Adaptee } from './adaptee';

/**
 * Adapter 클래스는 Adaptee의 인터페이스를 Target 인터페이스로 변환합니다.
 */
export class Adapter implements Target {
  private adaptee: Adaptee;

  constructor(adaptee: Adaptee) {
    this.adaptee = adaptee;
  }

  public request(): void {
    // 클라이언트가 호출하는 request() 메서드에서,
    // 내부적으로 Adaptee의 specificRequest()를 호출하여 기능을 수행합니다.
    console.log("Adapter: request() 호출 - 내부적으로 specificRequest() 호출");
    this.adaptee.specificRequest();
  }
}
```

#### **4) 클라이언트 코드에서의 사용 예시**

```typescript
// client.ts
import { Adapter } from './adapter';
import { Adaptee } from './adaptee';
import { Target } from './target';

// 기존 Adaptee 객체 생성
const adaptee = new Adaptee();

// 어댑터를 통해 Adaptee를 Target 인터페이스로 변환
const target: Target = new Adapter(adaptee);

// 클라이언트는 Target 인터페이스를 사용하여 request() 호출
target.request();

// 출력 결과:
// Adapter: request() 호출 - 내부적으로 specificRequest() 호출
// Adaptee: 특화된 요청 처리
```

- **구현 포인트:**  
  - `Target` 인터페이스는 클라이언트가 사용하기를 기대하는 메서드를 정의합니다.  
  - `Adaptee` 클래스는 원래의 특화된 인터페이스를 제공하며, 직접적으로 클라이언트가 사용하기에는 부적합합니다.  
  - `Adapter` 클래스는 `Target` 인터페이스를 구현하면서 내부에 `Adaptee` 객체를 포함하여, 클라이언트의 호출을 `specificRequest()`로 변환합니다.

---

## 4. 장단점 및 고려 사항

### 장점
- **유연한 통합:**  
  - 서로 다른 인터페이스를 가진 클래스들을 손쉽게 연결할 수 있어, 다양한 시스템과의 통합이 용이합니다.
  
- **결합도 감소:**  
  - 클라이언트는 어댑터를 통해 기능을 사용하므로, 구체적인 구현 클래스에 직접 의존하지 않아 유지보수성이 향상됩니다.
  
- **기존 코드 재사용:**  
  - 기존 클래스를 변경하지 않고도 새로운 인터페이스에 맞춰 재사용할 수 있습니다.

### 단점
- **추가 클래스 증가:**  
  - 어댑터를 도입함으로써 시스템에 새로운 클래스가 추가되어 구조가 복잡해질 수 있습니다.
  
- **복잡한 변환 로직:**  
  - 인터페이스 변환이 복잡한 경우, 어댑터의 구현이 어려워지고 유지보수에 부담이 될 수 있습니다.

### 추가 고려 사항
- **성능:**  
  - 어댑터를 통한 추가적인 메서드 호출로 인한 오버헤드를 고려해야 하며, 성능에 민감한 시스템에서는 주의가 필요합니다.
  
- **테스트:**  
  - 어댑터의 변환 로직이 올바르게 동작하는지 단위 테스트를 통해 철저히 검증해야 합니다.
  
- **보안:**  
  - 외부 시스템과 통합하는 경우, 데이터 변환 과정에서 보안 이슈가 발생하지 않도록 추가 검증을 고려해야 합니다.

---

## 5. 참고 자료

- [Refactoring Guru - Adapter Pattern](https://refactoring.guru/design-patterns/adapter)  
- _Design Patterns: Elements of Reusable Object-Oriented Software_ - Erich Gamma 외  
- _Head First Design Patterns_ - Eric Freeman

---

## 마무리

어댑터 패턴은 서로 다른 인터페이스를 가진 클래스들을 효과적으로 연결하여, 클라이언트가 일관된 방식으로 기능을 사용할 수 있도록 하는 강력한 설계 기법입니다.  
실제 프로젝트에서는 API 통합, 레거시 시스템 연동, UI 컴포넌트 표준화 등 다양한 상황에서 어댑터 패턴을 적용하여 코드의 재사용성과 유지보수성을 크게 향상시킬 수 있습니다.