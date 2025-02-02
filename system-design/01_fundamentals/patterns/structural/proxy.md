# 프록시 패턴

> **목표:**  
> - 실제 객체(RealSubject)에 대한 접근을 제어하고, 필요 시 추가적인 기능(예: 접근 제어, 캐싱, 로깅 등)을 부여한다.  
> - 클라이언트는 실제 객체와 동일한 인터페이스를 사용하지만, 프록시를 통해 간접적으로 해당 객체에 접근하도록 한다.  
> - 시스템의 성능, 보안, 자원 관리 등을 개선할 수 있다.

---

## 1. 개념 개요

- **정의:**  
  프록시 패턴은 실제 객체(RealSubject)의 대리자 역할을 하는 객체(Proxy)를 제공하여, 클라이언트의 요청을 대신 처리하거나 요청 전후에 추가 작업을 수행하는 구조적 디자인 패턴입니다.  
  프록시는 실제 객체와 동일한 인터페이스를 구현하므로, 클라이언트는 실제 객체를 직접 다루는 것과 같은 방식으로 프록시를 사용할 수 있습니다.

- **왜 중요한가?**  
  - **접근 제어:** 권한 확인, 인증, 로깅 등의 부가 기능을 통해 실제 객체에 대한 접근을 제어할 수 있습니다.  
  - **지연 초기화:** 실제 객체의 생성 비용이 크거나 리소스 사용이 많은 경우, 실제 객체의 생성을 필요할 때까지 지연(lazy initialization)할 수 있습니다.  
  - **캐싱 및 성능 최적화:** 빈번한 요청에 대해 캐싱을 제공하거나, 네트워크 통신 등 비용이 큰 작업을 최소화할 수 있습니다.

- **해결하는 문제:**  
  - 클라이언트와 실제 객체 간의 결합도를 낮추면서, 추가적인 기능(예: 로깅, 접근 제한, 성능 최적화)을 적용할 수 있도록 합니다.
  - 실제 객체의 무거운 초기화나 접근 제어를 효과적으로 관리하여 시스템 자원과 보안을 개선합니다.

---

## 2. 실무 적용 사례

- **원격 프록시 (Remote Proxy):**  
  - 네트워크를 통해 원격의 객체에 접근할 때, 프록시를 사용하여 로컬에서 실제 원격 객체와 통신을 관리합니다.
  
- **가상 프록시 (Virtual Proxy):**  
  - 실제 객체의 생성 비용이 큰 경우, 프록시를 통해 지연 초기화(lazy initialization)를 구현하여 필요한 시점에만 객체를 생성합니다.
  
- **보호 프록시 (Protection Proxy):**  
  - 객체에 대한 접근 권한을 제어하여, 특정 사용자나 상황에 따라 접근을 제한합니다.
  
- **캐싱 프록시 (Caching Proxy):**  
  - 반복적인 요청에 대해 결과를 캐싱하여, 불필요한 연산이나 네트워크 호출을 줄입니다.

---

## 3. 구현 방법

아래 예제는 TypeScript를 사용하여 프록시 패턴을 구현하는 방법을 보여줍니다.  
예제에서는 **Subject** 인터페이스를 정의하고, 이를 구현한 **RealSubject**와, 추가 기능(예: 접근 제어, 로깅 등)을 제공하는 **Proxy** 클래스를 작성합니다.

### 3.1 TypeScript 예제

#### **1) 공통 인터페이스 (Subject) 정의**

```typescript
// subject.ts
export interface Subject {
  request(): void;
}
```

#### **2) 실제 객체 (RealSubject) 구현**

```typescript
// realSubject.ts
import { Subject } from './subject';

export class RealSubject implements Subject {
  public request(): void {
    console.log("RealSubject: 실제 작업 수행");
  }
}
```

#### **3) 프록시 (Proxy) 클래스 구현**

```typescript
// proxy.ts
import { Subject } from './subject';
import { RealSubject } from './realSubject';

/**
 * Proxy 클래스는 Subject 인터페이스를 구현하고,
 * 내부에서 실제 객체(RealSubject)를 관리하며, 클라이언트 요청에 대해 추가적인 작업(예: 로깅, 접근 제어)을 수행합니다.
 */
export class Proxy implements Subject {
  private realSubject: RealSubject | null = null;

  // 실제 객체 생성 전, 클라이언트의 요청에 대한 전처리 수행
  private checkAccess(): boolean {
    console.log("Proxy: 접근 권한 확인 중...");
    // 실제 환경에서는 인증, 권한 검사 등의 로직을 구현합니다.
    return true;
  }

  // 실제 객체를 필요할 때 생성하는 지연 초기화
  private getRealSubject(): RealSubject {
    if (this.realSubject === null) {
      console.log("Proxy: RealSubject를 초기화합니다.");
      this.realSubject = new RealSubject();
    }
    return this.realSubject;
  }

  public request(): void {
    // 접근 제어 로직
    if (this.checkAccess()) {
      console.log("Proxy: 요청을 RealSubject에 전달합니다.");
      // 실제 객체의 메서드 호출 전후에 추가 작업을 수행할 수 있습니다.
      const subject = this.getRealSubject();
      subject.request();
      console.log("Proxy: 요청 처리 완료 후 후처리 작업 수행");
    } else {
      console.log("Proxy: 접근이 거부되었습니다.");
    }
  }
}
```

#### **4) 클라이언트 코드 예시**

```typescript
// client.ts
import { Proxy } from './proxy';
import { Subject } from './subject';

// 클라이언트는 Subject 인터페이스를 사용하여 프록시를 호출합니다.
const subject: Subject = new Proxy();
subject.request();

// 출력 예시:
// Proxy: 접근 권한 확인 중...
// Proxy: RealSubject를 초기화합니다.
// Proxy: 요청을 RealSubject에 전달합니다.
// RealSubject: 실제 작업 수행
// Proxy: 요청 처리 완료 후 후처리 작업 수행
```

- **구현 포인트:**  
  - **동일한 인터페이스 구현:** 프록시와 실제 객체 모두 Subject 인터페이스를 구현하므로, 클라이언트는 동일한 방식으로 사용할 수 있습니다.  
  - **지연 초기화:** `getRealSubject()` 메서드를 통해 실제 객체를 필요할 때만 생성합니다.  
  - **추가 기능:** 프록시 내에서 접근 제어나 로깅, 캐싱 등의 추가 로직을 구현하여, 실제 객체에 대한 호출 전후에 필요한 작업을 수행합니다.

---

## 4. 장단점 및 고려 사항

### 장점
- **접근 제어 및 보안 강화:**  
  - 클라이언트와 실제 객체 사이에서 권한 확인, 로깅, 캐싱 등의 기능을 수행하여 보안 및 성능을 개선할 수 있습니다.
  
- **지연 초기화:**  
  - 무거운 실제 객체의 생성을 필요 시점까지 지연시킴으로써 초기 리소스 사용을 최적화할 수 있습니다.
  
- **클라이언트 코드의 단순화:**  
  - 클라이언트는 프록시를 통해 실제 객체를 호출하므로, 복잡한 초기화나 접근 제어 로직을 신경쓰지 않아도 됩니다.

### 단점
- **추가 클래스 증가:**  
  - 프록시를 도입하면 시스템에 새로운 클래스가 추가되어 구조가 복잡해질 수 있습니다.
  
- **성능 오버헤드:**  
  - 프록시를 통한 추가 로직(예: 접근 제어, 로깅 등)으로 인해 실제 객체 호출 시 약간의 성능 오버헤드가 발생할 수 있습니다.
  
- **디버깅 어려움:**  
  - 프록시가 중간에 개입함으로써, 문제 발생 시 실제 객체와 프록시 간의 상호작용을 파악하기 어려울 수 있습니다.

### 추가 고려 사항
- **테스트:**  
  - 프록시와 실제 객체의 동작이 올바르게 분리되어 동작하는지 단위 테스트와 통합 테스트를 통해 철저히 검증해야 합니다.
  
- **동시성 문제:**  
  - 다중 스레드 환경에서는 프록시 내에서 실제 객체의 초기화와 접근에 대해 적절한 동기화 처리가 필요합니다.
  
- **설계 문서화:**  
  - 프록시 패턴을 도입할 경우, 프록시와 실제 객체의 역할 및 책임을 명확히 문서화하여 팀 내 협업 및 유지보수를 원활하게 해야 합니다.

---

## 5. 참고 자료

- [Refactoring Guru - Proxy Pattern](https://refactoring.guru/design-patterns/proxy)  
- _Design Patterns: Elements of Reusable Object-Oriented Software_ - Erich Gamma 외  
- _Head First Design Patterns_ - Eric Freeman

---

## 마무리

프록시 패턴은 실제 객체에 대한 접근을 제어하고, 추가적인 기능(접근 제어, 로깅, 지연 초기화 등)을 제공함으로써 시스템의 유연성과 보안, 성능을 개선할 수 있는 강력한 설계 기법입니다.  
실제 프로젝트에서는 네트워크 통신, 원격 서비스 호출, 캐싱 등의 다양한 시나리오에서 프록시 패턴을 활용하여 클라이언트와 실제 객체 간의 결합도를 낮추고, 유지보수성을 크게 향상시킬 수 있습니다.