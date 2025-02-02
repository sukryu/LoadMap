# Singleton 패턴

> **목표:**  
> - 클래스의 인스턴스가 단 하나만 존재하도록 보장하고, 어디서든 이 인스턴스에 접근할 수 있도록 한다.  
> - 전역 자원(예: 데이터베이스 연결, 로깅 시스템 등)의 관리 및 공유를 효과적으로 수행한다.  
> - 불필요한 객체 생성으로 인한 메모리 낭비와 초기화 비용을 줄인다.

---

## 1. 개념 개요

- **정의:**  
  싱글톤 패턴은 클래스의 인스턴스를 하나만 생성하고, 그 인스턴스에 전역적으로 접근할 수 있도록 하는 디자인 패턴입니다.

- **왜 중요한가?**  
  - **자원 관리 최적화:** 하나의 인스턴스를 통해 메모리 및 시스템 자원을 효율적으로 사용할 수 있음  
  - **일관성 유지:** 전역 상태를 공유함으로써 여러 모듈에서 동일한 데이터나 로직을 일관되게 관리할 수 있음

- **해결하는 문제:**  
  - 중복 객체 생성을 방지하여 메모리 낭비 및 초기화 비용 감소  
  - 전역 상태를 관리할 때 발생할 수 있는 동기화 문제 최소화

---

## 2. 실무 적용 사례

- **데이터베이스 연결 관리:**  
  데이터베이스 커넥션 풀이나 커넥션 매니저를 하나의 인스턴스로 관리하여 연결 자원의 효율적 활용

- **로깅 시스템:**  
  애플리케이션 전체에서 동일한 로거 인스턴스를 사용하여 로그 기록의 일관성 확보

- **설정 값 관리:**  
  전역 설정이나 환경 구성을 싱글톤 객체로 관리하여 애플리케이션 내 어디서든 동일한 설정값 사용

---

## 3. 구현 방법

### 3.1 TypeScript를 이용한 기본 구현

```typescript
// Singleton.ts
class Singleton {
  // 싱글톤 인스턴스를 저장할 private 정적 변수
  private static instance: Singleton;

  // 외부에서의 직접 인스턴스 생성을 막기 위해 생성자를 private으로 선언
  private constructor() {
    // 초기화 작업 수행 (예: 자원 할당 등)
  }

  // 싱글톤 인스턴스를 반환하는 정적 메서드
  public static getInstance(): Singleton {
    if (!Singleton.instance) {
      Singleton.instance = new Singleton();
    }
    return Singleton.instance;
  }

  // 예제 메서드
  public someMethod(): void {
    console.log("싱글톤 인스턴스의 메서드 호출");
  }
}

// 사용 예시
const singleton1 = Singleton.getInstance();
singleton1.someMethod();

const singleton2 = Singleton.getInstance();
console.log("두 인스턴스가 동일한가?", singleton1 === singleton2);  // true
```

- **구현 포인트:**  
  - **생성자 제한:** `private` 생성자를 사용하여 외부에서 직접 객체를 생성하지 못하게 함  
  - **인스턴스 제어:** `getInstance` 메서드를 통해 인스턴스가 없을 때만 생성하고, 이미 존재하면 기존 인스턴스를 반환

### 3.2 멀티스레드 환경에서의 고려 (Java 예시)

TypeScript/JavaScript는 기본적으로 싱글 스레드 환경이지만, 멀티스레드 환경에서는 동기화가 필요합니다.

```java
public class Singleton {
    // volatile 키워드를 사용해 멀티스레드 환경에서 가시성 확보
    private static volatile Singleton instance;

    // private 생성자
    private Singleton() {}

    public static Singleton getInstance() {
        if (instance == null) {
            synchronized(Singleton.class) {
                if (instance == null) {  // Double-Check Locking
                    instance = new Singleton();
                }
            }
        }
        return instance;
    }
}
```

- **설명:**  
  - **Double-Check Locking:** 인스턴스가 없는 경우에만 동기화 블록에 진입하여 안전하게 객체를 생성  
  - **volatile 사용:** 변수의 가시성을 보장하여 멀티스레드 환경에서 인스턴스 생성 시 문제를 방지

---

## 4. 장단점 및 고려 사항

### 장점
- **자원 최적화:**  
  단 하나의 인스턴스로 메모리 낭비를 줄이고, 자원 사용을 중앙 집중식으로 관리할 수 있음

- **글로벌 접근성:**  
  애플리케이션 전역에서 동일한 인스턴스에 접근하여 일관된 상태를 유지

### 단점
- **테스트의 어려움:**  
  전역 상태로 인해 단위 테스트 시, 모킹(Mock)이나 독립적인 테스트 구성이 어려울 수 있음

- **과도한 결합도:**  
  싱글톤에 의존하는 코드가 많아지면, 코드 간 결합도가 높아져 유지보수에 어려움이 발생할 수 있음

- **병목 현상:**  
  여러 클라이언트가 동시에 동일 인스턴스에 접근할 경우, 동기화 문제나 성능 병목이 발생할 가능성이 있음

### 추가 고려 사항
- **성능 최적화:**  
  인스턴스 생성은 lazy initialization을 사용해 필요한 경우에만 수행하도록 설계

- **보안 및 안정성:**  
  멀티스레드 환경에서는 동기화 메커니즘(예, Double-Check Locking)을 적용하여 인스턴스 생성의 안정성을 확보

- **테스트 전략:**  
  단위 테스트 시 싱글톤 인스턴스의 상태를 초기화하거나 별도의 모킹 전략을 도입하여 독립적인 테스트 환경을 구축

---

## 5. 참고 자료

- [Refactoring Guru - Singleton Pattern](https://refactoring.guru/design-patterns/singleton)  
- _Design Patterns: Elements of Reusable Object-Oriented Software_ - Erich Gamma 외  
- _Effective Java_ - Joshua Bloch

---

## 마무리

싱글톤 패턴은 객체 생성의 제어와 전역 상태 관리에 효과적이며, 시스템 자원의 효율적 사용을 도와줍니다.  
다만, 전역 상태로 인한 테스트 어려움과 과도한 결합도 등 단점도 존재하므로, 실제 프로젝트에 적용할 때는 상황에 맞는 신중한 고려가 필요합니다.