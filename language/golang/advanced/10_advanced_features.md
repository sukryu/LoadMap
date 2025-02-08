## 고급 기능 (Advanced Features)

### 1. reflect 패키지

#### 1.1 타입 정보 접근
reflect 패키지를 사용하면 런타임에 타입 정보를 확인하고 조작할 수 있다.

```go
func TypeInformation(v interface{}) {
    t := reflect.TypeOf(v)
    fmt.Printf("Type: %v\n", t)
    fmt.Printf("Kind: %v\n", t.Kind())

    if t.Kind() == reflect.Struct {
        for i := 0; i < t.NumField(); i++ {
            field := t.Field(i)
            fmt.Printf("Field: %s (%s)\n", field.Name, field.Type)
            fmt.Printf("Tags: %v\n", field.Tag)
        }
    }
}
```

#### 1.2 값 조작
reflect.Value를 이용하여 값을 동적으로 변경할 수 있다.

```go
func ValueManipulation(v interface{}) {
    val := reflect.ValueOf(v)

    if val.CanSet() {
        switch val.Kind() {
        case reflect.Int:
            val.SetInt(42)
        case reflect.String:
            val.SetString("modified")
        }
    }
}
```

#### 1.3 태그 처리
Go 구조체 필드의 태그를 동적으로 읽어올 수 있다.

```go
type Person struct {
    Name string `json:"name" validate:"required"`
    Age  int    `json:"age" validate:"gte=0,lte=130"`
}

func ProcessTags(v interface{}) map[string]map[string]string {
    t := reflect.TypeOf(v)
    tags := make(map[string]map[string]string)

    for i := 0; i < t.NumField(); i++ {
        field := t.Field(i)
        fieldTags := make(map[string]string)

        if jsonTag, ok := field.Tag.Lookup("json"); ok {
            fieldTags["json"] = jsonTag
        }
        if validateTag, ok := field.Tag.Lookup("validate"); ok {
            fieldTags["validate"] = validateTag
        }

        tags[field.Name] = fieldTags
    }
    return tags
}
```

### 2. unsafe 패키지

#### 2.1 포인터 조작
unsafe 패키지를 사용하면 메모리를 직접 조작할 수 있다.

```go
func UnsafePointerExample() {
    var i int32 = 42
    ptr := unsafe.Pointer(&i)
    f := *(*float32)(ptr)
    fmt.Println(f)
}
```

#### 2.2 메모리 레이아웃 확인
unsafe를 활용하여 메모리 오프셋 및 정렬을 확인할 수 있다.

```go
func MemoryLayout() {
    var x struct {
        a bool
        b int16
        c []int
    }
    fmt.Printf("a: offset=%v, size=%v\n", unsafe.Offsetof(x.a), unsafe.Sizeof(x.a))
}
```

### 3. plugin 패키지

#### 3.1 플러그인 로드
Go에서는 동적 로드를 위해 plugin 패키지를 사용할 수 있다.

```go
func LoadPlugin(path string) error {
    p, err := plugin.Open(path)
    if err != nil {
        return err
    }

    hello, err := p.Lookup("Hello")
    if err != nil {
        return err
    }

    if fn, ok := hello.(func() string); ok {
        fmt.Println(fn())
    }
    return nil
}
```

### 4. 실용적인 예제

#### 4.1 JSON 마샬링 커스터마이징
reflect를 활용하여 JSON 변환을 커스텀할 수 있다.

```go
type CustomMarshaler struct {
    Data map[string]interface{}
}

func (c *CustomMarshaler) MarshalJSON() ([]byte, error) {
    val := reflect.ValueOf(c.Data)
    modified := make(map[string]interface{})

    for _, key := range val.MapKeys() {
        value := val.MapIndex(key)
        modified[key.String()] = value.Interface()
    }

    return json.Marshal(modified)
}
```

### 5. 성능과 안정성

#### 5.1 reflect 성능 최적화
reflect를 사용할 경우, 성능 저하를 방지하기 위해 캐싱을 활용할 수 있다.

```go
type TypeCache struct {
    cache map[reflect.Type]map[string]reflect.Method
    mu    sync.RWMutex
}

func (c *TypeCache) GetMethod(t reflect.Type, name string) (reflect.Method, bool) {
    c.mu.RLock()
    methods, ok := c.cache[t]
    if !ok {
        c.mu.RUnlock()
        return c.cacheType(t, name)
    }
    c.mu.RUnlock()
    return methods[name], ok
}
```

#### 5.2 안전한 unsafe 사용
unsafe 패키지를 사용할 때 타입 변환을 안전하게 수행하는 방법이다.

```go
func SafeTypeConversion(data interface{}, target interface{}) error {
    src := reflect.ValueOf(data)
    dst := reflect.ValueOf(target)

    if dst.Kind() != reflect.Ptr {
        return errors.New("target must be a pointer")
    }

    if !src.Type().ConvertibleTo(dst.Elem().Type()) {
        return fmt.Errorf("cannot convert %v to %v", src.Type(), dst.Elem().Type())
    }

    dst.Elem().Set(src.Convert(dst.Elem().Type()))
    return nil
}
```

### 6. Best Practices

#### 6.1 reflect 사용
- 성능이 중요한 코드에서는 피하기
- 타입 안정성 보장
- 에러 처리 철저히 수행

#### 6.2 unsafe 사용
- 필요한 경우에만 제한적으로 사용
- 가비지 컬렉션 영향 고려
- 플랫폼 독립성 유지

#### 6.3 plugin 사용
- 버전 호환성을 고려한 설계 필요
- 보안 및 취약점 고려
- 플랫폼 의존성을 인지하고 사용

### 7. 주의사항

- reflect는 성능 오버헤드가 크므로 신중히 사용해야 한다.
- unsafe 패키지는 잘못된 접근 시 프로그램이 충돌할 위험이 있다.
- plugin 패키지는 플랫폼 종속성이 존재하므로 범용적인 프로그램에는 적합하지 않을 수 있다.

