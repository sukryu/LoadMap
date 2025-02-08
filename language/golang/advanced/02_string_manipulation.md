# 16. Go 문자열 처리 (String Manipulation)

## 1. `strings` 패키지 (문자열 조작)

### 1.1 문자열 검색
```go
str := "Hello, World!"

// 포함 여부 확인
fmt.Println(strings.Contains(str, "World"))      // true
fmt.Println(strings.ContainsAny(str, "abcd"))   // false
fmt.Println(strings.ContainsRune(str, 'H'))     // true

// 접두사/접미사 확인
fmt.Println(strings.HasPrefix(str, "Hello"))     // true
fmt.Println(strings.HasSuffix(str, "World!"))    // true

// 위치 찾기
fmt.Println(strings.Index(str, "World"))        // 7
fmt.Println(strings.LastIndex(str, "o"))        // 7
fmt.Println(strings.IndexRune(str, 'W'))        // 7
```

### 1.2 문자열 변환
```go
// 대소문자 변환
fmt.Println(strings.ToUpper("hello"))           // HELLO
fmt.Println(strings.ToLower("HELLO"))           // hello
fmt.Println(strings.Title("hello world"))       // Hello World

// 공백 및 특수문자 제거
fmt.Println(strings.TrimSpace(" hello "))       // "hello"
fmt.Println(strings.Trim("!!!hello!!!", "!"))   // "hello"
fmt.Println(strings.TrimLeft("!!!hello", "!"))  // "hello"
fmt.Println(strings.TrimRight("hello!!!", "!")) // "hello"

// 문자열 반복
fmt.Println(strings.Repeat("ha", 3))            // "hahaha"
```

### 1.3 문자열 분할과 결합
```go
// 문자열 분할
words := strings.Split("a,b,c", ",")            // ["a" "b" "c"]
lines := strings.Split("a\nb\nc", "\n")         // ["a" "b" "c"]
fields := strings.Fields("  a b  c  ")          // ["a" "b" "c"]

// 문자열 결합
joined := strings.Join([]string{"a", "b", "c"}, ",") // "a,b,c"

// 문자열 치환
replaced := strings.Replace("hello hello", "hello", "hi", 1)    // "hi hello"
replacedAll := strings.ReplaceAll("hello hello", "hello", "hi") // "hi hi"
```

---

## 2. `strconv` 패키지 (문자열과 숫자 변환)

### 2.1 문자열과 숫자 변환
```go
// 문자열 → 숫자
i, err := strconv.Atoi("123")              // string to int
f, err := strconv.ParseFloat("3.14", 64)   // string to float64
b, err := strconv.ParseBool("true")        // string to bool

// 숫자 → 문자열
s := strconv.Itoa(123)                     // int to string
s = strconv.FormatFloat(3.14, 'f', 2, 64)  // float64 to string
s = strconv.FormatBool(true)               // bool to string
```

### 2.2 진수 변환
```go
// 다양한 진수 변환
v, err := strconv.ParseInt("1010", 2, 64)  // 2진수 문자열 → 정수
v, err = strconv.ParseInt("ff", 16, 64)    // 16진수 문자열 → 정수

// 정수를 다양한 진수 문자열로 변환
s := strconv.FormatInt(10, 2)              // 2진수 문자열
s = strconv.FormatInt(255, 16)             // 16진수 문자열
```

---

## 3. `regexp` 패키지 (정규 표현식)

### 3.1 기본 정규표현식 사용
```go
// 정규표현식 컴파일
re := regexp.MustCompile(`\w+@\w+\.\w+`)

// 매칭 확인
fmt.Println(re.MatchString("test@example.com"))    // true
fmt.Println(re.MatchString("invalid"))             // false

// 첫 번째 매칭 찾기
match := re.FindString("contact: test@example.com") // "test@example.com"

// 모든 매칭 찾기
matches := re.FindAllString("a@b.com c@d.com", -1) // ["a@b.com" "c@d.com"]
```

### 3.2 정규표현식 그룹과 치환
```go
// 그룹 캡처
re := regexp.MustCompile(`(\w+):(\d+)`)
match := re.FindStringSubmatch("port:8080")
// match[0] = "port:8080", match[1] = "port", match[2] = "8080"

// 치환
re := regexp.MustCompile(`a+`)
result := re.ReplaceAllString("aaa bbb aaa", "x") // "x bbb x"
```

---

## 4. 실용적인 문자열 처리 예제

### 4.1 문자열 유효성 검사
```go
func isValidEmail(email string) bool {
    re := regexp.MustCompile(`^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$`)
    return re.MatchString(email)
}

func isValidPhoneNumber(phone string) bool {
    re := regexp.MustCompile(`^\+?[1-9]\d{1,14}$`)
    return re.MatchString(phone)
}
```

### 4.2 문자열 파싱
```go
func extractUrls(text string) []string {
    re := regexp.MustCompile(`https?://[^\s]+`)
    return re.FindAllString(text, -1)
}
```

---

## 5. 성능 최적화

### 5.1 문자열 연결
```go
// 효율적인 문자열 연결 (strings.Builder 사용)
func concatenateStrings(strs []string) string {
    var builder strings.Builder
    for _, s := range strs {
        builder.WriteString(s)
    }
    return builder.String()
}
```

### 5.2 정규표현식 최적화
```go
// 컴파일된 정규표현식 재사용
var emailRegex = regexp.MustCompile(`^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$`)

func validateEmails(emails []string) []bool {
    results := make([]bool, len(emails))
    for i, email := range emails {
        results[i] = emailRegex.MatchString(email)
    }
    return results
}
```

---

## 6. Best Practices

### 6.1 문자열 처리
- 큰 문자열 작업은 `strings.Builder` 사용
- 간단한 검색은 `strings` 패키지 함수 활용
- 문자열은 불변(immutable)임을 기억

### 6.2 정규표현식
- 자주 사용하는 패턴은 전역 변수로 컴파일
- 복잡한 패턴은 가독성을 위해 주석 추가
- 과도한 정규표현식 사용을 피하기

### 6.3 숫자 변환
- `strconv` 함수의 에러 처리를 철저히 수행
- 적절한 비트 크기와 진수를 선택하여 사용

---

## 7. 주의사항
- 문자열은 **불변(immutable)** 이므로 성능을 고려한 조작 필요
- 정규표현식은 복잡도가 높아 성능에 영향을 줄 수 있음
- UTF-8 인코딩을 고려한 문자열 처리 필요

