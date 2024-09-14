# Python 프로그래밍 언어 #

### Python이란? ###

Python은 1991년 귀도 반 로섬(Guido van Rossum)이 개발한 고급 프로그래밍 언어입니다. 다음과 같은 특징을 가지고 있습니다:

1. 인터프리터 언어: Python은 컴파일 과정 없이 코드를 한 줄씩 해석하고 실행하는 인터프리터 언어입니다.
2. 동적 타이핑: 변수의 타입을 명시적으로 선언할 필요 없이, 실행 시점에 자동으로 타입이 결정됩니다.
3. 객체 지향: Python은 모든 것이 객체로 취급되는 완전한 객체 지향 언어입니다.
4. 가독성 높은 문법: 들여쓰기를 사용하여 코드 블록을 구분하며, 간결하고 명확한 문법을 가지고 있습니다.
5. 풍부한 표준 라이브러리: 다양한 기능을 제공하는 방대한 표준 라이브러리를 포함하고 있습니다.
6. 크로스 플랫폼: Windows, macOS, Linux 등 다양한 운영 체제에서 실행 가능합니다.

### Python의 동작 방식 ###

Python 코드가 실행되는 과정은 다음과 같습니다:

1. 소스 코드 작성: .py 확장자를 가진 파일에 Python 코드를 작성합니다.
2. 바이트코드 컴파일: Python 인터프리터는 소스 코드를 바이트코드로 컴파일합니다. 이 바이트코드는 .pyc 파일로 저장될 수 있습니다.
3. Python Virtual Machine (PVM): 컴파일된 바이트코드는 PVM에서 실행됩니다. PVM은 바이트코드를 한 줄씩 해석하고 실행합니다.
4. 결과 출력: 프로그램의 실행 결과가 출력됩니다.


### Python의 주요 기능과 개념 ###

#### 변수와 데이터 타입 ####

- 변수:
    - Python에서 변수는 데이터를 저장하는 컨테이너 입니다. 변수 이름은 문자, 숫자, 밑줄(_)로 구성될 수 있지만, 숫자로 시작할 수 없습니다.
    - Python은 동적 타이핑을 지원하므로, 변수를 선언할 때 타입을 명시적으로 지정할 필요가 없습니다.

```python
x = 5
name = "Alice"
is_student = True
```

- 주요 데이터 타입:
    - 정수(int): 정수를 표현하는 데 사용됩니다. Python3에서는 크기 제한이 없습니다.
    ```python
    age = 25
    big_number = 1000000000000000000000
    ```

    - 실수(float): 소수점이 있는 숫자를 표현합니다. 내부적으로는 64비트 부동소수점 방식으로 저장됩니다.
    ```python
    pi = 3.14159
    e = 2.71828
    ```

    - 문자열(str): 텍스트를 표현하는 데 사용됩니다. 작은 따옴표('')나 큰 따옴표("")로 묶어 표현합니다.
    ```python
    name = "Bob"
    message = 'Hello, World!'
    multiline = '''This is a
    multiline string'''
    ```

    - 문자열 포맷팅:
    ```python
    name = "Alice"
    age = 30
    print(f"My name is {name} and I`m {age} years old.")
    ```

    - 불리언(bool): True 또는 False 값을 가집니다. 조건문이나 논리 연산에 사용됩니다.
    ```python
    is_raining = True
    has_license = False
    ```

    - None 타입: 값이 없음을 나타내는 특별한 타입입니다. 다른 언어의 null과 유사합니다.
    ```python
    result = None
    ```

    - 타입 변환: Python은 필요에 따라 데이터 타입을 변환할 수 있는 함수를 제공합니다.
    ```python
    # 문자열을 정수로
    x = int("5")

    # 정수를 실수로
    y = float(10)

    # 숫자를 문자열로
    z = str(3.14)

    # 다양한 타입을 불리언으로
    b1 = bool(1) # True
    b2 = bool("") # False
    ```

    - 타입 확인: type() 함수를 사용하여 변수의 타입을 확인할 수 있습니다.
    ```python
    x = 5
    print(type(x)) # <class 'int'>

    y = "Hello"
    print(type(y)) # <class 'str'>
    ```

    - 변수의 범위: Python에서 변수의 범위는 변수가 선언된 위치에 따라 결정됩니다.
        - 전역 변수: 함수 외부에서 선언된 변수로, 프로그램 전체에서 접근 가능합니다.
        - 지역 변수: 함수 내부에서 선언된 변수로, 해당 함수 내에서만 접근 가능합니다.
    ```python
    global_var = 10 # 전역 변수

    def my_function():
        local_var = 20 # 지역 변수
        print(global_var) # 전역 변수 접근 가능
        print(local_var) # 지역 변수 접근 가능

    my_function()
    print(global_var) # 전역 변수 접근 가능
    # print(local_var) # 오류 발생: 지역 변수는 함수 외부에서 접근 불가.
    ```

#### 제어 구조 ####

제어구조는 프로그램의 실행 흐름을 제어하는 데 사용됩니다. Python의 주요 제어 구조는 조건문과 반복문입니다.

- 조건문:
    - if문: 가장 기본적인 조건문으로, 특정 조건이 참일 때 코드 블록을 실행합니다.
    - 구문
    ```python
    if 조건:
        # 조건이 참일 때 실행할 코드
    ```
    - 예시
    ```python
    age = 10
    if age >= 18:
        print("성인입니다.")
    ```

    - if-else 문: 조건이 참일 때와 거짓일 때 각각 다른 코드 블록을 실행합니다.
    - 구문
    ```python
    if 조건:
        # 조건이 참일 때 실행할 코드
    else:
        # 조건이 거짓일 때 실행할 코드
    ```
    - 예시
    ```python
    temperature = 25
    if temperature > 30:
        print("더운 날씨입니다.")
    else:
        print("적당한 날씨입니다.")
    ```

    - if-elif-else 문: 여러 조건을 순차적으로 검사하고, 해당하는 조건의 코드 블록을 실행합니다.
    - 구문
    ```python
    if 조건1:
        # 조건1이 참일 때 실행할 코드
    elif 조건2:
        # 조건2가 참일 때 실행할 코드
    elif 조건3:
        # 조건3이 참일 때 실행할 코드
    else:
        # 모든 조건이 거짓일 때 실행할 코드
    ```
    - 예시
    ```python
    score = 85
    if score >= 90:
        print("A 등급")
    elif score >= 80:
        print("B 등급")
    elif score >= 70:
        print("C 등급")
    else:
        print("D 등급")
    ```

    - 중첩 조건문: 조건문 안에 또 다른 조건문을 넣을 수 있습니다.
    - 예시
    ```python
    age = 25
    has_license = True

    if age >= 18:
        if has_license:
            print("운전할 수 있습니다.")
        else:
            print("운전할 수 없습니다.")
    else:
        print("운전할 수 있는 나이가 아닙니다.")
    ```

    - 조건부 표현식(삼항 연산자): 간단한 if-else 문을 한 줄로 작성할 수 있습니다.
    - 구문
    ```python
    결과 = 참일_때의_값 if 조건 else 거짓일_때의_값
    ```
    - 예시
    ```python
    is_adult = "성인" if age >= 18 else "미성년자"
    ```

- 반복문:
    - for 문: 시퀀스(리스트, 튜플, 문자열 등)의 각 항목에 대해 코드 블록을 반복 실행합니다.
    - 구문
    ```python
    for 변수 in 시퀀스:
        # 반복할 코드
    ```
    - 예시
    ```python
    fruits = ["사과","바나나","체리"]
    for fruit in fruits:
        print(fruit)
    ```

    - range() 함수와 함께 사용:
    ```python
    for i in range(5): # 0부터 4까지
        print(i)
    ```

    - while 문: 조건이 참인 동안 코드 블록을 반복 실행합니다.
    - 구문:
    ```python
    while 조건:
        # 반복할 코드
    ```
    - 예시:
    ```python
    count = 0
    while count < 5:
        print(count)
        count+=1
    ```

    - break 문: 반복문을 즉시 종료하고 빠져나갑니다.
    - 예시
    ```python
    for i in range(10):
        if i == 5:
            break
        print(i) # 0부터 4까지만 출력됨.
    ```

    - continue 문: 현재 반복을 건너뛰고 다음 반복으로 진행합니다.
    - 예시:
    ```python
    for i in range(5):
        if i == 2:
            continue
        print(i) # 0, 1, 3, 4가 출력됨 (2는 건너뜀)
    ```

    - else 절과 함께 사용: 반복문이 정상적으로 완료되었을 때 실행될 코드를 지정할 수 있습니다.
    - 예시
    ```python
    for i in range(5):
        print(i)
    else:
        print("반복문이 정상적으로 완료되었습니다.")
    
    # break로 종료된 경우
    for i in range(5):
        if i == 3:
            break
        print(i)
    else:
        print("이 문장은 출력되지 않습니다.")
    ```

    - 중첩 반복문: 반복문 안에 다른 반복문을 넣을 수 있습니다.
    - 예시:
    ```python
    for i in range(3):
        for j in range(3):
            print(f"({i}, {j})")
    ```

    - 리스트 컴프리헨션: 간결하게 리스트를 생성하는 방법입니다.
    - 예시:
    ```python
    squares = [x**2 for x in range(10)]
    even_numbers = [x for x in range(20) if x % 2 == 0]
    ```

#### 함수 ####

함수는 특정 작업을 수행하는 코드 블록으로, 재사용성과 모듈화를 향상시키는 핵심 요소입니다.

- 함수 정의와 호출
    - 함수 정의: ```def``` 키워드를 사용하여 함수를 정의합니다.
    - 구문:
    ```python
    def 함수이름(매개변수1, 매개변수2, ...):
        # 함수 본문
        return 결과 # 선택적
    ```
    - 예시:
    ```python
    def greet(name):
        return f"안녕하세요, {name}님!"
    ```

    - 함수 호출: 함수 이름과 괄호를 사용하여 함수를 호출합니다.
    - 예시:
    ```python
    message = greet("Alice")
    print(message) # 출력 : 안녕하세요, Alice님!
    ```

- 매개변수와 인자
    - 위치 인자: 함수 호출 시 순서대로 전달되는 인자입니다.
    - 예시:
    ```python
    def add(a, b):
        return a + b

    result = add(3, 5) # 3은 a에 5는 b에 할당됨.
    ```

    - 키워드 인자: 매개변수 이름을 명시하여 전달하는 인자입니다.
    - 예시
    ```python
    def greet(name, greeting="안녕하세요"):
        return f"{greeting}, {name}님!"
    
    print(greet(name="Bob", greeting="반갑습니다.")) # 출력: 반갑습니다. Bob님!
    print(greet(name="Charlie")) # 출력: 안녕하세요, Charlie님!
    ```

    - 기본값 매개변수: 함수 정의 시 매개변수에 기본값을 지정할 수 있습니다.
    - 예시:
    ```python
    def power(base, exponent = 2):
        return base ** exponent
    
    print(power(3)) # 출력: 9 (3^2)
    print(power(3, 3)) # 출력: 27 (3^3)
    ```

    - 가변 인자(*args): 임의 개수의 위치 인자를 튜플로 받습니다.
    - 예시:
    ```python
    def sum_all(*numbers):
        return sum(numbers)

    print(sum_all(1, 2, 3, 4, 5)) # 출력: 15
    ```

    - 키워드 가변 인자 (**kwargs): 임의 개수의 키워드 인자를 딕셔너리로 받습니다.
    - 예시:
    ```python
    def print_info(**kwargs):
        for key, value in kwargs.items():
            print(f"{key} : {value}")
    
    print_info(name="Alice", age = 30, city="Seoul")
    ```

- 반환값:
    - 단일 값 반환:
    ```python
    def square(n):
        return n ** 2
    ```

    - 다중 값 반환:
    ```python
    def min_max(numbers):
        return min(numbers), max(numbers)

    minimum, maximum = min_max([1, 2, 3, 4, 5])
    ```

    - 반환값이 없는 함수: 명시적인 return 문이 없으면 None을 반환합니다.
    ```python
    def greet(name):
        print(f"Hello, {name}!")

    result = greet("Dave") # result는 None
    ```

- 람다 함수:
    - 람다 함수는 이름 없는 일회용 함수로, 간단한 함수를 한 줄로 정의할 수 있습니다.

    - 구문:
    ```python
    lambda 매개변수: 표현식
    ```

    - 예시:
    ```python
    square = lambda x: x ** 2
    print(square(5)) # 출력 25

    # 정렬에 사용
    pairs = [(1, 'one'), (2, 'two'), (3, 'three'), (4, 'four')]
    pairs.sort(key=lambda pair: pair[1])
    print(pairs) # 출력: [(4, 'four'), (1, 'one'), (3, 'three'), (2, 'two')] 
    ```

- 함수의 스코프와 네임스페이스
    - 전역 변수와 지역 변수:
    ```python
    x = 10  # 전역 변수

    def func():
        y = 20  # 지역 변수
        print(x)  # 전역 변수 접근 가능
        print(y)  # 지역 변수 접근 가능

    func()
    print(x)  # 전역 변수 접근 가능
    # print(y)  # 오류: 지역 변수는 함수 외부에서 접근 불가
    ```

    - global 키워드: 함수 내에서 전역 변수를 수정할 때 사용합니다.
    ```python
    x = 10

    def modify_global():
        global x
        x = 20

    modify_global()
    print(x)  # 출력: 20
    ```

- 재귀 함수:
    - 함수가 자기 자신을 호출하는 기법입니다.
    - 예시(팩토리얼 계산):
    ```python
    def factorial(n):
        if n == 0 or n == 1:
            return 1
        else:
            return n * factorial(n - 1)

    print(factorial(5))  # 출력: 120
    ```

- 함수 데코레이터
    - 기존 함수의 동작을 수정하거나 확장하는 데 사용됩니다.
    - 예시:
    ```python
    def uppercase_decorator(func):
    def wrapper():
        result = func()
        return result.upper()
    return wrapper

    @uppercase_decorator
    def greet():
        return "hello, world"

    print(greet())  # 출력: HELLO, WORLD
    ```