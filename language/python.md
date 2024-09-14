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

#### 데이터 구조 ####

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

