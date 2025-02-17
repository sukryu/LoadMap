# 템플릿 메서드 패턴

> **목표:**  
> - 알고리즘의 전체적인 골격(템플릿)을 미리 정의하고, 세부 단계는 서브클래스에서 구체적으로 구현할 수 있도록 한다.  
> - 공통된 처리 절차를 재사용하면서도, 특정 단계의 구현을 하위 클래스에서 변경할 수 있게 하여 코드의 재사용성과 확장성을 높인다.  
> - 상속을 활용해 알고리즘의 흐름은 일정하게 유지하면서도 세부 구현은 유연하게 변경할 수 있도록 한다.

---

## 1. 개념 개요

- **정의:**  
  템플릿 메서드 패턴은 알고리즘의 구조(전체 흐름)를 추상 클래스로 정의하고, 알고리즘의 특정 단계는 서브클래스에서 오버라이드하여 구체적으로 구현하도록 하는 디자인 패턴입니다.  
  즉, 알고리즘의 "템플릿"인 메서드가 전체 절차를 정의하고, 공통 단계는 기본 구현을 제공하며, 변하는 단계는 추상 메서드나 훅(Hook)을 통해 서브클래스에서 구현합니다.

- **왜 중요한가?**  
  - **코드 재사용 및 일관성:** 공통 로직을 추상 클래스에 정의하여 여러 서브클래스가 이를 재사용하므로, 중복 코드를 줄이고 알고리즘의 일관성을 유지할 수 있습니다.  
  - **유연한 확장:** 하위 클래스에서 특정 단계의 구현만 변경하면 되므로, 알고리즘 전체를 변경하지 않고도 새로운 기능을 손쉽게 도입할 수 있습니다.  
  - **조건문 제거:** 복잡한 조건문 없이, 상태나 조건에 따라 서로 다른 동작을 서브클래스에서 분리하여 구현할 수 있습니다.

- **해결하는 문제:**  
  - 알고리즘의 공통적인 처리 과정을 한 곳에 모아둠으로써, 유지보수와 확장이 용이하도록 하고, 세부 단계의 변화에 따라 코드 수정 범위를 최소화합니다.

---

## 2. 실무 적용 사례

- **음료 제조 과정:**  
  - 커피와 차 같이 공통된 절차(물 끓이기, 컵에 따르기 등)를 가지지만, 우려내기 방식이나 첨가물은 각각 다를 경우에 적용됩니다.
  
- **데이터 처리 파이프라인:**  
  - 데이터 읽기, 처리, 저장의 기본 흐름은 동일하지만, 데이터 처리 로직이나 포맷은 상황에 따라 달라질 때 유용합니다.
  
- **게임 루프 및 캐릭터 행동:**  
  - 게임 캐릭터의 행동 순서를 템플릿 메서드로 정의하고, 각 캐릭터 별로 공격, 이동, 방어 등의 세부 행동을 구현할 수 있습니다.

---

## 3. 구현 방법

아래 예제는 TypeScript를 사용하여 템플릿 메서드 패턴을 구현하는 방법을 보여줍니다.  
예제에서는 커피와 차를 준비하는 과정을 공통 템플릿으로 정의하고, 각 음료에 따른 세부 단계(우려내기 및 첨가물 추가)를 서브클래스에서 구현합니다.

### 3.1 추상 클래스(템플릿) 정의

```typescript
// CaffeineBeverage.ts
export abstract class CaffeineBeverage {
  // 템플릿 메서드: 전체 제조 과정을 정의하며, 서브클래스에서 오버라이드할 수 있는 단계를 포함함.
  public prepareRecipe(): void {
    this.boilWater();
    this.brew();
    this.pourInCup();
    this.addCondiments();
  }

  protected boilWater(): void {
    console.log("물 끓이는 중");
  }

  // 서브클래스에서 구체적으로 우려내는 방법을 구현
  protected abstract brew(): void;

  protected pourInCup(): void {
    console.log("컵에 따르는 중");
  }

  // 서브클래스에서 구체적으로 첨가물을 추가하는 방법을 구현
  protected abstract addCondiments(): void;
}
```

### 3.2 구체적인 서브클래스 구현

```typescript
// Coffee.ts
import { CaffeineBeverage } from './CaffeineBeverage';

export class Coffee extends CaffeineBeverage {
  protected brew(): void {
    console.log("커피를 우려내는 중");
  }

  protected addCondiments(): void {
    console.log("설탕과 우유를 추가하는 중");
  }
}
```

```typescript
// Tea.ts
import { CaffeineBeverage } from './CaffeineBeverage';

export class Tea extends CaffeineBeverage {
  protected brew(): void {
    console.log("차를 우려내는 중");
  }

  protected addCondiments(): void {
    console.log("레몬을 추가하는 중");
  }
}
```

### 3.3 클라이언트 코드 예시

```typescript
// client.ts
import { Coffee } from './Coffee';
import { Tea } from './Tea';

const coffee = new Coffee();
console.log("커피 준비:");
coffee.prepareRecipe();

const tea = new Tea();
console.log("차 준비:");
tea.prepareRecipe();

// 예상 출력:
// 커피 준비:
// 물 끓이는 중
// 커피를 우려내는 중
// 컵에 따르는 중
// 설탕과 우유를 추가하는 중
//
// 차 준비:
// 물 끓이는 중
// 차를 우려내는 중
// 컵에 따르는 중
// 레몬을 추가하는 중
```

- **구현 포인트:**  
  - **템플릿 메서드:** `prepareRecipe()`는 음료 제조 과정의 전체 흐름을 정의하며, 공통 단계(물 끓이기, 컵에 따르기)는 추상 클래스에서 구현하고, 우려내기 및 첨가물 추가는 서브클래스에서 구현합니다.  
  - **서브클래스 오버라이딩:** `Coffee`와 `Tea`는 각자의 방식으로 `brew()`와 `addCondiments()`를 오버라이드하여 서로 다른 음료 제조 과정을 구현합니다.

---

## 4. 장단점 및 고려 사항

### 장점
- **코드 재사용성:**  
  - 공통 절차를 추상 클래스에 구현함으로써 중복 코드를 줄이고, 전체 알고리즘의 구조를 재사용할 수 있습니다.
  
- **유연성:**  
  - 하위 클래스에서 필요한 단계만 변경하면 되므로, 새로운 알고리즘이나 변형을 쉽게 추가할 수 있습니다.
  
- **일관된 알고리즘 구조:**  
  - 전체 흐름이 템플릿 메서드에 의해 고정되어 있어, 알고리즘의 일관성을 유지할 수 있습니다.

### 단점
- **상속에 의존:**  
  - 템플릿 메서드 패턴은 상속을 기반으로 하므로, 자바스크립트/TypeScript 같은 프로토타입 기반 언어에서는 다소 제약이 있을 수 있습니다.
  
- **유연성 제한:**  
  - 전체 알고리즘 구조가 고정되어 있으므로, 알고리즘의 흐름을 완전히 변경하기는 어렵습니다.

### 추가 고려 사항
- **훅(Hook) 메서드 도입:**  
  - 선택적으로 오버라이드할 수 있는 훅 메서드를 템플릿에 포함하여, 기본 동작에 추가적인 기능을 쉽게 삽입할 수 있도록 할 수 있습니다.
  
- **테스트 및 유지보수:**  
  - 템플릿 메서드와 하위 클래스의 각 단계를 독립적으로 테스트하여, 전체 알고리즘이 의도대로 작동하는지 검증해야 합니다.
  
- **확장성:**  
  - 알고리즘의 특정 단계가 복잡할 경우, 해당 부분을 별도의 클래스로 분리하거나 전략 패턴 등 다른 디자인 패턴과 결합하여 확장할 수 있습니다.

---

## 5. 참고 자료

- [Refactoring Guru - Template Method Pattern](https://refactoring.guru/design-patterns/template-method)  
- _Design Patterns: Elements of Reusable Object-Oriented Software_ - Erich Gamma 외  
- _Head First Design Patterns_ - Eric Freeman

---

## 마무리

템플릿 메서드 패턴은 알고리즘의 전체적인 흐름을 미리 정의하고, 개별 단계의 구현을 서브클래스에 위임함으로써 코드의 재사용성과 일관성을 높이는 강력한 설계 기법입니다.  
실제 프로젝트에서는 음료 제조, 데이터 처리, 게임 루프 등 다양한 분야에서 이 패턴을 활용하여 유지보수성과 확장성이 높은 소프트웨어 아키텍처를 구현할 수 있습니다.