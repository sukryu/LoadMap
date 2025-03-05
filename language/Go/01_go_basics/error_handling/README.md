# Go Error Handling 🚨

이 디렉토리는 Go 언어의 **에러 처리** 기술을 심화 학습할 수 있도록 설계된 교육 자료를 제공합니다. 기본 에러 처리부터 커스텀 에러 타입, 에러 체인, 그리고 Go 1.13 이상에서 도입된 고급 기능(`errors.Is`, `errors.As`, `errors.Join`)까지 다룹니다. 초보자부터 중급 개발자까지 활용 가능하며, 실무에서 안정적이고 유지보수 가능한 에러 처리 전략을 익힐 수 있습니다.

## Learning Objectives 🎯

Go의 에러 처리 기술을 단계별로 학습하며, 다음과 같은 능력을 기르게 됩니다:

- 기본 에러 생성 및 처리 방법 이해
- 커스텀 에러 타입 설계 및 구현
- 에러 체인(wrapping)을 통한 컨텍스트 제공
- `errors.Is`와 `errors.As`를 활용한 에러 비교 및 타입 단언
- `errors.Join`을 사용한 다중 에러 집계
- 실무에서 유용한 에러 디버깅 및 로깅 전략 습득

## Directory Structure 📁

```plaintext
01-go-basics/error_handling/
├── main.go                         # 에러 처리 예제
├── errors/                        # 사용자 정의 에러 패키지 디렉토리
│   ├── custom_errors.go           # 커스텀 에러 타입 정의
│   └── custom_errors_test.go      # 커스텀 에러 테스트
├── go.mod                         # 모듈 정의 파일
├── go.sum                         # 의존성 체크섬 파일
└── README.md                      # 문서화
```

### Key Files and Directories

- **`main.go`**: 기본 에러 처리, 커스텀 에러, 에러 체인, `errors.Join` 등을 통합적으로 다루는 실행 파일.
- **`errors/`**: 사용자 정의 에러 타입을 구현하는 패키지.
  - `custom_errors.go`: 커스텀 에러 정의 및 헬퍼 함수.
  - `custom_errors_test.go`: 커스텀 에러의 동작 검증 테스트.
- **`go.mod`**: 모듈 정의와 의존성 선언.
- **`go.sum`**: 의존성 무결성을 보장하는 체크섬 파일.

## Getting Started 🚀

1. **Prerequisites**:
   - Go 1.21 이상 설치 (최신 에러 처리 기능 활용).
   - 코드 에디터 (VS Code + Go 확장 권장).
   - Git.

2. **Directory Setup**:
   ```bash
   # 리포지토리 클론
   git clone https://github.com/your-username/go-backend-roadmap.git
   cd go-backend-roadmap/01-go-basics/error_handling

   # 모듈 초기화 (최초 실행 시)
   go mod init github.com/your-username/go-backend-roadmap/01-go-basics/error_handling
   ```

3. **Dependencies Installation**:
   - 이 예제는 표준 라이브러리만 사용하므로 추가 의존성 설치 불필요.
   - 필요 시 정리:
     ```bash
     go mod tidy
     ```

4. **Running Examples**:
   ```bash
   # 메인 예제 실행
   go run main.go

   # 테스트 실행
   go test ./errors -v
   ```

## Learning Path 📚

1. **`main.go` 실행**: 기본 에러 처리와 고급 기능(`errors.Join`, 에러 체인)을 학습합니다.
2. **`errors/custom_errors.go` 분석**: 커스텀 에러 타입의 설계와 구현 방법을 익힙니다.
3. **테스트 실행**: `custom_errors_test.go`를 통해 에러 처리 동작을 검증합니다.
4. **실험**: 새로운 커스텀 에러를 추가하거나 에러 체인을 확장해보세요.
5. **디버깅 연습**: 에러 메시지와 스택 트레이스를 분석하며 디버깅 기술을 연마합니다.

## Example Workflow 🛠️

### 1. 모듈 초기화
```bash
go mod init github.com/your-username/go-backend-roadmap/01-go-basics/error_handling
```
- `go.mod` 파일이 생성되며 모듈 경로와 Go 버전이 정의됩니다.

### 2. 커스텀 에러 작성
- `errors/custom_errors.go`에서 사용자 정의 에러 타입을 구현하고, `main.go`에서 호출합니다.

### 3. 에러 체인 및 집계
- `fmt.Errorf`와 `%w`로 에러를 래핑하고, `errors.Join`으로 다중 에러를 통합합니다.

### 4. 테스트 실행
```bash
go test ./errors -v
```
- 커스텀 에러의 동작과 에러 체인 검증.

## Best Practices 💡

- **명확한 에러 메시지**: 에러 메시지는 구체적이고 실행 컨텍스트를 포함하세요.
- **커스텀 에러**: 특정 도메인에 맞는 에러 타입을 정의하여 명확성을 높이세요.
- **에러 래핑**: `fmt.Errorf`와 `%w`로 원인 에러를 체인에 포함시키세요.
- **에러 비교**: `errors.Is`로 특정 에러 확인, `errors.As`로 타입 단언 활용.
- **다중 에러 처리**: `errors.Join`으로 관련된 에러를 집계해 디버깅 용이성 확보.
- **테스트**: 모든 에러 케이스에 대해 단위 테스트를 작성하세요.
- **로깅**: 에러 발생 시 스택 트레이스나 컨텍스트를 로깅하세요 (예: `log.Printf("%+v", err)`).

## Next Steps 🎯

에러 처리를 충분히 익힌 후에는 다음 단계로 진행하세요:

1. [패키지 관리](../packages/README.md) - 모듈과 의존성 활용深化
2. [동시성 프로그래밍](../concurrency/README.md) - 고루틴과 채널 활용
3. [메모리 관리](../memory-management/README.md) - 메모리 최적화 기법

Happy Error Handling! 🚀