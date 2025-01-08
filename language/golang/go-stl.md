# Go 표준 라이브러리

## Go 입출력과 파일 시스템

1. fmt 패키지
    1. 기본 출력 함수
        ```go
        // 기본 출력
        fmt.Print("Hello")      // 줄바꿈 없음
        fmt.Println("Hello")    // 줄바꿈 포함
        fmt.Printf("숫자: %d\n", 42)  // 형식화된 출력

        // 문자열 반환
        s := fmt.Sprint("Hello")       // 문자열로 반환
        s := fmt.Sprintln("Hello")    // 줄바꿈 포함
        s := fmt.Sprintf("숫자: %d", 42) // 형식화된 문자열
        ```

    2. 형식 지정자
        ```go
        // 기본 형식 지정자
        fmt.Printf("%v\n", value)    // 기본 형식
        fmt.Printf("%+v\n", value)   // 필드 이름 포함
        fmt.Printf("%#v\n", value)   // Go 문법 형식
        fmt.Printf("%T\n", value)    // 타입 정보

        // 숫자 형식
        fmt.Printf("%d\n", 42)       // 10진수
        fmt.Printf("%x\n", 42)       // 16진수
        fmt.Printf("%o\n", 42)       // 8진수
        fmt.Printf("%f\n", 3.14)     // 부동소수점
        fmt.Printf("%.2f\n", 3.14)   // 소수점 2자리

        // 문자열과 문자
        fmt.Printf("%s\n", "hello")  // 문자열
        fmt.Printf("%q\n", "hello")  // 따옴표 포함
        fmt.Printf("%c\n", 'A')      // 문자
        ```

    3. 입력 함수
        ```go
        var name string
        var age int

        // 기본 입력
        fmt.Scan(&name)         // 공백으로 구분된 입력
        fmt.Scanln(&name, &age) // 한 줄 입력

        // 형식화된 입력
        fmt.Scanf("%s %d", &name, &age)

        // 에러 처리
        if _, err := fmt.Scanf("%s %d", &name, &age); err != nil {
            log.Fatal(err)
        }
        ```

2. os 패키지
    1. 파일 조작
        ```go
        // 파일 열기
        file, err := os.Open("input.txt")
        if err != nil {
            log.Fatal(err)
        }
        defer file.Close()

        // 파일 생성
        file, err := os.Create("output.txt")
        if err != nil {
            log.Fatal(err)
        }
        defer file.Close()

        // 파일 쓰기 모드로 열기
        file, err := os.OpenFile("data.txt", os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
        if err != nil {
            log.Fatal(err)
        }
        defer file.Close()
        ```

    2. 디렉토리 조작
        ```go
        // 디렉토리 생성
        err := os.Mkdir("newdir", 0755)
        if err != nil {
            log.Fatal(err)
        }

        // 중첩 디렉토리 생성
        err := os.MkdirAll("path/to/newdir", 0755)
        if err != nil {
            log.Fatal(err)
        }

        // 디렉토리 읽기
        dir, err := os.ReadDir(".")
        if err != nil {
            log.Fatal(err)
        }
        for _, entry := range dir {
            fmt.Println(entry.Name(), entry.IsDir())
        }
        ```

    3. 환경 변수와 프로세스
        ```go
        // 환경 변수
        os.Setenv("MY_VAR", "value")
        value := os.Getenv("MY_VAR")

        // 모든 환경 변수
        for _, env := range os.Environ() {
            fmt.Println(env)
        }

        // 프로세스 관련
        pid := os.Getpid()
        ppid := os.Getppid()

        // 현재 작업 디렉토리
        dir, err := os.Getwd()
        if err != nil {
            log.Fatal(err)
        }
        ```

3. io 패키지와 버퍼 I/O
    1. io.Reader와 io.Writer
        ```go
        // io.Reader 인터페이스
        type Reader interface {
            Read(p []byte) (n int, err error)
        }

        // io.Writer 인터페이스
        type Writer interface {
            Write(p []byte) (n int, err error)
        }

        // 파일 복사 예제
        func copyFile(src, dst string) error {
            sourceFile, err := os.Open(src)
            if err != nil {
                return err
            }
            defer sourceFile.Close()

            destFile, err := os.Create(dst)
            if err != nil {
                return err
            }
            defer destFile.Close()

            _, err = io.Copy(destFile, sourceFile)
            return err
        }
        ```

    2. bufio 사용
        ```go
        // 버퍼된 읽기
        file, err := os.Open("input.txt")
        if err != nil {
            log.Fatal(err)
        }
        defer file.Close()

        reader := bufio.NewReader(file)
        line, err := reader.ReadString('\n')

        // 스캐너 사용
        scanner := bufio.NewScanner(file)
        for scanner.Scan() {
            fmt.Println(scanner.Text())
        }
        if err := scanner.Err(); err != nil {
            log.Fatal(err)
        }

        // 버퍼된 쓰기
        file, err := os.Create("output.txt")
        if err != nil {
            log.Fatal(err)
        }
        defer file.Close()

        writer := bufio.NewWriter(file)
        _, err = writer.WriteString("Hello, World!\n")
        if err != nil {
            log.Fatal(err)
        }
        writer.Flush()
        ```

4. filepath 패키지
    1. 경로 조작
        ```go
        // 경로 결합
        path := filepath.Join("dir", "subdir", "file.txt")

        // 경로 분할
        dir, file := filepath.Split("/path/to/file.txt")

        // 확장자 처리
        ext := filepath.Ext("file.txt")
        name := strings.TrimSuffix("file.txt", filepath.Ext("file.txt"))

        // 절대 경로 얻기
        absPath, err := filepath.Abs("relative/path")
        if err != nil {
            log.Fatal(err)
        }
        ```

    2. 경로 탐색
        ```go
        // 디렉토리 순회
        err := filepath.Walk(".", func(path string, info os.FileInfo, err error) error {
            if err != nil {
                return err
            }
            fmt.Printf("방문: %s\n", path)
            return nil
        })
        if err != nil {
            log.Fatal(err)
        }

        // 패턴 매칭
        matches, err := filepath.Glob("*.txt")
        if err != nil {
            log.Fatal(err)
        }
        for _, match := range matches {
            fmt.Println(match)
        }
        ```

5. 실용적인 예제
    1. 파일 처리 유틸리티
        ```go
        // 파일 내용 읽기
        func readFileContent(filename string) (string, error) {
            content, err := os.ReadFile(filename)
            if err != nil {
                return "", err
            }
            return string(content), nil
        }

        // 파일에 내용 쓰기
        func writeFileContent(filename, content string) error {
            return os.WriteFile(filename, []byte(content), 0644)
        }

        // 파일 존재 여부 확인
        func fileExists(filename string) bool {
            _, err := os.Stat(filename)
            return !os.IsNotExist(err)
        }
        ```

    2. 대용량 파일 처리
        ```go
        func processLargeFile(filename string) error {
            file, err := os.Open(filename)
            if err != nil {
                return err
            }
            defer file.Close()

            reader := bufio.NewReader(file)
            buffer := make([]byte, 4096)

            for {
                n, err := reader.Read(buffer)
                if err == io.EOF {
                    break
                }
                if err != nil {
                    return err
                }

                // 버퍼 처리
                process(buffer[:n])
            }
            return nil
        }
        ```

6. Best Practices
    1. 파일 처리
        - 항상 defer로 file.Close() 호출
        - 큰 파일은 bufio 사용
        - 에러 처리 철저히

    2. 경로 처리
        - filepath 패키지 사용하여 OS 독립적 코드 작성
        - 상대 경로보다 절대 경로 선호

    3. 입출력 최적화
        - 적절한 버퍼 크기 선택
        - Scanner 사용 시 커스텀 버퍼 크기 설정 가능

    4. 에러 처리
        - os.IsNotExist()등 특정 에러 확인
        - 리소스 정리를 위한 defer 적극 활용

7. 주의사항
    1. 파일 핸들 누수 방지
    2. 권한 설정 (Permission) 주의
    3. 크로스 플랫폼 호환성 고려
    4. 동시성 처리 시 적절한 동기화 필요

## Go 문자열 처리 (String Manipulation)

1. strings 패키지
    1. 문자열 검색
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

    2. 문자열 반환
        ```go
        // 대소문자 변환
        fmt.Println(strings.ToUpper("hello"))           // HELLO
        fmt.Println(strings.ToLower("HELLO"))           // hello
        fmt.Println(strings.Title("hello world"))       // Hello World

        // 공백 제거
        fmt.Println(strings.TrimSpace(" hello "))       // "hello"
        fmt.Println(strings.Trim("!!!hello!!!", "!"))   // "hello"
        fmt.Println(strings.TrimLeft("!!!hello", "!"))  // "hello"
        fmt.Println(strings.TrimRight("hello!!!", "!")) // "hello"

        // 문자열 반복
        fmt.Println(strings.Repeat("ha", 3))            // "hahaha"
        ```

    3. 문자열 분할과 결합
        ```go
        // 분할
        words := strings.Split("a,b,c", ",")            // ["a" "b" "c"]
        lines := strings.Split("a\nb\nc", "\n")         // ["a" "b" "c"]
        fields := strings.Fields("  a b  c  ")          // ["a" "b" "c"]

        // 결합
        joined := strings.Join([]string{"a", "b", "c"}, ",") // "a,b,c"

        // 바꾸기
        replaced := strings.Replace("hello hello", "hello", "hi", 1)    // "hi hello"
        replacedAll := strings.ReplaceAll("hello hello", "hello", "hi") // "hi hi"
        ```

2. strconv 패키지
    1. 문자열과 숫자 변환
        ```go
        // 문자열 -> 숫자
        i, err := strconv.Atoi("123")              // string to int
        f, err := strconv.ParseFloat("3.14", 64)   // string to float64
        b, err := strconv.ParseBool("true")        // string to bool

        // 숫자 -> 문자열
        s := strconv.Itoa(123)                     // int to string
        s = strconv.FormatFloat(3.14, 'f', 2, 64)  // float64 to string
        s = strconv.FormatBool(true)               // bool to string
        ```

    2. 진수 변환
        ```go
        // 다양한 진수 처리
        v, err := strconv.ParseInt("1010", 2, 64)  // 2진수 문자열을 정수로
        v, err = strconv.ParseInt("ff", 16, 64)    // 16진수 문자열을 정수로

        // 정수를 다양한 진수의 문자열로
        s := strconv.FormatInt(10, 2)              // 2진수 문자열로
        s = strconv.FormatInt(255, 16)             // 16진수 문자열로

        // 출력 형식 지정
        b := []byte(strconv.AppendInt([]byte("Number: "), 42, 10))
        ```

3. regexp 패키지
    1. 기본 정규표현식
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

    2. 그룹과 치환
        ```go
        // 그룹 캡처
        re := regexp.MustCompile(`(\w+):(\d+)`)
        match := re.FindStringSubmatch("port:8080")
        // match[0] = "port:8080", match[1] = "port", match[2] = "8080"

        // 이름 있는 그룹
        re := regexp.MustCompile(`(?P<key>\w+):(?P<value>\d+)`)
        match := re.FindStringSubmatch("port:8080")
        key := re.SubexpNames()

        // 치환
        re := regexp.MustCompile(`a+`)
        result := re.ReplaceAllString("aaa bbb aaa", "x") // "x bbb x"

        // 함수를 사용한 치환
        re := regexp.MustCompile(`\d+`)
        result := re.ReplaceAllStringFunc("123 456", func(s string) string {
            n, _ := strconv.Atoi(s)
            return strconv.Itoa(n * 2)
        })
        // "246 912"
        ```

4. 실용적인 예시
    1. 문자열 유효성 검사
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

    2. 문자열 파싱
        ```go
        func parseCSVLine(line string) []string {
            // 쉼표로 분리하되, 따옴표 내의 쉼표는 무시
            re := regexp.MustCompile(`[^,\"]+|\"[^\"]*\"`)
            return re.FindAllString(line, -1)
        }

        func extractUrls(text string) []string {
            re := regexp.MustCompile(`https?://[^\s]+`)
            return re.FindAllString(text, -1)
        }
        ```

5. 성능 최적화
    1. 문자열 연결결
        ```go
        // 효율적인 문자열 연결 (strings.Builder 사용)
        func concatenateStrings(strs []string) string {
            var builder strings.Builder
            for _, s := range strs {
                builder.WriteString(s)
            }
            return builder.String()
        }

        // 작은 수의 문자열은 + 연산자 사용 가능
        result := "Hello" + " " + "World"
        ```

    2. 정규표현식 최적화
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

6. Best Practices
    1. 문자열 처리
        - 큰 문자열 작업은 strings.Builder 사용
        - 간단한 검색은 strings 패키지 함수 사용
        - 문자열은 불변(immutable)임을 기억

    2. 정규표현식
        - 자주 사용하는 패턴은 전역 변수로 컴파일
        - 복잡한 패턴은 가독성을 위해 주석 추가
        - 과도한 정규표현식 사용 피하기

    3. 숫자 변환
        - strconv 함수의 에러 처리 필수
        - 적절한 비트 크기와 진수 사용

7. 주의사항
    1. 문자열 불변성으로 인한 성능 고려
    2. 정규표현식의 복잡도와 성능 영향
    3. UTF-8 인코딩 관련 문제
    4. 메모리 사용량(특히 큰 문자열 작업 시)

## Go 시간과 날짜 처리 (Time and Date)

1. time 패키지 기본
    1. 현재 시간 얻기
        ```go
        // 현재 시간
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

    2. 시간 생성
        ```go
        // 특정 시간 생성
        t := time.Date(2024, time.January, 8, 15, 4, 5, 0, time.UTC)

        // Unix 타임스탬프로부터 생성
        unix := time.Unix(1641600000, 0)

        // 문자열에서 파싱
        t, err := time.Parse("2006-01-02", "2024-01-08")
        if err != nil {
            log.Fatal(err)
        }

        // 타임존 지정
        loc, err := time.LoadLocation("Asia/Seoul")
        if err != nil {
            log.Fatal(err)
        }
        t = time.Date(2024, time.January, 8, 15, 4, 5, 0, loc)
        ```

2. 시간 포맷팅과 파싱
    1. 시간 포맷팅
        ```go
        now := time.Now()

        // 기본 포맷
        fmt.Println(now.Format("2006-01-02 15:04:05")) // 2024-01-08 15:04:05
        fmt.Println(now.Format("January 2, 2006"))      // January 8, 2024
        fmt.Println(now.Format("3:04 PM"))              // 3:04 PM

        // 사전 정의된 포맷
        fmt.Println(now.Format(time.RFC3339))     // 2024-01-08T15:04:05Z07:00
        fmt.Println(now.Format(time.RFC822))      // 08 Jan 24 15:04 UTC
        fmt.Println(now.Format(time.Kitchen))     // 3:04PM
        ```

    2. 시간 파싱
        ```go
        // 기본 파싱
        t, err := time.Parse("2006-01-02", "2024-01-08")
        if err != nil {
            log.Fatal(err)
        }

        // 타임존 고려한 파싱
        loc, _ := time.LoadLocation("Asia/Seoul")
        t, err = time.ParseInLocation("2006-01-02 15:04:05", "2024-01-08 15:04:05", loc)

        // 다양한 포맷 파싱
        layouts := []string{
            "2006-01-02",
            "01/02/2006",
            "January 2, 2006",
        }

        for _, layout := range layouts {
            t, err := time.Parse(layout, "2024-01-08")
            if err == nil {
                fmt.Println("성공:", t)
                break
            }
        }
        ```

3. 시간 연산
    1. 시간 더하기/빼기
        ```go
        now := time.Now()

        // Duration 사용
        future := now.Add(24 * time.Hour)        // 1일 후
        past := now.Add(-24 * time.Hour)         // 1일 전

        // 특정 단위 더하기
        future = now.AddDate(1, 0, 0)            // 1년 후
        future = now.AddDate(0, 1, 0)            // 1달 후
        future = now.AddDate(0, 0, 1)            // 1일 후

        // 시간 차이 계산
        diff := future.Sub(now)                  // Duration 반환
        hours := diff.Hours()                    // 시간으로 변환
        minutes := diff.Minutes()                // 분으로 변환
        seconds := diff.Seconds()                // 초로 변환
        ```

    2. 시간 비교
        ```go
        now := time.Now()
        future := now.Add(time.Hour)

        // 비교 연산
        fmt.Println(now.Before(future))          // true
        fmt.Println(now.After(future))           // false
        fmt.Println(now.Equal(future))           // false

        // 시간 사이 확인
        checkTime := now.Add(30 * time.Minute)
        fmt.Println(checkTime.After(now) && checkTime.Before(future)) // true
        ```

4. 타이머와 시간 측정
    1. 타이머 사용
        ```go
        // 일회성 타이머
        timer := time.NewTimer(2 * time.Second)
        <-timer.C    // 2초 대기
        timer.Stop() // 타이머 중지

        // time.After 사용
        select {
        case <-time.After(2 * time.Second):
            fmt.Println("타임아웃")
        case data := <-dataChan:
            fmt.Println("데이터 수신:", data)
        }

        // 주기적 타이커
        ticker := time.NewTicker(1 * time.Second)
        defer ticker.Stop()

        for {
            select {
            case <-ticker.C:
                fmt.Println("틱")
            case <-done:
                return
            }
        }
        ```

    2. 시간 측정
        ```go
        // 단순 시간 측정
        start := time.Now()
        // ... 작업 수행
        elapsed := time.Since(start)
        fmt.Printf("작업 소요 시간: %v\n", elapsed)

        // 함수 실행 시간 측정 데코레이터
        func timeTrack(start time.Time, name string) {
            elapsed := time.Since(start)
            fmt.Printf("%s took %s\n", name, elapsed)
        }

        func myFunction() {
            defer timeTrack(time.Now(), "myFunction")
            // ... 함수 로직
        }
        ```

5. 난수 생성 (math/rand vs crypto/rand)
    1. 의사 난수 생성 (math/rand)
        ```go
        // 시드 설정
        rand.Seed(time.Now().UnixNano())

        // 난수 생성
        n := rand.Intn(100)        // 0-99 사이 정수
        f := rand.Float64()        // 0.0-1.0 사이 실수

        // 난수 슬라이스 생성
        numbers := make([]int, 10)
        for i := range numbers {
            numbers[i] = rand.Intn(100)
        }
        ```

    2. 암호학적 난수 생성 (crypto/rand)
        ```go
        import "crypto/rand"

        // 안전한 난수 바이트 생성
        b := make([]byte, 16)
        _, err := rand.Read(b)
        if err != nil {
            log.Fatal(err)
        }

        // 범위 내 안전한 난수 생성
        func securePseudoRandomNumber(min, max int64) int64 {
            n, err := rand.Int(rand.Reader, big.NewInt(max-min+1))
            if err != nil {
                log.Fatal(err)
            }
            return n.Int64() + min
        }
        ```

6. Best Practices
    1. 시간 처리
        - 항상 UTC로 저장하고 필요할 때 로컬 시간으로 변환
        - time.Time 타입 사용 (문자열이나 타임스탬프 대신)
        - 시간 비교는 Equal() 메서드 사용

    2. 타임존 관리
        - 명시적인 타임존 관리
        - LoadLocation 에러 처리
        - IANA 타임존 데이터베이스 이름 사용

    3. 성능 고려사항
        - 반복문에서 time.Now() 호출 최소화
        - 타이머는 적절히 Stop() 호출
        - 불필요한 문자열 파싱 피하기

7. 주의사항
    1. 시간 연산의 특수 케이스(융년, 일광절약시간 등)
    2. 문자열 파싱시 포맷 주의(2006-01-02 형식 사용)
    3. 타임존 변환 시 에러 처리
    4. 시간 비교 시 Equal() 메서드 사용 (== 연산자 대신)

## Go 네트워킹

1. net 패키지
    1. TCP 서버
        ```go
        // TCP 서버 생성
        func TCPServer() error {
            listener, err := net.Listen("tcp", ":8080")
            if err != nil {
                return err
            }
            defer listener.Close()

            for {
                conn, err := listener.Accept()
                if err != nil {
                    log.Printf("연결 수락 실패: %v", err)
                    continue
                }
                go handleConnection(conn)
            }
        }

        // 연결 처리
        func handleConnection(conn net.Conn) {
            defer conn.Close()

            buffer := make([]byte, 1024)
            for {
                n, err := conn.Read(buffer)
                if err != nil {
                    if err != io.EOF {
                        log.Printf("읽기 오류: %v", err)
                    }
                    return
                }
                
                // 데이터 처리
                data := buffer[:n]
                conn.Write(data) // 에코 서버 예제
            }
        }
        ```

    2. TCP 클라이언트
        ```go
        func TCPClient() error {
            conn, err := net.Dial("tcp", "localhost:8080")
            if err != nil {
                return err
            }
            defer conn.Close()

            // 데이터 전송
            fmt.Fprintf(conn, "Hello, Server!")

            // 응답 수신
            buffer := make([]byte, 1024)
            n, err := conn.Read(buffer)
            if err != nil {
                return err
            }

            fmt.Printf("서버로부터 받은 응답: %s\n", buffer[:n])
            return nil
        }
        ```

    3. UDP 통신
        ```go
        // UDP 서버
        func UDPServer() error {
            addr, err := net.ResolveUDPAddr("udp", ":8081")
            if err != nil {
                return err
            }

            conn, err := net.ListenUDP("udp", addr)
            if err != nil {
                return err
            }
            defer conn.Close()

            buffer := make([]byte, 1024)
            for {
                n, remoteAddr, err := conn.ReadFromUDP(buffer)
                if err != nil {
                    log.Printf("읽기 오류: %v", err)
                    continue
                }

                go func(data []byte, remoteAddr *net.UDPAddr) {
                    conn.WriteToUDP(data, remoteAddr)
                }(buffer[:n], remoteAddr)
            }
        }

        // UDP 클라이언트
        func UDPClient() error {
            conn, err := net.Dial("udp", "localhost:8081")
            if err != nil {
                return err
            }
            defer conn.Close()

            _, err = fmt.Fprintf(conn, "Hello, UDP Server!")
            return err
        }
        ```

2. net/http 패키지
    1. HTTP 서버
        ```go
        // 기본 HTTP 서버
        func BasicHTTPServer() {
            http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
                fmt.Fprintf(w, "Hello, HTTP!")
            })

            log.Fatal(http.ListenAndServe(":8080", nil))
        }

        // 고급 HTTP 서버
        func AdvancedHTTPServer() {
            mux := http.NewServeMux()
            
            // 라우트 등록
            mux.HandleFunc("/", homeHandler)
            mux.HandleFunc("/api/", apiHandler)

            // 서버 설정
            server := &http.Server{
                Addr:           ":8080",
                Handler:        mux,
                ReadTimeout:    10 * time.Second,
                WriteTimeout:   10 * time.Second,
                MaxHeaderBytes: 1 << 20,
            }

            log.Fatal(server.ListenAndServe())
        }

        // 미들웨어 예제
        func loggingMiddleware(next http.Handler) http.Handler {
            return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
                start := time.Now()
                next.ServeHTTP(w, r)
                log.Printf("%s %s %v", r.Method, r.URL.Path, time.Since(start))
            })
        }
        ```

    2. HTTP 클라이언트
        ```go
        // 기본 GET 요청
        func BasicGet() error {
            resp, err := http.Get("http://example.com")
            if err != nil {
                return err
            }
            defer resp.Body.Close()

            body, err := io.ReadAll(resp.Body)
            if err != nil {
                return err
            }

            fmt.Printf("응답: %s\n", body)
            return nil
        }

        // 커스텀 HTTP 클라이언트
        func CustomClient() error {
            client := &http.Client{
                Timeout: time.Second * 10,
                Transport: &http.Transport{
                    MaxIdleConns:        10,
                    IdleConnTimeout:     30 * time.Second,
                    DisableCompression:  true,
                },
            }

            req, err := http.NewRequest("GET", "http://example.com", nil)
            if err != nil {
                return err
            }

            // 헤더 추가
            req.Header.Add("User-Agent", "Custom-Client")

            resp, err := client.Do(req)
            if err != nil {
                return err
            }
            defer resp.Body.Close()

            return nil
        }
        ```

    3. HTTP 요청 처리
        ```go
        // JSON API 핸들러
        func apiHandler(w http.ResponseWriter, r *http.Request) {
            switch r.Method {
            case http.MethodGet:
                handleGet(w, r)
            case http.MethodPost:
                handlePost(w, r)
            default:
                http.Error(w, "Method not allowed", http.StatusMethodNotAllowed)
            }
        }

        func handlePost(w http.ResponseWriter, r *http.Request) {
            var data struct {
                Name string `json:"name"`
                Age  int    `json:"age"`
            }

            if err := json.NewDecoder(r.Body).Decode(&data); err != nil {
                http.Error(w, err.Error(), http.StatusBadRequest)
                return
            }

            // 응답 전송
            w.Header().Set("Content-Type", "application/json")
            json.NewEncoder(w).Encode(map[string]string{
                "status": "success",
            })
        }
        ```

3. 웹소켓
    1. 웹소켓 서버
        ```go
        // gorilla/websocket 사용
        var upgrader = websocket.Upgrader{
            ReadBufferSize:  1024,
            WriteBufferSize: 1024,
        }

        func wsHandler(w http.ResponseWriter, r *http.Request) {
            conn, err := upgrader.Upgrade(w, r, nil)
            if err != nil {
                log.Printf("웹소켓 업그레이드 실패: %v", err)
                return
            }
            defer conn.Close()

            for {
                msgType, msg, err := conn.ReadMessage()
                if err != nil {
                    return
                }

                // 메시지 에코
                if err := conn.WriteMessage(msgType, msg); err != nil {
                    return
                }
            }
        }
        ```

4. 보안 및 TLS
    1. HTTPS 서버
        ```go
        func HTTPSServer() {
            // 인증서 생성
            // openssl req -x509 -newkey rsa:4096 -keyout key.pem -out cert.pem -days 365 -nodes

            http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
                fmt.Fprintf(w, "Secure Hello!")
            })

            log.Fatal(http.ListenAndServeTLS(":443", "cert.pem", "key.pem", nil))
        }

        // 커스텀 TLS 설정
        func CustomTLSServer() {
            server := &http.Server{
                Addr: ":443",
                TLSConfig: &tls.Config{
                    MinVersion:               tls.VersionTLS12,
                    CurvePreferences:         []tls.CurveID{tls.CurveP521, tls.CurveP384, tls.CurveP256},
                    PreferServerCipherSuites: true,
                    CipherSuites: []uint16{
                        tls.TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384,
                        tls.TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA,
                    },
                },
            }

            log.Fatal(server.ListenAndServeTLS("cert.pem", "key.pem"))
        }
        ```

5. 실용적인 예시
    1. 로드밸런서서
        ```go
        type LoadBalancer struct {
            backends []string
            current  int
            mu       sync.Mutex
        }

        func (lb *LoadBalancer) NextBackend() string {
            lb.mu.Lock()
            defer lb.mu.Unlock()

            backend := lb.backends[lb.current]
            lb.current = (lb.current + 1) % len(lb.backends)
            return backend
        }

        func (lb *LoadBalancer) ServeHTTP(w http.ResponseWriter, r *http.Request) {
            backend := lb.NextBackend()
            
            // 프록시 요청
            proxy := httputil.NewSingleHostReverseProxy(&url.URL{
                Scheme: "http",
                Host:   backend,
            })
            proxy.ServeHTTP(w, r)
        }
        ```

    2. 레이트 리미터
        ```go
        type RateLimiter struct {
            tokens chan struct{}
        }

        func NewRateLimiter(limit int, interval time.Duration) *RateLimiter {
            rl := &RateLimiter{
                tokens: make(chan struct{}, limit),
            }

            // 토큰 보충
            go func() {
                ticker := time.NewTicker(interval / time.Duration(limit))
                defer ticker.Stop()

                for range ticker.C {
                    select {
                    case rl.tokens <- struct{}{}:
                    default:
                    }
                }
            }()

            return rl
        }

        func (rl *RateLimiter) Middleware(next http.Handler) http.Handler {
            return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
                select {
                case <-rl.tokens:
                    next.ServeHTTP(w, r)
                default:
                    http.Error(w, "Rate limit exceeded", http.StatusTooManyRequests)
                }
            })
        }
        ```

6. Best Practices
    1. 에러 처리
        - 모든 네트워크 작업에서 타임아웃 설정
        - Connection Close 확실히 처리
        - 에러 로깅과 모니터링

    2. 성능 최적화
        - 연결 풀링 사용
        - Keep-Alice 설정
        - 적절한 버퍼 크기 설정

    3. 보안
        - HTTPS 사용
        - 입력 검증
        - CORS 설정
        - 적절한 타임아웃 설정

7. 주의사항
    1. 고루틴 누수 방지
    2. 연결 관리(타임아웃, 재연결 등)
    3. 에러 처리와 복구
    4. 보안 설정 (TLS, CORS 등)
    5. 리소스 관리(연결 풀, 버퍼 등)

## 형식화와 직렬화(Serialization/Deserialization)

1. encoding/json 패키지
    1. 기본 json 처리
        ```go
        // 구조체 정의
        type Person struct {
            Name    string   `json:"name"`
            Age     int      `json:"age"`
            Email   string   `json:"email,omitempty"`
            Hobbies []string `json:"hobbies,omitempty"`
        }

        // JSON 인코딩
        func EncodeJSON() {
            person := Person{
                Name:    "Alice",
                Age:     30,
                Email:   "alice@example.com",
                Hobbies: []string{"reading", "hiking"},
            }

            // 구조체를 JSON으로 변환
            data, err := json.Marshal(person)
            if err != nil {
                log.Fatal(err)
            }

            // 보기 좋게 포맷팅된 JSON
            prettyData, err := json.MarshalIndent(person, "", "    ")
            if err != nil {
                log.Fatal(err)
            }
        }

        // JSON 디코딩
        func DecodeJSON(data []byte) {
            var person Person
            if err := json.Unmarshal(data, &person); err != nil {
                log.Fatal(err)
            }
        }
        ```

    2. JSON 태그 활용
        ```go
        type User struct {
            ID        int64      `json:"id"`
            Username  string     `json:"username"`
            Password  string     `json:"-"`                     // JSON에서 제외
            Email     string     `json:"email,omitempty"`       // 빈 값이면 생략
            CreatedAt time.Time  `json:"created_at,omitempty"`
            Metadata  map[string]interface{} `json:"metadata,omitempty"`
        }

        // 커스텀 JSON 마샬링
        type Duration struct {
            time.Duration
        }

        func (d Duration) MarshalJSON() ([]byte, error) {
            return json.Marshal(d.String())
        }

        func (d *Duration) UnmarshalJSON(b []byte) error {
            var v interface{}
            if err := json.Unmarshal(b, &v); err != nil {
                return err
            }
            
            switch value := v.(type) {
            case float64:
                d.Duration = time.Duration(value)
                return nil
            case string:
                var err error
                d.Duration, err = time.ParseDuration(value)
                if err != nil {
                    return err
                }
                return nil
            default:
                return fmt.Errorf("invalid duration")
            }
        }
        ```

    3. JSON 스트리밍
        ```go
        // JSON 스트림 인코딩
        func EncodeJSONStream(w io.Writer, data []interface{}) error {
            encoder := json.NewEncoder(w)
            for _, item := range data {
                if err := encoder.Encode(item); err != nil {
                    return err
                }
            }
            return nil
        }

        // JSON 스트림 디코딩
        func DecodeJSONStream(r io.Reader) error {
            decoder := json.NewDecoder(r)
            for {
                var value map[string]interface{}
                if err := decoder.Decode(&value); err != nil {
                    if err == io.EOF {
                        break
                    }
                    return err
                }
                // 값 처리
                processValue(value)
            }
            return nil
        }
        ```

2. encoding/xml 패키지
    1. 기본 XML 처리
        ```go
        // XML 구조체 정의
        type Config struct {
            XMLName  xml.Name `xml:"config"`
            Server   string   `xml:"server"`
            Port     int      `xml:"port"`
            Database struct {
                Host     string `xml:"host"`
                Username string `xml:"username"`
                Password string `xml:"password"`
            } `xml:"database"`
        }

        // XML 인코딩
        func EncodeXML(config Config) ([]byte, error) {
            return xml.MarshalIndent(config, "", "    ")
        }

        // XML 디코딩
        func DecodeXML(data []byte) (*Config, error) {
            var config Config
            err := xml.Unmarshal(data, &config)
            return &config, err
        }
        ```

    2. XML 속성과 콘텐츠
        ```go
        type Item struct {
            XMLName xml.Name `xml:"item"`
            ID      int      `xml:"id,attr"`
            Name    string   `xml:"name"`
            Content string   `xml:",chardata"`
        }

        // XML 스트리밍
        func ProcessXMLStream(r io.Reader) error {
            decoder := xml.NewDecoder(r)
            for {
                token, err := decoder.Token()
                if err == io.EOF {
                    break
                }
                if err != nil {
                    return err
                }

                switch se := token.(type) {
                case xml.StartElement:
                    if se.Name.Local == "item" {
                        var item Item
                        if err := decoder.DecodeElement(&item, &se); err != nil {
                            return err
                        }
                        // 아이템 처리
                    }
                }
            }
            return nil
        }
        ```

3. encoding/gob 패키지
    1. 기본 Gob 처리
        ```go
        // Gob 인코딩
        func EncodeGob(data interface{}) ([]byte, error) {
            var buf bytes.Buffer
            enc := gob.NewEncoder(&buf)
            err := enc.Encode(data)
            return buf.Bytes(), err
        }

        // Gob 디코딩
        func DecodeGob(data []byte, v interface{}) error {
            buf := bytes.NewBuffer(data)
            dec := gob.NewDecoder(buf)
            return dec.Decode(v)
        }

        // 구조체에서 사용
        type Message struct {
            ID        int
            Data      []byte
            Timestamp time.Time
        }

        func SendMessage(msg Message) error {
            // 네트워크 연결을 통한 전송
            conn, err := net.Dial("tcp", "localhost:8080")
            if err != nil {
                return err
            }
            defer conn.Close()

            enc := gob.NewEncoder(conn)
            return enc.Encode(msg)
        }
        ```

4. 실용적인 예시
    1. JSON API 구현
        ```go
        type APIResponse struct {
            Status  string      `json:"status"`
            Message string      `json:"message,omitempty"`
            Data    interface{} `json:"data,omitempty"`
            Error   string      `json:"error,omitempty"`
        }

        func APIHandler(w http.ResponseWriter, r *http.Request) {
            response := APIResponse{
                Status: "success",
                Data: map[string]interface{}{
                    "users": []string{"user1", "user2"},
                },
            }

            w.Header().Set("Content-Type", "application/json")
            json.NewEncoder(w).Encode(response)
        }
        ```

    2. 설정 파일 처리
        ```go
        type Config struct {
            Server struct {
                Host string `json:"host" xml:"host"`
                Port int    `json:"port" xml:"port"`
            } `json:"server" xml:"server"`
            Database struct {
                URL      string `json:"url" xml:"url"`
                Username string `json:"username" xml:"username"`
                Password string `json:"password" xml:"password"`
            } `json:"database" xml:"database"`
        }

        func LoadConfig(filename string) (*Config, error) {
            data, err := os.ReadFile(filename)
            if err != nil {
                return nil, err
            }

            var config Config
            switch filepath.Ext(filename) {
            case ".json":
                err = json.Unmarshal(data, &config)
            case ".xml":
                err = xml.Unmarshal(data, &config)
            default:
                return nil, fmt.Errorf("unsupported file format")
            }

            return &config, err
        }
        ```

5. 성능 최적화
    1. JSON 성능 개선
        ```go
        // 풀을 사용한 버퍼 재사용
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

        // json.RawMessage 사용
        type CacheItem struct {
            Data json.RawMessage `json:"data"`
        }
        ```

    2. 병렬 처리
        ```go
        func ProcessItemsParallel(items []Item) error {
            errChan := make(chan error, len(items))
            var wg sync.WaitGroup

            for _, item := range items {
                wg.Add(1)
                go func(item Item) {
                    defer wg.Done()
                    data, err := json.Marshal(item)
                    if err != nil {
                        errChan <- err
                        return
                    }
                    // 데이터 처리
                }(item)
            }

            wg.Wait()
            close(errChan)

            return processErrors(errChan)
        }
        ```

6. Best Practices
    1. JSON 처리
        - omitempty 태그 적절히 사용
        - 에러 처리 철저히
        - 큰 데이터는 스트리밍 처리

    2. XML 처리
        - 적절한 태그와 속성 사용
        - 네임스페이스 고려
        - 검증 로직 추가

    3. 성능
        - 버퍼 풀 사용
        - 적절한 캐싱
        - 병렬 처리 고려

7. 주의사항
    1. 순환 참조 주의
    2. 메모리 사용량 관리
    3. 보안(민감한 데이터 처리)
    4. 버전 관리와 하위 호환성

## 동시성 프로그래밍

1. sync 패키지
    1. Mutex
        ```go
        // 기본 뮤텍스 사용
        type Counter struct {
            mu    sync.Mutex
            count int
        }

        func (c *Counter) Increment() {
            c.mu.Lock()
            defer c.mu.Unlock()
            c.count++
        }

        func (c *Counter) GetCount() int {
            c.mu.Lock()
            defer c.mu.Unlock()
            return c.count
        }

        // RWMutex 사용
        type Cache struct {
            mu    sync.RWMutex
            items map[string]string
        }

        func (c *Cache) Get(key string) (string, bool) {
            c.mu.RLock()
            defer c.mu.RUnlock()
            item, exists := c.items[key]
            return item, exists
        }

        func (c *Cache) Set(key, value string) {
            c.mu.Lock()
            defer c.mu.Unlock()
            c.items[key] = value
        }
        ```

    2. WaitGroup
        ```go
        func ProcessItems(items []int) {
            var wg sync.WaitGroup
            
            for _, item := range items {
                wg.Add(1)
                go func(item int) {
                    defer wg.Done()
                    // 아이템 처리
                    processItem(item)
                }(item)
            }
            
            wg.Wait()
        }

        // 실제 사용 예제
        func processParallel(data []string) error {
            var wg sync.WaitGroup
            errChan := make(chan error, len(data))

            for _, item := range data {
                wg.Add(1)
                go func(item string) {
                    defer wg.Done()
                    if err := process(item); err != nil {
                        errChan <- err
                    }
                }(item)
            }

            // 별도의 고루틴에서 WaitGroup 완료 대기
            go func() {
                wg.Wait()
                close(errChan)
            }()

            // 에러 수집
            for err := range errChan {
                if err != nil {
                    return err
                }
            }
            return nil
        }
        ```

    3. Once
        ```go
        type Singleton struct {
            data string
        }

        var (
            instance *Singleton
            once     sync.Once
        )

        func GetInstance() *Singleton {
            once.Do(func() {
                instance = &Singleton{
                    data: "initialized",
                }
            })
            return instance
        }
        ```

    4. Cond
        ```go
        type Queue struct {
            cond *sync.Cond
            data []interface{}
            size int
        }

        func NewQueue(size int) *Queue {
            return &Queue{
                cond: sync.NewCond(&sync.Mutex{}),
                size: size,
            }
        }

        func (q *Queue) Put(item interface{}) {
            q.cond.L.Lock()
            defer q.cond.L.Unlock()

            for len(q.data) >= q.size {
                q.cond.Wait()
            }
            q.data = append(q.data, item)
            q.cond.Signal()
        }

        func (q *Queue) Get() interface{} {
            q.cond.L.Lock()
            defer q.cond.L.Unlock()

            for len(q.data) == 0 {
                q.cond.Wait()
            }
            item := q.data[0]
            q.data = q.data[1:]
            q.cond.Signal()
            return item
        }
        ```

2. sync/atomic 패키지
    1. 기본 원자성 연산
        ```go
        type AtomicCounter struct {
            count int64
        }

        func (c *AtomicCounter) Increment() {
            atomic.AddInt64(&c.count, 1)
        }

        func (c *AtomicCounter) Decrement() {
            atomic.AddInt64(&c.count, -1)
        }

        func (c *AtomicCounter) GetCount() int64 {
            return atomic.LoadInt64(&c.count)
        }
        ```

    2. CompareAndSwap
        ```go
        type AtomicFlag struct {
            flag int32
        }

        func (f *AtomicFlag) Set() bool {
            return atomic.CompareAndSwapInt32(&f.flag, 0, 1)
        }

        func (f *AtomicFlag) Clear() {
            atomic.StoreInt32(&f.flag, 0)
        }

        func (f *AtomicFlag) IsSet() bool {
            return atomic.LoadInt32(&f.flag) == 1
        }
        ```

3. Context 패키지
    1. 기본 콘텍스트 사용
        ```go
        func worker(ctx context.Context) {
            for {
                select {
                case <-ctx.Done():
                    fmt.Println("작업 중단:", ctx.Err())
                    return
                default:
                    // 작업 수행
                    time.Sleep(time.Second)
                }
            }
        }

        func main() {
            // 타임아웃 컨텍스트
            ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
            defer cancel()

            go worker(ctx)
            time.Sleep(6 * time.Second)
        }
        ```

    2. 값 전달
        ```go
        type key int

        const (
            userKey key = iota
            authKey
        )

        func ProcessRequest(ctx context.Context) {
            if user, ok := ctx.Value(userKey).(string); ok {
                fmt.Printf("Processing request for user: %s\n", user)
            }
            
            if authToken, ok := ctx.Value(authKey).(string); ok {
                fmt.Printf("Using auth token: %s\n", authToken)
            }
        }

        func main() {
            ctx := context.Background()
            ctx = context.WithValue(ctx, userKey, "alice")
            ctx = context.WithValue(ctx, authKey, "token123")

            ProcessRequest(ctx)
        }
        ```

4. runtime 패키지
    1. 고루틴 관리
        ```go
        func init() {
            // CPU 코어 수 설정
            runtime.GOMAXPROCS(runtime.NumCPU())
        }

        func monitorGoroutines() {
            // 현재 고루틴 수 모니터링
            go func() {
                for range time.Tick(time.Second) {
                    fmt.Printf("Active goroutines: %d\n", runtime.NumGoroutine())
                }
            }()
        }
        ```

5. 실용적인 패턴
    1. 작업자 풀
        ```go
        type WorkerPool struct {
            workers  int
            tasks    chan func()
            shutdown chan struct{}
        }

        func NewWorkerPool(workers int) *WorkerPool {
            pool := &WorkerPool{
                workers:  workers,
                tasks:    make(chan func()),
                shutdown: make(chan struct{}),
            }
            pool.Start()
            return pool
        }

        func (p *WorkerPool) Start() {
            for i := 0; i < p.workers; i++ {
                go func() {
                    for {
                        select {
                        case task := <-p.tasks:
                            task()
                        case <-p.shutdown:
                            return
                        }
                    }
                }()
            }
        }

        func (p *WorkerPool) Submit(task func()) {
            p.tasks <- task
        }

        func (p *WorkerPool) Stop() {
            close(p.shutdown)
        }
        ```

    2. 세마포어 패턴
        ```go
        type Semaphore struct {
            sem chan struct{}
        }

        func NewSemaphore(size int) *Semaphore {
            return &Semaphore{
                sem: make(chan struct{}, size),
            }
        }

        func (s *Semaphore) Acquire() {
            s.sem <- struct{}{}
        }

        func (s *Semaphore) Release() {
            <-s.sem
        }

        // 사용 예제
        func processWithLimit(items []string, concurrency int) {
            sem := NewSemaphore(concurrency)
            var wg sync.WaitGroup

            for _, item := range items {
                wg.Add(1)
                go func(item string) {
                    defer wg.Done()
                    sem.Acquire()
                    defer sem.Release()
                    // 아이템 처리
                    process(item)
                }(item)
            }

            wg.Wait()
        }
        ```

6. 동시성 패턴
    1. 파이프라인 패턴
        ```go
        func generator(nums ...int) <-chan int {
            out := make(chan int)
            go func() {
                defer close(out)
                for _, n := range nums {
                    out <- n
                }
            }()
            return out
        }

        func square(in <-chan int) <-chan int {
            out := make(chan int)
            go func() {
                defer close(out)
                for n := range in {
                    out <- n * n
                }
            }()
            return out
        }

        func main() {
            nums := generator(1, 2, 3, 4)
            squares := square(nums)
            
            for result := range squares {
                fmt.Println(result)
            }
        }
        ```

    2. Fan-out, Fan-in 패턴
        ```go
        func fanOut(ch <-chan int, n int) []<-chan int {
            channels := make([]<-chan int, n)
            for i := 0; i < n; i++ {
                channels[i] = processChannel(ch)
            }
            return channels
        }

        func fanIn(channels ...<-chan int) <-chan int {
            var wg sync.WaitGroup
            out := make(chan int)

            wg.Add(len(channels))
            for _, ch := range channels {
                go func(c <-chan int) {
                    defer wg.Done()
                    for n := range c {
                        out <- n
                    }
                }(ch)
            }

            go func() {
                wg.Wait()
                close(out)
            }()

            return out
        }
        ```

7. Best Practices
    1. 동시성 관리
        - 적절한 수의 고루틴 사용
        - 리소스 제한 설정
        - 컨텍스트를 통한 취소 처리

    2. 에러 처리
        - 고루틴 내 에러 수집
        - panic 복구
        - 우아한 종료

    3. 성능 최적화
        - 적절한 버퍼 크기
        - 메모리 사용량 관리
        - 컨텍스트 타임아웃 설정

8. 주의사항
    1. 데드락 방지
    2. 고루틴 누수 관리
    3. 공유 메모리 접근 동기화
    4. 채널 닫기 규칙 준수
    5. 컨텍스트 취소 처리

## 컨테이너와 자료구조 (Containers and Data Structures)

1. container/heap
    1. 기본 힙 구현
        ```go
        // IntHeap 타입 정의
        type IntHeap []int

        // heap.Interface 구현
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

        // 사용 예제
        func main() {
            h := &IntHeap{2, 1, 5}
            heap.Init(h)
            heap.Push(h, 3)
            
            for h.Len() > 0 {
                fmt.Printf("%d ", heap.Pop(h))
            }
        }
        ```

    2. 우선순위 큐 
        ```go
        // Item 구조체 정의
        type Item struct {
            value    string
            priority int
            index    int
        }

        // PriorityQueue 정의
        type PriorityQueue []*Item

        // heap.Interface 구현
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
            n := len(*pq)
            item := x.(*Item)
            item.index = n
            *pq = append(*pq, item)
        }

        func (pq *PriorityQueue) Pop() interface{} {
            old := *pq
            n := len(old)
            item := old[n-1]
            old[n-1] = nil // 메모리 누수 방지
            item.index = -1
            *pq = old[0 : n-1]
            return item
        }

        // 우선순위 갱신
        func (pq *PriorityQueue) Update(item *Item, value string, priority int) {
            item.value = value
            item.priority = priority
            heap.Fix(pq, item.index)
        }
        ```

2. container/list
    1. 이중 연결 리스트
        ```go
        // 기본 리스트 사용
        func BasicList() {
            list := list.New()
            
            // 요소 추가
            list.PushBack("first")
            list.PushFront("zero")
            list.PushBack("last")
            
            // 순회
            for e := list.Front(); e != nil; e = e.Next() {
                fmt.Println(e.Value)
            }
        }

        // 커스텀 리스트 구현
        type CustomList struct {
            *list.List
            length int
        }

        func NewCustomList() *CustomList {
            return &CustomList{
                List: list.New(),
            }
        }

        func (l *CustomList) AddSorted(value int) {
            for e := l.Front(); e != nil; e = e.Next() {
                if e.Value.(int) > value {
                    l.InsertBefore(value, e)
                    l.length++
                    return
                }
            }
            l.PushBack(value)
            l.length++
        }
        ```

    2. 리스트 조작
        ```go
        func ManipulateList() {
            l := list.New()
            
            // 요소 추가
            l.PushBack("one")
            l.PushBack("two")
            l.PushBack("three")
            
            // 특정 요소 찾기
            var element *list.Element
            for e := l.Front(); e != nil; e = e.Next() {
                if e.Value.(string) == "two" {
                    element = e
                    break
                }
            }
            
            // 요소 조작
            if element != nil {
                l.InsertAfter("two and half", element)
                l.Remove(element)
            }
        }
        ```

3. container/ring
    1. 원형 리스트
        ```go
        // 기본 링 사용
        func BasicRing() {
            // 크기 5인 링 생성
            r := ring.New(5)
            
            // 값 설정
            for i := 0; i < r.Len(); i++ {
                r.Value = i
                r = r.Next()
            }
            
            // 순회
            r.Do(func(p interface{}) {
                fmt.Println(p)
            })
        }

        // 링 조작
        func ManipulateRing() {
            // 두 개의 링 생성
            r1 := ring.New(3)
            r2 := ring.New(3)
            
            // 값 설정
            for i := 0; i < 3; i++ {
                r1.Value = i
                r2.Value = i + 3
                r1 = r1.Next()
                r2 = r2.Next()
            }
            
            // 링 연결
            r3 := r1.Link(r2)
            
            // 결과 출력
            r3.Do(func(p interface{}) {
                fmt.Println(p)
            })
        }
        ```

4. 실용적인 예시
    1. 작업 큐 구현
        ```go
        type Job struct {
            Priority int
            Data     interface{}
        }

        type JobQueue struct {
            queue PriorityQueue
        }

        func NewJobQueue() *JobQueue {
            jq := &JobQueue{
                queue: make(PriorityQueue, 0),
            }
            heap.Init(&jq.queue)
            return jq
        }

        func (jq *JobQueue) AddJob(priority int, data interface{}) {
            item := &Item{
                value:    data,
                priority: priority,
            }
            heap.Push(&jq.queue, item)
        }

        func (jq *JobQueue) ProcessJobs() {
            for jq.queue.Len() > 0 {
                item := heap.Pop(&jq.queue).(*Item)
                // 작업 처리
                process(item.value)
            }
        }
        ```

    2. LRU 캐시 구현
        ```go
        type LRUCache struct {
            capacity int
            cache    map[interface{}]*list.Element
            list     *list.List
        }

        type entry struct {
            key   interface{}
            value interface{}
        }

        func NewLRUCache(capacity int) *LRUCache {
            return &LRUCache{
                capacity: capacity,
                cache:    make(map[interface{}]*list.Element),
                list:     list.New(),
            }
        }

        func (c *LRUCache) Get(key interface{}) (interface{}, bool) {
            if element, exists := c.cache[key]; exists {
                c.list.MoveToFront(element)
                return element.Value.(*entry).value, true
            }
            return nil, false
        }

        func (c *LRUCache) Put(key, value interface{}) {
            if element, exists := c.cache[key]; exists {
                c.list.MoveToFront(element)
                element.Value.(*entry).value = value
                return
            }

            if c.list.Len() >= c.capacity {
                // 가장 오래된 항목 제거
                back := c.list.Back()
                c.list.Remove(back)
                delete(c.cache, back.Value.(*entry).key)
            }

            // 새 항목 추가
            element := c.list.PushFront(&entry{key, value})
            c.cache[key] = element
        }
        ```

5. 성능 고려사항
    1. 컨테이너 선택 가이드라인
        ```go
        // 슬라이스 vs 리스트
        // 슬라이스: 연속된 메모리, 빠른 접근, 크기 변경 비용
        numbers := make([]int, 0, initialCapacity)

        // 리스트: 동적 삽입/삭제, 메모리 오버헤드
        linkedList := list.New()

        // 링: 순환 데이터, 고정 크기
        circularBuffer := ring.New(size)

        // 힙: 우선순위 기반 처리
        priorityQueue := make(PriorityQueue, 0)
        ```

    2. 메모리 효율성
        ```go
        // 메모리 재사용
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

        // 사용
        pool := NewPool()
        lst := pool.Get().(*list.List)
        defer pool.Put(lst)
        ```

6. Best Practices
    1. 컨테이너 선택
        - 용도에 맞는 자료구조 선택
        - 성능 요구사항 고려
        - 메모리 사용량 고려

    2. 구현 패턴
        - 인터페이스 구현 완성도 체크
        - nil 포인터 처리
        - 동시성 고려

    3. 성능 최적화
        - 적절한 초기 용량 설정
        - 메모리 재사용
        - 불필요한 복사 방지

7. 주의사항
    1. 동시성 안정성 고려
    2. 메모리 누수 방지
    3. 순환 참조 주의
    4. 적절한 에러 처리
    5. 인터페이스 구현 완성도 확인

## 암호화와 보안 (Cryptography and Security)

1. 해시 함수
    1. SHA-2 해시
        ```go
        import (
            "crypto/sha256"
            "crypto/sha512"
            "fmt"
        )

        func HashExamples() {
            // SHA-256
            data := []byte("hello world")
            hash := sha256.Sum256(data)
            fmt.Printf("SHA-256: %x\n", hash)

            // SHA-512
            hash512 := sha512.Sum512(data)
            fmt.Printf("SHA-512: %x\n", hash512)

            // 스트리밍 해시
            h := sha256.New()
            h.Write([]byte("hello"))
            h.Write([]byte(" world"))
            fmt.Printf("Streamed SHA-256: %x\n", h.Sum(nil))
        }

        // 파일 해시 계산
        func HashFile(filepath string) (string, error) {
            f, err := os.Open(filepath)
            if err != nil {
                return "", err
            }
            defer f.Close()

            h := sha256.New()
            if _, err := io.Copy(h, f); err != nil {
                return "", err
            }

            return fmt.Sprintf("%x", h.Sum(nil)), nil
        }
        ```

    2. HMAC
        ```go
        import "crypto/hmac"

        func ComputeHMAC(message, key []byte) []byte {
            h := hmac.New(sha256.New, key)
            h.Write(message)
            return h.Sum(nil)
        }

        // HMAC 검증
        func ValidateHMAC(message, key, messageMAC []byte) bool {
            mac := ComputeHMAC(message, key)
            return hmac.Equal(messageMAC, mac)
        }
        ```

2. 대칭키 암호화
    1. AES 암호화
        ```go
        import (
            "crypto/aes"
            "crypto/cipher"
            "crypto/rand"
        )

        // AES-GCM 암호화
        func Encrypt(plaintext []byte, key []byte) ([]byte, error) {
            block, err := aes.NewCipher(key)
            if err != nil {
                return nil, err
            }

            gcm, err := cipher.NewGCM(block)
            if err != nil {
                return nil, err
            }

            nonce := make([]byte, gcm.NonceSize())
            if _, err := io.ReadFull(rand.Reader, nonce); err != nil {
                return nil, err
            }

            return gcm.Seal(nonce, nonce, plaintext, nil), nil
        }

        // AES-GCM 복호화
        func Decrypt(ciphertext []byte, key []byte) ([]byte, error) {
            block, err := aes.NewCipher(key)
            if err != nil {
                return nil, err
            }

            gcm, err := cipher.NewGCM(block)
            if err != nil {
                return nil, err
            }

            if len(ciphertext) < gcm.NonceSize() {
                return nil, errors.New("ciphertext too short")
            }

            nonce, ciphertext := ciphertext[:gcm.NonceSize()], ciphertext[gcm.NonceSize():]
            return gcm.Open(nil, nonce, ciphertext, nil)
        }
        ```

    2. 키 생성과 관리
        ```go
        func GenerateAESKey() ([]byte, error) {
            key := make([]byte, 32) // AES-256
            if _, err := rand.Read(key); err != nil {
                return nil, err
            }
            return key, nil
        }

        // 키 파생 함수 (PBKDF2)
        func DeriveKey(password, salt []byte, iterations int) []byte {
            return pbkdf2.Key(password, salt, iterations, 32, sha256.New)
        }
        ```

3. 비대칭키 암호화
    1. RSA
        ```go
        import "crypto/rsa"

        // RSA 키쌍 생성
        func GenerateRSAKeys() (*rsa.PrivateKey, error) {
            privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
            if err != nil {
                return nil, err
            }
            return privateKey, nil
        }

        // RSA 암호화
        func RSAEncrypt(publicKey *rsa.PublicKey, message []byte) ([]byte, error) {
            return rsa.EncryptOAEP(
                sha256.New(),
                rand.Reader,
                publicKey,
                message,
                nil,
            )
        }

        // RSA 복호화
        func RSADecrypt(privateKey *rsa.PrivateKey, ciphertext []byte) ([]byte, error) {
            return rsa.DecryptOAEP(
                sha256.New(),
                rand.Reader,
                privateKey,
                ciphertext,
                nil,
            )
        }
        ```

    2. 전자서명
        ```go
        // 서명 생성
        func Sign(privateKey *rsa.PrivateKey, message []byte) ([]byte, error) {
            hashed := sha256.Sum256(message)
            return rsa.SignPKCS1v15(rand.Reader, privateKey, crypto.SHA256, hashed[:])
        }

        // 서명 검증
        func Verify(publicKey *rsa.PublicKey, message, signature []byte) error {
            hashed := sha256.Sum256(message)
            return rsa.VerifyPKCS1v15(publicKey, crypto.SHA256, hashed[:], signature)
        }
        ```

4. TLS/SSL
    1. HTTPS 서버
        ```go
        func HTTPSServer() {
            // TLS 설정
            cfg := &tls.Config{
                MinVersion: tls.VersionTLS12,
                CurvePreferences: []tls.CurveID{
                    tls.X25519,
                    tls.CurveP256,
                },
                PreferServerCipherSuites: true,
                CipherSuites: []uint16{
                    tls.TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384,
                    tls.TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384,
                    tls.TLS_ECDHE_ECDSA_WITH_CHACHA20_POLY1305,
                    tls.TLS_ECDHE_RSA_WITH_CHACHA20_POLY1305,
                },
            }

            srv := &http.Server{
                Addr:         ":443",
                Handler:      handler(),
                TLSConfig:    cfg,
                TLSNextProto: make(map[string]func(*http.Server, *tls.Conn, http.Handler)),
            }

            log.Fatal(srv.ListenAndServeTLS("cert.pem", "key.pem"))
        }
        ```

    2. HTTPS 클라이언트
        ```go
        func HTTPSClient() *http.Client {
            tr := &http.Transport{
                TLSClientConfig: &tls.Config{
                    MinVersion: tls.VersionTLS12,
                },
                ForceAttemptHTTP2: true,
            }

            return &http.Client{Transport: tr}
        }
        ```

5. 보안 난수 생성
    1. crypto/rand 사용
        ```go
        func GenerateRandomBytes(n int) ([]byte, error) {
            b := make([]byte, n)
            _, err := rand.Read(b)
            if err != nil {
                return nil, err
            }
            return b, nil
        }

        // 보안 토큰 생성
        func GenerateToken(length int) (string, error) {
            b, err := GenerateRandomBytes(length)
            if err != nil {
                return "", err
            }
            return hex.EncodeToString(b), nil
        }
        ```

6. 안전한 패스워드 처리
    1. 패스워드 해싱
        ```go
        import "golang.org/x/crypto/bcrypt"

        func HashPassword(password string) (string, error) {
            bytes, err := bcrypt.GenerateFromPassword([]byte(password), bcrypt.DefaultCost)
            return string(bytes), err
        }

        func CheckPassword(password, hash string) bool {
            err := bcrypt.CompareHashAndPassword([]byte(hash), []byte(password))
            return err == nil
        }
        ```

7. 실용적인 예제
    1. 안전한 세션 관리
        ```go
        type Session struct {
            ID        string
            UserID    string
            CreatedAt time.Time
            ExpiresAt time.Time
        }

        func NewSession(userID string, duration time.Duration) (*Session, error) {
            sessionID, err := GenerateToken(32)
            if err != nil {
                return nil, err
            }

            now := time.Now()
            return &Session{
                ID:        sessionID,
                UserID:    userID,
                CreatedAt: now,
                ExpiresAt: now.Add(duration),
            }, nil
        }
        ```

    2. 안전한 쿠키 설정
        ```go
        func SetSecureCookie(w http.ResponseWriter, name, value string) {
            cookie := &http.Cookie{
                Name:     name,
                Value:    value,
                Path:     "/",
                HttpOnly: true,
                Secure:   true,
                SameSite: http.SameSiteStrictMode,
                MaxAge:   3600,
            }
            http.SetCookie(w, cookie)
        }
        ```

8. Best Practices
    1. 암호화
        - 검증된 암호화 알고리즘 사용
        - 적절한 키 길이 선택
        - 안전한 키 관리

    2. 보안 설정
        - TLS 1.2 이상 사용
        - 강력한 암호화 스위트 선택
        - 적절한 인증서 관리

    3. 입력 검증
        - 모든 사용자 입력 검증
        - SQL 인젝션 방지
        - XSS 공격 방지

    4. 세션 관리
        - 안전한 세션ID 생성
        - 적절한 세션 만료 설정
        - 세션 하이재킹 방지

9. 주의사항
    1. 자체 암호화 알고리즘 구현 금지
    2. 암호화 키의 안전한 관리
    3. 중요 정보 로깅 주의

## 에러 처리와 로깅, 디버깅

1. errors 패키지
    1. 기본 에러 생성과 처리
        ```go
        // 기본 에러 생성
        err := errors.New("something went wrong")

        // 포맷된 에러 생성
        name := "file.txt"
        err := fmt.Errorf("failed to read file %s", name)

        // 에러 랩핑 (Go 1.13+)
        err := fmt.Errorf("failed to process: %w", originalErr)

        // 에러 체크
        if err != nil {
            return fmt.Errorf("operation failed: %v", err)
        }
        ```

    2. 커스텀 에러 타입
        ```go
        // 커스텀 에러 타입 정의
        type ValidationError struct {
            Field   string
            Message string
        }

        func (e *ValidationError) Error() string {
            return fmt.Sprintf("validation failed on %s: %s", e.Field, e.Message)
        }

        // 에러 생성 함수
        func NewValidationError(field, message string) error {
            return &ValidationError{
                Field:   field,
                Message: message,
            }
        }

        // 에러 타입 검사
        if err != nil {
            var validationErr *ValidationError
            if errors.As(err, &validationErr) {
                fmt.Printf("Validation error: %s\n", validationErr.Message)
            }
        }
        ```

    3. 에러 체인
        ```go
        type QueryError struct {
            Query string
            Err   error
        }

        func (e *QueryError) Error() string {
            return fmt.Sprintf("query error for %q: %v", e.Query, e.Err)
        }

        func (e *QueryError) Unwrap() error {
            return e.Err
        }

        // 에러 체인 사용
        if err != nil {
            // 특정 에러 확인
            if errors.Is(err, sql.ErrNoRows) {
                // 처리
            }
            // 에러 타입 확인
            var queryErr *QueryError
            if errors.As(err, &queryErr) {
                // 처리
            }
        }
        ```

2. log 패키지
    1. 기본 로깅
        ```go
        // 기본 로그
        log.Println("Starting application...")
        log.Printf("Processing item: %v", item)

        // 에러 로그
        if err != nil {
            log.Printf("Error: %v", err)
        }

        // 치명적 에러 (프로그램 종료)
        if err != nil {
            log.Fatalf("Fatal error: %v", err)
        }
        ```

    2. 커스텀 로거
        ```go
        // 로그 설정
        func initLogger() *log.Logger {
            flags := log.Ldate | log.Ltime | log.Lshortfile
            
            // 파일에 로그 작성
            f, err := os.OpenFile("app.log", os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
            if err != nil {
                log.Fatal(err)
            }
            
            return log.New(f, "APP: ", flags)
        }

        // 멀티 로거
        type MultiLogger struct {
            loggers []*log.Logger
        }

        func (ml *MultiLogger) Printf(format string, v ...interface{}) {
            for _, logger := range ml.loggers {
                logger.Printf(format, v...)
            }
        }
        ```

    3. 구조화된 로깅
        ```go
        type LogEntry struct {
            Level     string    `json:"level"`
            Timestamp time.Time `json:"timestamp"`
            Message   string    `json:"message"`
            Fields    Fields    `json:"fields,omitempty"`
        }

        type Fields map[string]interface{}

        func (e *LogEntry) String() string {
            data, _ := json.Marshal(e)
            return string(data)
        }

        func NewLogger(w io.Writer) *Logger {
            return &Logger{
                output: w,
            }
        }

        func (l *Logger) Info(msg string, fields Fields) {
            l.log("INFO", msg, fields)
        }

        func (l *Logger) Error(msg string, fields Fields) {
            l.log("ERROR", msg, fields)
        }
        ```

3. runtime/pprof
    1. CPU 프로파일링
        ```go
        func CPUProfile() {
            f, err := os.Create("cpu.pprof")
            if err != nil {
                log.Fatal(err)
            }
            defer f.Close()

            if err := pprof.StartCPUProfile(f); err != nil {
                log.Fatal(err)
            }
            defer pprof.StopCPUProfile()

            // 프로파일링할 코드
            heavyComputation()
        }
        ```

    2. 메모리 프로파일링
        ```go
        func MemoryProfile() {
            f, err := os.Create("memory.pprof")
            if err != nil {
                log.Fatal(err)
            }
            defer f.Close()

            runtime.GC() // 가비지 컬렉션 강제 실행
            if err := pprof.WriteHeapProfile(f); err != nil {
                log.Fatal(err)
            }
        }
        ```

    3. HTTP 프로파일링
        ```go
        import _ "net/http/pprof"

        func main() {
            go func() {
                log.Println(http.ListenAndServe("localhost:6060", nil))
            }()

            // 메인 애플리케이션 코드
        }
        ```

4. 실용적인 에러 처리 패턴
    1. 에러 핸들러
        ```go
        type ErrorHandler struct {
            handlers map[error]func(error) error
        }

        func NewErrorHandler() *ErrorHandler {
            return &ErrorHandler{
                handlers: make(map[error]func(error) error),
            }
        }

        func (eh *ErrorHandler) Register(err error, handler func(error) error) {
            eh.handlers[err] = handler
        }

        func (eh *ErrorHandler) Handle(err error) error {
            for e, handler := range eh.handlers {
                if errors.Is(err, e) {
                    return handler(err)
                }
            }
            return err
        }
        ```

    2. 재시도 메커니즘
        ```go
        func Retry(attempts int, sleep time.Duration, f func() error) error {
            var err error
            
            for i := 0; i < attempts; i++ {
                err = f()
                if err == nil {
                    return nil
                }
                
                if i < attempts-1 {
                    time.Sleep(sleep * time.Duration(i+1))
                    log.Printf("Retry %d after error: %v", i+1, err)
                }
            }
            
            return fmt.Errorf("after %d attempts, last error: %v", attempts, err)
        }

        // 사용 예시
        err := Retry(3, time.Second, func() error {
            return someOperation()
        })
        ```

5. 디버깅 도구
    1. 런타임 디버깅
        ```go
        // 고루틴 스택 트레이스
        func dumpGoroutines() {
            buf := make([]byte, 1<<20)
            buf = buf[:runtime.Stack(buf, true)]
            fmt.Printf("=== goroutine dump:\n%s\n", buf)
        }

        // 메모리 통계
        func printMemStats() {
            var stats runtime.MemStats
            runtime.ReadMemStats(&stats)
            fmt.Printf("Alloc = %v MiB\n", stats.Alloc/1024/1024)
            fmt.Printf("TotalAlloc = %v MiB\n", stats.TotalAlloc/1024/1024)
            fmt.Printf("Sys = %v MiB\n", stats.Sys/1024/1024)
            fmt.Printf("NumGC = %v\n", stats.NumGC)
        }
        ```

    2. 트레이스 도구
        ```go
        func Trace() func() {
            start := time.Now()
            trace := fmt.Sprintf("enter: %s", functionName(1))
            fmt.Println(trace)
            return func() {
                fmt.Printf("exit: %s (%s)\n", functionName(1), time.Since(start))
            }
        }

        // 사용 예시
        func someFunction() {
            defer Trace()()
            // 함수 로직
        }
        ```

6. Best Practices
    1. 에러 처리
        - 의미 있는 에러 메시지 작성
        - 에러 컨텍스트 포함
        - 에러 타입 계층 구조 설계

    2. 로깅
        - 로그 레벨 적절히 사용
        - 구조화된 로깅 활용
        - 로그 순환(rotation) 구현

    3. 디버깅
        - 프로파일링 도구 활용
        - 디버그 로그 추가
        - 테스트 커버리지 확인

7. 주의사항
    1. 에러 처리 시 주의사항
        - 에러 무시하지 않기
        - 에러 메시지에 민감한 정보 포함하지 ㅇ낳기
        - panic/recover 적절히 사용

    2. 로깅 시 주의사항
        - 로그 레벨 적절히 선택
        - 성능 영향 고려
        - 디스크 공간 관리

    3. 디버깅 시 주의사항
        - 프로덕션 환경 영향 최소화
        - 디버그 코드 관리
        - 성능 영향 고려

## 고급 기능 (Advanced Features)

1. reflect 패키지
    1. 타입 정보 접근
        ```go
        func TypeInformation(v interface{}) {
            t := reflect.TypeOf(v)
            
            // 기본 타입 정보
            fmt.Printf("Type: %v\n", t)
            fmt.Printf("Kind: %v\n", t.Kind())
            
            // 구조체 필드 순회
            if t.Kind() == reflect.Struct {
                for i := 0; i < t.NumField(); i++ {
                    field := t.Field(i)
                    fmt.Printf("Field: %s (%s)\n", field.Name, field.Type)
                    fmt.Printf("Tags: %v\n", field.Tag)
                }
            }
            
            // 메서드 순회
            for i := 0; i < t.NumMethod(); i++ {
                method := t.Method(i)
                fmt.Printf("Method: %s\n", method.Name)
            }
        }
        ```

    2. 값 조작
        ```go
        func ValueManipulation(v interface{}) {
            val := reflect.ValueOf(v)

            // 값이 변경 가능한지 확인
            if val.CanSet() {
                switch val.Kind() {
                case reflect.Int:
                    val.SetInt(42)
                case reflect.String:
                    val.SetString("modified")
                }
            }

            // 메서드 호출
            if val.MethodByName("String").IsValid() {
                result := val.MethodByName("String").Call(nil)
                fmt.Printf("String() result: %v\n", result[0])
            }
        }

        // 구조체 동적 생성
        func CreateStruct(typ reflect.Type) interface{} {
            // 새 구조체 인스턴스 생성
            val := reflect.New(typ).Elem()
            
            // 필드 설정
            for i := 0; i < val.NumField(); i++ {
                field := val.Field(i)
                if field.CanSet() {
                    switch field.Kind() {
                    case reflect.String:
                        field.SetString("default")
                    case reflect.Int:
                        field.SetInt(0)
                    }
                }
            }
            
            return val.Interface()
        }
        ```

    3. 태그 처리
        ```go
        type Person struct {
            Name string `json:"name" validate:"required"`
            Age  int    `json:"age" validate:"gte=0,lte=130"`
        }

        func ProcessTags(v interface{}) map[string]map[string]string {
            t := reflect.TypeOf(v)
            if t.Kind() != reflect.Struct {
                return nil
            }

            tags := make(map[string]map[string]string)
            
            for i := 0; i < t.NumField(); i++ {
                field := t.Field(i)
                fieldTags := make(map[string]string)
                
                // json 태그 처리
                if jsonTag, ok := field.Tag.Lookup("json"); ok {
                    fieldTags["json"] = jsonTag
                }
                
                // validate 태그 처리
                if validateTag, ok := field.Tag.Lookup("validate"); ok {
                    fieldTags["validate"] = validateTag
                }
                
                tags[field.Name] = fieldTags
            }
            
            return tags
        }
        ```

2. unsafe 패키지
    1. 포인터 조작
        ```go
        func UnsafePointerExample() {
            // 문자열을 바이트 슬라이스로 변환 (복사 없이)
            str := "Hello, World!"
            bytes := *(*[]byte)(unsafe.Pointer(&str))
            
            // 슬라이스 헤더 직접 접근
            type sliceHeader struct {
                Data unsafe.Pointer
                Len  int
                Cap  int
            }
            
            // 정수 타입 변환
            var i int32 = 42
            ptr := unsafe.Pointer(&i)
            f := *(*float32)(ptr)
        }

        // 구조체 패딩 최적화
        type OptimizedStruct struct {
            a int64  // 8 bytes
            b int32  // 4 bytes
            c int16  // 2 bytes
            d int8   // 1 byte
        }
        ```

    2. 메모리 레이아웃
        ```go
        func MemoryLayout() {
            var x struct {
                a bool
                b int16
                c []int
            }

            // 필드 오프셋 출력
            fmt.Printf("a: offset=%v, size=%v\n",
                unsafe.Offsetof(x.a), unsafe.Sizeof(x.a))
            fmt.Printf("b: offset=%v, size=%v\n",
                unsafe.Offsetof(x.b), unsafe.Sizeof(x.b))
            fmt.Printf("c: offset=%v, size=%v\n",
                unsafe.Offsetof(x.c), unsafe.Sizeof(x.c))

            // 구조체 얼라인먼트
            fmt.Printf("Alignment: %v\n", unsafe.Alignof(x))
        }
        ```

3. plugin 패키지
    1. 플러그인 생성
        ```go
        // plugin/plugin.go
        package main

        import "fmt"

        func Hello() string {
            return "Hello from plugin!"
        }

        var Message = "Plugin message"

        type Plugin struct {
            Name string
        }

        func (p *Plugin) DoSomething() {
            fmt.Printf("Plugin %s doing something\n", p.Name)
        }
        ```

    2. 플러그인 사용
        ```go
        func LoadPlugin(path string) error {
            // 플러그인 로드
            p, err := plugin.Open(path)
            if err != nil {
                return err
            }

            // 심볼 조회
            hello, err := p.Lookup("Hello")
            if err != nil {
                return err
            }

            // 함수 호출
            if fn, ok := hello.(func() string); ok {
                fmt.Println(fn())
            }

            // 변수 조회
            msg, err := p.Lookup("Message")
            if err != nil {
                return err
            }
            fmt.Println(*msg.(*string))

            return nil
        }
        ```

4. 실용적인 예제
    1. JSON 마샬링 커스터마이징
        ```go
        type CustomMarshaler struct {
            Data map[string]interface{}
        }

        func (c *CustomMarshaler) MarshalJSON() ([]byte, error) {
            val := reflect.ValueOf(c.Data)
            modified := make(map[string]interface{})

            for _, key := range val.MapKeys() {
                value := val.MapIndex(key)
                modified[key.String()] = processValue(value.Interface())
            }

            return json.Marshal(modified)
        }

        func processValue(v interface{}) interface{} {
            val := reflect.ValueOf(v)
            switch val.Kind() {
            case reflect.Struct:
                return processStruct(val)
            case reflect.Slice:
                return processSlice(val)
            default:
                return v
            }
        }
        ```

    2. 동적 프록시 생성
        ```go
        type MethodInterceptor func(method string, args []interface{}) interface{}

        func CreateProxy(target interface{}, interceptor MethodInterceptor) interface{} {
            targetType := reflect.TypeOf(target)
            if targetType.Kind() != reflect.Ptr {
                panic("Target must be a pointer to struct")
            }

            proxyType := reflect.StructOf([]reflect.StructField{
                {
                    Name: "target",
                    Type: targetType,
                    Tag:  `proxy:"true"`,
                },
            })

            proxy := reflect.New(proxyType)
            proxy.Elem().Field(0).Set(reflect.ValueOf(target))

            return proxy.Interface()
        }
        ```

5. 성능과 안정성
    1. reflect 성능 최적화
        ```go
        // 캐시를 사용한 리플렉션 최적화
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
            
            method, ok := methods[name]
            return method, ok
        }

        func (c *TypeCache) cacheType(t reflect.Type, name string) (reflect.Method, bool) {
            c.mu.Lock()
            defer c.mu.Unlock()

            methods := make(map[string]reflect.Method)
            for i := 0; i < t.NumMethod(); i++ {
                method := t.Method(i)
                methods[method.Name] = method
            }
            
            c.cache[t] = methods
            method, ok := methods[name]
            return method, ok
        }
        ```

    2. 안전한 unsafe 사용
        ```go
        // 안전한 타입 변환
        func SafeTypeConversion(data interface{}, target interface{}) error {
            src := reflect.ValueOf(data)
            dst := reflect.ValueOf(target)

            if dst.Kind() != reflect.Ptr {
                return errors.New("target must be a pointer")
            }

            if !src.Type().ConvertibleTo(dst.Elem().Type()) {
                return fmt.Errorf("cannot convert %v to %v", 
                    src.Type(), dst.Elem().Type())
            }

            dst.Elem().Set(src.Convert(dst.Elem().Type()))
            return nil
        }
        ```

6. Best Practices
    1. reflect 사용
        - 성능 중요 코드에서는 피하기
        - 타입 안정성 보장
        - 에러 처리 철저히

    2. unsafe 사용
        - 필요한 경우에만 제한적 사용
        - 안전성 검사 추가
        - 문서화 철저히

    3. plugin 사용
        - 버전 호환성 고려
        - 에러 처리 추가
        - 플랫폼 제약 고려

7. 주의사항
    1. reflect 주의사항
        - 성능 오버헤드 고려
        - panic 가능성 처리
        - 타입 안정성 확보

    2. unsafe 주의사항
        - 메모리 안정성 위험
        - 가비지 컬렉션 영향
        - 플랫폼 종속성

    3. plugin 주의사항
        - 플랫폼 제약
        - 버전 호환성
        - 보안 위험