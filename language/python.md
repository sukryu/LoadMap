# Python 프로그래밍 언어 #

## Python이란? ##

Python은 1991년 귀도 반 로섬(Guido van Rossum)이 개발한 고급 프로그래밍 언어입니다. 다음과 같은 특징을 가지고 있습니다:

1. 인터프리터 언어: Python은 컴파일 과정 없이 코드를 한 줄씩 해석하고 실행하는 인터프리터 언어입니다.
2. 동적 타이핑: 변수의 타입을 명시적으로 선언할 필요 없이, 실행 시점에 자동으로 타입이 결정됩니다.
3. 객체 지향: Python은 모든 것이 객체로 취급되는 완전한 객체 지향 언어입니다.
4. 가독성 높은 문법: 들여쓰기를 사용하여 코드 블록을 구분하며, 간결하고 명확한 문법을 가지고 있습니다.
5. 풍부한 표준 라이브러리: 다양한 기능을 제공하는 방대한 표준 라이브러리를 포함하고 있습니다.
6. 크로스 플랫폼: Windows, macOS, Linux 등 다양한 운영 체제에서 실행 가능합니다.

## Python의 동작 방식 ##

Python 코드가 실행되는 과정은 다음과 같습니다:

1. 소스 코드 작성: .py 확장자를 가진 파일에 Python 코드를 작성합니다.
2. 바이트코드 컴파일: Python 인터프리터는 소스 코드를 바이트코드로 컴파일합니다. 이 바이트코드는 .pyc 파일로 저장될 수 있습니다.
3. Python Virtual Machine (PVM): 컴파일된 바이트코드는 PVM에서 실행됩니다. PVM은 바이트코드를 한 줄씩 해석하고 실행합니다.
4. 결과 출력: 프로그램의 실행 결과가 출력됩니다.


## Python의 주요 기능과 개념 ##

### 변수와 데이터 타입 ###

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

### 제어 구조 ###

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

### 함수 ###

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

### 데이터 구조 ###

- 데이터 구조: Python은 다양한 내장 데이터 구조를 제공하며, 이들은 데이터를 효율적으로 저장하고 조작하는 데 사용됩니다.
            주요 데이터 구조는 다음과 같습니다.

    - 리스트 (List):
        - 리스트는 순서가 있고 변경 가능한 (mutable)데이터 구조입니다.
        1. 생성:
        ```python
        empty_list = []
        numbers = [1, 2, 3, 4, 5]
        mixed = [1, "two", 3.0, [4, 5]]
        ```

        2. 접근과 슬라이싱:
        ```python
        print(numbers[0])     # 첫 번째 요소: 1
        print(numbers[-1])    # 마지막 요소: 5
        print(numbers[1:4])   # 슬라이싱: [2, 3, 4]
        print(numbers[::-1])  # 역순: [5, 4, 3, 2, 1]
        ```

        3. 수정:
        ```python
        numbers[0] = 10       # 요소 변경
        numbers.append(6)     # 끝에 추가
        numbers.insert(1, 15) # 특정 위치에 삽입
        numbers.extend([7, 8])# 리스트 확장
        popped = numbers.pop()# 마지막 요소 제거 및 반환
        numbers.remove(3)     # 특정 값 제거
        ```

        4. 기타 연산:
        ```python
        length = len(numbers) # 길이
        sorted_nums = sorted(numbers)  # 정렬된 새 리스트 반환
        numbers.sort()        # 원본 리스트 정렬
        numbers.reverse()     # 역순으로 변경
        ```

        5. 리스트 컴프리헨션:
        ```python
        squares = [x**2 for x in range(10)]
        evens = [x for x in range(20) if x % 2 == 0]
        ```

    - 튜플(Tuple)
        - 튜플은 순서가 있고 변경 불가능한 (immutable)데이터 구조입니다.

        1. 생성:
        ```python
        empty_tuple = ()
        single_element = (1, ) # 콤마 필수
        coordinates = (3, 4)
        mixed = (1, "two", 3.0)
        ```

        2. 접근:
        ```python
        print(coordinates[0])  # 3
        print(coordinates[-1]) # 4
        ```

        3. 언패킹:
        ```python
        x, y = coordinates
        ```

        4. 용도:
            - 변경되지 않아야 하는 데이터를 저장할 때
            - 딕셔너리의 키로 사용 가능
            - 함수에서 여러 값을 반환할 때
        
    
    - 집합 (Set)
        - 집합은 순서가 없고 중복을 허용하지 않는 데이터 구조입니다.

        1. 생성:
        ```python
        empty_set = set()
        numbers = {1, 2, 3, 4, 5}
        mixed = {1, "two", 3.0}
        ```
        
        2. 연산:
        ```python
        numbers.add(6)        # 요소 추가
        numbers.remove(3)     # 요소 제거 (없으면 에러)
        numbers.discard(10)   # 요소 제거 (없어도 에러 없음)
        popped = numbers.pop()# 임의의 요소 제거 및 반환

        # 집합 연산
        set1 = {1, 2, 3}
        set2 = {3, 4, 5}
        print(set1 | set2)    # 합집합: {1, 2, 3, 4, 5}
        print(set1 & set2)    # 교집합: {3}
        print(set1 - set2)    # 차집합: {1, 2}
        print(set1 ^ set2)    # 대칭차: {1, 2, 4, 5}
        ```

        3. 용도:
            - 중복 제거
            - 멤버십 테스트(in 연산자 사용)
            - 수학적 집합 연산

    - 딕셔너리(Dictionary)
        - 딕셔너리는 키-값 쌍을 저장하는 데이터 구조입니다.

        1. 생성:
        ```python
        empty_dict = {}
        person = {"name": "Alice", "age": 30, "city": "New York"}
        ```

        2. 접근과 수정
        ```python
        print(person["name"])  # Alice
        person["age"] = 31     # 값 수정
        person["job"] = "Engineer"  # 새 키-값 쌍 추가
        ```

        3. 메서드
        ```python
        keys = person.keys()       # 키 목록
        values = person.values()   # 값 목록
        items = person.items()     # (키, 값) 튜플 목록

        age = person.get("age", 0) # 키가 없을 때 기본값 반환
        person.update({"height": 170, "weight": 60})  # 여러 항목 추가/수정
        ```

        4. 딕셔너리 컴프리헨션
        ```python
        squares = {x: x**2 for x in range(5)}
        ```

    - 문자열(String)
        - 문자열은 변경 불가능한 문자의 시퀀스입니다.

        1. 생성:
        ```python
        single_quotes = 'Hello'
        double_quotes = "World"
        triple_quotes = '''Multi-line
        string'''
        ```

        2. 연산과 메서드
        ```python
        s = "Hello, World!"
        print(len(s))           # 길이: 13
        print(s.upper())        # 대문자로: HELLO, WORLD!
        print(s.lower())        # 소문자로: hello, world!
        print(s.split(", "))    # 분할: ['Hello', 'World!']
        print(", ".join(["A", "B", "C"]))  # 결합: A, B, C
        print(s.strip())        # 양쪽 공백 제거
        print(s.replace("World", "Python"))  # 치환: Hello, Python!
        ```

        3. 포매팅
        ```python
        name = "Alice"
        age = 30
        # f-string (Python 3.6+)
        print(f"{name} is {age} years old")
        # format() 메서드
        print("{} is {} years old".format(name, age))
        # % 연산자
        print("%s is %d years old" % (name, age))
        ```

    - 기타 데이터 구조
        1. collections 모듈: collections 모듈은 파이썬의 내장 컨테이너(dict, list, set, tuple)에 대한 대안을 제공합니다.
            1. namedtuple: 일반 튜플의 서브클래스로, 필드에 이름을 부여할 수 있습니다.
            ```python
            from collections import namedtuple

            Point = namedtuple('Point', ['x', 'y'])
            p = Point(11, y = 22)

            print(p.x)  # 11
            print(p.y)  # 22
            print(p)    # Point(x=11, y=22)
            ```
            - 특징:
                - 불변(immutable)이므로 튜플의 장점 유지
                - 필드에 이름으로 접근 가능하여 가독성 향상
                - 딕셔너리보다 메모리 효율적

            2. defaultdict: 키가 없을 때 기본값을 제공하는 딕셔너리 서브클래스입니다.
            ```python
            from collections import defaultdict

            dd = defaultdict(list)
            dd['key'].append(1)
            dd['key'].append(2)
            print(dd)  # defaultdict(<class 'list'>, {'key': [1, 2]})

            # 일반 딕셔너리와 비교
            d = {}
            # d['key'].append(1)  # KeyError 발생
            ```

            - 특징: 
                - 존재하지 않는 키에 접근할 때 KeyError 대신 기본값 반환
                - 기본값 팩토리 함수를 지정할 수 있음(list, int, set 등)

            3. Counter: 요소의 개수를 세는 딕셔너리 서브클래스입니다.
            ```python
            from collections import Counter

            c = Counter('gallahad')
            print(c)  # Counter({'a': 3, 'l': 2, 'g': 1, 'h': 1, 'd': 1})

            # 가장 흔한 요소
            print(c.most_common(2))  # [('a', 3), ('l', 2)]

            # 산술 연산
            c1 = Counter(a=3, b=1)
            c2 = Counter(a=1, b=2)
            print(c1 + c2)  # Counter({'a': 4, 'b': 3})
            print(c1 - c2)  # Counter({'a': 2})
            ```

            - 특징:
                - 데이터의 빈도를 쉽게 계산
                - 산술 연산을 통한 카운터 조합 가능

            4. deque(double-ended queue): 양쪽 끝에서 빠르게 추가와 삭제를 할 수 있는 리스트형 컨테이너입니다.
            ```python
            from collections import deque

            d = deque('abc')
            d.append('d')        # 오른쪽에 추가
            d.appendleft('z')    # 왼쪽에 추가
            print(d)  # deque(['z', 'a', 'b', 'c', 'd'])

            d.pop()              # 오른쪽에서 제거
            d.popleft()          # 왼쪽에서 제거
            print(d)  # deque(['a', 'b', 'c'])

            d.rotate(1)          # 오른쪽으로 회전
            print(d)  # deque(['c', 'a', 'b'])
            ```

            - 특징:
                - 양쪽 끝에서의 추가/제거가 O(1) 시간복잡도
                - 리스트보다 빠른 앞쪽 삽입/삭제
                - 최대 길이 지정 가능(maxlen 매개변수)
        
        2. heapq 모듈: 이진 합 알고리즘을 사용하여 리스트를 최소 힙으로 유지합니다.
        ```python
        import heapq

        h = []
        heapq.heappush(h, (5, 'write code'))
        heapq.heappush(h, (7, 'release product'))
        heapq.heappush(h, (1, 'write spec'))
        heapq.heappush(h, (3, 'create tests'))

        print(heapq.heappop(h))  # (1, 'write spec')
        print(heapq.heappop(h))  # (3, 'create tests')
        ```

        - 특징:
            - 항상 가장 작은 요소가 힙의 루트에 위치
            - 우선순위 큐 구현에 적합
            - 정렬된 리스트보다 삽입과 삭제가 효율적 (O(log n))
        
        3. array 모듈: 기본 데이터 타입의 컴팩트한 배열을 제공합니다.
        ```python
        from array import array

        # 부호 없는 16비트 정수의 배열
        arr = array('H', [4000, 10, 700, 22222])
        print(arr[1])  # 10

        # 파일에 쓰기
        with open('data.bin', 'wb') as f:
            arr.tofile(f)

        # 파일에서 읽기
        arr2 = array('H')
        with open('data.bin', 'rb') as f:
            arr2.fromfile(f, 4)  # 4개 요소 읽기

        print(arr2)  # array('H', [4000, 10, 700, 22222])
        ```

        - 특징:
            - 메모리 효율적(모든 요소가 같은 타입)
            - C 배열과 호환되어 외부 라이브러리와 인터페이스에 유용
            - 대량의 숫자 데이터 처리에 적합
        
        4. bisect 모듈: 정렬된 시퀀스에서 이진 검색과 삽입을 수행하는 함수를 제공합니다.
        ```python
        import bisect

        numbers = [1, 4, 5, 6, 8, 12, 15, 20]
        print(bisect.bisect(numbers, 13))  # 7 (13이 들어갈 위치)

        bisect.insort(numbers, 13)
        print(numbers)  # [1, 4, 5, 6, 8, 12, 13, 15, 20]
        ```

        - 특징:
            - 정렬된 리스트에서 효율적인 검색과 삽입 (O(log n))
            - 정렬 상태를 유지하면서 새 항목 삽입 가능

        5. queue 모듈: 여러 가지 큐 구현을 제공합니다.
        ```python
        from queue import Queue, LifoQueue, PriorityQueue

        # 선입선출(FIFO) 큐
        q = Queue()
        q.put(1)
        q.put(2)
        print(q.get())  # 1

        # 후입선출(LIFO) 큐 (스택)
        lifo = LifoQueue()
        lifo.put(1)
        lifo.put(2)
        print(lifo.get())  # 2

        # 우선순위 큐
        pq = PriorityQueue()
        pq.put((2, 'code'))
        pq.put((1, 'eat'))
        pq.put((3, 'sleep'))
        print(pq.get())  # (1, 'eat')
        ```

        - 특징:
            - 스레드 안전(멀티스레딩에 적합)
            - 다양한 큐 타입 제공(FIFO, LIFO, 우선순위 큐)

### 객체 지향 프로그래밍 ###

객체 지향 프로그래밍은 코드를 객체라는 단위로 구조화하는 프로그래밍 패러다임입니다.
Python은 완전한 객체 지향 언어로, OOP의 주요 개념들을 모두 지원합니다.

- 클래스와 객체

    1. 클래스 정의:
    ```python
    class Dog:
        def __init__(self, name, age):
            self.name = name
            self.age = age
        def bark(self):
            print(f"{self.name} says: Woof!")
    ```

    2. 객체 생성 및 사용
    ```python
    my_dog = Dog("Buddy", 3)
    print(my_dog.name)  # Buddy
    my_dog.bark()  # Buddy says: Woof!
    ```

- 상속: 상속을 통해 기존 클래스의 속성과 메서드를 새로운 클래스에서 재사용할 수 있습니다.
    ```python
    class Animal:
        def __init__(self, name):
            self.name = name

        def speak(self):
            pass

    class Cat(Animal):
        def speak(self):
            return f"{self.name} says Meow!"

    class Dog(Animal):
        def speak(self):
            return f"{self.name} says Woof!"

    cat = Cat("Whiskers")
    dog = Dog("Rex")
    print(cat.speak())  # Whiskers says Meow!
    print(dog.speak())  # Rex says Woof!
    ```

- 다형성: 다형성을 통해 같은 인터페이스를 사용하여 서로 다른 객체 타입을 다룰 수 있습니다.
    ```python
    def animal_sound(animal):
    print(animal.speak())

    cat = Cat("Mittens")
    dog = Dog("Fido")

    animal_sound(cat)  # Mittens says Meow!
    animal_sound(dog)  # Fido says Woof!
    ```

- 캡슐화: 캡슐화는 객체의 내부 상태를 외부로부터 숨기고, 특정 인터페이스를 통해서만 접근할 수 있게 하는 메커니즘입니다.
```python
class BankAccount:
    def __init__(self, balance):
        self._balance = balance  # 관례적으로 '_'로 시작하는 속성은 비공개로 간주

    def deposit(self, amount):
        if amount > 0:
            self._balance += amount
        else:
            print("Invalid amount")

    def withdraw(self, amount):
        if 0 < amount <= self._balance:
            self._balance -= amount
        else:
            print("Insufficient funds")

    def get_balance(self):
        return self._balance

account = BankAccount(1000)
account.deposit(500)
account.withdraw(200)
print(account.get_balance())  # 1300
```

- 특수 메서드(매직 매서드): Python은 특별한 이름을 가진 메서드를 통해 객체의 동작을 커스터마이즈할 수 있습니다.
```python
class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __str__(self):
        return f"Point({self.x}, {self.y})"

    def __add__(self, other):
        return Point(self.x + other.x, self.y + other.y)

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

p1 = Point(1, 2)
p2 = Point(3, 4)
print(p1)  # Point(1, 2)
print(p1 + p2)  # Point(4, 6)
print(p1 == Point(1, 2))  # True
```

- 클래스 메서드와 정적 메서드
    1. 클래스 메서드: 클래스 전체에 대해 동작하는 메서드
    2. 정적 메서드: 클래스나 인스턴스 상태에 접근하지 않는 메서드

    ```python
    class MathOperations:
    PI = 3.14

    def __init__(self, value):
        self.value = value

    @classmethod
    def get_pi(cls):
        return cls.PI

    @staticmethod
    def add(a, b):
        return a + b

    def multiply_by_pi(self):
        return self.value * self.PI

    print(MathOperations.get_pi())  # 3.14
    print(MathOperations.add(5, 3))  # 8

    math_obj = MathOperations(5)
    print(math_obj.multiply_by_pi())  # 15.7
    ```

- 추상 클래스: 추상 클래스는 하나 이상의 추상 메서드를 포함하는 클래스로, 직접 인스턴스화할 수 없습니다.
```python
from abc import ABC, abstractmethod

class Shape(ABC):
    @abstractmethod
    def area(self):
        pass

class Circle(Shape):
    def __init__(self, radius):
        self.radius = radius

    def area(self):
        return 3.14 * self.radius ** 2

# shape = Shape()  # TypeError: Can't instantiate abstract class Shape
circle = Circle(5)
print(circle.area())  # 78.5
```

### 모듈과 패키지 ###

모듈과 패키지는 Python 코드를 구조화하고 재사용 가능하게 만드는 중요한 메커니즘입니다.

- 모듈: 모듈은 Python 정의와 문장들을 담고 있는 파일입니다. 파일명이 모듈명이 됩니다.
    1. 모듈 생성: 예를 들어, my_module.py 라는 파일을 만들고 다음과 같이 작성합니다.
    ```python
    # my_module.py

    def greet(name):
        return f"Hello, {anme}!"
    
    PI = 3.14159
    ```

    2. 모듈 사용:
    ```python
    import my_module

    print(my_module.greet("Alice")) # Hello, Alice!
    print(my_module.PI) # 3.14159
    ```

    3. 특정 항목만 임포트
    ```python
    from my_module import greet, PI

    print(greet("Bob"))  # Hello, Bob!
    print(PI)  # 3.14159
    ```

    4. 별칭 사용:
    ```python
    import my_module as mm

    print(mm.greet("Charlie"))  # Hello, Charlie!
    ```

- 패키지: 패키지는 모듈을 담는 디렉토리입니다. 패키지는 모듈을 계층적으로 구조화하는 방법을 제공합니다.
    1. 패키지 구조:
    ```md
    my_package/
    __init__.py
    module1.py
    module2.py
    subpackage/
        __init__.py
        module3.py
    ```

    2. __init__.py: 이 파일은 디렉토리를 Python 패키지로 만듭니다. 비어있을 수 있으며, 패키지 초기화 코드를 포함할 수 있습니다.

    3. 패키지 사용:
    ```python
    import my_package.module1
    from my_package import module2
    from my_package.subpackage import module3
    ```

- 모듈 검색 경로
    - Python은 모듈을 임포트할 때 다음 순서대로 검색합니다.
        1. 현재 디렉토리
        2. PYTHONPATH 환경 변수에 나열된 디렉토리
        3. Python 기본 라이브러리 디렉토리

    - sys.path 리스트를 통해 현재 검색 경로를 확인하고 수정할 수 있습니다.

- 표준 라이브러리 모듈
    - Python은 풍부한 표준 라이브러리를 제공합니다. 몇가지 유용한 모듈은 다음과 같습니다.

    1. os: 운영 체제와 상호 작용
    2. sys: Python 인터프리터와 상호 작용
    3. datetime: 날짜와 시간 처리
    4. math: 수학 함수
    5. random: 난수 생성
    6. json: JSON 데이터 처리
    7. re: 정규 표현식
    8. collections: 특수 컨테이너 데이터형

- 서드파티 패키지
    - Python Package Index (PyPI)를 통해 수많은 서드파티 패키지를 사용할 수 있습니다.

    1. pip 사용:
    ```bash
    pip install package_name
    ```

    2. 가상 환경: venv 모듈을 사용하여 프로젝트별로 격리된 Python 환경을 만들 수 있습니다.
    ```bash
    python -m venv myenv
    source myenv/bin/activate # Linux/macOS
    myenv\Scripts\activate.bat # Windows
    ```

- 모듈과 패키지 작성 시 주의사항
    1. 순환 임포트 피하기: 모듈 간에 상호 임포트 하지 않도록 주의
    2. 상대 임포트 사용: 패키지 내에서는 상대 경로로 임포트 가능
    ```python
    from .module import function
    from ..subpackage import module
    ```
    3. if __name__ == "__main__": 사용: 모듈이 직접 실행될 때만 실행될 코드 지정

- 네임스페이스 패키지
    - Python 3.3 부터는 __init__.py 없이도 패키지를 만들 수 있습니다. 이를 네임스페이스 패키지라고 합니다.

- __all__ 변수
    - 모듈에서 __all__ 리스트를 정의하여 ``` from module import * ``` 사용 시 임포트될 이름들을 지정할 수 있습니다.
    ```python
    __all__ = ['function1', 'function2', 'CLASS1']
    ```

### 파일 처리 ###

Python에서 파일 처리는 데이터를 저장하고 불러오는 중요한 기능입니다. 텍스트 파일과 바이너리 파일 모두 다룰 수 있습니다.

- 기본적인 파일 열기와 닫기
    1. 파일 열기:
    ```python
    file = open("example.txt", 'r') # 읽기 모드로 열기

    # 파일 작업 수행

    file.close() # 파일 닫기
    ```

    2. with문 사용 (권장):
    ```python
    with open('example.txt', 'r') as file:
        # 파일 작업 수행
    # 블록을 벗어나면 자동으로 파일이 닫힘.
    ```

- 파일 모드
    1. ```'r'```: 읽기 모드 (기본값)
    2. ```'w'```: 쓰기 모드(파일이 존재하면 내용을 덮어씀)
    3. ```'a'```: 추가 모드(파일 끝에 내용을 추가)
    4. ```'x'```: 배타적 생성 모드 (파일이 이미 존재하면 실패)
    5. ```'b'```: 이진 모드 (텍스트 모드 대신 사용)
    6. ```'+'```: 일기와 쓰기를 동시에 할 수 있는 모드

- 텍스트 파일 읽기:
    1. 전체 내용 읽기:
    ```python
    with open('example.txt', 'r') as file:
        content = file.read()
        print(content)
    ```

    2. 한 줄씩 읽기:
    ```python
    with open('example.txt', 'r') as file:
        for line in file:
            print(line.strip()) # strip()으로 줄바꿈 문자 제거
    ```

    3. 모든 줄을 리스트로 읽기:
    ```python
    with open('example.txt', 'r') as file:
        lines = file.readlines()
        print(lines)
    ```

- 텍스트 파일 쓰기:
    1. 문자열 쓰기:
    ```python
    with open('output.txt', 'w') as file:
        file.write("Hello, World!\n")
        file.write("This is a new line.")
    ```

    2. 여러 줄 쓰기:
    ```python
    lines = ["Line 1", "Line 2", "Line 3"]
    with open('output.txt', 'w') as file:
        file.writelines(line + '\n' for line in lines)
    ```

- 파일 위치 제어:
    1. 현재 위치 확인:
    ```python
    lines = ["Line 1", "Line 2", "Line 3"]
    with open('output.txt', 'w') as file:
        file.writelines(line + '\n' for line in lines)
    ```

    2. 위치 변경:
    ```python
    with open('example.txt', 'r') as file:
        file.seek(10)  # 10번째 바이트로 이동
    ```

- 바이너리 파일 처리:
    1. 바이너리 파일 읽기:
    ```python
    with open('image.jpg', 'rb') as file:
        data = file.read()
    ```

    2. 바이너리 파일 쓰기:
    ```python
    with open('copy.jpg', 'wb') as file:
        file.write(data)
    ```

- CSV 파일 처리: CSV(Comma-Separated Values) 파일은 흔히 사용되는 데이터 형식입니다.
```python
import csv

# CSV 파일 읽기
with open('data.csv', 'r') as file:
    csv_reader = csv.reader(file)
    for row in csv_reader:
        print(row)

# CSV 파일 쓰기
data = [['Name', 'Age'], ['Alice', '30'], ['Bob', '25']]
with open('output.csv', 'w', newline='') as file:
    csv_writer = csv.writer(file)
    csv_writer.writerows(data)
```

- JSON 파일 처리: JSON은 데이터 교환 형식으로 널리 사용됩니다.
```python
import json

# JSON 파일 읽기
with open('data.json', 'r') as file:
    data = json.load(file)

# JSON 파일 쓰기
data = {'name': 'Alice', 'age': 30}
with open('output.json', 'w') as file:
    json.dump(data, file, indent=4)
```

- 파일 및 디렉토리 관리
    - os 모듈을 사용하여 파일 시스템을 조작할 수 있습니다.
    ```python
    import os

    # 현재 작업 디렉토리
    print(os.getcwd())

    # 디렉토리 생성
    os.mkdir('new_directory')

    # 파일 존재 여부 확인
    print(os.path.exists('file.txt'))

    # 파일 삭제
    os.remove('file.txt')

    # 디렉토리 내용 나열
    print(os.listdir('.'))
    ```

- 파일 처리 시 주의사항
    1. 항상 파일을 닫아주거나 ```with```문을 사용하세요.
    2. 대용량 파일을 다룰 때는 메모리 사용에 주의하세요. 한 번에 전체를 읽지 말고 청크 단위로 처리하세요.
    3. 예외 처리를 통해 파일 작업 중 발생할 수 있는 오류에 대비하세요.
    4. 텍스트 파일을 다룰 때 인코딩에 주의하세요 (예: ```open('file.txt', 'r', encoding='utf-8')```).


### 예외 처리 ###

예외 처리는 프로그램 실행 중 발생할 수 있는 오류를 관리하는 메커니즘입니다. 이를 통해 프로그램이 예기치 않은 
상황에서도 정상적으로 동작할 수 있도록 합니다.

1. 기본적인 예외 처리 구조
```python
try:
    # 예외가 발생할 수 있는 코드
    result = 10/0
except ZeroDivisionError:
    # 특정 예외 처리
    print("0으로 나눌 수 없습니다.")
except Exception as e:
    print(f"예외 발생: {e}")
else:
    # 예외가 발생하지 않았을 때 실행
    print("계산이 성공적으로 수행되었습니다.")
finally:
    # 예외 발생 여부와 관계없이 항상 실행
    print("예외 처리 구문이 끝났습니다.")
```

2. 다중 예외 처리
```python
try:
    x = int(input("숫자를 입력하세요: "))
    result = 10 / x
except ValueError:
    print("유효한 숫자를 입력하세요.")
except ZeroDivisionError:
    print("0으로 나눌 수 없습니다.")
```

3. 예외 발생시키기
    - ```raise``` 키워드를 사용하여 의도적으로 예외를 발생시킬 수 있습니다.
    ```python
    def validate_age(age):
        if age < 0:
            raise ValueError("나이는 음수일 수 없습니다.")
        if age > 120:
            raise ValueError("나이가 너무 많습니다.")
        return age

    try:
        validate_age(-5)
    except ValueError as e:
        print(e)
    ```

4. 사용자 정의 예외:
    - 필요에 따라 자신만의 예외 클래스를 정의할 수 있습니다.
    ```python
    class CustomError(Exception):
        def __init__(self, message):
            self.message = message
            super().__init__(self.message)

    try:
        raise CustomError("이것은 사용자 정의 예외입니다.")
    except CustomError as e:
        print(e)
    ```

5. 예외 체이닝:
    - 한 예외가 다른 예외를 직접적으로 발생시킬 때 사용합니다.
    ```python
    try:
        try:
            raise ValueError("원본 예외")
        except ValueError as e:
            raise RuntimeError("새로운 예외") from e
    except RuntimeError as e:
        print(f"예외 발생: {e}")
        print(f"원인: {e.__cause__}")
    ```

6. 컨텍스트 관리자와 예외 처리
    - ```with```문을 사용하여 리소스의 획득과 해제를 자동으로 관리할 수 있습니다.
    ```python
    class FileManager:
        def __init__(self, filename):
            self.filename = filename
        
        def __enter__(self):
            self.file = open(self.filename, 'w')
            return self.file
        
        def __exit__(self, exc_type, exc_value, traceback):
            if self.file:
                self.file.close()
            if exc_type is not None:
                print(f"예외 발생: {exc_type}, {exc_value}")
            return True  # 예외를 처리했음을 나타냄

    with FileManager('test.txt') as f:
        f.write("Hello, World!")
        raise ValueError("테스트 예외")
    ```

7. 예외 처리 모범 사례:
    1. 구체적인 예외를 먼저 처리하고, 더 일반적인 예외를 나중에 처리하세요.
    2. 빈 ```except```절을 사용하지 마세요. 모든 예외를 무시하면 디버깅이 어려워집니다.
    3. 로깅을 활용하여 예외 정보를 기록하세요.
    4. 예외 처리 블록 내에서 최소한의 코드만 실행하세요.
    5. 예외를 사용하여 일반적인 흐름을 제어하지 마세요. 예외는 예외적인 상황을 위한 것입니다.
     
### 정규 표현식 ###

정규 표현식은 문자열에서 특정 패턴을 찾거나 매칭하는 데 사용되는 강력한 도구입니다.
Python에서는 ```re```모듈을 통해 정규 표현식 기능을 제공합니다.

1. 기본 패턴 매칭:
```python
import re

text = "The quick brown fox jumps over the lazy dog"
pattern = r"fox"

if re.search(pattern, text):
    print("패턴을 찾았습니다!")
```

2. 주요 메타 문자:
    - ```.```: 임의의 한 문자
    - ```^```: 문자열의 시작
    - ```$```: 문자열의 끝
    - ```*```: 0회 이상 반복
    - ```+```: 1회 이상 반복
    - ```?```: 0회 또는 1회
    - ```{m,n}```: m회 이상 n회 이하 반복

    - 예시:
    ```python
    pattern = r"^The.*dog$"
    if re.match(pattern, text):
        print("전체 문장이 패턴과 일치합니다!")
    ```

3. 문자 클래스:
    - ```[abc]```: a,b 또는 c중 하나
    - ```[^abc]```: a,b,c를 제외한 모든 문자
    - ```[a-z]```: a부터 z까지의 모든 소문자
    - ```\d```: 숫자[0-9]
    - ```\w```: 단어 문자[a-zA-Z0-9]
    - ```\s```: 공백 문자
    
    - 예시:
    ```python
    pattern = r"\b\w+\b"
    words = re.findall(pattern, text)
    print(words)
    ```

4. 그룹과 캡처:
    - 괄호 ```()```를 사용하여 그룹을 만들고 캡처할 수 있습니다.
    ```python
    text = "John's phone number is 123-456-7890"
    pattern = r"(\d{3})-(\d{3})-(\d{4})"
    match = re.search(pattern, text)
    if match:
        print(f"Area code: {match.group(1)}")
        print(f"Exchange code: {match.group(2)}")
        print(f"Line number: {match.group(3)}")
    ```

5. 주요 re 모듈 함수:
    1. ```re.search(pattern, string)```: 문자열에서 패턴의 첫 번째 발생을 찾습니다.
    2. ```re.match(pattern, string)```: 문자열의 시작부터 패턴과 일치하는지 확인합니다.
    3. ```re.findall(pattern, string)```: 모든 일치하는 부분을 리스트로 반환합니다.
    4. ```re.finditer(pattern, string)```: 일치하는 부분의 이터레이터를 반환합니다.
    5. ```re.sub(pattern, string)```: 패턴과 일치하는 부분을 대체 문자열로 교체합니다.

6. 컴파일된 정규 표현식:
    - 자주 사용하는 패턴은 컴파일하여 성능을 향상시킬 수 있습니다.
    ```python
    pattern = re.compile(r"\b\w+\b")
    words = pattern.findall(text)
    ```

7. 플래그:
    - 정규 표현식의 동작을 수정하는 플래그를 사용할 수 있습니다.
        - ```re.IGNORECASE``` 또는 ```re.I```: 대소문자 구문 없이 매칭.
        - ```re.MULTILINE``` 또는 ```re.M```: 여러 줄에 걸쳐 매칭.
        - ```re.DOTALL``` 또는 ```re.S: ```:```.```이 개행 문자도 포함하도록 함.

    - 예시:
    ```python
    pattern = re.compile(r"^python", re.IGNORECASE | re.MULTILINE)
    ```

8. 탐욕적(Greedy) vs 비탐욕적(Non-greedy) 매칭:
    - 기본적으로 정규 표현식은 탐욕적입니다. 비탐욕적 매칭을 위해 ```?```를 사용합니다.
    ```python
    text = "<p>First paragraph</p><p>Second paragraph</p>"
    greedy = re.findall(r"<p>.*</p>", text)
    non_greedy = re.findall(r"<p>.*?</p>", text)
    print(f"Greedy: {greedy}")
    print(f"Non-greedy: {non_greedy}")
    ```

9. 정규 표현식 사용 시 주의사항:
    1. 복잡한 정규 표현식은 가독성이 떨어질 수 있으므로 주석을 달거나 분리하세요.
    2. 정규 표현식은 강력하지만, 때로는 간단한 문자열 메서드가 더 적합할 수 있습니다.
    3. 성능에 민감한 경우, 큰 텍스트에 대해 복잡한 정규 표현식을 반복 사용하는 것은 피하세요.
    4. 사용자 입력을 정규 표현식으로 사용하지 마세요. 보안 위험이 있을 수 있습니다.

### 함수형 프로그래밍 ###

함수형 프로그래밍은 계산을 수학적 함수의 평가로 취급하고 상태 변경과 가변 데이터를 피하는
프로그래밍 패러다임입니다. Python은 함수형 프로그래밍의 많은 특성을 지원합니다.

1. 일급 함수 (First-class Functions):
    - Python에서 함수는 일급 객체입니다. 이는 함수를 변수에 할당하고, 다른 함수의 인자로 전달하며, 함수에서 반환할 수 있음을 의미합니다.
    ```python
    def greet(name):
    return f"Hello, {name}!"

    # 함수를 변수에 할당
    say_hello = greet

    # 함수를 인자로 전달
    def apply_function(func, value):
        return func(value)

    result = apply_function(say_hello, "Alice")
    print(result)  # 출력: Hello, Alice!
    ```

2. 람다 함수 (Lambda Functions):
    - 람다 함수는 이름 없는 익명 함수를 생성하는 방법입니다.
    ```python
    square = lambda x: x ** 2
    print(square(5))  # 출력: 25

    # 정렬에 사용
    pairs = [(1, 'one'), (2, 'two'), (3, 'three'), (4, 'four')]
    pairs.sort(key=lambda pair: pair[1])
    print(pairs)  # 출력: [(4, 'four'), (1, 'one'), (3, 'three'), (2, 'two')]
    ```

3. 고차 함수(Higher-order Functions):
    - 고차 함수는 다른 함수를 인자로 받거나 함수를 결과로 반환하는 함수입니다.

    1. map() 함수:
    ```python
    numbers = [1, 2, 3, 4, 5]
    squared = list(map(lambda x: x**2, numbers))
    print(squared)  # 출력: [1, 4, 9, 16, 25]
    ```

    2. filter() 함수:
    ```python
    numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    evens = list(filter(lambda x: x % 2 == 0, numbers))
    print(evens)  # 출력: [2, 4, 6, 8, 10]
    ```

    3. Reduce() 함수:
    ```python
    from functools import reduce

    numbers = [1, 2, 3, 4, 5]
    sum_all = reduce(lambda x, y: x + y, numbers)
    print(sum_all)  # 출력: 15
    ```

4. 순수 함수(Pure Functions):
    - 순수 함수는 동일한 입력에 대해 항상 동일한 출력을 반환하며, 부작용(side effects)이 없는 함수입니다.
    ```python
    # 순수 함수
    def add(a, b):
        return a + b

    # 순수하지 않은 함수
    total = 0
    def add_to_total(value):
        global total
        total += value
        return total
    ```

5. 불변성(Immutabiliy):
    - 함수형 프로그래밍에서는 데이터의 불변성을 강조합니다. Python에서는 튜플과 frozenset 같은 불변 자료구조를 제공합니다.
    ```python
    # 불변 리스트 대신 튜플 사용
    immutable_list = (1, 2, 3, 4, 5)

    # 불변 집합
    immutable_set = frozenset([1, 2, 3, 4, 5])
    ```

6. 재귀(Recursion):
    - 재귀는 함수가 자기 자신을 호출하는 기법으로, 함수형 프로그래밍에서 반복을 표현하는 주요 방법입니다.
    ```python
    def factorial(n):
        if n == 0 or n == 1:
            return 1
        else:
            return n * factorial(n - 1)

    print(factorial(5))  # 출력: 120
    ```

7. 함수 데코레이터(Function Decorator):
    - 데코레이터는 기존 함수를 수정하지 않고 기능을 확장하는 방법입니다.
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

8. 클로저(Closure):
    - 클로저는 자신을 둘러싼 환경을 기억하는 함수입니다.
    ```python
    def multiplier(n):
        def multiply(x):
            return x * n
        return multiply

    double = multiplier(2)
    triple = multiplier(3)

    print(double(5))  # 출력: 10
    print(triple(5))  # 출력: 15
    ```

9. 함수형 프로그래밍의 이점:
    1. 코드의 간결성과 가독성 향상.
    2. 테스트와 디버깅이 쉬움.
    3. 병렬 처리에 적합
    4. 부작용을 줄여 예측 가능한 코드 작성 가능.

### 제너레이터와 이터레이터 ###

제너레이터와 이터레이터는 Python에서 대량의 데이터를 효율적으로 처리하는 데 사용되는 중요한 개념입니다.

1. 이터레이터 (Iterator):
    - 이터레이터는 데이터 스트림을 표현하는 객체입니다. ```__iter__()```와 ```__next__()``` 메서드를 구현합니다.
    
    1. 이터레이터 프로토콜:
    ```python
    class MyIterator:
        def __init__(self, max):
            self.max = max
            self.n = 0

        def __iter__(self):
            return self

        def __next__(self):
            if self.n < self.max:
                result = self.n
                self.n += 1
                return result
            else:
                raise StopIteration

    for i in MyIterator(5):
        print(i)  # 출력: 0, 1, 2, 3, 4
    ```

    2. 내장 함수 iter()와 next():
    ```python
    my_list = [1, 2, 3, 4, 5]
    my_iter = iter(my_list)

    print(next(my_iter))  # 출력: 1
    print(next(my_iter))  # 출력: 2
    ```

2. 제너레이터 (Generator):
    - 제너레이터는 이터레이터를 생성하는 함수입니다. ```yield```키워드를 사용하여 값을 하나씩 반환합니다.

    1. 제너레이터 함수:
    ```python
    def countdown(n):
        while n > 0:
            yield n
            n -= 1

    for i in countdown(5):
        print(i)  # 출력: 5, 4, 3, 2, 1
    ```

    2. 제너레이터 표현식:
    ```python
    squares = (x**2 for x in range(5))
    print(list(squares))  # 출력: [0, 1, 4, 9, 16]
    ```

3. 제너레이터 장점:
    1. 메모리 효율성: 모든 값을 한 번에 메모리에 저장하지 않고 필요할 때 생성합니다.
    2. 지연 평가 (Lazy Evaluation): 필요한 시점에 값을 계산합니다.
    3. 무한 시퀀스 표현 가능:
    ```python
    def infinite_sequence():
        n = 0
        while True:
            yield n
            n += 1

    gen = infinite_sequence()
    print(next(gen))  # 출력: 0
    print(next(gen))  # 출력: 1
    ```

4. 제너레이터 메서드:
    1. send(): 제너레이터 값을 전달합니다.
    2. throw(): 제너레이터에 예외를 전달합니다.
    3. close(): 제너레이터를 종료합니다.
    ```python
    def echo_generator():
        while True:
            value = yield
            print(f"Received: {value}")

    gen = echo_generator()
    next(gen)  # 제너레이터 초기화
    gen.send("Hello")  # 출력: Received: Hello
    gen.send("World")  # 출력: Received: World
    gen.close()
    ```

5. 이터레이터와 제너레이터의 활용:
    1. 파일 읽기:
    ```python
    def read_large_file(file_path):
        with open(file_path, 'r') as file:
            for line in file:
                yield line.strip()

    for line in read_large_file('large_file.txt'):
        print(line)
    ```

    2. 피보나치 수열:
    ```python
    def fibonacci():
        a, b = 0, 1
        while True:
            yield a
            a, b = b, a + b

    fib = fibonacci()
    for _ in range(10):
        print(next(fib))  # 처음 10개의 피보나치 수 출력
    ```

6. 이터레이터와 제너레이터 도구:
    1. itertools 모듈:
    ```python
    import itertools

    # 무한 반복
    for i in itertools.repeat("Hello", 3):
        print(i)  # "Hello"를 3번 출력

    # 순열
    for perm in itertools.permutations([1, 2, 3], 2):
        print(perm)

    # 조합
    for comb in itertools.combinations([1, 2, 3, 4], 2):
        print(comb)
    ```

    2. 제너레이터 파이프라인:
    ```python
    def generate_numbers(n):
        for i in range(n):
            yield i

    def square_numbers(numbers):
        for number in numbers:
            yield number ** 2

    def add_one(numbers):
        for number in numbers:
            yield number + 1

    pipeline = add_one(square_numbers(generate_numbers(5)))
    print(list(pipeline))  # 출력: [1, 2, 5, 10, 17]
    ```

### 데코레이터 ###

데코레이터는 기존 코드를 수정하지 않고 함수나 메서드의 기능을 확장하거나 수정하는 방법입니다.
이는 Python의 강력한 기능 중 하나로, 코드의 재사용성과 가독성을 높이는 데 도움이 됩니다.

1. 기본 데코레이터:
    1. 간단한 데코레이터:
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

    2. 인자를 가진 함수에 대한 데코레이터:
    ```python
    def decorator(func):
        def wrapper(*args, **kwargs):
            print("Something is happening before the function is called.")
            result = func(*args, **kwargs)
            print("Something is happening after the function is called.")
            return result
        return wrapper

    @decorator
    def say_hello(name):
        print(f"Hello, {name}!")

    say_hello("Alice")
    ```

2. 데코레이터에 인자 전달:
```python
def repeat(times):
    def decorator(func):
        def wrapper(*args, **kwargs):
            for _ in range(times):
                result = func(*args, **kwargs)
            return result
        return wrapper
    return decorator

@repeat(3)
def greet(name):
    print(f"Hello, {name}!")

greet("Bob")  # "Hello, Bob!"를 3번 출력
```

3. 클래스 데코레이터: 클래스를 데코레이터로 사용할 수 있습니다.
```python
class CountCalls:
    def __init__(self, func):
        self.func = func
        self.num_calls = 0

    def __call__(self, *args, **kwargs):
        self.num_calls += 1
        print(f"Call {self.num_calls} of {self.func.__name__!r}")
        return self.func(*args, **kwargs)

@CountCalls
def say_hello():
    print("Hello!")

say_hello()
say_hello()
```

4. 데코레이터 체이닝: 여러 데코레이터를 동시에 적용할 수 있습니다.
```python
def bold(func):
    def wrapper():
        return "<b>" + func() + "</b>"
    return wrapper

def italic(func):
    def wrapper():
        return "<i>" + func() + "</i>"
    return wrapper

@bold
@italic
def greet():
    return "Hello, world!"

print(greet())  # 출력: <b><i>Hello, world!</i></b>
```

5. functools.wraps 사용:
    - 데코레이터를 사용하면 원본 함수의 메타데이터가 손실될 수 있습니다. ```functools.wraps```를 사용하여 이를 방지할 수 있습니다.
    ```python
    from functools import wraps

    def log_function_call(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            print(f"Calling function: {func.__name__}")
            return func(*args, **kwargs)
        return wrapper

    @log_function_call
    def add(x, y):
        """Add two numbers."""
        return x + y

    print(add.__name__)  # 출력: add
    print(add.__doc__)   # 출력: Add two numbers.
    ```

6. 데코레이터의 일반적인 사용 사례:
    1. 로깅
    2. 시간 측정
    3. 접근 제어 및 인증
    4. 캐싱
    5. 에러 처리
    예시 (시간 측정 데코레이터):
    ```python
    import time

    def timing_decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            start_time = time.time()
            result = func(*args, **kwargs)
            end_time = time.time()
            print(f"{func.__name__} took {end_time - start_time:.2f} seconds to execute.")
            return result
        return wrapper

    @timing_decorator
    def slow_function():
        time.sleep(2)

    slow_function()
    ```

7. 클래스 메서드와 정적 메서드의 데코레이터:
    - Python에서는 ```@classmethod```와 ```@staticmethod```데코레이터를 제공하여 클래스 메서드와 정적 메서드를 정의할 수 있습니다.
    ```python
    class MyClass:
        @classmethod
        def class_method(cls):
            print("This is a class method")

        @staticmethod
        def static_method():
            print("This is a static method")

    MyClass.class_method()
    MyClass.static_method()
    ```

### 동시성 프로그래밍 ###

동시성 프로그래밍은 여러 작업을 동시에 실행하는 프로그래밍 패러다임입니다.
Python에서는 주로 threading, multiprocessing, 그리고 asyncio를 사용하여 동시성을 구현합니다.

1. 스레딩(Threading):
    - 스레딩은 하나의 프로세스 내에서 여러 실행 흐름을 만드는 방법입니다.

    1. 기본 스레드 생성:
    ```python
    import threading
    import time

    def worker(name):
        print(f"Worker {name} starting")
        time.sleep(2)
        print(f"Worker {name} finished")

    threads = []
    for i in range(5):
        t = threading.Thread(target=worker, args=(i,))
        threads.append(t)
        t.start()

    for t in threads:
        t.join()

    print("All workers finished")
    ```

    2. 스레드 동기화:
    ```python
    import threading

    counter = 0
    lock = threading.Lock()

    def increment():
        global counter
        with lock:
            for _ in range(100000):
                counter += 1

    threads = [threading.Thread(target=increment) for _ in range(5)]

    for t in threads:
        t.start()

    for t in threads:
        t.join()

    print(f"Counter value: {counter}")
    ```

2. 멀티 프로세싱 (Multiprocessing):
    - 멀티 프로세싱은 여러 프로세스를 생성하여 병렬 처리를 수행합니다. CPU 바운드 작업에 적합합니다.
    ```python
    import multiprocessing
    import time

    def worker(num):
        print(f"Worker {num} starting")
        time.sleep(2)
        print(f"Worker {num} finished")

    if __name__ == "__main__":
        processes = []
        for i in range(5):
            p = multiprocessing.Process(target=worker, args=(i,))
            processes.append(p)
            p.start()

        for p in processes:
            p.join()

        print("All workers finished")
    ```

3. 프로세스 풀(Process Pool):
    - 여러 작업을 동시에 처리하기 위한 프로세스 풀을 생성할 수 있습니다.
    ```python
    from multiprocessing import Pool

    def f(x):
        return x*x

    if __name__ == "__main__":
        with Pool(5) as p:
            print(p.map(f, [1, 2, 3, 4, 5]))
    ```

4. asyncio:
    - asyncio는 Python의 비동기 프로그래밍을 위한 라이브러리입니다. I/O 바운드 작업에 특히 유용합니다.

    1. 기본 asyncio 사용:
    ```python
    import asyncio

    async def say_after(delay, what):
        await asyncio.sleep(delay)
        print(what)

    async def main():
        print("started at", time.strftime('%X'))
        
        await say_after(1, 'hello')
        await say_after(2, 'world')
        
        print("finished at", time.strftime('%X'))

    asyncio.run(main())
    ```

    2. 여러 작업을 동시에 실행:
    ```python
    import asyncio

    async def fetch_data(url):
        print(f"Start fetching {url}")
        await asyncio.sleep(2)  # 네트워크 요청을 시뮬레이션
        print(f"Finished fetching {url}")
        return f"Data from {url}"

    async def main():
        urls = ['http://example.com', 'http://example.org', 'http://example.net']
        tasks = [fetch_data(url) for url in urls]
        results = await asyncio.gather(*tasks)
        print(results)

    asyncio.run(main())
    ```

5. 동시성 프로그래밍의 주의사항
    1. 경쟁 조건 (Race Conditions): 여러 스레드나 프로세스가 동시에 같은 자원에 접근할 때 발생할 수 있는 문제
    2. 데드락 (Deadlock): 두 개 이상의 작업이 서로 상대방의 작업이 끝나기를 기다리며 진행되지 않는 상태
    3. 동기화 오버헤드: 과도한 동기화는 성능 저하를 일으킬 수 있음
    4. 컨텍스트 스위칭: 스레드나 프로세스 간의 전환에 따른 비용

6. 동시성 프로그래밍 선택 가이드

    1. I/O 바운드 작업: asyncio 또는 threading
    2. CPU 바운드 작업: multiprocessing 
    3. 간단한 병렬 처리: concurrent.futures 모듈