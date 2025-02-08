# 19. Go 형식화와 직렬화 (Serialization/Deserialization)

## 1. `encoding/json` 패키지

### 1.1 기본 JSON 처리
```go
type Person struct {
    Name    string   `json:"name"`
    Age     int      `json:"age"`
    Email   string   `json:"email,omitempty"`
    Hobbies []string `json:"hobbies,omitempty"`
}

func EncodeJSON() {
    person := Person{
        Name:    "Alice",
        Age:     30,
        Email:   "alice@example.com",
        Hobbies: []string{"reading", "hiking"},
    }
    data, _ := json.Marshal(person)
    prettyData, _ := json.MarshalIndent(person, "", "    ")
}

func DecodeJSON(data []byte) {
    var person Person
    json.Unmarshal(data, &person)
}
```

### 1.2 JSON 태그 활용
```go
type User struct {
    ID       int64      `json:"id"`
    Username string     `json:"username"`
    Password string     `json:"-"`
    Email    string     `json:"email,omitempty"`
}
```

### 1.3 JSON 스트리밍
```go
func EncodeJSONStream(w io.Writer, data []interface{}) error {
    encoder := json.NewEncoder(w)
    for _, item := range data {
        if err := encoder.Encode(item); err != nil {
            return err
        }
    }
    return nil
}
```

---

## 2. `encoding/xml` 패키지

### 2.1 기본 XML 처리
```go
type Config struct {
    XMLName xml.Name `xml:"config"`
    Server  string   `xml:"server"`
}

func EncodeXML(config Config) ([]byte, error) {
    return xml.MarshalIndent(config, "", "    ")
}
```

### 2.2 XML 속성과 콘텐츠
```go
type Item struct {
    XMLName xml.Name `xml:"item"`
    ID      int      `xml:"id,attr"`
}
```

---

## 3. `encoding/gob` 패키지

### 3.1 기본 Gob 처리
```go
func EncodeGob(data interface{}) ([]byte, error) {
    var buf bytes.Buffer
    enc := gob.NewEncoder(&buf)
    err := enc.Encode(data)
    return buf.Bytes(), err
}

func DecodeGob(data []byte, v interface{}) error {
    buf := bytes.NewBuffer(data)
    dec := gob.NewDecoder(buf)
    return dec.Decode(v)
}
```

---

## 4. 실용적인 예제

### 4.1 JSON API 구현
```go
type APIResponse struct {
    Status  string      `json:"status"`
    Data    interface{} `json:"data,omitempty"`
}

func APIHandler(w http.ResponseWriter, r *http.Request) {
    response := APIResponse{
        Status: "success",
        Data:   map[string]interface{}{ "users": []string{"user1", "user2"} },
    }
    json.NewEncoder(w).Encode(response)
}
```

### 4.2 설정 파일 처리
```go
type Config struct {
    Server struct {
        Host string `json:"host" xml:"host"`
        Port int    `json:"port" xml:"port"`
    } `json:"server" xml:"server"`
}
```

---

## 5. 성능 최적화

### 5.1 JSON 성능 개선
```go
var bufferPool = sync.Pool{
    New: func() interface{} {
        return new(bytes.Buffer)
    },
}

func EncodeJSONWithPool(v interface{}) ([]byte, error) {
    buf := bufferPool.Get().(*bytes.Buffer)
    buf.Reset()
    defer bufferPool.Put(buf)
    encoder := json.NewEncoder(buf)
    if err := encoder.Encode(v); err != nil {
        return nil, err
    }
    return buf.Bytes(), nil
}
```

### 5.2 병렬 처리
```go
func ProcessItemsParallel(items []Item) error {
    errChan := make(chan error, len(items))
    var wg sync.WaitGroup
    for _, item := range items {
        wg.Add(1)
        go func(item Item) {
            defer wg.Done()
            json.Marshal(item)
        }(item)
    }
    wg.Wait()
    close(errChan)
    return nil
}
```

---

## 6. Best Practices

### 6.1 JSON 처리
- `omitempty` 태그 활용
- 스트리밍 처리로 대용량 데이터 효율적 관리

### 6.2 XML 처리
- 태그 및 속성 사용 최적화
- 네임스페이스 관리

### 6.3 성능 최적화
- 버퍼 풀 활용
- 병렬 처리 고려

---

## 7. 주의사항
- 순환 참조 방지
- 메모리 사용량 관리
- 보안(민감한 데이터 처리)

