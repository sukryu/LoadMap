# 일반 재귀 (Recursion)

* 재귀의 개념
    * 재귀는 함수가 자기 자신을 호출하여 문제를 해결하는 프로그래밍 기법입니다.
    * 큰 문제를 같은 형태의 작은 문제로 나누어 해결하는 방식입니다.
    * 재귀 함수는 항상 종료 조건(base case)을 가져야 합니다.
    * 대부분의 재귀는 반복문으로 변환이 가능합니다.

* 재귀의 필수 요소
    1. 종료 조건(base case)
        - 재귀 호출이 종료되는 조건
        - 더 이상의 재귀 호출이 필요 없는 가장 단순한 경우

    2. 재귀 단계 (Recursive Step)
        - 문제를 더 작은 부분 문제로 나누는 과정
        - 자기 자신을 호출하여 문제를 해결

* 기본 구현 예제
    ```python
    # 팩토리얼 계산
    def factorial(n):
        # 종료 조건
        if n <= 1:
            return 1
        # 재귀 단계
        return n * factorial(n - 1)

    # 피보나치 수열
    def fibonacci(n):
        # 종료 조건
        if n <= 1:
            return n
        # 재귀 단계
        return fibonacci(n - 1) + fibonacci(n - 2)
    ```

* 시간 복잡도
    * 문제와 구현 방식에 따라 다름
    * 예시:
        - 팩토리얼: O(n)
        - 피보나치(단순 재귀): O(2^n)
        - 이진 검색: O(log n)

* 공간 복잡도
    * 재귀 깊이만큼의 스택 공간 필요
    * 각 재귀 호출마다 지역 변수와 매개변수를 위한 메모리 필요
    * 대부분의 경우 O(n) 또는 그 이상

* 장단점
    * 장점
        - 코드가 직관적이고 이해하기 쉬움
        - 복잡한 문제를 단순한 부분으로 나누어 해결 가능
        - 수학적 귀납법과 유사한 문제 해결 방식
        - 트리나 그래프 같은 재귀적 자료구조를 다루기 적합

    * 단점
        - 메모리 사용량이 많음 (스택 오버플로우 위험)
        - 반복문에 비해 성능이 떨어질 수 있음.
        - 잘못 구현하면 무한 재귀에 빠질 수 있음.
        - 디버깅이 어려울 수 있음.

* 주요 응용 예제:
    1. 하노이 탑:
        ```python
        def hanoi(n, source, auxiliary, target):
            if n == 1:
                print(f"원반 1을 {source}에서 {target}으로 이동")
                return
            
            hanoi(n - 1, source, target, auxiliary)
            print(f"원반 {n}을 {source}에서 {target}으로 이동")
            hanoi(n - 1, auxiliary, source, target)
        ```

    2. 디렉토리 탐색:
        ```python
        import os

        def explore_directory(path, depth=0):
            indent = "  " * depth
            print(f"{indent}{os.path.basename(path)}/")
            
            try:
                for item in os.listdir(path):
                    item_path = os.path.join(path, item)
                    if os.path.isdir(item_path):
                        explore_directory(item_path, depth + 1)
                    else:
                        print(f"{indent}  {item}")
            except PermissionError:
                print(f"{indent}  Permission denied")
        ```

    3. 트리 순회:
        ```python
        class TreeNode:
        def __init__(self, value):
            self.value = value
            self.left = None
            self.right = None

        def inorder_traversal(node):
            if node:
                inorder_traversal(node.left)
                print(node.value, end=' ')
                inorder_traversal(node.right)
        ```

* 재귀를 반복문으로 변환
    ```python
    # 재귀적 팩토리얼
    def recursive_factorial(n):
        if n <= 1:
            return 1
        return n * recursive_factorial(n - 1)

    # 반복문으로 변환한 팩토리얼
    def iterative_factorial(n):
        result = 1
        for i in range(1, n + 1):
            result *= i
        return result
    ```

* 메모이제이션을 활용한 최적화
    ```python
    def fibonacci_memo(n, memo=None):
        if memo is None:
            memo = {}
        
        if n in memo:
            return memo[n]
        
        if n <= 1:
            return n
            
        memo[n] = fibonacci_memo(n - 1, memo) + fibonacci_memo(n - 2, memo)
        return memo[n]
    ```

* 꼬리 재귀 최적화
    ```python
    def tail_factorial(n, accumulator=1):
        if n <= 1:
            return accumulator
        return tail_factorial(n - 1, n * accumulator)
    ```

- 재귀는 프로그래밍의 강력한 도구이지만, 신중하게 사용해야 합니다. 특히 깊이가 깊어질 수 있는 경우에는 스택 오버플로우를 피하기 위해
반복문이나 꼬리 재귀를 고려해야 합니다. 또한, 성능이 중요한 경우에는 메모이제이션과 같은 최적화 기법을 활용하는 것이 좋습니다.

- 실제 사용할 때는 문제의 특성과 제약 조건을 고려하여 재귀와 반복문 중 적절한 방식을 선택해야 합니다. 특히 트리나 그래프와 같은 계층적
구조를 다룰 때는 재귀가 매우 유용할 수 있습니다.