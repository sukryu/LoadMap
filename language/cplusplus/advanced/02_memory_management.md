# 02_memory_management: Advanced Memory Management in C++

C++는 개발자에게 메모리 관리를 직접 제어할 수 있는 강력한 도구를 제공합니다. 하지만 잘못된 메모리 관리는 오류나 성능 저하를 초래할 수 있습니다. 이 문서에서는 C++의 고급 메모리 관리 기법을 다룹니다.

---

## 1. 동적 메모리 할당 (Dynamic Memory Allocation)
동적 메모리 할당은 런타임에 메모리를 생성하고 사용할 수 있도록 합니다.

### 1.1 기본 사용법
- `new`와 `delete` 키워드를 사용하여 메모리를 할당 및 해제합니다.

#### 예제: 단일 객체
```cpp
#include <iostream>

int main() {
    int* ptr = new int(10); // 정수 메모리 할당
    std::cout << *ptr << std::endl;
    delete ptr; // 메모리 해제
    return 0;
}
```

#### 예제: 배열
```cpp
#include <iostream>

int main() {
    int* arr = new int[5]; // 정수 배열 메모리 할당
    for (int i = 0; i < 5; ++i) {
        arr[i] = i * 2;
    }

    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    delete[] arr; // 배열 메모리 해제
    return 0;
}
```

### 1.2 메모리 누수 (Memory Leak)
메모리 누수는 할당된 메모리가 적절히 해제되지 않을 때 발생합니다. 이는 프로그램의 메모리 사용량이 증가해 성능 저하를 초래할 수 있습니다.

---

## 2. 스마트 포인터 (Smart Pointers)
스마트 포인터는 C++11에서 도입된 기능으로, 메모리를 자동으로 관리하여 메모리 누수를 방지합니다.

### 2.1 `std::unique_ptr`
- 단일 소유권을 가지며, 포인터가 범위를 벗어나면 메모리를 자동으로 해제합니다.

#### 예제
```cpp
#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<int> ptr = std::make_unique<int>(42);
    std::cout << *ptr << std::endl;
    return 0;
}
```

### 2.2 `std::shared_ptr`
- 여러 포인터가 자원을 공유하며, 마지막 포인터가 범위를 벗어날 때 메모리를 해제합니다.

#### 예제
```cpp
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> ptr1 = std::make_shared<int>(42);
    std::shared_ptr<int> ptr2 = ptr1; // 공유 소유권

    std::cout << *ptr1 << ", " << *ptr2 << std::endl;
    std::cout << "Use count: " << ptr1.use_count() << std::endl;
    return 0;
}
```

### 2.3 `std::weak_ptr`
- `std::shared_ptr`의 순환 참조 문제를 해결하기 위해 사용됩니다.

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

## 3. RAII (Resource Acquisition Is Initialization)
RAII는 리소스의 수명을 객체의 수명과 연결하여 메모리 누수를 방지하는 기법입니다.

### 예제
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
        handler.write("Hello, RAII!");
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
```

---

## 4. 메모리 풀 (Memory Pool)
메모리 풀은 자주 할당 및 해제되는 작은 객체들의 메모리 관리를 최적화하는 기술입니다.

### 예제
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

int main() {
    MemoryPool pool;

    int* a = static_cast<int*>(pool.allocate(sizeof(int)));
    *a = 10;
    std::cout << *a << std::endl;

    pool.deallocate(a);
    return 0;
}
```

---

## 5. 메모리 관리 모범 사례

### 5.1 할당과 해제를 항상 쌍으로 사용
- 동적 메모리를 할당한 후에는 반드시 해제해야 합니다.

### 5.2 스마트 포인터 사용
- 수동으로 `new`와 `delete`를 사용하는 대신 스마트 포인터를 사용하십시오.

### 5.3 RAII를 활용하여 리소스 관리
- 파일, 소켓, 동적 메모리 등 모든 리소스를 RAII 패턴으로 관리하십시오.

---

C++의 고급 메모리 관리 기법은 안정적이고 효율적인 프로그램을 개발하는 데 필수적입니다. 이 문서를 통해 동적 메모리 관리, 스마트 포인터, RAII, 메모리 풀 등의 개념을 학습하고 활용할 수 있습니다.

