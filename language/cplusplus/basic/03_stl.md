# 03_stl: Standard Template Library (STL) in C++

STL(Standard Template Library)은 C++의 강력한 기능 중 하나로, 효율적이고 재사용 가능한 데이터 구조와 알고리즘을 제공합니다. STL은 **컨테이너**, **반복자**, **알고리즘**의 세 가지 주요 구성 요소로 나뉩니다.

---

## 1. STL의 구성 요소

### 1.1 컨테이너 (Containers)
컨테이너는 데이터를 저장하고 관리하는 객체입니다. STL의 컨테이너는 크게 세 가지로 분류됩니다:
1. **시퀀스 컨테이너**: 데이터를 순차적으로 저장.
   - `vector`, `deque`, `list` 등.
2. **연관 컨테이너**: 키-값 쌍을 저장하며 정렬된 상태를 유지.
   - `set`, `map`, `multiset`, `multimap`.
3. **컨테이너 어댑터**: 기존 컨테이너를 기반으로 동작.
   - `stack`, `queue`, `priority_queue`.

### 1.2 반복자 (Iterators)
반복자는 컨테이너의 원소를 순회하기 위한 객체입니다. 주요 반복자 유형:
- 입력 반복자 (Input Iterator)
- 출력 반복자 (Output Iterator)
- 순방향 반복자 (Forward Iterator)
- 양방향 반복자 (Bidirectional Iterator)
- 임의 접근 반복자 (Random Access Iterator)

### 1.3 알고리즘 (Algorithms)
STL의 알고리즘은 정렬, 검색, 변환과 같은 작업을 수행합니다. 대부분의 알고리즘은 반복자를 사용하여 작동합니다.
- 예: `sort`, `find`, `count`, `accumulate`, `copy`, `transform` 등.

---

## 2. 시퀀스 컨테이너

### 2.1 `vector`
`vector`는 동적 배열로, 크기를 동적으로 조정할 수 있습니다.

#### 주요 연산
| 연산                 | 설명                          | 시간 복잡도 |
|----------------------|-------------------------------|-------------|
| `push_back`          | 마지막에 요소 추가           | O(1) 평균   |
| `pop_back`           | 마지막 요소 제거             | O(1)        |
| `insert`             | 특정 위치에 요소 삽입        | O(n)        |
| `erase`              | 특정 위치의 요소 제거        | O(n)        |
| `resize`             | 크기 변경                    | O(n)        |

#### 예제
```cpp
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {1, 2, 3};
    v.push_back(4);
    v.pop_back();

    for (int num : v) {
        std::cout << num << " ";
    }
    return 0;
}
```

### 2.2 `deque`
`deque`(Double-ended Queue)는 양쪽 끝에서 삽입과 삭제가 가능한 컨테이너입니다.

#### 주요 연산
| 연산                 | 설명                          | 시간 복잡도 |
|----------------------|-------------------------------|-------------|
| `push_front`         | 앞쪽에 요소 추가             | O(1) 평균   |
| `push_back`          | 뒤쪽에 요소 추가             | O(1) 평균   |
| `pop_front`          | 앞쪽 요소 제거               | O(1)        |
| `pop_back`           | 뒤쪽 요소 제거               | O(1)        |

#### 예제
```cpp
#include <deque>
#include <iostream>

int main() {
    std::deque<int> dq = {1, 2, 3};
    dq.push_front(0);
    dq.push_back(4);
    dq.pop_front();

    for (int num : dq) {
        std::cout << num << " ";
    }
    return 0;
}
```

### 2.3 `list`
`list`는 이중 연결 리스트로, 삽입 및 삭제가 효율적입니다.

#### 주요 연산
| 연산                 | 설명                          | 시간 복잡도 |
|----------------------|-------------------------------|-------------|
| `push_front`         | 앞쪽에 요소 추가             | O(1)        |
| `push_back`          | 뒤쪽에 요소 추가             | O(1)        |
| `insert`             | 특정 위치에 요소 삽입        | O(1)        |
| `erase`              | 특정 위치의 요소 제거        | O(1)        |

#### 예제
```cpp
#include <list>
#include <iostream>

int main() {
    std::list<int> lst = {1, 2, 3};
    lst.push_front(0);
    lst.push_back(4);

    for (int num : lst) {
        std::cout << num << " ";
    }
    return 0;
}
```

---

## 3. 연관 컨테이너

### 3.1 `set`
`set`은 고유한 요소를 정렬된 상태로 저장하는 컨테이너입니다.

#### 주요 연산
| 연산       | 설명                        | 시간 복잡도 |
|------------|-----------------------------|-------------|
| `insert`   | 요소 삽입                   | O(log n)    |
| `erase`    | 요소 제거                   | O(log n)    |
| `find`     | 요소 검색                   | O(log n)    |

#### 예제
```cpp
#include <set>
#include <iostream>

int main() {
    std::set<int> s = {3, 1, 4};
    s.insert(2);

    for (int num : s) {
        std::cout << num << " ";
    }
    return 0;
}
```

### 3.2 `map`
`map`은 키-값 쌍을 정렬된 상태로 저장하는 컨테이너입니다.

#### 주요 연산
| 연산       | 설명                        | 시간 복잡도 |
|------------|-----------------------------|-------------|
| `insert`   | 키-값 쌍 삽입               | O(log n)    |
| `erase`    | 키로 요소 제거              | O(log n)    |
| `find`     | 키로 값 검색                | O(log n)    |

#### 예제
```cpp
#include <map>
#include <iostream>

int main() {
    std::map<std::string, int> m;
    m["Alice"] = 30;
    m["Bob"] = 25;

    for (const auto& [key, value] : m) {
        std::cout << key << ": " << value << std::endl;
    }
    return 0;
}
```

---

## 4. 컨테이너 어댑터

### 4.1 `stack`
`stack`은 LIFO(Last In, First Out) 구조를 구현합니다.

#### 주요 연산
| 연산       | 설명                        | 시간 복잡도 |
|------------|-----------------------------|-------------|
| `push`     | 요소 추가                   | O(1)        |
| `pop`      | 마지막 요소 제거            | O(1)        |
| `top`      | 마지막 요소 반환            | O(1)        |

#### 예제
```cpp
#include <stack>
#include <iostream>

int main() {
    std::stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);

    while (!st.empty()) {
        std::cout << st.top() << " ";
        st.pop();
    }
    return 0;
}
```

### 4.2 `queue`
`queue`는 FIFO(First In, First Out) 구조를 구현합니다.

#### 주요 연산
| 연산       | 설명                        | 시간 복잡도 |
|------------|-----------------------------|-------------|
| `push`     | 요소 추가                   | O(1)        |
| `pop`      | 첫 번째 요소 제거           | O(1)        |
| `front`    | 첫 번째 요소 반환           | O(1)        |

#### 예제
```cpp
#include <queue>
#include <iostream>

int main() {
    std::queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    while (!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
    return 0;
}
```

---

## 5. STL 알고리즘
STL은 다양한 알고리즘을 제공합니다. 대부분 반복자를 사용합니다.

### 주요 알고리즘 예제
#### 정렬
```cpp
#include <vector>
#include <algorithm>
#include <iostream>

int main() {
    std::vector<int> v = {3, 1, 4, 1, 5};
    std::sort(v.begin(), v.end());

    for (int num : v) {
        std::cout << num << " ";
    }
    return 0;
}
```

#### 검색
```cpp
#include <vector>
#include <algorithm>
#include <iostream>

int main() {
    std::vector<int> v = {3, 1, 4, 1, 5};
    auto it = std::find(v.begin(), v.end(), 4);

    if (it != v.end()) {
        std::cout << "Found: " << *it << std::endl;
    } else {
        std::cout << "Not Found" << std::endl;
    }
    return 0;
}
```

---

이 문서를 통해 STL의 주요 컨테이너, 반복자, 알고리즘을 이해하고 활용할 수 있습니다. 다음 단계로 STL 고급 활용법을 학습하거나, 실전 문제에서 활용해보세요.

