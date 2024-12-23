# 이진 검색 트리의 확장/문제 해결

## AVL 트리(Adelson-Velsky and Landis Tree)
AVL 트리는 BST에서 발생하는 편향(Skewed) 문제를 해결하기 위해, 노드 높이 균형을 엄격하게 유지하는 자가 균형 이진 검색 트리의 한 종류입니다.
[AVL](avl.md)

# 이진 검색 트리 (BST: Binary Search Tree)

* 개념
    * 이진 검색 트리는 이진 트리의 한 종류로, 각 노드에 저장된 값에 대해 다음과 같은 정렬 규칙을 만족해야 합니다:
        - "왼쪽 자식 노드의 값 < (또는 <=) 현재 노드의 값 < (또는 >=) 오른쪽 자식 노드의 값"
            - (고전적인 정의에서)왼쪽 < 현재 < 오른쪽으로 표현
            - 중복 값 처리(= 허용 / = 오른쪽 자식으로 등)는 구현에 따라 다를 수 있음.
    * 이 규칙 덕분에, 특정 값을 빠르게 탐색할 수 있고, 삽입과 삭제 등의 연산도 효율적으로 수행할 수 있음 (평균 O(log n)).

* 특징
    1. 탐색(Search) 시간 복잡도
        - 평균 O(log n), 최악의 경우(편향 트리) O(n)
        - BST 규칙(왼쪽 < 현재 < 오른쪽)을 이용해, 탐색할 값이 현재 노드보다 작으면 왼쪽 자식, 크면 오른쪽 자식 방향으로 탐색 범위를 줄여감.

    2. 삽입(Insertion)도 평균 O(log n)
        - 탐색 과정처럼, 삽입할 위치를 찾아 내려가며(왼쪽 또는 오른쪽), 리프 위치에 새 노드를 붙임.
        - 편향 트리(스큐드 트리)가 되면 O(n)이 될 수 있음.

    3. 삭제(Deletion) 연산
        - 삭제하려는 노드가 **잎(Leaf)**인지, 자식이 하나인 노드인지, 자식이 두 개인 노드인지에 따라 다르게 처리
        - 자식이 두 개인 노드를 삭제할 때, 중위 후속자(inorder successor) 또는 **중위 전임자(inorder predecessor)**를 찾는 방식을 사용

    4. 중위 순회(Inorder Traversal)
        - 왼쪽 자식 -> 현재 노드 -> 오른쪽 자식 순으로 방문
        - BST에서 중위 순회 시, 오름차순(또는 내림차순)으로 정렬된 결과를 얻을 수 있음.

* BST의 주요 연산
    1. 탐색(Search)
        ```python
        def bst_search(root, target):
            if root is None:
                return None  # 찾는 값이 없음
            
            if target == root.val:
                return root
            elif target < root.val:
                return bst_search(root.left, target)
            else: # target > root.val
                return bst_search(root.right, target)
        ```
        1. 현재 노드가 `target`과 같은지 확인
        2. 작으면 왼쪽 자식으로, 크면 오른쪽 자식으로 재귀 탐색
        3. 노드를 찾거나 `None`이 될 때까지 반복

    2. 삽입(Insertion)
        ```python
        def bst_insert(root, value):
            if root is None:
                return TreeNode(value)  # 새 노드(leaf) 생성
            
            if value < root.val:
                root.left = bst_insert(root.left, value)
            else:  # value >= root.val 로 가정 (또는 value > root.val)
                root.right = bst_insert(root.right, value)
            
            return root
        ```
        1. 탐색과 동일한 방식으로 내려가며, 삽입할 위치를 찾음 (리프 위치)
        2. 노드가 비어있는 지점(`None`)에서 새 노드를 만들어 연결
        3. (구현에 따라 `value < root.val`을 왼쪽에 붙일 수도, 오른쪽에 붙일 수도 있음)

    3. 삭제 (Deletion)
        ```python
        def bst_delete(root, value):
            if root is None:
                return None
            
            if value < root.val:
                root.left = bst_delete(root.left, value)
            elif value > root.val:
                root.right = bst_delete(root.right, value)
            else:
                # 삭제할 노드를 찾음 -> root
                if root.left is None and root.right is None:
                    # 1) 자식이 없는 잎(leaf) 노드
                    return None
                elif root.left is None:
                    # 2) 자식이 하나(오른쪽만 존재)
                    return root.right
                elif root.right is None:
                    # 2) 자식이 하나(왼쪽만 존재)
                    return root.left
                else:
                    # 3) 자식이 두 개인 노드
                    # 중위 후속자(inorder successor) 찾기
                    successor = find_min(root.right)
                    root.val = successor.val
                    # 후속자를 삭제
                    root.right = bst_delete(root.right, successor.val)
            
            return root

        def find_min(node):
            # 오른쪽 서브트리에서 가장 작은 값을 찾으려면 왼쪽으로 내려감
            current = node
            while current.left:
                current = current.left
            return current
        ```
        - 삭제 케이스:
            1. 잎(leaf) 노드: 바로 제거 (None 반환)
            2. 자식이 하나인 노드: 그 자식을 부모에 연결
            3. 자식이 둘인 노드: 중위 후속자(또는 전임자)를 찾아, 현재 노드의 값을 대체한 뒤, 후속자 노드를 제거

* 예시 코드
    1. Python
        ```python
        class TreeNode:
            def __init__(self, val):
                self.val = val
                self.left = None
                self.right = None

        class BinarySearchTree:
            def __init__(self):
                self.root = None
            
            def search(self, value):
                return self._search_recursive(self.root, value)
            
            def _search_recursive(self, node, value):
                if node is None:
                    return None
                if node.val == value:
                    return node
                elif value < node.val:
                    return self._search_recursive(node.left, value)
                else:
                    return self._search_recursive(node.right, value)
            
            def insert(self, value):
                self.root = self._insert_recursive(self.root, value)
            
            def _insert_recursive(self, node, value):
                if node is None:
                    return TreeNode(value)
                
                if value < node.val:
                    node.left = self._insert_recursive(node.left, value)
                else:
                    node.right = self._insert_recursive(node.right, value)
                return node
            
            def delete(self, value):
                self.root = self._delete_recursive(self.root, value)
            
            def _delete_recursive(self, node, value):
                if node is None:
                    return None
                
                if value < node.val:
                    node.left = self._delete_recursive(node.left, value)
                elif value > node.val:
                    node.right = self._delete_recursive(node.right, value)
                else:
                    # node.val == value -> 삭제 대상
                    if node.left is None and node.right is None:
                        return None
                    elif node.left is None:
                        return node.right
                    elif node.right is None:
                        return node.left
                    else:
                        # 자식 2개
                        successor = self._find_min(node.right)
                        node.val = successor.val
                        node.right = self._delete_recursive(node.right, successor.val)
                return node
            
            def _find_min(self, node):
                while node.left:
                    node = node.left
                return node
            
            def inorder_traversal(self):
                self._inorder(self.root)
                print()
            
            def _inorder(self, node):
                if not node:
                    return
                self._inorder(node.left)
                print(node.val, end=' ')
                self._inorder(node.right)

        # 사용 예시
        if __name__ == "__main__":
            bst = BinarySearchTree()
            for v in [8, 3, 10, 1, 6, 14, 4, 7, 13]:
                bst.insert(v)

            bst.inorder_traversal()  # 1 3 4 6 7 8 10 13 14 (오름차순)
            
            # 검색
            node = bst.search(6)
            print("Search 6:", node.val if node else "Not found")
            
            # 삭제
            bst.delete(8)  # 루트(8) 삭제
            bst.inorder_traversal()  # 1 3 4 6 7 10 13 14 (8이 빠짐)
        ```

* 이진 검색 트리의 장단점
    1. 장점
        1. 탐색/삽입/삭제 평균 O(log n)
            - 왼쪽/오른쪽으로 탐색 범위를 반씩 줄여가기 때문

        2. 중위 순회(Inorder Traversal) 시 정렬된 순서로 노드 방문
        3. 구현이 비교적 단순 (왼쪽/오른쪽 포인터/참조 + 값의 비교)
        4. 동적 자료 구조 -> 노드 수가 유연하게 증가/감소

    2. 단점
        1. 편향(Skewed) 트리가 되면(예: 입력이 정렬된 상태로 삽입) O(n)으로 성능 저하
        2. 중간 노드 삭제 시, 재구성(서비트리 조정) 로직이 필요
        3. 중복 값 처리 방식(=, <, >)을 어떻게 할지 구현 시 결정해야 함.
        4. 중위 순회가 정렬된 순서가 되려면 BST 규칙이 엄격히 지켜져야 함.

* 편향 트리(스큐드 트리) 문제와 균형 트리
    * BST는 삽입되는 데이터의 순서에 따라 한쪽으로 치우친 형태(편향 트리)가 될 수 있음.
        - 예: 이미 오름차순 정렬된 데이터를 순차 삽입하면, 매번 오른쪽 자식만 생기는 편향 구조 -> O(n) 시간
    
    * 이를 해결하기 위해, AVL, Red-Black Tree, B-Tree 등 균형 이진 검색 트리가 고안됨.
        - 삽입/삭제 시 트리 균형을 회전(Rotation) 등을 통해 유지 -> 항상 O(log n)

* 실사용 사례
    1. 집합(Set) 또는 맵(Map) 구현
        - 예: C++의 `std::set`, `std::map`은 대부분 Red-Black Tree로 구현 (BST의 균형 버전)
    
    2. 중위 순회를 통한 데이터 정렬
        - 트리 자체가 삽입/삭제 과정을 거치면서도 정렬 상태(중위 순회 시)를 유지

    3. 검색/삽입/삭제가 고르게 필요한 경우
        - 평균 O(log n) 성능 보장 (단, 균형 트리를 쓰면 더욱 안정적)

    4. 멀티셋(Multiset), 다중맵(Multimap)등 중복 요소 처리

    5. 각종 구조 트리
        - 예를 들어, 게임 AI의 상태 트리, 표현식 파서, 사전 자료 구조 등

* 핵심 요약
    * **이진 검색 트리(BST)**는 이진 트리에 검색 효율을 더하기 위해, 왼쪽 < 현재 < 오른쪽 규칙을 적용한 자료구조.
    * 탐색/삽입/삭제 모두 평균 O(log n), 그러나 편향될 경우 최악 O(n)
    * 중위 순회 시 오름차순 / 내림차순 정렬된 순서로 노드를 방문하게 된다는 것이 큰 장점.
    * 실무 및 라이브러리 구현에서는 균형 트리(AVL, Red-Black, B-Tree 등) 형태로 더 자주 사용.