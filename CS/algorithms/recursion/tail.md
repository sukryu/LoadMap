# 꼬리 재귀 (Tail Recursion)

* 꼬리 재귀의 개념:
    * 꼬리 재귀는 재귀 호출이 함수의 마지막 연산으로 수행되는 형태의 재귀입니다.
    * 재귀 호출 이후에 추가적인 계산이 필요 없는 재귀 방식입니다.
    * 컴파일러가 최적화를 통해 반복문처럼 처리할 수 있어 일반 재귀보다 효율적입니다.
    * 스택 오버플로우의 위험이 적습니다.

* 일반 재귀와 꼬리 재귀의 차이
    ```python
    # 일반 재귀 (팩토리얼)
    def factorial(n):
        if n <= 1:
            return 1
        return n * factorial(n - 1)  # 재귀 호출 후 곱셈 연산 필요

    # 꼬리 재귀 (팩토리얼)
    def tail_factorial(n, accumulator=1):
        if n <= 1:
            return accumulator
        return tail_factorial(n - 1, n * accumulator)  # 재귀 호출이 마지막 연산
    ```

* 주요 특징
    1. 메모리 사용
        - 일반 재귀: 각 호출마다 스택 프레임 유지 필요
        - 꼬리 재귀: 컴파일러 최적화로 단일 스택 프레임만 사용 가능

    2. 성능
        - 일반 재귀보다 효율적
        - 반복문과 비슷한 성능 가능
        - 컴파일러의 최적화 지원 필요

* 구현 예제
    1. 피보나치 수열
        ```python
        # 꼬리 재귀로 구현한 피보나치
        def tail_fibonacci(n, curr=0, next=1):
            if n == 0:
                return curr
            return tail_fibonacci(n - 1, next, curr + next)
        ```

    2. 리스트 합계 계산
        ```python
        # 일반 재귀
        def sum_list(arr):
            if not arr:
                return 0
            return arr[0] + sum_list(arr[1:])

        # 꼬리 재귀
        def tail_sum_list(arr, acc=0):
            if not arr:
                return acc
            return tail_sum_list(arr[1:], acc + arr[0])
        ```

    3. 리스트 뒤집기
        ```python
        def tail_reverse_list(lst, acc=None):
            if acc is None:
                acc = []
            if not lst:
                return acc
            return tail_reverse_list(lst[1:], [lst[0]] + acc)
        ```

* 장단점
    * 장점
        - 메모리 효율성 향상
        - 스택 오버플로우 위험 감소
        - 컴파일러 최적화 가능
        - 실행 속도 향상 가능

    * 단점
        - 코드가 덜 직관적일 수 있음.
        - 누적 값(accumulator)관리 필요.
        - 모든 언어/컴파일러가 최적화를 지원하지 않음.
        - 일부 문제는 꼬리 재귀로 변환이 어려움.

* 실제 활용 예제
    1. 트리 순회
        ```python
        class TreeNode:
            def __init__(self, value):
                self.value = value
                self.left = None
                self.right = None

        def tail_inorder_traversal(node, acc=None):
            if acc is None:
                acc = []
                
            if not node:
                return acc
                
            # 왼쪽 서브트리 순회
            acc = tail_inorder_traversal(node.left, acc)
            # 현재 노드 처리
            acc.append(node.value)
            # 오른쪽 서브트리 순회
            return tail_inorder_traversal(node.right, acc)
        ```

    2. GCD(최대공약수) 계산
        ```python
        def tail_gcd(a, b):
            if b == 0:
                return a
            return tail_gcd(b, a % b)
        ```

* 꼬리 재귀로의 변환 가이드
    ```python
    # 일반적인 변환 패턴

    # 1. 누적 인자 추가
    def regular_sum(n):
        if n <= 1:
            return n
        return n + regular_sum(n - 1)

    def tail_sum(n, acc=0):
        if n <= 1:
            return n + acc
        return tail_sum(n - 1, acc + n)

    # 2. 보조 함수 사용
    def quick_sort(arr):
        def quick_sort_tail(arr, start, end):
            if start >= end:
                return
                
            pivot = partition(arr, start, end)
            quick_sort_tail(arr, start, pivot - 1)
            return quick_sort_tail(arr, pivot + 1, end)
            
        return quick_sort_tail(arr, 0, len(arr) - 1)
    ```

* 최적화 예제
    ```python
    class TailRecursionOptimizer:
        """꼬리 재귀 최적화를 시뮬레이션하는 클래스"""
        
        def __init__(self, func):
            self.func = func
            
        def __call__(self, *args, **kwargs):
            result = self.func(*args, **kwargs)
            while callable(result):
                result = result()
            return result

    @TailRecursionOptimizer
    def optimized_factorial(n, acc=1):
        if n <= 1:
            return acc
        return lambda: optimized_factorial(n - 1, n * acc)
    ```

- 꼬리 재귀는 일반 재귀의 단점을 보완하는 중요한 최적화 기법입니다. 특히 함수형 프로그래밍에서 자주 사용되며,
적절한 컴파일러 지원이 있을 경우 반복문 수준의 효율성을 얻을 수 있습니다. 하지만 Python과 같은 일부 언어들은 꼬리 재귀 최적화를
기본적으로 지원하지 않으므로, 이러한 제약사항을 고려하여 사용해야 합니다.