# 17. Go 시간과 날짜 처리 (Time and Date)

## 1. `time` 패키지 기본

### 1.1 현재 시간 얻기
```go
now := time.Now()
fmt.Println(now)                // 2024-01-08 15:04:05.123456789 +0900 KST

// 시간 컴포넌트 접근
fmt.Println(now.Year())        // 2024
fmt.Println(now.Month())       // January
fmt.Println(now.Day())         // 8
fmt.Println(now.Hour())        // 15
fmt.Println(now.Minute())      // 4
fmt.Println(now.Second())      // 5
fmt.Println(now.Nanosecond()) // 123456789
```

### 1.2 시간 생성
```go
// 특정 시간 생성
t := time.Date(2024, time.January, 8, 15, 4, 5, 0, time.UTC)

// Unix 타임스탬프에서 생성
unix := time.Unix(1641600000, 0)

// 문자열에서 파싱
t, err := time.Parse("2006-01-02", "2024-01-08")

// 타임존 지정
loc, err := time.LoadLocation("Asia/Seoul")
t = time.Date(2024, time.January, 8, 15, 4, 5, 0, loc)
```

---

## 2. 시간 포맷팅과 파싱

### 2.1 시간 포맷팅
```go
now := time.Now()
fmt.Println(now.Format("2006-01-02 15:04:05")) // 2024-01-08 15:04:05
fmt.Println(now.Format(time.RFC3339))          // 2024-01-08T15:04:05Z07:00
```

### 2.2 시간 파싱
```go
t, err := time.Parse("2006-01-02", "2024-01-08")
loc, _ := time.LoadLocation("Asia/Seoul")
t, err = time.ParseInLocation("2006-01-02 15:04:05", "2024-01-08 15:04:05", loc)
```

---

## 3. 시간 연산

### 3.1 시간 더하기/빼기
```go
now := time.Now()
future := now.Add(24 * time.Hour)        // 1일 후
past := now.Add(-24 * time.Hour)         // 1일 전
future = now.AddDate(1, 0, 0)            // 1년 후
```

### 3.2 시간 비교
```go
now := time.Now()
future := now.Add(time.Hour)
fmt.Println(now.Before(future))          // true
fmt.Println(now.After(future))           // false
fmt.Println(now.Equal(future))           // false
```

---

## 4. 타이머와 시간 측정

### 4.1 타이머 사용
```go
timer := time.NewTimer(2 * time.Second)
<-timer.C    // 2초 대기
timer.Stop()
```

### 4.2 시간 측정
```go
start := time.Now()
// ... 작업 수행
elapsed := time.Since(start)
fmt.Printf("작업 소요 시간: %v\n", elapsed)
```

---

## 5. 난수 생성 (`math/rand` vs `crypto/rand`)

### 5.1 의사 난수 생성 (`math/rand`)
```go
rand.Seed(time.Now().UnixNano())
n := rand.Intn(100)        // 0-99 사이 정수
```

### 5.2 암호학적 난수 생성 (`crypto/rand`)
```go
b := make([]byte, 16)
_, err := rand.Read(b)
```

---

## 6. Best Practices

### 6.1 시간 처리
- **UTC로 저장하고 필요할 때 로컬 시간으로 변환**
- **시간 비교는 `Equal()` 메서드 사용**

### 6.2 타임존 관리
- 명시적인 타임존 지정 (`time.LoadLocation()` 활용)

### 6.3 성능 고려
- **반복문에서 `time.Now()` 호출 최소화**
- **타이머는 `Stop()`을 호출하여 메모리 해제**

---

## 7. 주의사항
- **시간 연산 시 윤년, 일광절약시간(DST) 고려**
- **시간 비교 시 `Equal()` 메서드를 사용하고 `==` 연산자 피하기**
- **타임존 변환 시 에러 처리 필수**
