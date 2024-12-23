# AVL 트리 (AVL Tree)

* 개념
    * AVL 트리는 1962년 Georgy Adelson-Velsky와 Evgenii Landis가 고안한, **이진 검색 트리(BST)**의 한 형태입니다.

    * 왼쪽 서브트리와 오른쪽 서브트리의 **높이 차이(Height Difference)**가 1을 넘지 않도록 유지함으로써,
        * 최악의 경우에도 트리의 높이가 **O(log n)**에 머무르도록 설계되었습니다.

    * 이 원리에 따라, 탐색, 삽입, 삭제 모두 O(log n) 성능을 항상 보장합니다(편향되지 않음.)

* 균형 인수(Balance Factor)
    * 각 노드별로, 왼쪽 서브트리의 높이와 오른쪽 서브트리의 높이의 차이를 균형 인수(Balance Factor)라 합니다.
        - BF(node) = height(left subtree) - height(right subtree)
    
    * AVL 트리 규칙: 모든 노드에 대해 |BF(node)| <= 1.
        - 즉, 왼쪽과 오른쪽 서브트리의 높이 차가 최대 1을 넘지 않도록 유지.

    * 노드를 삽입/삭제할 때, 만약 어떤 노드의 BF가 -2 또는 +2가 되면(즉 균형 인수가 허용 범위를 벗어나면), 회전(Rotation) 작업으로 균형을 복구합니다.

* 회전(Rotation) 종류
    - AVL 트리에서 불균형을 해소하기 위해, 삽입/삭제 시 특정 **회전 연산(Rotation)**을 수행합니다. 대표적으로는 단일 회전(Single Rotation)과 이중 회전(Double Rotation)이 있습니다.

    1. LL 회전(Left-Left 불균형)
        - 새 노드가 왼쪽 자식의 왼쪽 부분에 삽입되어 높이 균형이 깨진 경우
        - 해결책: 오른쪽 회전(Right Rotation)

    2. RR 회전(Right-Right 불균형)
        - 새 노드가 오른쪽 자식의 오른쪽 부분에 삽입된 경우
        - 해결책: 왼쪽 회전(Left Rotation)

    3. LR 회전(Left-Right 불균형)
        - 새 노드가 왼쪽 자식의 오른쪽 부분에 삽입되어 불균형 발생
        - 해결책: 왼쪽 회전을 자식에게, 그 뒤 오른쪽 회전을 부모에게 (이중 회전)

    4. RL 회전(Right-Left 불균형)
        - 새 노드가 오른쪽 자식의 왼쪽 부분에 삽입된 경우
        - 해결책: 오른쪽 회전을 자식에게, 그 뒤 왼쪽 회전을 부모에게 (이중 회전)

    <center> <img src="https://upload.wikimedia.org/wikipedia/commons/2/27/Tree_Rebalancing.png" alt="AVL Rotation" width="450"> </center>
    - 회전(단일/이중)을 통해 트리의 높이가 더 이상 +2/-2 차이나지 않도록 조정

* 연산
    1. 탐색 (Search)
        - 기본적으로 이진 검색 트리와 같음 -> 평균 O(log n), 높이가 엄격히 제한되므로 최악도 O(log n).

    2. 삽입 (Insertion)
        1. BST 삽입 규칙대로 새 노드를 리프 위치에 삽입
        2. 삽입 후, 루트까지 거슬러 올라가면서 **균형 인수(Balance Factor)**를 확인
        3. 어떤 노드의 BF가 -2 또는 +2가 되면, **불균형 유형(LL, RR, LR, RL)**을 판별
        4. 해당 유형에 맞는 단일/이중 회전을 수행하여 균형 복구

    3. 삭제 (Deletion)
        1. BST 삭제와 동일하게 삭제 노드를 찾고, 자식 개수(0, 1, 2)에 따라 제거
        2. 삭제 후, 경로를 따라 올라가며 각 노드의 BF를 갱신
        3. 불균형이 발견되면(+-2), 해당 패턴(LL, RR, LR, RL)에 맞춰 회전 수행

* 예시 코드
    1. Python
        ```python
        class AVLNode:
            def __init__(self, val):
                self.val = val
                self.left = None
                self.right = None
                self.height = 1  # 노드의 높이를 저장

        def get_height(node):
            return node.height if node else 0

        def get_balance(node):
            if not node:
                return 0
            return get_height(node.left) - get_height(node.right)

        def update_height(node):
            node.height = 1 + max(get_height(node.left), get_height(node.right))

        def right_rotate(y):
            x = y.left
            T2 = x.right
            
            # 회전
            x.right = y
            y.left = T2
            
            # 높이 갱신
            update_height(y)
            update_height(x)
            
            return x  # x가 회전 후 루트

        def left_rotate(x):
            y = x.right
            T2 = y.left
            
            # 회전
            y.left = x
            x.right = T2
            
            # 높이 갱신
            update_height(x)
            update_height(y)
            
            return y  # y가 회전 후 루트

        def avl_insert(root, val):
            if not root:
                return AVLNode(val)
            
            # BST 삽입
            if val < root.val:
                root.left = avl_insert(root.left, val)
            else:
                root.right = avl_insert(root.right, val)
            
            # 노드 높이 갱신
            update_height(root)
            
            # 균형 인수 계산
            balance = get_balance(root)
            
            # 불균형 패턴 체크
            # LL
            if balance > 1 and val < root.left.val:
                return right_rotate(root)
            # RR
            if balance < -1 and val > root.right.val:
                return left_rotate(root)
            # LR
            if balance > 1 and val > root.left.val:
                root.left = left_rotate(root.left)
                return right_rotate(root)
            # RL
            if balance < -1 and val < root.right.val:
                root.right = right_rotate(root.right)
                return left_rotate(root)
            
            return root

        def inorder_traverse(node):
            if not node:
                return
            inorder_traverse(node.left)
            print(node.val, end=' ')
            inorder_traverse(node.right)

        # 사용 예시
        if __name__ == "__main__":
            avl_root = None
            for v in [10, 20, 30, 40, 50, 25]:
                avl_root = avl_insert(avl_root, v)
            # Inorder Traversal (오름차순 출력)
            inorder_traverse(avl_root)  # 10 20 25 30 40 50

        ```
        - 위 코드에서는 회전 후에 `update_height`를 잊지 않고 수행해야 함.
        - 삭제 시에도 유사한 방식으로 BST 삭제 후, 해당 노드까지 거슬러 올라가면서 BF 체크 -> 회전.

* 시간 복잡도
    * AVL 트리는 각 노드의 높이 차가 최대 1이므로, n개 노드에 대해 트리 높이가 **O(log n)**로 유지.
    * 탐색, 삽입, 삭제 모두 O(log n) 이며, 삽입/삭제 시 회전도 상수 횟수(최대 2회)만 일어남.

* 장단점
    1. 장점
        1. 엄격한 균형 유지: 높이 차가 최대 1 -> 항상 O(log n) 보장
        2. 탐색/삽입/삭제 성능 안정적
        3. 데이터가 특정 순서(정렬된 입력 등)로 들어와도 편향 트리가 되지 않음.

    2. 단점
        1. 구현 복잡도: 삽입/삭제 시, 회전(Rotation) 로직과 높이 갱싱, BF 체크가 필요
        2. 중복값 처리를 BST와 동일하게 하되, 중복으로 인한 균형 문제가 발생할 수 있음.
        3. 균형 유지가 엄격해서, 삽입/삭제가 잦은 경우 Red-Black Tree 등 좀 더 완화된 균형 트리를 선호하기도 함.

* 실무에서의 사용
    * AVL 트리는 이론적으로 BST의 완벽한 균형에 가까운 형태를 유지 -> 검색, 삽입, 삭제 모두 최악에도 O(log n)
    * Red-Black 트리나 B-Tree 등을 사용하는 라이브러리가 많아, 실제 C++ `std::map`, `std::set`등은 Red-Black 트리 기반인 경우가 많음.
    * AVL은 읽기(Search) 비중이 높으면서 삽입/삭제가 상대적으로 적은 상황에서 성능이 매우 좋음.
    * 삽입/삭제가 많다면, 재균형 연산 비용이나 구현 복잡도 면에서 Red-Black 트리가 더 자주 쓰이기도 함.

* 요약
    * AVL 트리는 이진 검색 트리의 한 종류로, 각 노드에서 왼/오른쪽 서브트리 높이 차가 최대 1이라는 엄격한 균형 조건을 지킴.
    * 이에 따라, 탐색/삽입/삭제가 항상 **O(log n)**을 보장하며, 특정 입력 패턴(예: 정렬된 순서)에서도 편향이 발생하지 않음.
    * 단점으로는 구현 난이도가 높으며, 삽입/삭제가 빈번한 경우에는 Red-Black 트리와 같은 다른 균형 트리에 비해 회전이 자주 발생할 수 있음.
    * 그래도 BST의 편향 문제를 가장 효과적으로 극복한 자료구조 중 하나로, 검색과 삽입/삭제가 모두 균일한 성능을 요구하는 환경에서 활용도가 큼.