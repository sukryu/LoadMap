# Python 객체지향 프로그래밍: 다형성(Polymorphism) 🔄

## 다형성의 이해

다형성은 '여러 가지 형태를 가질 수 있는 능력'을 의미합니다. 프로그래밍에서 다형성은 동일한 인터페이스로 다양한 객체를 다룰 수 있게 해주는 핵심 개념입니다. 

### 다형성의 기본 원리

다형성을 이해하기 위해 실생활의 예시를 들어보겠습니다. 스마트폰의 충전 포트를 생각해보세요. USB-C 타입 포트 하나로 충전도 하고, 데이터 전송도 하며, 외부 디스플레이 연결도 가능합니다. 이처럼 하나의 인터페이스가 상황에 따라 다양한 기능을 수행할 수 있는 것이 다형성의 본질입니다.

### Python에서의 다형성 구현

다음은 동물 소리를 내는 프로그램을 통해 다형성을 구현한 예시입니다:

```python
class Animal:
    def make_sound(self):
        pass

class Dog(Animal):
    def make_sound(self):
        return "멍멍! 🐕"

class Cat(Animal):
    def make_sound(self):
        return "야옹! 🐱"

class Duck(Animal):
    def make_sound(self):
        return "꽥꽥! 🦆"

def animal_sound(animal):
    print(animal.make_sound())

# 다형성 활용
my_dog = Dog()
my_cat = Cat()
my_duck = Duck()

animals = [my_dog, my_cat, my_duck]
for animal in animals:
    animal_sound(animal)  # 각 동물의 고유한 소리 출력
```

## 다형성의 주요 형태

### 1. 메서드 오버라이딩 (Method Overriding)

부모 클래스의 메서드를 자식 클래스에서 재정의하는 것입니다.

```python
class Shape:
    def calculate_area(self):
        return 0

class Rectangle(Shape):
    def __init__(self, width, height):
        self.width = width
        self.height = height
    
    def calculate_area(self):  # 메서드 오버라이딩
        return self.width * self.height

class Circle(Shape):
    def __init__(self, radius):
        self.radius = radius
    
    def calculate_area(self):  # 메서드 오버라이딩
        return 3.14 * self.radius ** 2
```

### 2. 덕 타이핑 (Duck Typing)

Python의 특징적인 다형성 구현 방식으로, "오리처럼 걷고, 오리처럼 꽥꽥거리면, 그것은 오리다"라는 개념에서 유래했습니다.

```python
class Printer:
    def print_document(self, document):
        print(f"프린터로 출력: {document}")

class Screen:
    def print_document(self, document):
        print(f"화면에 표시: {document}")

class Phone:
    def print_document(self, document):
        print(f"모바일로 전송: {document}")

def show_document(output_device, document):
    output_device.print_document(document)

# 서로 다른 클래스이지만 동일한 인터페이스 사용
printer = Printer()
screen = Screen()
phone = Phone()

show_document(printer, "안녕하세요")  # 프린터로 출력
show_document(screen, "안녕하세요")   # 화면에 표시
show_document(phone, "안녕하세요")    # 모바일로 전송
```

## 실전 활용 예제

급여 시스템을 통해 다형성의 실제 활용을 살펴보겠습니다:

```python
class Employee:
    def __init__(self, name):
        self.name = name
    
    def calculate_salary(self):
        pass

class FullTimeEmployee(Employee):
    def __init__(self, name, monthly_salary):
        super().__init__(name)
        self.monthly_salary = monthly_salary
    
    def calculate_salary(self):
        return self.monthly_salary

class PartTimeEmployee(Employee):
    def __init__(self, name, hours_worked, hourly_rate):
        super().__init__(name)
        self.hours_worked = hours_worked
        self.hourly_rate = hourly_rate
    
    def calculate_salary(self):
        return self.hours_worked * self.hourly_rate

# 급여 계산 시스템
def process_payroll(employees):
    for employee in employees:
        salary = employee.calculate_salary()
        print(f"{employee.name}의 급여: {salary:,}원")

# 직원 목록
employees = [
    FullTimeEmployee("김철수", 3000000),
    PartTimeEmployee("이영희", 120, 15000),
    FullTimeEmployee("박지민", 3500000)
]

process_payroll(employees)
```

## 다형성의 장점

1. **코드 재사용성 향상**: 동일한 인터페이스로 다양한 객체를 처리할 수 있습니다.
2. **유지보수 용이성**: 새로운 클래스 추가가 기존 코드 수정 없이 가능합니다.
3. **확장성**: 시스템을 쉽게 확장할 수 있습니다.
4. **코드 유연성**: 객체의 실제 타입에 관계없이 일관된 방식으로 처리할 수 있습니다.

## 연습문제 🎯

다음 요구사항을 만족하는 도형 계산 프로그램을 작성해보세요:

1. `Shape` 기본 클래스 생성
2. `Rectangle`, `Circle`, `Triangle` 클래스 구현
3. 각 도형의 면적과 둘레를 계산하는 메서드 구현
4. 여러 도형을 리스트로 받아 전체 면적의 합을 계산하는 함수 구현