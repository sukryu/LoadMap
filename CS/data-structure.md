# 데이터 구조 #

## Array ##

- 이론:
    - 배열은 동일한 타입의 요소들을 연속적인 메모리 공간에 저장하는 데이터 구조입니다. 배열의 특징은 다음과 같습니다.

        - 인덱스를 사용하여 요소에 접근 (0부터 시작)
        - 고정된 크기: 선언 시 크기가 정해지며 변경 불가
        - 빠른 접근 속도: O(1) 시간 복잡도로 임의의 요소에 접근 가능

    - C로 구현
    ```c
    #include <stdio.h>

    int main() {
        // 크기가 5인 정수형 배열 선언
        int arr[5] = {1, 2, 3, 4, 5};

        // 배열 요소 접근 및 출력
        for(int i = 0; i < 5; i++) {
            printf("arr[%d] = %d\n", i, arr[i]);
        }

        return 0;
    }
    ```

    - 주의사항:
        - 배열의 인덱스 범위를 벗어나 접근하면 **정의되지 않은 동작(Undifined Behavior)**이 발생합니다.
        - 배열의 크기는 컴파일 타임에 결정됩니다.

## 링크드 리스트 (Linked List)

- 이론:
    - 링크드 리스트는 각 요소가 데이터와 다음 노드를 가리키는 포인터를 가지는 노드들의 집합입니다. 특징은 다음과 같습니다:
        
        - 동적 크기: 노드의 추가 및 삭제로 크기 변경 가능
        - 연속적이지 않은 메모리 배치: 노드들이 메모리상에 흩어져 있음
        - 노드 접근 시간: 특정 위치의 노드에 접근하려면 처음부터 순회 필요 O(n)

    - C로 구현

        - 노드 구조체 정의
        ```c
        #include <stdio.h>
        #include <stdlib.h>

        // 노드 구조체 정의
        typedef struct Node {
            int data;
            struct Node* next;
        } Node;

        ```

        - 노드 생성 함수
        ```c
        Node* createNode(int data) {
            Node* newNode = (Node*)malloc(sizeof(Node));
            if (!newNode) {
                printf("메모리 할당 실패\n");
                exit(1);
            }
            newNode->data = data;
            newNode->next = NULL;
            return newNode;
        }
        ```

        - 리스트에 노드 추가
        ```c
        void appendNode(Node** headRef, int data) {
            Node* newNode = createNode(data);
            if (*headRef == NULL) {
                *headRef = newNode;
                return;
            }

            Node* temp = *headRef;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newNode;
        }
        ```

        - 리스트 출력 함수
        ```c
        void printList(Node* head) {
            Node* temp = head;
            while (temp != NULL) {
                printf("%d -> ", temp->data);
                temp = temp->next;
            }
            printf("NULL\n");
        }
        ```

        - 메인 함수
        ```c
        int main() {
            Node* head = NULL;

            // 노드 추가
            appendNode(&head, 10);
            appendNode(&head, 20);
            appendNode(&head, 30);

            // 리스트 출력
            printList(head);

            return 0;
        }
        ```

    - 메모리 관리:
        - 동적 메모리를 할당했으므로 사용 후 `free()`함수를 통해 해제해야 합니다.

## 스택 (Stack) ##

- 이론:
    - 스택은 후입선출(LIFO, Last In First Out) 방식의 자료 구조입니다. 주요 연산은 다음과 같습니다.

        - push: 스택의 맨 위에 요소 추가
        - pop: 스택의 맨 위 요소 제거 및 반환
        - peek: 스택의 맨 위 요소 확인

    - C로 구현
        - 배열을 이용한 스택 구현:

        - 상수 및 전역 변수 정의
        ```c
        #define MAX_SIZE 100

        int stack[MAX_SIZE];
        int top = -1;
        ```

        - 스택 연산 함수들
        ```c
        // 요소 추가
        void push(int data) {
            if (top >= MAX_SIZE - 1) {
                printf("스택 오버플로우\n");
                return;
            }
            stack[++top] = data;
        }

        // 요소 제거
        int pop() {
            if (top < 0) {
                printf("스택 언더플로우\n");
                return -1;
            }
            return stack[top--];
        }

        // 맨 위 요소 확인
        int peek() {
            if (top < 0) {
                printf("스택이 비어있습니다\n");
                return -1;
            }
            return stack[top];
        }
        ```

        - 메인 함수
        ```c
        int main() {
            push(10);
            push(20);
            push(30);

            printf("Top element is %d\n", peek());

            printf("Popped element is %d\n", pop());
            printf("Popped element is %d\n", pop());

            return 0;
        }
        ```
    - 연결 리스트를 이용한 스택 구현도 가능합니다.

## 큐(Queue) ##

- 이론:
    - 큐는 선입선출(FIFO, First In First Out) 방식의 자료구조입니다. 주요 연산은 다음과 같습니다.

        - enqueue: 큐의 뒤에 요소 추가
        - dequeue: 큐의 앞에서 요소 제거 및 반환
        - front: 큐의 앞 요소 확인

    - C로 구현
        - 배열을 이용한 큐 구현(순환 큐 방식)

        - 상수 및 전역변수 정의
        ```c
        #define MAX_SIZE 100

        int queue[MAX_SIZE];
        int front = 0;
        int rear = 0;
        ```

        - 큐 연산 함수들
        ```c
        // 요소 추가
        void enqueue(int data) {
            if ((rear + 1) % MAX_SIZE == front) {
                printf("큐가 가득 찼습니다\n");
                return;
            }
            queue[rear] = data;
            rear = (rear + 1) % MAX_SIZE;
        }

        // 요소 제거
        int dequeue() {
            if (front == rear) {
                printf("큐가 비어있습니다\n");
                return -1;
            }
            int data = queue[front];
            front = (front + 1) % MAX_SIZE;
            return data;
        }

        // 앞 요소 확인
        int getFront() {
            if (front == rear) {
                printf("큐가 비어있습니다\n");
                return -1;
            }
            return queue[front];
        }
        ```

        - 메인 함수
        ```c
        int main() {
            enqueue(10);
            enqueue(20);
            enqueue(30);

            printf("Front element is %d\n", getFront());

            printf("Dequeued element is %d\n", dequeue());
            printf("Dequeued element is %d\n", dequeue());

            return 0;
        }
        ```
    - 연결 리스트를 이용한 큐 구현도 가능합니다.

## 트리 (Tree) ##

- 이론:
    - 트리는 계층적인 데이터를 표현하는 비선형 자료구조입니다. 이진 트리는 각 노드가 최대 두 개의 자식을 가지는 트리입니다.

        - 루트 노드: 트리의 시작 노드
        - 리프 노드: 자식이 없는 노드
        - 서브트리: 노드와 그 자식들로 이루어진 트리

    - C로 구현
        
        - 노드 구조체 정의
        ```c
        typedef struct TreeNode {
            int data;
            struct TreeNode* left;
            struct TreeNode* right;
        } TreeNode;
        ```

        - 노드 생성 함수
        ```c
        TreeNode* createTreeNode(int data) {
            TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
            if (!newNode) {
                printf("메모리 할당 실패\n");
                exit(1);
            }
            newNode->data = data;
            newNode->left = NULL;
            newNode->right = NULL;
            return newNode;
        }
        ```

        - 트리 순회 방법
            - 전위 순회 (Pre-order): Root -> Left -> Right
            - 중위 순회 (In-order): Left -> Root -> Right
            - 후위 순회 (Post-order): Left -> Right -> Root

        - 전위 순회 함수
        ```c
        void preorderTraversal(TreeNode* root) {
            if (root == NULL)
                return;
            printf("%d ", root->data);
            preorderTraversal(root->left);
            preorderTraversal(root->right);
        }
        ```

        - 메인 함수
        ```c
        int main() {
            // 트리 생성
            TreeNode* root = createTreeNode(1);
            root->left = createTreeNode(2);
            root->right = createTreeNode(3);
            root->left->left = createTreeNode(4);
            root->left->right = createTreeNode(5);

            // 전위 순회 출력
            printf("Pre-order Traversal: ");
            preorderTraversal(root);
            printf("\n");

            return 0;
        }
        ```

    - 메모리 관리:
        - 트리를 사용한 후에는 각 노드를 `free()`를 통해 메모리를 해제해야 합니다.

## 그래프 (Graph) ##

- 이론:
    - 그래프는 **정점(Vertex)**과 **간선(Edge)**으로 이루어진 데이터 구조로, 복잡한 관계를 표현합니다.

        - 방향 그래프: 간선에 방향이 있는 그래프
        - 무방향 그래프: 간선에 방향이 없는 그래프
        - 인접 리스트와 인접 행렬로 그래프를 표현

    - C로 구현
        - 인접 리스트를 이용한 그래프 구현

        - 정점 구조체 정의
        ```c
        typedef struct AdjListNode {
            int dest;
            struct AdjListNode* next;
        } AdjListNode;
        ```

        - 인접 리스트 구조체 정의
        ```c
        typedef struct AdjList {
            AdjListNode* head;
        } AdjList;
        ```

        - 그래프 구조체 정의
        ```c
        typedef struct Graph {
            int V; // 정점의 개수
            AdjList* array;
        } Graph;
        ```

        - 그래프 생성 함수
        ```c
        Graph* createGraph(int V) {
            Graph* graph = (Graph*)malloc(sizeof(Graph));
            graph->V = V;

            // 인접 리스트 배열 생성
            graph->array = (AdjList*)malloc(V * sizeof(AdjList));

            for (int i = 0; i < V; ++i)
                graph->array[i].head = NULL;

            return graph;
        }
        ```
        
        - 새로운 인접 리스트 생성
        ```c
        AdjListNode* newAdjListNode(int dest) {
            AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
            newNode->dest = dest;
            newNode->next = NULL;
            return newNode;
        }
        ```

        - 간선 추가 함수
        ```c
        void addEdge(Graph* graph, int src, int dest) {
            // src -> dest 추가
            AdjListNode* newNode = newAdjListNode(dest);
            newNode->next = graph->array[src].head;
            graph->array[src].head = newNode;

            // 무방향 그래프라면 dest -> src 추가
            newNode = newAdjListNode(src);
            newNode->next = graph->array[dest].head;
            graph->array[dest].head = newNode;
        }
        ```

        - 그래프 출력 함수
        ```c
        void printGraph(Graph* graph) {
            for (int v = 0; v < graph->V; ++v) {
                AdjListNode* pCrawl = graph->array[v].head;
                printf("\n 정점 %d의 인접 리스트\n head ", v);
                while (pCrawl) {
                    printf("-> %d", pCrawl->dest);
                    pCrawl = pCrawl->next;
                }
                printf("\n");
            }
        }
        ```

        - 메인 함수
        ```c
        int main() {
            int V = 5;
            Graph* graph = createGraph(V);

            addEdge(graph, 0, 1);
            addEdge(graph, 0, 4);
            addEdge(graph, 1, 2);
            addEdge(graph, 1, 3);
            addEdge(graph, 1, 4);
            addEdge(graph, 2, 3);
            addEdge(graph, 3, 4);

            printGraph(graph);

            return 0;
        }
        ```

## 해시 테이블 (Hash Table) ##

- 이론:
    - 해시 테이블은 키(key)를 해시 함수(hash function)에 입력하여 해시 값(hash value)를 얻고, 이를 인덱스로 사용하여 데이터를 저장하는 자료 구조입니다.

        - 해시 함수: 임의의 길이의 데이터를 고정 길이의 데이터로 매핑하는 함수
        - 충돌 처리: 서로 다른 키가 동일한 해시 값을 가질 때 처리 방법 (예: 체이닝, 오픈 어드레싱)

    - C로 구현
        - 간단한 체이닝을 이용한 해시 테이블 구현

        - 상수 정의
        ```c
        #define TABLE_SIZE 10
        ```

        - 노드 구조체 정의
        ```c
        typedef struct HashNode {
            int key;
            int value;
            struct HashNode* next;
        } HashNode;
        ```

        - 해시 테이블 배열 정의
        ```c
        HashNode* hashTable[TABLE_SIZE] = { NULL };
        ```

        - 해시 함수
        ```c
        int hashFunction(int key) {
            return key % TABLE_SIZE;
        }
        ```

        - 데이터 삽입 함수
        ```c
        void insert(int key, int value) {
            int hashIndex = hashFunction(key);
            HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
            if (!newNode) {
                printf("메모리 할당 실패\n");
                return;
            }
            newNode->key = key;
            newNode->value = value;
            newNode->next = NULL;

            if (hashTable[hashIndex] == NULL) {
                hashTable[hashIndex] = newNode;
            } else {
                // 체이닝
                HashNode* temp = hashTable[hashIndex];
                while (temp->next)
                    temp = temp->next;
                temp->next = newNode;
            }
        }
        ```

        - 데이터 검색 함수
        ```c
        int search(int key) {
            int hashIndex = hashFunction(key);
            HashNode* temp = hashTable[hashIndex];
            while (temp) {
                if (temp->key == key)
                    return temp->value;
                temp = temp->next;
            }
            return -1; // 찾지 못한 경우
        }
        ```

        - 메인 함수
        ```c
        int main() {
            insert(1, 10);
            insert(11, 20);
            insert(21, 30);

            printf("Key: 1, Value: %d\n", search(1));
            printf("Key: 11, Value: %d\n", search(11));
            printf("Key: 21, Value: %d\n", search(21));

            return 0;
        }
        ```

## 힙 (Heap) ##

- 이론:
    - 힙은 완전 이진 트리의 일종으로, 부모의 노드의 키 값이 자식 노드의 키 값보다 항상 크거나(최대 힙) 작아야(최소 힙)하는 특정을 가집니다.

        - 최대 힙: 부모 노드 >= 자식 노드
        - 최소 힙: 부모 노드 <= 자식 노드

    - 힙은 주로 우선순위 큐를 구현하는 데 사용됩니다.

    - C로 구현
        - 배열을 이용한 최대 힙 구현:

        - 상수 및 전역 변수 정의
        ```c
        #define MAX_HEAP_SIZE 100

        int heap[MAX_HEAP_SIZE];
        int heapSize = 0;
        ```

        - 삽입 함수
        ```c
        void insertHeap(int data) {
            int i = ++heapSize;

            // 새로운 노드가 삽입될 위치를 찾음
            while (i != 1 && data > heap[i / 2]) {
                heap[i] = heap[i / 2];
                i /= 2;
            }
            heap[i] = data;
        }
        ```

        - 삭제 함수
        ```c
        int deleteHeap() {
            if (heapSize == 0) {
                printf("힙이 비어있습니다\n");
                return -1;
            }

            int root = heap[1];
            int temp = heap[heapSize--];
            int parent = 1;
            int child = 2;

            while (child <= heapSize) {
                // 두 자식 중 더 큰 자식을 선택
                if (child < heapSize && heap[child] < heap[child + 1])
                    child++;

                if (temp >= heap[child])
                    break;

                heap[parent] = heap[child];
                parent = child;
                child *= 2;
            }

            heap[parent] = temp;
            return root;
        }
        ```

        - 메인 함수
        ```c
        int main() {
            insertHeap(10);
            insertHeap(40);
            insertHeap(30);
            insertHeap(50);
            insertHeap(20);

            printf("Deleted: %d\n", deleteHeap());
            printf("Deleted: %d\n", deleteHeap());

            return 0;
        }
        ```