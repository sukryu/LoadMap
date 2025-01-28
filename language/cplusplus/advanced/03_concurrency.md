# 03_concurrency: Advanced Concurrency in C++

C++는 멀티스레드 프로그래밍을 지원하기 위해 표준 라이브러리에 동시성(concurrency) 관련 도구들을 제공합니다. 이 문서에서는 동시성 프로그래밍의 주요 구성 요소와 활용 방법을 다룹니다.

---

## 1. C++의 동시성 지원
C++11부터 표준 라이브러리는 멀티스레드와 동시성 프로그래밍을 지원하기 위한 다양한 기능을 제공합니다. 주요 구성 요소는 다음과 같습니다:

- **스레드**: `std::thread`
- **뮤텍스**: `std::mutex`, `std::lock_guard`
- **조건 변수**: `std::condition_variable`
- **퓨처와 프로미스**: `std::future`, `std::promise`
- **원자적 연산**: `std::atomic`

---

## 2. `std::thread`: 스레드 생성 및 관리
`std::thread`는 멀티스레드 프로그램을 작성할 때 사용하는 기본적인 클래스입니다.

### 2.1 스레드 생성
스레드는 함수, 람다 표현식, 또는 함수 객체로 생성할 수 있습니다.

#### 예제
```cpp
#include <iostream>
#include <thread>

void printMessage() {
    std::cout << "Hello from thread!" << std::endl;
}

int main() {
    std::thread t(printMessage); // 스레드 생성
    t.join(); // 스레드 종료 대기
    return 0;
}
```

### 2.2 스레드 분리
- `join()`: 스레드가 완료될 때까지 대기합니다.
- `detach()`: 스레드를 백그라운드에서 실행되도록 분리합니다.

#### 예제
```cpp
#include <iostream>
#include <thread>
#include <chrono>

void printMessage() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Hello from detached thread!" << std::endl;
}

int main() {
    std::thread t(printMessage);
    t.detach(); // 백그라운드 실행

    std::cout << "Main thread continues..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 0;
}
```

---

## 3. `std::mutex`와 `std::lock_guard`
뮤텍스는 공유 자원의 동기화를 위해 사용됩니다. `std::lock_guard`를 사용하면 뮤텍스를 자동으로 관리할 수 있습니다.

### 3.1 기본 뮤텍스 사용
#### 예제
```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void printMessage(const std::string& message) {
    mtx.lock();
    std::cout << message << std::endl;
    mtx.unlock();
}

int main() {
    std::thread t1(printMessage, "Hello from thread 1");
    std::thread t2(printMessage, "Hello from thread 2");

    t1.join();
    t2.join();
    return 0;
}
```

### 3.2 `std::lock_guard` 사용
`std::lock_guard`는 뮤텍스를 자동으로 잠그고, 범위를 벗어나면 잠금을 해제합니다.

#### 예제
```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void printMessage(const std::string& message) {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << message << std::endl;
}

int main() {
    std::thread t1(printMessage, "Hello from thread 1");
    std::thread t2(printMessage, "Hello from thread 2");

    t1.join();
    t2.join();
    return 0;
}
```

---

## 4. `std::condition_variable`
조건 변수는 스레드 간 통신을 위해 사용됩니다. 하나의 스레드가 조건을 기다리고, 다른 스레드가 조건을 만족시키면 신호를 보냅니다.

### 예제
```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void workerThread() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return ready; }); // 조건 기다리기
    std::cout << "Worker thread is running!" << std::endl;
}

int main() {
    std::thread t(workerThread);

    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
    }
    cv.notify_one(); // 조건 신호 보내기

    t.join();
    return 0;
}
```

---

## 5. `std::future`와 `std::promise`
퓨처와 프로미스는 스레드 간 데이터를 주고받는 데 사용됩니다.

### 예제
```cpp
#include <iostream>
#include <thread>
#include <future>

void calculateSquare(std::promise<int>&& promise, int value) {
    promise.set_value(value * value);
}

int main() {
    std::promise<int> promise;
    std::future<int> future = promise.get_future();

    std::thread t(calculateSquare, std::move(promise), 4);

    std::cout << "Square: " << future.get() << std::endl;
    t.join();
    return 0;
}
```

---

## 6. `std::atomic`
`std::atomic`은 원자적 연산을 제공하여 락 없이도 안전한 동시성 프로그래밍을 가능하게 합니다.

### 예제
```cpp
#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> counter(0);

void increment() {
    for (int i = 0; i < 1000; ++i) {
        ++counter;
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Counter: " << counter << std::endl;
    return 0;
}
```

---

## 7. 병렬 알고리즘 (C++17)
C++17부터 병렬 실행 정책을 지원하는 알고리즘이 도입되었습니다. 이를 통해 더 효율적인 데이터 처리가 가능합니다.

### 예제
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>

int main() {
    std::vector<int> vec = {1, 3, 5, 7, 9};
    std::for_each(std::execution::par, vec.begin(), vec.end(), [](int& n) {
        n *= 2;
    });

    for (int n : vec) {
        std::cout << n << " ";
    }
    return 0;
}
```

---

C++의 동시성 도구는 병렬 프로그래밍의 복잡성을 줄이고 효율성을 극대화하는 데 도움을 줍니다. 이 문서를 통해 스레드 관리, 동기화, 조건 변수, 원자적 연산 등을 학습하고 적용할 수 있습니다.

