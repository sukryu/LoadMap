# 레드-블랙 트리 (Red-Black Tree)

* 개념
    * 레드-블랙 트리는 이진 검색 트리의 일종으로, 각 노드에 **색상(빨간/검정)**을 추가하여 트리의 높이를 일정 수준으로 균형되게 유지합니다.
    
    * AVL과 달리, 노드의 구체적인 높이 차(+-1)를 제한하는 대신, 레드/블랙 색상 규칙을 통해 **모든 리프(또는 NIL 노드)**까지의 "검은색 노드 수"가 동일하도록 보장합니다.

    * 이러한 색상 규칙으로 인해 **최악의 경우에도 트리 높이가 O(log n)**임을 보장하며, 삽입/삭제 시 회전이 발생해도 AVL보다 상대적으로 덜 발생하는 경향이 있습니다(균형 유지 조건이 완화됨.)

* 핵심 속성 (레드-블랙 트리 불변식)
    - 레드-블랙 트리의 노드는 "레드(Red)" 또는 "블랙(Black)" 색깔을 가집니다. 다음 속성을 항상 만족해야 합니다:
        1. 노드는 빨간색 혹은 검은색
        2. 루트 노드는 항상 검은색(Black)
        3. 리프(leaf) 노드(또는 `NIL`노드)는 모두 검은색
            - 구현에 따라 실제 데이터를 담지 않는 `NIL` 노드를 명시적으로 둠.
        4. 빨간 노드의 부모와 자식은 모두 검은색
            - 빨간 노드가 연속해서 연결되지 못하도록 (Red nod cannot have a Red child)
        5. 각 노드에서 리프(NIL) 노드에 도달하는 모든 경로는 동일한 개수의 검은색 노드를 포함해야 함.

    - 이러한 불변식을 레드-블랙 특성이라 부르며, 이를 지키기 위해 삽입/삭제 후에 색상 재조정과 회전이 이루어집니다.

* 시간 복잡도
    * 탐색(Search), 삽입(Insertion), 삭제(Deletion) 모두 O(log n) 보장
    * 트리 높이가 최악의 경우에도 2 * log2(n + 1) 이하(대략)로 제한됨
    * AVL 트리처럼 편향되지 않으며, 삽입/삭제 시 회전이 적게 발생(균형 조건이 조금 더 느슨)

* 삽입(Insert) 개략
    1. 이진 검색 트리(BST) 규칙대로 삽입 위치를 찾고, 새 노드를 **빨간색(Red)**으로 생성
    2. 삽입된 노드가 레드-블랙 속성을 어기는지 확인
        - 예: 새 노드와 부모가 모두 빨간색이면 속성 위반
        - 이 경우 색상 바꾸기(Recoloring), 회전(Rotation) 등을 통해 규칙을 복원
    3. 루트 노드는 항상 검은색으로 유지

    * 삽입 과정에서 주로 발생하는 문제 패턴:
        - Case 1: 삽입된 노드의 부모와 삼촌이 모두 빨강 -> 색상 반전(Recolor)
        - Case 2/3: 부모는 빨강이고 삼촌은 검정, 삽입된 노드가 "삼촌 방향"에 위치 -> 회전 + 색상 변경 등

* 삭제(Deletion) 개략
    1. BST 삭제 로직으로 해당 노드를 찾고 제거
    2. 만약 삭제되는 노드 혹은 대체 노드가 검은색이면, 레드-블랙 속성이 깨질 수 있음
    3. 더블 블랙(Double Black) 상태 등 복잡한 케이스를 색상 재조정과 회전으로 해결
        - 다양한 케이스(형제 노드가 레드/블랙, 형제의 자식 색, 조부모 등)에 따라 회전/색상 변경

    * 삭제 로직은 삽입보다 더 경우의 수가 많아 구현이 복잡합니다. 주요 아이디어:
        - Case 1: 형제가 빨간색 -> 색상 스왑 + 회전
        - Case 2: 형제와 형제의 자식들이 모두 검정 -> 부모까지 검정화(=더블 블랙 전파)
        - Case 3: 형제가 검정이고, 형제의 자식 중 하나가 빨강 -> 회전/색상 교체

* 예시 구현
    1. Python
        - 삽입 위주의 개략 예시(삭제도 유사하게 회전과 색상 변경 과정을 코드화 해야 함.)
        ```python
        RED = True
        BLACK = False

        class RBNode:
            def __init__(self, val):
                self.val = val
                self.color = RED
                self.left = None
                self.right = None
                self.parent = None

        def is_red(node):
            return node is not None and node.color == RED

        def left_rotate(root, node):
            # node의 오른쪽 자식을 x라 하자
            x = node.right
            node.right = x.left
            if x.left:
                x.left.parent = node
            x.parent = node.parent
            if node.parent is None:
                root = x
            elif node == node.parent.left:
                node.parent.left = x
            else:
                node.parent.right = x
            x.left = node
            node.parent = x
            return root

        def right_rotate(root, node):
            x = node.left
            node.left = x.right
            if x.right:
                x.right.parent = node
            x.parent = node.parent
            if node.parent is None:
                root = x
            elif node == node.parent.right:
                node.parent.right = x
            else:
                node.parent.left = x
            x.right = node
            node.parent = x
            return root

        def rb_insert(root, val):
            if root is None:
                node = RBNode(val)
                node.color = BLACK
                return node
            
            # BST insert
            cur = root
            parent = None
            while cur:
                parent = cur
                if val < cur.val:
                    cur = cur.left
                else:
                    cur = cur.right
            
            node = RBNode(val)
            node.parent = parent
            if val < parent.val:
                parent.left = node
            else:
                parent.right = node
            
            # 삽입 후 fix
            return insert_fixup(root, node)

        def insert_fixup(root, node):
            while node.parent and is_red(node.parent):
                grand = node.parent.parent
                if node.parent == grand.left:
                    # 삼촌 = grand.right
                    uncle = grand.right
                    # Case 1: 삼촌이 레드
                    if is_red(uncle):
                        node.parent.color = BLACK
                        uncle.color = BLACK
                        grand.color = RED
                        node = grand
                    else:
                        # Case 2 / Case 3
                        if node == node.parent.right:
                            node = node.parent
                            root = left_rotate(root, node)
                        node.parent.color = BLACK
                        grand.color = RED
                        root = right_rotate(root, grand)
                else:
                    # 대칭: node.parent == grand.right
                    uncle = grand.left
                    if is_red(uncle):
                        node.parent.color = BLACK
                        uncle.color = BLACK
                        grand.color = RED
                        node = grand
                    else:
                        if node == node.parent.left:
                            node = node.parent
                            root = right_rotate(root, node)
                        node.parent.color = BLACK
                        grand.color = RED
                        root = left_rotate(root, grand)
            # 루트는 항상 블랙
            root.color = BLACK
            return root

        # 사용 예시
        if __name__ == "__main__":
            root = None
            for v in [10, 20, 30, 15, 25, 27]:
                root = rb_insert(root, v)
            # (트리 순회 코드는 별도 구현)
        ```

* 장단점
    1. 장점
        1. O(log n) 성능 보장
            - (약간의) 균형을 항상 유지

        2. 회전이 AVL보다 적게 발생
            - 삽입/삭제 시, 색상 변경(Recolor)만으로 해결되는 케이스가 많음.
        
        3. 실무 라이브러리에서 많이 사용
            - 예: C++ `std::map`, `std::set`, Java `TreeMap`, `TreeSet` 등 대부분 Red-Black 트리 기반

    2. 단점
        1. AVL보다 검색 성능이 아주 약간 떨어질 수 있음 (균형도가 조금 덜 엄격)
        2. 구현 난이도(삭제가 특히 까다로움)는 AVL 이상으로 복잡
        3. 노드에 추가 정보(색상, 부모 포인터, NIL 노드 등)를 관리해야 함.

* AVL vs. Red-Black 비교

    | |특징| AVL 트리| Red-Black 트리|  | 
    |----|----|----|----|
    |균형 유지 조건|노드별 왼/오른쪽 높이차 <= 1|루트~리프 경로의 '검은색 수' 동일|
    |삽입/삭제  회전|더 자주(엄격균형)|상대적으로 덜 자주(완화균형)|
    |탐색 성능|더 엄격한 균형 -> 빠름|약간 완화된 균형 -> 미세하게 더 느릴 수 있음|
    |구현 복잡도|높이 관리, 4가지 회전 유형|색깔 관리, 삽입/삭제 더 많은 케이스|
    |적용 사례례|읽기(Search) 비중 ↑|삽입/삭제가 많은 맵/셋 라이브러리|

    - 실제로는 각 구현체마다 차이가 있을 수 있으나, AVL은 탐색 성능 우수, Red-Black은 삽입/삭제가 많은 경우 좋다는 일반적인 인식이 있음.