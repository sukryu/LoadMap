# 배열 (Array)

* 배열은 여러 개의 같은 타입의 데이터를 순서대로 저장하는 구조입니다. 서랍장을 생각하면 이해하기 편합니다.

<img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FcqPkgm%2FbtsJDgS66VB%2FeKSm2MhNKbPJgECDp2SkYK%2Fimg.png" width="832" height="101">

1. 기본 연산고 시간 복잡도
    * 접근 (Access) - O(1)
        - 인덱스를 통한 직접 접근
        - 한 번의 계산으로 원하는 위치 접근 가능
        - 예: 배열[3] = 시작주소 + 데이터크기(x3)

    <img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FxAtLX%2FbtsJD7U9Wt8%2FnAKNwOuLCtddlOkebYQeh1%2Fimg.png" width="824" heigth="157">

    * 수정 (Modification) - O(1)
        - 특정 인덱스의 값을 즉시 수정 가능
        - 다른 요소들에 영향을 주지 않음.

    <img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FbphKNP%2FbtsJDyFRLnJ%2FKGITXVSklzrzyEY4gc0vO0%2Fimg.png" width="844" height="160">

    * 삽입 (Insertion) - O(n)
        - 중간 삽입 시 뒤의 모든 요소를 이동시켜야 함.
        - 예: 5번째 위치에 삽입 -> 6 ~ 10번 요소를 한 칸씩 뒤로 이동

    <img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2Fr64nM%2FbtsJEUgAaFr%2FkeogcMz3YKRKHjIQeK94M0%2Fimg.png" width="819" height="294">

    * 삭제 (Deletion) - O(n)
        - 중간 삭제 시 모든 요소를 앞으로 이동
        - 예: 5번째 위치 삭제 -> 6 ~ 10번 요소 모두 한 칸씩 앞으로 이동

    <img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FbehhFB%2FbtsJD0aMDDV%2FPspBPc8uDuARgvPspNtwO1%2Fimg.png" width="846" height="303">

2. 배열의 시작 복잡도 요약표
    * 접근 (O(1))
    * 수정 (O(1))
    * 삽입 (O(n))
    * 삭제 (O(n))

3. 배열의 종류
    1. 정적 배열 (Static Array)
        * 크기가 고정된 배열
        * 메모리 사용이 효율적
        * 크기 변경 불가
        * 예: C언어의 기본 배열

    2. 동적 배열 (Dynamic Array)
        * 크기가 가변적인 배열
        * 필요에 따라 크기 조정 가능
        * 메모리 재할당 필요
        * 예: C++의 vector, Java의 ArrayList

4. 심화 학습 내용
    1. 다차원 배열
        ```java
        // 2차원 배열 예시
        int[][] matrix = new int[3][4];
        ```
        - 행렬 구현에 적합
        - 그래프 표현 가능
        - 이미지 처리에 활용

    2. 언어별 특성
        - JavaScript
        ```javascript
        let arr = [];
        arr.push(1);
        arr.pop();
        ```

        - TypeScript
        ```typescript
        let numbers: number[] = [1, 2, 3];
        let matrix: number[][] = [[1, 2], [3, 4]];
        ```

        - Go
        ```go
        var arr [5]int              // 정적 배열
        slice := make([]int, 5)     // 슬라이스(동적 배열)
        ```

        - Python
        ```python
        array = [1, 2, 3, 4, 5]

        print(array[2])

        array[2] = 10
        print(array)

        array.insert(2, 99)
        print(array)

        array.pop(2)
        print(array)
        ```

    3. 메모리 관리
        * 스택 메모리 vs 힙 메모리
        * 메모리 누수 방지
        * 가비지 컬렉션

    4. 배열의 장단점 예시
        * 장점
            * 빠른 접근 시간 O(1)
            * 간단한 구현
            * 메모리 효율성
            * 캐시 지역성

        * 단점
            * 크기 변경의 어려움(정적 배열)
            * 삽입/삭제의 비효율성
            * 메모리 낭비 가능성
            * 연속된 메모리 공간 필요

    5. 실전 활용 팁
        1. 데이터 크기가 고정적일 때 정적 배열 사용
        2. 빈번한 접근이 필요할 경우 배열 선호
        3. 삽입/삭제가 빈번한 경우 다른 자료구조 고려
        4. 캐시 효율성을 고려한 배치