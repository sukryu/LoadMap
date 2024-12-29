# 해시 탐색 (Hash Search)

* 해시 탐색의 개념:
    * 해시 탐색은 해시 테이블을 사용하여 데이터를 저장하고 검색하는 방법입니다.
    * 해시 함수를 사용하여 검색 키를 해시 테이블의 인덱스로 변환합니다.
    * 이상적인 경우 O(1)의 시간 복잡도로 검색이 가능합니다.
    * 키-값 쌍의 데이터를 다루는데 매우 효율적입니다.

* 동작 과정
    1. 키를 해시 함수에 입력하여 해시 값(인덱스)를 생성합니다.
    2. 해시 값을 테이블 크기로 모듈로 연산하여 실제 인덱스를 계산합니다.
    3. 해당 인덱스에서 데이터를 검색합니다.
    4. 충돌이 발생한 경우 충돌 해결 방법을 사용합니다.
    <img src="https://blog.kakaocdn.net/dn/qm7rv/btqSpGi1keL/DmcosF7WCgjRmGiM5cE4p1/img.gif">

* 기본 구현
    ```python
    class HashTable:
        def __init__(self, size=10):
            self.size = size
            self.table = [[] for _ in range(self.size)]
        
        def _hash(self, key):
            if isinstance(key, str):
                # 문자열 키의 경우
                return sum(ord(c) for c in key) % self.size
            # 숫자 키의 경우
            return key % self.size
        
        def insert(self, key, value):
            hash_key = self._hash(key)
            # 체이닝 방식으로 충돌 해결
            for item in self.table[hash_key]:
                if item[0] == key:
                    item[1] = value  # 키가 이미 존재하면 값 업데이트
                    return
            self.table[hash_key].append([key, value])
        
        def search(self, key):
            hash_key = self._hash(key)
            # 체인에서 키 검색
            for item in self.table[hash_key]:
                if item[0] == key:
                    return item[1]
            return None
    ```
    ```cpp
    #include <bits/stdc++.h>

    class HashTable {
    private:
        int size_;
        std::vector<std::vector<std::pair<std::string, int>>> table;

    public:
        HashTable(int size = 10) : size_(size) {
            table.resize(size_);
        }

        int _hash(const std::string& key) const {
            long long sumVal = 0;
            for (char c : key) {
                sumVal += static_cast<unsigned char>(c);
            }
            return static_cast<int>(sumVal % size_);
        }

        void insert(const std::string& key, int value) {
            int hash_key = _hash(key);

            for (auto &item : table[hash_key]) {
                if (item.first == key) {
                    item.second = value;
                    return;
                }
            }
            table[hash_key].push_back({key, value});
        }

        int search(const std::string& key) const {
            int hash_key = _hash(key);
            for (auto &item : table[hash_key]) {
                if (item.first == key) {
                    return item.second;
                }
            }
            return -1;
        }
    };
    ```

* 충돌 해결 방법
    1. 체이닝 (Chaining)
        ```python
        class ChainHashTable:
            def __init__(self, size):
                self.size = size
                self.table = [[] for _ in range(size)]
            
            def insert(self, key, value):
                hash_key = self._hash(key)
                self.table[hash_key].append([key, value])
            
            def search(self, key):
                hash_key = self._hash(key)
                for k, v in self.table[hash_key]:
                    if k == key:
                        return v
                return None
        ```

    2. 개방 주소법(Open Addressing)
        ```python
        class OpenAddressHashTable:
            def __init__(self, size):
                self.size = size
                self.table = [None] * size
            
            def _probe(self, key, i):
                # 선형 조사
                return (self._hash(key) + i) % self.size
            
            def insert(self, key, value):
                i = 0
                while i < self.size:
                    hash_key = self._probe(key, i)
                    if self.table[hash_key] is None:
                        self.table[hash_key] = [key, value]
                        return True
                    i += 1
                return False  # 테이블이 가득 참
            
            def search(self, key):
                i = 0
                while i < self.size:
                    hash_key = self._probe(key, i)
                    if self.table[hash_key] is None:
                        return None
                    if self.table[hash_key][0] == key:
                        return self.table[hash_key][1]
                    i += 1
                return None
        ```

* 시간 복잡도
    * 최선의 경우: O(1)
        - 충돌이 없는 경우
    
    * 평균의 경우: O(1)
        - 좋은 해시 함수와 적절한 테이블 크기 사용 시

    * 최악의 경우: O(n)
        - 모든 키가 같은 값을 가지는 경우

* 공간 복잡도
    - O(n): n개의 키-값 쌍을 저장하기 위한 공간 필요

* 장단점
    * 장점
        - 평균적으로 매우 빠른 검색 속도 (O(1))
        - 삽입과 삭제도 빠름
        - 키-값 쌍의 데이터를 다루기에 적합
        - 정렬되지 않은 데이터에서도 효율적

    * 단점
        - 추가 메모리 공간 필요
        - 해시 충돌 가능성
        - 데이터의 순서가 유지되지 않음
        - 적절한 해시 함수 선택이 중요

* 해시 함수 예제
    ```python
    def string_hash(key, table_size):
        """문자열 키에 대한 해시 함수"""
        hash_value = 0
        for char in key:
            hash_value = (hash_value * 31 + ord(char)) % table_size
        return hash_value

    def integer_hash(key, table_size):
        """정수 키에 대한 해시 함수"""
        return key % table_size

    def djb2_hash(key, table_size):
        """DJB2 해시 함수"""
        hash_value = 5381
        for char in str(key):
            hash_value = ((hash_value << 5) + hash_value) + ord(char)
        return hash_value % table_size
    ```

* 실제 응용 사례
    - 데이터베이스 인덱싱
    - 캐시 구현
    - 중복 검사
    - 사용자 인증 시스템
    - 블룸 필터

* 고급 기능 구현
    ```python
    class AdvancedHashTable:
        def __init__(self, size=10):
            self.size = size
            self.table = [[] for _ in range(self.size)]
            self.item_count = 0
            self.load_factor_threshold = 0.7
        
        def _resize(self):
            """테이블 크기를 두 배로 증가"""
            old_table = self.table
            self.size *= 2
            self.table = [[] for _ in range(self.size)]
            self.item_count = 0
            
            # 기존 항목들을 새 테이블에 재삽입
            for bucket in old_table:
                for key, value in bucket:
                    self.insert(key, value)
        
        def insert(self, key, value):
            if self.item_count / self.size >= self.load_factor_threshold:
                self._resize()
            
            hash_key = self._hash(key)
            for item in self.table[hash_key]:
                if item[0] == key:
                    item[1] = value
                    return
            
            self.table[hash_key].append([key, value])
            self.item_count += 1
    ```

- 해시 탐색은 현대 컴퓨터 시스템에서 가장 널리 사용되는 탐색방법 중 하나입니다. 특히 데이터베이스, 캐시 시스템,
컴파일러 등에서 핵심적인 역할을 합니다. 적절한 해시 함수와 충돌 해결 방법을 선택하면 매우 효율적인 검색 성능을 얻을 수 있습니다.

* 각 기초 탐색들의 장단점 비교표

| 알고리즘  | 시간 복잡도 (최선/평균/최악) | 공간 복잡도 | 장점 | 단점             |
|-----------|------------------------------|-------------|---------|-----------------------|
| 선형 탐색 | O(1) / O(n/2) / O(n)  | O(1) | 구현이 간단, 정렬 불필요  | 비효율적         |
| 이진 탐색 | O(1) / O(log n) / O(log n)     | O(1) | 효율적, 정렬된 데이터에서 강력    | 정렬 필요|
| 해시 탐색 | O(1) / O(1) / O(n)      | O(n)  |  매우 빠른 검색 속도   | 데이터 순서 유지 X |

* 기초 탐색 알고리즘의 사용 사례

| 알고리즘  | 사용 사례                                      |
|-----------|-----------------------------------------------|
| 선형 탐색 | 작은 데이터셋에서는 선형 탐색도 충분히 효율적. & 정렬되지 않은 작은 데이터나 드문 검색에는 선형 탐색이 적합. |
| 이진 탐색 | 정렬된 큰 데이터셋에서는 이진 탐색이 최적. & 데이터 정렬 후 이진 탐색을 사용하는 것이 효율적일 수 있음. |
| 해시 탐색 | 키-값 쌍의 데이터는 해시 탐색이 가장 효율적. |
