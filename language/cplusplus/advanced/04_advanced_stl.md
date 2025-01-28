# 04_advanced_stl: Advanced Use of the Standard Template Library (STL) in C++

STL은 효율적인 데이터 구조와 알고리즘을 제공하지만, 고급 기능을 활용하면 더욱 강력한 프로그래밍이 가능합니다. 이 문서에서는 C++ STL의 고급 활용법과 코딩 테스트에서 자주 사용되는 패턴을 다룹니다.

---

## 1. 입출력 최적화
STL 활용에서 입출력 속도는 중요한 요소입니다. 빠른 입출력을 구현하면 시간 초과를 방지할 수 있습니다.

### 1.1 기본 입출력 최적화
```cpp
#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    cout << n << endl;
    return 0;
}
```

### 1.2 Fast I/O 구현
```cpp
#include <cstdio>

inline int readInt() {
    int x = 0, c;
    while ((c = getchar()) < '0' || c > '9');
    do {
        x = x * 10 + c - '0';
    } while ((c = getchar()) >= '0' && c <= '9');
    return x;
}

int main() {
    int n = readInt();
    printf("%d\n", n);
    return 0;
}
```

---

## 2. 주요 컨테이너 활용

### 2.1 `vector`
`vector`는 동적 배열로, 가장 자주 사용되는 컨테이너 중 하나입니다.

#### 주요 연산 및 복잡도
| 연산            | 설명                 | 복잡도 |
|-----------------|----------------------|-------|
| `push_back`     | 요소 추가           | O(1) 평균 |
| `pop_back`      | 마지막 요소 제거    | O(1) |
| `insert`        | 특정 위치에 삽입    | O(n) |
| `erase`         | 특정 위치의 요소 제거 | O(n) |

#### 예제: 기본 연산
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vec = {1, 2, 3};
    vec.push_back(4);
    vec.erase(vec.begin());

    for (int n : vec) {
        cout << n << " ";
    }
    return 0;
}
```

### 2.2 `set`과 `unordered_set`
`set`은 정렬된 고유 요소를 저장하며, `unordered_set`은 해시 기반으로 저장합니다.

#### 주요 연산 및 복잡도
| 연산            | 설명                     | `set` 복잡도 | `unordered_set` 복잡도 |
|-----------------|--------------------------|--------------|------------------------|
| `insert`       | 요소 추가               | O(log n)     | O(1) 평균 |
| `erase`        | 요소 제거               | O(log n)     | O(1) 평균 |
| `find`         | 요소 검색               | O(log n)     | O(1) 평균 |

#### 예제: `set`
```cpp
#include <iostream>
#include <set>
using namespace std;

int main() {
    set<int> s;
    s.insert(3);
    s.insert(1);
    s.insert(2);

    for (int n : s) {
        cout << n << " ";
    }
    return 0;
}
```

---

## 3. STL 알고리즘

### 3.1 정렬 (`sort`와 `partial_sort`)
`sort`는 전체 정렬, `partial_sort`는 일부만 정렬합니다.

#### 예제: `sort`
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> vec = {5, 2, 8, 1, 3};
    sort(vec.begin(), vec.end());

    for (int n : vec) {
        cout << n << " ";
    }
    return 0;
}
```

#### 예제: `partial_sort`
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> vec = {9, 7, 8, 3, 2};
    partial_sort(vec.begin(), vec.begin() + 3, vec.end());

    for (int n : vec) {
        cout << n << " ";
    }
    return 0;
}
```

### 3.2 이진 탐색 (`lower_bound`와 `upper_bound`)
`lower_bound`와 `upper_bound`는 정렬된 컨테이너에서 범위를 찾는 데 유용합니다.

#### 예제
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> vec = {1, 2, 2, 3, 4};
    auto lb = lower_bound(vec.begin(), vec.end(), 2);
    auto ub = upper_bound(vec.begin(), vec.end(), 2);

    cout << "Lower bound: " << (lb - vec.begin()) << endl;
    cout << "Upper bound: " << (ub - vec.begin()) << endl;
    return 0;
}
```

---

## 4. 실전 팁

### 4.1 `emplace` 사용
`emplace`는 객체를 직접 생성하여 삽입합니다. 생성 비용을 줄이는 데 유용합니다.

#### 예제
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<pair<int, int>> vec;
    vec.emplace_back(1, 2);

    for (const auto& p : vec) {
        cout << "(" << p.first << ", " << p.second << ")" << endl;
    }
    return 0;
}
```

### 4.2 `erase-remove` 이디엄
중복 제거나 특정 값을 삭제할 때 유용합니다.

#### 예제
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> vec = {1, 2, 2, 3, 4};
    vec.erase(remove(vec.begin(), vec.end(), 2), vec.end());

    for (int n : vec) {
        cout << n << " ";
    }
    return 0;
}
```

---

C++ STL은 효율적인 데이터 관리와 알고리즘 구현을 위한 강력한 도구를 제공합니다. 위의 내용을 통해 코딩 테스트에서 자주 사용되는 STL 패턴과 최적화 기법을 익힐 수 있습니다.

