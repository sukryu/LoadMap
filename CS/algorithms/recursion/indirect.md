# 간접 재귀 (Indirect Recursion)

* 간접 재귀의 개념
    * 두 개 이상의 함수가 서로를 호출하며 재귀를 형성하는 방식입니다.
    * 순환적 의존 관계를 가진 함수들의 호출입니다.
    * A -> B -> C -> A 형태로 호출이 순환됩니다.

* 기본 구현 예제
    ```python
    def is_even(n):
        if n == 0:
            return True
        return is_odd(n - 1)

    def is_odd(n):
        if n == 0:
            return False
        return is_even(n - 1)
    ```

* 실용적인 예제
    ```python
    class TreeNode:
        def __init__(self, value):
            self.value = value
            self.children = []

    def process_tree(node):
        print(f"처리: {node.value}")
        process_children(node.children)

    def process_children(children):
        if not children:
            return
        process_tree(children[0])
        process_children(children[1:])
    ```

* 파일 탐색 시스템 예제
    ```python
    def explore_directory(path):
        if os.path.isfile(path):
            process_file(path)
        else:
            process_directory(path)

    def process_directory(path):
        for item in os.listdir(path):
            full_path = os.path.join(path, item)
            explore_directory(full_path)

    def process_file(path):
        print(f"파일 발견: {path}")
    ```

* 성능 최적화
    ```python
    # 메모이제이션을 활용한 최적화
    def evaluate_expression(expr, memo=None):
        if memo is None:
            memo = {}
        if expr in memo:
            return memo[expr]
            
        result = parse_and_evaluate(expr, memo)
        memo[expr] = result
        return result

    def parse_and_evaluate(expr, memo):
        # 수식 파싱 및 평가
        if is_simple_expression(expr):
            return calculate(expr)
        return evaluate_expression(simplify(expr), memo)
    ```

* 시간 및 공간 복잡도
    * 시간 복잡도: 서로 호출하는 함수들의 복잡도 합
    * 공간 복잡도: 재귀 깊이에 비례(보통 O(n))

* 장단점
    * 장점
        - 복잡한 문제를 논리적으로 분할 가능
        - 코드의 모듈성 향상
        - 자연스러운 문제 해결 방식

    * 단점
        - 디버깅이 어려움
        - 함수 간 의존성 관리 필요
        - 메모리 사용량이 많음

* 데이터 구조 처리 예제
    ```python
    class LinkedList:
        def __init__(self):
            self.head = None

        def process_odd_nodes(self, node):
            if not node:
                return
            print(f"홀수 노드: {node.value}")
            if node.next:
                self.process_even_nodes(node.next)

        def process_even_nodes(self, node):
            if not node:
                return
            print(f"짝수 노드: {node.value}")
            if node.next:
                self.process_odd_nodes(node.next)
    ```

* 게임 로직 예제
    ```python
    def player1_turn(score1, score2):
        if score1 >= 100:
            return "Player 1 wins!"
        if score2 >= 100:
            return "Player 2 wins!"
        
        move = get_player1_move()
        return player2_turn(score1 + move, score2)

    def player2_turn(score1, score2):
        if score1 >= 100:
            return "Player 1 wins!"
        if score2 >= 100:
            return "Player 2 wins!"
            
        move = get_player2_move()
        return player1_turn(score1, score2 + move)
    ```

- 간접 재귀는 복잡한 문제를 여러 단계로 나누어 해결할 때 유용합니다. 특히 상태 기계나 게임 로직 구현에
자주 사용됩니다. 하지만 직접 재귀보다 디버깅이 어렵고 함수 간 의존성을 잘 관리해야 하므로 신중하게 사용해야 합니다.
