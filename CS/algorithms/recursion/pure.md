# 순수 재귀 (Pure Recursion)

* 순수 재귀의 개념
    * 의부 변수나 상태를 사용하지 않고 오직 매개변수와 반환값만으로 재귀를 구현하는 방식
    * 함수형 프로그래밍의 원칙을 따르는 재귀 방식
    * 부수 효과(side effect)가 없는 재귀 구현

* 기본 구현
    ```python
    # 순수 재귀 팩토리얼
    def pure_factorial(n):
        if n <= 1:
            return 1
        return n * pure_factorial(n - 1)

    # 순수 재귀 피보나치
    def pure_fibonacci(n):
        if n <= 1:
            return n
        return pure_fibonacci(n - 1) + pure_fibonacci(n - 2)
    ```

* 리스트 처리 예제
    ```python
    def pure_sum(arr):
        if not arr:
            return 0
        return arr[0] + pure_sum(arr[1:])

    def pure_reverse(lst):
        if not lst:
            return []
        return [lst[-1]] + pure_reverse(lst[:-1])

    def pure_map(func, lst):
        if not lst:
            return []
        return [func(lst[0])] + pure_map(func, lst[1:])
    ```

* 트리 구조 처리
    ```python
    class TreeNode:
        def __init__(self, value):
            self.value = value
            self.left = None
            self.right = None

    def pure_tree_sum(node):
        if not node:
            return 0
        return node.value + pure_tree_sum(node.left) + pure_tree_sum(node.right)
    ```

* 장단점
    * 장점
        - 코드가 명확하고 예측 가능
        - 디버깅이 용이
        - 병렬 처리에 적합
        - 테스트가 쉬움

    * 단점
        - 성능이 상대적으로 낮을 수 있음.
        - 메모리 사용량이 많을 수 있음
        - 일부 문제는 구현이 복잡할 수 있음.

* 실제 응용
    ```python
    # 깊은 복사
    def pure_deep_copy(obj):
        if isinstance(obj, (int, float, str, bool)):
            return obj
        if isinstance(obj, list):
            return [pure_deep_copy(item) for item in obj]
        if isinstance(obj, dict):
            return {k: pure_deep_copy(v) for k, v in obj.items()}
        return obj

    # 경로 탐색
    def pure_find_path(maze, start, end, path=()):
        if start == end:
            return path + (end,)
        if start not in maze:
            return None
        
        for next_pos in maze[start]:
            if next_pos not in path:
                new_path = pure_find_path(maze, next_pos, end, path + (start,))
                if new_path:
                    return new_path
        return None
    ```

* 최적화 기법
    ```python
    def pure_fibonacci_optimized(n, a=0, b=1):
        if n == 0:
            return a
        if n == 1:
            return b
        return pure_fibonacci_optimized(n - 1, b, a + b)
    ```

- 순수 재귀는 함수형 프로그래밍의 원칙을 따르며, 코드의 예측 가능성과 테스트 용이성을 높입니다. 하지만 성능과 메모리 사용에
주의해야 하며, 적절한 사용 사례를 선택하는 것이 중요합니다.