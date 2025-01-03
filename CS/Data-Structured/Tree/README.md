# 트리의 확장판

## 이진 트리(Binary Tree)
[Binary-Tree](./binary-tree/README.md)

## 세그먼트 트리(Segment Tree)
[Segment Tree](segment.md)

## 펜윅 트리 (Fenwick Tree)
[Fenwick Tree](fenwick.md)

# 트라이 (Trie)
[Trie](trie.md)

## 라디슐 트리 (Radix Tree)
[Radix Tree](radix.md)

```mermaid
graph TD
    T[Tree] -->|특수화| BT[Binary Tree]
    BT -->|정렬 규칙 추가| BST[Binary Search Tree]
    BST -->|높이 균형 추가| AVL[AVL Tree]
    BST -->|색상 균형 추가| RB[Red-Black Tree]

    T_DESC["• 계층적 구조
    • N개 자식 가능
    • 사이클 없음"]
    style T_DESC text-align:left

    BT_DESC["• 최대 2개 자식
    • left, right 구분
    • 순회: 전위/중위/후위"]
    style BT_DESC text-align:left

    BST_DESC["• left < parent < right
    • 중위순회 = 정렬된 순서
    • 평균 O(log n), 최악 O(n)"]
    style BST_DESC text-align:left

    AVL_DESC["• |BF| ≤ 1 (엄격한 균형)
    • 회전으로 균형 유지
    • 항상 O(log n)"]
    style AVL_DESC text-align:left

    RB_DESC["• Red/Black 색상 규칙
    • 느슨한 균형
    • 삽입/삭제 시 회전 적음"]
    style RB_DESC text-align:left

    T --- T_DESC
    BT --- BT_DESC
    BST --- BST_DESC
    AVL --- AVL_DESC
    RB --- RB_DESC

    style T fill:#f9f,stroke:#333,stroke-width:4px
    style BT fill:#bbf,stroke:#333,stroke-width:4px
    style BST fill:#bfb,stroke:#333,stroke-width:4px
    style AVL fill:#fbb,stroke:#333,stroke-width:4px
    style RB fill:#fbf,stroke:#333,stroke-width:4px
```

# 트리 (Tree)

* 개념
    * **트리(Tree)**는 계층적(Hierarchical) 구조를 표현하는 자료구조로, **노드(Node)**가 서로 연결된 형태를 갖습니다.
    * 루트(Root) 노드로부터 시작하여 자식(Child) 노드들로 확장되고, 각 노드는 0개 이상의 자식을 가질 수 있습니다.
    * 사이클(Cycle)이 없는 무방향 그래프의 한 형태로 볼 수도 있습니다.

    <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/f/f7/Binary_tree.svg/330px-Binary_tree.svg.png" width="250" alt="트리 예시"/>

* 트리의 기본 용어
    1. 노드(Node)
        - 트리의 데이터를 저장하는 기본 단위
        - `value`(또는 `data`)와 자식에 대한 참조(링크)를 가짐

    2. 루트(Root) 노드
        - 트리의 시작점이 되는 노드
        - 부모가 없는 노드

    3. 부모(Parent) 노드와 자식(Child) 노드
        - 트리에서 연결된 두 노드 간 관계
        - 루트를 제외하면 모든 노드는 하나의 부모를 가짐

    4. 형제(Sibling)
        - 같은 부모 노드를 공유하는 노드들

    5. 잎(Leaf) 노드
        - 자식이 없는 노드
        - 트리의 가장 말단(끝) 노드

    6. 깊이(Depth) / 레벨(Level)
        - 루트 노드에서 특정 노드까지의 경로에 포함된 에지(간선) 수
        - 또는 계층 구조에서의 층 수

    7. 높이 (Height)
        - 루트 노드에서 잎 노드까지의 최대 깊이

    8. 서브 트리(Subtree)
        - 트리 내 임의의 노드를 루트로 하는 부분 트리

* 트리의 특성
    1. 계층적 구조
        - 루트 노드에서부터 아래 방향으로 확장

    2. 사이클이 없음 (Acyclic)
        - 한 노드를 다시 참조하는 순환 구조가 없음

    3. 연결성(Connectivity)
        - 모든 노드가 서로 연결되어 있어야 함

    4. 노드 수와 간선 수
        - 트리에 N개의 노드가 있으면, 간선(에지)은 N-1개

* 트리의 기본 연산
    1. 탐색(Traversal)
        - 트리 구조를 순회하면서 노드들에 접근
        - 대표 예: 전위/중위/후위 순회(이진 트리에서 많이 다룸), 레벨 순회 등

    2. 삽입(Insertion)
        - 트리에 새 노드를 추가
        - 어느 노드의 자식으로 삽입할지 결정 필요

    3. 삭제(Deletion)
        - 특정 노드를 제거
        - 해당 노드가 자식을 갖는다면 처리 방법(자식 승계, 하위 트리 삭제 등)을 고민해야 함.

    4. 검색(Search)
        - 특정 값(또는 조건)을 만족하는 노드를 찾음
        - 트리 순회로 구현 가능

* 트리의 분류
    1. 이진 트리 (Binary Tree)
        - 각 노드가 최대 2개의 자식을 가짐 (왼쪽 자식, 오른쪽 자식)
        - 자료구조로 많이 다루는 형태(이진 검색 트리, 힙 등)

    2. 다진 트리(Multi-way Tree)
        - 한 노드가 2개 이상의 자식을 가질 수 있음.
        - 예: 일반 트리(General Tree), N-ary 트리, K-ary 트리 등

    3. 이진 검색 트리 (Binary Search Tree, BST)
        - 왼쪽 자식이 현재 노드보다 작고, 오른쪽 자식이 현재 노드보다 큰 이진 트리
        - 빠른 검색, 삽입, 삭제(O(log n))를 기대할 수 있으나, 편향되면 O(n) 가능

    4. 균형 트리(AVL, Red-Black, B-Tree 등)
        - 노드 분포가 한쪽으로 치우치치 않도록 자체 균형 유지
        - 항상 O(log n)시간에 탐색/삽입/삭제 가능

* 간단한 트리 구현 예시
    1. Python: 일반 트리
        ```python
        class TreeNode:
            def __init__(self, val):
                self.val = val
                self.children = []  # 여러 자식을 가질 수 있는 일반 트리

        def add_child(parent: TreeNode, child: TreeNode):
            parent.children.append(child)

        def traverse(root: TreeNode):
            # 트리 순회 (전위 방식)
            print(root.val, end=' ')
            for c in root.children:
                traverse(c)

        # 사용 예시
        if __name__ == "__main__":
            # 루트 노드 생성
            root = TreeNode("A")
            # 자식 노드 생성
            b = TreeNode("B")
            c = TreeNode("C")
            d = TreeNode("D")
            # 구조 형성
            add_child(root, b)
            add_child(root, c)
            add_child(b, d)
            
            # 트리 순회
            traverse(root)  # A B D C (전위 순회)
        ```

* 트리 순회(Traversal) 기초
    1. 전위 순회(Preorder Traversal)
        1. 현재 노드 방문
        2. 왼쪽 서브트리 순회
        3. 오른쪽 서브트리 순회

    2. 중위 순회(Inorder Traversal)
        1. 왼쪽 서브트리 순회
        2. 현재 노드 방문
        3. 오른쪽 서브트리 순회
        - 이진 탐색 트리에서 중위 순회 시 정렬된 결과를 얻음.

    3. 후위 순회(Postorder Traversal)
        1. 왼쪽 서브트리 순회
        2. 오른쪽 서브트리 순회
        3. 현재 노드 방문

    4. 레벨 순회(Level-order Traversal)
        - 루트에서 시작, 같은 레벨의 노드를 왼쪽에서 오른쪽으로 방문
        - 큐(Queue)를 사용하여 구현

* 실용 사례
    1. 파일 시스템
        - 디렉토리(폴더)와 파일 구조를 트리 형태로 표현

    2. UI 컴포넌트 트리
        - 웹/모바일 UI는 트리 구조로 컴포넌트가 중첩

    3. 조직도
        - CEO(루트), 부서(자식), 직원(잎 노드)등 계층 구조

    4. XML/HTML DOM
        - 문서의 계층 구조를 트리로 파싱하여 관리

    5. 데이터베이스 인덱스(B-Tree / B+ Tree)
        - 대용량 데이터에서 빠른 검색을 위해 트리 구조 사용

    6. 그래프 알고리즘
        - 최소 신장 트리(MST), 루트 있는 트리, 파싱 트리, 결정 트리 등

* 장단점
    1. 장점
        - 계층 구조 표현에 뛰어남
        - 부모-자식 관계로 재귀적 구조
        - 검색, 삽입, 삭제 등 다양한 트리 기반 알고리즘에서 O(log n) 기대 (이진 검색 트리, 균형 트리 일 경우)

    2. 단점
        - 편향(Skewed) 트리의 경우, 성능(탐색/삽입/삭제)이 O(n)에 근접
        - 구현과 메모리 관리(포인터/링크 관리)가 배열만큼 간단하지 않을 수 있음
        - 중간 노드 삭제 시, 서브트리를 어떻게 연결할지 추가 로직 필요

* 마무리
    - 트리는 루트부터 하위 노드로 이어지는 계층 구조를 표현하는 핵심 자료구조이며, 노드 간의 부모-자식 관계로 구성됩니다.
    - 디렉토리, 조직도, UI 구조, DB 인덱스 등 실제 시스템에서 계층적 정보를 다룰 때 폭넓게 사용됩니다.
    - 이진 트리, 이진 검색 트리, 균형 트리, 힙, 트라이(Trie)등 다양한 파생 구조가 있어, 상황에 따라 알맞은 트리 유형을 선택하게 됩니다.