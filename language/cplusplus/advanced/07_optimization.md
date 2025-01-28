# 07_optimization: Advanced Optimization Techniques in C++

C++는 고성능 프로그래밍을 위해 설계된 언어로, 성능 최적화에 유리한 다양한 기능과 기법을 제공합니다. 이 문서에서는 C++에서 자주 사용되는 최적화 기법과 실전에서 활용 가능한 팁을 다룹니다.

---

## 1. 컴파일러 최적화 옵션
컴파일러의 최적화 옵션을 활용하면 코드의 실행 속도를 크게 향상시킬 수 있습니다.

### 1.1 GCC/Clang 최적화 옵션
- `-O1`: 기본 최적화.
- `-O2`: 대부분의 최적화 적용.
- `-O3`: 최대 수준의 최적화.
- `-Ofast`: 엄격한 표준 준수 요구를 무시하고 성능 극대화.
- `-march=native`: 현재 CPU의 고급 명령어 세트를 사용.

#### 예제
```bash
g++ -O3 -march=native program.cpp -o program
```

---

## 2. 메모리 관리 최적화

### 2.1 메모리 풀 (Memory Pool)
메모리 풀은 자주 생성/삭제되는 객체들의 메모리 관리를 최적화합니다.

#### 예제
```cpp
#include <iostream>
#include <vector>

class MemoryPool {
private:
    std::vector<void*> pool;

public:
    void* allocate(size_t size) {
        if (pool.empty()) {
            return operator new(size);
        } else {
            void* ptr = pool.back();
            pool.pop_back();
            return ptr;
        }
    }

    void deallocate(void* ptr) {
        pool.push_back(ptr);
    }

    ~MemoryPool() {
        for (void* ptr : pool) {
            operator delete(ptr);
        }
    }
};
```

### 2.2 캐시 친화적 데이터 구조
데이터를 연속된 메모리에 저장하면 캐시 효율성을 높일 수 있습니다.

#### 예제: 배열 기반 접근
```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> data(1000000, 1);
    long long sum = 0;

    for (size_t i = 0; i < data.size(); ++i) {
        sum += data[i];
    }

    std::cout << "Sum: " << sum << std::endl;
    return 0;
}
```

---

## 3. 함수 호출 최적화

### 3.1 인라인 함수
인라인 함수는 호출 오버헤드를 제거하여 성능을 향상시킵니다.

#### 예제
```cpp
#include <iostream>

inline int add(int a, int b) {
    return a + b;
}

int main() {
    std::cout << add(3, 5) << std::endl;
    return 0;
}
```

### 3.2 `constexpr` 함수
`constexpr` 함수는 컴파일 타임에 계산을 수행하여 런타임 오버헤드를 줄입니다.

#### 예제
```cpp
#include <iostream>

constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

int main() {
    constexpr int result = factorial(5);
    std::cout << "Factorial: " << result << std::endl;
    return 0;
}
```

---

## 4. 데이터 구조와 알고리즘 최적화

### 4.1 적절한 데이터 구조 선택
- **랜덤 접근 빈번**: `std::vector`.
- **양쪽 끝 삽입/삭제 빈번**: `std::deque`.
- **정렬된 상태 유지 필요**: `std::set`, `std::map`.
- **빠른 검색 필요**: `std::unordered_set`, `std::unordered_map`.

#### 예제: `std::unordered_map` 활용
```cpp
#include <iostream>
#include <unordered_map>

int main() {
    std::unordered_map<std::string, int> umap;
    umap["apple"] = 5;
    umap["banana"] = 3;

    std::cout << "Apple count: " << umap["apple"] << std::endl;
    return 0;
}
```

### 4.2 알고리즘 최적화
- 정렬이 필요한 경우, `std::sort` 대신 `std::partial_sort` 사용.
- 중복 제거 시 `std::unique`와 `erase` 조합.

#### 예제: 중복 제거
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 2, 3, 4, 4, 5};
    auto it = std::unique(vec.begin(), vec.end());
    vec.erase(it, vec.end());

    for (int n : vec) {
        std::cout << n << " ";
    }
    return 0;
}
```

---

## 5. 병렬 프로그래밍 최적화

### 5.1 OpenMP
OpenMP는 멀티코어 프로세서를 활용한 병렬 처리를 지원합니다.

#### 예제
```cpp
#include <iostream>
#include <omp.h>

int main() {
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < 1000000; ++i) {
        sum += i;
    }

    std::cout << "Sum: " << sum << std::endl;
    return 0;
}
```

### 5.2 C++17 병렬 STL
C++17부터는 STL 알고리즘에 병렬 실행 정책을 사용할 수 있습니다.

#### 예제
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>

int main() {
    std::vector<int> vec(1000000, 1);
    int sum = std::reduce(std::execution::par, vec.begin(), vec.end());

    std::cout << "Sum: " << sum << std::endl;
    return 0;
}
```

---

## 6. 디버깅과 프로파일링

### 6.1 디버깅
- **GDB**: GNU 디버거로, 런타임 버그를 추적.
- **Valgrind**: 메모리 누수와 잘못된 메모리 접근 탐지.

### 6.2 프로파일링
- **gprof**: 함수별 실행 시간을 분석.
- **perf**: 시스템 전체의 성능 분석.

#### 프로파일링 예제
```bash
g++ -pg program.cpp -o program
./program
gprof program gmon.out > analysis.txt
```

---

C++ 최적화는 성능을 극대화하기 위한 핵심 기술입니다. 위의 기법들을 통해 프로그램의 속도와 효율성을 향상시킬 수 있습니다.

