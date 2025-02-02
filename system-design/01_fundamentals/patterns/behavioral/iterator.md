# 이터레이터 패턴

> **목표:**  
> - 컬렉션(집합)의 내부 구조를 노출하지 않고, 순차적으로 접근할 수 있는 방법을 제공한다.  
> - 클라이언트가 컬렉션의 내부 구현에 의존하지 않고, 동일한 방식으로 요소들을 순회할 수 있도록 한다.  
> - 다양한 데이터 구조에 대해 일관된 순회 메커니즘을 제공하여 코드의 재사용성과 확장성을 높인다.

---

## 1. 개념 개요

- **정의:**  
  이터레이터 패턴은 컬렉션의 요소들을 순회(traverse)할 수 있는 인터페이스를 제공하며, 컬렉션의 내부 구현 방식과 무관하게 외부에서 요소들에 접근할 수 있도록 하는 행동 패턴입니다.  
  이 패턴을 통해 클라이언트는 컬렉션의 구조를 신경쓰지 않고 순차적인 접근이 가능해집니다.

- **왜 중요한가?**  
  - **추상화:** 컬렉션의 내부 데이터 구조를 감추고, 일관된 방식으로 요소를 순회할 수 있도록 함으로써, 컬렉션 변경 시 클라이언트 코드의 영향을 최소화합니다.  
  - **재사용성 및 확장성:** 다양한 컬렉션에 대해 동일한 순회 인터페이스를 제공함으로써, 코드를 재사용하고 새로운 데이터 구조에 쉽게 적용할 수 있습니다.
  - **복잡도 감소:** 복잡한 내부 구조를 외부에 노출하지 않으므로, 클라이언트 코드의 복잡도를 낮추고 가독성을 향상시킵니다.

- **해결하는 문제:**  
  - 컬렉션 내부의 복잡한 구현 방식을 감추고, 요소에 대한 순차 접근을 위한 단일 인터페이스를 제공하여 결합도를 낮춥니다.
  - 다양한 컬렉션(배열, 연결 리스트 등)에 대해 일관된 접근 방법을 적용할 수 있도록 합니다.

---

## 2. 실무 적용 사례

- **컬렉션 순회:**  
  - 배열, 리스트, 트리 등 다양한 자료구조에서 요소들을 순차적으로 접근할 때 사용됩니다.
  
- **UI 컴포넌트 렌더링:**  
  - 복합 UI 컴포넌트(예: 메뉴, 트리 뷰 등)의 자식 요소들을 순회하며 렌더링할 때 유용합니다.
  
- **데이터 처리 파이프라인:**  
  - 데이터베이스 결과 집합이나 파일의 레코드를 순차적으로 읽어 처리하는 과정에 적용할 수 있습니다.

---

## 3. 구현 방법

아래 예제는 TypeScript를 사용하여 이터레이터 패턴을 구현하는 방법을 보여줍니다.  
예제에서는 간단한 숫자 컬렉션을 대상으로 이터레이터를 생성하여, 컬렉션의 요소들을 순차적으로 접근하는 구조를 구현합니다.

### 3.1 이터레이터 인터페이스 정의

```typescript
// Iterator.ts
export interface Iterator<T> {
  // 컬렉션에 다음 요소가 있는지 확인
  hasNext(): boolean;
  // 다음 요소를 반환하고, 커서를 이동
  next(): T;
  // 커서를 초기 위치로 재설정 (필요에 따라 구현)
  reset(): void;
}
```

### 3.2 컬렉션(집합) 인터페이스 정의 및 구체 클래스 구현

```typescript
// Aggregate.ts
import { Iterator } from './Iterator';

export interface Aggregate<T> {
  // 해당 컬렉션에 대한 이터레이터를 생성하여 반환
  createIterator(): Iterator<T>;
}
```

```typescript
// NumberCollection.ts
import { Aggregate } from './Aggregate';
import { Iterator } from './Iterator';

export class NumberCollection implements Aggregate<number> {
  private items: number[] = [];

  public add(item: number): void {
    this.items.push(item);
  }

  public getItems(): number[] {
    return this.items;
  }

  public createIterator(): Iterator<number> {
    return new NumberIterator(this.items);
  }
}

// 내부에서 사용할 이터레이터 구현
class NumberIterator implements Iterator<number> {
  private collection: number[];
  private current: number = 0;

  constructor(collection: number[]) {
    this.collection = collection;
  }

  public hasNext(): boolean {
    return this.current < this.collection.length;
  }

  public next(): number {
    if (this.hasNext()) {
      return this.collection[this.current++];
    }
    throw new Error("이터레이터의 끝에 도달했습니다.");
  }

  public reset(): void {
    this.current = 0;
  }
}
```

### 3.3 클라이언트 코드 예시

```typescript
// client.ts
import { NumberCollection } from './NumberCollection';

const collection = new NumberCollection();
collection.add(10);
collection.add(20);
collection.add(30);
collection.add(40);

const iterator = collection.createIterator();

console.log("컬렉션 순회 시작:");
while (iterator.hasNext()) {
  console.log(iterator.next());
}

iterator.reset();
console.log("이터레이터 초기화 후 재순회:");
while (iterator.hasNext()) {
  console.log(iterator.next());
}

// 출력 예시:
// 컬렉션 순회 시작:
// 10
// 20
// 30
// 40
// 이터레이터 초기화 후 재순회:
// 10
// 20
// 30
// 40
```

- **구현 포인트:**  
  - **Iterator 인터페이스:** `hasNext()`, `next()`, `reset()` 등의 메서드를 통해 컬렉션 요소에 대한 순회 로직을 정의합니다.  
  - **Aggregate 인터페이스:** 컬렉션(집합) 객체가 자신만의 이터레이터를 생성하여 반환할 수 있도록 `createIterator()` 메서드를 제공합니다.  
  - **클라이언트 코드:** 이터레이터를 통해 컬렉션의 내부 구현과 무관하게 요소들을 순회할 수 있습니다.

---

## 4. 장단점 및 고려 사항

### 장점
- **내부 구현 캡슐화:**  
  - 컬렉션의 내부 구조를 클라이언트에 노출하지 않고, 일관된 인터페이스를 통해 요소에 접근할 수 있습니다.
  
- **유연한 순회:**  
  - 다양한 컬렉션 구조에 대해 동일한 순회 방법을 제공하여, 코드 재사용성과 확장성을 높입니다.
  
- **단순화된 클라이언트 코드:**  
  - 복잡한 컬렉션 순회 로직을 이터레이터 내부로 감추어, 클라이언트 코드를 간결하게 유지할 수 있습니다.

### 단점
- **추가 객체 생성:**  
  - 각 컬렉션에 대해 별도의 이터레이터 객체가 생성되므로, 매우 큰 규모의 데이터 처리 시 약간의 메모리 오버헤드가 발생할 수 있습니다.
  
- **동기화 문제:**  
  - 멀티스레드 환경에서 컬렉션의 변경과 이터레이터 순회가 동시에 발생하는 경우, 별도의 동기화 처리가 필요할 수 있습니다.

### 추가 고려 사항
- **동시성:**  
  - 컬렉션이 변경될 가능성이 있는 환경에서는 이터레이터 생성 시 컬렉션의 스냅샷을 사용하거나, 변경에 따른 예외 처리를 고려해야 합니다.
  
- **테스트:**  
  - 이터레이터의 순회 로직과 reset 기능 등 각 메서드에 대해 단위 테스트를 작성하여 올바른 동작을 검증합니다.
  
- **확장성:**  
  - 다른 컬렉션(연결 리스트, 트리 등)에 대해서도 동일한 이터레이터 인터페이스를 적용하여 일관된 접근 방식을 유지할 수 있도록 설계합니다.

---

## 5. 참고 자료

- [Refactoring Guru - Iterator Pattern](https://refactoring.guru/design-patterns/iterator)  
- _Design Patterns: Elements of Reusable Object-Oriented Software_ - Erich Gamma 외  
- _Head First Design Patterns_ - Eric Freeman

---

## 마무리

이터레이터 패턴은 컬렉션의 내부 구조를 감추면서도, 클라이언트가 일관된 방식으로 요소에 접근할 수 있도록 하는 강력한 설계 기법입니다.  
실제 프로젝트에서는 다양한 데이터 구조에 대해 동일한 순회 인터페이스를 제공하여, 코드의 재사용성과 유지보수성을 크게 향상시킬 수 있습니다.