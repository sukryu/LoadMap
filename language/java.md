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


### Java의 메서드 ###

Java에서 메서드는 특정 작업을 수행하는 코드 블록입니다. 메서드는 객체 지향 프로그래밍의 핵심 구성 요소로, 코드의 재사용성과 모듈화를 촉진합니다.

1. 메서드 정의
    - 메서드의 기본 구조는 다음과 같습니다.
    ```Java
    접근제어자 반환타입 메서드이름(매개변수목록) {
        // 메서드 본문
        return 반환값; // 반환 타입이 void가 아닌 경우
    }
    ```

    - 예시:
    ```Java
    public int add(int a, int b) {
        return a + b;
    }
    ```

2. 메서드 호출
    - 객체의 메서드를 호출하거나 static 메서드를 직접 호출할 수 있습니다.
    ```java
    ClassName objectName = new ClassName();
    int result = objectName.methodName(arguments);

    // static 메서드의 경우
    int result = ClassName.staticMethodName(arguments);
    ```

    - 예시:
    ```Java
    Caclurator calc = new Calculator();
    int sum = calc.add(5, 3);

    // static 메서드 호출
    int max = Math.max(10, 20);
    ```

3. 매개변수:
    - 메서드는 여러 개의 매개변수를 가질 수 있습니다.

    1. 기본 타입 매개변수:
        - 기본 데이터 타입은 값으로 전달됩니다. (pass by value).
        ```Java
        public void incrementNumber(int number) {
            number++;
        }

        int x = 5;
        incrementNumber(x);
        System.out.println(x); // 출력: 5 (x의 값은 변경되지 않음)
        ```

    2. 참조 타입 매개변수
        - 객체는 참조로 전달됩니다. (pass by reference).
        ```Java
        public void modifyList(List<Integer> numbers) {
            numbers.add(100);
        }

        List<Integer> myList = new ArrayList<>();
        myList.add(1);
        modifyList(myList);
        System.out.println(myList); // 출력: [1, 100]
        ```

    3. 가변 인자 (Varargs)
        - 메서드가 임의의 개수의 인자를 받을 수 있게 합니다.
        ```Java
        public int sum(int... numbers) {
            int total = 0;
            for (int num : numbers) {
                total += num;
            }
            return total;
        }

        int result = sum(1, 2, 3, 4, 5);
        ```

    4. 반환 값
        - 메서드는 작업 결과를 반환할 수 있습니다.
        ```Java
        public double calculatorArea(double radius) {
            return Math.PI * radius * radius;
        }

        double area = calculatorArea(5.0);
        ```

        - void 반환 타입은 메서드가 값을 반환하지 않음을 나타냅니다.
        ```Java
        public void printMessage(String message) {
            System.out.println(message);
        }
        ```

    5. 메서드 오버로딩
        - 같은 이름의 메서드를 여러 개 정의할 수 있습니다. 단, 매개변수의 타입이나 개수가 달라야 합니다.
        ```Java
        public int add(int a, int b) {
            return a + b;
        }

        public double add(double a, double b) {
            return a + b;
        }

        public int add(int a, int b, int c) {
            return a + b + c;
        }
        ```

    6. 재귀 메서드
        - 메서드가 자기 자신을 호출하는 것을 재귀라고 합니다.
        ```Java
        public int factorial(int n) {
            if (n == 0 || n == 1) {
                return 1;
            }
            return n * factorial(n - 1);
        }
        ```

    7. static 메서드
        - 클래스 레벨에서 호출할 수 있는 메서드입니다. 객체를 생성하지 않고도 사용할 수 있습니다.
        ```Java
        public class MathUtils {
            public static int square(int number) {
                return number * number;
            }
        }

        int result = MathUtils.square(5);
        ```

    8. 접근 제어자
        - 메서드의 가시성을 제어합니다.

        - `public`: 어디서든 접근 가능
        - `protected`: 같은 패키지 내에서, 그리고 다른 패키지의 자식 클래스에서 접근 가능.
        - `default`: (package-private): 같은 패키지 내에서만 접근 가능
        - `private`: 같은 클래스 내에서만 접근 가능.

        ```Java
        public class MyClass {
            public void publicMethod() { }
            protected void protectedMethod() { }
            void defaultMethod() { }
            private void privateMethod() { }
        }
        ```

### 배열과 컬렉션 ###

1. 배열 (Array):
    - 배열은 같은 타입의 여러 변수를 하나의 이름으로 그룹화하여 관리하는 자료구조입니다.

    1. 배열 선언과 초기화:
    ```Java
    // 선언만 하기
    int[] numbers;

    // 선언과 동시에 메모리 할당
    int[] numbers = new int[5];

    // 선언, 메모리 할당, 초기화를 동시에
    int[] numbers = {1, 2, 3, 4, 5};

    // 배열 크기 지정과 함께 초기화
    int[] numbers = new int[]{1, 2, 3, 4, 5};
    ```

    2. 배열의 특징:
        - 고정된 크기: 한번 생성된 배열의 크기는 변경할 수 없습니다.
        - 인덱스 기반 접근: 0부터 시작하는 인덱스를 사용하여 요소에 접근합니다.
        - 연속된 메모리 할당: 배열의 요소들은 메모리 상에 연속으로 저장됩니다.

    3. 다차원 배열:
        - Java는 다차원 배열을 지원합니다. 가장 일반적인 것은 2차원 배열입니다.
        ```Java
        int[][] matrix = new int[3][3];

        // 비정방형 배열도 가능합니다
        int[][] jaggedArray = new int[3][];
        jaggedArray[0] = new int[2];
        jaggedArray[1] = new int[3];
        jaggedArray[2] = new int[4];
        ```

    4. 배열 복사:
    ```Java
    // System.arraycopy 사용
    int[] source = {1, 2, 3, 4, 5};
    int[] destination = new int[5];
    System.arraycopy(source, 0, destination, 0, source.length);

    // Arrays.copyOf 사용
    int[] copy = Arrays.copyOf(source, source.length);
    ```

    5. 배열 정렬과 검색
    ```Java
    int[] numbers = {5, 2, 8, 1, 9};
    Arrays.sort(numbers);
    int index = Arrays.binarySearch(numbers, 8);
    ```

    6. 동적 크기 배열 생성
        - Java에서는 C언어와 달리 직접적인 동적 메모리 할당을 사용하지 않지만, 다음과 같은 방법으로 동적 크기의 배열을 다룰 수 있습니다.
        
        1. ArrayList 사용
        - ArrayList는 동적으로 크기가 조절되는 배열 기반의 리스트입니다.
        ```Java
        import java.util.ArrayList;
        import java.util.Scanner;

        public class DynamicArrayExample {
            public static void main(String[] args) {
                ArrayList<Integer> numbers = new ArrayList<>();
                Scanner scanner = new Scanner(System.in);

                System.out.println("숫자를 입력하세요. 입력을 마치려면 -1을 입력하세요:");

                while (true) {
                    int input = scanner.nextInt();
                    if (input == -1) break;
                    numbers.add(input);
                }

                System.out.println("입력받은 숫자들: " + numbers);
                System.out.println("개수: " + numbers.size());

                scanner.close();
            }
        }
        ```

        2. 배열 재할당:
            - 기본 배열을 사용하면서 필요에 따라 크기를 늘리는 방법입니다.
            ```Java
            import java.util.Arrays;
            import java.util.Scanner;

            public class DynamicArrayReallocation {
                public static void main(String[] args) {
                    int[] numbers = new int[5];  // 초기 크기 5로 시작
                    int size = 0;
                    Scanner scanner = new Scanner(System.in);

                    System.out.println("숫자를 입력하세요. 입력을 마치려면 -1을 입력하세요:");

                    while (true) {
                        int input = scanner.nextInt();
                        if (input == -1) break;

                        if (size == numbers.length) {
                            // 배열이 가득 찼을 때 크기를 2배로 늘림
                            numbers = Arrays.copyOf(numbers, numbers.length * 2);
                        }

                        numbers[size++] = input;
                    }

                    // 실제 사용된 크기로 배열을 조정
                    numbers = Arrays.copyOf(numbers, size);

                    System.out.println("입력받은 숫자들: " + Arrays.toString(numbers));
                    System.out.println("개수: " + numbers.length);

                    scanner.close();
                }
            }
            ```

    2. 컬렉션 프레임워크 (Collection Framework)
        - Java 컬렉션 프레임워크는 데이터를 저장하고 처리하는 다양한 클래스와 인터페이스를 제공합니다.

        1. List 인터페이스
            - List는 순서가 있는 데이터의 집합을 나타내며, 중복을 허용합니다.
            
            1. ArrayList:
                - 내부적으로 동적 배열을 사용하여 구현됩니다.
                ```Java
                List<String> list = new ArrayList<>();
                list.add("Apple");
                list.add("Banana");
                list.add(1, "Cherry"); // 인덱스 1에 삽입

                String fruit = list.get(1); // "Cherry" 반환
                list.remove(0); // "Apple" 제거
                boolean contains = list.contains("Banana"); // true
                ```

                - 특징:
                    - 요소의 추가/삭제: O(1) 평균, O(n) 최악
                    - 요소 접근: O(1)
                    - 메모리 사용: 연속된 메모리 공간 사용

            
            2. LinkedList
                - 이 중 연결 리스트로 구현됩니다.
                ```Java
                LinkedList<String> linkedList = new LinkedList<>();
                linkedList.addFirst("First");
                linkedList.addLast("Last");
                linkedList.add("Middle");

                String first = linkedList.getFirst();
                String last = linkedList.removeLast();
                ```

                - 특징:
                    - 요소의 추가/삭제: O(1)
                    - 요소 접근: O(n)
                    - 메모리 사용: 각 노드가 데이터와 포인터를 가짐.
        
        2. Set 인터페이스
            - Set은 중복을 허용하지 않는 데이터의 집합을 나타냅니다.

            1. HashSet
                - 해시 테이블을 사용하여 구현됩니다.
                ```Java
                Set<Integer> set = new HashSet<>();
                set.add(1);
                set.add(2);
                set.add(1); // 무시됨

                boolean contains = set.contains(2); // true
                set.remove(1);
                ```

                - 특징:
                    - 요소의 추가/삭제/검색: O(1) 평균
                    - 순서를 보장하지 않음.
            
            2. TreeSet
                - 이진 검색 트리 (Red-Black Tree)로 구현됩니다.
                ```Java
                TreeSet<String> treeSet = new TreeSet<>();
                treeSet.add("C");
                treeSet.add("A");
                treeSet.add("B");

                System.out.println(treeSet); // [A, B, C] 출력
                String first = treeSet.first(); // "A"
                String last = treeSet.last(); // "C"
                ```

                - 특징:
                    - 요소의 추가/삭제/검색: O(log n)
                    - 정렬된 순서 유지

            
            3. LinkedHashSet
                - HashSet과 LinkedList를 결합한 형태입니다.
                ```Java
                LinkedHashSet<String> linkedHashSet = new LinkedHashSet<>();
                linkedHashSet.add("B");
                linkedHashSet.add("A");
                linkedHashSet.add("C");

                System.out.println(linkedHashSet); // [B, A, C] 출력 (삽입 순서 유지)
                ```

                - 특징:
                    - 요소의 추가/삭제/검색: O(1)
                    - 삽입 순서 유지
                
            
        3. Map 인터페이스
            - Map은 키-값 쌍으로 이루어진 데이터의 집합을 나타냅니다.

            1. HashMap:
            ```Java
            Map<String, Integer> map = new HashMap<>();
            map.put("One", 1);
            map.put("Two", 2);

            int value = map.get("One"); // 1
            map.remove("Two");

            for (Map.Entry<String, Integer> entry : map.entrySet()) {
                System.out.println(entry.getKey() + ": " + entry.getValue());
            }
            ```
            - 특징:
                - 키와 값 쌍의 추가/삭제/검색: O(1) 평균
                - 순서를 보장하지 않음.
            

            2. TreeMap
            ```Java
            TreeMap<String, Integer> treeMap = new TreeMap<>();
            treeMap.put("C", 3);
            treeMap.put("A", 1);
            treeMap.put("B", 2);

            System.out.println(treeMap); // {A=1, B=2, C=3} 출력
            String firstKey = treeMap.firstKey(); // "A"
            Map.Entry<String, Integer> lastEntry = treeMap.lastEntry(); // "C"=3
            ```

            - 특징:
                - 키와 값 쌍의 추가/삭제/검색: O(log n)
                - 키를 기준으로 정렬된 순서 유지
            

            3. LinkedHashMap
                - 삽입 순서 또는 접근 순서를 유지하는 HashMap입니다.
                ```Java
                LinkedHashMap<String, Integer> linkedHashMap = new LinkedHashMap<>(16, 0.75f, true);
                linkedHashMap.put("A", 1);
                linkedHashMap.put("B", 2);
                linkedHashMap.put("C", 3);

                linkedHashMap.get("A"); // "A"를 맨 뒤로 이동

                System.out.println(linkedHashMap); // {B=2, C=3, A=1} 출력
                ```

                - 특징:
                    - 요소의 추가/삭제/검색: O(1)
                    - 삽입 순서 또는 접근 순서 유지 가능.

        4. Queue 인터페이스
            - Queue는 선입선출(FIFO) 구조의 데이터 집합을 나타냅니다.

            1. LinkedList(Queue로 사용)
            ```Java
            Queue<String> queue = new LinkedList<>();
            queue.offer("First");
            queue.offer("Second");

            String first = queue.poll(); // "First" 반환 및 제거
            String peek = queue.peek(); // "Second" 반환 (제거하지 않음)
            ```

            2. PriorityQueue
                - 요소의 우선순위에 따라 정렬되는 큐입니다.
                ```Java
                PriorityQueue<Integer> pq = new PriorityQueue<>();
                pq.offer(3);
                pq.offer(1);
                pq.offer(2);

                System.out.println(pq.poll()); // 1 출력
                System.out.println(pq.poll()); // 2 출력
                ```

        5. Deque 인터페이스
            - Deque(Double Enabled Queue)는 양쪽 끝에서 삽입과 삭제가 가능한 자료구조입니다.
            ```Java
            Deque<String> deque = new ArrayDeque<>();
            deque.addFirst("First");
            deque.addLast("Last");

            String first = deque.removeFirst();
            String last = deque.removeLast();
            ```

        6. Collections 유틸리티 클래스
            - `Collections`클래스는 컬렉션을 다루는 유용한 정적 메서드들을 제공합니다.
            ```Java
            List<Integer> list = new ArrayList<>(Arrays.asList(3, 1, 4, 1, 5, 9));

            Collections.sort(list); // 정렬
            Collections.reverse(list); // 역순으로 변경
            int max = Collections.max(list); // 최대값
            int frequency = Collections.frequency(list, 1); // 1의 출현 빈도

            List<Integer> synchronizedList = Collections.synchronizedList(list); // 동기화된 리스트 생성
            List<Integer> unmodifiableList = Collections.unmodifiableList(list); // 수정 불가능한 리스트 생성
            ```


### Java의 객제지향 프로그래밍 ###

1. 클래스와 객체:
    1. 클래스:
        - 클래스는 객체의 속성(필드)과 행동(메서드)을 정의하는 템플릿입니다.
        ```Java
        public class Car {
            // 인스턴스 변수 (객체의 속성)
            private String model;
            private int year;
            private double speed;

            // 클래스 변수 (모든 Car 객체가 공유)
            private static int totalCars = 0;

            // 생성자
            public Car(String model, int year) {
                this.model = model;
                this.year = year;
                this.speed = 0;
                totalCars++;
            }

            // 인스턴스 메서드
            public void accelerate(double amount) {
                speed += amount;
                System.out.println(model + " is accelerating. Current speed: " + speed);
            }

            // 정적 메서드
            public static int getTotalCars() {
                return totalCars;
            }

            // Getter와 Setter 메서드
            public String getModel() { return model; }
            public void setModel(String model) { this.model = model; }
            public int getYear() { return year; }
            public void setYear(int year) { this.year = year; }
        }
        ```
    2. 객체:
        - 객체는 클래스의 인스턴스입니다. 각 객체는 고유한 속성 값을 가집니다.
        ```Java
        Car myCar = new Car("Tesla Model 3", 2023);
        Car yourCar = new Car("Toyota Camry", 2022);

        myCar.accelerate(10);
        yourCar.accelerate(5);

        System.out.println("Total cars created: " + Car.getTotalCars());
        ```

2. 캡슐화:
    - 캡슐화는 데이터(필드)와 그 데이터를 처리하는 메서드를 하나로 묶고, 데이터에 대한 직접 접근을 제한하는 것입니다.
    ```Java
    public class BankAccount {
        private double balance;
        private String accountNumber;

        public BankAccount(String accountNumber, double initialBalance) {
            this.accountNumber = accountNumber;
            if (initialBalance > 0) {
                this.balance = initialBalance;
            }
        }

        public void deposit(double amount) {
            if (amount > 0) {
                balance += amount;
                System.out.println("Deposited: " + amount);
            } else {
                System.out.println("Invalid deposit amount");
            }
        }

        public void withdraw(double amount) {
            if (amount > 0 && balance >= amount) {
                balance -= amount;
                System.out.println("Withdrawn: " + amount);
            } else {
                System.out.println("Invalid withdrawal amount or insufficient funds");
            }
        }

        public double getBalance() {
            return balance;
        }

        // accountNumber는 setter를 제공하지 않아 변경 불가능
        public String getAccountNumber() {
            return accountNumber;
        }
    }
    ```

    - 캡슐화의 이점:
        1. 데이터 은닉: 객체의 내부 상태를 외부로부터 보호합니다.
        2. 유연성: 내부 구현을 변경해도 외부 코드에 영향을 주지 않습니다.
        3. 유효성 검사: setter 메서드에서 데이터의 유효성을 검사할 수 있습니다.

    
3. 상속:
    - 상속은 기존 클래스(부모 클래스)의 속성과 메서드를 새로운 클래스(자식 클래스)가 재사용할 수 있게 해줍니다.
    ```Java
    public class Vehicle {
        protected String brand;
        protected int year;

        public Vehicle(String brand, int year) {
            this.brand = brand;
            this.year = year;
        }

        public void start() {
            System.out.println("The vehicle is starting");
        }

        public void stop() {
            System.out.println("The vehicle is stopping");
        }
    }

    public class Car extends Vehicle {
        private int numberOfDoors;

        public Car(String brand, int year, int numberOfDoors) {
            super(brand, year);  // 부모 클래스의 생성자 호출
            this.numberOfDoors = numberOfDoors;
        }

        @Override
        public void start() {
            System.out.println("The car is starting its engine");
        }

        public void honk() {
            System.out.println("Beep beep!");
        }
    }

    public class Bicycle extends Vehicle {
        private int numberOfGears;

        public Bicycle(String brand, int year, int numberOfGears) {
            super(brand, year);
            this.numberOfGears = numberOfGears;
        }

        @Override
        public void start() {
            System.out.println("The bicycle is ready to ride");
        }

        public void pedal() {
            System.out.println("Pedaling the bicycle");
        }
    }
    ```

    - 상속의 이점:
        1. 코드 재사용: 공통 기능을 부모 클래스에 정의하여 중복을 줄입니다.
        2. 확장성: 기존 클래스를 수정하지 않고 새로운 기능을 추가할 수 있습니다.
        3. 다형성: 부모 타입의 참조 변수로 자식 객체를 다룰 수 있습니다.

4. 다형성
    - 다형성은 같은 타입이지만 실행 결과가 다양한 객체를 이용할 수 있는 성질을 말합니다.
    ```Java
    Vehicle vehicle1 = new Car("Toyota", 2023, 4);
    Vehicle vehicle2 = new Bicycle("Trek", 2022, 21);

    vehicle1.start();  // "The car is starting its engine"
    vehicle2.start();  // "The bicycle is ready to ride"

    // 다운캐스팅
    if (vehicle1 instanceof Car) {
        Car car = (Car) vehicle1;
        car.honk();  // "Beep beep!"
    }

    if (vehicle2 instanceof Bicycle) {
        Bicycle bicycle = (Bicycle) vehicle2;
        bicycle.pedal();  // "Pedaling the bicycle"
    }
    ```

    - 다형성의 이점:
        1. 유연성: 코드를 더 유연하게 만들어 재사용성을 높입니다.
        2. 확장성: 새로운 클래스를 추가하기 쉽습니다.
        3. 유지보수성: 코드 변경의 영향을 최소화합니다.

5. 추상화:
    - 추상화는 공통적인 속성과 기능을 추출하여 정의하는 것을 말합니다.
    ```Java
    public abstract class Shape {
        protected String color;

        public Shape(String color) {
            this.color = color;
        }

        // 추상 메서드 - 하위 클래스에서 반드시 구현해야 함
        public abstract double calculateArea();

        // 일반 메서드
        public void displayColor() {
            System.out.println("This shape is " + color);
        }
    }

    public class Circle extends Shape {
        private double radius;

        public Circle(String color, double radius) {
            super(color);
            this.radius = radius;
        }

        @Override
        public double calculateArea() {
            return Math.PI * radius * radius;
        }
    }

    public class Rectangle extends Shape {
        private double width;
        private double height;

        public Rectangle(String color, double width, double height) {
            super(color);
            this.width = width;
            this.height = height;
        }

        @Override
        public double calculateArea() {
            return width * height;
        }
    }
    ```

    - 추상화의 이점:
        1. 코드 재사용: 공통 기능을 추상 클래스에 정의하여 중복을 줄입니다.
        2. 강제 구현: 추상 메서드를 통해 하위 클래스가 특정 기능을 반드시 구현하도록 강제할 수 있습니다.
        3. 설계의 유연성: 구체적인 구현을 하위 클래스에 위임하여 다양한 구현이 가능합니다.

6. 인터페이스:
    - 인터페이스는 메서드의 시그니처만을 정의하고, 구현은 이를 구현하는 클래스에 맡깁니다.
    ```Java
    public interface Flyable {
        void takeOff();
        void fly();
        void land();
    }

    public interface Swimmable {
        void swim();
        void dive();
    }

    public class Bird implements Flyable {
        @Override
        public void takeOff() {
            System.out.println("Bird is taking off");
        }

        @Override
        public void fly() {
            System.out.println("Bird is flying");
        }

        @Override
        public void land() {
            System.out.println("Bird is landing");
        }
    }

    public class Duck implements Flyable, Swimmable {
        @Override
        public void takeOff() {
            System.out.println("Duck is taking off from water");
        }

        @Override
        public void fly() {
            System.out.println("Duck is flying");
        }

        @Override
        public void land() {
            System.out.println("Duck is landing on water");
        }

        @Override
        public void swim() {
            System.out.println("Duck is swimming");
        }

        @Override
        public void dive() {
            System.out.println("Duck is diving");
        }
    }
    ```

    - 인터페이스의 이점:
        1. 다중 구현: 클래스는 여러 인터페이스를 구현할 수 있어 유연성이 높습니다.
        2. 계약 정의: 인터페이스는 클래스가 구현해야 할 메서드를 정의합니다.
        3. 노슨한 결합: 인터페이스를 통해 객체 간의 관계를 정의하면 구현체의 교체가 용이합니다.

7. 패키지:
    - 패키지는 관련된 클래스와 인터페이스를 그룹화하는 메커니즘입니다.
    
    1. 패키지 생성 및 사용
    ```Java
    // 파일: com/example/myapp/MyClass.java
    package com.example.myapp;

    public class MyClass {
        // 클래스 내용
    }

    // 다른 파일에서 사용
    import com.example.myapp.MyClass;
    // 또는
    import com.example.myapp.*;
    ```

    2. 패키지의 이점:
        1. 이름 충돌 방지: 동일한 이름의 클래스를 다른 패키지에 둘 수 있습니다.
        2. 코드 구조화: 관련된 클래스들을 논리적으로 그룹화합니다.
        3. 접근 제어: 패키지 레벨의 접근 제어를 제공합니다.

    3. Built-in 패키지
        - Java는 많은 built-in 패키지를 제공합니다.

        - `java.lang`: 기본 클래스들(자동으로 import됨)
        - `java.util`: 유틸리티 클래스들 (Collections 등)
        - `java.io`: 입출력 관련 클래스들

8. 접근 제어자 (Access Modifiers)
    - 접근 제어자는 클래스, 변수, 메서드, 생성자의 접근 범위를 제어합니다.

    1. 종류와 범위
        - `public`: 어디서든 접근 가능
        - `protected`: 같은 패키지 내에서, 그리고 다른 패키지의 자식 클래스에서 접근 가능
        - `default`: (package-private): 같은 패키지 내에서만 접근 가능
        - `private`: 같은 클래스 내에서만 접근 가능

    2. 사용 예시:
    ```Java
    public class AccessExample {
        public int publicVar;
        protected int protectedVar;
        int defaultVar;
        private int privateVar;

        public void publicMethod() { }
        protected void protectedMethod() { }
        void defaultMethod() { }
        private void privateMethod() { }
    }
    ```

    3. 접근 제어자의 중요성
        1. 캡슐화 강화: 내부 구현을 숨기고 필요한 부 분만 노출
        2. 유지보수성 향상: 외부에서의 직접적인 데이터 조작 방지
        3. 유연성 증가: 내부 구현을 변경해도 외부 코드에 영향을 주지 않음.

9. static 키워드
    - `static` 키워드는 클래스 레벨의 멤버를 정의합니다. 이는 객체 생성 없이 사용할 수 있는 멤버를 만듭니다.

    1. static 변수
    ```Java
    public class Counter {
        private static int count = 0;

        public Counter() {
            count++;
        }

        public static int getCount() {
            return count;
        }
    }

    // 사용
    System.out.println(Counter.getCount()); // 0
    Counter c1 = new Counter();
    Counter c2 = new Counter();
    System.out.println(Counter.getCount()); // 2
    ```

    2. static 메서드
    ```Java
    public class MathUtils {
        public static int add(int a, int b) {
            return a + b;
        }
    }

    // 사용
    int sum = MathUtils.add(5, 3);
    ```

    3. static 블록:
        - 클래스가 로드될 때 한 번만 실행되는 초기화 블록입니다.
        ```Java
        public class StaticBlockExample {
            static {
                System.out.println("This is a static initialization block.");
            }
        }
        ```

    4. static import
        - static 멤버를 직접 참소할 수 있게 해줍니다.
        ```Java
        import static java.lang.Math.PI;
        import static java.lang.Math.sqrt;

        public class StaticImportExample {
            public void printCircleArea(double radius) {
                System.out.println(PI * radius * radius);
            }

            public double calculateHypotenuse(double a, double b) {
                return sqrt(a*a + b*b);
            }
        }
        ```

10. final 키워드:
    - `fianl`키워드는 엔티티를 "변경할 수 없게" 만듭니다.

    1. final 변수:
        - 값을 한 번만 할당할 수 있는 상수를 만듭니다.
        ```Java
        public class FinalVariableExample {
            private final int CONSTANT = 100;
            private final String NAME;

            public FinalVariableExample(String name) {
                this.NAME = name;  // 생성자에서 초기화
            }
        }
        ```

    2. final 메서드
        - 오버라이딩을 금지합니다.
        ```Java
        public class Parent {
            public final void cannotOverride() {
                System.out.println("This method cannot be overridden");
            }
        }

        public class Child extends Parent {
            // 컴파일 에러: Cannot override the final method from Parent
            // public void cannotOverride() { }
        }
        ```

    3. final 클래스
        - 상속을 금지합니다.
        ```Java
        public final class FinalClass {
            // 이 클래스는 상속될 수 없습니다.
        }

        // 컴파일 에러: Cannot inherit from final FinalClass
        // public class SubClass extends FinalClass { }
        ```

    4. final의 이점:
        1. 불변성 보장: 데이터의 무결성을 유지
        2. 스레드 안정성: 멀티스레드 환경에서 안전하게 공유 가능
        3. 성능 최적화: 컴파일러가 final 키워드를 활용하여 최적화 수행

11. 고급 개념:
    1. 제네릭 (Generics)
        - 제네릭은 클래스나 메서드에서 사용할 데이터 타입을 컴파일 시에 미리 지정하는 방법입니다.
        ```Java
        public class Box<T> {
            private T content;

            public void set(T content) {
                this.content = content;
            }

            public T get() {
                return content;
            }
        }

        Box<Integer> integerBox = new Box<>();
        integerBox.set(10);
        Integer content = integerBox.get();
        ```

    2. 람다 표현식 (Lambda Expressions)
        - 람다 표현식은 함수형 프로그래밍을 지원하기 위해 Java 8에서 도입되었습니다.
        ```Java
        List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5);

        // 람다를 사용한 필터링
        List<Integer> evenNumbers = numbers.stream()
                                        .filter(n -> n % 2 == 0)
                                        .collect(Collectors.toList());
        ```

    3. 스트림 API (Stream API)
        - 스트림 API는 컬렉션을 함수형으로 처리할 수 있게 해줍니다.
        ```Java
        List<String> names = Arrays.asList("Alice", "Bob", "Charlie", "David");

        List<String> filteredNames = names.stream()
                                        .filter(name -> name.startsWith("A"))
                                        .map(String::toUpperCase)
                                        .collect(Collectors.toList());
        ```

    4. Optional 클래스
        - Optional 클래스는 null 처리를 보다 우아하게 할 수 있게 해줍니다.
        ```Java
        Optional<String> optionalName = Optional.ofNullable(getName());
        String name = optionalName.orElse("Unknown");
        ```

### 패키지와 모듈 ###

1. 패키지 (Packages): 
    - 패키지는 관련된 클래스와 인터페이스를 그룹화하는 메커니즘입니다.

    1. 패키지의 목적:
        1. 이름 충돌 방지
        2. 관련 클래스들의 논리적 그룹화
        3. 접근 제어 제공
    
    2. 패키지 선언:
    ```Java
    package com.example.myapp;

    public class MyClass {
        // 클래스 내용
    }
    ```

    3. 패키지 사용:
    ```Java
    import com.example.myapp.MyClass;
    // 또는
    import com.example.myapp.*;

    public class Main {
        public static void main(String[] args) {
            MyClass obj = new MyClass();
        }
    }
    ```

    4. 패키지 구조:
    ```bash
    src/
    com/
        example/
            myapp/
                MyClass.java
                AnotherClass.java
    ```

    5. 주요 Java 패키지
        - `java.lang`: 기본 클래스 (String, Math 등)
        - `java.util`: 유틸리티 클래스 (Colletions, Scanner 등)
        - `java.io`: 입출력 관련 클래스
        - `java.net`: 네트워킹 관련 클래스

2. 모듈 시스템 (Module System)
    - Java 9에서 도입된 모듈 시스템은 대규모 애플리케이션의 구조화와 캡슐화를 개선합니다.

    1. 모듈의 목적:
        1. 강력한 캡슐화
        2. 명시적 의존성 선언
        3. 신뢰할 수 있는 구성
        4. 향상된 성능

    2. module-info.java
        - 모듈은 `module-info.java` 파일로 정의됩니다.
        ```Java
        module com.example.mymodule {
            requires java.base;  // 기본적으로 포함됨
            requires java.sql;

            exports com.example.mymodule.api;
            
            provides com.example.mymodule.spi.MyService 
                with com.example.mymodule.internal.MyServiceImpl;
        }
        ```

    3. 주요 모듈 지시어
        - `requires`: 의존하는 모듈 지정
        - `exports`: 다른 모듈에서 사용할 수 있는 패키지 지정
        - `opens`: 리플렉션을 통해 접근 가능한 패키지 지정
        - `provides ... with ...`: 서비스 제공
        - `uses`: 사용할 서비스지정


    4. 모듈 사용 예시
    ```Java
    // Module A (module-info.java)
    module moduleA {
        exports com.example.moduleA;
    }

    // Module B (module-info.java)
    module moduleB {
        requires moduleA;
    }

    // Module B (SomeClass.java)
    package com.example.moduleB;

    import com.example.moduleA.SomeApiClass;

    public class SomeClass {
        public void doSomething() {
            SomeApiClass api = new SomeApiClass();
            // Use the API
        }
    }
    ```

    5. 모듈 명령어
        - `java --list-modules`: 사용 가능한 모듈 나열
        - `java --discribe-module <moduel-name>`: 모듈 설명 보기
        - `jdeps`: 모듈 종속성 분석 도구

3. 패키지와 모듈의 차이점
    1. 범위:
        - 패키지: 관련 클래스의 논리적 그룹
        - 모듈: 관련 패키지의 더 큰 그룹

    2. 캡슐화:
        - 패키지: 패키지 수준의 접근 제어
        - 모듈: 모듈 수준의 강력한 캡슐화

    3. 의존성:
        - 패키지: 암시적 의존성
        - 모듈: 명시적 의존성 선언

    4. 버전:
        - 패키지: Java 1.0부터 존재
        - 모듈: Java 9에서 도입

4. 모범사례
    1. 의미 있는 패키지 이름 사용 (예: `com.company.project.feature`)
    2. 패키지 내 관련 클래스만 포함
    3. 순환 종속성 피하기
    4. 필요한 경우에만 패키지를 `exports`
    5. 모듈 간 느슨한 결합 유지

### 파일 처리 ###

Java는 파일 및 입출력(I/O) 작업을 위한 다양한 클래스와 메서드를 제공합니다. 이를 통해 파일 읽기, 쓰기, 생성, 삭제 등의 작업을 수행할 수 있습니다.

1. 기본 파일 처리
    1. File 클래스:
        - `File`클래스는 파일 시스템의 파일이나 디렉토리를 표현합니다.
        ```Java
        import java.io.File;

        File file = new File("example.txt");
        boolean exists = file.exists();
        long length = file.length();
        boolean isDirectory = file.isDirectory();
        String[] fileList = file.list();  // 디렉토리인 경우
        ```

    2. 파일 생성 및 삭제:
    ```Java
    File newFile = new File("newFile.txt");
    boolean created = newFile.createNewFile();
    boolean deleted = newFile.delete();
    ```

2. 텍스트 파일 읽기와 쓰기

    1. FileReader와 FileWriter
    ```Java
    // 파일 읽기
    try (FileReader reader = new FileReader("input.txt");
        BufferedReader bufferedReader = new BufferedReader(reader)) {
        String line;
        while ((line = bufferedReader.readLine()) != null) {
            System.out.println(line);
        }
    } catch (IOException e) {
        e.printStackTrace();
    }

    // 파일 쓰기
    try (FileWriter writer = new FileWriter("output.txt");
        BufferedWriter bufferedWriter = new BufferedWriter(writer)) {
        bufferedWriter.write("Hello, World!");
        bufferedWriter.newLine();
        bufferedWriter.write("This is a new line.");
    } catch (IOException e) {
        e.printStackTrace();
    }
    ```

    2. Scanner 클래스 사용
    ```Java
    try (Scanner scanner = new Scanner(new File("input.txt"))) {
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            System.out.println(line);
        }
    } catch (FileNotFoundException e) {
        e.printStackTrace();
    }
    ```

3. 바이너리 파일 처리

    1. FileInputStream과 FileOutputStream
    ```Java
    // 파일 읽기
    try (FileInputStream fis = new FileInputStream("input.bin");
        BufferedInputStream bis = new BufferedInputStream(fis)) {
        int data;
        while ((data = bis.read()) != -1) {
            System.out.print((char) data);
        }
    } catch (IOException e) {
        e.printStackTrace();
    }

    // 파일 쓰기
    try (FileOutputStream fos = new FileOutputStream("output.bin");
        BufferedOutputStream bos = new BufferedOutputStream(fos)) {
        byte[] data = {65, 66, 67, 68, 69}; // ABCDE
        bos.write(data);
    } catch (IOException e) {
        e.printStackTrace();
    }
    ```

4. NIO (New I/O)
    - Java NIO는 더 효율적인 I/O 작업을 위해 도입되었습니다.

    1. Files 클래스
    ```Java
    import java.nio.file.*;

    // 파일 읽기
    List<String> lines = Files.readAllLines(Paths.get("input.txt"));

    // 파일 쓰기
    Files.write(Paths.get("output.txt"), lines);

    // 파일 복사
    Files.copy(Paths.get("source.txt"), Paths.get("destination.txt"), StandardCopyOption.REPLACE_EXISTING);

    // 파일 이동
    Files.move(Paths.get("old.txt"), Paths.get("new.txt"), StandardCopyOption.REPLACE_EXISTING);
    ```

    2. Channel과 Buffer
    ```Java
    try (FileChannel channel = FileChannel.open(Paths.get("file.txt"), StandardOpenOption.READ)) {
        ByteBuffer buffer = ByteBuffer.allocate(1024);
        int bytesRead = channel.read(buffer);
        while (bytesRead != -1) {
            buffer.flip();
            while (buffer.hasRemaining()) {
                System.out.print((char) buffer.get());
            }
            buffer.clear();
            bytesRead = channel.read(buffer);
        }
    } catch (IOException e) {
        e.printStackTrace();
    }
    ```

5. 직렬화 (Serialization)
    - 객체를 파일에 저장하거나 네트워크로 전송할 수 있게 해줍니다.
    ```Java
    import java.io.*;

    class Person implements Serializable {
        private String name;
        private int age;

        // 생성자, getter, setter 생략
    }

    // 객체 직렬화
    try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream("person.ser"))) {
        Person person = new Person("John Doe", 30);
        oos.writeObject(person);
    } catch (IOException e) {
        e.printStackTrace();
    }

    // 객체 역직렬화
    try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream("person.ser"))) {
        Person person = (Person) ois.readObject();
        System.out.println(person.getName() + ", " + person.getAge());
    } catch (IOException | ClassNotFoundException e) {
        e.printStackTrace();
    }
    ```

6. 파일 및 디렉토리 관리

    1. 디렉토리 생성
    ```Java
    Files.createDirectory(Paths.get("newDir"));
    Files.createDirectories(Paths.get("path/to/newDir"));
    ```

    2. 파일 목록 가져오기
    ```Java
    try (DirectoryStream<Path> stream = Files.newDirectoryStream(Paths.get("."))) {
        for (Path file : stream) {
            System.out.println(file.getFileName());
        }
    } catch (IOException e) {
        e.printStackTrace();
    }
    ```

    3. 파일 속성 관리
    ```Java
    Path file = Paths.get("example.txt");
    System.out.println("Size: " + Files.size(file));
    System.out.println("Last Modified: " + Files.getLastModifiedTime(file));
    System.out.println("Is Hidden: " + Files.isHidden(file));
    ```

7. 파일 감시 (File Watching)
```Java
WatchService watchService = FileSystems.getDefault().newWatchService();
Path path = Paths.get(".");
path.register(watchService, StandardWatchEventKinds.ENTRY_CREATE, 
              StandardWatchEventKinds.ENTRY_DELETE, StandardWatchEventKinds.ENTRY_MODIFY);

while (true) {
    WatchKey key = watchService.take();
    for (WatchEvent<?> event : key.pollEvents()) {
        System.out.println("Event kind: " + event.kind() + ". File affected: " + event.context() + ".");
    }
    key.reset();
}
```