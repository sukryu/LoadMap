# 04_exceptions: Exception Handling in C++

C++의 예외 처리(Exception Handling)는 프로그램 실행 중에 발생하는 오류를 효율적으로 관리하는 방법을 제공합니다. 예외 처리를 통해 오류를 감지하고 적절히 대응하여 프로그램의 안정성과 신뢰성을 높일 수 있습니다.

---

## 1. 예외 처리 기본 개념
예외 처리는 주로 `try`, `catch`, `throw` 키워드를 사용합니다.

### 1.1 예외 처리 구조
```cpp
try {
    // 예외가 발생할 가능성이 있는 코드
} catch (exception_type variable) {
    // 예외 처리 코드
}
```

### 1.2 예제: 기본 예외 처리
```cpp
#include <iostream>

int main() {
    try {
        int a = 10;
        int b = 0;
        if (b == 0) {
            throw "Division by zero!";
        }
        std::cout << a / b << std::endl;
    } catch (const char* e) {
        std::cerr << "Error: " << e << std::endl;
    }
    return 0;
}
```

#### 설명:
- `throw`: 예외를 발생시킵니다.
- `try`: 예외가 발생할 가능성이 있는 코드를 감쌉니다.
- `catch`: 예외를 처리하는 블록입니다.

---

## 2. 예외의 전파
예외는 호출 스택을 거슬러 올라가면서 적절한 `catch` 블록을 찾을 때까지 전파됩니다.

### 예제: 예외 전파
```cpp
#include <iostream>

void functionA() {
    throw std::runtime_error("Error in functionA");
}

void functionB() {
    functionA();
}

int main() {
    try {
        functionB();
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
}
```

#### 출력:
```
Caught exception: Error in functionA
```

---

## 3. 표준 예외 클래스
C++ 표준 라이브러리는 다양한 예외 클래스를 제공합니다.

### 주요 예외 클래스
| 클래스             | 설명                                        |
|--------------------|---------------------------------------------|
| `std::exception`   | 모든 표준 예외의 기본 클래스                |
| `std::runtime_error` | 런타임 오류를 나타냅니다.                 |
| `std::logic_error`   | 논리적 오류를 나타냅니다.                 |
| `std::bad_alloc`     | 메모리 할당 실패를 나타냅니다.             |
| `std::out_of_range`  | 범위를 벗어난 접근을 나타냅니다.           |

### 예제: 표준 예외 클래스 사용
```cpp
#include <iostream>
#include <stdexcept>

int main() {
    try {
        throw std::out_of_range("Index out of range");
    } catch (const std::out_of_range& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
}
```

---

## 4. 사용자 정의 예외
사용자 정의 예외는 표준 예외 클래스를 상속받아 구현할 수 있습니다.

### 예제: 사용자 정의 예외 클래스
```cpp
#include <iostream>
#include <exception>

class MyException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Custom exception occurred!";
    }
};

int main() {
    try {
        throw MyException();
    } catch (const MyException& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
```

---

## 5. 예외 처리 모범 사례

### 5.1 구체적인 예외 사용
- 일반적인 예외(`std::exception`)보다 구체적인 예외(`std::out_of_range`, `std::invalid_argument` 등)를 사용하는 것이 좋습니다.

### 5.2 예외 안전성 보장
- 자원을 올바르게 해제하여 리소스 누수를 방지해야 합니다.

#### 예제: 예외 안전성 보장
```cpp
#include <iostream>
#include <memory>

void process() {
    std::unique_ptr<int> ptr(new int(10));
    throw std::runtime_error("Error occurred");
}

int main() {
    try {
        process();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
```

### 5.3 예외를 예외적인 상황에서만 사용
- 일반적인 흐름 제어에는 예외를 사용하지 않습니다.

---

## 6. noexcept
`noexcept`는 함수가 예외를 던지지 않음을 나타냅니다.

### 예제: `noexcept` 사용
```cpp
#include <iostream>

void safeFunction() noexcept {
    std::cout << "This function does not throw exceptions." << std::endl;
}

int main() {
    safeFunction();
    return 0;
}
```

---

## 7. 전역 예외 처리
전역 예외 처리는 처리되지 않은 예외를 포착할 때 사용됩니다.

### 예제: 전역 예외 처리
```cpp
#include <iostream>
#include <exception>

void handleTerminate() {
    std::cerr << "Unhandled exception!" << std::endl;
    std::abort();
}

int main() {
    std::set_terminate(handleTerminate);

    throw std::runtime_error("Unhandled exception example");

    return 0;
}
```

---

C++의 예외 처리는 프로그램의 안정성을 유지하고 오류를 처리하는 데 필수적입니다. 이 문서를 통해 예외 처리의 기본 및 고급 주제를 학습할 수 있습니다.

