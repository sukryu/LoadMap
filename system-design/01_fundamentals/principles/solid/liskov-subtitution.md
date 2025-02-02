# 리스코프 치환 원칙 (Liskov Substitution Principle, LSP)

리스코프 치환 원칙은 **"프로그램에서 상위 클래스(또는 인터페이스)의 인스턴스를 하위 클래스로 대체해도 프로그램이 올바르게 동작해야 한다"**는 원칙입니다.  
즉, 하위 클래스는 상위 클래스의 계약(메서드의 기능, 반환 값, 부수 효과 등)을 준수하여, 상위 클래스 객체를 사용하는 모든 곳에서 문제 없이 동작해야 합니다.

---

## 1. LSP의 개념 이해

### 1.1. 기본 개념
- **대체 가능성(Substitutability):**  
  상위 클래스의 인스턴스를 사용하는 곳에 하위 클래스의 인스턴스를 넣어도, 프로그램의 기능이 깨지지 않아야 합니다.
  
- **계약 준수:**  
  상위 클래스가 제공하는 인터페이스(메서드, 속성 등)의 동작을 하위 클래스가 동일하게 보장해야 합니다.  
  예를 들어, 상위 클래스의 메서드가 특정한 입력에 대해 일정한 출력을 보장한다면, 하위 클래스에서도 동일하게 동작해야 합니다.

### 1.2. 왜 LSP가 중요한가?
- **예측 가능성:**  
  상위 타입으로 작성된 코드가 하위 타입으로 대체되어도 동일하게 동작하기 때문에, 코드의 동작을 예측하기 쉽습니다.
  
- **안정성:**  
  LSP를 준수하면, 상속 관계에 의한 부작용을 최소화하여 시스템의 안정성을 높일 수 있습니다.
  
- **유지보수성:**  
  상속 구조가 명확해지고, 하위 클래스의 변경이 상위 클래스의 계약을 위반하지 않는다면, 코드 변경 시 발생할 수 있는 문제를 줄일 수 있습니다.

---

## 2. 문제 상황과 해결 방안

### 2.1. 문제 상황: 잘못된 상속 관계로 인한 예측 불가능한 동작

전통적인 예로 **사각형(Rectangle)**과 **정사각형(Square)**의 관계가 있습니다.  
일반적으로 정사각형은 사각형의 일종으로 볼 수 있지만, 상속을 통해 구현할 경우 의도한 대로 동작하지 않을 수 있습니다.

#### LSP 위반 예시:
```python
# 사각형 클래스
class Rectangle:
    def __init__(self, width, height):
        self.width = width
        self.height = height

    def set_width(self, width):
        self.width = width

    def set_height(self, height):
        self.height = height

    def area(self):
        return self.width * self.height

# 정사각형 클래스 - Rectangle을 상속
class Square(Rectangle):
    def __init__(self, side):
        super().__init__(side, side)

    # 정사각형은 가로와 세로가 같아야 하므로, 둘을 동시에 변경
    def set_width(self, width):
        self.width = width
        self.height = width

    def set_height(self, height):
        self.width = height
        self.height = height

def process_rectangle(rect: Rectangle):
    rect.set_width(5)
    rect.set_height(10)
    return rect.area()

# Rectangle 인스턴스 사용
rect = Rectangle(2, 3)
print(process_rectangle(rect))  # 예상 출력: 50 (5 * 10)

# Square 인스턴스 사용
sq = Square(5)
print(process_rectangle(sq))  
# 예상 출력: 50, 하지만 실제 출력은 100 
# (Square에서는 set_width와 set_height가 연동되어 동작하기 때문)
```

**문제점:**  
`Square` 클래스가 `Rectangle`을 상속받아 구현되었지만,  
상위 클래스의 계약(가로와 세로를 개별적으로 설정하여 원하는 면적을 계산하는 것)을 위반하게 되어  
`process_rectangle` 함수 내에서 예상한 동작(면적 50)을 보장하지 못합니다.

---

### 2.2. 해결 방안: 상속 구조 재설계 또는 공통 인터페이스 도입

#### 방법 1: 공통 인터페이스(추상 클래스) 도입
정사각형과 사각형 모두 **Shape**라는 공통 인터페이스를 구현하도록 하여,  
각 클래스가 독자적으로 `area()` 메서드를 구현하게 할 수 있습니다.

```python
from abc import ABC, abstractmethod

# 공통 인터페이스
class Shape(ABC):
    @abstractmethod
    def area(self):
        pass

# 사각형 클래스
class Rectangle(Shape):
    def __init__(self, width, height):
        self.width = width
        self.height = height

    def area(self):
        return self.width * self.height

# 정사각형 클래스
class Square(Shape):
    def __init__(self, side):
        self.side = side

    def area(self):
        return self.side * self.side

# 사용 예시
rect = Rectangle(5, 10)
sq = Square(5)

print(rect.area())  # 50
print(sq.area())    # 25
```

**장점:**  
- 각 클래스가 자신에게 맞는 방식으로 면적을 계산하므로, 상속에 의한 부작용을 피할 수 있습니다.  
- 공통 인터페이스(Shape)를 사용하므로, 어떤 도형이든 동일한 방식으로 다룰 수 있습니다.

#### 방법 2: 상속 구조 재검토
만약 상속 관계를 반드시 유지해야 한다면,  
하위 클래스가 상위 클래스의 메서드 계약을 완전히 준수하도록 신중하게 설계해야 합니다.  
그러나 일반적으로 위의 공통 인터페이스 접근법이 더 명확하고 안전합니다.

---

## 3. 구체적 구현 방법 및 베스트 프랙티스

### 3.1. 구현 시 고려 사항
- **계약(Contract) 확인:**  
  상위 클래스나 인터페이스에서 정의한 메서드가 어떤 역할을 하는지 명확히 파악하고,  
  하위 클래스에서도 이를 동일하게 구현해야 합니다.
  
- **단위 테스트 작성:**  
  상위 클래스의 인스턴스를 하위 클래스로 대체했을 때 동일한 동작을 하는지 테스트 케이스를 통해 검증합니다.
  
- **상속보다는 조합(Composition) 고려:**  
  복잡한 상속 관계 대신, 조합을 사용하여 기능을 재사용하고, 변경에 유연한 구조를 만드는 것도 좋은 방법입니다.

### 3.2. 엣지 케이스 고려
- **예외 상황:**  
  하위 클래스에서 상위 클래스의 메서드를 오버라이드할 때, 예상치 못한 예외나 부수 효과가 발생하지 않도록 주의합니다.
  
- **상태 관리:**  
  객체의 내부 상태가 일관되게 유지되는지 확인하여, 상태 변경이 상위 클래스의 계약을 위반하지 않도록 합니다.

---

## 4. 추가 고려 사항

- **문서화:**  
  각 클래스와 메서드가 어떤 계약을 따르는지 명확하게 문서화하여, 개발자들이 올바른 사용법을 이해하도록 합니다.
  
- **코드 리뷰:**  
  상속 구조나 인터페이스 구현 시 팀원들과의 코드 리뷰를 통해 LSP 준수 여부를 확인합니다.
  
- **유지보수성:**  
  LSP를 준수하면, 코드 변경 시 기존 기능에 미치는 영향을 최소화할 수 있어 장기적인 유지보수가 용이해집니다.

---

## 5. 결론

리스코프 치환 원칙(LSP)은 **하위 클래스가 상위 클래스의 역할을 온전히 대체할 수 있어야 한다**는 중요한 설계 원칙입니다.  
- LSP를 준수하면, 상속 관계에서 발생할 수 있는 예측 불가능한 동작을 방지할 수 있습니다.  
- 올바른 상속 구조와 공통 인터페이스 도입을 통해, 코드의 재사용성과 안정성을 동시에 달성할 수 있습니다.

초보자도 이해할 수 있는 LSP의 개념과 사례를 통해, 보다 견고하고 예측 가능한 소프트웨어를 설계할 수 있습니다.