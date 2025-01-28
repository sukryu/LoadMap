# 05_cpp11_basics: C++11 Basics

C++11은 C++ 언어의 주요 업데이트로, 생산성과 성능을 향상시키는 다양한 기능을 도입했습니다. 이 문서에서는 C++11의 핵심 기능과 이를 활용하는 방법을 다룹니다.

---

## 1. 자동 타입 추론 (`auto`)
`auto` 키워드는 컴파일러가 변수의 타입을 자동으로 추론하도록 합니다.

### 예제
```cpp
#include <iostream>
#include <vector>

int main() {
    auto x = 10;              // x는 int 타입
    auto y = 3.14;            // y는 double 타입
    auto z = "Hello, C++11!"; // z는 const char* 타입

    std::vector<int> numbers = {1, 2, 3, 4};
    for (auto num : numbers) {
        std::cout << num << " ";
    }
    return 0;
}
```

---

## 2. 범위 기반 for 루프
C++11에서는 컨테이너의 요소를 쉽게 순회할 수 있는 범위 기반 for 루프를 제공합니다.

### 예제
```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    for (int num : vec) {
        std::cout << num << " ";
    }

    // 요소를 수정하려면 참조 사용
    for (int& num : vec) {
        num *= 2;
    }

    for (int num : vec) {
        std::cout << num << " ";
    }
    return 0;
}
```

---

## 3. 람다 표현식 (Lambda Expressions)
람다는 익명 함수(이름이 없는 함수)를 정의하는 데 사용됩니다.

### 기본 문법
```cpp
[capture_list](parameter_list) -> return_type {
    // 함수 본문
};
```

### 예제
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 람다를 사용하여 벡터 요소 출력
    std::for_each(vec.begin(), vec.end(), [](int num) {
        std::cout << num << " ";
    });

    // 람다로 요소 필터링
    vec.erase(std::remove_if(vec.begin(), vec.end(), [](int num) {
        return num % 2 == 0; // 짝수 제거
    }), vec.end());

    std::cout << "\nAfter filtering: ";
    for (int num : vec) {
        std::cout << num << " ";
    }

    return 0;
}
```

---

## 4. 스마트 포인터
C++11은 메모리 관리를 자동화하기 위해 스마트 포인터(`std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`)를 도입했습니다.

### 4.1 `std::unique_ptr`
- 단일 소유권을 가진 스마트 포인터.

#### 예제
```cpp
#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<int> ptr = std::make_unique<int>(42);
    std::cout << *ptr << std::endl;

    // 소유권 이동
    std::unique_ptr<int> ptr2 = std::move(ptr);
    if (!ptr) {
        std::cout << "ptr is now empty." << std::endl;
    }
    return 0;
}
```

### 4.2 `std::shared_ptr`
- 참조 카운트를 통해 여러 포인터가 동일한 자원을 공유.

#### 예제
```cpp
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> ptr1 = std::make_shared<int>(42);
    std::shared_ptr<int> ptr2 = ptr1; // 공유 소유권

    std::cout << "Use count: " << ptr1.use_count() << std::endl;
    return 0;
}
```

### 4.3 `std::weak_ptr`
- `std::shared_ptr`의 순환 참조 문제를 해결.

#### 예제
```cpp
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> shared = std::make_shared<int>(42);
    std::weak_ptr<int> weak = shared;

    if (auto spt = weak.lock()) { // 공유 포인터 생성
        std::cout << *spt << std::endl;
    } else {
        std::cout << "Resource is no longer available." << std::endl;
    }
    return 0;
}
```

---

## 5. 이동 의미론과 `std::move`
C++11은 이동 의미론을 도입하여 불필요한 복사를 줄이고 성능을 최적화했습니다.

### 예제
```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec1 = {1, 2, 3};
    std::vector<int> vec2 = std::move(vec1); // vec1의 자원을 vec2로 이동

    std::cout << "vec1 size: " << vec1.size() << std::endl;
    std::cout << "vec2 size: " << vec2.size() << std::endl;
    return 0;
}
```

---

## 6. 초기화 리스트
초기화 리스트를 사용하면 객체를 더 간결하고 직관적으로 초기화할 수 있습니다.

### 예제
```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    for (int num : vec) {
        std::cout << num << " ";
    }
    return 0;
}
```

---

## 7. `nullptr`
`nullptr`는 명확하고 타입 안전한 null 포인터를 나타냅니다.

### 예제
```cpp
#include <iostream>

void foo(int* ptr) {
    if (ptr == nullptr) {
        std::cout << "Pointer is null." << std::endl;
    }
}

int main() {
    int* p = nullptr;
    foo(p);
    return 0;
}
```

---

## 8. 열거형 클래스 (`enum class`)
C++11은 강한 타입을 가진 열거형 클래스를 제공합니다.

### 예제
```cpp
#include <iostream>

enum class Color { Red, Green, Blue };

int main() {
    Color c = Color::Red;
    if (c == Color::Red) {
        std::cout << "Color is Red." << std::endl;
    }
    return 0;
}
```

---

C++11은 이전 표준에 비해 많은 개선을 제공하여 더 간결하고 효율적인 코드를 작성할 수 있도록 도와줍니다. 이 문서를 통해 C++11의 주요 기능을 익히고 실무에 적용할 수 있습니다.

