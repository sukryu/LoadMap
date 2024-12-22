# 스택 (Stack)

1. 스택의 개념
    * 스택(Stack)은 데이터가 차곡차곡 쌓이는 형태의 자료구조로 LIFO(Last In First Out)원칙을 따릅니다. 즉, 마지막에 추가된 데이터가 가장 먼저 제거됩니다.

    * 일상 생활에서의 예시:
        * 접시 쌓기: 새로운 접시는 맨 위에 놓이고, 사용할 때도 맨 위의 접시부터 꺼냅니다.
        * 서류 더미: 새로운 서류를 맨 위에 놓이고, 처리할 때도 맨 위의 서류부터 처리합니다.

2. 스택의 연산
    * 스택은 기본적으로 다음과 같은 연산을 지원합니다.
        * `push(item)`: 스택의 맨 위에 `item`을 추가합니다.
        * `pop()`: 스택의 맨 위에 있는 아이템을 제거하고 반환합니다.
        * `peek()`: 스택의 맨 위에 있는 아이템을 반환하지만 제거하지는 않습니다.
        * `isEmpty()`: 스택이 비어 있는지 확인합니다.

3. 스택의 구현
    * 배열 기반의 스택 구현
        1. Python
           ```python
           class Stack:
                def __init__(self):
                    self.stack = []
            
                def push(self, item):
                    self.stack.append(item)
            
                def pop(self):
                    if not self.is_empty():
                        return self.stack.pop()
                    return None
            
                def peek(self):
                    if not self.is_empty():
                        return self.stack[-1]
                    return None
            
                def is_empty(self):
                    return len(self.stack) == 0
            
            # 사용 예제
            stack = Stack()
            stack.push(1)
            stack.push(2)
            stack.push(3)
            print(stack.pop())  # 출력: 3
            print(stack.peek())  # 출력: 2
           ```

        3. TypeScript
            ```typescript
            class ArrayStack<T> {
                private items: T[];
                private top: number;
                private readonly initialCapacity: number = 10;
                
                constructor() {
                    this.items = new Array<T>(this.initialCapacity);
                    this.top = -1;
                }
                
                push(item: T): void {
                    if (this.top === this.items.length - 1) {
                        this.resize();
                    }
                    this.items[++this.top] = item;
                }
                
                pop(): T | undefined {
                    if (this.isEmpty()) {
                        return undefined;
                    }
                    const item = this.items[this.top];
                    this.items[this.top--] = undefined!;
                    return item;
                }
                
                private resize(): void {
                    const newItems = new Array<T>(this.items.length * 2);
                    for (let i = 0; i < this.items.length; i++) {
                        newItems[i] = this.items[i];
                    }
                    this.items = newItems;
                }
                
                isEmpty(): boolean {
                    return this.top === -1;
                }
            }
            ```

        4. Golang
            ```go
            package stack

            type ArrayStack struct {
                items []interface{}
                top   int
            }

            func NewArrayStack() *ArrayStack {
                return &ArrayStack{
                    items: make([]interface{}, 0),
                    top:   -1,
                }
            }

            func (s *ArrayStack) Push(item interface{}) {
                s.items = append(s.items, item)
                s.top++
            }

            func (s *ArrayStack) Pop() interface{} {
                if s.IsEmpty() {
                    return nil
                }
                item := s.items[s.top]
                s.items = s.items[:s.top]
                s.top--
                return item
            }

            func (s *ArrayStack) IsEmpty() bool {
                return s.top == -1
            }
            ```

    * 연결 리스트 기반의 스택 구현
        1. Java
            ```java
            public class LinkedStack<T> {
                private class Node {
                    T data;
                    Node next;
                    
                    Node(T data) {
                        this.data = data;
                    }
                }
                
                private Node top;
                private int size;
                
                public void push(T item) {
                    Node newNode = new Node(item);
                    newNode.next = top;
                    top = newNode;
                    size++;
                }
                
                public T pop() {
                    if (isEmpty()) {
                        throw new IllegalStateException("Stack is empty");
                    }
                    T item = top.data;
                    top = top.next;
                    size--;
                    return item;
                }
                
                public boolean isEmpty() {
                    return top == null;
                }
                
                public int size() {
                    return size;
                }
            }
            ```

        2. TypeScript
            ```typescript
            class LinkedStack<T> {
                private class Node {
                    data: T;
                    next: Node | null;
                    
                    constructor(data: T) {
                        this.data = data;
                        this.next = null;
                    }
                }
                
                private top: Node | null = null;
                private size: number = 0;
                
                push(item: T): void {
                    const newNode = new Node(item);
                    newNode.next = this.top;
                    this.top = newNode;
                    this.size++;
                }
                
                pop(): T | undefined {
                    if (this.isEmpty()) {
                        return undefined;
                    }
                    const item = this.top!.data;
                    this.top = this.top!.next;
                    this.size--;
                    return item;
                }
                
                isEmpty(): boolean {
                    return this.top === null;
                }
                
                getSize(): number {
                    return this.size;
                }
            }
            ```

        3. Golang
            ```go
            type Node struct {
                data interface{}
                next *Node
            }

            type LinkedStack struct {
                top  *Node
                size int
            }

            func NewLinkedStack() *LinkedStack {
                return &LinkedStack{}
            }

            func (s *LinkedStack) Push(item interface{}) {
                newNode := &Node{data: item}
                newNode.next = s.top
                s.top = newNode
                s.size++
            }

            func (s *LinkedStack) Pop() interface{} {
                if s.IsEmpty() {
                    return nil
                }
                item := s.top.data
                s.top = s.top.next
                s.size--
                return item
            }

            func (s *LinkedStack) IsEmpty() bool {
                return s.top == nil
            }

            func (s *LinkedStack) Size() int {
                return s.size
            }
            ```

4. 스택의 사용 사례
    * 재귀 알고리즘
        * 재귀 알고리즘 호출 시 함수 호출 스택이 사용됩니다. 각 함수 호출은 스택 프레임에 저장되며, 함수가 종료되면 스택에서 제거됩니다.

        * 예제: 재귀함수
            ```python
            def recursive(data):
                if data < 0:
                    print('ended')
                else:
                    print(data)
                    recursive(data - 1)
                    print('returned', data)

            recursive(3)
            ```
            * 출력 결과:
                ```bash
                3
                2
                1
                0
                ended
                returned 0
                returned 1
                returned 2
                returned 3
                ```

    * 웹 브라우저의 방문 기록
        * 뒤로 가기: 방문한 페이지들을 스택에 저장하여 이전 페이지로 돌아갈 수 있습니다.
        * 언어별 구현
            1. Java
                ```java
                public class BrowserHistory {
                    private Stack<String> backStack = new Stack<>();
                    private Stack<String> forwardStack = new Stack<>();
                    
                    public void visit(String url) {
                        backStack.push(url);
                        forwardStack.clear(); // 새로운 페이지 방문 시 forward 기록 삭제
                    }
                    
                    public String back() {
                        if (backStack.size() <= 1) return backStack.peek();
                        
                        forwardStack.push(backStack.pop());
                        return backStack.peek();
                    }
                    
                    public String forward() {
                        if (forwardStack.isEmpty()) return backStack.peek();
                        
                        String url = forwardStack.pop();
                        backStack.push(url);
                        return url;
                    }
                }
                ```

            2. TypeScript
                ```typescript
                class BrowserHistory {
                    private backStack: string[] = [];
                    private forwardStack: string[] = [];
                    
                    visit(url: string): void {
                        this.backStack.push(url);
                        this.forwardStack = [];
                    }
                    
                    back(): string | undefined {
                        if (this.backStack.length <= 1) return this.backStack[this.backStack.length - 1];
                        
                        const current = this.backStack.pop()!;
                        this.forwardStack.push(current);
                        return this.backStack[this.backStack.length - 1];
                    }
                    
                    forward(): string | undefined {
                        if (this.forwardStack.length === 0) return this.backStack[this.backStack.length - 1];
                        
                        const url = this.forwardStack.pop()!;
                        this.backStack.push(url);
                        return url;
                    }
                }
                ```

            3. Golang
                ```go
                type BrowserHistory struct {
                    backStack    []string
                    forwardStack []string
                }

                func NewBrowserHistory() *BrowserHistory {
                    return &BrowserHistory{
                        backStack:    make([]string, 0),
                        forwardStack: make([]string, 0),
                    }
                }

                func (bh *BrowserHistory) Visit(url string) {
                    bh.backStack = append(bh.backStack, url)
                    bh.forwardStack = make([]string, 0)
                }

                func (bh *BrowserHistory) Back() string {
                    if len(bh.backStack) <= 1 {
                        return bh.backStack[len(bh.backStack)-1]
                    }
                    
                    current := bh.backStack[len(bh.backStack)-1]
                    bh.backStack = bh.backStack[:len(bh.backStack)-1]
                    bh.forwardStack = append(bh.forwardStack, current)
                    return bh.backStack[len(bh.backStack)-1]
                }
                ```
    * 실행 취소 기능
        * Undo 기능: 사용자 동작을 스택에 저장하여 이전 상태로 복구할 수 있습니다.
        * 언어별 구현
            1. java
                ```java
                public class UndoManager<T> {
                    private Stack<T> undoStack = new Stack<>();
                    private Stack<T> redoStack = new Stack<>();
                    
                    public void doAction(T action) {
                        undoStack.push(action);
                        redoStack.clear();
                    }
                    
                    public T undo() {
                        if (undoStack.isEmpty()) {
                            throw new IllegalStateException("No actions to undo");
                        }
                        T action = undoStack.pop();
                        redoStack.push(action);
                        return action;
                    }
                    
                    public T redo() {
                        if (redoStack.isEmpty()) {
                            throw new IllegalStateException("No actions to redo");
                        }
                        T action = redoStack.pop();
                        undoStack.push(action);
                        return action;
                    }
                }
                ```

            2. TypeScript
                ```typescript
                class UndoManager<T> {
                    private undoStack: T[] = [];
                    private redoStack: T[] = [];
                    
                    doAction(action: T): void {
                        this.undoStack.push(action);
                        this.redoStack = [];
                    }
                    
                    undo(): T | undefined {
                        if (this.undoStack.length === 0) {
                            throw new Error("No actions to undo");
                        }
                        const action = this.undoStack.pop()!;
                        this.redoStack.push(action);
                        return action;
                    }
                    
                    redo(): T | undefined {
                        if (this.redoStack.length === 0) {
                            throw new Error("No actions to redo");
                        }
                        const action = this.redoStack.pop()!;
                        this.undoStack.push(action);
                        return action;
                    }
                }
                ```

            3. Golang
                ```go
                type UndoManager struct {
                    undoStack []interface{}
                    redoStack []interface{}
                }

                func NewUndoManager() *UndoManager {
                    return &UndoManager{
                        undoStack: make([]interface{}, 0),
                        redoStack: make([]interface{}, 0),
                    }
                }

                func (um *UndoManager) DoAction(action interface{}) {
                    um.undoStack = append(um.undoStack, action)
                    um.redoStack = make([]interface{}, 0)
                }

                func (um *UndoManager) Undo() interface{} {
                    if len(um.undoStack) == 0 {
                        return nil
                    }
                    
                    action := um.undoStack[len(um.undoStack)-1]
                    um.undoStack = um.undoStack[:len(um.undoStack)-1]
                    um.redoStack = append(um.redoStack, action)
                    return action
                }
                ```
    * 수식의 괄호 검사
        * 괄호 짝 맞추기: 여는 괄호를 스택에 저장하고, 닫는 괄호를 만나면 스택에서 꺼내어 짝이 맞는지 확인합니다.
        * 언어별 구현
            1. Java
                ```java
                public class BracketChecker {
                    public boolean isValid(String s) {
                        Stack<Character> stack = new Stack<>();
                        Map<Character, Character> brackets = Map.of(
                            ')', '(',
                            '}', '{',
                            ']', '['
                        );
                        
                        for (char c : s.toCharArray()) {
                            if (brackets.containsValue(c)) {
                                stack.push(c);
                            } else if (brackets.containsKey(c)) {
                                if (stack.isEmpty() || stack.pop() != brackets.get(c)) {
                                    return false;
                                }
                            }
                        }
                        
                        return stack.isEmpty();
                    }
                }
                ```

            2. TypeScript
                ```typescript
                class BracketChecker {
                    isValid(s: string): boolean {
                        const stack: string[] = [];
                        const brackets: Map<string, string> = new Map([
                            [')', '('],
                            ['}', '{'],
                            [']', '[']
                        ]);
                        
                        for (const char of s) {
                            if (['{', '[', '('].includes(char)) {
                                stack.push(char);
                            } else if (brackets.has(char)) {
                                if (stack.length === 0 || stack.pop() !== brackets.get(char)) {
                                    return false;
                                }
                            }
                        }
                        
                        return stack.length === 0;
                    }
                }
                ```

            3. Golang
                ```go
                func isValid(s string) bool {
                    stack := make([]rune, 0)
                    brackets := map[rune]rune{
                        ')': '(',
                        '}': '{',
                        ']': '[',
                    }
                    
                    for _, char := range s {
                        if char == '(' || char == '{' || char == '[' {
                            stack = append(stack, char)
                        } else if opening, exists := brackets[char]; exists {
                            if len(stack) == 0 || stack[len(stack)-1] != opening {
                                return false
                            }
                            stack = stack[:len(stack)-1]
                        }
                    }
                    
                    return len(stack) == 0
                }
                ```
    * 후위 표기법 계산
        * 표현식 평가: 연산자와 피연산자를 스택에 저장하여 후위 표기식을 계산합니다.

5. 스택의 장점과 단점
    * 장점
        * 간단한 구현: 구조가 단순하여 구현이 쉽습니다.
        * 데이터 역순 처리: 후입선출이 필요한 상황에서 유용합니다.
        * 메모리 효율성: 연속된 메모리 공간을 사용하여 캐시 적중률이 높습니다.

    * 단점
        * 임의 접근 불가: 중간에 있는 요소에 직접 접근할 수 없습니다.
        * 크기 제한: 고정 크기의 스택은 오버플로우 위험이 있습니다.
        * 오버플로우/언더플로우: 스택이 가득 찼거나 비었을 떄 오류가 발생할 수 있습니다.

6. 심화 내용
    * 스택 오버플로우와 언더플로우
        * 스택 오버플로우(Stack Overflow): 스택이 가득 찬 상태에서 `push`연산을 수행하면 발생합니다.
        * 스택 언더플로우(Stack Underflow): 스택이 비어 있는데 `pop`연산을 수행하면 발생합니다.

        - 예외처리 예제:

    * 스택을 이용한 알고리즘 문제
        * 예제: DFS(깊이 우선 탐색)
        * 언어별 구현
            1. Java
                ```java
                public class DFS {
                    public void dfs(Graph graph, int start) {
                        boolean[] visited = new boolean[graph.V];
                        Stack<Integer> stack = new Stack<>();
                        
                        stack.push(start);
                        
                        while (!stack.isEmpty()) {
                            int vertex = stack.pop();
                            
                            if (!visited[vertex]) {
                                visited[vertex] = true;
                                System.out.print(vertex + " ");
                                
                                for (int adj : graph.getAdjacent(vertex)) {
                                    if (!visited[adj]) {
                                        stack.push(adj);
                                    }
                                }
                            }
                        }
                    }
                }
                ```

            2. TypeScript
                ```typescript
                class DFS {
                    dfs(graph: Map<number, number[]>, start: number): void {
                        const visited = new Set<number>();
                        const stack: number[] = [];
                        
                        stack.push(start);
                        
                        while (stack.length > 0) {
                            const vertex = stack.pop()!;
                            
                            if (!visited.has(vertex)) {
                                visited.add(vertex);
                                console.log(vertex);
                                
                                const adjacent = graph.get(vertex) || [];
                                for (const adj of adjacent) {
                                    if (!visited.has(adj)) {
                                        stack.push(adj);
                                    }
                                }
                            }
                        }
                    }
                }
                ```

            3. Golang
                ```go
                type Graph struct {
                    vertices map[int][]int
                }

                func NewGraph() *Graph {
                    return &Graph{
                        vertices: make(map[int][]int),
                    }
                }

                func (g *Graph) DFS(start int) {
                    visited := make(map[int]bool)
                    stack := []int{start}
                    
                    for len(stack) > 0 {
                        vertex := stack[len(stack)-1]
                        stack = stack[:len(stack)-1]
                        
                        if !visited[vertex] {
                            visited[vertex] = true
                            fmt.Printf("%d ", vertex)
                            
                            for _, adj := range g.vertices[vertex] {
                                if !visited[adj] {
                                    stack = append(stack, adj)
                                }
                            }
                        }
                    }
                }
                ```
7. 정리
    * 스택은 단순하지만 강력한 자료구조로, 다양한 분야에서 활용됩니다. 스택의 기본 원리인 LIFO는 많은 알고리즘과 시스템에서
    핵심적인 역할을 합니다.

    * 핵심 개념: LIFO(Last In First Out)
    * 주요 사용 사례: 재귀 호출, 실행 취소 기능, 수식 계산, 괄호 검사 등
    * 장점: 간단한 구현, 역순 처리에 용이
    * 단점: 임의 접근 불가, 크기 제한