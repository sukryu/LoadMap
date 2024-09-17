# JavaScript 프로그래밍 언어 #

## JavaScript란 ? ##

JavaScript는 웹 개발에서 필수적인 동적이고 다목적인 프로그래밍 언어입니다.
1995년 Netscape의 Brendan Eich에 의해 개발되었으며, 현재는 클라이언트 측 웹 개발뿐만 아니라 서버 측 개발,
모바일 앱 개발, 테스트콥 애플리케이션 개발 등 다양한 분야에서 사용되고 있습니다.

- 주요 특징:
    1. 동적 타이핑: 변수의 타입을 명시적으로 선언할 필요가 없습니다.
    2. 객체 지향: 프로토타입 기반의 객체 지향 프로그래밍을 지원합니다.
    3. 함수형 프로그래밍: 일급 함수를 지원하여 함수형 프로그래밍 패러다임을 따를 수 있습니다.
    4. 이벤트 기반: 사용자 상호작용 및 기타 이벤트에 반응하는 프로그래밍 모델을 제공합니다.
    5. 인터프리터 언어: 컴파일 과정 없이 실행 시점에 코드를 해석합니다.
    6. 크로스 플랫폼: 다양한 플랫폼과 환경에서 실행될 수 있습니다.

- JavaScript의 발전:

    - 1997년: ECMA 국제 표준화 기구에 의해 ECMAScript라는 이름으로 표준화
    - 2009년: ECMAScript 5 (ES5) 발표, 엄격 모드 등 새로운 기능 추가
    - 2015년: ECMAScript 2015 (ES6) 발표, 클래스, 모듈, 화살표 함수 등 다수의 새로운 기능 도입
    - 이후 매년 새로운 버전이 발표되며 지속적으로 발전 중

- 사용분야:
    1. 웹 프론트엔드 개발
    2. 서버 사이트 개발(Node.js)
    3. 모바일 앱 개발(React Native, Ionic)
    4. 데스크톱 앱 개발 (Electron)
    5. 게임 개발 (Phaser, Three.js)
    6. 머신 러닝 및 데이터 분석 (TensorFlow.js)

## JavaScript의 동작 방식 ##

JavaScript는 주로 웹 브라우저에서 실행되지만, Node.js와 같은 런타임 환경에서도 실행될 수 있습니다.
여기서는 브라우저에서의 JavaScript 실행 과정을 중심으로 설명하겠습니다.

1. 로딩: HTML 파서가 `<script>` 태그를 만나면 JavaScript 코드를 로드합니다.
    ```html
    <script src="example.js"></script>
    ```

2. 파싱: JavaScript 엔진이 코드를 파싱하여 AST(Abstract Syntax Tree)를 생성합니다.
3. 컴파일: AST가 바이트코드로 컴파일됩니다. 최신 JavaScript 엔진은 JIT(Just-In-Time)컴파일러를 사용하여 실행 시점에
네이티브 코드로 컴파일하기도 합니다.
4. 실행: 컴파일된 코드가 JavaScript 엔진에 의해 실행됩니다.

- JavaScript 엔진:
    1. V8 (Chrome, Node.js)
    2. SpiderMonkey (Firefox)
    3. JavaScriptCore (Safari)
    4. Chakra (Internet Explorer, Mikrosoft Edge (레거시))

- 실행 컨텍스트:
    - JavaScript 코드가 실행될 때 생성되는 환경입니다. 주요 구성 요소는 다음과 같습니다.

    1. 변수 환경: let과 const로 선언된 변수
    2. 렉시컬 환경: var로 선언된 변수와 함수 선언
    3. this 바인딩

    - 예시:

    ```javascript
    function exampleFunction() {
        var a = 1;
        let b = 2;
        const c = 3;
        
        function innerFunction() {
            console.log(a, b, c);
        }
        
        innerFunction();
    }

    exampleFunction();
    ```

    - 이 코드가 실행될 때 다음과 같은 컨텍스트가 생성됩니다.:

    1. 전역 실행 컨텍스트
    2. exampleFunction 실행 컨텍스트
    3. innerFunction 실행 컨텍스트

    - 각 컨텍스트는 자신만의 변수 환경과 렉시컬 환경을 가지며, 외부 환경에 대한 참조를 통해 스코프 체인을 형성합니다.

    - 이벤트 루프:
        - JavaScript는 단일 스레드 언어이지만, 비동기 작업을 처리하기 위해 이벤트 루프를 사용합니다.

        1. 콜 스택: 현재 실행 중인 작업을 추적합니다.
        2. 태스크 큐: 비동기 콜백 함수가 대기합니다.
        3. 마이크로태스크 큐: Promise의 콜백과 같은 높은 우선순위 태스트가 대기합니다.

    - 작동 방식:
        1. 동기 코드가 콜 스택에서 실행됩니다.
        2. 비동기 작업은 Web API로 넘겨지고, 완료 후 콜백이 태스크 큐에 추가됩니다.
        3. 콜 스택이 비면 이벤트 루프가 태스트 큐에서 다음 작업을 가져와 실행합니다.

    - 예시:
    ```javascript
    console.log('시작');

    setTimeout(() => {
        console.log('타임아웃');
    }, 0);

    Promise.resolve().then(() => {
        console.log('프로미스');
    });

    console.log('끝');
    ```

    - 실행결과:

    ```bash
    시작
    끝
    프로미스
    타임아웃
    ```

    - 이 예시에서 `setTimeout`의 콜백은 태스크 큐로, `Promise`의 콜백은 마이크로태스크 큐로 이동합니다.
    마이크로태스크가 항상 일반 태스크보다 먼저 처리되기 때문에 위와 같은 순서로 출력됩니다.

## JavaScript의 주요 기능과 개념 ##

### 변수와 데이터 타입 ###

JavaScript에서 변수는 값을 저장하는 컨테이너입니다. ES6 이후로 변수를 선언하는 세 가지 키워드(var, let, const)가 있으며, 각각 다른 특성을 가집니다.

1. 변수 선언:
    1. var:
        - 함수 스코프 또는 전역 스코프
        - 호이스팅 됨
        - 재선언 가능

        ```javascript
        var x = 5;
        var x = 10; // 재선언 가능
        ```

    2. let:
        - 블록 스코프
        - 호이스팅 되지만 TDZ(Temporal Daed Zone) 존재
        - 재선언 불가능

        ```javascript
        let y = 5;
        // let y = 10; // Error: 재선언 불가능
        y = 10; // 재할당 가능
        ``
        
    3. const:
        - 블록 스코프
        - 호이스팅 되지만 TDZ 존재
        - 재선언 및 재할당 불가능

        ```javascript
        const z = 5;
        // z = 10; // Error: 재할당 불가능
        ```

        - 주의: const로 선언된 객체의 속성은 변경 가능합니다.
        ```javascript
        const obj = { prop: 5 }
        obj.prop = 10; // 가능
        // obj = {}; // Error: 객체 자체 재할당 불가능
        ```

2. 데이터 타입: 
    - JavaScript는 동적 타입 언어로, 변수의 타입이 런타임에 결정됩니다.

    1. 원시 타입 (Primitive Types):

        1. Number: 정수와 실수를 모두 표현
        ```javascript
        let num1 = 5;
        let num2 = 3.14;
        ```

        2. String: 택스트 데이터
        ```javascript
        let str1 = "Hello";
        let str2 = "World";
        let str3 = `Template literal: ${str1}`;
        ```

        3. Boolean: true or false
        ```javascript
        let isTrue = true;
        let isFalse = false;
        ```

        4. Undefined: 값이 할당되지 않은 상태
        ```javascript
        let undefinedVar;
        console.log(undefinedVar); // undefined
        ```

        5. Null: 의도적으로 빈 값을 나타냄.
        ```javascript
        let nulVar = null;
        ```

        6. Symbol(ES6): 유일하고 변경 불가능한 원시 값
        ```javascript
        const sym1 = Symbol('description');
        const sym2 = Symbol('description');
        console.log(sym1 === sym2); // false
        ```

    2. 객체 타입 (Object Type):
        1. Object: 키 - 값 쌍의 집합
        ```javascript
        let person = {
        name: "John",
        age: 30,
        isStudent: false
        };
        ```

        2. Array: 순서가 있는 요소의 집합
        ```javascript
        let fruits = ["apple", "banana", "orange"];
        ```

        3. Function: 실행 가능한 코드 블록
        ```javascript
        function greet(name) {
        return `Hello, ${name}!`;
        }
        ```

3. 타입 확인: typeof 연산자를 사용하여 변수의 타입을 확인할 수 있습니다.
```javascript
console.log(typeof 5); // "number"
console.log(typeof "Hello"); // "string"
console.log(typeof true); // "boolean"
console.log(typeof undefined); // "undefined"
console.log(typeof null); // "object" (JavaScript의 오래된 버그)
console.log(typeof {}); // "object"
console.log(typeof []); // "object"
console.log(typeof function(){}); // "function"
```

4. 타입 변환: JavaScript는 필요에 따라 자동으로 타입을 변환합니다. (암시적 변환). 또는 명시적으로 타입을 변환할 수도 있습니다. (명시적 변환).
    - 암시적 변환:
    ```javascript
    console.log("5" + 3); // "53" (문자열 연결)
    console.log("5" - 3); // 2 (숫자로 변환 후 연산)
    console.log("5" == 5); // true (값만 비교)
    console.log("5" === 5); // false (값과 타입 모두 비교)
    ```

    - 명시적 변환:
    ```javascript
    console.log(Number("5")); // 5
    console.log(String(5)); // "5"
    console.log(Boolean(1)); // true
    ```

5. 변수 스코프: 변수의 스코프는 해당 변수가 접근 가능한 범위를 결정합니다.

    1. 전역 스코프: 어디서든 접근 가능
    ```javascript
    var globalVar = "I'm global";
    ```

    2. 함수 스코프 (var): 함수 내에서만 접근 가능.
    ```javascript
    function exampleFunction() {
    var functionScopedVar = "I'm function scoped";
    }
    ```

    3. 블록 스코프 (let, const): 블록 `{}` 내에서만 접근 가능
    ```javascript
    if (true) {
    let blockScopedVar = "I'm block scoped";
    }
    ```