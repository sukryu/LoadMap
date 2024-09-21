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
    - C는 하드웨어를 직접 제어할 수 있는 저수준 기능과 추상화된 고수준 구조를 동시에 제공합니다. 이를 통해 높은 성능과 효율성을 달성 할 수 있습니다.

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
        - 객체 파일 (.o 또는 .obj) todtjd
    
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

        a = a + b;
        b = a - b;
        a = a - b;

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