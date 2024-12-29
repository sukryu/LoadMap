# 직접 재귀 (Direct Recursion)

* 직접 재귀의 개념
    * 함수가 자기 자신을 직접적으로 호출하는 재귀 방식입니다.
    * 가장 기본적이고 단순한 형태의 재귀입니다.
    * 중간 매개 함수 없이 바로 자신을 호출합니다.

* 구조와 특징
    * 함수 내부에서 동일한 함수를 직접 호출
    * 종료 조건과 재귀 호출로 구성
    * 스택 프레임이 직접적으로 쌓임

* 기본 구현 예제
    ```python
    def factorial(n):
        # 종료 조건
        if n <= 1:
            return 1
        # 직접 재귀 호출
        return n * factorial(n - 1)

    def countdown(n):
        # 종료 조건
        if n <= 0:
            print("발사!")
            return
        print(n)
        # 직접 재귀 호출
        countdown(n - 1)
    ```

* 활용 예제
    1. 배열의 합 계산
        ```python
        def array_sum(arr):
            if not arr:  # 빈 배열 체크
                return 0
            return arr[0] + array_sum(arr[1:])
        ```

    2. 문자열 뒤집기
        ```python
        def reverse_string(s):
            if len(s) <= 1:
                return s
            return reverse_string(s[1:]) + s[0]
        ```

    3. 거듭제곱 계산
        ```python
        def power(base, exponent):
            if exponent == 0:
                return 1
            return base * power(base, exponent - 1)
        ```

* 시간 복잡도와 공간 복잡도
    * 시간 복잡도: 문제에 따라 다름
        - 팩토리얼: O(n)
        - 피보나치: O(2^n)

    * 공간 복잡도: 재귀 깊이에 비례
        - 대부분 O(n)이상의 스택 공간 필요

* 최적화 기법
    ```python
    # 메모이제이션을 활용한 최적화
    def fibonacci_memo(n, memo=None):
        if memo is None:
            memo = {}
        if n in memo:
            return memo[n]
        if n <= 1:
            return n
        
        memo[n] = fibonacci_memo(n-1, memo) + fibonacci_memo(n-2, memo)
        return memo[n]

    # 파라미터 최적화
    def optimized_array_sum(arr, start=0):
        if start >= len(arr):
            return 0
        return arr[start] + optimized_array_sum(arr, start + 1)
    ```

* 장단점
    * 장점
        - 구현이 간단하고 직관적
        - 코드 가독성이 좋음
        - 문제를 자연스럽게 분할 가능

    * 단점
        - 메모리 사용량이 많음
        - 스택 오버플로우 위험
        - 깊은 재귀에서 성능 저하

* 실제 사용 예시
    ```python
    # 디렉토리 탐색
    def list_files(path):
        if os.path.isfile(path):
            return [path]
        
        files = []
        for item in os.listdir(path):
            full_path = os.path.join(path, item)
            files.extend(list_files(full_path))
        return files

    # 트리 순회
    class TreeNode:
        def __init__(self, value):
            self.value = value
            self.left = None
            self.right = None

    def preorder(self):
        print(self.value, end=' ')
        if self.left:
            self.left.preorder()
        if self.right:
            self.right.preorder()
    ```

- 직접 재귀는 가장 기본적인 재귀 형태로, 적절한 종료 조건과 함계 사용하면 많은 문제를 효율적으로 해결할 수 있습니다.
하지만 깊은 재귀나 큰 입력값에 대해서는 스택 오버플로우와 성능 저하에 주의해야 합니다.