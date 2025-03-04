# Go Syntax Fundamentals 🔤

이 디렉토리는 Go 언어의 **기본 문법**을 체계적으로 학습할 수 있도록 구성된 교육 자료를 제공합니다. 기본적인 구문부터 고급 기능까지, Go 프로그래밍의 핵심 개념을 실전 예제를 통해 학습할 수 있습니다. 초보자부터 중급 개발자까지 사용할 수 있도록 설계되었으며, 프로덕션 환경에서 활용 가능한 코드 품질을 목표로 합니다.

## Learning Objectives 🎯

Go 프로그래밍의 핵심 개념들을 단계별로 학습하며, 다음과 같은 능력을 기르게 됩니다:

- Go의 기본 구문과 타입 시스템 이해 (포인터, 복합 타입 포함)
- 함수형 프로그래밍 및 객체 지향 프로그래밍 패턴 활용 (포인터 리시버, 인터페이스)
- 채널 및 슬라이스의 고급 활용 (닫기, 브로드캐스트, 3인덱스 슬라이싱)
- 동시성과 순회 패턴 습득 (이터레이터, 동시성 안전성)
- 에러 처리와 리소스 관리 전략 습득 (타입 단언, 빈 인터페이스)
- Go의 제네릭 및 리플렉션 활용
- 테스트 작성과 성능 최적화 기법 습득

## Directory Structure 📁

```plaintext
01-go-basics/syntax/
├── main.go                         # 핵심 문법 예제 (포인터 리시버 포함)
├── examples/
│   ├── 01_type_conversion.go      # 타입 변환 예제
│   ├── 02_error_handling.go       # 에러 처리 패턴
│   ├── 03_interfaces.go           # 인터페이스 활용 (타입 단언, 빈 인터페이스 추가)
│   ├── 04_generics.go             # 제네릭 프로그래밍
│   ├── 05_reflection.go           # 리플렉션 활용
│   ├── 06_functional.go           # 함수형 프로그래밍
│   ├── 07_testing.go              # 테스트 작성
│   ├── 08_context.go              # 컨텍스트 활용
│   ├── 09_channel_advanced.go     # 채널 고급 활용 (닫기, 브로드캐스트, 타임아웃)
│   ├── 10_slice_advanced.go       # 슬라이스 고급 활용 (3인덱스 슬라이싱, 다차원 슬라이스)
│   └── 11_iteration.go            # 순회 심화 (range, 이터레이터 패턴)
└── README.md                      # 문서화
```

### Examples Directory Contents

`examples` 디렉토리는 다음과 같은 주제별 예제 파일을 포함합니다:

1. **Type Conversion (01_type_conversion.go)**:
   - 숫자형, 문자열 간의 타입 변환
   - 사용자 정의 타입 변환
   - 안전한 타입 변환 패턴

2. **Error Handling (02_error_handling.go)**:
   - 사용자 정의 에러 타입
   - 에러 래핑과 언래핑
   - 에러 체인 관리

3. **Interfaces (03_interfaces.go)**:
   - 인터페이스 정의와 구현
   - 다형성과 타입 단언(Type Assertion)
   - 빈 인터페이스(`interface{}`) 활용

4. **Generics (04_generics.go)**:
   - 제네릭 함수와 타입
   - 제약 조건 활용
   - 제네릭 컨테이너 구현

5. **Reflection (05_reflection.go)**:
   - 런타임 타입 정보 활용
   - 동적 값 조작
   - 리플렉션 성능 고려사항

6. **Functional Programming (06_functional.go)**:
   - 고차 함수
   - 함수형 프로그래밍 패턴
   - 이터레이터 패턴 기본 활용

7. **Testing (07_testing.go)**:
   - 단위 테스트 작성
   - 테이블 기반 테스트
   - 벤치마크 테스트

8. **Context Usage (08_context.go)**:
   - 컨텍스트 생성과 활용
   - 타임아웃과 취소 처리
   - 값 전파 패턴

9. **Channel Advanced (09_channel_advanced.go)**:
   - 채널 닫기(`close`)와 안전한 수신
   - 브로드캐스트 패턴 (다중 수신자)
   - 타임아웃 처리 (`time.After`)

10. **Slice Advanced (10_slice_advanced.go)**:
    - 3인덱스 슬라이싱 (`slice[start:end:cap]`) 활용
    - 다차원 슬라이스 생성과 조작
    - 슬라이스 내부 구조 분석

11. **Iteration (11_iteration.go)**:
    - `range`의 다양한 활용 (인덱스/값 분리, 맵/구조체 순회)
    - 사용자 정의 이터레이터 패턴 (동시성 안전성 포함)
    - 이터레이터 재설정 및 재사용

## Getting Started 🚀

1. **Prerequisites**:
   - Go 1.21 이상 설치
   - 코드 에디터 (VS Code + Go 확장 권장)
   - Git

2. **Repository Setup**:
   ```bash
   git clone https://github.com/your-username/go-backend-roadmap.git
   cd go-backend-roadmap/01-go-basics/syntax
   ```

3. **Running Examples**:
   ```bash
   # 기본 예제 실행
   go run main.go

   # 특정 예제 실행
   go run examples/09_channel_advanced.go
   ```

## Learning Path 📚

1. `main.go`의 기본 예제를 통해 Go의 핵심 문법(포인터 리시버 포함)을 학습합니다.
2. `examples` 디렉토리의 예제들을 순서대로 실행하며 심화 개념을 익힙니다.
3. 각 예제의 주석을 참고하여 코드 동작 원리를 이해합니다.
4. 예제를 수정하고 확장하여 실험하며, 동시성 및 성능 테스트를 추가해보세요.

## Best Practices 💡

- 각 예제 파일을 직접 실행하고 수정하며 학습하세요.
- 코드의 동작을 예측한 뒤 실제 결과와 비교하여 이해를 깊이 합니다.
- 에러 메시지를 주의 깊게 분석하고, `go vet`와 같은 도구로 코드 점검하세요.
- Go 공식 문서 ([pkg.go.dev](https://pkg.go.dev/))와 소스 코드를 참고해 추가 학습하세요.
- 동시성 예제는 `go run -race`로 데이터 레이스 점검을 수행하세요.

## Next Steps 🎯

기본 문법을 충분히 이해한 후에는 다음 단계로 진행하세요:

1. [동시성 프로그래밍](../concurrency/README.md) - 고루틴과 채널의 실무 활용
2. [메모리 관리](../memory-management/README.md) - 메모리 최적화와 GC 튜닝
3. [입출력과 파일시스템](../io-filesystem/README.md) - 파일 처리와 네트워크 I/O

Happy Coding! 🚀