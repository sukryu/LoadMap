# Python 고급 기능: 데코레이터의 이해와 활용 🎯

## 데코레이터란?

데코레이터는 기존 함수나 클래스의 동작을 수정하거나 확장하는 Python의 강력한 기능입니다. 데코레이터를 사용하면 코드를 수정하지 않고도 새로운 기능을 추가할 수 있으며, 코드의 재사용성과 유지보수성을 높일 수 있습니다.

## 기본 데코레이터 구현

가장 기본적인 데코레이터의 구조를 살펴보겠습니다:

```python
def simple_decorator(func):
    def wrapper():
        print("함수 실행 전 작업")
        func()
        print("함수 실행 후 작업")
    return wrapper

@simple_decorator
def greet():
    print("안녕하세요!")

# 실행 결과:
# 함수 실행 전 작업
# 안녕하세요!
# 함수 실행 후 작업
```

## 매개변수를 가진 함수 데코레이팅

```python
def parameter_decorator(func):
    def wrapper(*args, **kwargs):
        print(f"전달된 인자: {args}, {kwargs}")
        result = func(*args, **kwargs)
        print(f"함수 반환값: {result}")
        return result
    return wrapper

@parameter_decorator
def add_numbers(a, b):
    return a + b

# 사용 예시
result = add_numbers(3, 5)  # 전달된 인자: (3, 5), {}
                           # 함수 반환값: 8
```

## 데코레이터에 인자 전달하기

데코레이터 자체에 매개변수를 전달하는 방법입니다:

```python
def repeat(times):
    def decorator(func):
        def wrapper(*args, **kwargs):
            results = []
            for _ in range(times):
                result = func(*args, **kwargs)
                results.append(result)
            return results
        return wrapper
    return decorator

@repeat(times=3)
def get_random_number():
    import random
    return random.randint(1, 100)

# 사용 예시
numbers = get_random_number()  # [45, 78, 23] (무작위 숫자 3개)
```

## 실전 활용 사례

### 1. 실행 시간 측정 데코레이터

```python
import time
import functools

def measure_time(func):
    @functools.wraps(func)  # 함수의 메타데이터 보존
    def wrapper(*args, **kwargs):
        start_time = time.time()
        result = func(*args, **kwargs)
        end_time = time.time()
        print(f"{func.__name__} 함수 실행 시간: {end_time - start_time:.4f}초")
        return result
    return wrapper

@measure_time
def complex_calculation():
    # 시간이 걸리는 작업 수행
    return sum(i * i for i in range(1000000))
```

### 2. 캐싱(메모이제이션) 데코레이터

```python
def memoize(func):
    cache = {}
    @functools.wraps(func)
    def wrapper(*args):
        if args not in cache:
            cache[args] = func(*args)
        return cache[args]
    return wrapper

@memoize
def fibonacci(n):
    if n < 2:
        return n
    return fibonacci(n-1) + fibonacci(n-2)
```

### 3. 로깅 데코레이터

```python
import logging

def log_function_call(func):
    logging.basicConfig(level=logging.INFO)
    logger = logging.getLogger(func.__name__)
    
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        logger.info(f"함수 호출: {func.__name__}(args={args}, kwargs={kwargs})")
        try:
            result = func(*args, **kwargs)
            logger.info(f"함수 반환값: {result}")
            return result
        except Exception as e:
            logger.error(f"함수 실행 중 오류 발생: {str(e)}")
            raise
    return wrapper

@log_function_call
def divide_numbers(a, b):
    return a / b
```

### 4. 입력 검증 데코레이터

```python
def validate_inputs(*types):
    def decorator(func):
        @functools.wraps(func)
        def wrapper(*args):
            if len(args) != len(types):
                raise ValueError("인자 개수가 올바르지 않습니다.")
            
            for arg, type_ in zip(args, types):
                if not isinstance(arg, type_):
                    raise TypeError(f"잘못된 타입: {arg}는 {type_}이어야 합니다.")
            
            return func(*args)
        return wrapper
    return decorator

@validate_inputs(int, int)
def calculate_rectangle_area(width, height):
    return width * height
```

## 클래스 데코레이터

클래스에도 데코레이터를 적용할 수 있습니다:

```python
def singleton(cls):
    instances = {}
    
    @functools.wraps(cls)
    def get_instance(*args, **kwargs):
        if cls not in instances:
            instances[cls] = cls(*args, **kwargs)
        return instances[cls]
    
    return get_instance

@singleton
class DatabaseConnection:
    def __init__(self):
        self.connected = False
    
    def connect(self):
        if not self.connected:
            print("데이터베이스에 연결합니다.")
            self.connected = True
```

## 데코레이터 응용: 웹 프레임워크 예시

실제 웹 프레임워크에서 자주 사용되는 데코레이터 패턴입니다:

```python
def route(path):
    def decorator(func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            print(f"요청 경로: {path}")
            return func(*args, **kwargs)
        wrapper.route = path
        return wrapper
    return decorator

@route('/hello')
def hello():
    return "Hello, World!"

@route('/users/<id>')
def get_user(id):
    return f"사용자 ID: {id}"
```

## 주의사항과 모범 사례

1. **functools.wraps 사용**: 데코레이터 사용 시 원본 함수의 메타데이터를 보존하기 위해 필수적입니다.

2. **디버깅 용이성**: 데코레이터가 너무 복잡해지면 디버깅이 어려워질 수 있으므로 적절한 수준의 복잡도를 유지해야 합니다.

3. **성능 고려**: 여러 데코레이터를 중첩해서 사용할 경우 성능에 영향을 줄 수 있습니다.

4. **문서화**: 데코레이터의 동작을 명확히 문서화하여 다른 개발자들이 쉽게 이해할 수 있도록 합니다.

## 실습 과제

다음 요구사항을 만족하는 데코레이터를 구현해보세요:

1. 함수의 실행 시간이 지정된 시간을 초과할 경우 경고를 출력하는 데코레이터
2. 함수의 반환값을 파일에 자동으로 저장하는 데코레이터
3. 특정 예외가 발생했을 때 재시도하는 데코레이터
4. API 요청에 대한 응답을 캐싱하는 데코레이터