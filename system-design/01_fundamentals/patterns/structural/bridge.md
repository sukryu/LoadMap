# 브릿지 패턴

> **목표:**  
> - 추상화(Abstraction)와 구현(Implementation)을 분리하여, 두 계층이 독립적으로 확장 및 변경 가능하도록 한다.  
> - 복잡한 계층 구조를 단순화하고, 서로 다른 구현을 유연하게 결합할 수 있도록 한다.  
> - 시스템의 확장성과 유지보수성을 높인다.

---

## 1. 개념 개요

- **정의:**  
  브릿지 패턴은 추상화와 구현을 별도의 계층으로 분리하여, 두 계층이 독립적으로 변화할 수 있도록 하는 구조 패턴입니다.  
  추상화 계층은 고수준의 제어 로직을 담당하고, 구현 계층은 저수준의 기능을 수행합니다. 이 두 계층은 브릿지를 통해 연결됩니다.

- **왜 중요한가?**  
  - **독립적 확장:** 추상화와 구현을 분리함으로써, 각각을 독립적으로 확장하거나 수정할 수 있어 변화에 유연하게 대응할 수 있습니다.  
  - **복잡도 감소:** 상속을 통한 복잡한 계층 구조를 피하고, 서로 다른 구현을 쉽게 교체할 수 있도록 합니다.  
  - **유지보수성 향상:** 코드의 결합도를 낮춰, 한쪽 계층의 변경이 다른 계층에 미치는 영향을 최소화합니다.

- **해결하는 문제:**  
  - 다중 상속이 불가능한 언어에서 발생할 수 있는 계층 구조의 결합도 문제  
  - 추상화와 구현의 변화가 서로 독립적으로 이루어져야 하는 요구 사항을 충족

---

## 2. 실무 적용 사례

- **UI 프레임워크:**  
  - 창(Window)과 운영체제별 구현(Windows, macOS 등)을 분리하여, 창의 추상화된 기능과 OS별 그리기 구현을 독립적으로 관리
- **그래픽 시스템:**  
  - 도형(Shape) 추상화와 다양한 그리기 API(벡터, 래스터 등)를 분리하여, 도형의 공통 기능은 그대로 두면서 다양한 표현 방식을 지원
- **데이터베이스 드라이버:**  
  - 데이터베이스에 대한 추상화 계층과 실제 연결 구현을 분리하여, 새로운 데이터베이스 추가 시 추상화 계층의 변경 없이 구현만 확장

---

## 3. 구현 방법

### 3.1 TypeScript를 이용한 브릿지 패턴 예제

이번 예제에서는 **도형(Shape)** 추상화와 **그리기 API(DrawingAPI)** 구현을 분리하여, 원(Circle)을 그리는 예제를 구현합니다.

#### **1) 구현 계층 (Implementor) 인터페이스 정의**

```typescript
// drawingAPI.ts
export interface DrawingAPI {
  drawCircle(x: number, y: number, radius: number): void;
}
```

#### **2) 구체적인 구현 클래스 (ConcreteImplementor) 구현**

```typescript
// drawingAPI1.ts
import { DrawingAPI } from './drawingAPI';

export class DrawingAPI1 implements DrawingAPI {
  public drawCircle(x: number, y: number, radius: number): void {
    console.log(`DrawingAPI1: 원을 그립니다. 위치 (${x}, ${y}), 반지름 ${radius}`);
  }
}
```

```typescript
// drawingAPI2.ts
import { DrawingAPI } from './drawingAPI';

export class DrawingAPI2 implements DrawingAPI {
  public drawCircle(x: number, y: number, radius: number): void {
    console.log(`DrawingAPI2: 원을 그립니다. 위치 (${x}, ${y}), 반지름 ${radius}`);
  }
}
```

#### **3) 추상화 계층 (Abstraction) 클래스 정의**

```typescript
// shape.ts
import { DrawingAPI } from './drawingAPI';

export abstract class Shape {
  protected drawingAPI: DrawingAPI;

  constructor(drawingAPI: DrawingAPI) {
    this.drawingAPI = drawingAPI;
  }

  public abstract draw(): void;
  public abstract resizeByPercentage(pct: number): void;
}
```

#### **4) 구체적인 추상화 클래스 (Refined Abstraction) 구현**

```typescript
// circle.ts
import { Shape } from './shape';
import { DrawingAPI } from './drawingAPI';

export class Circle extends Shape {
  private x: number;
  private y: number;
  private radius: number;

  constructor(x: number, y: number, radius: number, drawingAPI: DrawingAPI) {
    super(drawingAPI);
    this.x = x;
    this.y = y;
    this.radius = radius;
  }

  public draw(): void {
    this.drawingAPI.drawCircle(this.x, this.y, this.radius);
  }

  public resizeByPercentage(pct: number): void {
    this.radius *= (pct / 100);
  }
}
```

#### **5) 클라이언트 코드 예시**

```typescript
// client.ts
import { Circle } from './circle';
import { DrawingAPI1 } from './drawingAPI1';
import { DrawingAPI2 } from './drawingAPI2';

// 두 개의 원을 각각 다른 그리기 API를 사용하여 생성
const circle1 = new Circle(5, 10, 10, new DrawingAPI1());
const circle2 = new Circle(15, 20, 20, new DrawingAPI2());

circle1.draw();  // DrawingAPI1을 통해 원을 그림
circle2.draw();  // DrawingAPI2를 통해 원을 그림

// 출력 예시:
// DrawingAPI1: 원을 그립니다. 위치 (5, 10), 반지름 10
// DrawingAPI2: 원을 그립니다. 위치 (15, 20), 반지름 20
```

- **구현 포인트:**  
  - **추상화 계층(Shape):** 고수준의 제어 로직(예, draw, resizeByPercentage)을 정의하며, 내부에 구현 계층(DrawingAPI)의 인스턴스를 보유합니다.  
  - **구체적 구현 계층(DrawingAPI1, DrawingAPI2):** 실제 그리기 로직을 담당하며, 추상화와 독립적으로 변화할 수 있습니다.  
  - **클라이언트 코드:** 추상화와 구현을 결합하는 방식으로, 서로 다른 구현을 쉽게 교체하여 사용할 수 있습니다.

---

## 4. 장단점 및 고려 사항

### 장점
- **독립적 확장:**  
  - 추상화 계층과 구현 계층을 분리하여, 각 계층이 독립적으로 확장 및 수정 가능
- **유연성 증가:**  
  - 서로 다른 구현을 동적으로 결합할 수 있어, 다양한 기능 조합이 가능
- **결합도 감소:**  
  - 상속 대신 구성(composition)을 사용하여, 시스템의 결합도를 낮추고 유지보수를 용이하게 함

### 단점
- **설계 복잡성:**  
  - 계층을 분리함으로써 전체 설계가 다소 복잡해질 수 있음
- **초기 설계 부담:**  
  - 추상화와 구현을 별도로 설계해야 하므로 초기 작업량이 증가할 수 있음

### 추가 고려 사항
- **성능 최적화:**  
  - 브릿지 계층을 통한 호출 오버헤드가 발생할 수 있으므로, 성능이 민감한 부분에 대해서는 최적화가 필요함
- **테스트 전략:**  
  - 추상화와 구현 계층을 별도로 테스트하여, 각 계층의 변화가 독립적으로 올바르게 동작하는지 검증
- **유지보수:**  
  - 두 계층 간의 인터페이스 정의와 문서화를 철저히 하여, 팀 내 협업과 코드 리뷰 시 혼선을 줄임

---

## 5. 참고 자료

- [Refactoring Guru - Bridge Pattern](https://refactoring.guru/design-patterns/bridge)  
- _Design Patterns: Elements of Reusable Object-Oriented Software_ - Erich Gamma 외  
- _Head First Design Patterns_ - Eric Freeman

---

## 마무리

브릿지 패턴은 추상화와 구현을 분리하여, 두 계층을 독립적으로 확장할 수 있는 유연한 구조를 제공합니다.  
실제 프로젝트에서는 복잡한 계층 구조를 단순화하고, 다양한 구현을 효과적으로 결합하여 유지보수성과 확장성을 높이는 데 큰 도움을 줍니다.