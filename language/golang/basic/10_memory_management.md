# 09. Go 메모리 관리와 기본 데이터 구조 (Memory Management and Data Structures)

## 1. Go의 메모리 관리 개요

Go는 **가비지 컬렉션(Garbage Collection, GC)**을 통해 메모리를 자동으로 관리합니다. 하지만 개발자가 효율적인 메모리 사용을 위해 특정 원칙을 이해하는 것이 중요합니다.

### 1.1 스택(Stack)과 힙(Heap)
- **스택(Stack)**: 함수 호출 시 지역 변수와 반환 주소가 저장되는 메모리 공간. 빠르게 할당 및 해제됨.
- **힙(Heap)**: 동적으로 할당된 메모리 공간으로, 명확한 해제 시점이 없으며 GC에 의해 관리됨.

### 1.2 메모리 할당 방식
- `var` 또는 지역 변수 → **스택 할당** (GC 부담 없음)
- `new()` 또는 `make()` → **힙 할당** (GC 관리 필요)

#### 예제: 스택과 힙 메모리 할당
```go
package main
import "fmt"

type Person struct {
    Name string
    Age  int
}

func main() {
    // 스택 메모리 할당 (함수 종료 시 해제됨)
    x := 10
    fmt.Println("Stack allocated:", x)
    
    // 힙 메모리 할당 (GC에 의해 해제됨)
    p := new(Person)
    p.Name = "Alice"
    p.Age = 25
    fmt.Println("Heap allocated:", p)
}
```

---

## 2. 가비지 컬렉션(GC)

Go의 가비지 컬렉터는 자동으로 메모리를 회수하지만, 개발자는 다음 사항을 고려하여 메모리 사용을 최적화해야 합니다.

### 2.1 가비지 컬렉션 작동 방식
- **Mark & Sweep** 방식 사용
- 객체가 참조되지 않으면 메모리에서 제거됨
- 주기적으로 실행되며, 실행 시 CPU 및 메모리 사용량 증가 가능

### 2.2 GC 최적화 기법
- **메모리 재사용**: `sync.Pool`을 사용하여 객체를 재사용 가능
- **큰 객체는 피하기**: 힙 할당이 많아지면 GC 부담 증가
- **메모리 누수 감지**: `pprof` 패키지를 활용한 성능 분석

#### 예제: `sync.Pool`을 활용한 객체 재사용
```go
package main
import (
    "fmt"
    "sync"
)

var pool = sync.Pool{
    New: func() interface{} {
        return new(Person)
    },
}

type Person struct {
    Name string
    Age  int
}

func main() {
    p1 := pool.Get().(*Person)
    p1.Name = "Alice"
    p1.Age = 25
    fmt.Println("From Pool:", p1)
    pool.Put(p1) // 객체 반환
}
```

> `sync.Pool`을 활용하면 메모리 할당 비용을 줄일 수 있음.

---

## 3. 기본 데이터 구조

### 3.1 배열 (Array)
배열은 고정된 크기의 데이터 컨테이너로, 선언 시 크기를 지정해야 합니다.
```go
var arr [5]int // 정수형 배열 (크기 5)
```

#### 배열 초기화 및 접근
```go
arr := [3]int{1, 2, 3}
fmt.Println(arr[0]) // 1
```

> 배열은 크기가 고정되므로 동적으로 크기를 조절할 수 없음.

---

### 3.2 슬라이스 (Slice)
슬라이스는 배열을 동적으로 관리할 수 있는 데이터 구조입니다.

#### 슬라이스 선언 및 초기화
```go
s := []int{1, 2, 3, 4}
fmt.Println(s)
```

#### 슬라이스 길이 및 용량
```go
s := make([]int, 5, 10) // 길이 5, 용량 10
fmt.Println(len(s), cap(s))
```

#### 슬라이스 추가 (`append`)
```go
s = append(s, 6)
fmt.Println(s)
```

---

### 3.3 맵 (Map)
맵은 키-값 쌍을 저장하는 해시 테이블 기반 자료구조입니다.

#### 맵 선언 및 초기화
```go
m := make(map[string]int)
m["Alice"] = 25
fmt.Println(m["Alice"]) // 25
```

#### 맵 요소 삭제
```go
delete(m, "Alice")
```

---

### 3.4 연결 리스트 (Linked List)
Go의 표준 라이브러리에서 `container/list` 패키지를 제공하여 연결 리스트를 지원합니다.

#### 리스트 사용 예제
```go
package main
import (
    "container/list"
    "fmt"
)

func main() {
    l := list.New()
    l.PushBack(10)
    l.PushBack(20)
    for e := l.Front(); e != nil; e = e.Next() {
        fmt.Println(e.Value)
    }
}
```

---

## 4. 성능 최적화를 위한 메모리 관리 기법

### 4.1 구조체 정렬 및 패딩 최적화
Go는 구조체의 필드를 정렬할 때 **메모리 패딩**을 적용합니다. 올바른 필드 정렬을 하면 메모리 사용량을 줄일 수 있습니다.

#### 예제: 비효율적인 구조체 (패딩 발생)
```go
type BadStruct struct {
    A int8  // 1바이트
    B int64 // 8바이트 (패딩 발생)
}
```

#### 예제: 최적화된 구조체
```go
type GoodStruct struct {
    B int64 // 큰 타입을 먼저 배치
    A int8
}
```

### 4.2 Zero-copy 기법 활용
Go에서는 **메모리 복사를 최소화하는 기법**을 사용할 수 있습니다.

#### `strings.Builder`를 활용한 문자열 결합 최적화
```go
package main
import (
    "fmt"
    "strings"
)

func main() {
    var sb strings.Builder
    sb.WriteString("Hello, ")
    sb.WriteString("World!")
    fmt.Println(sb.String())
}
```

> `+` 연산자 대신 `strings.Builder`를 사용하면 메모리 복사를 줄일 수 있습니다.

---

## 5. 결론

- **가비지 컬렉션(GC)**을 이해하고 최적화 기법(`sync.Pool` 등)을 활용해야 합니다.
- **슬라이스(Slice)와 맵(Map)**을 적절히 활용하여 메모리 사용을 최적화해야 합니다.
- **구조체 정렬과 패딩**을 고려하여 메모리 낭비를 방지해야 합니다.
- **Zero-copy 기법**을 적용하여 불필요한 메모리 복사를 줄일 수 있습니다.

다음으로 Go의 패키지와 모듈(Packages and Modules)에 대해 알아보겠습니다.

