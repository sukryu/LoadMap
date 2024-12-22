# 이진 트리 (Binary Tree)

* 개념
    * 이진 트리란, 트리 구조에서 각 노드가 최대 2개의 자식 노드(왼쪽 자식, 오른쪽 자식)만 가질 수 있는 형태를 말합니다.
    * 자식 노드 간에는 특별한 "값의 정렬 규칙"이 존재하지 않을 수도 있습니다.
        - 예: 왼쪽 자식의 값이 반드시 작거나, 오른쪽 자식의 값이 반드시 크다는 규칙은 **이진 검색 트리(BST)**에서만 적용됨.
    * 일반 트리(모든 노드가 임의의 수의 자식을 가짐)보다 구현이 단순하고, 2분법 구조를 적용하는 많은 알고리즘/자료구조의 기초가 됩니다.
        - 예: 힙(Heap), 이진 검색 트리(BST), 이진 트라이 등

* 기본 구성 요소
    1. 노드(Node)
        - **데이터(data) 또는 값(value)**를 저장하고,
        - 왼쪽(left), 오른쪽(right) 자식 노드에 대한 참조(포인터)를 가집니다.

        ```python
        class BinaryTreeNode:
            def __init__(self, val):
                self.val = val
                self.left = None
                self.right = None
        ```

    2. 루트(Root)
        - 이진 트리의 시작점이 되는 노드
        - 부모가 없는 최상위 노드

    3. 잎(Leaf)
        - 왼쪽 자식과 오른쪽 자식이 모두 없는 노드

    4. 깊이(Depth) / 높이(Height)
        - 깊이(Depth): 루트 노드에서 현재 노드까지 이르는 경로의 간선 개수
        - 높이(Height): 특정 노드에서 가장 깊은 잎 노드까지의 경로 길이

* 이진 트리의 종류
    1. 정 이진 트리(Full Binary Tree)
        - 모든 노드가 0개 또는 2개의 자식을 가지는 이진 트리
    
    2. 완전 이진 트리(Complete Binary Tree)
        - 모든 레벨이 꽉 찬 상태(노드가 빠짐없이)이고, 마지막 레벨만 왼쪽부터 차례대로 노드가 채워진 형태
        - 힙(Heap) 구조를 배열에 저장할 때, 완전 이진 트리 형태를 활용

    3. 포화 이진 트리(Perfect Binary Tree)
        - 모든 레벨이 노드로 완전히 채워져 있으며, 각 노드는 2개의 자식을 가짐
        - 정 이진 트리이면서 완전 이진 트리인 특수한 경우

    4. 편향 이진 트리(Skewed Binary Tree)
        - 모든 노드가 왼쪽 자식 혹은 오른쪽 자식 중 한 방향으로만 연결된 상태
        - 사실상 연결 리스트(Linked-List)에 가까운 구조가 되어, 탐색 시 O(n) 성능

* 이진 트리 순회 (Traversal)
    - 이진 트리 순회 방법은 크게 깊이 우선 탐색(DFS) 계열인 전위/중위/후위 순회와, 너비 우선 탐색(BFS) 계열인 레벨 순회로 나눌 수 있습니다.

    1. 전위 순회 (Preorder Traversal)
        1. 현재 노드 방문
        2. 왼쪽 서브트리 전위 순회
        3. 오른쪽 서브트리 전위 순회
        ```python
        def preorder(node):
            if not node:
                return
            print(node.val)         # 1. 현재 노드 방문
            preorder(node.left)     # 2. 왼쪽 서브트리
            preorder(node.right)    # 3. 오른쪽 서브트리
        ```

    2. 중위 순회 (Inorder Travarsal)
        1. 왼쪽 서브트리 중위 순회
        2. 현재 노드 방문
        3. 오른쪽 서브트리 중위 순회
        ```python
        def inorder(node):
            if not node:
                return
            inorder(node.left)      # 1. 왼쪽 서브트리
            print(node.val)         # 2. 현재 노드 방문
            inorder(node.right)     # 3. 오른쪽 서브트리
        ```
        - **이진 검색 트리(BST)**에서 중위 순회를 하면 오름차순 정렬된 순서로 노드를 방문하게 됨.

    3. 후위 순회 (Postorder Traversal)
        1. 왼쪽 서브트리 후위 순회
        2. 오른쪽 서브트리 후위 순회
        3. 현재 노드 방문
        ```python
        def postorder(node):
            if not node:
                return
            postorder(node.left)    # 1. 왼쪽 서브트리
            postorder(node.right)   # 2. 오른쪽 서브트리
            print(node.val)         # 3. 현재 노드 방문
        ```

    4. 레벨 순회 (Level-order Traversal, BFS)
        - 같은 레벨의 노드들을 왼쪽에서 오른쪽 순으로 방문
        - 보통  **큐(Queue)**를 사용하여 구현
        ```python
        from collections import deque

        def level_order(root):
            if not root:
                return
            queue = deque([root])
            while queue:
                node = queue.popleft()
                print(node.val)
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
        ```

* 이진 트리의 구현 예시
    1. Python
        ```python
        class Node:
            def __init__(self, val):
                self.val = val
                self.left = None
                self.right = None

        class BinaryTree:
            def __init__(self):
                self.root = None
            
            def add_left(self, parent: Node, child_val):
                child = Node(child_val)
                parent.left = child
                return child
            
            def add_right(self, parent: Node, child_val):
                child = Node(child_val)
                parent.right = child
                return child
            
            def preorder_traversal(self, node):
                if not node:
                    return
                print(node.val, end=' ')
                self.preorder_traversal(node.left)
                self.preorder_traversal(node.right)

        # 사용 예시
        if __name__ == "__main__":
            bt = BinaryTree()
            bt.root = Node("A")
            
            # A 노드의 왼쪽, 오른쪽 자식 추가
            b_node = bt.add_left(bt.root, "B")
            c_node = bt.add_right(bt.root, "C")
            
            # B 노드의 왼쪽 자식 D
            d_node = bt.add_left(b_node, "D")
            
            # 전위 순회 출력
            bt.preorder_traversal(bt.root)  # A B D C
        ```

* 이진 트리 vs 이진 검색 트리(BST)
    - 이진 트리: 노드가 최대 2개의 자식을 가진다. 왼쪽과 오른쪽 자식 노드에 값의 대소 관계에 대한 필수 규칙이 없음.
    - 이진 검색 트리(BST): 이진 트리의 특수한 형태. 왼쪽 자식 < 부모 노드 < 오른쪽 자식 규칙(또는 같음 허용 등 변형)에 따라 노드 배치.
        - 이를 통해 특정 값 탐색/삽입/삭제 연산을 평균 O(log n)에 수행 가능.
        - 이진 트리 != 이진 검색 트리(모든 BST는 이진 트리이지만, 모든 이진 트리가 BST인 것은 아니다.)

* 이진 트리의 활용 예시
    1. 힙(Heap)
        - 완전 이진 트리 형태 + 부모-자식 우선순위(최대 힙 or 최소 힙)
        - 우선순위 큐 구현

    2. 이진 검색 트리(BST)
        - 탐색, 정렬, 삽입/삭제 등 평균 O(log n) 기대

    3. 표현식 트리(Expression Tree)
        - 수학/논리식 구조를 이진 트리로 구성

    4. 허프만 트리(Huffman Tree)
        - 문자열 압축 알고리즘에서 사용 (Huffam 코딩)

    5. 이진 결정 트리 (Decision Tree)
        - 머신러닝(의사결정트리) 또는 알고리즘 설계 등

* 장단점
    1. 장점
        - 구현이 비교적 단순(왼/오른쪽 참조만 관리)
        - 재귀적(Recursively) 구조가 직관적(왼쪽 / 오른쪽 부분 트리)
        - 노드가 2개 이하의 자식을 가지므로, 특정 알고리즘(힙, BST)에 최적화되어 있음.

    2. 단점
        - 한쪽으로만 편향(Skewed)되면, 사실상 연결 리스트처럼 동작 -> 일부 연산이 O(n)
        - 일반 트리에 비해 노드당 자식 수가 최대 2개로 제한 (더 많은 자식이 필요한 경우 다진 트리를 고려)
        - 부모/자식 포인터(참조) 관리 필요, 중간 노드 제거 시 서브트리 재연결 로직이 필요

* 마무리
    - **이진 트리(Binary Tree)**는 각 노드가 최대 2개의 자식을 가지는 트리 구조로,
        - 노드 간 좌/우 구분
        - 재귀적 구조
        - 전위/중위/후위 순회 같은 다양한 순회 방식을 특징으로 합니다.

    - 이진 트리는 힙, 이진 검색 트리(BST), 허프만 트리, 세그먼트 트리 등 수많은 자료구조의 기초가 되며, 계층적이면서 2분화된 문제를 다루는 데 유용합니다.
    - 다만, 단순 이진 트리는 노드 값의 정렬 규칙을 보장하지 않는다는 점에서, 빠른 탐색을 위해선 BST나 균형 트리를 별도로 구현해야 한다는 점을 명심해야 합니다.