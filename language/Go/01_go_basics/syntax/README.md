# Go Syntax Fundamentals 🔤

이 디렉토리는 Go 언어의 **기본 문법**을 체계적으로 학습할 수 있도록 구성된 교육 자료를 제공합니다. 기본적인 구문부터 시작하여 고급 기능까지, Go 프로그래밍의 핵심 개념을 실전 예제를 통해 학습할 수 있습니다.

## Learning Objectives 🎯

Go 프로그래밍의 핵심 개념들을 단계별로 학습하며, 다음과 같은 능력을 기르게 됩니다:

- Go의 기본 구문과 타입 시스템 이해
- 함수형 프로그래밍과 객체 지향 프로그래밍 패턴 활용
- 에러 처리와 리소스 관리 전략 습득
- Go의 타입 시스템과 인터페이스 활용
- 테스트 작성과 성능 최적화 기법 습득

## Directory Structure 📁

```plaintext
01-go-basics/syntax/
├── main.go                         # 핵심 문법 예제
├── examples/
│   ├── 01_type_conversion.go      # 타입 변환 예제
│   ├── 02_error_handling.go       # 에러 처리 패턴
│   ├── 03_interfaces.go           # 인터페이스 활용
│   ├── 04_generics.go            # 제네릭 프로그래밍
│   ├── 05_reflection.go          # 리플렉션 활용
│   ├── 06_functional.go          # 함수형 프로그래밍
│   ├── 07_testing.go             # 테스트 작성
│   └── 08_context.go             # 컨텍스트 활용
└── README.md                      # 문서화
```

### Examples Directory Contents

examples 디렉토리는 다음과 같은 주제별 예제 파일을 포함합니다:

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
   - 다형성 활용
   - 컴포지션 패턴

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
   - 이터레이터 패턴

7. **Testing (07_testing.go)**:
   - 단위 테스트 작성
   - 테이블 기반 테스트
   - 벤치마크 테스트

8. **Context Usage (08_context.go)**:
   - 컨텍스트 생성과 활용
   - 타임아웃과 취소 처리
   - 값 전파 패턴

## Getting Started 🚀

1. **Prerequisites**:
   - Go 1.21 이상 설치
   - 코드 에디터 (VS Code 권장)
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
   go run examples/01_type_conversion.go
   ```

## Learning Path 📚

1. main.go의 기본 예제를 통해 Go의 핵심 문법을 학습합니다.
2. examples 디렉토리의 예제들을 순서대로 학습하며 심화 개념을 익힙니다.
3. 각 예제의 주석을 참고하여 코드의 동작 원리를 이해합니다.
4. 예제를 수정하고 확장하며 실험해봅니다.

## Best Practices 💡

- 각 예제 파일의 코드를 직접 실행하고 수정해보며 학습합니다.
- 코드의 동작을 예측하고 실제 결과와 비교해봅니다.
- 에러 메시지를 주의 깊게 읽고 이해합니다.
- Go 공식 문서를 참고하여 추가 학습을 진행합니다.

## Next Steps 🎯

기본 문법을 충분히 이해한 후에는 다음 단계로 진행하세요:

1. [동시성 프로그래밍](../concurrency/README.md)
2. [메모리 관리](../memory-management/README.md)
3. [입출력과 파일시스템](../io-filesystem/README.md)

Happy Coding! 🚀