# Go Package Management 📦

이 디렉토리는 Go 언어의 **패키지 관리**와 모듈 시스템을 학습할 수 있도록 설계된 교육 자료를 제공합니다. Go 모듈 초기화(`go.mod`), 외부 의존성 추가(`go get`), 그리고 사용자 정의 패키지 작성 및 사용 방법을 실습 예제를 통해 익힐 수 있습니다. 이 자료는 초보자부터 중급 개발자까지 활용 가능하며, 프로덕션 환경에서의 패키지 관리 모범 사례를 포함합니다.

## Learning Objectives 🎯

Go의 패키지 관리와 모듈 시스템을 단계별로 학습하며, 다음과 같은 능력을 기르게 됩니다:

- Go 모듈 시스템의 기본 개념 이해 (`go.mod`, `go.sum`)
- 프로젝트 초기화 및 외부 의존성 관리 (`go get`, `go mod tidy`)
- 사용자 정의 패키지 작성 및 재사용 가능한 코드 설계
- 패키지 네임스페이스와 버전 관리 이해
- 의존성 주입 및 모듈 간 상호작용 패턴 습득

## Directory Structure 📁

```plaintext
01-go-basics/packages/
├── main.go                         # 패키지 사용 예제
├── logger/                        # 사용자 정의 패키지 예제 디렉토리
│   ├── logger.go                  # 로깅 기능 패키지
│   └── logger_test.go             # 로깅 패키지 테스트
├── go.mod                         # 모듈 정의 파일
├── go.sum                         # 의존성 체크섬 파일
└── README.md                      # 문서화
```

### Key Files and Directories

- **`main.go`**: 외부 의존성과 사용자 정의 패키지를 사용하는 메인 실행 파일.
- **`logger/`**: 사용자 정의 패키지 예제 (`logger`)로, 간단한 로깅 기능을 구현.
  - `logger.go`: 로깅 기능 구현.
  - `logger_test.go`: 로깅 기능 단위 테스트.
- **`go.mod`**: 모듈 정의와 의존성 선언.
- **`go.sum`**: 의존성의 무결성을 보장하는 체크섬 파일.

## Getting Started 🚀

1. **Prerequisites**:
   - Go 1.21 이상 설치
   - 코드 에디터 (VS Code + Go 확장 권장)
   - Git

2. **Directory Setup**:
   ```bash
   # 리포지토리 클론
   git clone https://github.com/your-username/go-backend-roadmap.git
   cd go-backend-roadmap/01-go-basics/packages

   # 모듈 초기화 (최초 실행 시)
   go mod init github.com/your-username/go-backend-roadmap/01-go-basics/packages
   ```

3. **Dependencies Installation**:
   - 예제에서 사용할 외부 의존성 추가:
     ```bash
     go get github.com/sirupsen/logrus
     ```
   - 의존성 정리:
     ```bash
     go mod tidy
     ```

4. **Running Examples**:
   ```bash
   # 메인 예제 실행
   go run main.go

   # 테스트 실행
   go test ./logger -v
   ```

## Learning Path 📚

1. **`go.mod` 초기화**: 모듈 시스템의 기본 구조와 설정 방법을 학습합니다.
2. **의존성 추가**: 외부 패키지(`logrus`)를 추가하고 사용하는 과정을 실습합니다.
3. **사용자 정의 패키지**: `logger` 패키지를 작성하고, `main.go`에서 활용합니다.
4. **테스트 작성**: `logger_test.go`를 통해 패키지의 동작을 검증합니다.
5. **실험**: 패키지를 수정하거나 새 의존성을 추가하며 동작을 확인합니다.

## Example Workflow 🛠️

### 1. 모듈 초기화
```bash
go mod init github.com/your-username/go-backend-roadmap/01-go-basics/packages
```
- `go.mod` 파일이 생성되며, 모듈 이름과 Go 버전이 정의됩니다.

### 2. 외부 의존성 추가
```bash
go get github.com/sirupsen/logrus
```
- `logrus` 로깅 라이브러리를 추가하고, `go.mod`와 `go.sum`이 업데이트됩니다.

### 3. 사용자 정의 패키지 작성
- `logger/logger.go`에서 간단한 로깅 기능을 구현하고, `main.go`에서 호출합니다.

### 4. 테스트 실행
```bash
go test ./logger -v
```
- `logger_test.go`의 테스트 케이스를 실행하여 패키지 안정성 확인.

## Best Practices 💡

- **모듈 이름**: 고유한 모듈 경로(예: GitHub 경로)를 사용해 충돌 방지.
- **의존성 관리**: 사용하지 않는 의존성은 `go mod tidy`로 정리.
- **패키지 설계**: 단일 책임 원칙을 지키며, 공개 API는 대문자로 시작.
- **테스트**: 각 패키지에 단위 테스트를 작성하여 품질 보장.
- **버전 관리**: `go.mod`에 의존성 버전을 명시하고, 필요 시 `go get -u`로 업데이트.
- **빌드 점검**: `go build`와 `go vet`로 코드 오류 사전 확인.

## Next Steps 🎯

패키지 관리와 모듈 시스템을 익힌 후에는 다음 단계로 진행하세요:

1. [동시성 프로그래밍](../concurrency/README.md) - 고루틴과 채널 활용深化
2. [메모리 관리](../memory-management/README.md) - 메모리 최적화 기법
3. [입출력과 파일시스템](../io-filesystem/README.md) - 파일 및 네트워크 I/O

Happy Package Managing! 🚀