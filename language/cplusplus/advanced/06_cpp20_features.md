# 06_cpp20_features: C++20 New Features

C++20은 C++ 표준의 중요한 업데이트로, 프로그래밍 생산성과 성능을 크게 향상시키는 많은 기능들을 도입했습니다. 이 문서에서는 C++20의 주요 기능과 그 활용 방법을 다룹니다.

---

## 1. Concepts
Concepts는 템플릿 매개변수에 제약 조건을 설정하여 코드의 가독성과 안정성을 높입니다.

### 1.1 기본 문법
```cpp
template <typename T>
concept Numeric = requires(T a, T b) {
    a + b;
    a - b;
    a * b;
    a / b;
};

Numeric auto add(Numeric auto a, Numeric auto b) {
    return a + b;
}
```

### 1.2 예제
```cpp
#include <iostream>
#include <concepts>
using namespace std;

template <typename T>
concept Numeric = requires(T a, T b) {
    a + b;
    a - b;
    a * b;
    a / b;
};

Numeric auto add(Numeric auto a, Numeric auto b) {
    return a + b;
}

int main() {
    cout << add(3, 5) << endl;       // 8 출력
    cout << add(3.5, 2.5) << endl;   // 6.0 출력
    return 0;
}
```

---

## 2. Ranges
Ranges 라이브러리는 컨테이너와 알고리즘을 더 쉽게 조합할 수 있는 새로운 방식의 인터페이스를 제공합니다.

### 2.1 기본 사용법
```cpp
#include <iostream>
#include <vector>
#include <ranges>
using namespace std;

int main() {
    vector<int> vec = {1, 2, 3, 4, 5};

    auto even = vec | std::ranges::views::filter([](int n) { return n % 2 == 0; })
                    | std::ranges::views::transform([](int n) { return n * 2; });

    for (int n : even) {
        cout << n << " ";
    }
    return 0;
}
```

---

## 3. 코루틴 (Coroutines)
코루틴은 중단점과 재개점을 지원하는 함수로, 비동기 프로그래밍이나 생성기를 구현하는 데 사용됩니다.

### 3.1 예제: 생성기 구현
```cpp
#include <iostream>
#include <coroutine>
using namespace std;

struct Generator {
    struct promise_type {
        int current_value;

        Generator get_return_object() {
            return Generator{Handle::from_promise(*this)};
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        std::suspend_always yield_value(int value) {
            current_value = value;
            return {};
        }
        void return_void() {}
        void unhandled_exception() { std::exit(1); }
    };

    using Handle = std::coroutine_handle<promise_type>;
    Handle coro;

    explicit Generator(Handle h) : coro(h) {}
    ~Generator() { if (coro) coro.destroy(); }

    bool move_next() { return coro.resume(), !coro.done(); }
    int current_value() { return coro.promise().current_value; }
};

Generator generator(int start, int end) {
    for (int i = start; i < end; ++i) {
        co_yield i;
    }
}

int main() {
    auto gen = generator(1, 5);
    while (gen.move_next()) {
        cout << gen.current_value() << " ";
    }
    return 0;
}
```

---

## 4. `std::span`
`std::span`은 범위를 표현하는 경량 뷰로, 배열이나 컨테이너의 데이터를 복사하지 않고 참조합니다.

### 4.1 예제
```cpp
#include <iostream>
#include <span>
using namespace std;

void print(span<int> arr) {
    for (int n : arr) {
        cout << n << " ";
    }
}

int main() {
    int data[] = {1, 2, 3, 4, 5};
    print(data);
    return 0;
}
```

---

## 5. Three-way Comparison Operator (`<=>`)
`<=>` 연산자는 세 가지 관계를 동시에 비교할 수 있는 기능을 제공합니다.

### 5.1 기본 사용법
```cpp
#include <iostream>
#include <compare>
using namespace std;

struct Point {
    int x, y;
    auto operator<=>(const Point&) const = default;
};

int main() {
    Point p1{1, 2}, p2{1, 3};

    if (p1 < p2) {
        cout << "p1 is less than p2" << endl;
    } else {
        cout << "p1 is not less than p2" << endl;
    }

    return 0;
}
```

---

## 6. Modules
Modules는 헤더 파일의 단점을 보완하고 컴파일 시간을 단축하기 위해 도입된 새로운 기능입니다.

### 6.1 기본 사용법
#### math.ixx
```cpp
export module math;

export int add(int a, int b) {
    return a + b;
}
```

#### main.cpp
```cpp
import math;
#include <iostream>
using namespace std;

int main() {
    cout << add(3, 5) << endl; // 8 출력
    return 0;
}
```

---

## 7. 기타 기능
### 7.1 `constexpr` 가상 함수

`constexpr` 가상 함수는 C++20에서 도입된 기능으로, 컴파일 타임에 평가 가능한 가상 함수를 정의할 수 있습니다. 이를 통해 상속 구조에서도 컴파일 타임 상수를 사용할 수 있습니다.

```cpp
#include <iostream>
using namespace std;

struct Base {
    virtual constexpr int value() const = 0;
};

struct Derived : Base {
    constexpr int value() const override { return 42; }
};

int main() {
    constexpr Derived d;
    static_assert(d.value() == 42);
    return 0;
}
```
```cpp
#include <iostream>
using namespace std;

struct Base {
    virtual constexpr int value() const = 0;
};

struct Derived : Base {
    constexpr int value() const override { return 42; }
};

int main() {
    constexpr Derived d;
    static_assert(d.value() == 42);
    return 0;
}
```

### 7.2 `std::format`
C++20은 Python 스타일의 문자열 포매팅을 지원합니다.
```cpp
#include <iostream>
#include <format>
using namespace std;

int main() {
    cout << format("Hello, {}!", "world") << endl;
    return 0;
}
```

---

C++20은 많은 혁신적인 기능을 도입하여 프로그래머의 생산성을 높이고, 코드를 더 간결하고 강력하게 만듭니다. 이 문서를 통해 C++20의 주요 기능을 학습하고 실무에 활용할 수 있습니다.

