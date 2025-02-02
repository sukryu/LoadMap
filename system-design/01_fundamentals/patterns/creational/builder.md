# 빌더 패턴

> **목표:**  
> - 복잡한 객체를 단계별로 구성하여 생성하는 과정을 단순화한다.  
> - 객체 생성과 표현을 분리하여, 동일한 생성 프로세스에서 다양한 표현 방식을 지원한다.  
> - 생성 과정의 유연성을 확보하여, 객체의 구성 요소가 많거나 옵션이 다양한 경우 효과적으로 관리할 수 있다.

---

## 1. 개념 개요

- **정의:**  
  빌더 패턴은 복잡한 객체를 생성하는 과정을 여러 단계로 나누어, 각 단계에서 객체의 일부분을 구성하고 최종적으로 완성된 객체를 반환하는 디자인 패턴입니다.  
  생성자(constructor)나 팩토리 패턴에 비해, 객체의 생성 과정이 복잡하거나 많은 옵션을 필요로 할 때 유용합니다.

- **왜 중요한가?**  
  - **복잡한 객체 생성:** 객체가 갖는 속성이나 내부 구성 요소가 많을 때, 하나의 생성자에 모든 인자를 전달하는 대신 단계별로 설정할 수 있습니다.
  - **가독성과 유지보수성:** 생성 로직을 분리하여 코드의 가독성을 높이고, 객체 구성 옵션 변경 시 유연하게 대처할 수 있습니다.
  - **불변 객체 지원:** 빌더를 통해 필요한 값들을 설정한 후, 불변 객체로 생성할 수 있으므로 안전한 상태를 보장할 수 있습니다.

- **해결하는 문제:**  
  - 생성자 인자나 설정 옵션이 많아지는 경우의 코드 복잡도 문제  
  - 동일한 객체 생성 과정에서 다양한 옵션 조합에 따른 객체 생성 지원  
  - 객체 생성 시 불필요한 중복 코드를 제거하고, 단계별 설정을 통해 가독성을 개선

---

## 2. 실무 적용 사례

- **복잡한 DTO(Data Transfer Object) 생성:**  
  여러 필드와 옵션을 가진 DTO를 생성할 때, 빌더 패턴을 통해 필요한 값만 설정하고 나머지는 기본값을 사용할 수 있습니다.

- **UI 컴포넌트 구성:**  
  화면 구성 요소(예: 대시보드, 폼 등)에서 여러 설정 값(레이아웃, 테마, 이벤트 핸들러 등)을 단계별로 구성할 때 빌더 패턴을 활용할 수 있습니다.

- **설정 파일 및 환경 구성:**  
  애플리케이션 초기화 시, 다양한 옵션과 설정을 적용하여 복잡한 객체(예: 서버 설정, 클라이언트 옵션 등)를 생성할 때 유용합니다.

---

## 3. 구현 방법

아래 예시는 TypeScript를 사용하여 **Car** 객체를 빌더 패턴으로 생성하는 방법을 보여줍니다.

### 3.1 Car 클래스와 빌더 클래스 정의

```typescript
// Car.ts
export class Car {
  public engine: string;
  public seats: number;
  public color: string;
  public gps: boolean;

  // 빌더를 통해 생성된 값을 Car 생성자에 전달받음
  constructor(builder: CarBuilder) {
    this.engine = builder.engine;
    this.seats = builder.seats;
    this.color = builder.color;
    this.gps = builder.gps;
  }

  public toString(): string {
    return `Car [Engine: ${this.engine}, Seats: ${this.seats}, Color: ${this.color}, GPS: ${this.gps}]`;
  }
}
```

```typescript
// CarBuilder.ts
import { Car } from './Car';

export class CarBuilder {
  public engine: string = 'Standard Engine';
  public seats: number = 4;
  public color: string = 'White';
  public gps: boolean = false;

  public setEngine(engine: string): CarBuilder {
    this.engine = engine;
    return this;
  }

  public setSeats(seats: number): CarBuilder {
    this.seats = seats;
    return this;
  }

  public setColor(color: string): CarBuilder {
    this.color = color;
    return this;
  }

  public setGPS(gps: boolean): CarBuilder {
    this.gps = gps;
    return this;
  }

  public build(): Car {
    return new Car(this);
  }
}
```

### 3.2 클라이언트 코드 사용 예시

```typescript
// index.ts
import { CarBuilder } from './CarBuilder';

const myCar = new CarBuilder()
  .setEngine('V8 Engine')
  .setSeats(2)
  .setColor('Red')
  .setGPS(true)
  .build();

console.log(myCar.toString());
// 출력: Car [Engine: V8 Engine, Seats: 2, Color: Red, GPS: true]
```

- **구현 포인트:**  
  - **단계별 설정:** 빌더 클래스(`CarBuilder`)의 메서드들을 통해 필요한 속성을 순차적으로 설정합니다.
  - **유연한 확장:** 기본값을 제공함으로써, 필수 항목과 선택 항목을 구분하여 객체 생성 시 유연하게 옵션을 추가할 수 있습니다.
  - **불변 객체 생성:** 최종적으로 `build()` 메서드를 호출하여 완성된 객체를 생성하면, 해당 객체는 빌더를 통해 설정된 상태를 갖게 됩니다.

---

## 4. 장단점 및 고려 사항

### 장점
- **가독성 향상:**  
  복잡한 객체 생성 시, 빌더 패턴을 통해 생성 과정을 명확하게 단계별로 구분할 수 있습니다.
  
- **유연한 객체 생성:**  
  필요한 속성만 선택적으로 설정할 수 있어, 다양한 객체 구성 옵션을 쉽게 지원합니다.
  
- **불변성 확보:**  
  빌더 패턴을 활용하여 한 번 설정된 객체의 상태를 변경하지 않도록 할 수 있습니다.

### 단점
- **추가 클래스 증가:**  
  객체 생성 로직을 별도의 빌더 클래스로 분리함에 따라 클래스 수가 늘어나고, 관리가 복잡해질 수 있습니다.
  
- **복잡한 설계:**  
  단순한 객체 생성에는 오히려 불필요한 추상화가 될 수 있으므로, 대상 객체의 복잡도가 높은 경우에 적합합니다.

### 추가 고려 사항
- **성능 최적화:**  
  빌더 패턴은 객체 생성 시 여러 메서드 호출이 발생하므로, 성능에 민감한 시스템에서는 주의 깊게 사용해야 합니다.
  
- **테스트 전략:**  
  빌더 클래스를 모듈 단위로 테스트하여, 각 단계별 설정 값이 올바르게 적용되는지 확인하는 단위 테스트를 작성합니다.
  
- **동시성 이슈:**  
  빌더 인스턴스는 일반적으로 단일 스레드에서 사용되지만, 멀티스레드 환경에서는 별도 인스턴스를 생성하거나 동기화 처리를 고려해야 합니다.

---

## 5. 참고 자료

- [Refactoring Guru - Builder Pattern](https://refactoring.guru/design-patterns/builder)  
- _Design Patterns: Elements of Reusable Object-Oriented Software_ - Erich Gamma 외  
- _Head First Design Patterns_ - Eric Freeman

---

## 마무리

빌더 패턴은 복잡한 객체 생성 과정을 단계별로 관리하여 가독성과 유지보수성을 높이는 효과적인 설계 기법입니다.  
실제 프로젝트에서는 객체의 옵션이 많거나 생성 과정이 복잡한 경우 빌더 패턴을 도입하여 코드의 명확성과 유연성을 확보할 수 있습니다.