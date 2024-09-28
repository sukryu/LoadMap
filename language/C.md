# C 언어 #

## C 언어의 정의와 역사 ##

C언어는 1972년 벨 연구소의 Dennis Ritchie에 의해 개발된 범용 프로그래밍 언어입니다.
C는 UNIX 운영 체제를 개발하기 위해 만들어졌으며, 이후 컴퓨터 과학과 소프트웨어 개발 분야에서 혁명적인 변화를 가져왔습니다.

1. C 이전의 언어들:
    - 기계어: 컴퓨터가 직접 이해할 수 있는 이진 코드
    - 어셈블리: 기계어의 니모닉 표현
    - FORTRAN, COBOL: 고급 언어이지만 특정 분야에 특화됨.

2. C의 탄생 배경
    - UNIX 운영 체제 개발의 필요성
    - 하드웨어에 가까우면서도 추상화된 언어의 필요성
    - 이식성(portability)과 효율성의 균형 추구

## C 언어의 패러다임과 철학 ##

C 언어는 몇 가지 핵심적인 철학과 패러다임을 바탕으로 설계되었습니다.

1. 절차적 프로그래밍
    - C는 절차적 프로그래밍 언어입니다. 이는 프로그램이 일련의 절차나 함수들로 구성된다는 것을 의미합니다.
    프로그램의 실행은 이러한 절차들을 순차적으로 수행하는 것으로 이루어집니다.

2. 구조적 프로그래밍
    - C는 구조적 프로그래밍을 지원합니다. 이는 프로그램을 논리적 블록으로 구조화하여 가독성과 유지보수성을 향상시키는 방법입니다.
    `if-else`, `for`, `while` 등의 제어 구조를 사용하여 실현됩니다.

3. 최소주의 철학
    - C는 "프로그래머를 신뢰한다"는 철학을 가지고 있습니다. 이는 언어 자체에 많은 제약을 두지 않고, 프로그래머에게
    큰 자유와 책임을 부여한다는 의미입니다.

4. 효율성 중시
    - C는 하드웨어의 관점에서 생각할 수 있는 하이레벨 언어입니다. 이를 통해 높은 성능과 효율성을 달성 할 수 있습니다.

## C 언어의 주요 특징 ##

1. 이식성 (Portability)
    - C로 작성된 프로그램은 다양한 컴퓨터 아키텍처에서 실행될 수 있습니다. 이는 C 컴파일러가 각 플랫폼에 맞게 코드를 최적화하기 때문입니다.

2. 효율성 (Effciency)
    - C는 저수준 언어의 효율성과 고수준 언어의 추상화를 결합했습니다. 이로 인해 시스템 프로그래밍부터 응용 프로그램 개발까지 다양한 영역에서 사용될 수 있습니다.

3. 유연성 (Flexibility)
    - C는 프로그래머에게 많은 제어권을 제공합니다. 포인터를 통한 메모리 직접 접근, 비트 단위 연산 등이 가능합니다.

4. 표준 라이브러리
    - C는 풍부한 표준 라이브러리를 제공합니다. 이 라이브러리들은 파일 I/O, 문자열 처리, 메모리 관리 등 다양한 기능을 제공합니다.

## C 언어의 동작 방식 ##

C 언어로 작성된 프로그램이 실행되기까지의 과정을 이해하는 것은 매우 중요합니다. 이 과정은 크게 컴파일 단계와 실행 단계로 나눌 수 있습니다.

1. 컴파일 과정
    1. 전처리 (PreProcessing)
        - `#include`, `#define`등의 전처리기 지시문 처리
        - 매크로 확장
        - 조건부 컴파일 처리

    2. 컴파일 (Compilation)
        - 소스 코드를 어셈블리 코드로 변환
        - 문법 검사 수행
        - 최적화 수행 (컴파일러 옵션에 따라)

    3. 어셈블 (Assembly)
        - 어셈블리 코드를 기계어로 변환
        - 객체 파일 (.o 또는 .obj) 생성
    
    4. 링킹 (Linking)
        - 여러 객체 파일들을 하나의 실행 파일로 결합
        - 라이브러리 함수 연결
        - 메모리 주소 할당

2. 실행 과정
    1. 프로그램 로딩
        - 운영 체제가 실행 파일을 메모리에 로드
        
    2. 메모리 할당
        - 스택, 힙, 데이터 영역 등 메모리 영역 설정

    3. 초기화
        - 전역 변수 초기화
        - main() 함수 호출 준비

    4. 실행
        - CPU가 명령어를 순차적으로 실행
        - 함수 호출, 반환 등의 과정 수행

    5. 종료
        - 프로그램 실행 완료
        - 사용한 자원 해제

## C 언어의 메모리 모델 ##

C 언어의 강력함은 메모리를 직접 다룰 수 있다는 점에서 나옵니다. C 프로그램의 메모리는 크게 다음과 같이 구분됩니다.

1. 텍스트 영역 (Text Segment)
    - 실행 가능한 코드가 저장되는 영역
    - 읽기 전용

2. 데이터 영역 (Data Segment)
    - 초기화된 전역 변수와 정적 변수 저장
    - 프로그램 시작 시 초기화되고, 프로그램 종료 시까지 유지

3. BSS 영역 (BSS Segment)
    - 초기화되지 않은 전역 변수와 정적 변수 저장
    - 프로그램 시작 시 0으로 초기화

4. 힙 (Heap)
    - 동적으로 할당되는 메모리 영역
    - malloc(), calloc() 등으로 할당, free()로 해제
    - 프로그래머가 직접 관리해야 함.

5. 스택 (Stack)
    - 지역 변수, 함수 매개변수, 반환 주소 등 저장
    - 함수 호출 시 생성되고, 함수 종료 시 자동으로 해제
    - LIFO(Last In First Out)구조

## C 언어의 사용 목적 ##

C 언어는 다양한 목적으로 사용되지만, 주로 다음과 같은 영역에서 강점을 발휘합니다.

1. 시스템 프로그래밍
    - 운영 체제
    - 디바이스 드라이버
    - 임베디드 시스템

2. 응용 프로그램 개발
    - 데이터베이스 관리 시스템
    - 그래픽 소프트웨어
    - 게임 엔진

3. 성능 중심 애플리케이션
    - 실시간 시스템
    - 고성능 컴퓨팅
    - 네트워크 서버

4. 다른 프로그래밍 언어의 기반
    - 많은 현대 프로그래밍 언어들이 C의 영향을 받음
    - 예: C++, Objective-C, Java, Python 등

C 언어의 이러한 다양한 용도는 그 효율성, 유연성, 이식성 때문입니다. C로 작성된 코드는 높은 성능을 필요로 하는 영역에서 특히 유용합니다.


### 변수와 데이터 타입 ###

1. 변수의 개념
    - 변수는 프로그램에서 데이터를 저장하고 참조하는 데 사용되는 이름이 붙은 메모리 공간입니다. C 언어에서 변수는
    특정 데이터 타입을 가지며, 이 타입에 따라 변수가 저장할 수 있는 데이터의 종류와 크기가 결정됩니다.

    1. 변수 선언
        - C 언어에서 변수를 사용하기 전에 반드시 선언해야 합니다. 변수 선언의 기본 형식은 다음과 같습니다.

        ```c
        데이터타입 변수명;
        ```

        - 예를 들어:
        ```c
        int age;
        float temperature;
        char grade;
        ```

    2. 변수 초기화
        - 변수를 선언할 때 동시에 초기값을 할당할 수 있습니다.

        ```c
        int count = 0;
        float pi = 3.14159;
        char initial = 'A';
        ```

    3. 변수 명명 규칙
        1. 문자, 숫자, 언더스코어(_)만 사용 가능
        2. 첫 글자는 문자나 언더스코어로 시작
        3. 대소문자 구분
        4. 예약어 사용 불가

        - 예시:

        ```c
        int validVariable;
        int _also_valid;
        int NOT_VALID123; // 유효하지만 일반적으로 상수에 사용되는 명명 규칙
        // int 2invalid;  // 잘못된 예: 숫자로 시작
        // int void;      // 잘못된 예: 예약어 사용
        ```

2. 기본 데이터 타입

    1. 정수형:
        1. int: 일반적인 정수
        2. short: int보다 작은 범위의 정수
        3. long: int보다 큰 범위의 정수
        4. long long: long보다 큰 범위의 정수 (C99 이상)
        5. char: 문자를 저장하는 데 사용되지만, 작은 정수로도 사용 가능

        - 예제:
        ```c
        #include <stdio.h>
        #include <limits.h>

        int main() {
            int a = 10;
            short b = 20;
            long c = 30L;
            long long d = 40LL;
            char e = 'A';

            printf("int: %d (size: %zu bytes)\n", a, sizeof(int));
            printf("short: %hd (size: %zu bytes)\n", b, sizeof(short));
            printf("long: %ld (size: %zu bytes)\n", c, sizeof(long));
            printf("long long: %lld (size: %zu bytes)\n", d, sizeof(long long));
            printf("char: %c (ASCII: %d, size: %zu byte)\n", e, e, sizeof(char));

            printf("int 범위: %d to %d\n", INT_MIN, INT_MAX);

            return 0;
        }
        ```

    2. 부동소수점형:
        1. float: 단밀도 부동소수점
        2. double: 배정밀도 부동소수점
        3. long double: 확장 정밀도 부동소수점

        ```c
        #include <stdio.h>
        #include <float.h>

        int main() {
            float f = 3.14f;
            double d = 3.14159265359;
            long double ld = 3.14159265359L;

            printf("float: %f (size: %zu bytes)\n", f, sizeof(float));
            printf("double: %lf (size: %zu bytes)\n", d, sizeof(double));
            printf("long double: %Lf (size: %zu bytes)\n", ld, sizeof(long double));

            printf("float 정밀도: %d 자리\n", FLT_DIG);
            printf("double 정밀도: %d 자리\n", DBL_DIG);

            return 0;
        }
        ```

    3. 문자열
        - char 타입은 작은 정수로도 사용될 수 있지만, 주로 문자를 저장하는 데 사용됩니다.

        - 예제:
        ```c
        #include <stdio.h>

        int main() {
            char c1 = 'A';
            char c2 = 65;  // ASCII 코드로 'A'

            printf("c1: %c\n", c1);
            printf("c2: %c\n", c2);
            printf("c1 as integer: %d\n", c1);

            return 0;
        }
        ```

    4. 불리언형
        - C89까지는 불리언 타입이 없었지만, C99부터 _Bool타입이 도입되었습니다. `<stdbool.h>`헤더를 사용하면
        bool, true, false를 사용할 수 있습니다.

        - 예제:
        ```c
        #include <stdio.h>
        #include <stdbool.h>

        int main() {
            bool is_valid = true;
            _Bool is_active = 1;  // C99 스타일

            printf("is_valid: %d\n", is_valid);
            printf("is_active: %d\n", is_active);

            return 0;
        }
        ```

3. 형변환
    - C언어에서는 다른 타입 간의 변환이 필요할 때 형변환을 사용합니다.

    1. 암시적 형변환 (자동 형변환)
        - 컴파일러가 자동으로 수행하는 형변환입니다.

        - 예제:
        ```c
        #include <stdio.h>

        int main() {
            int i = 10;
            float f = 3.14;
            double d = i + f;  // int가 float로 변환된 후 계산되고, 결과는 double로 저장

            printf("d: %lf\n", d);

            return 0;
        }
        ```

    2. 명시적 형변환 (강제 형변환)
        - 프로그래머가 직접 지정하는 형변환입니다.

        - 예제:
        ```c
        #include <stdio.h>

        int main() {
            float f = 3.14;
            int i = (int)f;  // float를 int로 명시적 변환

            printf("f: %f\n", f);
            printf("i: %d\n", i);

            return 0;
        }
        ```

4. 상수
    - 변경되지 않는 값을 나타내는 데 사용됩니다.

    1. 리터럴 상수
        - 직접 값을 표현하는 방식입니다.

        - 예제:
        ```c
        int count = 10;  // 10은 정수 리터럴
        float pi = 3.14f;  // 3.14f는 float 리터럴
        char newline = '\n';  // '\n'은 문자 리터럴
        ```

    2. const 키워드
        - 변수를 상수로 선언합니다.

        - 예제:
        ```c
       #include <stdio.h>

        int main() {
            const int MAX_SIZE = 100;
            // MAX_SIZE = 200;  // 오류: const 변수는 수정할 수 없음

            printf("MAX_SIZE: %d\n", MAX_SIZE);

            return 0;
        } 
        ```

    3. #define 전처리기
        - 상수를 정의하는 또 다른 방법입니다.

        - 예제:
        ```c
        #include <stdio.h>

        #define PI 3.14159

        int main() {
            float radius = 5.0;
            float area = PI * radius * radius;

            printf("원의 넓이: %f\n", area);

            return 0;
        }
        ```

5. 열거형 (Enumeration)
    - 관련된 상수들의 집합을 정의합니다.

    - 예제:
    ```c
    #include <stdio.h>

    enum Days {SUN, MON, TUE, WED, THU, FRI, SAT};

    int main() {
        enum Days today = WED;

        printf("오늘은 %d번째 요일입니다.\n", today);

        return 0;
    }
    ```

6. 실제 사용 예제
    - 다음은 학생 관리 프로그램의 일부로, 다양한 데이터 타입과 변수를 사용하는 예제입니다:

    ```c
    #include <stdio.h>
    #include <string.h>
    #include <stdbool.h>

    #define MAX_NAME_LENGTH 50
    #define MAX_STUDENTS 100

    int main() {
        char names[MAX_STUDENTS][MAX_NAME_LENGTH];
        int ages[MAX_STUDENTS];
        float grades[MAX_STUDENTS];
        bool is_passing[MAX_STUDENTS];
        int num_students = 0;

        // 학생 정보 입력
        while (num_students < MAX_STUDENTS) {
            printf("학생 이름 (종료하려면 'q' 입력): ");
            scanf("%s", names[num_students]);
            
            if (strcmp(names[num_students], "q") == 0) {
                break;
            }

            printf("나이: ");
            scanf("%d", &ages[num_students]);

            printf("성적: ");
            scanf("%f", &grades[num_students]);

            is_passing[num_students] = (grades[num_students] >= 60.0);

            num_students++;
        }

        // 학생 정보 출력
        printf("\n--- 학생 정보 ---\n");
        for (int i = 0; i < num_students; i++) {
            printf("이름: %s, 나이: %d, 성적: %.2f, 합격여부: %s\n",
                names[i], ages[i], grades[i],
                is_passing[i] ? "합격" : "불합격");
        }

        return 0;
    }
    ```

7. 연습 문제
    1. 문제: 섭씨 온도를 화씨 온도로 변환하는 프로그램을 작성하세요. 사용자로부터 섭씨 온도를 입력 받고,
    이를 화씨 온도로 변환하여 출력하세요. 변환 공식은 (섭씨 * 9/5) + 32 입니다.

    - 해결 방법:
    
    ```c
    #include <stdio.h>

    int main() {
        float celsius, fahrenheit;

        printf("섭씨 온도를 입력하세요: ");
        scanf("%f", &celsius);

        fahrenheit = (celsius * 9 / 5) + 32;

        printf("%.2f°C는 %.2f°F입니다.\n", celsius, fahrenheit);

        return 0;
    }
    ```

    2. 문제: 정수형 변수 두 개를 선언하고 초기화한 후, 이 두 변수의 값을 서로 교환하는 프로그램을 작성하세요.
    단, 추가적인 변수를 사용하지 않고 해결하세요.

    - 해결 방법:

    ```c
    #include <stdio.h>

    int main() {
        int a = 5, b = 10;

        printf("교환 전: a = %d, b = %d\n", a, b);

        a ^= b;
        b ^= a;
        a ^= b;

        printf("교환 후: a = %d, b = %d\n", a, b);

        return 0;
    }
    ```

### 연산자와 표현식 ###

1. 연산자 개요
    - 연산자는 프로그램에서 데이터를 조작하고 계산을 수행하는 데 사용되는 기호입니다.
    C 언어는 다양한 연산자를 제공하여 복잡한 연산을 수행할 수 있게 해줍니다.

2. 산술 연산자
    - 산술 연산자는 수학적 계산을 수행하는 데 사용됩니다.

    1. 기본 산술 연산자
        - `+`: (덧셈)
        - `-`: (뺄셈)
        - `*`: (곱셈)
        - `/`: (나눗셈)
        - `%`: (모듈로, 나머지)

        - 예제:
        ```c
        #include <stdio.h>

        int main() {
            int a = 10, b = 3;
            
            printf("a + b = %d\n", a + b);
            printf("a - b = %d\n", a - b);
            printf("a * b = %d\n", a * b);
            printf("a / b = %d\n", a / b);
            printf("a %% b = %d\n", a % b);

            return 0;
        }
        ```

        - 출력:
        ```bash
        a + b = 13
        a - b = 7
        a * b = 30
        a / b = 3
        a % b = 1
        ```

        - 주의사항:
            - 정수 나눗셈의 결과는 정수입니다 (소수점 이하 버림).
            - 0으로 나누면 런타임 에러가 발생합니다.

    2. 증감 연산자
        - `++`: (증가)
        - `--`: (감소)

        - 예제:
        ```c
        #include <stdio.h>

        int main() {
            int x = 5;
            
            printf("x   = %d\n", x);
            printf("x++ = %d\n", x++);
            printf("x   = %d\n", x);
            printf("++x = %d\n", ++x);
            
            return 0;
        }
        ```

        - 출력:
        ```bash
        x   = 5
        x++ = 5
        x   = 6
        ++x = 7
        ```

    3. 관계 연산자
        - 관계 연산자는 두 값을 비교하는 데 사용되며, 결과는 참(1) 또는 거짓(0)입니다.

        - `==`: (같음)
        - `!=`: (다름)
        - `<`: (작음)
        - `>`: (큼)
        - `<=`: (작거나 같음)
        - `>=`: (크거나 같음)

        - 예제:
        ```c
        #include <stdio.h>

        int main() {
            int a = 5, b = 7;
            
            printf("a == b: %d\n", a == b);
            printf("a != b: %d\n", a != b);
            printf("a < b: %d\n", a < b);
            printf("a > b: %d\n", a > b);
            printf("a <= b: %d\n", a <= b);
            printf("a >= b: %d\n", a >= b);

            return 0;
        }
        ```

        - 출력:
        ```c
        a == b: 0
        a != b: 1
        a < b: 1
        a > b: 0
        a <= b: 1
        a >= b: 0
        ```

    4. 논리 연산자
        - 논리 연산자는 조건을 결합하거나 부정하는 데 사용됩니다.

        - `&&`(AND)
        - `||`(OR)
        - `!`(NOT)

        - 예제:
        ```c
        #include <stdio.h>

        int main() {
            int a = 5, b = 0, c = 10;
            
            printf("(a > 0) && (b > 0): %d\n", (a > 0) && (b > 0));
            printf("(a > 0) || (b > 0): %d\n", (a > 0) || (b > 0));
            printf("!(a > 0): %d\n", !(a > 0));
            printf("(a > 0) && (c > 0): %d\n", (a > 0) && (c > 0));

            return 0;
        }
        ```

        - 출력:
        ```bash
        (a > 0) && (b > 0): 0
        (a > 0) || (b > 0): 1
        !(a > 0): 0
        (a > 0) && (c > 0): 1
        ```

    5. 비트 연산자
        - 비트 연산자는 개별 비트를 조작하는 데 사용됩니다.

        - `&`: (비트 AND)
        - `!`: (비트 OR)
        - `^`: (비트 XOR)
        - `~`: (비트 NOT)
        - `<<`: (왼쪽 시프트)
        - `>>`: (오르쪽 시프트)

        - 예제:
        ```c
        #include <stdio.h>

        int main() {
            unsigned char a = 5;  // 0000 0101
            unsigned char b = 9;  // 0000 1001
            
            printf("a & b = %d\n", a & b);   // 0000 0001
            printf("a | b = %d\n", a | b);   // 0000 1101
            printf("a ^ b = %d\n", a ^ b);   // 0000 1100
            printf("~a = %d\n", (unsigned char)~a);  // 1111 1010
            printf("a << 1 = %d\n", a << 1); // 0000 1010
            printf("b >> 1 = %d\n", b >> 1); // 0000 0100

            return 0;
        }
        ```

        - 출력:
        ```bash
        a & b = 1
        a | b = 13
        a ^ b = 12
        ~a = 250
        a << 1 = 10
        b >> 1 = 4
        ```

    6. 할당 연산자
        - 할당 연산자는 변수에 값을 할당하는 데 사용됩니다.

        - `=`: (기본 할당)
        - `+=`, `-=`, `*=`, `/=`, `%=`: (복합 할당)
        - `&=`, `|=`, `^=`, `<<=`, `>>=`: (비트 연산 복합 할당)

        - 예제:
        ```c
        #include <stdio.h>

        int main() {
            int x = 10;
            
            x += 5;  // x = x + 5
            printf("x += 5: %d\n", x);
            
            x *= 2;  // x = x * 2
            printf("x *= 2: %d\n", x);
            
            x &= 0xF;  // x = x & 0xF
            printf("x &= 0xF: %d\n", x);

            return 0;
        }
        ```

        - 출력:
        ```bash
        x += 5: 15
        x *= 2: 30
        x &= 0xF: 14
        ```

    7. 조건 연산자 (삼항 연산자)
        - 조건 연산자는 조건에 따라 두 값 중 하나를 선택합니다.

        - 구문: `조건 ? 참일 때 값 : 거짓일 때 값`

        - 예제:
        ```c
        #include <stdio.h>

        int main() {
            int a = 10, b = 20;
            int max = (a > b) ? a : b;
            
            printf("a와 b 중 큰 값: %d\n", max);

            return 0;
        }
        ```

        - 출력:
        ```bash
        a와 b 중 큰 값: 20
        ```

    8. sizeof 연산자
        - sizeof 연산자는 데이터 타입이나 변수의 크기(바이트)를 반환합니다.

        - 예제:
        ```c
        #include <stdio.h>

        int main() {
            int x;
            double y;
            
            printf("int의 크기: %zu 바이트\n", sizeof(int));
            printf("x의 크기: %zu 바이트\n", sizeof x);
            printf("double의 크기: %zu 바이트\n", sizeof(double));
            printf("y의 크기: %zu 바이트\n", sizeof y);

            return 0;
        }
        ```
        - 출력(시스템에 따라 다를 수 있음):

        ```bash
        int의 크기: 4 바이트
        x의 크기: 4 바이트
        double의 크기: 8 바이트
        y의 크기: 8 바이트
        ```

    9. 연산자 우선순위
        - C 언어에서 연산자들은 우선순위를 가지고 있어, 복잡한 표현식에서 어떤 연산이 먼저 수행될지 결정합니다.
        괄호를 사용하여 우선순위를 명시적으로 지정할 수 있습니다.

        - 예제:
        ```c
        #include <stdio.h>

        int main() {
            int result = 5 + 3 * 2;
            printf("5 + 3 * 2 = %d\n", result);
            
            result = (5 + 3) * 2;
            printf("(5 + 3) * 2 = %d\n", result);

            return 0;
        }
        ```

        - 출력:
        ```bash
        5 + 3 * 2 = 11
        (5 + 3) * 2 = 16
        ```

    10. 실제 사용 예제
        - 다음은 간단한 계산기 프로그램으로, 다양한 연산자를 사용하는 예제입니다.

        ```c
        #include <stdio.h>

        int main() {
            double num1, num2, result;
            char operator;

            printf("간단한 계산기\n");
            printf("사용 가능한 연산: +, -, *, /\n");
            printf("수식 입력 (예: 5 + 3): ");
            scanf("%lf %c %lf", &num1, &operator, &num2);

            switch(operator) {
                case '+':
                    result = num1 + num2;
                    break;
                case '-':
                    result = num1 - num2;
                    break;
                case '*':
                    result = num1 * num2;
                    break;
                case '/':
                    if(num2 != 0)
                        result = num1 / num2;
                    else {
                        printf("오류: 0으로 나눌 수 없습니다.\n");
                        return 1;
                    }
                    break;
                default:
                    printf("오류: 잘못된 연산자입니다.\n");
                    return 1;
            }

            printf("결과: %.2f %c %.2f = %.2f\n", num1, operator, num2, result);

            return 0;
        }
        ```

### 제어 구조 ###

1. 제어 구조 개요
    - 제어 구조는 프로그램의 실행 흐름을 제어하는 데 사용됩니다. C언어에서는 주로 다음과 같은 제어 구조를 사용합니다.

    1. 조건문 (if, if-else, switch)
    2. 반복문 (for, while, do-while)
    3. 분기문 (break, continue, goto)

2. 조건문
    1. if문
        - if 문은 가장 기본적인 조건문으로, 조건이 참일 때 특정 코드 블록을 실행합니다.

        - 구문:
            ```c
            if (조건) {
                // 조건이 참일 때 실행할 코드
            }
            ```

        - 예제:
            ```c
            #include <stdio.h>

            int main() {
                int age = 20;

                if (age >= 18) {
                    printf("성인입니다.\n");
                }

                return 0;
            }
            ```

    2. if-else 문
        - if-else 문은 조건이 참일 때와 거짓일 떄 각각 다른 코드 블록을 실행합니다.

        - 구문:
            ```c
            if (조건) {
                // 조건이 참일 때 실행할 코드
            } else {
                // 조건이 거짓일 때 실행할 코드
            }
            ```

            
        - 예제:
            ```c
            #include <stdio.h>

            int main() {
                int number = 7;

                if (number % 2 == 0) {
                    printf("%d는 짝수입니다.\n", number);
                } else {
                    printf("%d는 홀수입니다.\n", number);
                }

                return 0;
            }
            ```

    3. if-else if-else 문
        - 여러 조건을 순차적으로 검사하고 싶을 때 사용합니다.

        - 구문:
            ```c
            if (조건1) {
            // 조건1이 참일 때 실행할 코드
            } else if (조건2) {
                // 조건2가 참일 때 실행할 코드
            } else {
                // 모든 조건이 거짓일 때 실행할 코드
            }
            ```

        - 예제:
            ```c
            #include <stdio.h>

            int main() {
                int score = 85;

                if (score >= 90) {
                    printf("A 등급\n");
                } else if (score >= 80) {
                    printf("B 등급\n");
                } else if (score >= 70) {
                    printf("C 등급\n");
                } else {
                    printf("D 등급\n");
                }

                return 0;
            }
            ```

    4. switch 문
        - switch 문은 여러 가지 경우 중 하나를 선택할 때 사용합니다.

        - 구문:
            ```c
            switch (표현식) {
                case 상수1:
                    // 코드
                    break;
                case 상수2:
                    // 코드
                    break;
                default:
                    // 기본 코드
            }
            ```

        - 예제:
            ```c
            #include <stdio.h>

            int main() {
                char grade = 'B';

                switch (grade) {
                    case 'A':
                        printf("우수\n");
                        break;
                    case 'B':
                        printf("양호\n");
                        break;
                    case 'C':
                        printf("보통\n");
                        break;
                    default:
                        printf("노력 필요\n");
                }

                return 0;
            }
            ```

3. 반복문
    1. for 루프
        - for 루프는 초기화, 조건, 증감을 한 줄에 표현할 수 있어 간결합니다.

        - 구문:
            ```c
            for (초기화; 조건; 증감) {
                // 반복할 코드
            }
            ```

        - 예제:
            ```c
            #include <stdio.h>

            int main() {
                for (int i = 0; i < 5; i++) {
                    printf("%d ", i);
                }
                printf("\n");

                return 0;
            }
            ```

    2. while 루프
        - while 루프는 조건이 참인 동안 코드 블록을 실행합니다.

        - 구문:
            ```c
            while (조건) {
                // 반복할 코드
            }
            ```

        - 예제:
            ```c
            #include <stdio.h>

            int main() {
                int count = 0;

                while (count < 5) {
                    printf("%d ", count);
                    count++;
                }
                printf("\n");

                return 0;
            }
            ```

    3. do - while 루프
        - do-while 루프는 코드 블록을 최소한 한 번 실행한 후 조건을 검사합니다.

        - 구문:
            ```c
            do {
                // 반복할 코드
            } while (조건);
            ```

        - 예제:
            ```c
            #include <stdio.h>

            int main() {
                int num;

                do {
                    printf("양수를 입력하세요: ");
                    scanf("%d", &num);
                } while (num <= 0);

                printf("입력한 양수: %d\n", num);

                return 0;
            }
            ```

4. 분기문
    1. break 문
        - break 문은 현재의 루프나 switch 문을 즉시 종료합니다.

        - 예제:
            ```c
            #include <stdio.h>

            int main() {
                for (int i = 0; i < 10; i++) {
                    if (i == 5) {
                        break;
                    }
                    printf("%d ", i);
                }
                printf("\n");

                return 0;
            }
            ```

    2. continue 문
        - continue 문은 현재 반복을 건너뛰고 다음 반복으로 즉시 이동합니다.

        - 예제:
            ```c
            #include <stdio.h>

            int main() {
                for (int i = 0; i < 10; i++) {
                    if (i % 2 == 0) {
                        continue;
                    }
                    printf("%d ", i);
                }
                printf("\n");

                return 0;
            }
            ```

    3. goto 문
        - goto 문은 프로그램의 실행을 지정된 레이블로 무조건 이동시킵니다. 하지만 구조적 프로그래밍을 해치므로 사용을 권하지 않습니다.

        - 예제:
            ```c
            #include <stdio.h>

            int main() {
                int i = 0;

            start:
                if (i >= 5) goto end;
                printf("%d ", i);
                i++;
                goto start;

            end:
                printf("\n");
                return 0;
            }
            ```

5. 실제 사용 예제
    - 다음은 간단한 메뉴 기반 프로그램으로, 여러 제어 구조를 사용하는 예제입니다.

    ```c
    #include <stdio.h>

    int main() {
        int choice;
        int number;

        do {
            printf("\n간단한 계산기\n");
            printf("1. 짝수/홀수 판별\n");
            printf("2. 양수/음수 판별\n");
            printf("3. 종료\n");
            printf("선택하세요 (1-3): ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("숫자를 입력하세요: ");
                    scanf("%d", &number);
                    if (number % 2 == 0) {
                        printf("%d는 짝수입니다.\n", number);
                    } else {
                        printf("%d는 홀수입니다.\n", number);
                    }
                    break;
                case 2:
                    printf("숫자를 입력하세요: ");
                    scanf("%d", &number);
                    if (number > 0) {
                        printf("%d는 양수입니다.\n", number);
                    } else if (number < 0) {
                        printf("%d는 음수입니다.\n", number);
                    } else {
                        printf("0입니다.\n");
                    }
                    break;
                case 3:
                    printf("프로그램을 종료합니다.\n");
                    break;
                default:
                    printf("잘못된 선택입니다. 다시 선택해주세요.\n");
            }
        } while (choice != 3);

        return 0;
    }
    ```

### 함수 ###

1. 함수 개요
    - 함수는 특정 작업을 수행하는 코드 블록으로, 프로그램을 작은 단위로 나누어 모듈화하고 코드 재사용성을 높이는 데 사용됩니다.

2. 함수의 구조
    - C언어에서 함수의 기본 구조는 다음과 같습니다.

    ```c
    반환타입 함수이름(매개변수 목록) {
        // 함수 본문
        return 반환값; // 반환 타입이 void가 아닌 경우
    }
    ```

    - 예제:
    
    ```c
    int add(int a, int b) {
        return a + b;
    }
    ```

3. 함수 선언과 정의
    1. 함수 선언 (프로토타입)
        - 함수 선언은 컴파일러에게 함수의 존재를 알리는 역할을 합니다.

        ```c
        int add(int a, int b);  // 함수 선언
        ```

    2. 함수 정의
        - 함수 정의는 함수의 실제 구현을 포함합니다.

        ```c
        int add(int a, int b) {
            return a + b;
        }
        ```
4. 함수 호출
    - 함수를 사용하려면 함수를 호출해야 합니다.

    - 예제:
    ```c
    #include <stdio.h>

    int add(int a, int b);  // 함수 선언

    int main() {
        int result = add(5, 3);
        printf("5 + 3 = %d\n", result);
        return 0;
    }

    int add(int a, int b) {  // 함수 정의
        return a + b;
    }
    ```

5. 매개변수 전달 방식
    1. 값에 의한 전달 (Call by Value)
        - 기본적으로 C는 값에 의한 전달 방식을 사용합니다. 이 방식에서는 함수의 인자의 복사본이 전달됩니다.

        - 예제:
        ```c
        void swap(int x, int y) {
            int temp = x;
            x = y;
            y = temp;
        }

        int main() {
            int a = 5, b = 10;
            swap(a, b);
            printf("a: %d, b: %d\n", a, b);  // a: 5, b: 10 (값이 변경되지 않음)
            return 0;
        }
        ```

    2. 참조에 의한 전달 (Call by Reference)
        - 포인터를 사용하여 참조에 의한 전달을 구현할 수 있습니다.

        - 예제:
        ```c
        void swap(int *x, int *y) {
            int temp = *x;
            *x = *y;
            *y = temp;
        }

        int main() {
            int a = 5, b = 10;
            swap(&a, &b);
            printf("a: %d, b: %d\n", a, b);  // a: 10, b: 5 (값이 변경됨)
            return 0;
        }
        ```

6. 함수의 반환 값
    - 함수는 `return`문을 사용하여 값을 반환할 수 있습니다.

    - 예제:
    ```c
    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    int main() {
        printf("Max of 5 and 10 is: %d\n", max(5, 10));
        return 0;
    }
    ```

7. void 함수
    - 반환 값이 없는 함수는 `void` 타입으로 선언합니다.

    - 예제:
    ```c
    void printHello() {
        printf("Hello, World!\n");
    }

    int main() {
        printHello();
        return 0;
    }
    ```

8. 재귀 함수
    - 재귀 함수는 자기 자신을 호출하는 함수입니다.

    - 예제(팩토리얼 계산):
    ```c
    int factorial(int n) {
        if (n == 0 || n == 1) {
            return 1;
        }
        return n * factorial(n - 1);
    }

    int main() {
        printf("5! = %d\n", factorial(5));
        return 0;
    }
    ```

9. 함수 포인터
    - 함수 포인터는 함수의 주소를 저장하는 포인터입니다.

    - 예제:
    ```c
    int add(int a, int b) { return a + b; }
    int subtract(int a, int b) { return a - b; }

    int main() {
        int (*operation)(int, int);
        operation = add;
        printf("10 + 5 = %d\n", operation(10, 5));
        operation = subtract;
        printf("10 - 5 = %d\n", operation(10, 5));
        return 0;
    }
    ```

10. 인라인 함수
    - `inline` 키워드를 사용하여 함수를 인라인화할 수 있습니다. 이는 컴파일러에게 호출 대신 함수 본문을 직접 삽입하도록 제안하는 것입니다.

    - 예제:
    ```c
    inline int square(int x) {
        return x * x;
    }

    int main() {
        printf("5 squared is: %d\n", square(5));
        return 0;
    }
    ```

11. 가변 인자 함수
    - `stdarg.h`헤더를 사용하면 가변 개수의 인자를 받는 함수를 만들 수 있습니다.

    - 예제:
    ```c
    #include <stdio.h>
    #include <stdarg.h>

    int sum(int count, ...) {
        va_list args;
        va_start(args, count);

        int total = 0;
        for (int i = 0; i < count; i++) {
            total += va_arg(args, int);
        }

        va_end(args);
        return total;
    }

    int main() {
        printf("Sum: %d\n", sum(4, 10, 20, 30, 40));
        return 0;
    }
    ```

12. 실제 사용 예제:
    - 다음은 여러 함수를 사용하는 간단한 계산기 프로그램입니다.

    ```c
    #include <stdio.h>

    float add(float a, float b) { return a + b; }
    float subtract(float a, float b) { return a - b; }
    float multiply(float a, float b) { return a * b; }
    float divide(float a, float b) { return b != 0 ? a / b : 0; }

    float calculate(float a, float b, char op) {
        switch(op) {
            case '+': return add(a, b);
            case '-': return subtract(a, b);
            case '*': return multiply(a, b);
            case '/': return divide(a, b);
            default: return 0;
        }
    }

    int main() {
        float a, b, result;
        char op;

        printf("Enter calculation (e.g., 5 + 3): ");
        scanf("%f %c %f", &a, &op, &b);

        result = calculate(a, b, op);
        printf("Result: %.2f\n", result);

        return 0;
    }
    ```

### 배열과 문자열 ###

1. 배열 (Arrays)
    - 배열은 동일한 데이터 타입의 연속된 메모리 공간에 저장된 데이터의 집합입니다.

    1. 배열 선언과 초기화

        ```c
        int numbers[5];  // 크기가 5인 정수 배열 선언
        int values[] = {1, 2, 3, 4, 5};  // 초기화와 함께 선언
        ```

        - 예제:
        ```c
        #include <stdio.h>

        int main() {
            int scores[5] = {85, 92, 78, 90, 88};
            
            for (int i = 0; i < 5; i++) {
                printf("Score %d: %d\n", i+1, scores[i]);
            }

            return 0;
        }
        ```

    2. 다차원 배열
        - C 언어는 다차원 배열을 지원합니다.

            ```c
            int matrix[3][3] = {
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
            };
            ```

            - 예제:
            
            ```c
            #include <stdio.h>

            int main() {
                int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
                
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        printf("%d ", matrix[i][j]);
                    }
                    printf("\n");
                }

                return 0;
            }
            ```

    3. 배열과 함수
        - 배열을 함수에 전달할 때는 포인터로 전달됩니다.

            ```c
            void printArray(int arr[], int size) {
                for (int i = 0; i < size; i++) {
                    printf("%d ", arr[i]);
                }
                printf("\n");
            }

            int main() {
                int numbers[] = {1, 2, 3, 4, 5};
                printArray(numbers, 5);
                return 0;
            }
            ```

2. 문자열 (Strings)
    - C언어에서 문자열은 널 종료 문자 (`\0`)로 끝나는 문자 배열입니다.

    1. 문자열 선언과 초기화

        ```c
        char str1[] = "Hello";  // 자동으로 널 문자 추가
        char str2[6] = {'H', 'e', 'l', 'l', 'o', '\0'};  // 명시적 널 문자
        ```

        - 예제:
        
        ```c
        #include <stdio.h>

        int main() {
            char greeting[] = "Hello, World!";
            printf("%s\n", greeting);

            return 0;
        }
        ```

    2. 문자열 처리 함수
        - C언어는 `<string.h>`헤더에 문자열 처리를 위한 다양한 함수를 제공합니다.

        1. strlen(): 문자열 길이 계산
        2. strcpy(): 문자열 복사
        3. strcat(): 문자열 연결
        4. strcmp(): 문자열 비교

        - 예제:
            
            ```c
            #include <stdio.h>
            #include <string.h>

            int main() {
                char str1[20] = "Hello";
                char str2[] = "World";

                printf("Length of str1: %lu\n", strlen(str1));
                
                strcat(str1, " ");
                strcat(str1, str2);
                printf("Concatenated string: %s\n", str1);

                char str3[20];
                strcpy(str3, str1);
                printf("Copied string: %s\n", str3);

                if (strcmp(str1, str3) == 0) {
                    printf("str1 and str3 are identical\n");
                }

                return 0;
            }
            ```

    3. 문자열 입력 받기
        - `scanf()`나 `fgets()`함수를 사용하여 문자열을 입력받을 수 있습니다.

            ```c
            #include <stdio.h>

            int main() {
                char name[50];
                printf("Enter your name: ");
                fgets(name, sizeof(name), stdin);
                printf("Hello, %s", name);

                return 0;
            }
            ```

3. 배열과 포인터의 관계
    - 배열 이름은 배열의 첫 번째 요소를 가리키는 포인터로 사용될 수 있습니다.

        ```c
        int numbers[] = {1, 2, 3, 4, 5};
        int *ptr = numbers;  // numbers는 &numbers[0]와 동일

        printf("%d\n", *ptr);  // 1 출력
        printf("%d\n", *(ptr + 1));  // 2 출력
        ```

4. 실제 사용 예제:
    - 다음은 학생들의 성적을 관리하는 간단한 프로그램입니다.

    ```c
    #include <stdio.h>
    #include <string.h>

    #define MAX_STUDENTS 50
    #define MAX_NAME_LENGTH 30

    struct Student {
        char name[MAX_NAME_LENGTH];
        int score;
    };

    void addStudent(struct Student students[], int *count) {
        if (*count < MAX_STUDENTS) {
            printf("Enter student name: ");
            fgets(students[*count].name, MAX_NAME_LENGTH, stdin);
            students[*count].name[strcspn(students[*count].name, "\n")] = 0;  // Remove newline

            printf("Enter student score: ");
            scanf("%d", &students[*count].score);
            getchar();  // Consume newline

            (*count)++;
        } else {
            printf("Maximum number of students reached.\n");
        }
    }

    void printStudents(struct Student students[], int count) {
        printf("\nStudent List:\n");
        for (int i = 0; i < count; i++) {
            printf("%s: %d\n", students[i].name, students[i].score);
        }
    }

    int main() {
        struct Student students[MAX_STUDENTS];
        int studentCount = 0;
        char choice;

        do {
            printf("\n1. Add student\n2. Print students\n3. Exit\nEnter choice: ");
            scanf(" %c", &choice);
            getchar();  // Consume newline

            switch (choice) {
                case '1':
                    addStudent(students, &studentCount);
                    break;
                case '2':
                    printStudents(students, studentCount);
                    break;
                case '3':
                    printf("Exiting...\n");
                    break;
                default:
                    printf("Invalid choice. Try again.\n");
            }
        } while (choice != '3');

        return 0;
    }
    ```

### 포인터 ###

1. 포인터의 기본 개념
    - 포인터는 메모리 주소를 저장하는 `변수`입니다. 이를 통해 메모리를 직접 조작할 수 있어 효율적인 프로그래밍이 가능해집니다.

    1. 메모리와 주소
        - 컴퓨터의 메모리는 연속된 바이트들의 집합입니다.
        - 각 바이트는 고유한 주소를 가집니다.
        - 변수는 메모리의 특정 위치를 차지합니다.

    2. 포인터의 선언
        - 포인터는 asterisk(*)를 사용하여 선언합니다.

        ```c
        int *ptr; // 정수형 포인터 선언
        ```
        - 여기서 `ptr`은 정수형 변수의 주소를 저장할 수 있는 포인터입니다.

    3. 주소 연산자(&)와 역참조 연산자(*)
        - `&`연산자: 변수의 주소를 얻습니다.
        - `*`연산자: 포인터가 가리키는 주소의 값을 얻습니다(역참조).

        ```c
        int num = 10;
        int *ptr = &num;  // num의 주소를 ptr에 저장

        printf("num의 값: %d\n", num);        // 10
        printf("num의 주소: %p\n", (void*)&num);  // num의 메모리 주소
        printf("ptr의 값: %p\n", (void*)ptr);     // num의 메모리 주소
        printf("ptr이 가리키는 값: %d\n", *ptr);  // 10
        ```

2. 포인터와 데이터 타입
    - 포인터와 데이터 타입은 중요합니다. 이는 포인터가 가리키는 메모리의 크기와 해석 방법을 결정합니다.

    ```c
    int *iptr;     // int 타입 변수의 주소를 저장
    char *cptr;    // char 타입 변수의 주소를 저장
    double *dptr;  // double 타입 변수의 주소를 저장
    ```

    - 각 포인터 타입은 해당 데이터 타입의 크기만큼 메모리를 읽거나 씁니다.

3. 포인터 연산
    - 포인터에 대한 산술 연산은 해당 데이터 타입의 크기를 단위로 합니다.

    ```c
    int arr[5] = {10, 20, 30, 40, 50};
    int *ptr = arr;  // arr은 배열의 첫 번째 요소의 주소

    printf("%d\n", *ptr);     // 10
    printf("%d\n", *(ptr+1)); // 20
    printf("%d\n", *(ptr+2)); // 30

    // 포인터 증가
    ptr++;  // 다음 정수로 이동 (4바이트 이동)
    printf("%d\n", *ptr);  // 20
    ```

4. 포인터와 배열
    - 배열 이름은 배열의 첫 번째 요소를 가리키는 포인터로 취급됩니다.

    ```c
    int arr[5] = {10, 20, 30, 40, 50};
    int *ptr = arr;

    for(int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);    // 배열 표기법
        printf("%d ", *(arr + i));  // 포인터 산술
        printf("%d ", ptr[i]);      // 포인터를 배열처럼 사용
        printf("%d ", *(ptr + i));  // 포인터 산술
        printf("\n");
    }
    ```

5. 포인터와 문자열
    - C에서 문자열은 널 종료 문자(`\0`)로 끝나는 문자 배열입니다.

    ```c
    char str[] = "Hello";
    char *ptr = str;

    while(*ptr != '\0') {
        printf("%c", *ptr);
        ptr++;
    }
    ```

6. 포인터 함수
    1. 함수 인자로서의 포인터 (Call by Reference)
        
        ```c
        void swap(int *a, int *b) {
            int temp = *a;
            *a = *b;
            *b = temp;
        }

        int main() {
            int x = 5, y = 10;
            swap(&x, &y);
            printf("x = %d, y = %d\n", x, y);  // x = 10, y = 5
            return 0;
        }
        ```

    2. 포인터 반환
        - 함수는 포인터를 반환할 수 있습니다.

        ```c
        int* larger(int *a, int *b) {
            return (*a > *b) ? a : b;
        }

        int main() {
            int x = 5, y = 10;
            int *result = larger(&x, &y);
            printf("더 큰 값: %d\n", *result);  // 10
            return 0;
        }
        ```

    3. 함수 포인터
        - 함수의 주소를 저장하는 포인터입니다.

        ```c
        int add(int a, int b) { return a + b; }
        int subtract(int a, int b) { return a - b; }

        int main() {
            int (*operation)(int, int);
            operation = add;
            printf("5 + 3 = %d\n", operation(5, 3));
            operation = subtract;
            printf("5 - 3 = %d\n", operation(5, 3));
            return 0;
        }
        ```

7. 다중 포인터
    - 포인터의 포인터를 사용할 수 있습니다.

    ```c
    int num = 10;
    int *ptr1 = &num;
    int **ptr2 = &ptr1;
    int ***ptr3 = &ptr2;

    printf("%d\n", *ptr1);    // 10
    printf("%d\n", **ptr2);   // 10
    printf("%d\n", ***ptr3);  // 10
    ```

8. void 포인터
    - void 포인터는 모든 타입의 포인터로 변환될 수 있습니다.

    ```c
    void *vptr;
    int num = 10;
    float f = 3.14;

    vptr = &num;
    printf("%d\n", *(int*)vptr);

    vptr = &f;
    printf("%f\n", *(float*)vptr);
    ```

9. 동적 메모리 할당
    - C언어에서 동적 메모리 할당은 프로그램 실행 중에 메모리를 할당하고 해제하는 과정을 말합니다.
    이를 위해 주로 사용되는 함수들은 `malloc()`, `calloc()`, `realloc()`, `free()`입니다. 이 함수들은
    `<stdlib.h>`헤더 파일에 정의되어 있습니다.
    
    1. malloc() 함수:
        - 정의
        
            ```c
            void* malloc(size_t size);
            ```

        - 동작:
            - 지정된 크기(바이트 단위)의 메모리 블록을 할당합니다.
            - 할당된 메모리는 초기화되지 않습니다. (쓰레기 값을 포함할 수 있음.)
            - 성공 시 할당된 메모리의 첫 번째 바이트에 대한 포인터를 반환합니다.
            - 실패 시 NULL포인터를 반환합니다.

        - 사용 예:
        
            ```c
            int *ptr = (int*)malloc(5 * sizeof(int));
            if (ptr == NULL) {
                printf("메모리 할당 실패\n");
                return 1;
            }
            // 메모리 사용
            free(ptr);  // 사용 후 해제
            ```

        - 내부 동작
            1. 요청된 크기의 연속된 메모리 블록을 힙(heap)에서 찾습니다.
            2. 적절한 블록을 찾으면, 그 블록을 "사용 중"으로 표시합니다.
            3. 블록의 주소를 반환합니다.

        - 주의사항
            - 할당된 메모리는 반드시 `free()`로 해제해야 합니다.
            - 할당 실패 여부를 항상 확인해야 합니다.
            - 할당된 메모리의 크기를 초과하여 접근하면 안 됩니다.

    2. calloc() 함수
        - 정의
            
            ```c
            void* calloc(size_t num, size_t size);
            ```

        - 동작:
            - 지정된(num)만큼의 원소를 저장할 수 있는 메모리를 할당합니다. 각 원소의 크기는 size 바이트입니다.
            - 할당된 메모리를 모두 0으로 초기화합니다.
            - 성공 시 할당된 메모리의 첫 번째 바이트에 대한 포인터를 반환합니다.
            - 실패 시 NULL포인터를 반환합니다.

        - 사용 예:
            
            ```c
            int *ptr = (int*)calloc(5, sizeof(int));
            if (ptr == NULL) {
                printf("메모리 할당 실패\n");
                return 1;
            }
            // 메모리 사용
            free(ptr);  // 사용 후 해제
            ```

        - 내부 동작
            1. `malloc()`과 유사하게 메모리를 할당합니다.
            2. 할당된 메모리 전체를 0으로 초기화합니다.
            3. 블록의 주소를 반환합니다.

        - 주의사항
            - `malloc()`과 동일한 주의사항이 적용됩니다.
            - 초기화로 인해 `malloc()`보다 느릴 수 있습니다.

    3. realloc() 함수
        - 정의

            ```c
            void* realloc(void* ptr, size_t new_size);
            ```

        - 동작:
            - 이전에 할당된 메모리 블록의 크기를 변경합니다.
            - 새 크기가 더 크면 추가 메모리가 할당되고, 작으면 메모리가 해제됩니다.
            - 가능하면 기존 메모리 위치를 그대로 사용하지만, 불가능하면 새로운 위치로 데이터를 복사합니다.
            - 성공 시 재할당된 메모리의 포인터를 반환합니다(새 위치일 수 있음).
            - 실패 시 NULL을 반환하고, 원본 메모리는 변경되지 않습니다.

        - 사용 예:

            ```c
            int *ptr = (int*)malloc(5 * sizeof(int));
            // ... 메모리 사용 ...
            ptr = (int*)realloc(ptr, 10 * sizeof(int));
            if (ptr == NULL) {
                printf("메모리 재할당 실패\n");
                return 1;
            }
            // 추가 메모리 사용
            free(ptr);  // 사용 후 해제
            ``` 

        - 내부 동작
            1. 새 크기가 현재 크기보다 작으면, 메모리 블록의 크기를 줄입니다.
            2. 새 크기가 더 크고 현재 위치에서 확장이 가능하면, 그 자리에서 확장합니다.
            3. 확장이 불가능하면, 새로운 위치에 메모리를 할당하고 데이터를 복사합니다.
            4. 원본 메모리를 해제하고, 새 메모리의 주소를 반환합니다.

        - 주의사항
            - NULL 포인터로 호출하면 `malloc()`처럼 동작합니다.
            - 크기를 0으로 지정하면 메모리를 해제하고 NULL을 반환합니다.
            - 재할당 후에는 항상 반환값을 확인해야 합니다. 원본 포인터가 무효화될 수 있습니다.

    4. free() 함수
        - 정의

            ```c
            void free(void* ptr);
            ```

        - 동작

            - 이전에 `malloc()`, `calloc()`, 또는 `realloc()`으로 할당된 메모리를 해제합니다.
            - 해제된 메모리는 프로그램에서 다시 사용할 수 있게 됩니다.

        - 사용 예:
            
            ```c
            int *ptr = (int*)malloc(5 * sizeof(int));
            // ... 메모리 사용 ...
            free(ptr);
            ptr = NULL;  // 해제 후 NULL로 설정 (선택사항이지만 권장됨)
            ```

        - 내부 동작
            1. 메모리 블록을 '사용 가능'상태로 표시합니다.
            2. 인접한 사용 가능한 블록들과 병합할 수 있는지 확인합니다.
            3. 메모리 관리 세스템에 해제된 메모리를 반환합니다.

        - 주의사항
            - 이미 해제된 메모리를 다시 해제하면 정의되지 않은 동작이 발생합니다(이중 해제 오류)
            - NULL포인터를 해제하는 것은 안전하며, 아무 동작도 하지 않습니다.
            - 해제 후에는 포인터를 NULL로 설정하는 것이 좋습니다.(dangling pointer 방지)

    5. 메모리 누스 (Memory Leak)
        - 메모리 누수는 할당된 메모리를 적절히 해제하지 않을 때 발생합니다. 이는 프로그램의 메모리
        사용량을 증가시키고, eventually out of memory오류를 발생시킬 수 있습니다.

        - 메모리 누수 예방 방법
            1. 모든 동적 할당된 메모리를 사용 후 반드시 해제합니다.
            2. 함수에서 동적 할당된 메모리를 반환할 때, 호출자에게 해제 책임을 명확히 전달합니다.
            3. 복잡한 데이터 구조에서는 모든 메모리를 추적하고 해제합니다.
            4. 스마트 포인터(C++에서)또는 가비지 컬렉션(다른 언어들)을 사용하는 것을 고려합니다.

    6. 실제 사용 예제: 동적 배열 구현
        - 다음은 동적으로 크기가 조절되는 정수 배열을 구현하는 예제입니다.

        ```c
        #include <stdio.h>
        #include <stdlib.h>

        typedef struct {
            int* array;
            size_t used;
            size_t size;
        } DynamicArray;

        void initArray(DynamicArray* a, size_t initialSize) {
            a->array = (int*)malloc(initialSize * sizeof(int));
            a->used = 0;
            a->size = initialSize;
        }

        void insertArray(DynamicArray* a, int element) {
            if (a->used == a->size) {
                a->size *= 2;
                a->array = (int*)realloc(a->array, a->size * sizeof(int));
            }
            a->array[a->used++] = element;
        }

        void freeArray(DynamicArray* a) {
            free(a->array);
            a->array = NULL;
            a->used = a->size = 0;
        }

        int main() {
            DynamicArray a;
            initArray(&a, 5);  // 초기 크기 5로 시작

            for (int i = 0; i < 10; i++) {
                insertArray(&a, i);  // 10개 요소 삽입 (자동으로 크기 증가)
            }

            printf("배열 내용: ");
            for (size_t i = 0; i < a.used; i++) {
                printf("%d ", a.array[i]);
            }
            printf("\n");

            freeArray(&a);  // 메모리 해제
            return 0;
        }
        ```
            
### 구조체와 공용체 ###

1. 구조체 (Structures)
    - 구조체는 서로 다른 데이터 타입의 변수들을 하나의 단위로 그룹화하는 사용자정의 데이터 타입입니다.

    1. 구조체 정의

        ```c
        struct Person {
            char name[50];
            int age;
            float height;
        };
        ```

    2. 구조체 변수 선언

        ```c
        struct Person person1;
        struct Person person2 = {"John Doe", 30, 175.5};
        ```

    3. 구조체 멤버 접근

        ```c
        strcpy(person1.name, "Jane Doe");
        person1.age = 25;
        person1.height = 165.0;

        printf("Name: %s, Age: %d, Height: %.1f\n", person1.name, person1.age, person1.height);
        ```

    4. 구조체 포인터

        ```c
        struct Person *ptr = &person1;
        printf("Name: %s, Age: %d\n", ptr->name, ptr->age);
        ```

    5. 구조체 배열

        ```c
        struct Person people[3] = {
            {"Alice", 20, 160.0},
            {"Bob", 22, 175.0},
            {"Charlie", 21, 170.0}
        };
        ```

    6. 구조체 중첩

        ```c
        struct Address {
            char street[100];
            char city[50];
            char country[50];
        };

        struct Employee {
            char name[50];
            int id;
            struct Address address;
        };
        ```

    7. typedef를 사용한 구조체

        ```c
        typedef struct {
            char brand[50];
            int year;
        } Car;

        Car myCar = {"Toyota", 2020};
        ```

2. 공용체 (Unions)
    - 공용체는 여러 데이터 타입 중 하나를 저장할 수 있는 메모리 공간을 제공합니다. 모든 멤버가 같은 메모리 위치를 공유합니다.

    1. 공용체 정의

        ```c
        union Data {
            int i;
            float f;
            char str[20];
        };
        ```

    2. 공용체 변수 선언
        
        ```c
        union Data data;
        ```

    3. 공용체 멤버 접근

        ```c
        data.i = 10;
        printf("Integer: %d\n", data.i);

        data.f = 3.14;
        printf("Float: %f\n", data.f);

        strcpy(data.str, "Hello");
        printf("String: %s\n", data.str);
        ```

3. 구조체와 공용체의 메모리 레이아웃
    1. 구조체의 메모리 레이아웃
        - 구조체는 각 멤버를 순차적으로 메모리에 저장합니다.

        ```c
        struct Example {
            char c;    // 1 byte
            int i;     // 4 bytes
            double d;  // 8 bytes
        };
        ```

        - 이 구조체의 크기는 멤버들의 단순한 합보다 클 수 있습니다(패딩 때문).

    2. 공용체 메모리 레이아웃
        - 공용체는 가장 큰 멤버의 크기만큼 메모리를 할당합니다.

        ```c
        union Example {
            char c;    // 1 byte
            int i;     // 4 bytes
            double d;  // 8 bytes
        };
        ```

        - 이 공용체의 크기는 8바이트입니다(가장 큰 멤버인 double의 크기).

4. 구조체와 함수
    1. 구조체를 함수 인자로 전달

        ```c
        void printPerson(struct Person p) {
            printf("Name: %s, Age: %d\n", p.name, p.age);
        }
        ```
    
    2. 구조체 포인터를 함수 인자로 전달

        ```c
        void updateAge(struct Person *p, int newAge) {
            p->age = newAge;
        }
        ```

    3. 구조체를 반환하는 함수
        
        ```c
        struct Person createPerson(const char *name, int age) {
            struct Person p;
            strcpy(p.name, name);
            p.age = age;
            return p;
        }
        ```

5. 구조체 비트 필드
    - 비트필드를 사용하여 구조체 멤버의 비트 수를 지정할 수 있습니다.

    ```c
    struct PackedData {
        unsigned int flag : 1;
        unsigned int data : 7;
    };
    ```

6. 공용체의 활용
    - 공용체는 여러 데이터 타입을 하나의 메모리 공간에 저장할 때 유용합니다.

    ```c
    union IPAddress {
        uint32_t address;
        struct {
            uint8_t a;
            uint8_t b;
            uint8_t c;
            uint8_t d;
        } octets;
    };
    ```

7. 실제 사용 예제: 도서관 관리 시스템
    - 다음은 구조체를 사용한 간단한 도서 관리 시스템의 예입니다:

    ```c
    #include <stdio.h>
    #include <string.h>

    #define MAX_BOOKS 100

    struct Book {
        char title[100];
        char author[50];
        int year;
        float price;
    };

    struct Library {
        struct Book books[MAX_BOOKS];
        int count;
    };

    void addBook(struct Library *lib, const char *title, const char *author, int year, float price) {
        if (lib->count < MAX_BOOKS) {
            struct Book *book = &lib->books[lib->count];
            strcpy(book->title, title);
            strcpy(book->author, author);
            book->year = year;
            book->price = price;
            lib->count++;
            printf("책이 추가되었습니다.\n");
        } else {
            printf("라이브러리가 가득 찼습니다.\n");
        }
    }

    void printBooks(const struct Library *lib) {
        printf("도서 목록:\n");
        for (int i = 0; i < lib->count; i++) {
            const struct Book *book = &lib->books[i];
            printf("%d. '%s' by %s (%d) - $%.2f\n", 
                i+1, book->title, book->author, book->year, book->price);
        }
    }

    int main() {
        struct Library library = {0};

        addBook(&library, "The C Programming Language", "K&R", 1978, 29.99);
        addBook(&library, "C: A Modern Approach", "K. N. King", 2008, 69.99);
        addBook(&library, "C Programming: A Modern Approach", "K. N. King", 1996, 45.99);

        printBooks(&library);

        return 0;
    }
    ```

### 파일 입출력 ###

1. 파일 입출력 개요
    - C언어에서 파일 입출력은 `<stdio.h>`헤더 파일에 정의된 함수들을 사용하여 수행합니다.
    파일 처리의 기본 단계는 다음과 같습니다.

    1. 파일 열기(open)
    2. 파일 읽기 또는 쓰기 (read/write)
    3. 파일 닫기 (close)

2. 파일 포인터
    - 파일 처리를 위해 FILE 구조체에 대한 포인터를 사용합니다.

    ```c
    FILE *fp;
    ```

3. 파일 열기: fopen()

    ```c
    FILE *fopen(const char *filename, const char *mode);
    ```

    - 주요 모드:

        - "r": 읽기 모드
        - "w": 쓰기 모드(파일이 존재하면 내용을 지움)
        - "a": 추가 모드(파일 끝에 내용을 추가)
        - "r+": 읽기와 쓰기 모드
        - "w+": 읽기와 쓰기 모드 (파일이 존재하면 내용을 지움)
        - "a+": 읽기와 추가 모드

    - 예제:

        ```c
        FILE *fp = fopen("example.txt", "r");
        if (fp == NULL) {
            printf("파일을 열 수 없습니다.\n");
            return 1;
        }
        ```

4. 파일 닫기: fclose()

    ```c
    int fclose(FILE *fp);
    ```

    - 예제:
    ```c
    fclose(fp);
    ```
    

5. 파일 읽기
    1. 문자 단위 읽기: fgetc()

        ```c
        int fgetc(FILE *fp);
        ```

        - 예제:

        ```c
        int ch;
        while ((ch = fgetc(fp)) != EOF) {
            putchar(ch);
        }
         ```

    2. 문자열 읽기: fgets()

        ```c
        char *fgets(char *str, int n, FILE *fp);
        ```

        - 예제:

        ```c
        char buffer[100];
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%s", buffer);
        }
        ```

    3. 형식화된 읽기: fscanf()

        ```c
        int fscanf(FILE *fp, const char *format, ...);
        ```

        - 예제:

        ```c
        int num;
        char str[50];
        while (fscanf(fp, "%d %s", &num, str) == 2) {
            printf("Number: %d, String: %s\n", num, str);
        }
        ```

6. 파일 쓰기
    1. 문자 단위 쓰기: fputc()

        ```c
        int fputc(int ch, FILE *fp);
        ```

        - 예제:

        ```c
        for (char ch = 'A'; ch <= 'Z'; ch++) {
            fputc(ch, fp);
        }
        ```

    2. 문자열 쓰기: fputs()

        ```c
        int fputs(const char *str, FILE *fp);
        ```

        - 예제:

        ```c
        fputs("Hello, World!\n", fp);
        ```

    3. 형식화된 쓰기: fprintf()

        ```c
        int fprintf(FILE *fp, const char *format, ...);
        ```

        - 예제:

        ```c
        int num = 123;
        char *str = "Test";
        fprintf(fp, "Number: %d, String: %s\n", num, str);
        ```

7. 파일 위치 제어
    1. 파일 위치 이동: fseek()

        ```c
        int fseek(FILE *fp, long offset, int whence);
        ```

        - whence 값:
            - SEEK_SET: 파일 시작
            - SEEK_CUR: 현재 위치
            - SEEK_END: 파일 끝

        - 예제:

        ```c
        fseek(fp, 10, SEEK_SET);  // 파일의 10번째 바이트로 이동
        ```

    2. 현재 파일 위치 확인: ftell()

        ```c
        long ftell(FILE *fp);
        ```

        - 예제:

        ```c
        long pos = ftell(fp);
        printf("현재 파일 위치: %ld\n", pos);
        ```

    3. 파일 위치 초기화: rewind()

        ```c
        void rewind(FILE *fp);
        ```

        - 예제:

        ```c
        rewind(fp);  // 파일 위치를 처음으로 되돌림
        ```

8. 이진 파일 입출력
    1. 이진 파일 읽기: fread()
        
        ```c
        size_t fread(void *ptr, size_t size, size_t nmemb, FILE *fp);
        ```

    2. 이진 파일 쓰기: fwrite()

        ```c
        size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *fp);
        ```

        - 예제:

        ```c
        struct Record {
            int id;
            char name[50];
        };

        struct Record record = {1, "John Doe"};

        // 쓰기
        fwrite(&record, sizeof(struct Record), 1, fp);

        // 읽기
        struct Record read_record;
        fread(&read_record, sizeof(struct Record), 1, fp);
        ```

9. 에러 처리
    1. 파일 끝 확인: feof()

        ```c
        int feof(FILE *fp);
        ```

    2. 파일 에러 확인: ferror()

        ```c
        int ferror(FILE *fp);
        ```

        - 예제:

        ```c
        if (ferror(fp)) {
            printf("파일 읽기/쓰기 중 에러 발생\n");
            clearerr(fp);  // 에러 플래그 초기화
        }
        ```

10. 실제 사용 예제: 간단한 텍스트 파일 복사 프로그램

    ```c
    #include <stdio.h>

    #define BUFFER_SIZE 1000

    int main() {
        FILE *source, *destination;
        char buffer[BUFFER_SIZE];
        size_t bytes;

        source = fopen("source.txt", "r");
        if (source == NULL) {
            printf("원본 파일을 열 수 없습니다.\n");
            return 1;
        }

        destination = fopen("destination.txt", "w");
        if (destination == NULL) {
            printf("대상 파일을 생성할 수 없습니다.\n");
            fclose(source);
            return 1;
        }

        while ((bytes = fread(buffer, 1, BUFFER_SIZE, source)) > 0) {
            fwrite(buffer, 1, bytes, destination);
        }

        printf("파일이 성공적으로 복사되었습니다.\n");

        fclose(source);
        fclose(destination);

        return 0;
    }
    ```

### 전처리기 ###

1. 전처리기 개요
    - 전처리기는 C컴파일러의 일부로, 실제 컴파일 전에 소스 코드를 처리합니다. 주요 기능은 다음과 같습니다.

    - 파일 포함
    - 매크로 확장
    - 조건부 컴파일

    - 전처리기 지시문은 항상 `#`기호로 시작합니다.

2. 파일 포함: #include
    - 다른 파일의 내용을 현재 파일에 포함시킵니다.

    ```c
    #include <stdio.h>  // 시스템 헤더 파일
    #include "myheader.h"  // 사용자 정의 헤더 파일
    ```

3. 매크로 정의: #define
    1. 간단한 매크로

        ```c
        #define PI 3.14159
        #define MAX(a, b) ((a) > (b) ? (a) : (b))
        ```

        - 사용 예:

        ```c
        float area = PI * radius * radius;
        int max_value = MAX(x, y);
        ```

    2. 함수형 매크로

        ```c
        #define SQUARE(x) ((x) * (x))
        ```

        사용 예:

        ```c
        int result = SQUARE(5);  // 25
        ```

        주의: 매크로 인자를 항상 괄호로 감싸야 합니다.

    3. 다중 행 매크로

        ```c
        #define DEBUG_PRINT(x) do { \
            if (debug_mode) { \
                printf("%s = %d\n", #x, x); \
            } \
        } while (0)
        ```

    4. 문자열화 연산자 (#)
        - 매크로 인자를 문자열로 변환합니다

        ```c
        #define STRINGIFY(x) #x
        ```

        - 사용 예:

        ```c
        printf("%s\n", STRINGIFY(Hello));  // 출력: "Hello"
        ```

    5. 토큰 병합 연산자(##)
        - 두 토큰을 하나로 결합합니다.

        ```c
        #define CONCAT(a, b) a ## b
        ```

        - 사용 예:

        ```c
        int xy = 10;
        printf("%d\n", CONCAT(x, y));  // 출력: 10
        ```

4. 조건부 컴파일
    1. #if, #elif, #else, #endif

        ```c
        #define DEBUG 1

        #if DEBUG
            printf("Debug mode is on\n");
        #elif defined(RELEASE)
            printf("Release mode\n");
        #else
            printf("Unknown mode\n");
        #endif
        ```

    2. #ifdef, #ifndef

        ```c
        #ifdef DEBUG
            printf("Debugging...\n");
        #endif

        #ifndef MAX_SIZE
            #define MAX_SIZE 100
        #endif
        ```

5. 기타 전처리기 지시문
    1. #undef
        - 매크로 정의를 제거합니다.

        ```c
        #define MAX 100
        // ... 코드 ...
        #undef MAX
        ```
    
    2. #pragma
        - 컴파일러 특정 기능을 제어합니다.

        ```c
        #pragma once // 헤더 파일이 한 번만 포함되도록 함.
        ```

    3. #error
        - 컴파일 에러를 발생시킵니다.

        ```c
        #if !defined(MIN_VERSION) || (MIN_VERSION < 5)
            #error "This program requires version 5 or higher"
        #endif
        ```

6. 미리 정의된 매크로
    - C 언어는 몇 가지 미리 정의된 매크로를 제공합니다:

        - `__FILE__`: 현재 소스 파일 이름
        - `__LINE__`: 현재 소스 코드 라인 번호
        - `__DATE__`: 컴파일 날짜
        - `__TIME__`: 컴파일 시간
        - `__STDC__`: 표준 C컴파일러면 1

    - 사용 예:

    ```c
    printf("This file: %s\n", __FILE__);
    printf("Line number: %d\n", __LINE__);
    printf("Compiled on: %s at %s\n", __DATE__, __TIME__);
    ```

7. 실제 사용 예제: 디버그 매크로

    ```c
    #define DEBUG 1

    #if DEBUG
        #define DEBUG_PRINT(x) printf("%s = %d\n", #x, x)
    #else
        #define DEBUG_PRINT(x)
    #endif

    int main() {
        int x = 5;
        DEBUG_PRINT(x);  // DEBUG가 1일 때만 출력됨
        return 0;
    }
    ```

8. 연습 문제
    1. 문제: 안전한 배열 접근을 위한 매크로를 작성하세요. 배열의 범위를 벗어나는 접근을 방지해야 합니다.

    ```c
    #include <stdio.h>

    #define ARRAY_SIZE 5
    #define SAFE_ACCESS(arr, index) ((index) >= 0 && (index) < ARRAY_SIZE ? arr[index] : 0)

    int main() {
        int arr[ARRAY_SIZE] = {1, 2, 3, 4, 5};

        printf("%d\n", SAFE_ACCESS(arr, 2));  // 출력: 3
        printf("%d\n", SAFE_ACCESS(arr, 10)); // 출력: 0 (안전한 접근)

        return 0;
    }
    ```

    2. 문제: 조건부 컴ㅁ파일을 사용하여 운영 체제에 따라 다른 코드를 컴파일하는 프로그램을 작성하세요.

    ```c
    #include <stdio.h>

    #if defined(_WIN32) || defined(_WIN64)
        #define OS "Windows"
    #elif defined(__APPLE__) || defined(__MACH__)
        #define OS "macOS"
    #elif defined(__linux__)
        #define OS "Linux"
    #else
        #define OS "Unknown"
    #endif

    int main() {
        printf("This program is running on %s\n", OS);
        return 0;
    }
    ```

### 메모리 관리 ###

1. C 프로그램의 메모리 구조
    - C 프로그램의 메모리는 일반적으로 다음과 같은 세그먼트로 나뉩니다:

        1. 텍스트 세그먼트(코드 세그먼트)
        2. 데이터 세그먼트(초기화된 데이터)
        3. BSS 세그먼트(초기화되지 않은 데이터)
        4. 힙 (동적 메모리 할당)
        5. 스택(함수 호출, 지역 변수)

    ```
    높은 주소
    +------------------+
    |      스택        |
    |        ↓         |
    |                  |
    |                  |
    |        ↑         |
    |       힙         |
    +------------------+
    |       BSS        |
    +------------------+
    |      데이터      |
    +------------------+
    |      텍스트      |
    +------------------+
    낮은 주소
    ```

2. 정적 메모리 할당
    - 정적 메모리 할당은 컴파일 시간에 이루어집니다.

    1. 전역 변수

        ```c
        int global_var = 10;  // 데이터 세그먼트
        int uninitialized_var;  // BSS 세그먼트
        ```

    2. 정적 지역 변수

        ```c
        void function() {
            static int count = 0;  // 데이터 세그먼트
            count++;
            printf("%d\n", count);
        }
        ```

3. 동적 메모리 할당
    - 동적 메모리 할당을 프로그램 실행 중에 힙에서 이루어집니다.

    1. malloc()

        ```c
        #include <stdlib.h>

        int *ptr = (int *)malloc(5 * sizeof(int));
        if (ptr == NULL) {
            // 메모리 할당 실패 처리
        }
        ```

    2. calloc()

        ```c
        int *ptr = (int *)calloc(5, sizeof(int));
        ```

    3. realloc()

        ```c
        ptr = (int *)realloc(ptr, 10 * sizeof(int));
        ```

    4. free()

        ```c
        free(ptr);
        ptr = NULL;  // 댕글링 포인터 방지
        ```
        
4. 메모리 누수 (Memory Leak)
    - 메모리 누수는 할당된 메모리를 해제하지 않을 때 발생합니다.

    ```c
    void memory_leak_example() {
        int *ptr = (int *)malloc(sizeof(int));
        *ptr = 10;
        // free(ptr); // 이 줄이 없으면 메모리 누수 발생
    }
    ```

5. 버퍼 오퍼블로우(Buffer Overflow)
    - 버퍼 오버플로우는 할당된 메모리 범위를 벗어나 데이터를 쓸 때 발생합니다.

    ```c
    void buffer_overflow_example() {
        char buffer[5];
        strcpy(buffer, "This is too long");  // 버퍼 오버플로우 발생
    }
    ```

6. 메모리 단편화 (Memory Fragmentation)
    1. 외부 단편화
        - 여러 번의 할당과 해제로 인해 사용 가능한 메모리가 작은 조각으로 나뉘는 현상

    2. 내부 단편화
        - 할당된 메모리 블록이 요청된 크기보다 약간 더 클 때 발생

7. 메모리 정렬 (Memory Alignment)
    - 데이터 타입의 크기에 따라 메모리 주소를 정렬하는 것

    ```c
    struct Aligned {
        char c;   // 1 byte
        int i;    // 4 bytes
        char d;   // 1 byte
    };  // 실제 크기: 12 bytes (패딩 때문)
    ```

8. 가비지 컬렉션 (Garbage Collection)
    - C언어는 자동 가비지 컬렉션을 제공하지 않습니다. 프로그래머가 직접 메모리를 관리해야 합니다.

9. 스마트 포인터 (C++의 개념)
    - C++에서는 스마트 포인터를 통해 자동 메모리 관리를 지원하지만, C에는 이 개념이 없습니다.

10. 메모리 관리 모범 사례:
    1. 항상 할당한 메모리를 해제하세요.
    2. NULL 포인터 체크를 하세요.
    3. 메모리 경계를 넘지 않도록 주의하세요.
    4. valgrind 같은 도구를 사용하여 메모리 오류를 검사하세요.

11. 실제 사용 예제: 동적 문자열 처리

    ```c
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    char* createDynamicString(const char* input) {
        char* str = (char*)malloc(strlen(input) + 1);
        if (str == NULL) {
            return NULL;
        }
        strcpy(str, input);
        return str;
    }

    int main() {
        const char* input = "Hello, World!";
        char* dynamicStr = createDynamicString(input);
        
        if (dynamicStr != NULL) {
            printf("%s\n", dynamicStr);
            free(dynamicStr);
        } else {
            printf("Memory allocation failed.\n");
        }

        return 0;
    }
    ```

12. 연습 문제

    1. 문제: 동적으로 정수 배열을 생성하고, 사용자로부터 입력받은 값으로 채운 후, 합계를 계산하는 프로그램을 작성하세요.

    ```c
    #include <stdio.h>
    #include <stdlib.h>

    int* createArray(int size) {
        return (int*)malloc(size * sizeof(int));
    }

    int calculateSum(int* arr, int size) {
        int sum = 0;
        for (int i = 0; i < size; i++) {
            sum += arr[i];
        }
        return sum;
    }

    int main() {
        int size;
        printf("배열의 크기를 입력하세요: ");
        scanf("%d", &size);

        int* arr = createArray(size);
        if (arr == NULL) {
            printf("메모리 할당 실패\n");
            return 1;
        }

        for (int i = 0; i < size; i++) {
            printf("정수를 입력하세요: ");
            scanf("%d", &arr[i]);
        }

        int sum = calculateSum(arr, size);
        printf("합계: %d\n", sum);

        free(arr);
        return 0;
    }
    ```

    2. 문제: 메모리 누수를 포함한 코드를 찾고 수정하세요.
    
    - 오류가 있는 코드
    ```c
    #include <stdlib.h>

    void leakyFunction() {
        int* ptr = (int*)malloc(sizeof(int));
        *ptr = 10;
        ptr = NULL;  // 메모리 누수 발생
    }

    int main() {
        for (int i = 0; i < 1000; i++) {
            leakyFunction();
        }
        return 0;
    }
    ```

    - 수정된 코드
    ```c
    #include <stdlib.h>

    void nonLeakyFunction() {
        int* ptr = (int*)malloc(sizeof(int));
        if (ptr != NULL) {
            *ptr = 10;
            free(ptr);  // 메모리 해제
        }
    }

    int main() {
        for (int i = 0; i < 1000; i++) {
            nonLeakyFunction();
        }
        return 0;
    }
    ```

### 추가적인 타입과 타입 수식어 ###

1. 부호 있는/없는 정수 타입 (Signed/Unsigned Integer Types)
    1. unsigned 키워드
        - `unsigned`키워드는 변수가 양수 값만 저장할 수 있음을 나타냅니다.

        ```c
        unsigned int positive_num = 42;
        unsigned char byte = 255;  // 0 to 255
        ```

        - 주의: unsigned 변수에 음수를 할당하면 오버플로우가 발생합니다.

    2. signed 키워드
        `signed`키워드는 변수가 양수와 음수 모두를 저장할 수 있음을 나타냅니다(기본값).


2. 크기 지정 정수 타입 (Size-specific Integer Types)
    - `<stdint.h>`헤더에 정의되어 있습니다.

    ```c
    #include <stdint.h>

    int8_t i8 = 127;
    uint8_t ui8 = 255;
    int16_t i16 = 32767;
    uint16_t ui16 = 65535;
    int32_t i32 = 2147483647;
    uint32_t ui32 = 4294967295;
    int64_t i64 = 9223372036854775807LL;
    uint64_t ui64 = 18446744073709551615ULL;
    ```

3. size_t 타입
    - `size_t`는 객체의 값의 크기를 나타내는 데 사용되는 unsigned 정수 타입입니다.

    ```c
    #include <stddef.h>

    size_t size = sizeof(int);
    size_t length = strlen("Hello");
    ```

4. ssize_t 타입
    - `ssize_t`는 `size_t`의 signed 버전으로, POSIX 시스템에서 사용됩니다.

    ```c
    #include <sys/types.h>

    ssize_t result = read(fd, buffer, count);
    ```

5. 타입 수식어 (Type Modifiers)
    1. static 키워드: 참조 범위를 수정하지 않으면서 수명을 프로그램의 수명과 동일하게 맞춘다.
        1. 지역 변수에 사용:
            - 변수의 수명을 프로그램 전체로 확장
            - 초기화는 한 번만 수행

        ```c
        void count_calls() {
            static int count = 0;
            count++;
            printf("This function has been called %d times\n", count);
        }
        ```

        2. 전역 변수나 함수에 사용:
            - 해당 변수나 함수의 범위를 현재 파일로 제한

        ```c
        static int file_scope_var = 10;
        static void file_scope_function() { /* ... */ }
        ```

    2. const 키워드
        - 값이 변경되지 않음을 나타냅니다.

        ```c
        const int MAX_SIZE = 100;
        const char* str = "Hello";  // str이 가리키는 문자열은 변경 불가
        char* const ptr = buffer;   // ptr 자체는 변경 불가
        ```

    3. volatile 키워드
        - 컴파일러 최적화를 방지하고, 항상 메모리에서 값을 읽도록 합니다.

        ```c
        volatile int sensor_value;  // 하드웨어에 의해 변경될 수 있는 값
        ```

6. 실제 사용 예제: 바이트 조작

    ```c
    #include <stdio.h>
    #include <stdint.h>

    void print_bits(uint8_t byte) {
        for (int i = 7; i >= 0; i--) {
            printf("%d", (byte >> i) & 1);
        }
        printf("\n");
    }

    int main() {
        uint8_t flags = 0;
        
        // 비트 설정
        flags |= (1 << 2);  // 3번째 비트 설정
        flags |= (1 << 5);  // 6번째 비트 설정
        
        printf("Flags: ");
        print_bits(flags);
        
        // 비트 확인
        if (flags & (1 << 2)) {
            printf("3번째 비트가 설정되어 있습니다.\n");
        }
        
        // 비트 클리어
        flags &= ~(1 << 5);  // 6번째 비트 클리어
        
        printf("Updated flags: ");
        print_bits(flags);
        
        return 0;
    }
    ```

7. 주의사항
    1. 부호 없는 정수 타입을 사용할 때는 오버플로우와 언더플로우에 주의해야 합니다.
    2. `size_t`를 사용할 때는 printf에서 `%zu`포맷 지정자를 사용해야 합니다.
    3. `static` 지역 변수는 스레드 안정성 문제를 일으킬 수 있으므로 멀티스레드 환경에서 주의해야 합니다.
    4. `const`와 포인터를 함께 사용할 때는 의미를 정확히 이해해야 합니다(`const int*` vs `int* const`).
        - `const int*`는 메모리 주소 변경하지 말라의 의미.
        - `int* const`는 포인터 주소는 변경하지 못하지만 데이터의 값은 변경 가능.'

    5. `volatile`은 필요한 경우에만 사용해야 합니다. 과도한 사용은 성능 저하를 일으킬 수 있습니다.


### 고급 포인터 개념 ###

1. 다중 포인터 (Multiple Indirection)
    - 다중 포인터는 포인터의 포인터를 의미합니다. 이는 포인터 변수의 주소를 저장하는 포인터입니다.

    1. 이중 포인터 (Double Pointer)

        ```c
        int value = 5;
        int *ptr = &value;
        int **pptr = &ptr;

        printf("Value: %d\n", **pptr);  // 출력: 5
        ```

    2. 다중 포인터의 사용 예
        1. 2D 배열 동적 할당:

        ```c
        int rows = 3, cols = 4;
        int **matrix = (int **)malloc(rows * sizeof(int *));
        for (int i = 0; i < rows; i++) {
            matrix[i] = (int *)malloc(cols * sizeof(int));
        }

        // 사용 후 메모리 해제
        for (int i = 0; i < rows; i++) {
            free(matrix[i]);
        }
        free(matrix);
        ```

        2. 함수에서 포인터 수정:

        ```c
        void allocateMemory(int **ptr, int size) {
            *ptr = (int *)malloc(size * sizeof(int));
        }

        int main() {
            int *dynamicArray = NULL;
            allocateMemory(&dynamicArray, 10);
            // dynamicArray 사용
            free(dynamicArray);
            return 0;
        }
        ```

2. void 포인터 (Void Pointer)
    - void 포인터는 모든 데이터 타입의 주소를 저장할 수 있는 일반적인 포인터 타입입니다.

    1. void 포인터 선언 및 사용

    ```c
    void *vptr;
    int num = 10;
    float f = 3.14;

    vptr = &num;
    printf("Integer value: %d\n", *(int *)vptr);

    vptr = &f;
    printf("Float value: %f\n", *(float *)vptr);
    ```

    2. void 포인터의 활용

        1. 일반화된 함수 작성:

        ```c
        void printArray(void *arr, size_t size, size_t elem_size, void (*print_func)(void *)) {
            char *ptr = (char *)arr;
            for (size_t i = 0; i < size; i++) {
                print_func(ptr + i * elem_size);
            }
        }

        void printInt(void *elem) {
            printf("%d ", *(int *)elem);
        }

        void printFloat(void *elem) {
            printf("%.2f ", *(float *)elem);
        }

        int main() {
            int intArr[] = {1, 2, 3, 4, 5};
            float floatArr[] = {1.1, 2.2, 3.3, 4.4, 5.5};

            printArray(intArr, 5, sizeof(int), printInt);
            printf("\n");
            printArray(floatArr, 5, sizeof(float), printFloat);
            printf("\n");

            return 0;
        }
        ```

3. const 포인터 (Constant Pointer)
    - const 키워드는 포인터와 함께 사용되어 다양한 의미를 가질 수 있습니다.

    1. 포인터가 가리키는 값이 상수 (Pointer to constant)

    ```c
    const int *ptr;
    // or
    int const *ptr;
    ```
    - 이 경우, ptr을 통해 가리키는 값을 변경할 수 있습니다.

    2. 상수 포인터 (Constant pointer)

    ```c
    int * const ptr;
    ```
    - 이 경우, ptr이 가리키는 주소를 변경할 수 없습니다.

    3. 상수를 가리키는 상수 포인터 (Constant pointer to constant)

    ```c
    const int * const ptr;
    ```
    - 이 경우, ptr이 가리키는 주소와 값 모두 변경할 수 없습니다.

    ```c
    int value = 10;
    const int * const ptr = &value;
    // *ptr = 20;      // 컴파일 에러
    // ptr = &value;   // 컴파일 에러
    ```

4. 함수 포인터 (Function Pointer)
    - 함수 포인터는 함수의 주소를 저장하는 포인터입니다.

    1. 함수 포인터 선언 및 사용

    ```c
    int add(int a, int b) { return a + b; }
    int subtract(int a, int b) { return a - b; }

    int (*operation)(int, int);

    operation = add;
    printf("Result: %d\n", operation(5, 3));  // 출력: 8

    operation = subtract;
    printf("Result: %d\n", operation(5, 3));  // 출력: 2
    ```

    2. 함수 포인터 배열

    ```c
    int (*operations[])(int, int) = {add, subtract};
    printf("Result: %d\n", operations[0](5, 3));  // 출력: 8
    printf("Result: %d\n", operations[1](5, 3));  // 출력: 2
    ```

5. 주의사항 및 모범 사례
    1. 다중 포인터 사용 시 가독성에 주의하세요. 필요 이상으로 복잡하게 만들지 마세요.
    2. void 포인터 사용 시 항상 적절한 타입으로 캐스팅하세요.
    3. const 포인터를 사용하여 의도치 않은 수정을 방지하세요.
    4. 함수 포인터를 사용할 때는 함수 시그니처가 정확히 일치하는지 확인하세요.
    5. 포인터 연산 시 항상 경계 검사를 수행하여 버퍼 오퍼플로우를 방지하세요.

6. 실제 사용 예제: 플러그인 시스템
    - 다음은 함수 포인터를 사용한 간단한 플러그인 시스템의 예입니다:

    ```c
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    typedef struct {
        char name[50];
        void (*execute)(void);
    } Plugin;

    void hello_plugin() {
        printf("Hello from plugin!\n");
    }

    void bye_plugin() {
        printf("Goodbye from plugin!\n");
    }

    int main() {
        Plugin plugins[] = {
            {"Hello", hello_plugin},
            {"Bye", bye_plugin}
        };
        int num_plugins = sizeof(plugins) / sizeof(Plugin);

        char command[50];
        while (1) {
            printf("Enter plugin name (or 'quit' to exit): ");
            scanf("%s", command);

            if (strcmp(command, "quit") == 0) break;

            int found = 0;
            for (int i = 0; i < num_plugins; i++) {
                if (strcmp(command, plugins[i].name) == 0) {
                    plugins[i].execute();
                    found = 1;
                    break;
                }
            }

            if (!found) {
                printf("Plugin not found.\n");
            }
        }

        return 0;
    }
    ```

### 비트 조작 ###

1. 비트 연산자
    - C언어는 비트 단위의 연산을 위한 여러 연산자를 제공합니다.

    1. 비트 AND(&)
        - 두 비트가 모두 1일 때 1을 반환합니다.

        ```c
        int a = 12;  // 1100 in binary
        int b = 10;  // 1010 in binary
        int result = a & b;  // 1000 in binary (8 in decimal)
        ```

    2. 비트 OR(|)
        - 두 비트 중 하나라도 1이면 1을 반환합니다.

        ```c
        int a = 12;  // 1100 in binary
        int b = 10;  // 1010 in binary
        int result = a | b;  // 1110 in binary (14 in decimal)
        ```

    3. 비트 XOR(^)
        - 두 비트가 다를 때 1을 반환합니다.

        ```c
        int a = 12;  // 1100 in binary
        int b = 10;  // 1010 in binary
        int result = a ^ b;  // 0110 in binary (6 in decimal)
        ```

    4. 비트 NOT(~)
        - 비트를 반전시킵니다.

        ```c
        unsigned int a = 12;  // 00001100 in binary
        unsigned int result = ~a;  // 11110011 in binary
        ```

    5. 왼쪽 시프트 (<<)
        - 비트를 왼쪽으로 이동시킵니다.

        ```c
        int a = 1;  // 0001 in binary
        int result = a << 2;  // 0100 in binary (4 in decimal)
        ```

    6. 오른쪽 시프트 (>>)
        - 비트를 오른쪽으로 이동시킵니다.

        ```c
        int a = 8;  // 1000 in binary
        int result = a >> 2;  // 0010 in binary (2 in decimal)
        ```

2. 비트 필드
    - 구조체 내에서 비트 단위로 메모리를 할당할 수 있습니다.

    ```c
    struct PackedStruct {
        unsigned int f1 : 1;
        unsigned int f2 : 4;
        unsigned int f3 : 4;
    } pack;

    pack.f1 = 1;
    pack.f2 = 12;
    pack.f3 = 8;
    ```

3. 비트 마스킹 기법
    1. 특정 비트 설정

        ```c
        unsigned int flag = 0;
        flag |= (1 << 3);  // 3번째 비트를 1로 설정
        ```

    2. 특정 비트 클리어
        
        ```c
        unsigned int flag = 15;  // 1111 in binary
        flag &= ~(1 << 2);  // 2번째 비트를 0으로 설정, 결과는 1011
        ```

    3. 특정 비트 토글

        ```c
        unsigned int flag = 10;  // 1010 in binary
        flag ^= (1 << 1);  // 1번째 비트를 토글, 결과는 1000
        ```

    4. 특정 비트 확인

        ```c
        unsigned int flag = 10;  // 1010 in binary
        if (flag & (1 << 1)) {
            printf("1번째 비트가 설정되어 있습니다.\n");
        }
        ```

4. 실제 사용 예제
    1. 플래그 관리 시스템

        ```c
        #define FLAG_READY    (1 << 0)
        #define FLAG_ACTIVE   (1 << 1)
        #define FLAG_PAUSED   (1 << 2)
        #define FLAG_FINISHED (1 << 3)

        unsigned int status = 0;

        // 플래그 설정
        status |= FLAG_READY;
        status |= FLAG_ACTIVE;

        // 플래그 확인
        if (status & FLAG_READY) {
            printf("시스템이 준비되었습니다.\n");
        }

        // 플래그 해제
        status &= ~FLAG_ACTIVE;

        // 플래그 토글
        status ^= FLAG_PAUSED;
        ```

    2. 색상 처리 (RGBA)

        ```c
        typedef unsigned int Color;

        Color createColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
            return (r << 24) | (g << 16) | (b << 8) | a;
        }

        unsigned char getRed(Color color) {
            return (color >> 24) & 0xFF;
        }

        unsigned char getGreen(Color color) {
            return (color >> 16) & 0xFF;
        }

        unsigned char getBlue(Color color) {
            return (color >> 8) & 0xFF;
        }

        unsigned char getAlpha(Color color) {
            return color & 0xFF;
        }

        int main() {
            Color myColor = createColor(255, 128, 64, 255);
            printf("Red: %d\n", getRed(myColor));
            printf("Green: %d\n", getGreen(myColor));
            printf("Blue: %d\n", getBlue(myColor));
            printf("Alpha: %d\n", getAlpha(myColor));
            return 0;
        }
        ```

5. 주의사항 및 최적화 팁
    1. 부호 있는 정수형의 시프트 연산은 구현에 따라 다를 수 있으므로 주의해야 합니다.
    2. 비트 필드를 사용할 때는 이식성에 주의해야 합니다. 컴파일러마다 구현이 다를 수 있습니다.
    3. 비트 연산은 일반적으로 산술 연산보다 빠르므로, 성능이 중요한 경우 활용할 수 있습니다.
    4. 2의 거듭제곱 연산은 시프트 연산으로 최적화할 수 있습니다. (예: `1 << n`은 2^n과 같습니다).
    5. 비트 마스킹을 사용하면 메모리 사용을 줄일 수 있지만, 코드의 가독성이 떨어질 수 있으므로 적절한 주석이 필요합니다.

6. 게임 서버 개발에서의 응용
    1. 네트워크 프로토콜: 패킷 헤더의 효율적인 인코딩과 디코딩
    2. 권한 관리: 사용자 권한을 비트 플래그로 관리
    3. 게임 상태 관리: 각종 상태 플래그를 비트로 표현
    4. 메모리 최적화: 작은 정보를 비트 단위로 저장하여 메모리 사용 최소화
    5. 해시 함수: 비트 연산을 활용한 빠른 해시 함수 구현

### 함수 고급 주제 ###

1. 재귀 함수 (Recursive Functions)
    - 재귀 함수는 자기 자신을 호출하는 함수입니다. 복잡한 문제를 더 작은 문제로 나누어 해결할 때 유용합니다.

    1. 재귀 함수의 구조

        ```c
        return_type recursive_function(parameters) {
            // 기저 조건 (Base case)
            if (종료 조건) {
                return 결과;
            }
            // 재귀 단계 (Recursive step)
            return recursive_function(수정된 매개변수);
        }
        ```

    2. 예제: 팩토리얼 계산

        ```c
        unsigned long long factorial(unsigned int n) {
            if (n == 0 || n == 1) {
                return 1;  // 기저 조건
            }
            return n * factorial(n - 1);  // 재귀 단계
        }
        ```

    3. 주의사항
        1. 항상 종료 조건(기저 조건)을 명확히 설정해야 합니다.
        2. 스택 오버플로우에 주의해야 합니다. 재귀 깊이가 너무 깊어지면 스택 메모리가 고갈될 수 있습니다.
        3. 때로는 반복문이 재귀보다 효율적일 수 있습니다. 상황에 따라 적절히 선택해야 합니다.

    4. 꼬리 재귀 최적회 (Tail Recursive Optimization)
        - 일부 컴파일러는 꼬리 재귀를 최적화하여 반복문처럼 효율적으로 만들 수 있습니다.

        ```c
        unsigned long long factorial_tail(unsigned int n, unsigned long long acc) {
            if (n == 0 || n == 1) {
                return acc;
            }
            return factorial_tail(n - 1, n * acc);
        }

        unsigned long long factorial(unsigned int n) {
            return factorial_tail(n, 1);
        }
        ```

2. 인라인 함수 (Inline Functions)
    - 인라인 함수는 컴파일러에게 함수 호출 대신 함수 본문을 직접 삽입하도록 요청하는 방식입니다.
    작은 함수의 성능을 향상시키는 데 사용됩니다.

    1. 인라인 함수 선언

        ```c
        inline int max(int a, int b) {
            return (a > b) ? a : b;
        }
        ```

    2. 주의사항
        1. `inline`키워드는 컴파일러에 대한 힌트일 뿐, 반드시 인라인화되는 것은 아닙니다.
        2. 큰 함수를 인라인화하면 코드 크기가 증가할 수 있습니다.
        3. 재귀 함수나 복잡한 함수는 인라인화하기 어렵습니다.

    3. 사용 예

        ```c
        #include <stdio.h>

        inline int square(int x) {
            return x * x;
        }

        int main() {
            for (int i = 0; i < 5; i++) {
                printf("%d의 제곱: %d\n", i, square(i));
            }
            return 0;
        }
        ```

3. 가변 인자 함수 (Variadic Functions)
    - 가변 인자 함수는 인자의 개수가 가변적인 함수입니다. `printf` 함수가 대표적인 예입니다.

    1. 가변 인자 함수 선언 및 사용

        ```c
        #include <stdarg.h>

        int sum(int count, ...) {
            va_list args;
            va_start(args, count);

            int total = 0;
            for (int i = 0; i < count; i++) {
                total += va_arg(args, int);
            }

            va_end(args);
            return total;
        }

        int main() {
            printf("Sum: %d\n", sum(4, 10, 20, 30, 40));
            return 0;
        }
        ```

    2. 주요 매크로
        - `va_list`: 가변 인자 목록을 저장하는 타입
        - `va_start`: 가변 인자 목록 처리 시작
        - `va_arg`: 다음 가변 인자 가져오기
        - `va_end`: 가변 인자 목록 처리 종료

    3. 주의사항
        1. 가변 인자의 타입과 개수를 추적하는 것은 프로그래머의 책임입니다.
        2. 타입 안정성이 떨어질 수 있으므로 주의해서 사용해야 합니다.

4. 함수 포인터 (Function Pointers)
    - 함수 포인터는 함수의 주소를 저장하는 포인터입니다. 런타임에 동적으로 함수를 선택하고 호출할 수 있게 해줍니다.

    1. 함수 포인터 선인 및 사용

        ```c
        int add(int a, int b) { return a + b; }
        int subtract(int a, int b) { return a - b; }

        int (*operation)(int, int);

        int main() {
            operation = add;
            printf("10 + 5 = %d\n", operation(10, 5));

            operation = subtract;
            printf("10 - 5 = %d\n", operation(10, 5));

            return 0;
        }
        ```

    2. 함수 포인터 배열

        ```c
        int (*operations[])(int, int) = {add, subtract};
        printf("10 + 5 = %d\n", operations[0](10, 5));
        printf("10 - 5 = %d\n", operations[1](10, 5));
        ```

5. 응용 예제: 간단한 명령 처리기
    - 다음은 함수 포인터를 사용한 간단한 명령 처리기 예제입니다.

    ```c
    #include <stdio.h>
    #include <string.h>

    void hello() { printf("Hello, World!\n"); }
    void quit() { printf("Goodbye!\n"); }

    typedef void (*command_function)();

    typedef struct {
        const char* name;
        command_function function;
    } Command;

    Command commands[] = {
        {"hello", hello},
        {"quit", quit}
    };

    int num_commands = sizeof(commands) / sizeof(Command);

    int main() {
        char input[20];
        while (1) {
            printf("Enter a command: ");
            scanf("%s", input);

            int i;
            for (i = 0; i < num_commands; i++) {
                if (strcmp(input, commands[i].name) == 0) {
                    commands[i].function();
                    break;
                }
            }

            if (i == num_commands) {
                printf("Unknown command\n");
            }

            if (strcmp(input, "quit") == 0) {
                break;
            }
        }

        return 0;
    }
    ```

6. 게임 서버 개발에서의 응용
    1. 재귀 함수: 트리 구조의 데이터 처리 (예: 게임 월드의 계층 구조)
    2. 인라인 함수: 자주 호출되는 작은 함수의 최적화(예: 벡터 연산)
    3. 가변 인자 함수: 유연한 로깅 시스템 구현
    4. 함수 포인터: 이벤트 핸들러 시스템, 플러그인 아키텍처 구현


### 메모리 최적화 ###

1. 메모리 정렬 (Memory Alignment)
    - 메모리 정렬은 데이터가 메모리 상에서 특정 주소 경계에 맞춰 저장되도록 하는 것입니다.

    1. 정렬의 중요성
        - 정렬된 메모리 접근은 더 빠릅니다.
        - 일부 아키텍처에서는 정렬되지 않은 메모리 접근 시 오류가 발생할 수 있습니다.

    2. 구조체 패딩

        ```c
        struct Aligned {
            char c;    // 1 byte
            int i;     // 4 bytes
            short s;   // 2 bytes
        };

        printf("Size of Aligned: %zu\n", sizeof(struct Aligned));  // 출력: 12 (패딩 때문)
        ```

    3. 패딩 최소화

        ```c
        struct Optimized {
            int i;     // 4 bytes
            short s;   // 2 bytes
            char c;    // 1 byte
            char pad;  // 1 byte (명시적 패딩)
        };

        printf("Size of Optimized: %zu\n", sizeof(struct Optimized));  // 출력: 8
        ```

    4. 정렬 지정자

        ```c
        struct alignas(8) AlignedStruct {
            int i;
            char c;
        };
        ```

2. 캐시 친화적 프로그래밍
    - 캐시 친화적 프로그래밍은 CPU 캐시를 효율적으로 활용하여 성능을 향상시키는 기법입니다.

    1. 데이터 지역성
        - 시간적 지역성: 최근 사용된 데이터는 곧 다시 사용될 가능성이 높습니다.
        - 공간적 지역성: 메모리 상에서 가까운 데이터는 함께 사용될 가능성이 높습니다.

    2. 배열 순회 최적화

        ```c
        // 캐시 친화적인 방식
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                process(matrix[i][j]);
            }
        }

        // 캐시 비효율적인 방식
        for (int j = 0; j < cols; j++) {
            for (int i = 0; i < rows; i++) {
                process(matrix[i][j]);
            }
        }
        ```

    2. False Sharing 방지
        - 멀티스레드 환경에서 서로 다른 변수가 같은 캐시 라인에 있을 때 발생하는 성능 저하를 방지합니다.

        ```c
        struct ThreadData {
            int data;
            char padding[60];  // 캐시 라인 크기를 고려한 패딩
        };
        ```

3. 메모리 풀 (Memory Pool)
    - 메모리 풀은 동적 메모리 할당의 오버헤드를 줄이기 위해 사용되는 기법입니다.

    1. 간단한 메모리 풀 구현

        ```c
        #define POOL_SIZE 1000
        #define CHUNK_SIZE 32

        static char pool[POOL_SIZE];
        static int next_free = 0;

        void* allocate() {
            if (next_free + CHUNK_SIZE > POOL_SIZE) {
                return NULL;  // 메모리 풀이 가득 참
            }
            void* result = &pool[next_free];
            next_free += CHUNK_SIZE;
            return result;
        }

        void deallocate(void* ptr) {
            // 이 간단한 예제에서는 실제로 메모리를 해제하지 않습니다.
        }
        ```

    2. 메모리 풀의 장점
        - 할당 및 해제 속도가 빠릅니다.
        - 메모리 단편화를 줄일 수 있습니다.
        - 메모리 누수를 방지하기 쉽습니다.

4. 메모리 매핑 (Memory Mapping)
    - 메모리 매핑은 파일이나 디바이스를 메모리에 직접 매핑하는 기법입니다.

    ```c
    #include <sys/mman.h>
    #include <fcntl.h>
    #include <unistd.h>

    int fd = open("data.bin", O_RDONLY);
    off_t size = lseek(fd, 0, SEEK_END);
    void* mapped = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);

    // mapped를 통해 파일 내용에 직접 접근
    // ...

    munmap(mapped, size);
    close(fd);
    ```

5. 메모리 압축 (Memory Compression)
    - 데이터를 압축하여 메모리 사용량을 줄이는 기법입니다.

    1. 비트 필드 사용

        ```c
        struct CompressedData {
            unsigned int flag1 : 1;
            unsigned int flag2 : 1;
            unsigned int value : 6;
        };
        ```

    2. Run-Length Encoding

        ```c
        char* compress_rle(const char* input) {
            // RLE 압축 구현
        }

        char* decompress_rle(const char* compressed) {
            // RLE 압축 해제 구현
        }
        ```

6. 게임 서버 개발에서의 응용

    1. 오브젝트 풀링
        - 자주 생성되고 파괴되는 게임 오브젝트(예: 총알, 파티클)를 위한 메모리 풀 구현

        ```c
        #define MAX_BULLETS 1000

        struct Bullet {
            float x, y;
            float velocity;
            bool active;
        };

        struct Bullet bullet_pool[MAX_BULLETS];

        struct Bullet* get_bullet() {
            for (int i = 0; i < MAX_BULLETS; i++) {
                if (!bullet_pool[i].active) {
                    bullet_pool[i].active = true;
                    return &bullet_pool[i];
                }
            }
            return NULL;  // 사용 가능한 총알 없음
        }

        void return_bullet(struct Bullet* bullet) {
            bullet->active = false;
        }
        ```
        

### 표준 라이브러리 ###

C 표준 라이브러리는 C 프로그래밍 언어의 핵심 부분으로, 다양한 유용한 함수와 매크로를 제공합니다.
이 라이브러리는 C언어의 표준 사양의 일부로, 모든 표준 준수 C 구현에서 사용할 수 있습니다.

1. `<stdio.h>`
    - 이 헤더는 표준 입출력 함수를 포함합니다.

    - 주요 함수:

        1. `printf()`: 포맷된 출력을 화면에 표시
            ```c
            printf("Hello, %s! You are %d years old. \n", name, age);
            ```

        2. `scanf()`: 포맷된 입력을 받음
            ```c
            scanf("%d", &number);
            ```

        3. `fopen()`, `fclose()`: 파일 열기와 닫기
            ```c
            FILE *file = fopen("example.txt", "r");
            if (file == NULL) {
                printf("파일을 열 수 없습니다.\n");
                return 1;
            }
            // 파일 작업 수행
            fclose(file);
            ```

        4. `fread()`, `fwrite()`: 파일에서 읽기와 쓰기
            ```c
            char buffer[100];
            size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);
            size_t bytesWritten = fwrite(buffer, 1, bytesRead, outputFile);
            ```

        5. `fprintf()`, `fscanf()`: 파일에서 포맷된 출려과 파일에서 포맷된 입력
            ```c
            fprintf(file, "Name: %s, Age: %d\n", name, age);
            fscanf(file, "%s %d", name, &age);
            ```

    2. `<string.h>`
        - 문자열 처리 함수들을 포함합니다.

        - 주요 함수:

            1. `strlen()`: 문자열 길이 계산
                ```c
                size_t length = strlen("Hello"); // 결과: 5
                ```

            2. `strcpy()`, `strncpy()`: 문자열 복사
                ```c
                char dest[20];
                strcpy(dest, "Hello"); // dest에 "Hello" 복사
                strncpy(dest, "Hello, World!", 5); // dest에 "Hello" 복사 (최대 5글자) 
                ```

            3. `strcat()`, `strncat()`: 문자열 연결
                ```c
                char str[20] = "Hello";
                strcat(str, " World");  // str은 이제 "Hello World"
                strncat(str, "!!!", 2);  // str은 이제 "Hello World!!"
                ```

            4. `strcmp()`, `strncmp()`: 문자열 비교
                ```c
                int result = strcmp("hello", "hello");  // 결과: 0 (같음)
                result = strncmp("hello", "help", 3);  // 결과: 0 (첫 3글자 같음)
                ```

            5. `strchr()`, `strstr()`: 문자열에서 문자 또는 부분 문자열 찾기
                ```c
                char *pos = strchr("Hello", 'e');  // 'e'의 위치를 반환
                pos = strstr("Hello World", "World");  // "World"의 시작 위치를 반환
                ```

    3. `<math.h>`
        - 수학 함수들을 포함합니다.

        - 주요 함수:

            1. `sqrt()`: 제곱근
                ```c
                double result = sqrt(16.0);  // 결과: 4.0
                ```

            2. `pow()`: 거듭제곱
                ```c
                double result = pow(2.0, 3.0);  // 결과: 8.0
                ```

            3. `sin()`, `cos()`, `tan()`: 삼각함수
                ```c
                double sine = sin(3.14159 / 2);  // 약 1.0
                ```

            4. `log()`, `log10()`: 자연로그, 상용로그
                ```c
                double natural_log = log(2.71828);  // 약 1.0
                double common_log = log10(100.0);   // 2.0
                ```

            5. `ceil`, `floor()`: 올림, 내림
                ```c
                double ceiled = ceil(3.7);   // 결과: 4.0
                double floored = floor(3.7); // 결과: 3.0
                ```

    4. `<stdlib.h>`
        - 일반적인 유틸리티 함수들을 포함합니다.

        - 주요 함수:

            1. `malloc()`, `calloc()`, `realloc()`, `free()`: 동적 메모리 관리
                ```c
                int *arr = (int *)malloc(5 * sizeof(int));
                // 사용 후
                free(arr);
                ```

            2. `atoi()`, `atof()`: 문자열을 정수 또는 부동소수점으로 변환
                ```c
                int num = atoi("123");    // 결과: 123
                double fnum = atof("3.14"); // 결과: 3.14
                ```

            3. `rand()`, `srand()`: 난수 생성
                ```c
                srand(time(NULL));  // 시드 설정
                int random_num = rand() % 100;  // 0-99 사이의 난수
                ```

            4. `qsort()`: 빠른 정렬 알고리즘
                ```c
                int compare(const void *a, const void *b) {
                    return (*(int*)a - *(int*)b);
                }
                int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
                qsort(arr, 10, sizeof(int), compare);
                ```

            5. `exit()`: 프로그램 종료
                ```c
                exit(EXIT_SUCCESS); // 또는 exit(0);
                ```

    5. `<time.h>`
        - 시간 관련 함수들을 포함합니다.

        - 주요 함수:

            1. `time()`: 현재 시간을 얻음
                ```c
                time_t now = time(NULL);
                ```

            2. `localtime()`: time_t를 struct tm으로 변환
                ```c
                struct tm *local_time = localtime(&now);
                ```

            3. `strftime()`: 시간을 포맷된 문자열로 변환
                ```c
                char time_str[50];
                strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", local_time);
                ```

    6. `<ctype.h>`
        - 문자 처리 함수들을 포함합니다.

            - `isalpha()`: 알파벳인지 확인
            - `isdigit()`: 숫자인지 확인
            - `isalnum()`: 알파벳 또는 숫자인지 확인
            - `tolower()`: 소문자로 변환
            - `toupper()`: 대문자로 변환

        - 예제:

            ```c
            #include <ctype.h>
            #include <stdio.h>

            int main() {
                char c = 'A';
                printf("Is alpha: %d\n", isalpha(c));  // 1
                printf("To lower: %c\n", tolower(c));  // 'a'
                return 0;
            }
            ```

    7. `<limits.h>`
        - 정수 타입의 최소값과 최대값을 정의합니다.

            - `INT_MAX`: int의 최대값
            - `INT_MIN`: int의 최소값
            - `CHAR_MAX`: char의 최대값
            - `LONG_MAX`: long의 최대값

        - 예제:

            ```c
            #include <limits.h>
            #include <stdio.h>

            int main() {
                printf("Max int: %d\n", INT_MAX);
                printf("Min int: %d\n", INT_MIN);
                return 0;
            }
            ```

    8. `<float.h>`
        - 부동소수점 타입의 특성을 정의합니다.

            - `FLT_MAX`: float의 최대값
            - `DBL_MAX`: double의 최대값
            - `FLT_EXSILON`: 1.0과 구분 가능한 가장 작은 float 값

        - 예제:

            ```c
            #include <float.h>
            #include <stdio.h>

            int main() {
                printf("Max float: %e\n", FLT_MAX);
                printf("Float epsilon: %e\n", FLT_EPSILON);
                return 0;
            }
            ```

    9. `<assert.h>`
        - 런타임 오류 검사를 위한 매크로를 제공합니다.

            - `assert()`: 조건이 거짓이면 프로그램을 중단

        - 예제:

            ```c
            #include <assert.h>

            int main() {
                int x = 5;
                assert(x == 5);  // 통과
                assert(x == 10); // 프로그램 중단
                return 0;
            }
            ```

    10. `<signal.h>`
        - 시그널 처리 함수를 제공합니다.

            - `signal()`: 시그널 핸들러 설정
            - `raise()`: 시그널 발생

        - 예제:

            ```c
            #include <signal.h>
            #include <stdio.h>

            void signal_handler(int signum) {
                printf("Received signal %d\n", signum);
            }

            int main() {
                signal(SIGINT, signal_handler);
                raise(SIGINT);
                return 0;
            }
            ```


### 오류 처리 ###

- C언어에서 오류 처리는 프로그램의 안정성과 신뢰성을 높이는 데 매우 중요합니다. 주요 오류 처리 메커니즘에는 반환 값 확인,
errno 변수 사용, 그리고 perror()와 strerror() 함수 사용 등이 있습니다.

1. 반환 값 확인
    - 많은 C 함수들은 오류 발생 시 특정 값(보통 -1이나 NULL)을 반환합니다. 이를 확인하는 것이 가장 기본적인 오류 처리 방법입니다.

    - 예제:

        ```c
        #include <stdio.h>

        int main() {
            FILE *file = fopen("non_existent_file.txt", "r");
            if (file == NULL) {
                printf("파일을 열 수 없습니다.\n");
                return 1;
            }
            // 파일 처리 코드...
            fclose(file);
            return 0;
        }
        ```

2. errno 변수
    - `errno`는 `<errno.h>`헤더에 정의되어 있는 전역 변수로, 최근 발생한 오류의 번호를 저장합니다.

    - 주요 특징:
        - 오류가 발생하면 시스템 함수가 errno를 설정합니다.
        - errno 값은 각각 특정 오류 상황을 나타냅니다. (예: ENOENT는 "No such file or directory").
        - errno를 직접 0으로 설정하는 것은 좋은 관행입니다. 함수들은 성공 시 errno를 0으로 재설정하지 않기 때문입니다.

    - 예제:

        ```c
        #include <stdio.h>
        #include <errno.h>
        #include <string.h>

        int main() {
            FILE *file = fopen("non_existent_file.txt", "r");
            if (file == NULL) {
                printf("오류 번호: %d\n", errno);
                printf("오류 메시지: %s\n", strerror(errno));
                return 1;
            }
            // 파일 처리 코드...
            fclose(file);
            return 0;
        }
        ```

3. perror() 함수
    - `perror()`함수는 현재의 errno 값에 해당하는 오류 메시지를 표준 오류 스트림(stderr)에 출력합니다.

    - 예제:

        ```c
        #include <stdio.h>
        #include <errno.h>

        int main() {
            FILE *file = fopen("non_existent_file.txt", "r");
            if (file == NULL) {
                perror("파일 열기 오류");
                return 1;
            }
            // 파일 처리 코드...
            fclose(file);
            return 0;
        }
        ```

4. strerror() 함수
    - `strerror()` 함수는 errno 값에 해당하는 오류 메시지 문자열을 반환합니다.

    - 예제:

        ```c
        #include <stdio.h>
        #include <string.h>
        #include <errno.h>

        int main() {
            FILE *file = fopen("non_existent_file.txt", "r");
            if (file == NULL) {
                printf("오류: %s\n", strerror(errno));
                return 1;
            }
            // 파일 처리 코드...
            fclose(file);
            return 0;
        }
        ```

5. 사용자 정의 오류 처리
    - 복잡한 프로그램에서는 사용자 정의 오류 처리 시스템을 구현하는 것이 유용할 수 있습니다.

    - 예제:

        ```c
        #include <stdio.h>
        #include <stdlib.h>
        #include <string.h>

        #define MAX_ERROR_MSG 100

        void error(const char *msg) {
            char error_msg[MAX_ERROR_MSG];
            snprintf(error_msg, sizeof(error_msg), "오류: %s\n", msg);
            fprintf(stderr, "%s", error_msg);
            exit(1);
        }

        int main() {
            FILE *file = fopen("non_existent_file.txt", "r");
            if (file == NULL) {
                error("파일을 열 수 없습니다");
            }
            // 파일 처리 코드...
            fclose(file);
            return 0;
        }
        ```

- 주의사항
    - errno는 스레드 안전하지만, 다중 스레드 환경에서는 주의가 필요합니다.
    - 일부 함수는 errno를 설정하지 않을 수 있으므로, 함수의 문서를 항상 확인해야 합니다.
    - 오류 처리 코드를 일관성 있게 작성하고, 가능한 모든 오류 상황을 고려해야 합니다.
    - 중요한 리소스(파일, 메모리 등)를 해제하는 것을 잊지 말아야 합니다.


### 멀티스레딩 ###

- 멀티스레딩은 프로그램이 여러 실행 스레드를 동시에 실행할 수 있게 해주는 기술입니다. C 언어에서 멀티 스레딩은
주로 POSIX 스레드(pthread)라이브러리를 통해 구현됩니다.

1. 기본 개념
    - 스레드: 프로세스 내에서 실행되는 독립적인 실행 단위
    - 동시성: 여러 작업이 동시에 실행되는 것처럼 보이는 것
    - 병렬성: 여러 작업이 실제로 동시에 실행되는 것

2. POSIX 스레드 (pthread)라이브러리
    - POSIX 스레드는 유닉스 계열 운영체제에서 표준으로 사용되는 스레드 라이브러리입니다.

    - 주요 함수:

        - `pthread_create()`: 새 스레드 생성
        - `pthread_join()`: 스레드 종료 대기
        - `pthread_exit()`: 현재 스레드 종료
        - `pthread_self()`: 현재 스레드의 ID 반환
        - `pthread_cancle()`: 스레드 강제 종료

    - 기본 사용 예제:

        ```c
        #include <stdio.h>
        #include <pthread.h>

        void *print_message(void *ptr) {
            char *message;
            message = (char *) ptr;
            printf("%s\n", message);
            return NULL;
        }

        int main() {
            pthread_t thread1, thread2;
            char *message1 = "Thread 1";
            char *message2 = "Thread 2";

            pthread_create(&thread1, NULL, print_message, (void*) message1);
            pthread_create(&thread2, NULL, print_message, (void*) message2);

            pthread_join(thread1, NULL);
            pthread_join(thread2, NULL);

            printf("Threads finished.\n");
            return 0;
        }
        ```

3. 동기화 기법
    - 여러 스레드가 공유 자원에 접근할 때 발생할 수 있는 경쟁 조건(race condition)을 방지하기 위해 동기화가 필요합니다.

    - 주요 동기화 기법:
        1. 뮤텍스 (Mutex)
            - 상호 배제를 위한 잠금 메커니즘
            - `pthread_mutex_init()`, `pthread_mutex_lock()`, `pthread_mutex_unlock()`

        2. 세마포어 (Semaphore)
            - 여러 스레드의 접근을 제어하는 카운팅 메커니즘
            - `sem_init()`, `sem_wait()`, `sem_post()`

        3. 조건 변수 (Condition Variable)
            - 스레드 간 신호를 주고받는 메커니즘
            - `pthread_cond_init()`, `pthread_cond_wait()`, `pthread_cond_signal()`

    - 뮤텍스 사용 예제:

        ```c
        #include <stdio.h>
        #include <pthread.h>

        #define NUM_THREADS 5

        pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
        int shared_variable = 0;

        void *increment(void *arg) {
            for (int i = 0; i < 10000; i++) {
                pthread_mutex_lock(&mutex);
                shared_variable++;
                pthread_mutex_unlock(&mutex);
            }
            return NULL;
        }

        int main() {
            pthread_t threads[NUM_THREADS];

            for (int i = 0; i < NUM_THREADS; i++) {
                pthread_create(&threads[i], NULL, increment, NULL);
            }

            for (int i = 0; i < NUM_THREADS; i++) {
                pthread_join(threads[i], NULL);
            }

            printf("Final value: %d\n", shared_variable);
            return 0;
        }
        ```

4. 스레드 안정성 (Thread Safety)
    - 스레드 안전한 함수는 여러 스레드에서 동시에 호출되어도 정확하게 동작합니다.

    - 스레드 안정성을 위한 기법:

        1. 지역 변수 사용: 스택에 저장되어 각 스레드마다 독립적
        2. 재진입 가능한 (reentrant)함수 작성
        3. 전역 변수 대신 스레드 로컬 저장소 (Thread Local Storage) 사용
        4. 적절한 동기화 메커니즘 사용

5. 데드락 (DeadLock)방지
    - 데드락은 두 개 이상의 스레드가 서로의 자원을 기다리며 무한히 블록된 상태를 말합니다.

    - 데드락 방지 기법:
        1. 자원에 대한 순서화된 접근
        2. 타임아웃 사용
        3. 데드락 검출 및 복구 알고리즘 사용

6. 성능 고려사항
    1. 스레드 생성 오버헤드: 스레드 풀 사용 고려
    2. 컨텍스트 스위칭 비용: 너무 많은 스레드 생성 자제
    3. 캐시 일관성: false sharing 방지를 위한 데이터 구조 설계

7. 주의 사항
    1. 공유 자원에 대한 적절한 동기화 필수
    2. 데드락과 경쟁 조건에 주의
    3. 스레드 안정성을 항상 고려
    4. 디버깅이 어려울 수 있으므로 철저한 테스트 필요


### 네트워크 프로그래밍 ###

- C 언어에서의 네트워크 프로그래밍은 주로 소켓 API를 사용하여 이루어집니다. 이는 TCP/IP 프로토콜을 기반으로 한 네트워크 통신을 가능하게 합니다.

1. 소켓 프로그래밍 기초
    - 소켓은 네트워크 통신의 끝점(endpoint)으로, 데이터를 주고받는 통로 역할을 합니다.

    - 주요 함수:
        1. `socket()`: 새로운 소켓 생성
        2. `bind()`: 소켓에 주소 할당
        3. `listen()`: 연결 요청 대기
        4. `accept()`: 클라이언트 연결 수락
        5. `connect()`: 서버에 연결 요청
        6. `send()`, `recv()`: 데이터 송수신
        7. `close()`: 소켓 닫기

2. TCP/IP 통신
    - TCP/IP는 인터넷 프로토콜 스위트의 핵심 프로토콜로, 신뢰성 있는 데이터 전송을 제공합니다.

    - 클라이언트-서버 모델:
        1. 서버: 특정 포트에서 클라이언트의 연결을 기다림
        2. 클라이언트: 서버의 IP 주소와 포트 번호를 사용하여 연결 요청

3. 서버 프로그램 예제:
    ```c
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <sys/socket.h>

    #define PORT 8080

    int main() {
        int server_fd, new_socket;
        struct sockaddr_in address;
        int opt = 1;
        int addrlen = sizeof(address);
        char buffer[1024] = {0};
        char *hello = "Hello from server";

        // 소켓 생성
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }

        // 소켓 옵션 설정
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(PORT);

        // 소켓에 주소 바인딩
        if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }

        // 연결 대기
        if (listen(server_fd, 3) < 0) {
            perror("listen");
            exit(EXIT_FAILURE);
        }

        // 클라이언트 연결 수락
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // 데이터 수신
        read(new_socket, buffer, 1024);
        printf("Message from client: %s\n", buffer);

        // 데이터 송신
        send(new_socket, hello, strlen(hello), 0);
        printf("Hello message sent\n");

        close(new_socket);
        close(server_fd);
        return 0;
    }
    ```

4. 클라이언트 프로그램 예제

    ```c
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <sys/socket.h>

    #define PORT 8080

    int main() {
        int sock = 0;
        struct sockaddr_in serv_addr;
        char *hello = "Hello from client";
        char buffer[1024] = {0};

        // 소켓 생성
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            printf("\n Socket creation error \n");
            return -1;
        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);

        // 서버 IP 주소 설정
        if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
            printf("\nInvalid address/ Address not supported \n");
            return -1;
        }

        // 서버에 연결
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            printf("\nConnection Failed \n");
            return -1;
        }

        // 데이터 송신
        send(sock, hello, strlen(hello), 0);
        printf("Hello message sent\n");

        // 데이터 수신
        read(sock, buffer, 1024);
        printf("Message from server: %s\n", buffer);

        close(sock);
        return 0;
    }
    ```

5. 주요 고려사항
    1. 에러 처리: 모든 네트워크 함수 호출 후 반환값 확인
    2. 버퍼 오버플로우: 수신 버퍼 크기 주의
    3. 바이트 오더: 네트워크 바이트 오더(빅 엔디안)사용
    4. 비동기 I/O: `select()`, `poll()`, `epoll()`등을 이용한 효율적인 I/O처리
    5. 보안: SSL/TLS 사용 고려

6. 고급 주제
    1. UDP 통신: 비연결형, 신뢰성 없는 통신
    2. 멀티태스크: 그룹 통신
    3. 비동기 I/O: 이벤트 기반 프로그래밍
    4. 프로토콜 설계: 애플리케이션 레벨 프로토콜 정의

7. 주의사항
    1. 네트워크 상태 변화에 대한 처리 (연결 끊김, 타임아웃 등)
    2. 리소스 관리(소켓, 메모리 등의 적절한 해제)
    3. 크로스 플랫폼 호환성 고려
    4. 네트워크 보안 (데이터 암호화, 인증 등)


### 디버깅 기법 ###

- 디버깅 기법은 프로그램의 오류를 찾아 수정하는 과정입니다. C 언어에서는 다양한 디버깅 도구와 기법을 사용할 수 있습니다.

1. GDB (GNU Debugger)
    - GDB는 Unix 계열 시스템에서 가장 널리 사용되는 디버거입니다.

    - 주요 GDB 명령어:

        1. `run`(r): 프로그램 실행
        2. `break`(b): 중단점 설정
        3. `continue`(c): 다음 중단점까지 실행
        4. `next`(n): 다음 줄 실행 (함수 호출 시 함수 내부로 들어가지 않음)
        5. `step`(s): 다음 줄 실행 (함수 호출 시 함수 내부로 들어감)
        6. `print`(p): 변수 값 출력
        7. `backtrace`(bt): 호출 스택 출력
        8. `watch`: 변수 감시
        9. `info`: 프로그램 상태 정보 출력

    - GDB 사용 예제:

        ```bash
        $ gcc -g program.c -o program  # -g 옵션으로 디버그 정보 포함하여 컴파일
        $ gdb ./program

        (gdb) break main
        (gdb) run
        (gdb) next
        (gdb) print variable_name
        (gdb) continue
        (gdb) quit
        ```

2. Valgrind
    - Valgrind는 메모리 누수 및 기타 메모리 관련 버그를 찾는 데 유용한 도구입니다.

    - Valgrind 사용 예제:

        ```bash
        $ gcc -g program.c -o program
        $ valgrind --leak-check=full ./program
        ```

    - Valgrind는 다음과 같은 문제들을 검출할 수 있습니다.
        - 메모리 누수
        - 초기화되지 않은 메모리 사용
        - 잘못된 메모리 접근
        - 이중 해제 (double free)

3. 정적 분석 도구
    - 정적 분석 도구는 코드를 실행하지 않고 소스 코드를 분석하여 잠재적인 버그를 찾아냅니다.

    - 주요 정적 분석 도구:

        1. Clang Static Analyzer
        2. CppCheck
        3. Splint

    - CppCheck 사용 예제:

        ```bash
        cppcheck program.c
        ```

4. 로깅 (logging)
    - 로깅은 프로그램의 실행 흐름과 상태를 추적하는 데 유용한 기법입니다.

    - 간단한 로깅 매크로 예제:
        ```c
        #include <stdio.h>
        #include <time.h>

        #define LOG_ERROR(message, ...) do { \
            time_t now = time(NULL); \
            char *time_str = ctime(&now); \
            time_str[strlen(time_str) - 1] = '\0'; \
            fprintf(stderr, "[ERROR] [%s] " message "\n", time_str, ##__VA_ARGS__); \
        } while (0)

        int main() {
            int x = 5;
            LOG_ERROR("An error occurred: x = %d", x);
            return 0;
        }
        ```

5. 어설션 (Assertions)
    - 어설션은 프로그램의 상태가 예상과 일치하는지 확인하는 데 사용됩니다.

    ```c
    #include <assert.h>

    void function(int* ptr) {
        assert(ptr != NULL);  // ptr이 NULL이면 프로그램 중단
        // 함수 로직...
    }
    ```

6. 메모리 덤프 분석
    - 프로그램이 비정상적으로 종료될 때 생성되는 코어 덤프 파일을 분석하여 문제의 원인을 찾을 수 있습니다.

    ```bash
    gdb ./program core
    (gdb) backtrace
    ```

7. 프로파일링
    - 프로파일링은 프로그램의 성능을 분석하고 최적화하는 데 사용됩니다.

    - gprof 사용 예제:

    ```bash
    $ gcc -pg program.c -o program
    $ ./program
    $ gprof program gmon.out > analysis.txt
    ```

8. 주요 디버깅 전략:
    1. 문제 재현: 버그를 일관성 있게 재현할 수 있는 방법 찾기
    2. 이진 검색: 문제 영역을 반으로 나누어 범위 좁히기
    3. 로그 분석: 상세한 로그를 통해 문제 추적
    4. 코드 리뷰: 다른 개발자와 함께 코드 검토
    5. 단위 테스트: 작은 단위의 기능 테스트로 문제 영역 특정

- 주의사항
    1. 디버그 빌드와 릴리스 빌드의 차이 이해
    2. 최적화로 인한 디버깅의 어려움 인식
    3. 실제 환경과 디버그 환경의 차이 고려
    4. 디버깅 코드가 프로덕션 코드에 남지 않도록 주의
    5. 버그 수정 후 회귀 테스트 수행

### 빌드 시스템 ###

- 빌드 시스템은 소스 코드를 실행 가능한 프로그램으로 변환하는 과정을 자동화합니다. C 언어에서는 주로 Makefile을 사용하여 빌드 프로세스를 관리합니다.

1. Makefile 기초
    - Makefile은 프로젝트의 빌드 규칙을 정의하는 파일입니다.

    - Makefile의 기본 구조:
        ```makefile
        target: dependencies
            commands
        ```

        - `target`: 생성할 파일
        - `dependencies`: 타겟을 만드는 데 필요한 파일들
        - `commands`: 타겟을 생성하기 위해 실행할 명령어 (탭으로 들여쓰기)

    - 간단한 Makefile 예제:

        ```makefile
        CC = gcc
        CFLAGS = -Wall -g

        program: main.o helper.o
            $(CC) $(CFLAGS) -o program main.o helper.o

        main.o: main.c helper.h
            $(CC) $(CFLAGS) -c main.c

        helper.o: helper.c helper.h
            $(CC) $(CFLAGS) -c helper.c

        clean:
            rm -f program *.o
        ```

        - 이 Makefile은 `main.c`와 `helper.c`를 컴파일하여 `program`이라는 실행 파일을 만듭니다.


2. Makefile 변수
    - Makefile에서는 변수를 사용하여 반복되는 값을 저장할 수 있습니다.

    ```makefile
    CC = gcc
    CFLAGS = -Wall -g
    OBJS = main.o helper.o
    TARGET = program

    $(TARGET): $(OBJS)
        $(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

    clean:
        rm -f $(TARGET) $(OBJS)
    ```

3. 자동 변수
    - Makefile에서는 특별한 자동 변수를 제공합니다:

        - `$@`: 현재 타겟의 이름
        - `$<`: 첫 번째 타켓의 의존성 이름
        - `$^`: 모든 의존성의 이름

    ```makefile
    $(TARGET): $(OBJS)
        $(CC) $(CFLAGS) -o $@ $^
    ```

4. 패턴 규칙
    - 패턴 규칙을 사용하여 반복적인 빌드 규칙을 간단히 표현할 수 있습니다.

    ```makefile
    %.o: %.c
        $(CC) $(CFLAGS) -c $< -o $@
    ```
    - 이 규칙은 모든 `.c` 파일을 `.o`파일로 컴파일합니다.

5. 헤더 파일 관리
    - 헤더 가드 (Header Guards)
        - 헤더 가드는 헤더 파일이 여러 번 포함되는 것을 방지합니다.

        ```c
        #ifndef MYHEADER_H
        #define MYHEADER_H

        // 헤더 파일 내용

        #endif // MYHEADER_H
        ```

    - #pragma once
        - 일부 컴파일러에서는 `#pragma once`를 사용하여 더 간단히 헤더 가드를 구현할 수 있습니다.

        ```c
        #pragma once

        // 헤더 파일 내용
        ```

6. 의존성 자동 생성
    - gcc의 `-MM`옵션을 사용하여 헤더 파일 의존성을 자동으로 생성할 수 있습니다.

    ```makefile
    depend: $(SRCS)
        $(CC) -MM $(CFLAGS) $^ > .depend

    -include .depend
    ```

7. 조건부 컴파일
    - Makefile에서 조건문을 사용하여 다양한 빌드 설정을 관리할 수 있습니다.

    ```makefile
    ifdef DEBUG
    CFLAGS += -g
    else
    CFLAGS += -O2
    endif
    ```

8. 실제 프로젝트 Makefile 예제
    ```makefile
    CC = gcc
    CFLAGS = -Wall -g
    LDFLAGS = -lm
    SRCS = $(wildcard *.c)
    OBJS = $(SRCS:.c=.o)
    TARGET = myprogram

    .PHONY: all clean depend

    all: $(TARGET)

    $(TARGET): $(OBJS)
        $(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

    %.o: %.c
        $(CC) $(CFLAGS) -c $< -o $@

    clean:
        rm -f $(TARGET) $(OBJS) .depend

    depend: $(SRCS)
        $(CC) -MM $(CFLAGS) $^ > .depend

    -include .depend
    ```

    - 이 Makefile은 현재 디렉토리의 모든 `.c` 파일을 컴파일하여 `mygrogram`이라는 실행 파일을 생성합니다.

- 주의사항
    1. Makefile에서는 탭을 사용하여 명령어를 들여써야 합니다. (스페이스 사용 시 오류 발생).
    2. 순환 의존성을 만들지 않도록 주의해야 합니다.
    3. 대규모 프로젝트의 경우 CMake나 Autotools 같은 더 강력한 빌드 시스템 사용을 고려해볼 수 있습니다.
    4. 헤더 파일의 변경사항이 제대로 반영되도록 의존성을 정확히 명시해야 합니다.
    5. 크로스 플랫폼 빌드를 고려한다면 이식성 있는 명령어를 사용해야 합니다.

### 최적화 기법 ###

- 최적화는 프로그램의 실행 속도를 높이거나 메모리 사용량을 줄이는 과정입니다. C언어에서는 다양한 수준에서 최적화를 적용할 수 있습니다.

1. 컴파일러 최적화 옵션
    - GCC(GNU Compiler Collection)는 다양한 최적화 옵션을 제공합니다.

    - 주요 최적화 레벨:
        - `-00`: 최적화 없음 (기본값)
        - `-01`: 기본적인 최적화
        - `-02`: 더 많은 최적화 (추천)
        - `-03`: 가장 강력한 최적화 (주의 필요)
        - `0s`: 코드 크기 최적화

    - 사용 예:
    ```bash
    gcc -02 -o program program.c
    ```

2. 코드 레벨 최적화
    1. 루프 최적화
        - 루프 언롤링: 루프 내부 코드를 풀어서 반복 횟수 감소

        ```c
        // 최적화 전
        for (int i = 0; i < 4; i++) {
            array[i] = i;
        }

        // 최적화 후
        array[0] = 0;
        array[1] = 1;
        array[2] = 2;
        array[3] = 3;
        ```

        - 루프 불변식 이동: 루프 내에서 변하지 않는 연산을 루프 밖으로 이동

        ```c
        // 최적화 전
        for (int i = 0; i < n; i++) {
            result += array[i] * (a * b);
        }

        // 최적화 후
        int temp = a * b;
        for (int i = 0; i < n; i++) {
            result += array[i] * temp;
        }
        ```

    2. 함수 인라인화
        - 작은 함수를 호출 지점에 직접 삽입하여 함수 호출 오버헤드 제거

        ```c
        inline int square(int x) {
            return x * x;
        }
        ```

    3. 데이터 구조 최적화
        - 구조체 멤버 정렬

        ```c
        // 최적화 전
        struct Example {
            char a;
            int b;
            char c;
        };

        // 최적화 후
        struct Example {
            int b;
            char a;
            char c;
            char padding;
        };
        ```

    4. 비트 연산 활용
        - 곱셈/나눗셈을 비트 시프트로 대체(2의 거듭제곱인 경우)

        ```c
        // 최적화 전
        int result = num * 4;

        // 최적화 후
        int result = num << 2;
        ```

3. 메모리 최적화
    1. 메모리 풀 사용
        - 자주 할당/해제되는 객체들을 위한 메모리 풀 구현

        ```c
        #define POOL_SIZE 1000
        #define OBJECT_SIZE sizeof(struct MyObject)

        char memory_pool[POOL_SIZE * OBJECT_SIZE];
        int next_free = 0;

        void* allocate() {
            if (next_free < POOL_SIZE) {
                return &memory_pool[next_free++ * OBJECT_SIZE];
            }
            return NULL;
        }

        void deallocate(void* ptr) {
            // 간단한 구현에서는 실제로 아무것도 하지 않음
        }
        ```

    2. 캐시 친화적 데이터 접근
        - 데이터 지역성을 고려한 메모리 접근 패턴 사용

        ```c
        // 캐시 효율적
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                process(array[i][j]);
            }
        }

        // 캐시 비효율적
        for (int j = 0; j < M; j++) {
            for (int i = 0; i < N; i++) {
                process(array[i][j]);
            }
        }
        ```

4. 프로파일링 도구
    - 프로파일링은 프로그램의 성능을 분석하여 병목 지점을 찾는 과정입니다.

    1. gprof 사용

        ```bash
        # 프로파일링 정보를 포함하여 컴파일
        gcc -pg -o program program.c

        # 프로그램 실행 (gmon.out 파일 생성)
        ./program

        # 프로파일 분석
        gprof program gmon.out > analysis.txt
        ```

    2. Valgrind 사용

        ```bash
        valgrind --tool=callgrind ./program
        ```

        - 이후 KCachegrind 등의 도구로 결과 분석

5. 최적화 주의 사항
    1. 가독성과 유지보수성 저하: 과도한 최적화는 코드의 가독성을 해칠 수 있습니다.
    2. 예상치 못한 부작용: 특히 컴파일러 최적화 옵션 사용 시 주의가 필요합니다.
    3. 플랫폼 의존성: 일부 최적화는 특정 플랫폼에서만 효과적일 수 있습니다.
    4. 과도한 조기 최적화 경계: 프로파일링을 통해 실제 병목 지점을 파악한 후 최적화하는 것이 중요합니다.

    - 최적화 전략

        1. 측정 먼저: 최적화 전후로 항상 성능을 측정하여 효과를 확인합니다.
        2. 80-20 규칙 적용: 대부분의 성능 문제는 코드의 일부분에서 발생합니다.
        3. 알고리즘 개선: 때로는 더 효율적인 알고리즘을 사용하는 것이 미시적 최적화보다 더 효과적입니다.
        4. 컴파일러 최적화 활용: 많은 경우 컴파일러 최적화만으로도 상당한 성능 향상을 얻을 수 있습니다.
        5. 병렬화 고려: 멀티코어 환경에서는 병렬 처리를 통해 성능을 크게 향상시킬 수 있습니다.


### 보안 기법 ###

- C 언어는 강력하지만 동시에 위험할 수 있는 언어입니다. 메모리를 직접 관리하고 포인터를 사용하기 때문에 보안 취약점이 발생할 가능성이 높습니다.
따라서 안전한 코딩 practices를 따르는 것이 매우 중요합니다.

1. 버퍼 오버플로우 방지
    - 버퍼 오버플로우는 가장 흔하고 위험한 보안 취약점 중 하나입니다.

    - 예방 기법:

        1. 배열 경계 검사

        ```c
        #define ARRAY_SIZE 10

        void safe_copy(int *dest, int *src, size_t n) {
            if (n > ARRAY_SIZE) {
                n = ARRAY_SIZE;  // 배열 크기를 초과하지 않도록 제한
            }
            for (size_t i = 0; i < n; i++) {
                dest[i] = src[i];
            }
        }
        ```

        2. 안전한 문자열 함수 사용

        ```c
        #include <string.h>

        char dest[20];
        const char *src = "This is a very long string";

        // 위험한 방식
        // strcpy(dest, src);  // 버퍼 오버플로우 발생 가능

        // 안전한 방식
        strncpy(dest, src, sizeof(dest) - 1);
        dest[sizeof(dest) - 1] = '\0';  // null 종료 문자 보장
        ```

        3. 동적 메모리 할당 시 크기 검사

        ```c
        char *buffer = (char *)malloc(strlen(user_input) + 1);
        if (buffer == NULL) {
            // 메모리 할당 실패 처리
            return;
        }
        strcpy(buffer, user_input);
        // 사용 후
        free(buffer);
        ```

2. 정수 오버플로우 방지
    - 정수 오버플로우는 예상치 못한 결과를 초래할 수 있습니다.

    ```c
    #include <limits.h>

    int safe_add(int a, int b) {
        if ((b > 0 && a > INT_MAX - b) || (b < 0 && a < INT_MIN - b)) {
            // 오버플로우 발생
            return 0;  // 또는 에러 처리
        }
        return a + b;
    }
    ```

3. 형식 문자열 취약점 방지
    - 형식 문자열 공격은 `printf`와 같은 함수를 악용합니다.
    
    ```c
    // 위험한 방식
    // printf(user_input);  // 사용자 입력을 직접 형식 문자열로 사용

    // 안전한 방식
    printf("%s", user_input);
    ```

4. 안전한 입력 처리
    - 사용자 입력은 항상 검증되어야 합니다.

    ```c
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define MAX_INPUT 100

    char* get_input() {
        char* input = (char*)malloc(MAX_INPUT);
        if (input == NULL) {
            return NULL;
        }

        if (fgets(input, MAX_INPUT, stdin) == NULL) {
            free(input);
            return NULL;
        }

        // 개행 문자 제거
        input[strcspn(input, "\n")] = 0;

        return input;
    }

    // 사용
    char* user_input = get_input();
    if (user_input != NULL) {
        // 입력 처리
        free(user_input);
    }
    ```

5. 메모리 관리
    - 메모리 누수와 use-after-free 취약점을 방지합니다.

    ```c
    void* safe_malloc(size_t size) {
        void* ptr = malloc(size);
        if (ptr == NULL) {
            // 메모리 할당 실패 처리
            exit(1);
        }
        return ptr;
    }

    void safe_free(void** ptr) {
        if (ptr != NULL && *ptr != NULL) {
            free(*ptr);
            *ptr = NULL;  // dangling pointer 방지
        }
    }

    // 사용
    int* numbers = (int*)safe_malloc(10 * sizeof(int));
    // 사용 후
    safe_free((void**)&numbers);
    ```

6. 권한 관리
    - 최소 권한 원칙을 따릅니다.

    ```c
    #include <unistd.h>

    void drop_privileges() {
        if (setuid(getuid()) != 0) {
            // 권한 강하 실패 처리
            exit(1);
        }
    }
    ```

7. 안전한 난수 생성
    - 암호학적으로 안전한 난수 생성기를 사용합니다.

    ```c
    #include <openssl/rand.h>

    unsigned char generate_random_byte() {
        unsigned char byte;
        if (RAND_bytes(&byte, 1) != 1) {
            // 난수 생성 실패 처리
            exit(1);
        }
        return byte;
    }
    ```

8. 컴파일러 보안 옵션 활용
    - gcc에서 제공하는 보안 관련 컴파일 옵션을 사용합니다.

    ```bash
    gcc -Wall -Wextra -Werror -fstack-protector-all -D_FORTIFY_SOURCE=2 -O2 -o program program.c
    ```

9. 데이터 무결성 검사
    - 중요한 데이터의 무결성을 검사합니다.

    ```c
    #include <openssl/sha.h>

    void compute_hash(const char* data, size_t length, unsigned char* hash) {
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, data, length);
        SHA256_Final(hash, &sha256);
    }
    ```

10. 보안 관련 Best Practices
    1. 모든 사용자 입력을 신뢰하지 않고 검증합니다.
    2. 에러 메시지에 민감한 정보를 포함하지 않습니다.
    3. 하드코딩된 비밀번호나 키를 사용하지 않습니다.
    4. 안전한 라이브러리와 최신 버전의 컴파일러를 사용합니다.
    5. 정기적으로 코드 리뷰와 보안 감사를 수행합니다.
    6. 필요 이상의 권한으로 프로그램을 실행하지 않습니다.
    7. 중요한 데이터는 암호화하여 저장합니다.

### 플랫폼 특정 기능 ###

- C언어는 다양한 플랫폼에서 사용되는 범용 프로그래밍 언어입니다. 하지만 각 플랫폼마다 특정한 API와 기능들이 있어, 이들을 활용하면
해당 플랫폼에 최적화된 프로그램을 작성할 수 있습니다.

1. Windows API
    - Windows API(또는 Win32 API)는 Microsoft Windows 운영 체제에서 제공하는 시스템 호출과 함수들의 집합입니다.

    - 주요 기능:
        1. 파일 및 디렉토리 조작
        2. 프로세스 및 스레드 관리
        3. 메모리 관리
        4. GUI 프로그래밍
        5. 네트워킹

    - 예제: 파일 생성 및 쓰기

        ```c
        #include <windows.h>
        #include <stdio.h>

        int main() {
            HANDLE hFile;
            DWORD dwBytesWritten = 0;
            char data[] = "Hello, Windows!";

            hFile = CreateFile("test.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

            if (hFile == INVALID_HANDLE_VALUE) {
                printf("Could not create file (error %d)\n", GetLastError());
                return 1;
            }

            WriteFile(hFile, data, strlen(data), &dwBytesWritten, NULL);
            CloseHandle(hFile);

            printf("Written %d bytes\n", dwBytesWritten);
            return 0;
        }
        ```
        
        - 컴파일 방법:
        ```bash
        cl program.c /link user32.lib gdi32.lib
        ```

2. POSIX API
    - POSIX(Portable Operating System Interface)는 유닉스 계열 운영체제에서 사용되는 표준 API 집합입니다.

    - 주요 기능:
        1. 프로세스 관리
        2. 파일 시스템 조작
        3. 파이프와 FIFO
        4. 시그널 처리
        5. POSIX 스레드 (pthread)

    - 예제: 프로세스 생성

        ```c
        #include <stdio.h>
        #include <stdlib.h>
        #include <unistd.h>
        #include <sys/wait.h>

        int main() {
            pid_t pid = fork();

            if (pid < 0) {
                fprintf(stderr, "Fork failed\n");
                return 1;
            } else if (pid == 0) {
                printf("Child process\n");
                execlp("/bin/ls", "ls", NULL);
            } else {
                printf("Parent process\n");
                wait(NULL);
                printf("Child complete\n");
            }

            return 0;
        }
        ```

        - 컴파일 방법:
        ```bash
        gcc -o program program.c
        ```

3. 플랫폼 간 이식성
    - 플랫폼 특정 기능을 사용하면서도 이식성을 유지하는 방법이 있습니다.

    1. 조건부 컴파일 사용

        ```c
        #ifdef _WIN32
            // Windows specific code
        #else
            // POSIX specific code
        #endif
        ```

        - 예제: 플랫폼 독립적 파일 읽기

            ```c
            #include <stdio.h>
            #include <stdlib.h>

            #ifdef _WIN32
            #include <windows.h>
            #else
            #include <unistd.h>
            #endif

            void sleep_for(int seconds) {
            #ifdef _WIN32
                Sleep(seconds * 1000);
            #else
                sleep(seconds);
            #endif
            }

            int main() {
                printf("Going to sleep for 3 seconds...\n");
                sleep_for(3);
                printf("Awake!\n");
                return 0;
            }
            ```

4. 플랫폼 특정 라이브러리
    - Windows: COM(Component Object Model)
        - COM은 Windows에서 사용되는 바이너리 인터페이스 표준입니다.

        ```c
        #include <windows.h>
        #include <objbase.h>

        int main() {
            HRESULT hr = CoInitialize(NULL);
            if (SUCCEEDED(hr)) {
                // COM objects can be created and used here
                CoUninitialize();
            }
            return 0;
        }
        ```

    - POSIX: X11(X Window System)
        - X11은 유닉스 계열 시스템에서 사용되는 윈도우 시스템입니다.

        ```c
        #include <X11/Xlib.h>

        int main() {
            Display *display = XOpenDisplay(NULL);
            if (display == NULL) {
                fprintf(stderr, "Cannot open display\n");
                return 1;
            }
            
            // X11 operations can be performed here
            
            XCloseDisplay(display);
            return 0;
        }
        ```

5. 주의사항
    1. 플랫폼 특정 기능을 사용할 때는 이식성이 저하될 수 있음을 인지해야 합니다.
    2. 가능한 한 표준 C라이브러리 함수를 사용하여 이식성을 높이는 것이 좋습니다.
    3. 플랫폼 간 차이를 추상화하는 라이브러리 (예: SDL, Qt)를 사용하는 것도 좋은 방법입니다.
    4. 플랫폼 특정 기능을 사용할 때는 해당 플랫폼의 문서를 철저히 참고해야 합니다.
    5. 여러 플랫폼을 지원해야 하는 경우, 각 플랫폼에서 충분한 테스트가 필요합니다.