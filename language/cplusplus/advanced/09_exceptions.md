# 09_exceptions: Advanced Exception Handling in C++

C++의 예외 처리는 프로그램의 안정성을 유지하고 오류를 관리하는 데 중요한 역할을 합니다. 이 문서에서는 예외 처리의 고급 주제와 실무에서 활용할 수 있는 기법을 다룹니다.

---

## 1. 표준 예외 클래스
C++ 표준 라이브러리는 다양한 예외 클래스 계층을 제공합니다.

### 1.1 주요 예외 클래스
| 클래스             | 설명                                        |
|--------------------|---------------------------------------------|
| `std::exception`   | 모든 표준 예외의 기본 클래스                |
| `std::runtime_error` | 런타임 오류를 나타냅니다.                 |
| `std::logic_error`   | 논리적 오류를 나타냅니다.                 |
| `std::out_of_range`  | 범위를 벗어난 접근을 나타냅니다.           |
| `std::bad_alloc`     | 메모리 할당 실패를 나타냅니다.             |

### 1.2 표준 예외 클래스 사용 예제
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

## 2. 사용자 정의 예외
사용자 정의 예외는 표준 예외 클래스를 상속받아 구현할 수 있습니다.

### 2.1 사용자 정의 예외 구현
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

## 3. 예외 전파
예외는 호출 스택을 따라 전파되며, 적절한 `catch` 블록에서 처리됩니다.

### 3.1 예제: 예외 전파
```cpp
#include <iostream>
#include <stdexcept>

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

---

## 4. `noexcept`
`noexcept`는 함수가 예외를 던지지 않음을 나타냅니다. 이를 통해 컴파일러는 추가적인 최적화를 수행할 수 있습니다.

### 4.1 예제
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

## 5. 전역 예외 처리
전역 예외 처리는 처리되지 않은 예외를 포착할 때 사용됩니다.

### 5.1 예제
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

## 6. 예외 안전성
예외가 발생해도 리소스가 올바르게 해제되도록 설계하는 것이 중요합니다.

### 6.1 RAII와 예외 안전성
RAII(Resource Acquisition Is Initialization)는 리소스 관리를 객체의 수명과 연관시키는 기법입니다.

#### 예제
```cpp
#include <iostream>
#include <fstream>

class FileHandler {
private:
    std::ofstream file;

public:
    FileHandler(const std::string& filename) {
        file.open(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file");
        }
    }

    ~FileHandler() {
        if (file.is_open()) {
            file.close();
        }
    }

    void write(const std::string& content) {
        file << content << std::endl;
    }
};

int main() {
    try {
        FileHandler handler("example.txt");
        handler.write("Hello, RAII with exceptions!");
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
```

---

## 7. 예외 처리 모범 사례

### 7.1 구체적인 예외를 사용
- 일반적인 `std::exception` 대신 구체적인 예외 클래스 사용을 권장합니다.

### 7.2 예외는 예외적인 상황에서만 사용
- 일반적인 흐름 제어에는 예외를 사용하지 않습니다.

### 7.3 리소스 누수 방지
- RAII 패턴을 활용하여 리소스를 안전하게 관리합니다.

---

C++의 예외 처리 메커니즘은 복잡한 시스템에서 안정성과 유지보수성을 높이는 데 필수적입니다. 위의 내용을 통해 고급 예외 처리 기법을 익히고 실무에 활용할 수 있습니다.