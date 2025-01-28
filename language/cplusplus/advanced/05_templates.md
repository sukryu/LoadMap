# 05_templates: Advanced Template Programming in C++

템플릿은 C++의 강력한 기능 중 하나로, 제네릭 프로그래밍을 가능하게 합니다. 템플릿을 활용하면 타입에 독립적인 코드를 작성할 수 있으며, 컴파일 타임에 성능 최적화를 이룰 수 있습니다.

---

## 1. 함수 템플릿
함수 템플릿은 여러 타입에 대해 동작하는 함수를 정의할 수 있도록 합니다.

### 1.1 기본 문법
```cpp
template <typename T>
T add(T a, T b) {
    return a + b;
}
```

### 1.2 예제: 함수 템플릿 사용
```cpp
#include <iostream>
using namespace std;

template <typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    cout << add(3, 5) << endl;       // int 타입
    cout << add(3.5, 2.5) << endl;   // double 타입
    return 0;
}
```

---

## 2. 클래스 템플릿
클래스 템플릿은 타입에 독립적인 클래스를 정의하는 데 사용됩니다.

### 2.1 기본 문법
```cpp
template <typename T>
class Box {
private:
    T value;

public:
    Box(T val) : value(val) {}

    T getValue() const {
        return value;
    }
};
```

### 2.2 예제: 클래스 템플릿 사용
```cpp
#include <iostream>
using namespace std;

template <typename T>
class Box {
private:
    T value;

public:
    Box(T val) : value(val) {}

    T getValue() const {
        return value;
    }
};

int main() {
    Box<int> intBox(10);
    Box<string> strBox("Hello");

    cout << intBox.getValue() << endl;   // 10 출력
    cout << strBox.getValue() << endl;  // Hello 출력
    return 0;
}
```

---

## 3. 템플릿 특수화
템플릿 특수화는 특정 타입에 대해 별도의 구현을 제공하는 방법입니다.

### 3.1 기본 문법
```cpp
template <typename T>
class Box {
    // 기본 템플릿 구현
};

template <>
class Box<int> {
    // int 타입에 대한 특수화 구현
};
```

### 3.2 예제: 템플릿 특수화
```cpp
#include <iostream>
using namespace std;

template <typename T>
class Box {
private:
    T value;

public:
    Box(T val) : value(val) {}

    void display() const {
        cout << "Value: " << value << endl;
    }
};

template <>
class Box<int> {
private:
    int value;

public:
    Box(int val) : value(val) {}

    void display() const {
        cout << "Integer Value: " << value << endl;
    }
};

int main() {
    Box<string> strBox("Hello");
    Box<int> intBox(42);

    strBox.display();   // Value: Hello 출력
    intBox.display();   // Integer Value: 42 출력
    return 0;
}
```

---

## 4. 가변 인자 템플릿 (Variadic Templates)
C++11부터 지원하는 가변 인자 템플릿은 임의의 개수의 템플릿 인자를 처리할 수 있습니다.

### 4.1 기본 문법
```cpp
template <typename... Args>
void print(Args... args) {
    // 인자 처리
}
```

### 4.2 예제: 가변 인자 템플릿
```cpp
#include <iostream>
using namespace std;

template <typename... Args>
void print(Args... args) {
    (cout << ... << args) << endl;
}

int main() {
    print(1, 2, 3, "Hello", 4.5); // 1 2 3 Hello 4.5 출력
    return 0;
}
```

---

## 5. 템플릿 메타 프로그래밍 (Template Metaprogramming)
템플릿 메타 프로그래밍은 컴파일 타임에 계산을 수행하는 기법입니다.

### 5.1 예제: 팩토리얼 계산
```cpp
#include <iostream>
using namespace std;

template <int N>
struct Factorial {
    static const int value = N * Factorial<N - 1>::value;
};

template <>
struct Factorial<0> {
    static const int value = 1;
};

int main() {
    cout << "Factorial of 5: " << Factorial<5>::value << endl; // 120 출력
    return 0;
}
```

---

## 6. SFINAE와 `std::enable_if`
SFINAE(Substitution Failure Is Not An Error)는 템플릿 인스턴스화 실패를 허용하여 다른 오버로드를 시도할 수 있게 합니다. 이를 활용하여 조건부 템플릿을 작성할 수 있습니다.

### 6.1 예제: `std::enable_if` 사용
```cpp
#include <iostream>
#include <type_traits>
using namespace std;

template <typename T>
typename enable_if<is_integral<T>::value, T>::type add(T a, T b) {
    return a + b;
}

int main() {
    cout << add(3, 5) << endl; // 8 출력
    // cout << add(3.5, 5.5) << endl; // 컴파일 에러
    return 0;
}
```

---

## 7. Concepts (C++20)
C++20에서 도입된 Concepts는 템플릿에 대한 제약 조건을 정의할 수 있는 기능입니다.

### 7.1 예제: Concepts 사용
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

template <Numeric T>
T add(T a, T b) {
    return a + b;
}

int main() {
    cout << add(3, 5) << endl;       // 8 출력
    cout << add(3.5, 2.5) << endl;   // 6.0 출력
    return 0;
}
```

---

템플릿은 C++의 핵심 기능으로, 제네릭 프로그래밍과 성능 최적화에 중요한 역할을 합니다. 이 문서를 통해 템플릿의 기초부터 고급 기능까지 학습하고 실무에 활용할 수 있습니다.

