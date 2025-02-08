# 21. Go 컨테이너와 자료구조 (Containers and Data Structures)

## 1. `container/heap`

### 1.1 기본 힙 구현
```go
type IntHeap []int

func (h IntHeap) Len() int           { return len(h) }
func (h IntHeap) Less(i, j int) bool { return h[i] < h[j] }
func (h IntHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }
func (h *IntHeap) Push(x interface{}) {
    *h = append(*h, x.(int))
}
func (h *IntHeap) Pop() interface{} {
    old := *h
    n := len(old)
    x := old[n-1]
    *h = old[0 : n-1]
    return x
}
```

### 1.2 우선순위 큐
```go
type Item struct {
    value    string
    priority int
    index    int
}

type PriorityQueue []*Item

func (pq PriorityQueue) Len() int { return len(pq) }
func (pq PriorityQueue) Less(i, j int) bool {
    return pq[i].priority > pq[j].priority
}
func (pq PriorityQueue) Swap(i, j int) {
    pq[i], pq[j] = pq[j], pq[i]
    pq[i].index = i
    pq[j].index = j
}
func (pq *PriorityQueue) Push(x interface{}) {
    item := x.(*Item)
    *pq = append(*pq, item)
}
func (pq *PriorityQueue) Pop() interface{} {
    old := *pq
    item := old[len(old)-1]
    *pq = old[:len(old)-1]
    return item
}
```

---

## 2. `container/list`

### 2.1 이중 연결 리스트
```go
func BasicList() {
    list := list.New()
    list.PushBack("first")
    list.PushFront("zero")
    list.PushBack("last")
    for e := list.Front(); e != nil; e = e.Next() {
        fmt.Println(e.Value)
    }
}
```

---

## 3. `container/ring`

### 3.1 원형 리스트
```go
func BasicRing() {
    r := ring.New(5)
    for i := 0; i < r.Len(); i++ {
        r.Value = i
        r = r.Next()
    }
    r.Do(func(p interface{}) {
        fmt.Println(p)
    })
}
```

---

## 4. 실용적인 예시

### 4.1 작업 큐 구현
```go
type Job struct {
    Priority int
    Data     interface{}
}

type JobQueue struct {
    queue PriorityQueue
}

func (jq *JobQueue) AddJob(priority int, data interface{}) {
    item := &Item{value: data, priority: priority}
    heap.Push(&jq.queue, item)
}
```

### 4.2 LRU 캐시 구현
```go
type LRUCache struct {
    capacity int
    cache    map[interface{}]*list.Element
    list     *list.List
}

func (c *LRUCache) Get(key interface{}) (interface{}, bool) {
    if element, exists := c.cache[key]; exists {
        c.list.MoveToFront(element)
        return element.Value.(*entry).value, true
    }
    return nil, false
}
```

---

## 5. 성능 고려사항

### 5.1 컨테이너 선택 가이드라인
```go
numbers := make([]int, 0, 10) // 슬라이스
linkedList := list.New()      // 리스트
circularBuffer := ring.New(5) // 링
priorityQueue := make(PriorityQueue, 0) // 힙
```

### 5.2 메모리 효율성
```go
type Pool struct {
    sync.Pool
}

func NewPool() *Pool {
    return &Pool{
        Pool: sync.Pool{
            New: func() interface{} {
                return list.New()
            },
        },
    }
}
```

---

## 6. Best Practices

### 6.1 컨테이너 선택
- 용도에 맞는 자료구조 선택
- 성능 요구사항 고려
- 메모리 사용량 고려

### 6.2 구현 패턴
- 인터페이스 구현 완성도 체크
- nil 포인터 처리
- 동시성 고려

### 6.3 성능 최적화
- 적절한 초기 용량 설정
- 메모리 재사용
- 불필요한 복사 방지

---

## 7. 주의사항
- 동시성 안정성 고려
- 메모리 누수 방지
- 순환 참조 주의
- 적절한 에러 처리

---

Go의 컨테이너 및 자료구조를 활용하여 효율적인 데이터 처리를 수행할 수 있습니다! 🚀

