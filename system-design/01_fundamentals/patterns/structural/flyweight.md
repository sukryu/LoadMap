# 플라이웨이트 패턴

> **목표:**  
> - 동일하거나 유사한 객체가 다수 존재할 때, 공통된 intrinsic 상태를 공유하여 메모리 사용량을 줄인다.  
> - extrinsic(외부) 상태와 intrinsic(내부) 상태를 분리하여, 객체의 재사용성을 극대화한다.  
> - 시스템 전체의 성능과 자원 사용 최적화를 도모한다.

---

## 1. 개념 개요

- **정의:**  
  플라이웨이트 패턴은 많은 수의 유사 객체들이 개별적인 상태(내부 상태: intrinsic state)를 공유하도록 하여 메모리 사용량을 줄이는 디자인 패턴입니다.  
  **Intrinsic State:** 객체 내부에서 공유되는 불변 데이터  
  **Extrinsic State:** 객체 외부에서 관리되는, 개별 인스턴스마다 달라질 수 있는 데이터

- **왜 중요한가?**  
  - **메모리 효율성:** 동일한 데이터를 여러 객체가 공유함으로써, 시스템 내 객체 수가 많아도 메모리 사용량을 최소화할 수 있습니다.  
  - **성능 최적화:** 객체 생성 및 관리 비용을 줄여 성능 향상에 기여합니다.  
  - **유연한 객체 관리:** 외부 상태를 분리하여 필요에 따라 개별 객체의 차이를 적용할 수 있습니다.

- **해결하는 문제:**  
  - 다량의 유사 객체를 생성해야 하는 경우 발생하는 메모리 낭비 문제  
  - 객체 생성과 관리에 따른 성능 저하 문제

---

## 2. 실무 적용 사례

- **문서 편집기:**  
  - 텍스트 편집기에서 문자(Glyph) 객체를 생성할 때, 동일한 글자 모양과 폰트 정보(내부 상태)는 공유하고, 위치나 크기 등의 외부 상태는 별도로 관리합니다.

- **게임 개발:**  
  - 수많은 나무나 건물 객체에서 동일한 모델, 텍스처 정보는 공유하고, 각 객체의 위치나 크기 등의 차별화된 정보는 외부에서 제공하여 메모리 사용을 최적화합니다.

- **그래픽 시스템:**  
  - 벡터 그래픽 요소에서 동일한 스타일 정보(예: 색상, 선 굵기 등)를 공유하고, 실제 그리기 위치 등은 외부 상태로 관리하여 성능을 향상시킵니다.

---

## 3. 구현 방법

아래 예제는 TypeScript를 사용하여 플라이웨이트 패턴을 구현하는 방법을 보여줍니다.  
예제에서는 간단한 `Flyweight` 인터페이스와 이를 구현한 `ConcreteFlyweight` 클래스, 그리고 플라이웨이트 객체들을 관리하는 `FlyweightFactory` 클래스를 작성합니다.

### 3.1 플라이웨이트 인터페이스와 구체 클래스

```typescript
// flyweight.ts
export interface Flyweight {
  /**
   * 외부 상태를 매개변수로 받아서, 내부 상태와 조합하여 동작을 수행합니다.
   * @param extrinsicState - 객체의 외부 상태 (예: 위치, 식별자 등)
   */
  operation(extrinsicState: any): void;
}

// ConcreteFlyweight 클래스는 내부 상태(intrinsicState)를 공유하며, 외부 상태는 매개변수로 처리합니다.
export class ConcreteFlyweight implements Flyweight {
  private intrinsicState: string;

  constructor(intrinsicState: string) {
    this.intrinsicState = intrinsicState;
  }

  public operation(extrinsicState: any): void {
    console.log(
      `ConcreteFlyweight: 내부 상태 = ${this.intrinsicState}, 외부 상태 = ${extrinsicState}`
    );
  }
}
```

### 3.2 플라이웨이트 팩토리 클래스

플라이웨이트 팩토리는 동일한 내부 상태를 가진 객체들을 재사용하도록 관리합니다.

```typescript
// flyweightFactory.ts
import { Flyweight, ConcreteFlyweight } from './flyweight';

export class FlyweightFactory {
  private flyweights: { [key: string]: Flyweight } = {};

  public getFlyweight(key: string): Flyweight {
    if (!(key in this.flyweights)) {
      console.log(`새로운 플라이웨이트 생성: ${key}`);
      this.flyweights[key] = new ConcreteFlyweight(key);
    } else {
      console.log(`기존 플라이웨이트 재사용: ${key}`);
    }
    return this.flyweights[key];
  }

  public getFlyweightCount(): number {
    return Object.keys(this.flyweights).length;
  }
}
```

### 3.3 클라이언트 코드 예시

```typescript
// client.ts
import { FlyweightFactory } from './flyweightFactory';

// 팩토리 생성
const factory = new FlyweightFactory();

// 플라이웨이트 객체를 요청 (내부 상태를 기준으로 공유)
const flyweightA1 = factory.getFlyweight("A");
const flyweightA2 = factory.getFlyweight("A"); // 동일 키 "A"이므로 재사용

const flyweightB = factory.getFlyweight("B");

// 외부 상태를 전달하여 동작 수행
flyweightA1.operation("첫 번째 외부 상태");
flyweightA2.operation("두 번째 외부 상태");
flyweightB.operation("다른 외부 상태");

console.log(`플라이웨이트 객체 총 개수: ${factory.getFlyweightCount()}`);

// 출력 예시:
// 새로운 플라이웨이트 생성: A
// 기존 플라이웨이트 재사용: A
// 새로운 플라이웨이트 생성: B
// ConcreteFlyweight: 내부 상태 = A, 외부 상태 = 첫 번째 외부 상태
// ConcreteFlyweight: 내부 상태 = A, 외부 상태 = 두 번째 외부 상태
// ConcreteFlyweight: 내부 상태 = B, 외부 상태 = 다른 외부 상태
// 플라이웨이트 객체 총 개수: 2
```

- **구현 포인트:**  
  - **내부 상태 공유:** `ConcreteFlyweight` 클래스는 생성 시 전달된 내부 상태(예: 문자열 `A`, `B`)를 보유하며, 이를 재사용합니다.  
  - **외부 상태 분리:** 클라이언트는 `operation()` 메서드를 호출할 때마다 외부 상태를 매개변수로 전달합니다.  
  - **객체 재사용:** `FlyweightFactory`를 통해 동일한 내부 상태를 가진 객체는 재사용되므로, 메모리 사용을 최소화할 수 있습니다.

---

## 4. 장단점 및 고려 사항

### 장점
- **메모리 절감:**  
  - 동일한 데이터를 공유하여 많은 수의 객체를 생성할 때 메모리 사용량을 현저히 줄일 수 있습니다.
  
- **객체 생성 비용 감소:**  
  - 객체 재사용을 통해 초기화 및 생성 비용을 줄이고, 성능을 개선할 수 있습니다.

- **유연한 상태 관리:**  
  - 내부 상태와 외부 상태를 명확하게 분리하여, 객체의 재사용성과 유지보수성을 높입니다.

### 단점
- **복잡한 설계:**  
  - 내부 상태와 외부 상태를 분리하는 추가 설계가 필요하며, 코드 구조가 복잡해질 수 있습니다.
  
- **외부 상태 관리 부담:**  
  - 클라이언트는 각 객체에 대해 외부 상태를 별도로 관리해야 하므로, 상태 전달 및 동기화가 필요할 수 있습니다.

### 추가 고려 사항
- **동시성 및 스레드 안전:**  
  - 다중 스레드 환경에서 플라이웨이트 객체 공유 시, 외부 상태 전달과 객체 접근에 대한 동기화가 필요할 수 있습니다.
  
- **적용 범위:**  
  - 플라이웨이트 패턴은 객체의 수가 매우 많고, 내부 상태가 공유 가능한 경우에 유리합니다. 모든 상황에 무조건 적용할 수 있는 패턴은 아니므로, 사용 여부를 신중히 판단해야 합니다.
  
- **테스트 및 모니터링:**  
  - 객체 재사용 및 외부 상태 적용에 따른 부작용을 방지하기 위해, 단위 테스트와 통합 테스트를 통해 올바른 동작을 검증합니다.

---

## 5. 참고 자료

- [Refactoring Guru - Flyweight Pattern](https://refactoring.guru/design-patterns/flyweight)  
- _Design Patterns: Elements of Reusable Object-Oriented Software_ - Erich Gamma 외  
- _Head First Design Patterns_ - Eric Freeman

---

## 마무리

플라이웨이트 패턴은 다량의 유사 객체가 필요한 상황에서 메모리 사용을 최적화하고, 객체 생성 비용을 줄이는 데 매우 효과적인 디자인 기법입니다.  
실제 프로젝트에서는 문서 편집기, 게임 개발, 그래픽 시스템 등 다양한 분야에서 객체의 공유와 상태 분리를 통해 성능과 자원 활용도를 크게 향상시킬 수 있습니다.