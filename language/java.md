# JAVA 프로그래밍 언어 #

## Java란? ###

Java는 1995년 Sun Microsystems(현재 Oracle Corporation의 자회사)에서 개발한 객체 지향 프로그래밍 언어입니다.
Java는 "Write Once, Run Anywhere" (한 번 작성하면 어디서나 실행 가능)라는 철학을 바탕으로 설계되었으며, 이는 Java 플랫폼의 독립성을 나타냅니다.

### Java의 주요 특징 ###

Java의 주요 특징은 다음과 같습니다.

1. 객체 지향: Java는 완전한 객체 지향 언어로, 모든 코드가 클래스 내에 작성됩니다.
2. 플랫폼 독립성: Java 프로그램은 Java Virtual Machine (JVM)에서 실행되므로, 다양한 운영체제에서 동일하게 동작합니다.
3. 강력한 타입 검사: Java는 정적 타입 언어로, 컴파일 시점에 타입 오류를 잡아낼 수 있습니다.
4. 자동 메모리 관리: 가비지 컬렉션을 통해 개발자가 명시적으로 메모리를 관리할 필요가 없습니다.
5. 멀티스레딩 지원: Java는 동시성 프로그래밍을 위한 내장 지원을 제공합니다.
6. 풍부한 표준 라이브러리: Java는 다양한 기능을 제공하는 방대한 표준 라이브러리를 포함하고 있습니다.

### Java의 동작 방식 ###

Java 프로그램의 실행 과정은 다음과 같습니다.

1. 소스 코드 작성: 개발자가 .java 확장자를 가진 파일에 Java 코드를 작성합니다.
2. 컴파일: javac 컴파일러를 사용하여 소스 코드 (.java 파일)를 바이트코드 (.class)로 변환합니다. 바이트코드는 JVM이 이해할 수 있는 중간 언어입니다.
3. 클래스 로딩: 프로그램 실행 시, JVM의 클래스 로더가 필요한 .class 파일을 메모리에 로드합니다.
4. 바이트코드 검증: JVM의 바이트코드 검증기가 로드된 바이트코드의 무결성을 검사합니다.
5. 실행: JVM의 인터프리터가 바이트코드를 한 줄씩 기계어로 변환하여 실행합니다. 자주 사용되는 코드는 JIT(Just-In-Time) 컴파일러에 의해 네이티브 코드로 컴파일되어 더 빠르게 실행됩니다.

### JVM(Java Virtual Machine) ###

JVM은 Java 프로그램을 실행하는 가상 머신으로, 다음과 같은 주요 구성 요소를 가집니다.

1. 클래스 로더: 클래스 파일을 로드하고 링크하는 역할을 합니다.
2. 실행 엔진:
    - 인터프리터: 바이트코드를 한 줄씩 해석하고 실행합니다.
    - JIT 컴파일러: 반복적으로 실행되는 코드를 네이티브 코드로 컴파일하여 성능을 향상시킵니다.
    - 가비지 컬렉터: 더 이상 사용되지 않는 객체를 자동으로 메모리에서 제거합니다.

3. 런타임 데이터 영역:
    - 메서드 영역: 클래스 구조, 메서드 데이터, 생성자 등을 저장합니다.
    - 힙: 모든 객체 인스턴스와 배열이 할당되는 영역입니다.
    - 스택: 메서드 호출과 지역 변수를 저장합니다.
    - PC 레지스터: 현재 실행 중인 JVM 명령의 주소를 저장합니다.
    - 네이티브 메서드 스택: 네이티브 메서드 정보를 저장합니다.

### Java의 메모리 관리 ###

Java는 가비지 컬렉션을 통해 자동으로 메모리를 관리합니다.

1. 객체 생성: 새로운 객체가 생성되면 힙 메모리에 할당됩니다.
2. 가비지 컬렉션: JVM은 주기적으로 가비지 컬렉션을 실행하여 더 이상 참조되지 않는 객체를 식별하고 제거합니다.
3. 세대별 가비지 컬렉션: 객체를 Young Generation과 Old Generation으로 분류하여 효율적으로 관리합니다.
4. GC 알고리즘: Serial GC, Parallel GC, CMS GC, G1 GC 등 다양한 가비지 컬렉션 알고리즘을 제공합니다.

Java의 자동 메모리 관리는 개발자의 부담을 줄이지만, 대규모 애플리케이션에서는 GC 튜닝이 필요할 수 있습니다.

### Java의 버전 역사 ###

Java는 지속적으로 발전해왔으며, 주요 버전별 특징은 다음과 같습니다.

- Java 1.0(1996): 최초의 공식 릴리즈
- Java 1.1(1997): 내부 클래스, JavaBeans 등 추가
- Java 1.2(1998): Swing, Collections 프레임워크 도입
- Java 1.3(2000): HotSpot JVM, JNDI 등 추가
- Java 1.4 (2002): assert 키워드, 정규표현식, NIO 등 도입
- Java 5 (2004): 제네릭, 열거형, 어노테이션, 오토박싱/언박싱 등 도입
- Java 6 (2006): 성능 개선, Scripting API 등 추가
- Java 7 (2011): try-with-resources, 다이아몬드 연산자 등 도입
- Java 8 (2014): 람다 표현식, 스트림 API, 새로운 날짜/시간 API등 추가
- Java 9 (2017): 모듈 시스템 도입, JShell 추가
- Java 10 (2018): 지역 변수 타입 추론 (var) 도입
- Java 11 (2018): HTTP 클라이언트 API 표준화, 람다 매개변수에 var 사용 가능
- Java 12-15: 스위치 표현식, 텍스트 블록 등 다양한 기능 추가
- Java 16 (2021): 레코드, 패턴 매칭 for instanceof등 도입
- Java 17 (2021, LTS): 봉인 클래스, 새로운 랜덤 넘버 생성 API등 추가

이러한 버전 업데이트를 통해 Java는 현대적인 프로그래밍 패러다임을 지원하면서도 하위 호환성을 유지하고 있습니다.

## Java의 주요 기능과 개념 ##

### 변수와 데이터 타입 ###

1. 변수: 변수는 데이터를 저장하는 컨테이너입니다. Java에서 변수를 선언할 때는 데이터 타입을 명시해야 합니다.
    1. 변수 선언: 기본 형식: `데이터 타입 변수명;`
    - 예시:
    ```Java
    int age;
    double salary;
    String name;
    ```

    2. 변수 초기화: 변수를 선언함과 동시에 값을 할당할 수 있습니다.
    - 예시:
    ```Java
    int age = 25;
    double salary = 50000.50;
    String name = "John Doe";
    ```

    3. 변수 명명 규칙:
        - 문자, 숫자, 언더스코어(_), 달러기호($)만 사용 가능.
        - 숫자로 시작할 수 없음
        - 대소문자 구분
        - 예약어 사용 불가
        - 관례적으로 camelCase 사용 (첫 단어는 소문자, 이후 단어는 대문자로 시작)

    4. 변수의 스코프:
        - 지역 변수: 메서드나 블록 내에서 선언되고 사용됨.
        - 인스턴스 변수: 클래스 내부, 메서드 외부에서 선언됨.
        - 클래스 변수 (static 변수): static 키워드를 사용하여 선언됨.

2. 데이터 타입:
    - Java는 두 가지 주요 데이터 타입 범주를 가집니다. 기본 타입(Primitive Types)과 참조 타입(Reference Types).

    1. 기본 타입(Primitive Types)
        1. 정수형:
            1. byte:
                - 8비트 부호 있는 2의 보수 정수
                - 범위: -128 ~ 127
                - 예: `byte b = 100;`
            
            2. short:
                - 16비트 부호 있는 2의 보수 정수
                - 범위: -32,768 ~ 32767
                - 예: `short s = 1000;`

            3. int:
                - 32비트 부호있는 2의 보수 정수
                - 범위: -2^31 ~ 2^31 - 1
                - 예: `int i = 100000;`

            4. long:
                - 64비트 부호있는 2의 보수 정수
                - 범위: -2^63 ~ 2^63 - 1
                - 예: `long i = 100000L;` (L또는 l 접미사 사용)

        2. 실수형:
            1. float
                - 32비트 IEEE 754 부동소수점
                - 범위: 약 ±3.40282347E+38F (6-7개의 유효 자릿수)
                - 예: `float f = 3.14f;` (f 또는 F접미사 사용)

            2. double
                - 64비트 IEEE 754 부동소수점
                - 범위: 약  ±1.79769313486231570E+308 (15개의 유효 자릿수)
                - 예: `double d = 3.14159265359;`
        
        3. 문자형:
            1. char
                - 16비트 유니코드 문자
                - 범위: '\u0000' (0) ~ '\uffff' (65,535)
                - 예: `char c = 'A';`
        
        4. 논리형:
            1. boolean
                - true or false 값을 가짐
                - 예: `boolean isJavaFun = true;`
        
    2. 참조 타입 (Reference Types)
        - 참조 타입은 기본 타입을 제외한 모든 타입입니다. 이들은 객체의 주소를 저장합니다.

        1. 클래스 타입:
            - 예: `String str = "Hello";`
        
        2. 인터페이스 타입:
            - 예: `List<String> list = new ArrayList<>();`
        
        3. 배열 타입:
            - 예: `int[] numbers = {1, 2, 3, 4, 5};`

    3. 타입 변환 (Type Casting)
        
        1. 자동 타입 변환 (묵시적 형변환)
            - 작은 크기의 타입에서 큰 크기의 타입으로 자동으로 변환됩니다.
            - 예:
            ```Java
            int intValue = 100;
            long longValue = intValue; // int에서 long으로 자동 변환
            ```
        
        2. 강제 타입 변환(명시적 형변환)
            - 큰 크기의 타입에서 작은 크기의 타입으로 변환할 때 사용합니다. 데이터 손실의 가능성이 있습니다.
            - 예:
            ```Java
            long longValue = 100;
            int intValue = (int) longValue; // long에서 int로 강제 변환
            ```
        
    4. Wrapper 클래스
        - 기본 타입에 대응하는 객체 타입입니다. Java 5부터 오토박싱과 언박싱을 지원합니다.

        - byte -> Byte
        - short -> Short
        - int -> Int
        - long -> Long
        - float -> Float
        - double -> Double
        - char -> Character
        - boolean -> Boolean

        -예:
        ```Java
        Integer num = 100; // 오토박싱
        int value = num; // 언박싱
        ```

    5. 상수 (Constants)
        - final 키워드를 사용하여 상수를 선언합니다. 상수는 한 번 초기화되면 값을 변경할 수 없습니다.
        - 예:
        ```Java
        final double PI = 3.14159;
        ```


### 제어 구조 ###

Java의 제어 구조는 프로그램의 실행 흐름을 제어하는 데 사용됩니다. 주요 제어 구조는 조건문, 반복문, 그리고 분기문으로 나눌 수 있습니다.

1. 조건문:
    - 조건문은 특정 조건에 따라 코드 블록의 실행 여부를 결정합니다.

    1. if문
        - 가장 기본적인 조건문입니다.
        ```Java
        if (condition) {
        // 조건이 참일 때 실행되는 코드
        }
        ```

        - 예시:
        ```Java
        int age = 18;
        if (age >= 18) {
            System.out.println("성인입니다.");
        }
        ```
    2. if-else 문
        - 조건이 거짓일 때 실행할 코드를 지정할 수 있습니다.
        ```Java
        if (condition) {
            // 조건이 참일 떄 실행할 코드
        } else {
            // 조건이 거짓일 때 실행할 코드
        }
        ```

        - 예시:
        ```Java
        int age = 16;
        if (age >= 18) {
            System.out.println("성인입니다.");
        } else {
            System.out.println("미성년자입니다.");
        }
        ```

    3. if-else if-else 문
        - 여러 조건을 순차적으로 검사할 수 있습니다.
        ```Java
        if (condition1) {
            // 조건1이 참일 때 실행되는 코드
        } else if (condition2) {
            // 조건2가 참일 때 실행되는 코드
        } else {
            // 모든 조건이 거짓일 때 실행되는 코드
        }
        ```

        - 예시:
        ```Java
        int score = 85;
        if (score >= 90) {
            System.out.println("A 등급");
        } else if (score >= 80) {
            System.out.println("B 등급");
        } else if (score >= 70) {
            System.out.println("C 등급");
        } else {
            System.out.println("D 등급");
        }
        ```

    4. switch 문
        - 여러 가지 경우 중 하나를 선택하여 실행합니다.
        ```Java
        switch (expression) {
            case value1:
                // value1에 해당하는 코드
                break;
            case value2:
                // value2에 해당하는 코드
                break;
            // ...
            default:
                // 어떤 case에도 해당하지 않을 때 실행되는 코드
        }
        ```

        -예시:
        ```Java
        int dayOfWeek = 3;
        switch (dayOfWeek) {
            case 1:
                System.out.println("월요일");
                break;
            case 2:
                System.out.println("화요일");
                break;
            case 3:
                System.out.println("수요일");
                break;
            // ...
            default:
                System.out.println("잘못된 입력");
        }
        ```

2. 반복문
    - 반복문은 특정 코드 블록을 여러 번 실행하는 데 사용됩니다.

    1. for 루프
        - 특정 횟수만큼 반복할 때 주로 사용합니다.
        ```Java
        for (initialization; condition; update) {
            // 반복 실행할 코드
        }
        ```

        - 예시:
        ```Java
        for (int i = 0; i < 5; i++) {
            System.out.println("반복 " + i);
        }
        ```

    2. while 루프
        - 조건이 참인 동안 계속해서 반복합니다.
        ```Java
        while (contidion) {
            // 반복 실행할 코드
        }
        ```

        - 예시:
        ```Java
        int count = 0;
        while (count < 5) {
            System.out.println("반복 " + count);
            count++;
        }
        ```

    3. do-while 루프
        - 코드 블록을 최소한 한 번 실행한 후, 조건이 참인 동안 계속 반복합니다.
        ```Java
        do {
            // 반복 실행할 코드
        } while (condition);
        ```

        - 예시:
        ```Java
        int count = 0;
        do {
            System.out.println("반복 " + count);
            count++;
        } while (count < 5);
        ```

    4. 향상된 for 루프 (for-each)
        - 배열이나 컬렉션의 모든 요소를 순회할 때 사용합니다.
        ```Java
        for (elementType element : collection) {
            // 각 요소에 대해 실행할 코드
        }
        ```

        - 예시:
        ```Java
        int[] numbers = {1, 2, 3, 4, 5};
        for (int num : numbers) {
            System.out.println(num);
        }
        ```

    5. 분기문
        - 분기문은 반복문의 실행을 제어하는 데 사용됩니다.

        1. break 문:
            - 반복문이나 switch 문을 즉시 종료합니다.
            - 예시:
            ```Java
            for (int i = 0; i < 10; i++) {
                if (i == 5) {
                    break;
                }
                System.out.println(i);
            }
            ```

        2. continue 문:
            - 현재 반복을 건너뛰고 다음 반복으로 진행합니다.
            - 예시:
            ```Java
            for (int i = 0; i < 5; i++) {
                if (i == 2) {
                    continue;
                }
                System.out.println(i);
            }
            ```

        3. return 문:
            - 메서드의 실행을 종료하고 결과를 반환합니다.
            - 예시:
            ```Java
            public int sum(int a, int b) {
                return a + b;
            }
            ```
