# 전략 패턴

> **목표:**  
> - 동일한 문제를 해결하기 위한 다양한 알고리즘(전략)을 캡슐화하여, 클라이언트 코드에서 쉽게 교체할 수 있도록 한다.  
> - 실행 시점에 알고리즘을 선택할 수 있도록 하여, 시스템의 유연성과 확장성을 높인다.  
> - 조건문 없이도 알고리즘을 변경할 수 있어 코드의 가독성과 유지보수성을 향상시킨다.

---

## 1. 개념 개요

- **정의:**  
  전략 패턴은 동일한 문제를 해결하기 위한 여러 알고리즘(전략)을 별도의 클래스로 캡슐화하여, 클라이언트가 실행 시점에 원하는 전략을 선택하여 사용할 수 있도록 하는 행동 패턴입니다.  
  클라이언트는 추상화된 전략 인터페이스를 통해 알고리즘에 접근하며, 구체적인 전략 클래스는 해당 인터페이스를 구현합니다.

- **왜 중요한가?**  
  - **알고리즘 교체의 유연성:**  
    전략 패턴을 사용하면, 클라이언트 코드의 변경 없이 알고리즘을 동적으로 변경할 수 있으므로, 조건문(if/else)으로 복잡하게 분기하는 것을 피할 수 있습니다.
  - **결합도 감소:**  
    클라이언트는 특정 알고리즘의 구체적인 구현에 의존하지 않고, 추상화된 인터페이스에만 의존하게 되어 결합도가 낮아집니다.
  - **확장 용이성:**  
    새로운 전략이 필요할 때, 기존 코드를 수정하지 않고 새로운 전략 클래스를 추가함으로써 기능을 쉽게 확장할 수 있습니다.

- **해결하는 문제:**  
  - 여러 알고리즘이 존재하는 경우, 이를 조건문으로 분기 처리하면 코드가 복잡해지고 유지보수가 어려워집니다.
  - 각 알고리즘을 독립적으로 캡슐화하여 관리함으로써, 코드 재사용과 테스트가 용이해집니다.

---

## 2. 실무 적용 사례

- **결제 시스템:**  
  - 다양한 결제 방식(신용카드, 페이팔, 가상계좌 등)을 각각의 전략으로 구현하여, 사용자가 결제 시점에 원하는 결제 방식을 선택할 수 있도록 합니다.
  
- **정렬 알고리즘:**  
  - 데이터 정렬 시, 상황에 따라 버블 정렬, 퀵 정렬, 병합 정렬 등의 알고리즘을 전략으로 캡슐화하여, 데이터 특성에 맞는 정렬 방식을 선택할 수 있습니다.
  
- **압축 알고리즘:**  
  - 파일 압축 시, ZIP, RAR, GZIP 등 다양한 압축 방법을 전략으로 구현하여, 파일 크기나 압축 속도 등 조건에 따라 적절한 압축 전략을 사용할 수 있습니다.

---

## 3. 구현 방법

아래 예제는 TypeScript를 사용하여 전략 패턴을 구현하는 방법을 보여줍니다.  
예제에서는 간단한 텍스트 압축 애플리케이션을 대상으로, 여러 압축 전략(예: 단순 압축, 고급 압축)을 선택할 수 있도록 구현합니다.

### 3.1 전략 인터페이스 정의

```typescript
// CompressionStrategy.ts
export interface CompressionStrategy {
  compress(data: string): string;
}
```

### 3.2 구체적인 전략 클래스 구현

```typescript
// SimpleCompression.ts
import { CompressionStrategy } from './CompressionStrategy';

export class SimpleCompression implements CompressionStrategy {
  public compress(data: string): string {
    // 단순 예시: 데이터를 모두 대문자로 변환하여 "압축"하는 방식
    console.log("SimpleCompression 전략 사용");
    return data.toUpperCase();
  }
}
```

```typescript
// AdvancedCompression.ts
import { CompressionStrategy } from './CompressionStrategy';

export class AdvancedCompression implements CompressionStrategy {
  public compress(data: string): string {
    // 단순 예시: 문자열의 길이를 반환하는 방식 (실제 압축 알고리즘은 아님)
    console.log("AdvancedCompression 전략 사용");
    return `압축된 데이터 길이: ${data.length}`;
  }
}
```

### 3.3 컨텍스트 클래스 구현

컨텍스트(Context) 클래스는 현재 사용중인 전략을 보유하며, 클라이언트의 요청에 따라 해당 전략을 실행합니다.

```typescript
// CompressionContext.ts
import { CompressionStrategy } from './CompressionStrategy';

export class CompressionContext {
  private strategy: CompressionStrategy;

  constructor(strategy: CompressionStrategy) {
    this.strategy = strategy;
  }

  public setStrategy(strategy: CompressionStrategy): void {
    this.strategy = strategy;
  }

  public compressData(data: string): string {
    return this.strategy.compress(data);
  }
}
```

### 3.4 클라이언트 코드 예시

```typescript
// client.ts
import { CompressionContext } from './CompressionContext';
import { SimpleCompression } from './SimpleCompression';
import { AdvancedCompression } from './AdvancedCompression';

const data = "Example data for compression";

// 기본 전략: SimpleCompression
const context = new CompressionContext(new SimpleCompression());
console.log("압축 결과:", context.compressData(data));

// 전략 변경: AdvancedCompression
context.setStrategy(new AdvancedCompression());
console.log("압축 결과:", context.compressData(data));

// 예상 출력 예시:
// SimpleCompression 전략 사용
// 압축 결과: EXAMPLE DATA FOR COMPRESSION
// AdvancedCompression 전략 사용
// 압축 결과: 압축된 데이터 길이: 31
```

- **구현 포인트:**  
  - **전략 인터페이스:** `CompressionStrategy`는 모든 압축 전략이 따라야 할 메서드(`compress`)를 정의합니다.  
  - **구체 전략 클래스:** `SimpleCompression`과 `AdvancedCompression`은 각각의 압축 방식을 구현하며, 클라이언트가 원하는 알고리즘을 선택할 수 있도록 합니다.  
  - **컨텍스트 클래스:** `CompressionContext`는 현재 선택된 전략을 보유하고 있으며, 클라이언트의 요청에 따라 해당 전략을 적용하여 데이터를 압축합니다.

---

## 4. 장단점 및 고려 사항

### 장점
- **알고리즘 교체의 유연성:**  
  - 전략을 동적으로 변경할 수 있어, 실행 시점에 최적의 알고리즘을 선택할 수 있습니다.
  
- **결합도 감소:**  
  - 클라이언트는 추상화된 전략 인터페이스만 의존하므로, 구체적인 알고리즘 구현 변경에 영향을 받지 않습니다.
  
- **확장 용이성:**  
  - 새로운 전략을 추가할 때 기존 코드를 수정할 필요 없이, 새로운 전략 클래스를 도입할 수 있습니다.

### 단점
- **객체 수 증가:**  
  - 각 전략이 별도의 클래스로 구현되므로, 클래스 수가 증가하여 코드 구조가 복잡해질 수 있습니다.
  
- **전략 선택 책임:**  
  - 클라이언트가 적절한 전략을 선택해야 하므로, 선택 기준이 명확하지 않으면 잘못된 전략이 사용될 수 있습니다.

### 추가 고려 사항
- **전략 결정 로직:**  
  - 전략 선택을 자동화하기 위해 팩토리 패턴이나 의존성 주입(DI)을 함께 사용할 수 있습니다.
  
- **테스트:**  
  - 각 전략의 동작을 단위 테스트로 검증하고, 컨텍스트에서 전략 변경 시 예상대로 작동하는지 통합 테스트로 확인해야 합니다.
  
- **성능:**  
  - 전략에 따라 성능 차이가 클 수 있으므로, 실제 상황에 맞는 최적의 전략을 선택할 수 있도록 벤치마킹이 필요할 수 있습니다.

---

## 5. 참고 자료

- [Refactoring Guru - Strategy Pattern](https://refactoring.guru/design-patterns/strategy)  
- _Design Patterns: Elements of Reusable Object-Oriented Software_ - Erich Gamma 외  
- _Head First Design Patterns_ - Eric Freeman

---

## 마무리

전략 패턴은 동일한 문제에 대해 다양한 알고리즘을 독립적으로 캡슐화하여, 실행 시점에 유연하게 교체할 수 있도록 하는 강력한 설계 기법입니다.  
실제 프로젝트에서는 결제 시스템, 정렬 알고리즘, 압축 알고리즘 등 다양한 분야에서 전략 패턴을 활용하여 코드의 유연성과 유지보수성을 크게 향상시킬 수 있습니다.