# 해시 테이블 (Hash Table)

1. 해시 테이블의 개념
    1. 기본 개념

        * 해시 테이블은 (Key, Value) 쌍으로 데이터를 저장하는 자료구조로, 빠른 데이터 검색이 가능하다.
        
        * 해시 테이블이 빠른 검색속도를 제공하는 이유는 내부적으로 배열(버킷)을 사용하여 데이터를 저장하기 때문입니다. 해시 테이블은 각각의 Key값에 해시함수를 적용해
            배열의 고유한 index를 생성하고, 이 index를 활용해 값을 저장하거나 검색하게 된다. 여기서 실제 값이 저장되는 장소를 버킷 또는 슬롯이라고 한다.

        * 해시 테이블의 평균 시간복잡도는 O(1)이다.

        * 해시 테이블 구조
            <img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2Fb1zOw1%2FbtqL6HAW7jy%2FjpBA5pPkQFnfiZcPLakg00%2Fimg.png">
            * Key, Hash Function, Hash, Value, 저장소(Bucket, Slot)로 구성
            * Key
                * 고유한 값
                * 저장 공간의 효율성을 위해 Hash Function에 입력하여 Hash로 변경 후 저장
                * Key는 길이가 다양하기 때문에 그대로 저장하면 다양한 길이만큼 저장소 구성이 필요
            * Hash Function
                * Key를 Hash로 바꿔주는 역할
                * 해시 충돌(서로 다른 Key가 같은 Hash가 되는 경우)이 발생할 확률을 최대한 줄이는 함수를 만드는 것이 중요
            * Hash
                * Hash Function의 결과
                * 저장소에서 Value와 매칭되어 저장
            * Value
                * 저장소에 최종적으로 저장되는 값
                * 키와 매칭되어 저장, 삭제, 검색, 접근 가능

        * 해시 테이블 동작 과정
            1. Key -> Hash Function -> Hash Function 결과 = Hash
            2. Hash를 배열의 Index로 사용
            3. 해당 Index에 Value 저장
            * HashTable 크기가 10이라면 A라는 Key의 Value를 찾을 때 hashFunction("A") % 10 연산을 통해 인덱스 값 계산하여 Value 조회

        * Hash 충돌
            * 서로 다른 Key가 Hash Function에서 중복 Hash로 나오는 경우
            * 충돌이 많아질수록 탐색의 시간 복잡도가 O(1)에서 O(n)으로 증가

    2. 해시 함수
        * 해시 함수는 키를 고유한 인덱스로 변환하는 함수입니다.

        * 주요 해시 함수:
            * Division Method: `index = key % table_size`
                * 나눗셈을 이용하는 방법으로 입력값을 테이블의 크기로 나누어 계산한다. (주소 = 입력값 % 테이블의 크기) 테이블의 크기를 소수로 정하고 2의 제곱수와 먼 값을 사용해야 효과가 좋다고 알려져있다.
            * Digit Folding: ASCII 코드 변환 후 합산
                * 각 Key의 문자열을 ASCII 코드로 바꾸고 값을 합한 데이터를 테이블 내의 주소로 사용하는 방법이다.
            * Multiplication Method: `h(k) = (kA mod 1) x m`
                * 숫자로 된 Key값 K와 0과 1사이의 실수 A, 보통 2의 제곱수인 m을 사용하여 위와 같은 계산을 한다.
            * Universal Hashing: 다수의 해시함수 중 무작위 선택
                * 다수의 해시함수를 만들어 집합 H에 넣어두고, 무작위로 해시함수를 선택해 해시값을 만드는 기법이다.

    3. 해시 (Hash)값이 충돌하는 경우
        * 간혹 해시 테이블이 충돌하는 경우가 있는데 이 경우 `분리 연결법(Separate Chaining)과 개방 주소법(Open Addressing)` 크게 2가지로 해결하고 있다.

        1. 분리 연결법(Separate Chaining)
            <img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FbTF67c%2FbtqL7xx3OGw%2FDM8KEKU5x7dx6Nks4JR7K1%2Fimg.png">

            - Separate Chaining이란 동일한 버킷의 데이터에 대해 자료구조를 활용해 추가 메모리를 사용하여 다음 데이터의 주소를 저장하는 것이다.
            위의 그림과 같이 동일한 버킷으로 접근을 한다면 데이터들을 연결해서 관리해주고 있다. 실제로 Java8의 Hash 테이블은 Self-Balancing Binary Search Tree 자료구조를 사용해
            Chaining 방식을 구현하였다. 이러한 Chaining방식은 해시 테이블의 확장이 필요 없고 구현이 간단하며, 손쉽게 삭제할 수 있다는 장점이 있지만 데이터의 수가 많아지면 버킷에 Chaining되는
            데이터가 많아지며 그에 따라 캐시 효율성이 감소한다.

        2. 개방 주소법(Open Addressing)
            * Open Addressing이란 추가적인 메모리를 사용하는 Chaining 방식과 다르게 비어있는 해시 테이블의 공간을 활용하는 방법이다.
            Open Addressing을 구현하기 우한 대표적인 방법으로는 3가지 방식이 존재한다.

            1. Linear Probing: 현재의 버킷 index로부터 고정폭 만큼씩 이동하여 차례대로 검색해 비어있는 버킷에 데이터를 저장한다.

            2. Quadratic Probing: 해시의 저장순서 폭을 제곱으로 저장하는 방식이다. 예를 들어 처음 충돌이 발생한 경우에는 1만큼 이동하고 그 다음 계속
            충돌이 발생하면 2^2, 3^2 칸씩 옮기는 방식이다.

            3. Double Hashing Probing: 해시된 값을 한 번 더 해싱하여 해시의 규칙성을 없애버리는 방식이다. 해시된 값을 한 번 더 해싱하여 새로운 주소를 할당하기 때문에
            다른 방법들보다 많은 연산을 하게 된다.

            <img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FWR1fv%2FbtqL5APCcSa%2FBZN6wvxUXzJBEiOfOMLfR0%2Fimg.png">

            * Open Addressing에서 데이터를 삭제하면 삭제된 공간은 Dummy Space로 활용되는데, 그렇기 때문에 `Hash Table을 재정리 해주는 작업`이 필요하다고 한다.

        3. Resizing
            * 저장 공간이 일정 수준 채워지면 Separate Chaining의 경우 성능 향상을 위해, Open Addressing의 경우 배열 크기 확장을 위해 Resizing
            * 보통 두 배로 확장함
            * 확장 임계점은 현재 데이터 개수가 Hash Bucket 개수의 75%가 될 때

    4. 해시 테이블의 장점
         * 적은 리소스로 많은 데이터를 효율적으로 관리 가능
            * ex. HDD. Cloud에 있는 많은 데이터를 Hash로 매핑하여 작은 크기의 시 메모리로 프로세스 관리 가능

        * 배열의 인덱스를 사용하기 때문에 빠른 검색, 삽입, 삭제 (O(1))
            * HashTable의 경우 인덱스는 데이터의 고유 위치이기 때문에 삽입 삭제 시 다른 데이터를 이동할 필요가 없어 삽입, 삭제도 빠른 속도 가능

        * Key와 Hash에 연관성이 없어 보안 유리
        
        * 데이터 캐싱에 많이 사용
            * get, put 기능에 캐시 로직 추가 시 자주 hit하는 데이터 바로 검색 가능\

        * 중복 제거 유용

    5. 해시 테이블의 단점
        * HashTable 단점
        * 충돌 발생 가능성
        * 공간 복잡도 증가
        * 순서 무시
        * 해시 함수에 의존

    6. HashTable vs HashMap
        * Key-Value 구조 및 Key에 대한 Hash로 Value 관리하는 것은 동일
        * HashTable
            * 동기
            * Key-Value 값으로 null 미허용 (Key가 hashcode(), equals()를 사용하기 때문)
            * 보조 Hash Function과 separating Chaining을 사용해서 비교적 충돌 덜 발생 (Key의 Hash 변형)
        * HashMap
            * 비동기 (멀티 스레드 환경에서 주의)
            * Key-Value 값으로 null 허용

    7. HashTable 성능

    | |평균|최악|
    |----|----|----|
    |탐색|O(1)|O(N)|
    |삽입|O(1)|O(N)|
    |삭제|O(1)|O(N)|