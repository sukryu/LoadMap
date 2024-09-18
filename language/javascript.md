# JavaScript 프로그래밍 언어 #

## JavaScript 란? ##

JavaScript는 1995년 Netscape의 Brendan Eich에 의해 개발된 고급 프로그래밍 언어입니다. 원래는 웹 브라우저에서 동작하는
클라이언트 사이드 스크립트 언어로 시작했지만, 현재는 서버 사이드 개발(Node.js)을 포함한 다양한 환경에서 사용되고 있습니다.

- 다음과 같은 특징을 가집니다.
    1. 인터프리터 언어: JavaScript는 컴파일 과정 없이 코드를 한 줄씩 해석하고 실행하는 인터프리터 언어입니다.
    2. 동적 타이핑: 변수의 타입을 명시적으로 선언할 필요 없이, 실행 시점에 자동으로 타입이 결정됩니다.
    3. 객체 지향: JavaScript는 프로토타입 기반의 객체 지향 언어입니다.
    4. 함수형 프로그래밍: 함수를 일급 객체로 취급하며, 함수형 프로그래밍 패러다임을 지원합니다.
    5. 이벤트 기반: 사용자 상호작용, 타이머 등의 이벤트에 반응하여 프로그램을 실행할 수 있습니다.
    6. 크로스 플랫폼: 대부분의 웹 브라우저에서 실행 가능하며, Node.js를 통해 서버 환경에서도 실행할 수 있습니다.

## JavaScript의 동작 방식 ##

JavaScript 코드가 실행되는 과정은 다음과 같습니다.

1. 소스 코드 작성: .js 확장자를 가진 파일에 JavaScript 코드를 작성합니다.
2. 파싱: JavaScript 엔진이 소스 코드를 파싱하여 추상 구문 트리 (AST)를 생성합니다.
3. 컴파일: 많은 현대 JavaScript 엔진은 Just-In-Time(JIT) 컴파일러를 사용하여 AST를 바이트코드로 컴파일합니다.
4. 실행: 컴파일된 코드가 JavaScript 엔진에 의해 실행됩니다.
5. 최적화: 코드 실행 중에 JavaScript 엔진은 지속적으로 코드를 분석하고 최적화합니다.

## JavaScript의 주요 기능과 개념 ##

### 변수와 데이터 타입 ###

- 변수:
    - JavaScript에서 변수는 `var`, `let`, `const` 키워드를 사용하여 선언합니다.
    - `var`는 함수 스코프를 가지며, `let`과 `const`는 블록 스코프를 가집니다.
    - `const`는 상수를 선언할 때 사용하며, 재할당이 불가능합니다.

```javascript
var x = 5;
let name = "Alice";
const PI = 3.14159;
```

- 주요 데이터 타입:
    - 숫자(Number): 정수와 실수를 모두 표함합니다.
    ```javascript
    let age = 25;
    let pi = 3.14159;
    ```

    - 문자열 (String): 텍스트를 표현하는 데 사용됩니다. 작은 따옴표(''), 큰 따옴표(""), 또는 백틱 (``)으로 묶어 표현합니다.
    ```javascript
    let name = "Bob";
    let message = 'Hello, World!';
    let multiline = `This is a
    multiline string`;
    ```

    - 템플릿 리터럴:
    ```javascript
    let name = "Alice";
    let age = 30;
    console.log(`My name is ${name} and I'm ${age} years old.`);
    ```

    - 불리언 (Boolean): `true` or `false` 값을 가집니다.
    ```javascript
    let isRaining = true;
    let hasLicense = false;
    ```

    - Null과 Undefined
        - `null`은 값이 의도적으로 없음을 나타냅니다.
        - `undefined`는 값이 할당되지 않았음을 나타냅니다.
    ```javascript
    let result = null;
    let notDefined;
    console.log(notDefined);  // undefined
    ```

    - 심볼 (Symbol): ES6에서 도입된 고유한 식별자를 생성하는 데 사용됩니다.
    ```javascript
    const sym1 = Symbol();
    const sym2 = Symbol("description");
    ```

    - 객체 (Object): 키-값 쌍의 집합입니다.
    ```javascript
    let person = {
        name: "Alice",
        age: 30,
        isStudent: false
    };
    ```

    - 배열(Array): 값의 순서가 있는 집합입니다.
    ```javascript
    let fruits = ["apple", "banana", "cherry"];
    ```

    - 타입 변환:
    ```javascript
    // 문자열을 숫자로
    let x = Number("5");

    // 숫자를 문자열로
    let y = String(3.14);

    // 불리언으로 변환
    let b1 = Boolean(1);  // true
    let b2 = Boolean("");  // false
    ```

    - 타입 확인:
    ```javascript
    console.log(typeof 42);  // "number"
    console.log(typeof "Hello");  // "string"
    console.log(typeof true);  // "boolean"
    console.log(typeof {});  // "object"
    console.log(typeof []);  // "object" (배열도 객체의 일종)
    console.log(typeof null);  // "object" (JavaScript의 오래된 버그)
    console.log(typeof undefined);  // "undefined"
    ```

- 변수의 스코프
    - JavaScript에서 변수의 스코프는 변수가 선언된 위치와 사용된 키워드 (`var`, `let`, `const` ) 에 따라 결정됩니다.

    1. 전역 스코프: 함수 외부에서 선언된 변수는 전역 스코프를 가지며, 어디서든 접근 가능합니다.
    2. 함수 스코프: `var`로 선언된 변수는 함수 스코프를 가집니다.
    3. 블록 스코프: `let`과 `const`로 선언된 변수는 블록 스코프를 가집니다.

    ```javascript
    var globalVar = 10;  // 전역 변수

    function exampleFunction() {
        var functionVar = 20;  // 함수 스코프 변수
        let blockVar = 30;  // 블록 스코프 변수

        if (true) {
            var varInBlock = 40;  // 함수 스코프 (호이스팅됨)
            let letInBlock = 50;  // 블록 스코프
            const constInBlock = 60;  // 블록 스코프
        }

        console.log(varInBlock);  // 40
        // console.log(letInBlock);  // ReferenceError
        // console.log(constInBlock);  // ReferenceError
    }

    exampleFunction();
    console.log(globalVar);  // 10
    // console.log(functionVar);  // ReferenceError
    ```

### 연산자와 표현식 ###

#### 연산자 ####

JavaScript에서 연산자는 값에 대해 연산을 수행하는 기호입니다. 다양한 종류의 연산자가 있으며,
이를 통해 산술 연산, 비교, 논리 연산 등을 수행할 수 있습니다.

1. 산술 연산자
    - 산술 연산자는 수학적 계산을 수행합니다.

    - `+`: 덧셈
    - `-`: 뺄셈
    - `*`: 곱셈
    - `/`: 나눗셈
    - `%`: 나머지
    - `**`: 거듭제곱(ES7+)

    ```javascript
    let a = 10;
    let b = 3;

    console.log(a + b);  // 13
    console.log(a - b);  // 7
    console.log(a * b);  // 30
    console.log(a / b);  // 3.3333333333333335
    console.log(a % b);  // 1
    console.log(a ** b); // 1000
    ```

    2. 할당 연산자
        - 할당 연산자는 변수에 값을 할당합니다.

        - `=`: 기본 할당
        - `+=`, `-=`, `*=`, `/=`, `%=`: 복합 할당

        ```javascript
        let x = 5;
        x += 3;  // x = x + 3
        console.log(x);  // 8

        x *= 2;  // x = x * 2
        console.log(x);  // 16
        ```

    3. 비교 연산자
        - 비교 연산자는 두 값을 비교하고 boolean 값을 반환합니다.

        - `==`: 동등
        - `===`: 일치(값과 타입이 모두 같음)
        - `!=`: 부등
        - `!==`: 불일치
        - `>`, `<`, `>=`, `<=`: 대소 비교

        ```javascript
        console.log(5 == "5");   // true
        console.log(5 === "5");  // false
        console.log(5 != "6");   // true
        console.log(5 !== 5);    // false
        console.log(5 > 3);      // true
        console.log(5 <= 5);     // true
        ```

    4. 논리 연산자
        - 논리 연산자는 boolean 값에 대한 연산을 수행합니다.

        - `&&`: AND
        - `||`: OR
        - `!`: NOT

        ```javascript
        let t = true;
        let f = false;

        console.log(t && f);  // false
        console.log(t || f);  // true
        console.log(!t);      // false
        ```

    5. 단항 연산자
        - 단항 연산자는 하나의 피연산자에 대한 연산을 수행합니다.

        - `+`: 숫자로 변환
        - `-`: 부호 변경
        - `++`: 증가
        - `--`: 감소
        - `typeof`: 타입 확인

        ```javascript
        let num = 5;
        console.log(+"-10");     // -10 (문자열을 숫자로 변환)
        console.log(-num);       // -5
        console.log(typeof num); // "number"

        let x = 3;
        console.log(x++);        // 3 (후위 증가: 현재 값 반환 후 증가)
        console.log(++x);        // 5 (전위 증가: 증가 후 값 반환)
        ```

    6. 조건 (삼항)연산자
        - 조건 연산자는 조건에 따라 값을 반환합니다.

        ```javascript
        let age = 20;
        let status = (age >= 18) ? "성인" : "미성년자";
        console.log(status);  // "성인"
        ```

    7. 비트 연산자
        - 비트 연산자는 숫자의 비트 단위 연산을 수행합니다.

        - `&`: AND
        - `|`: OR
        - `^`: XOR
        - `~`: NOT
        - `<<`, `>>`: 왼쪽/오른쪽 시프트
        - `>>>`: 부호 없는 쪽으로 시프트

        ```javascript
        let a = 5;  // 101 in binary
        let b = 3;  // 011 in binary

        console.log(a & b);   // 1 (001 in binary)
        console.log(a | b);   // 7 (111 in binary)
        console.log(a ^ b);   // 6 (110 in binary)
        console.log(~a);      // -6
        console.log(a << 1);  // 10 (1010 in binary)
        console.log(a >> 1);  // 2 (10 in binary)
        ```

#### 표현식 ####

표현식은 값으로 평가될 수 있는 코드의 조각입니다. JavaScript에서 표현식은 다음과 같은 형태를 가질 수 있습니다.:

1. 리터럴 표현식:
```javascript
42
"Hello, world!"
true
```

2. 변수 표현식:
```javascript
let x = 5;
x  // 이 자체가 표현식입니다.
```

3. 산술 표현식:
```javascript
3 + 4
x * y
```

4. 문자열 표현식:
```javascript
"Hello, " + name
`The sum is ${a + b}`  // 템플릿 리터럴
```

5. 논리 표현식:
```javascript
a > b && c < d
```

6. 함수 호출 표현식:
```javascript
Math.max(5, 10)
console.log("Hello")
```

7. 객체와 배열 표현식:
```javascript
{ name: "Alice", age: 30 }
[1, 2, 3, 4, 5]
```

8. 화살표 함수 표현식:
```javascript
(a, b) => a + b
```

### 제어 구조 ###

제어 구조는 프로그램의 실행 흐름을 제어하는 데 사용됩니다.
JavaScript의 주요 제어 구조는 조건문과 반복문입니다.

#### 조건문 ####

조건문은 특정 조건에 따라 코드 블록을 실행할지 여부를 결정합니다.

1. if문
    - 가장 기본적인 조건문으로, 특정 조건이 참일 때 코드 블록을 실행합니다.

    ```javascript
    let age = 18;
    if (age >= 18) {
        console.log("성인입니다.");
    }
    ```

2. if-else문
    - 조건이 참일 때와 거짓일 때 각각 다른 코드 블록을 실행합니다.

    ```javascript
    let temperature = 25;
    if (temperature > 30) {
        console.log("더운 날씨입니다.");
    } else {
        console.log("적당한 날씨입니다.");
    }
    ```

3. if-else if-else 문
    - 여러 조건을 순차적으로 검사하고, 해당하는 조건의 코드 블록을 실행합니다.

    ```javascript
    let score = 85;
    if (score >= 90) {
        console.log("A 등급");
    } else if (score >= 80) {
        console.log("B 등급");
    } else if (score >= 70) {
        console.log("C 등급");
    } else {
        console.log("D 등급");
    }
    ```

4. switch 문
    - 하나의 표현식을 여러 가능한 case와 비교하여 일치하는 case의 블록을 실행합니다.

    ```javascript
    let day = "Monday";
    switch (day) {
        case "Monday":
            console.log("Start of the work week");
            break;
        case "Friday":
            console.log("End of the work week");
            break;
        case "Saturday":
        case "Sunday":
            console.log("Weekend");
            break;
        default:
            console.log("Midweek");
    }
    ```

5. 삼항 연산자
    - 간단한 조건문을 한 줄로 작성할 수 있습니다.
    
    ```javascript
    let age = 20;
    let status = (age >= 18) ? "성인" : "미성년자";
    console.log(status);  // "성인"
    ```

#### 반복문 ####

반복문은 코드 블록을 여러 번 실행하는 데 사용됩니다.

1. for문
    - 지정된 횟수만큼 코드 블록을 반복 실행합니다.
    
    ```javascript
    for (let i = 0; i < 5; i++) {
        console.log(i);  // 0부터 4까지 출력
    }
    ```

2. while 문
    - 조건이 참인 동안 코드 블록을 반복 실행합니다.

    ```javascript
    let count = 0;
    while (count < 5) {
        console.log(count);
        count++;
    }
    ```

3. do-while 문
    - 코드 블록을 최소한 한 번 실행한 후, 조건이 참인 동안 반복 실행합니다.

    ```javascript
    let i = 0;
    do {
        console.log(i);
        i++;
    } while (i < 5);
    ```

4. for .. in문
    - 객체의 열거 가능한 속성들을 순회합니다.

    ```javascript
    let person = {name: "John", age: 30, job: "developer"};
    for (let key in person) {
        console.log(key + ": " + person[key]);
    }
    ```

5. for .. of 문
    - iterable 객체(배열, 문자열)의 값들을 순회합니다.

    ```javascript
    let fruits = ["apple", "banana", "cherry"];
    for (let fruit of fruits) {
        console.log(fruit);
    }
    ```

#### 제어 흐름 문 ####

1. break 문
    - 반복문이나 switch 문을 즉시 종료하고 빠져나갑니다.

    ```javascript
    for (let i = 0; i < 10; i++) {
        if (i === 5) {
            break;
        }
        console.log(i);  // 0부터 4까지만 출력됨
    }
    ```

2. continue 문
    - 현재 반복을 건너뛰고 다음 반복으로 진행합니다.

    ```javascript
    for (let i = 0; i < 5; i++) {
        if (i === 2) {
            continue;
        }
        console.log(i);  // 0, 1, 3, 4가 출력됨 (2는 건너뜀)
    }
    ```

3. return 문
    - 함수의 실행을 종료하고 결과값을 반환합니다.

    ```javascript
    function isEven(num) {
        if (num % 2 === 0) {
            return true;
        }
        return false;
    }

    console.log(isEven(4));  // true
    console.log(isEven(5));  // false
    ```

4. throw 문
    - 예외를 발생시킵니다.

    ```javascript
    function divide(a, b) {
        if (b === 0) {
            throw new Error("Division by zero");
        }
        return a / b;
    }

    try {
        console.log(divide(10, 2));  // 5
        console.log(divide(10, 0));  // Error: Division by zero
    } catch (error) {
        console.log(error.message);
    }
    ```

### 함수 ###

함수는 JavaScript에서 핵심적인 개념으로, 재사용 가능한 코드 블록을 정의하는 데 사용됩니다.
함수를 통해 코드의 모듈화, 재사용성, 그리고 추상화를 구현할 수 있습니다.

1. 함수 정의와 호출

#### 함수 선언문 ####
```javascript
function greet(name) {
    return `Hello, ${name}!`;
}

console.log(greet("Alice"));  // 출력: Hello, Alice!
```

#### 함수 표현식 ####
```javascript
const greet = function(name) {
    return `Hello, ${name}!`;
};

console.log(greet("Bob"));  // 출력: Hello, Bob!
```

#### 화살표 함수

ES6에서 도입된 더 간결한 함수 문법입니다.

```javascript
const greet = (name) => `Hello, ${name}!`;

console.log(greet("Charlie"));  // 출력: Hello, Charlie!
```

2. 매개변수와 인자

#### 기본 매개 변수 ####
```javascript
function greet(name = "Guest") {
    return `Hello, ${name}!`;
}

console.log(greet());  // 출력: Hello, Guest!
console.log(greet("Alice"));  // 출력: Hello, Alice!
```

#### 나머지 매개변수 ####
```javascript
function sum(...numbers) {
    return numbers.reduce((total, num) => total + num, 0);
}

console.log(sum(1, 2, 3, 4));  // 출력: 10
```

3. 반환값

함수는 `return`문을 사용하여 값을 반환할 수 있습니다.

```javascript
function multiply(a, b) {
    return a * b;
}

console.log(multiply(3, 4));  // 출력: 12
```

함수가 명시적으로 값을 반환하지 않으면 `undefined`를 반환합니다.

```javascript
function greet(name) {
    console.log(`Hello, ${name}!`);
}

console.log(greet("Alice"));  // 출력: Hello, Alice! 그리고 undefined
```

4. 스코프와 클로저

#### 렉시컬 스코프 ####

JavaScript는 렉시컬 스코프를 사용합니다. 이는 함수가 정의된 위치에 따라 상위 스코프가 결정된다는 의미입니다.

```javascript
const x = 10;

function outer() {
    const y = 20;
    function inner() {
        const z = 30;
        console.log(x + y + z);
    }
    inner();
}

outer();  // 출력: 60
```

#### 클로저 ####

클로저는 함수와 그 함수가 선언된 렉시컬 환경의 조합입니다.

```javascript
function makeAdder(x) {
    return function(y) {
        return x + y;
    };
}

const add5 = makeAdder(5);
console.log(add5(3));  // 출력: 8
```

5. 고차 함수

고차함수는 다른 함수를 인자로 받거나 함수를 반환하는 함수입니다.

```javascript
function applyOperation(x, y, operation) {
    return operation(x, y);
}

const add = (a, b) => a + b;
const multiply = (a, b) => a * b;

console.log(applyOperation(5, 3, add));      // 출력: 8
console.log(applyOperation(5, 3, multiply)); // 출력: 15
```

6. 메서드

객체의 속성으로 할당된 함수를 메서드라고 합니다.

```javascript
const person = {
    name: "Alice",
    greet: function() {
        console.log(`Hello, I'm ${this.name}`);
    }
};

person.greet();  // 출력: Hello, I'm Alice
```

7. this 키워드

`this`는 함수가 어떻게 호출되었는지에 따라 다른 객체를 참조합니다.

```javascript
const person = {
    name: "Alice",
    greet: function() {
        console.log(`Hello, I'm ${this.name}`);
    }
};

person.greet();  // 출력: Hello, I'm Alice

const greetFunction = person.greet;
greetFunction();  // 출력: Hello, I'm undefined (strict mode에서는 에러)
```

8. 화살표 함수와 this

화살표 함수는 자신만의 `this`를 바인딩하지 않고, 외부 스코프의 `this`를 그대로 사용합니다.

```javascript
const person = {
    name: "Alice",
    greet: function() {
        setTimeout(() => {
            console.log(`Hello, I'm ${this.name}`);
        }, 1000);
    }
};

person.greet();  // 1초 후 출력: Hello, I'm Alice
```

9. 즉시 실행 함수 표현식 (IIFE)

함수를 정의하자마자 즉시 실행하는 패턴입니다.

```javascript
(function() {
    const secret = "I'm a secret value";
    console.log(secret);
})();

// console.log(secret);  // ReferenceError: secret is not defined
```

10. 재귀 함수

자기 자신을 호출하는 함수입니다.

```javascript
function factorial(n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

console.log(factorial(5));  // 출력: 120
```