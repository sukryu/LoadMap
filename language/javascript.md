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

### 객체 지향 프로그래밍 ###

JavaScript는 프로토타입 기반의 객체 지향 프로그래밍을 지원합니다.
ES6부터는 클래스 문법도 도입되어 더욱 직관적인 객체 지향 프로그래밍이 가능해졌습니다.

1. 객체 생성과 프로토타입

    1. 객체 리터럴
        - 가장 간단한 객체 생성 방법입니다.
        ```javascript
        const person = {
            name: "Alice",
            age: 30,
            greet: function() {
                console.log(`Hello, I'm ${this.name}`);
            }
        };

        person.greet();  // 출력: Hello, I'm Alice
        ```

    2. 생성자 함수
    ```javascript
    function Person(name, age) {
        this.name = name;
        this.age = age;
        this.greet = function() {
            console.log(`Hello, I'm ${this.name}`);
        };
    }

    const alice = new Person("Alice", 30);
    alice.greet();  // 출력: Hello, I'm Alice
    ```

    3. 프로토타입
        - 프로토타입을 사용하면 모든 인스턴스가 공유하는 메서드를 정의할 수 있습니다.
        ```javascript
        function Person(name, age) {
            this.name = name;
            this.age = age;
        }

        Person.prototype.greet = function() {
            console.log(`Hello, I'm ${this.name}`);
        };

        const alice = new Person("Alice", 30);
        alice.greet();  // 출력: Hello, I'm Alice
        ```

2. 클래스
    - ES6부터 도입된 클래스 문법은 객체 지향 프로그래밍을 더 직관적으로 만듭니다.

    ```javascript
    class Person {
        constructor(name, age) {
            this.name = name;
            this.age = age;
        }

        greet() {
            console.log(`Hello, I'm ${this.name}`);
        }
    }

    const alice = new Person("Alice", 30);
    alice.greet();  // 출력: Hello, I'm Alice
    ```

3. 상속
    - 프로토타입 체인을 이용한 상속

    ```javascript
    function Animal(name) {
        this.name = name;
    }

    Animal.prototype.speak = function() {
        console.log(`${this.name} makes a sound.`);
    };

    function Dog(name) {
        Animal.call(this, name);
    }

    Dog.prototype = Object.create(Animal.prototype);
    Dog.prototype.constructor = Dog;

    Dog.prototype.bark = function() {
        console.log(`${this.name} barks.`);
    };

    const dog = new Dog("Buddy");
    dog.speak();  // 출력: Buddy makes a sound.
    dog.bark();   // 출력: Buddy barks.
    ```

    - 클래스를 이용한 상속

    ```javascript
    class Animal {
        constructor(name) {
            this.name = name;
        }

        speak() {
            console.log(`${this.name} makes a sound.`);
        }
    }

    class Dog extends Animal {
        bark() {
            console.log(`${this.name} barks.`);
        }
    }

    const dog = new Dog("Buddy");
    dog.speak();  // 출력: Buddy makes a sound.
    dog.bark();   // 출력: Buddy barks.
    ```

4. 캡슐화
    - javascript에서는 진정한 의미의 private 속성을 지원하지 않지만,
    몇 가지 방법으로 캡슐화를 구현할 수 있습니다.

    1. 클로저를 이용한 캡슐화
    
    ```javascript
    function Counter() {
        let count = 0;  // private 변수

        this.increment = function() {
            count++;
        };

        this.getCount = function() {
            return count;
        };
    }

    const counter = new Counter();
    counter.increment();
    console.log(counter.getCount());  // 출력: 1
    console.log(counter.count);  // 출력: undefined
    ```

    2. Symbol을 이용한 캡슐화

    ```javascript
    const _count = Symbol('count');

    class Counter {
        constructor() {
            this[_count] = 0;
        }

        increment() {
            this[_count]++;
        }

        get count() {
            return this[_count];
        }
    }

    const counter = new Counter();
    counter.increment();
    console.log(counter.count);  // 출력: 1
    console.log(counter[_count]);  // 출력: 1 (하지만 이는 권장되지 않음)
    ```

5. 다형성
    - 다형성은 같은 인터페이스를 사용하여 다양한 객체 타입을 다룰 수 있는 능력입니다.

    ```javascript
    class Shape {
        area() {
            throw new Error("Area method should be implemented");
        }
    }

    class Circle extends Shape {
        constructor(radius) {
            super();
            this.radius = radius;
        }

        area() {
            return Math.PI * this.radius ** 2;
        }
    }

    class Rectangle extends Shape {
        constructor(width, height) {
            super();
            this.width = width;
            this.height = height;
        }

        area() {
            return this.width * this.height;
        }
    }

    function printArea(shape) {
        console.log(`Area: ${shape.area()}`);
    }

    const circle = new Circle(5);
    const rectangle = new Rectangle(4, 5);

    printArea(circle);     // 출력: Area: 78.53981633974483
    printArea(rectangle);  // 출력: Area: 20
    ```

6. 정적 메서드와 속성
    - 클래스나 생성자 함수에 직접 연결된 메서드와 속성입니다.

    ```javascript
    class MathOperations {
        static PI = 3.14159;

        static square(x) {
            return x * x;
        }
    }

    console.log(MathOperations.PI);  // 출력: 3.14159
    console.log(MathOperations.square(5));  // 출력: 25
    ```

7. getter와 setter
    - 객체의 속성에 접근하거나 수정할 때 특별한 동작을 정의할 수 있습니다.

    ```javascript
    class Person {
        constructor(name) {
            this._name = name;
        }

        get name() {
            return this._name.toUpperCase();
        }

        set name(newName) {
            if (newName.length > 0) {
                this._name = newName;
            } else {
                console.log("Name cannot be empty");
            }
        }
    }

    const person = new Person("Alice");
    console.log(person.name);  // 출력: ALICE
    person.name = "Bob";
    console.log(person.name);  // 출력: BOB
    person.name = "";  // 출력: Name cannot be empty
    ```

### 비동기 프로그래밍 ###

JavaScript는 단일 스레드 언어이지만, 비동기 프로그래밍을 통해 효율적으로
I/O 작업을 처리하고 반응성 있는 애플리케이션을 만들 수 있습니다. 비동기 프로그래밍은
시간이 걸리는 작업(예: 네트워크 요청, 파일 읽기/쓰기)을 처리할 때 특히 유용합니다.

1. 콜백 (Callbacks)
    - 콜백은 JavaScript에서 비동기 프로그래밍을 구현하는 가장 기본적인 방법입니다.

    ```javascript
    function fetchData(callback) {
        setTimeout(() => {
            const data = { id: 1, name: "John Doe" };
            callback(data);
        }, 1000);
    }

    fetchData((data) => {
        console.log(data);  // 1초 후 출력: { id: 1, name: "John Doe" }
    });

    console.log("Fetching data...");  // 즉시 출력
    ```

    하지만 콜백을 중첩해서 사용하면 "콜백 지옥"이라고 불리는
    가독성 떨어지는 코드가 만들어질 수 있습니다.

    ```javascript
    fetchUser(function(user) {
        fetchPosts(user.id, function(posts) {
            fetchComments(posts[0].id, function(comments) {
                // 이렇게 계속 중첩될 수 있습니다...
            });
        });
    });
    ```

2. Promise
    - Promise는 ES6에서 도입된 비동기 작업의 최종 완료 또는 실패를 나타내는 객체입니다.

    ```javascript
    function fetchData() {
        return new Promise((resolve, reject) => {
            setTimeout(() => {
                const data = { id: 1, name: "John Doe" };
                resolve(data);
                // 에러가 발생했다면: reject(new Error("Failed to fetch data"));
            }, 1000);
        });
    }

    fetchData()
        .then(data => console.log(data))
        .catch(error => console.error(error));

    console.log("Fetching data...");
    ```

    Promise를 사용하면 콜백 지옥 문제를 해결할 수 있습니다.

    ```javascript
    fetchUser()
        .then(user => fetchPosts(user.id))
        .then(posts => fetchComments(posts[0].id))
        .then(comments => {
            // 처리 로직
        })
        .catch(error => console.error(error));
    ```

    1. Promise.all()
        - 여러 개의 Promise를 병렬로 처리할 때 사용합니다.

        ```javascript
        const promise1 = fetchUser();
        const promise2 = fetchPosts();

        Promise.all([promise1, promise2])
            .then(([user, posts]) => {
                // user와 posts 데이터를 모두 받은 후 처리
            })
            .catch(error => console.error(error));
        ```

    2. Promise.race()
        - 여러 Promise 중 가장 먼저 완료되는 것만 처리합니다.

        ```javascript
        const promise1 = new Promise(resolve => setTimeout(() => resolve("First"), 500));
        const promise2 = new Promise(resolve => setTimeout(() => resolve("Second"), 100));

        Promise.race([promise1, promise2])
            .then(result => console.log(result))  // 출력: "Second"
            .catch(error => console.error(error));
        ``` 
    
3. async/await
    - async/await는 ES2017에서 도입된 기능으로, Promise를 더 쉽고 직관적으로 사용할 수 있게 해줍니다.

    ```javascript
    async function fetchUserData() {
        try {
            const user = await fetchUser();
            const posts = await fetchPosts(user.id);
            const comments = await fetchComments(posts[0].id);
            return { user, posts, comments };
        } catch (error) {
            console.error(error);
        }
    }

    fetchUserData().then(data => console.log(data));
    ```

    async 함수는 항상 Promise를 반환합니다. await 키워드는 Promise가 처리될 때까지
    함수의 실행을 일시 중지합니다.

    - 병렬 처리
    ```javascript
    async function fetchAllData() {
        const [user, posts] = await Promise.all([fetchUser(), fetchPosts()]);
        return { user, posts };
    }
    ```

4. 이벤트 루프
    - JavaScript의 비동기 동작을 이해하려면 이벤트 루프의 개념을 아는 것이 중요합니다.

    1. 콜 스택: 동기적으로 실행되는 코드가 쌓입니다.
    2. 태스크 큐: setTimeout, setInterval 등의 비동기 작업이 완료된 후 실행될 콜백이 쌓입니다.
    3. 마이크로태스크 큐: Promise의 then/catch/finally 핸들러가 쌓입니다.

    - 이벤트 루프는 다음과 같은 순서로 작동합니다:
        1. 콜 스택이 비어있는지 확인합니다.
        2. 마이크로태스크 큐에 작업이 있으면 실행합니다.
        3. 렌더링 작업을 수행합니다. (브라우저 환경의 경우).
        4. 태스크 큐에서 하나의 작업을 가져와 실행합니다.
        5. 1번으로 돌아갑니다.

5. Web API
    - 브라우저 환경에서 JavaScript는 Web API를 통해 비동기 작업을 수행합니다.

    - setTimeout/setInterval: 일정 시간 후에 콜백을 실행합니다.
    - fetch: HTTP 요청을 보냅니다.
    - addEventListner: 이벤트 리스너를 등록합니다.

    ```javascript
    console.log("Start");

    setTimeout(() => console.log("Timeout"), 0);

    Promise.resolve().then(() => console.log("Promise"));

    console.log("End");

    // 출력 순서:
    // Start
    // End
    // Promise
    // Timeout
    ```

6. 에러 처리
    - 비동기 코드에서의 에러 처리는 동기 코드와는 다르게 작동합니다.

    ```javascript
    // Promise
    fetchData()
        .then(data => {
            // 데이터 처리
        })
        .catch(error => {
            console.error("An error occurred:", error);
        });

    // async/await
    async function fetchData() {
        try {
            const data = await fetchAPI();
            // 데이터 처리
        } catch (error) {
            console.error("An error occurred:", error);
        }
    }
    ```

### 모듈 시스템 ###

모듈 시스템은 코드를 구조화하고 재사용 가능한 단위로 분리하는 메커니즘입니다.
JavaScript에서는 여러 모듈 시스템이 발전해 왔으며, 현재는 ES6(ES2015)모듈이 표준으로 사용되고 있습니다.

1. 모듈의 필요성
    - 코드 구조화 및 네임스페이스 관리
    - 코드 재사용성 향상
    - 의존성 관리
    - 전역 스코프 오염 방지

2. CommonJS
    - Node.js에서 주로 사용되는 모듈 시스템입니다.

    1. 내보내기 (Exporting)

    ```javascript
    // math.js
    function add(a, b) {
        return a + b;
    }

    function subtract(a, b) {
        return a - b;
    }

    module.exports = {
        add: add,
        subtract: subtract
    };

    // 또는 개별적으로 내보내기
    // exports.add = add;
    // exports.subtract = subtract;
    ```

    2. 가져오기 (Importing)

    ```javascript
    const math = require('./math');

    console.log(math.add(5, 3));      // 출력: 8
    console.log(math.subtract(5, 3)); // 출력: 2

    // 구조 분해 할당을 사용할 수도 있습니다
    // const { add, subtract } = require('./math');
    ```

3. ES6 모듈
    - ES6에서 도입된 표준 모듈 시스템입니다. 브라우저와 최신 Node.js 버전에서 지원됩니다.

    1. 내보내기 (Exporting)

    ```javascript
    // math.js
    export function add(a, b) {
        return a + b;
    }

    export function subtract(a, b) {
        return a - b;
    }

    // 기본 내보내기
    export default function multiply(a, b) {
        return a * b;
    }
    ```

    2. 가져오기 (Importing)

    ```javascript
    import { add, subtract } from './math.js';
    import multiply from './math.js';  // 기본 내보내기 가져오기

    console.log(add(5, 3));      // 출력: 8
    console.log(subtract(5, 3)); // 출력: 2
    console.log(multiply(5, 3)); // 출력: 15

    // 모든 내보내기를 한 번에 가져오기
    // import * as math from './math.js';
    // console.log(math.add(5, 3));
    ```

4. 동적 임포트
    - ES2020에서 도입된 기능으로, 필요한 시점에 모듈을 동적으로 가져올 수 있습니다.

    ```javascript
    async function loadModule() {
        if (someCondition) {
            const { default: myModule } = await import('./myModule.js');
            myModule.doSomething();
        }
    }
    ```

5. 모듈 번들러
    - 대규모 애플리케이션에서는 모듈 번들러를 사용하여 여러 모듈을 하나의 파일로 묶어 성능을 최적화합니다.

    - Webpack
    - Rollup
    - Parcel

    - 예: Webpack 설정 (webpack.config.js)

    ```javascript
    const path = require('path');

    module.exports = {
        entry: './src/index.js',
        output: {
            filename: 'bundle.js',
            path: path.resolve(__dirname, 'dist'),
        },
        module: {
            rules: [
                {
                    test: /\.js$/,
                    exclude: /node_modules/,
                    use: {
                        loader: 'babel-loader',
                        options: {
                            presets: ['@babel/preset-env']
                        }
                    }
                }
            ]
        }
    };
    ```

6. 순환 의존성
    - 모듈 간 순환 의존성이 발생할 수 있으며, 이는 주의해서 다뤄야 합니다.

    ```javascript
    // a.js
    import { b } from './b.js';
    export const a = 1;
    console.log(b);

    // b.js
    import { a } from './a.js';
    export const b = 2;
    console.log(a);

    // 이런 경우, a는 undefined로 출력될 수 있습니다.
    ```

7. Node.js에서의 ES 모듈 사용
    - Node.js에서 ES 모듈을 사용하려면 다음 방법 중 하나를 선택할 수 있습니다.

    1. 파일 확장자를 `.mjs`로 변경
    2. 가장 가까운 `package.json`에 `"type":"module"` 추가

    ```json
    {
        "name": "my-project",
        "version": "1.0.0",
        "type": "module"
    }
    ```

8. 모듈 패턴(클로저를 이용한 모듈)
    - ES6 이전에 모듈과 유사한 패턴을 구현하는 방법입니다.

    ```javascript
    const myModule = (function() {
        let privateVariable = 0;

        function privateFunction() {
            console.log('This is private');
        }

        return {
            publicMethod: function() {
                privateFunction();
                console.log(privateVariable);
            },
            publicVariable: 42
        };
    })();

    myModule.publicMethod();  // 출력: This is private, 0
    console.log(myModule.publicVariable);  // 출력: 42
    // console.log(myModule.privateVariable);  // undefined
    ```

9. 모듈의 장점
    1. 코드 재사용성: 모듈화된 코드는 여러 프로젝트에서 쉽게 사용할 수 있습니다.
    2. 의존성 관리: 모듈 간의 의존성을 명확하게 관리할 수 있습니다.
    3. 네임스페이스 관리: 전역 스코프 오염을 방지하고 변수명 충돌을 줄일 수 있습니다.
    4. 코드 구조화: 큰 프로그램을 작은 단위로 나누어 관리할 수 있습니다.
    5. 성능 최적화: 필요한 모듈만 로드하여 초기 로딩 시간을 줄일 수 있습니다.

### DOM 조작 ###

DOM(Document Object Model)은 HTML 문서의 프로그래밍 인터페이스입니다.
JavaScript를 사용하여 DOM을 조작함으로써 웹 페이지의 내용, 구조, 스타일을 동적으로 변경할 수 있습니다.

1. DOM 요소 선택
    1. 단일 요소 선택
    ```javascript
    // ID로 선택
    const element = document.getElementById('myId');

    // CSS 선택자로 첫 번째 일치하는 요소 선택
    const element = document.querySelector('.myClass');
    ```

    2. 여러 요소 선택
    ```javascript
    // 클래스명으로 선택
    const elements = document.getElementsByClassName('myClass');

    // 태그명으로 선택
    const elements = document.getElementsByTagName('div');

    // CSS 선택자로 일치하는 모든 요소 선택
    const elements = document.querySelectorAll('p.intro');
    ```

2. DOM 요소 생성 및 추가
    1. 요소 생성
    ```javascript
    const newDiv = document.createElement('div');
    const newText = document.createTextNode('Hello, World!');
    newDiv.appendChild(newText);
    ```

    2. 요소 추가
    ```javascript
    // 부모 요소의 마지막 자식으로 추가
    parentElement.appendChild(newDiv);

    // 특정 위치에 삽입
    parentElement.insertBefore(newDiv, referenceNode);
    ```

3. DOM 요소 수정
    1. 내용 수정
    ```javascript
    element.textContent = 'New text content';
    element.innerHTML = '<span>New HTML content</span>';
    ```

    2. 속성 수정
    ```javascript
    element.setAttribute('class', 'newClass');
    element.id = 'newId';
    ```

    3. 스타일 수정
    ```javascript
    element.style.color = 'red';
    element.style.backgroundColor = '#f0f0f0';
    ```

4. DOM 요소 제거
```javascript
// 요소 자체 제거
element.remove();

// 부모 요소에서 자식 요소 제거
parentElement.removeChild(childElement);
```

5. 이벤트 처리
    - 이벤트 리스너 추가

    ```javascript
    element.addEventListener('click', function(event) {
        console.log('Element clicked!');
    });
    ```

    - 이벤트 객체 사용

    ```javascript
    element.addEventListener('click', function(event) {
        console.log('Clicked at: ', event.clientX, event.clientY);
        event.preventDefault(); // 기본 동작 방지
    });
    ```

6. DOM 탐색
    - 부모, 자식, 형제요소 접근

    ```javascript
    const parent = element.parentNode;
    const children = element.children;
    const nextSibling = element.nextElementSibling;
    const previousSibling = element.previousElementSibling;
    ```

7. 클래스 조작
```javascript
element.classList.add('newClass');
element.classList.remove('oldClass');
element.classList.toggle('toggleClass');
element.classList.contains('checkClass');
```

8. 데이터 속성 사용

    - HTML:
    ```html
    <div id="myElement" data-info="Some information"></div>
    ```

    - JavaScript:
    ```javascript
    const element = document.getElementById('myElement');
    console.log(element.dataset.info); // "Some information"
    element.dataset.newInfo = "New information";
    ```

9. DOM 요소 복제

```javascript
const clone = element.cloneNode(true); // true는 깊은 복사를 의미
parentElement.appendChild(clone);
```

10. 프래그먼트 사용
    - 여러 요소를 한 번에 추가할 때 성능 향상을 위해 사용합니다.

    ```javascript
    const fragment = document.createDocumentFragment();
    for (let i = 0; i < 1000; i++) {
        const newElement = document.createElement('div');
        newElement.textContent = `Element ${i}`;
        fragment.appendChild(newElement);
    }
    parentElement.appendChild(fragment);
    ```

11. 요소의 크기와 위치
```javascript
const rect = element.getBoundingClientRect();
console.log(rect.top, rect.left, rect.width, rect.height);
```

12. DOM 변경 감지 (MutationObserver)
```javascript
const observer = new MutationObserver((mutations) => {
    mutations.forEach((mutation) => {
        console.log(mutation.type);
    });
});

observer.observe(targetNode, { childList: true, subtree: true });
```

13. 성능 고려사항
    1. DOM 조작을 최소화하세요. 여러 변경사항을 한 번에 적용하는 것이 좋습니다.
    2. `innerHTML`보다 `textContent`를 사용하면 더 빠르고 안전합니다.
    3. 요소를 자주 선택해야 할 경우, 변수에 저장하여 재사용하세요.
    4. 큰 리스트를 렌더링할 때는 가상 스크롤을 고려하세요.

14. 브라우저 지원 및 폴리필
    - 일부 DOM API는 구현 브라우저에서 지원되지 않을 수 있습니다.
    필요한 경우 폴리필을 사용하여 호환성을 확보하세요.

    ```javascript
    if (!Element.prototype.matches) {
        Element.prototype.matches = Element.prototype.msMatchesSelector || 
                                    Element.prototype.webkitMatchesSelector;
    }
    ```

### AJAX와 API 통신

AJAX(Asynchronous JavaScript and XML)는 웹 페이지가 서버와 동기적으로 데이터를 교환할 수 있게 해주는 기술입니다.
현대 웹 애플리케이션에서는 AJAX를 사용하여 RESTful API와 통신하는 것이 일반적입니다.

1. XMLHttpRequest
    - XMLHttpRequest는 AJAX의 가장 기본적인 방식입니다.

    ```javascript
    const xhr = new XMLHttpRequest();
    xhr.open('GET', 'https://api.example.com/data', true);

    xhr.onload = function() {
        if (xhr.status === 200) {
            const response = JSON.parse(xhr.responseText);
            console.log(response);
        } else {
            console.error('Request failed. Status:', xhr.status);
        }
    };

    xhr.onerror = function() {
        console.error('Request failed. Network error');
    };

    xhr.send();
    ```

2. Fetch API
    - Fetch API는 XMLHttpRequest보다 더 강력하고 유연한 최신 API입니다.

    ```javascript
    fetch('https://api.example.com/data')
        .then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            return response.json();
        })
        .then(data => console.log(data))
        .catch(error => console.error('Fetch error:', error));
    ```

    - POST 요청 예시

    ```javascript
    fetch('https://api.example.com/post', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ key: 'value' })
    })
        .then(response => response.json())
        .then(data => console.log(data))
        .catch(error => console.error('Error:', error));
    ```

3. Axios
    - Axios는 브라우저와 Node.js에서 사용할 수 있는 인기 있는 HTTP 클라이언트 라이브러리입니다.

    ```javascript
    axios.get('https://api.example.com/data')
        .then(response => console.log(response.data))
        .catch(error => console.error('Error:', error));

    // POST 요청
    axios.post('https://api.example.com/post', { key: 'value' })
        .then(response => console.log(response.data))
        .catch(error => console.error('Error:', error));
    ```

4. async/await와 함께 사용
    - modern JavaScript에서는 async/await를 사용하여 비동기 코드를 더 읽기 쉽게 만들 수 있습니다.

    ```javascript
    async function fetchData() {
        try {
            const response = await fetch('https://api.example.com/data');
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            const data = await response.json();
            console.log(data);
        } catch (error) {
            console.error('Fetch error:', error);
        }
    }

    fetchData();
    ```

5. 에러 처리
    - API 통신 시 적절한 에러 처리는 매우 중요합니다.

    ```javascript
    fetch('https://api.example.com/data')
        .then(response => {
            if (!response.ok) {
                if (response.status === 404) {
                    throw new Error('Data not found');
                } else if (response.status === 500) {
                    throw new Error('Server error');
                } else {
                    throw new Error('Unknown error');
                }
            }
            return response.json();
        })
        .then(data => console.log(data))
        .catch(error => {
            console.error('Error:', error.message);
            // 사용자에게 에러 메시지 표시
    });
    ```

6. CORS (Cross-Origin Resource Sharing)
    - 브라우저의 동일 출처 정책으로 인해 다른 도메인의 리소스에 접근할 때 CORS 설정이 필요합니다.

    - 서버 측에서 적절한 CORS 헤더를 설정해야 하며, 클라이언트 측에서는 다음과 같이 처리할 수 있습니다.

    ```javascript
    fetch('https://api.example.com/data', {
        mode: 'cors', // 'no-cors', 'cors', 'same-origin'
        credentials: 'include', // 'include', 'same-origin', 'omit'
    })
        .then(response => response.json())
        .then(data => console.log(data))
        .catch(error => console.error('Error:', error));
    ```

7. API 인증
    - 많은 API는 인증을 요구합니다. 일반적인 인증 방식으로는 API키, Oauth, JWT 등이 있습니다.

    ```javascript
    // API 키를 사용한 예시
    fetch('https://api.example.com/data', {
        headers: {
            'Authorization': 'Bearer YOUR_API_KEY'
        }
    })
        .then(response => response.json())
        .then(data => console.log(data))
        .catch(error => console.error('Error:', error));
    ```

8. 요청 취소
    - fetch API를 사용할 때 AbortController를 사용하여 요청을 취소할 수 있습니다.

    ```javascript
    const controller = new AbortController();
    const signal = controller.signal;

    fetch('https://api.example.com/data', { signal })
        .then(response => response.json())
        .then(data => console.log(data))
        .catch(error => {
            if (error.name === 'AbortError') {
                console.log('Fetch aborted');
            } else {
                console.error('Error:', error);
            }
        });

    // 요청 취소
    controller.abort();
    ```

9. 동시 요청
    - 여러 API를 동시에 호출해야 할 때는 Promise.all을 사용할 수 있습니다.

    ```javascript
    const urls = [
        'https://api.example.com/data1',
        'https://api.example.com/data2',
        'https://api.example.com/data3'
    ];

    Promise.all(urls.map(url => fetch(url).then(resp => resp.json())))
        .then(results => {
            console.log(results);
        })
        .catch(error => console.error('Error:', error));
    ```

10. 재시도 로직
    - 네트워크 불안정 등의 이유로 요청이 실패할 경우, 재시도 로직을 구현할 수 있습니다.

    ```javascript
    async function fetchWithRetry(url, options = {}, retries = 3) {
        try {
            return await fetch(url, options);
        } catch (err) {
            if (retries > 0) {
                return await fetchWithRetry(url, options, retries - 1);
            } else {
                throw err;
            }
        }
    }

    fetchWithRetry('https://api.example.com/data')
        .then(response => response.json())
        .then(data => console.log(data))
        .catch(error => console.error('Error:', error));
    ```

11. 캐싱
    - 반복적인 API 호출을 줄이기 위해 응답을 캐싱할 수 있습니다.

    ```javascript
    const cache = new Map();

    async function fetchWithCache(url) {
        if (cache.has(url)) {
            return cache.get(url);
        }

        const response = await fetch(url);
        const data = await response.json();
        cache.set(url, data);
        return data;
    }

    fetchWithCache('https://api.example.com/data')
        .then(data => console.log(data))
        .catch(error => console.error('Error:', error));
    ```

### ES6+ 기능 ###

ECMAScript 2015 (ES6)이후로 JavaScript는 많은 새로운 기능과
개선사항을 도입했습니다. 이러한 기능들은 코드를 더 간결하고 읽기 쉽게 만들며,
더 강력한 프로그래밍 패턴을 가능하게 합니다.

1. let과 const
    - 블록 스코프 변수 선언.

    ```javascript
    let x = 10;
    const PI = 3.14159;

    if (true) {
        let x = 20; // 블록 스코프 내의 새로운 변수
        console.log(x); // 20
    }
    console.log(x); // 10
    ```

2. 화살표 함수
    - 더 간결한 함수 문법
    
    ```javascript
    // 기존 함수
    function add(a, b) {
        return a + b;
    }

    // 화살표 함수
    const add = (a, b) => a + b;

    // this 바인딩 차이
    const obj = {
        name: 'John',
        greet: function() {
            setTimeout(() => {
                console.log(`Hello, ${this.name}`);
            }, 1000);
        }
    };
    ```

3. 템플릿 리터럴
    - 문자열 삽입과 멀티라인 문자열 지원

    ```javascript
    const name = 'John';
    const age = 30;

    const greeting = `Hello, my name is ${name} and I'm ${age} years old.

    This is a multi-line string.`;
    ```

4. 구조 분해 할당
    - 배열이나 객체의 값을 개별 변수에 쉽게 할당

    ```javascript
    // 배열 구조 분해
    const [a, b] = [1, 2];

    // 객체 구조 분해
    const { name, age } = { name: 'John', age: 30 };

    // 함수 매개변수에서의 구조 분해
    function greet({ name, age }) {
        console.log(`Hello, ${name}. You are ${age} years old.`);
    }
    ```

5. 전개 연산자
    - 배열이나 객체를 펼치는데 사용

    ```javascript
    const arr1 = [1, 2, 3];
    const arr2 = [...arr1, 4, 5]; // [1, 2, 3, 4, 5]

    const obj1 = { x: 1, y: 2 };
    const obj2 = { ...obj1, z: 3 }; // { x: 1, y: 2, z: 3 }

    function sum(...numbers) {
        return numbers.reduce((total, num) => total + num, 0);
    }
    ```

6. 기본 매개변수
    - 함수 매개변수의 기본값 설정.

    ```javascript
    function greet(name = 'Guest') {
        console.log(`Hello, ${name}!`);
    }

    greet(); // "Hello, Guest!"
    greet('John'); // "Hello, John!"
    ```

7. 클래스
    - 객체 지향 프로그래밍을 위한 문법.

    ```javascript
    class Animal {
        constructor(name) {
            this.name = name;
        }

        speak() {
            console.log(`${this.name} makes a sound.`);
        }
    }

    class Dog extends Animal {
        speak() {
            console.log(`${this.name} barks.`);
        }
    }

    const dog = new Dog('Rex');
    dog.speak(); // "Rex barks."
    ```

8. Promise와 async/await
    - 비동기 프로그래밍을 위한 기능.

    ```javascript
    // Promise
    function fetchData() {
        return new Promise((resolve, reject) => {
            setTimeout(() => resolve('Data'), 1000);
        });
    }

    fetchData().then(data => console.log(data));

    // async/await
    async function getData() {
        const data = await fetchData();
        console.log(data);
    }

    getData();
    ```

9. 모듈
    - 코드를 모듈화하고 재사용하기 위한 기능

    ```javascript
    // math.js
    export function add(a, b) {
        return a + b;
    }

    // main.js
    import { add } from './math.js';
    console.log(add(2, 3)); // 5
    ```

10. Map과 Set
    - 새로운 데이터 구조

    ```javascript
    // Map
    const map = new Map();
    map.set('key', 'value');
    console.log(map.get('key')); // "value"

    // Set
    const set = new Set([1, 2, 3, 3, 4]);
    console.log(set); // Set(4) {1, 2, 3, 4}
    ```

11. Symbol
    - 유일한 식별자 생성.

    ```javascript
    const sym = Symbol('description');
    const obj = {
        [sym]: 'Value'
    };
    console.log(obj[sym]); // "Value"
    ```

12. 이터레이터와 제너레이터
    - 반복 가능한 객체와 함수 제어

    ```javascript
    // 이터레이터
    const iterable = {
        [Symbol.iterator]() {
            let i = 0;
            return {
                next() {
                    if (i < 3) {
                        return { value: i++, done: false };
                    }
                    return { done: true };
                }
            };
        }
    };

    for (const num of iterable) {
        console.log(num); // 0, 1, 2
    }

    // 제너레이터
    function* numberGenerator() {
        yield 1;
        yield 2;
        yield 3;
    }

    const gen = numberGenerator();
    console.log(gen.next().value); // 1
    console.log(gen.next().value); // 2
    ```

13. Object.assign() 및 Object.entries()
    - 객체 조작을 위한 메서드

    ```javascript
    const obj1 = { a: 1 };
    const obj2 = { b: 2 };
    const merged = Object.assign({}, obj1, obj2);
    console.log(merged); // { a: 1, b: 2 }

    const obj = { x: 1, y: 2 };
    for (const [key, value] of Object.entries(obj)) {
        console.log(`${key}: ${value}`);
    }
    ```

14. Optional Chaning(?.)
    - ES2020에서 도입된 기능으로, 중첩된 객체 속성에 안전하게 접근.

    ```javascript
    const user = {
        address: {
            street: 'Main St'
        }
    };

    console.log(user?.address?.street); // "Main St"
    console.log(user?.contact?.email); // undefined
    ```

15. Nullish Coalescing Operator (??)
    - ES2020에서 도입된 기능으로 null 또는 undefined일 대만 대체값 사용.

    ```javascript
    const value = null;
    const defaultValue = 'Default';

    console.log(value ?? defaultValue); // "Default"
    console.log(0 ?? defaultValue); // 0
    ```

### 에러 처리 ###

에러 처리는 프로그램의 안전성과 신뢰성을 높이는 중요한 부분입니다. JavaScript에서는
다양한 방법으로 에러를 처리하고 디버깅할 수 있습니다.

1. try..catch 문

    - 기본적인 에러 처리 방법입니다.

    ```javascript
    try {
        // 에러가 발생할 수 있는 코드
        throw new Error('An error occurred');
    } catch (error) {
        console.error('Caught an error:', error.message);
    } finally {
        // 항상 실행되는 코드
        console.log('This always runs');
    }
    ```

2. 에러 객체
    - JavaScript에는 여러 내장 에러 타입이 있습니다.

    1. Error: 기본 에러
    2. SyntaxError: 문법 오류
    3. ReferenceError: 잘못된 참조
    4. TypeError: 타입 오류
    5. RangeError: 범위 오류
    6. URIError: URI 관련 오류

    ```javascript
    try {
        const obj = null;
        console.log(obj.property);
    } catch (error) {
        if (error instanceof TypeError) {
            console.error('Type error:', error.message);
        } else {
            console.error('An error occurred:', error.message);
        }
    }
    ```

3. 커스텀 에러
    - 사용자 정의 에러를 만들 수 있습니다.

    ```javascript
    class CustomError extends Error {
        constructor(message) {
            super(message);
            this.name = 'CustomError';
        }
    }

    try {
        throw new CustomError('This is a custom error');
    } catch (error) {
        if (error instanceof CustomError) {
            console.error('Custom error:', error.message);
        } else {
            console.error('An error occurred:', error.message);
        }
    }
    ```

4. 비동기 코드에서의 에러 처리
    - Promise 체인에서의 에러 처리

    ```javascript
    fetchData()
        .then(result => processData(result))
        .then(processed => saveData(processed))
        .catch(error => console.error('An error occurred:', error));
    ```

    - async/await에서의 에러 처리

    ```javascript
    async function fetchAndProcessData() {
        try {
            const result = await fetchData();
            const processed = await processData(result);
            await saveData(processed);
        } catch (error) {
            console.error('An error occurred:', error);
        }
    }
    ```

5. 전역 에러 처리
    - 브라우저 환경에서 처리되지 않은 에러를 잡을 수 있습니다.

    ```javascript
    window.addEventListener('error', function(event) {
        console.error('Uncaught error:', event.error);
    });

    // 또는
    window.onerror = function(message, source, lineno, colno, error) {
        console.error('Uncaught error:', error);
        return true; // 브라우저의 기본 에러 처리를 막음
    };
    ```

    - Node.js 환경에서는
    
    ```javascript
    process.on('uncaughtException', (error) => {
        console.error('Uncaught exception:', error);
        // 정리 작업 수행
        process.exit(1);
    });
    ```

6. 에러 로깅
    - 개발 환경과 프로덕션 환경에서 다르게 처리할 수 있습니다.

    ```javascript
    function logError(error) {
        if (process.env.NODE_ENV === 'production') {
            // 프로덕션 환경: 에러 로깅 서비스에 보고
            errorLoggingService.report(error);
        } else {
            // 개발 환경: 콘솔에 상세 정보 출력
            console.error('Error details:', error);
        }
    }
    ```

7. 에러 스택 추적
    - 에러 객체의 stack 속성을 사용하여 에러가 발생한 위치를 추적할 수 있습니다.

    ```javascript
    try {
        throw new Error('An error occurred');
    } catch (error) {
        console.error('Error stack trace:', error.stack);
    }
    ```

8. 조건부 에러 발생
    - 특정 조건에서 에러를 발생시킬 수 있습니다.

    ```javascript
    function divide(a, b) {
        if (b === 0) {
            throw new Error('Division by zero');
        }
        return a / b;
    }

    try {
        console.log(divide(10, 0));
    } catch (error) {
        console.error('Error:', error.message);
    }
    ```

9. 에러 다시 던지기
    - catch 블록에서 에러를 처리한 후 다시 던질 수 있습니다.

    ```javascript
    try {
        throw new Error('Original error');
    } catch (error) {
        console.error('Caught an error:', error.message);
        // 에러 수정 또는 로깅 후 다시 던지기
        throw error;
    }
    ```

10. Promise.reject()
    - Promise에서 명시적으로 에러를 발생시킬 수 있습니다.

    ```javascript
    function fetchData() {
        return new Promise((resolve, reject) => {
            if (/* 에러 조건 */) {
                reject(new Error('Failed to fetch data'));
            } else {
                resolve(/* 데이터 */);
            }
        });
    }

    fetchData()
        .then(data => console.log(data))
        .catch(error => console.error('Error:', error.message));
    ```

11. 에러 처리 모범 사례

    1. 구체적인 에러 메시지 사용
    2. 적절한 에러 타입 선택
    3. 에러 처리 로직 분리
    4. 중요한 정보 로깅
    5. 사용자에게 친화적인 에러 메시지 제공
    6. 에러 복구 메커니즘 구현 (가능한 경우)

    ```javascript
    function handleAPIError(error) {
        if (error.response) {
            // 서버가 2xx 범위를 벗어난 상태 코드로 응답
            console.error('API error:', error.response.data);
            console.error('Status:', error.response.status);
        } else if (error.request) {
            // 요청이 이루어졌으나 응답을 받지 못함
            console.error('Network error:', error.request);
        } else {
            // 요청 설정 중 에러 발생
            console.error('Error:', error.message);
        }
        // 사용자에게 친화적인 메시지 표시
        showUserFriendlyError('서비스에 일시적인 문제가 발생했습니다. 잠시 후 다시 시도해 주세요.');
    }

    function showUserFriendlyError(message) {
        // UI에 에러 메시지 표시
    }
    ```

### 정규 표현식 ###

정규 표현식(Regular Expressions, 줄여서 RegEx)은 문자열에서
특정 패턴을 찾거나 매칭하는 데 사용되는 강력한 도구입니다. JavaScript에서는 내장된
RegExp 객체를 통해 정규 표현식을 지원합니다.

1. 정규 표현식 생성
    - 정규 표현식은 두 가지 방법으로 생성할 수 있습니다.

    ```javascript
    // 리터럴 문법
    const regex1 = /pattern/flags;

    // RegExp 객체 생성자
    const regex2 = new RegExp('pattern', 'flags');
    ```

2. 기본 패턴 매칭
    ```javascript
    const text = "The quick brown fox jumps over the lazy dog";
    const pattern = /fox/;

    console.log(pattern.test(text));  // true
    console.log(text.match(pattern)); // ["fox"]
    ```

3. 메타 문자
    - `.`: 임의의 한 문자
    - `^`: 문자열의 시작
    - `$`: 문자열의 끝
    - `*`: 0회 이상 반복
    - `+`: 1회 이상 반복
    - `?`: 0회 또는 1회
    - `{n}`: 정확히 n회 반복
    - `{n,}`: n회 이상 반복
    - `{n,m}`: n외 이상 m회 이하 반복

    ```javascript
    console.log(/^The/.test("The quick brown fox")); // true
    console.log(/fox$/.test("The quick brown fox")); // true
    console.log(/qu.ck/.test("quick")); // true
    console.log(/fo*x/.test("fx")); // true
    console.log(/fo+x/.test("foox")); // true
    ```

4. 문자 클래스
    - `[abc]`: a, b, 또는 c중 하나
    - `[^abc]`: a,b,c를 제외한 모든 문자
    - `[a-z]`: a ~ z까지의 모든 소문자
    - `\d`: 숫자 [0-9]
    - `\w`: 단어 문자 [a-zA-z0-9]
    - `\s`: 공백 문자

    ```javascript
    console.log(/[aeiou]/.test("hello")); // true
    console.log(/[^aeiou]/.test("sky")); // true
    console.log(/\d{3}/.test("123")); // true
    ```

5. 그룹과 캡쳐
    - 괄호 `()`를 사용하여 그룹을 만들고 캡처할 수 있습니다.

    ```javascript
    const phoneRegex = /(\d{3})-(\d{3})-(\d{4})/;
    const phone = "123-456-7890";
    const match = phone.match(phoneRegex);

    console.log(match[1]); // "123"
    console.log(match[2]); // "456"
    console.log(match[3]); // "7890"
    ```

6. 수량자와 탐욕적/비탐욕적 매칭
    - 기본적으로 수량자는 탐욕적입니다. 비탐욕적 매칭을 위해 `?`를 사용합니다.

    ```javascript
    const html = "<div>Hello</div><div>World</div>";
    console.log(html.match(/<div>.*<\/div>/)[0]); // "<div>Hello</div><div>World</div>"
    console.log(html.match(/<div>.*?<\/div>/)[0]); // "<div>Hello</div>"
    ```

7. 전방 탐색과 후방 탐색
    - `(?=...)`: 긍정적 전방 탐색
    - `(?!...)`: 부정적 전방 탐색
    - `(?<=...)`: 긍정적 후방 탐색 (ES2018+)
    - `(?<!...)`: 부정적 후방 탐색 (ES2018+)

    ```javascript
    console.log("1234".match(/\d+(?=\d)/)[0]); // "123"
    console.log("1234".match(/\d+(?!\d)/)[0]); // "1234"
    console.log("$123".match(/(?<=\$)\d+/)[0]); // "123"
    console.log("123".match(/(?<!\$)\d+/)[0]); // "123"
    ```

8. 플래그
    - `g`: 전역 검색
    - `i`: 대소문자 구분 없음
    - `m`: 다중 행 모드
    - `s`: dotAll 모드 (ES2018+)
    - `u`: 유니코드 모드
    - `y`: sticky 모드

    ```javascript
    const text = "Hello hello HELLO";
    console.log(text.match(/hello/gi)); // ["Hello", "hello", "HELLO"]
    ```

9. 정규 표현식과 메서드
    - String 메서드

        - `match()`: 매칭되는 부분을 찾아 배열로 반환
        - `replace()`: 매칭되는 부분을 다른 문자열로 교체
        - `search()`: 매칭되는 부분의 인덱스를 반환
        - `split()`: 정규 표현식을 구분자로 사용하여 문자열을 분할

        ```javascript
        const str = "The quick brown fox";
        console.log(str.match(/quick/)); // ["quick"]
        console.log(str.replace(/quick/, "slow")); // "The slow brown fox"
        console.log(str.search(/brown/)); // 10
        console.log(str.split(/\s/)); // ["The", "quick", "brown", "fox"]
        ```

    - RegExp 메서드

        - `test()`: 매칭되는 부분이 있으면 true, 없으면 false 반환
        - `exec()`: 매칭되는 정보를 담은 배열 반환

        ```javascript
        const regex = /fox/;
        console.log(regex.test("The quick brown fox")); // true
        console.log(regex.exec("The quick brown fox")); // ["fox", index: 16, input: "The quick brown fox", groups: undefined]
        ```

10. 정규 표현식 예제

    1. 이메일 주소 유효성 검사:
    ```javascript
    const emailRegex = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    console.log(emailRegex.test("example@email.com")); // true
    ```

    2. URL 추출:
    ```javascript
    const text = "Visit https://www.example.com and http://another.com";
    const urlRegex = /https?:\/\/[^\s]+/g;
    console.log(text.match(urlRegex)); // ["https://www.example.com", "http://another.com"]
    ```

    3. HTML 태그 제거:
    ```javascript
    const html = "<p>This is <b>bold</b> text</p>";
    console.log(html.replace(/<[^>]+>/g, '')); // "This is bold text"
    ```

    4. 비밀번호 강도 검사:
    ```javascript
    const strongPasswordRegex = /^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,}$/;
    console.log(strongPasswordRegex.test("StrongP@ssw0rd")); // true
    ```

11. 성능 고려사항

    - 과도하게 복잡한 정규 표현식은 성능 문제를 일으킬 수 있습니다.
    - 가능한 경우 정규 펴현식 대신 문자열 메서드를 사용하는 것이 더 빠를 수 있습니다.
    - 반복적으로 사용되는 정규 표현식은 변수에 저장하여 재사용하세요.

    ```javascript
    // 비효율적
    for (let i = 0; i < 1000; i++) {
        /complex regex/.test(someString);
    }

    // 효율적
    const regex = /complex regex/;
    for (let i = 0; i < 1000; i++) {
        regex.test(someString);
    }
    ```

### 함수형 프로그래밍 ###

함수형 프로그래밍은 프로그램 구조와 요소를 구성하는 데 수학적 함수의 개념을 사용하는 프로그래밍 패러다임입니다.
JavaScript는 함수형 프로그래밍을 지원하는 다중 패러다임 언어입니다.

1. 함수형 프로그래밍의 핵심 개념

    1. 순수 함수
        - 순수 함수는 동일한 입력에 대해 항상 동일한 출력을 반환하며, 부작용(side effects)이 없는 함수입니다.

        ```javascript
        // 순수 함수
        function add(a, b) {
            return a + b;
        }

        // 비순수 함수 (외부 상태에 의존)
        let c = 0;
        function addWithSideEffect(a, b) {
            c++;
            return a + b + c;
        }
        ```

    2. 불변성
        - 함수형 프로그래밍에서는 데이터의 불변성을 중요시합니다.

        ```javascript
        // 불변성을 지키지 않는 예
        const arr = [1, 2, 3];
        arr.push(4); // 원본 배열 변경

        // 불변성을 지키는 예
        const newArr = [...arr, 4]; // 새로운 배열 생성
        ```

    3. 고차 함수
        - 고차 함수는 함수를 인자로 받거나 함수를 반환하는 함수입니다.

        ```javascript
        function multiplyBy(factor) {
            return function(number) {
                return number * factor;
            }
        }

        const double = multiplyBy(2);
        console.log(double(5)); // 10
        ```

2. JavaScript의 함수형 프로그래밍 기능

    1. map, filter, reduce
        - 이 메서드들은 배열을 변환하거나 처리하는 데 사용되는 대표적인 함수형 프로그래밍 도구입니다.

        ```javascript
        const numbers = [1, 2, 3, 4, 5];

        // map: 각 요소를 변환
        const doubled = numbers.map(n => n * 2);

        // filter: 조건에 맞는 요소만 선택
        const evens = numbers.filter(n => n % 2 === 0);

        // reduce: 배열을 단일 값으로 축소
        const sum = numbers.reduce((acc, n) => acc + n, 0);

        console.log(doubled); // [2, 4, 6, 8, 10]
        console.log(evens);   // [2, 4]
        console.log(sum);     // 15
        ```

    2. 함수 합성
        - 여러 함수를 조합하여 새로운 함수를 만드는 기법입니다.

        ```javascript
        const compose = (...fns) => x => fns.reduceRight((y, f) => f(y), x);

        const addOne = x => x + 1;
        const double = x => x * 2;
        const addOneThenDouble = compose(double, addOne);

        console.log(addOneThenDouble(3)); // 8
        ```

    3. 커링
        - 여러 개의 인자를 받는 함수를 하나의 인자만 받는 함수들의 체인으로 변환하는 기법입니다.

        ```javascript
        const curry = (fn) => {
            return function curried(...args) {
                if (args.length >= fn.length) {
                    return fn.apply(this, args);
                } else {
                    return function(...args2) {
                        return curried.apply(this, args.concat(args2));
                    }
                }
            };
        }

        const add = curry((a, b, c) => a + b + c);
        console.log(add(1)(2)(3)); // 6
        console.log(add(1, 2)(3)); // 6
        ```

3. 함수형 프로그래밍의 장점
    1. 코드의 가독성과 유지보수성 향상
    2. 테스트와 디버깅이 용이함
    3. 병렬 처리에 적합
    4. 부작용을 줄여 예측 가능한 코드 작성 가능

4. 실제 예제
    1. 데이터 처리 파이프라인

    ```javascript
    const people = [
        { name: 'Alice', age: 25 },
        { name: 'Bob', age: 30 },
        { name: 'Charlie', age: 35 },
        { name: 'David', age: 40 }
    ];

    const pipeline = compose(
        (people) => people.filter(p => p.age > 30),
        (people) => people.map(p => p.name),
        (names) => names.join(', ')
    );

    console.log(pipeline(people)); // "Charlie, David"
    ```

    2. 함수형 방식으로 상태 관리(Redux 예시)

    ```javascript
    const createStore = (reducer) => {
        let state;
        let listeners = [];

        const getState = () => state;

        const dispatch = (action) => {
            state = reducer(state, action);
            listeners.forEach(listener => listener());
        };

        const subscribe = (listener) => {
            listeners.push(listener);
            return () => {
                listeners = listeners.filter(l => l !== listener);
            };
        };

        dispatch({});

        return { getState, dispatch, subscribe };
    };

    // 사용 예
    const countReducer = (state = 0, action) => {
        switch (action.type) {
            case 'INCREMENT':
                return state + 1;
            case 'DECREMENT':
                return state - 1;
            default:
                return state;
        }
    };

    const store = createStore(countReducer);

    store.subscribe(() => console.log(store.getState()));

    store.dispatch({ type: 'INCREMENT' }); // 1
    store.dispatch({ type: 'INCREMENT' }); // 2
    store.dispatch({ type: 'DECREMENT' }); // 1
    ```

5. 함수형 프로그래밍 라이브러리

- JavaScript에서 함수형 프로그래밍을 더 쉽게 적용할 수 있도록 도와주는 라이브러리들이 있습니다:

    1. Ramda: 순수 함수형 프로그래밍을 위한 실용적인 도구 모음
    2. Ladash/FP: Lodash의 함수형 프로그래밍 변형
    3. Immutable.js: 불변 데이터 구조를 제공하는 라이브러리

    ```javascript
    // Ramda 예제
    const R = require('ramda');

    const numbers = [1, 2, 3, 4, 5];
    const doubleOddNumbers = R.pipe(
        R.filter(n => n % 2 !== 0),
        R.map(n => n * 2)
    );

    console.log(doubleOddNumbers(numbers)); // [2, 6, 10]
    ```

### 테스팅 ###

소프트웨어 테스팅은 프로그램의 품질을 보장하고 버그를 찾아내는 중요한 과정입니다.
JavaScript에서는 다양한 테스팅 도구와 프레임워크를 사용할 수 있습니다.

1. 테스트 유형
    1. 단위 테스트:
        - 개별 함수나 컴포넌트의 동작을 검증합니다.

    2. 통합 테스트:
        - 여러 컴포넌트나 모듈이 함께 작동하는 방식을 테스트합니다.

    3. 엔드-투-엔드 (E2E)테스트
        - 실제 사용자 시나리오를 시뮬레이션하여 전체 애플리케이션을 테스트합니다.

2. 테스팅 프레임워크
    1. Jest
        - Facebook에서 개발한 JavaScript 테스팅 프레임워크로, 단위 테스트와 통합 테스트에 주로 사용됩니다.

        ```javascript
        // sum.js
        function sum(a, b) {
            return a + b;
        }
        module.exports = sum;

        // sum.test.js
        const sum = require('./sum');

        test('adds 1 + 2 to equal 3', () => {
            expect(sum(1, 2)).toBe(3);
        });
        ```

    2. Mocha
        -  유연한 JavaScript 테스트 프레임워크로, Node.js와 브라우저에서 모두 실행 가능합니다.

        ```javascript
        const assert = require('assert');

        describe('Array', function() {
            describe('#indexOf()', function() {
                it('should return -1 when the value is not present', function() {
                    assert.equal([1, 2, 3].indexOf(4), -1);
                });
            });
        });
        ```

    3. Jasmine
        - 행동 주도 개발(BDD) 스타일의 테스팅 프레임워크입니다.

        ```javascript
        describe("A suite", function() {
            it("contains spec with an expectation", function() {
                expect(true).toBe(true);
            });
        });
        ```

3. assertion 라이브러리
    1. Chai
        - TDD, BDD, Assert 스타일을 지원하는 assertion 라이브러리입니다.

        ```javascript
        const expect = require('chai').expect;

        describe('Array', function() {
            it('should start empty', function() {
                const arr = [];
                expect(arr).to.be.empty;
            });
        });
        ```

4. 모킹 (Mocking)
    - 외부 의존성을 시뮬레이션하여 테스트를 격리시킵니다.

    1. Sinon.JS
        - 독립적인 테스트 스파이, 스텁, 목을 제공합니다.

        ```javascript
        const sinon = require('sinon');

        describe('User', function() {
            it('should call save once', function() {
                const user = new User('John');
                const saveSpy = sinon.spy(user, 'save');
                
                user.saveAndNotify();
                
                sinon.assert.calledOnce(saveSpy);
            });
        });
        ```

5. 코드 커버리지
    - 테스트가 코드베이스의 얼마나 많은 부분을 실행하는지 측정합니다.

    1. Istanbul
        - JavaScript 코드 커버리지 도구입니다.

        ```bash
        nyc mocha tests/
        ```

6. 브라우저 테스팅
    1. Selenium WebDriver
        - 브라우저 자동화 도구로, 다양한 브라우저에서 테스트를 실행할 수 있습니다.

        ```javascript
        const {Builder, By, Key, until} = require('selenium-webdriver');

        (async function example() {
            let driver = await new Builder().forBrowser('firefox').build();
            try {
                await driver.get('http://www.google.com');
                await driver.findElement(By.name('q')).sendKeys('webdriver', Key.RETURN);
                await driver.wait(until.titleIs('webdriver - Google Search'), 1000);
            } finally {
                await driver.quit();
            }
        })();
        ```

    2. Cypress
        - 현대적인 웹 애플리케이션을 위한 E2E 테스팅 도구입니다.

        ```javascript
        describe('My First Test', () => {
            it('Visits the Kitchen Sink', () => {
                cy.visit('https://example.cypress.io')
                cy.contains('type').click()
                cy.url().should('include', '/commands/actions')
                cy.get('.action-email')
                    .type('fake@email.com')
                    .should('have.value', 'fake@email.com')
            })
        })
        ```

7. 컴포넌트 테스팅
    1. React Testing Library
        - React 컴포넌트를 테스트하기 위한 라이브러리입니다.

        ```javascript
        import { render, screen } from '@testing-library/react';
        import userEvent from '@testing-library/user-event';
        import '@testing-library/jest-dom';
        import Fetch from './Fetch';

        test('loads and displays greeting', async () => {
            render(<Fetch url="/greeting" />);

            await screen.findByRole('heading');

            expect(screen.getByRole('heading')).toHaveTextContent('hello there');
            expect(screen.getByRole('button')).toBeDisabled();
        });
        ```

8. 성능 테스팅
    1. Lighthouse
        - 웹 앱의 성능, 접근성, 프로그레시브 웹 앱 기능 등을 측정하는 도구입니다.

        ```bash
        lighthouse https://www.example.com
        ```

9. API 테스팅
    1. Supertest
        - HTTP assertion을 쉽게 만들 수 있게 해주는 라이브러리입니다.

        ```javascript
        const request = require('supertest');
        const express = require('express');

        const app = express();

        app.get('/user', function(req, res) {
            res.status(200).json({ name: 'john' });
        });

        request(app)
            .get('/user')
            .expect('Content-Type', /json/)
            .expect('Content-Length', '15')
            .expect(200)
            .end(function(err, res) {
                if (err) throw err;
            });
        ```

10. 테스트 주도 개발 (TDD)
    - 테스트를 먼저 작성한 후 실제 코드를 구현하는 개발 방법론입니다.

    1. 실패하는 테스트 작성
    2. 테스트를 통과하는 최소한의 코드 작성
    3. 리팩토링

    ```javascript
    // 1. 실패하는 테스트 작성
    test('reverseString reverses a string', () => {
        expect(reverseString('hello')).toBe('olleh');
    });

    // 2. 테스트를 통과하는 코드 작성
    function reverseString(str) {
        return str.split('').reverse().join('');
    }

    // 3. 리팩토링 (필요한 경우)
    ```

### 프로토타입 (Prototype) ###

1. 프로토타입의 개념
    - 프로토타입은 JavaScript의 핵심 개념 중 하나로, 객체 지향 프로그래밍의 상속을 구현하는 메커니즘입니다.

    1. JavaScript에서 프로토타입의 정의
        - 프로토타입은 객체의 원형이 되는 객체입니다. 모든 JavaScript 객체는 다른 객체를 가리키는 내부 링크를 가지고 있으며,
        이 링크가 가리키는 객체를 해당 객체의 프로토타입이라고 합니다.

        ```javascript
        let animal = {
            eats: true
        };

        let rabbit = {
            jumps: true
        };

        rabbit.__proto__ = aniaml; // rabbit의 프로토타입을 animal로 변경

        console.log(rabbit.eats); // true
        console.log(rabbit.jumps); // true
        ```

        - 이 예제에서 `rabbit`객체는 `animal` 객체를 프로토타입으로 가집니다. 따라서 `rabbit` 객체는 `animal`객체의 속성을 받아서 사용할 수 있습니다.

    2. 객체 지향 프로그래밍에서의 프로토타입의 역할
        - 프로토타입은 객체 지향 프로그래밍에서 상속을 구현하는 방법을 제공합니다. 이를 통해 코드 재사용성을 높이고, 메모리 사용을 효율적으로 만들 수 있습니다.

        ```javascript
        function Animal(name) {
            this.name = name;
        }

        Animal.prototype.speak = function() {
            console.log(this.name + ' makes a noise.');
        };

        let dog = new Animal('Rex');
        dog.speak(); // "Rex makes a noise."
        ```

        - 이 예제에서 `speak`메서드는 `Animal.prototype`에 정의되어 있습니다. 이렇게 하면 `Animal` 생성자로 만든 모든 객체가 `speak` 메서드를 공유할 수 있어, 메모리 사용이 효율적입니다.

    3. 프로토타입 기반 언어로서의 JavaScript
        - JavaScript는 클래스 기반 언어가 아닌 프로토타입 기반 언어입니다. ES6에서 도입된 `class`문법은 사실 프로토타입 기반 상속의 문법적 설탕(syntactic sugar)에 불가합니다.

        ```javascript
        // ES6 클래스 문법
        class Animal {
            constructor(name) {
                this.name = name;
            }

            speak() {
                console.log(this.name + ' makes a noise.');
            }
        }

        // 위 클래스는 내부적으로 다음과 같이 동작합니다
        function Animal(name) {
            this.name = name;
        }

        Animal.prototype.speak = function() {
            console.log(this.name + ' makes a noise.');
        };
        ```

    - 이처럼 JavaScript의 모든 객체 지향적 특징은 프로토타입을 기반으로 구현됩니다. 프로토타입 체인을 통해 객체는 다른 객체의 속성과 메서드를 상속받을 수 있으며, 이는 JavaScript의 유연성과 강력함의 근간이 됩니다.

2. 프로토타입 객체
    - 프로토타입 객체는 JavaScript에서 객체 간 상속을 구현하는 메커니즘의 핵심입니다. 모든 JavaScript 객체는 프로토타입 객체를 가지며, 이를 통해 속성과 메서드를 상속받습니다.

    1. 모든 객체의 [[Prototype]] 내부 슬롯
        - 모든 JavaScript 객체는 `[[Prototype]]`이라는 내부 슬롯을 가집니다. 이 슬롯은 객체의 프로토타입을 가리키며, 객체 생성 시 자동으로 설정됩니다.

        ```javascript
        let obj = {};
        console.log(Object.getPrototypeOf(obj) === Object.prototype); // true
        ```

        - 여기서 `Object.getPrototypeOf()`메서드는 객체의 `[[Prototype]]`을 반환합니다.

    2. 객체 리터럴로 생성된 객체의 프로토타입
        - 객체 리터럴로 생성된 객체의 프로토타입은 `Object.prototype`입니다.
        
        ```javascript
        let obj = {x: 10, y: 20};
        console.log(obj.__proto__ === Object.prototype); // true
        ```

        - `__proto__`는 `[[Prototype]]`에 접근하기 위한 접근자 프로퍼티입니다. 그러나 최신 JavaScript에서는 `Object.getPrototypeOf()`와 `Object.setPrototypeOf()`메서드를 사용하는 것이 권장됩니다.

    3. 생성자 함수로 생성된 객체의 프로토타입
        - 생성자 함수로 생성된 객체의 프로토타입은 해당 생성자 함수의 `prototype`프로퍼티가 가리키는 객체입니다.

        ```javascript
        function Person(name) {
            this.name = name;
        }

        Person.prototype.sayHello = function() {
            console.log(`Hello, I'm ${this.name}`);
        };

        let person1 = new Person(Alice);
        console.log(Object.getPrototypeOf(person1) === Person.prototype) // true
        person1.sayHello(); // "Hello, I`m Alice"
        ```

        - 이 예제에서 `person`객체는 `Person.prototype`을 포로토타입으로 가집니다. 따라서 `Person.prototype`에 정의된 `sayHello`메서드를 상속받아 사용할 수 있습니다.

    4. 프로토타입 체인
        - 객체의 프로퍼티나 메서드에 접근할 때, JavaScript 엔진은 먼저 객체 자체에서 해당 프로퍼티나 메서드를 찾습니다. 찾지 못하면 객체의 프로토타입에서 찾고, 거기에서도 찾지 못하면 프로토타입의 프로토타입에서 찾는 식으로 계속 탐색합니다. 이를 프로토타입 체인이라고 합니다.

        ```javascript
        let obj = {a: 1};
        console.log(obj.toString()); // "[object Object]"
        ```

        - 여기서 `obj`객체는 `toString`메서드를 직접 가지고 있지 않지만, 프로토타입 체인을 통해 `Object.prototype`의 `toString`메서드를 사용할 수 있습니다.

3. 프로토타입 체인
    - 프로토타입 체인은 JavaScript에서 객체 간의 상속을 구현하는 메커니즘입니다. 이를 통해 객체는 자신이 직접 정의하지 않은 속성과 메서드에 접근할 수 있습니다.

    1. 프로토타입 체인의 개념
        - 프로토타입 체인은 객체의 프로토타입을 따라 연결된 일련의 객체들을 의미합니다. 각 객체는 다른 객체를 프로토타입으로 가질 수 있으며, 이 프로토타입 역시 자신의 프로토타입을 가질 수 있습니다.

        ```javascript
        let animal = {
            eats: true
        };

        let rabbit = {
            jumps: true
        };

        rabbit.__proto__ = animal;

        console.log(rabbit.eats);  // true
        console.log(rabbit.jumps); // true
        ```

        - 이 예제에서 `rabbit`은 `aniaml`을 프로토타입을오 가집니다. 따라서 `rabbit`은 `animal`의 속성을 상속받아 사용할 수 있습니다.

    2. 프로퍼티 검색 과정에서의 프로토타입 체인 동작
        - JavaScript 엔진이 객체의 프로퍼티를 찾는 과정은 다음과 같습니다:

            1. 객체 자체에서 프로퍼티를 찾습니다.
            2. 찾지 못하면 객체의 프로토타입에서 찾습니다.
            3. 프로토타입에서도 찾지 못하면 프로토타입의 프로토타입에서 찾습니다.
            4. 이 과정을 프로토타입 체인의 끝 (보통 `Object.prototype`)까지 반복합니다.
            5. 끝까지 찾지 못하면 `undefined`를 반환합니다.

        ```javascript
        let animal = {
            eats: true
        };

        let rabbit = {
            jumps: true
        };

        rabbit.__proto__ = animal;

        let longEar = {
            earLength: 10
        };

        longEar.__proto__ = rabbit;

        console.log(longEar.jumps);  // true (rabbit에서 상속)
        console.log(longEar.eats);   // true (animal에서 상속)
        console.log(longEar.bark);   // undefined
        ```

    3. Object.prototype과 프로토타입 체인의 종점
        - 모든 객체의 프로토타입 체인은 궁극적으로 `Object.prototype`에서 끝납니다.
        - `Object.prototype`은 프로토타입 체인의 종점으로, 그 자체의 프로토타입은 `null`입니다.

        ```javascript
        console.log(Object.prototype.__proto__ === null);  // true
        ```

        - `Object.prototype`은 모든 객체가 상속받는 메서드들(예: `toString()`, `hasOwnProperty()` 등)을 제공합니다.

        ```javascript
        let obj = {};
        console.log(obj.toString());  // [object Object]
        console.log(obj.hasOwnProperty('toString'));  // false
        console.log(Object.prototype.hasOwnProperty('toString'));  // true
        ```

4. 프로토타입 접근 방법
    - JavaScript에서는 객체의 프로토타입에 접근하고 조작하는 여러 방법이 있습니다. 각 방법은 특정 상황에 적합하며, 일부는 레거시 코드에서 사용되거나 권장되지 않는 방법도 있습니다.

    1. proto 접근자 프로퍼티 (deprecated)
        - `__proto__` 접근자 프로퍼티는 객체의 프로토타입에 직접 접근할 수 있게 해줍니다. 그러나 이 방법은 현재 deprecated(사용 권장되지 않음)상태입니다.

        ```javascript
        let animal = {
            eats: true
        };

        let rabbit = {
            jumps: true
        };

        console.log(rabbit.__proto__);  // {constructor: ƒ, __defineGetter__: ƒ, …}
        rabbit.__proto__ = animal;
        console.log(rabbit.eats);  // true
        ```

        - `__proto__`는 브라우저 환경에서 널리 지원되지만, 최신 JavaScript 표준에서는 이 방법 대신 다른 방법을 사용하도록 권장하고 있습니다.

    2. Object.getPrototypeOf()와 Object.setPrototypeOf() 메서드
        - 이 메서드들은 객체의 프로토타입을 안전하게 가져오거나 설정할 수 있는 현대적인 방법입니다.

        ```javascript
        let animal = {
            eats: true
        };

        let rabbit = {
            jumps: true
        };

        console.log(Object.getPrototypeOf(rabbit));  // {constructor: ƒ, __defineGetter__: ƒ, …}
        Object.setPrototypeOf(rabbit, animal);
        console.log(rabbit.eats);  // true
        ```

        - 이 방법은 `__proto__`보다 안전하고 표준화되어 있어 권장됩니다.

    3. 생성자 함수의 prototype 프로퍼티
        - 생성자 함수는 `prototype` 프로퍼티를 통해 생성될 인스턴스의 프로토타입을 설정할 수 있습니다.

        ```javascript
        function Animal(name) {
            this.name = name;
        }

        Animal.prototype.eats = true;

        let rabbit = new Animal('White Rabbit');
        console.log(rabbit.eats);  // true
        ```

        - `new`연산자로 객체를 생성할 때, 생성된 객체의 `[[Prototype]]`은 생성자 함수의 `prototype`프로퍼티가 가리키는 객체로 설정됩니다.

    4. Object.create() 메서드
        - `Object.create()`메서드는 지정된 프로토타입 객체와 프로퍼티를 갖는 새 객체를 생성합니다.

        ```javascript
        let animal = {
            eats: true
        };

        let rabbit = Object.create(animal);
        rabbit.jumps = true;

        console.log(rabbit.eats);  // true
        console.log(rabbit.jumps);  // true
        ```

        - 이 방법은 객체를 생성하면서 동시에 프로토타입을 설정할 수 있어 유용합니다.

    5. 프로토타입 접근 시 주의사항
        1. 성능: 프로토타입 체인을 따라 프로퍼티를 찾는 것은 직접 객체에서 찾는 것보다 느릴 수 있습니다.
        2. 보안: `Object.setPrototypeOf()`나 `__proto__`를 사용해 프로토타입을 변경하는 것은 성능에 악영향을 줄 수 있으며, 예기치 않은 동작을 일으킬 수 있습니다.
        3. 표준: 최신 JavaScript 표준을 따르는 것이 좋습니다. `Object.getPrototypeOf()`, `Object.setPrototypeOf()`를 사용하는 것이 권장됩니다.

5. 프로토타입 상속
    - 프로토타입 상속은 JavaScript에서 객체 지향 프로그래밍의 핵심 메커니즘입니다. 이를 통해 객체는 다른 객체의 속성과 메서드를 상속받아 재사용할 수 있습니다.

    1. 상속의 구현 방식으로서의 프로토타입
        - JavaScript에서 상속은 프로토타입 체인을 통해 구현됩니다. 객체는 자신의 프로토타입 객체의 속성과 메서드를 상속받습니다.

        ```javascript
        let animal = {
            eats: true,
            walk() {
                console.log("Animal walks");
            }
        };

        let rabbit = {
            jumps: true
        };

        rabbit.__proto__ = animal; // rabbit이 animal을 상속받음

        console.log(rabbit.eats); // true
        rabbit.walk(); // "Animal walks"
        ```

        - 이 예제에서 `rabbit`은 `animal`의 속성과 메서드를 상속받아 사용할 수 있습니다.

    2. Object.create()를 이용한 프로토타입 상속
        - `Object.create()` 메서드는 지정된 프로토타입 객체와 속성을 갖는 새 객체를 생성합니다. 이 방법은 프로토타입 상속을 구현하는 현대적이고 권장되는 방법입니다.

        ```javascript
        let animal = {
            eats: true,
            walk() {
                console.log("Animal walks");
            }
        };

        let rabbit = Object.create(animal);
        rabbit.jumps = true;

        console.log(rabbit.eats); // true
        rabbit.walk(); // "Animal walks"
        console.log(rabbit.jumps); // true
        ```

        - `Object.create()`를 사용하면 새 객체를 생성하면서 동시에 프로토타입을 설정할 수 있습니다.

    3. 프로토타입 체인을 통한 메서드 공유
        - 프로토타입 상속의 주요 이점 중 하나는 메서드를 공유할 수 있다는 점입니다. 이는 메모리 사용을 효율적으로 만듭니다.

        ```javascript
        function Animal(name) {
            this.name = name;
        }

        Animal.prototype.walk = function() {
            console.log(`${this.name} walks`);
        };

        function Rabbit(name) {
            Animal.call(this, name);
        }

        Rabbit.prototype = Object.create(Animal.prototype);
        Rabbit.prototype.constructor = Rabbit;

        Rabbit.prototype.jump = function() {
        console.log(`${this.name} jumps`);
        };

        let rabbit = new Rabbit("White Rabbit");
        rabbit.walk(); // "White Rabbit walks"
        rabbit.jump(); // "White Rabbit jumps"
        ```

        - 이 예제에서 `Rabbit`은 `Animal`을 상속받습니다. `walk` 메서드는 `Animal.prototype`에 정의되어 있지만, `Rabbit`인스턴스에서도 사용할 수 있습니다.

    4. 상속과 프로토타입 체인의 주의사항
        1. 프로토타입 체인의 깊이: 프로토타입 체인이 너무 길어지면 성능에 영향을 줄 수 있습니다.
        2. 프로퍼티 섀도잉: 하위 객체에서 상위 객체의 프로퍼티와 같은 이름의 프로퍼티를 정의하면, 하위 객체의 프로퍼티가 상위 객체의 프로퍼티를 가립니다.
        3. 프로토타입 수정: 프로토타입을 직접 수정하면 해당 프로토타입을 상속받는 모든 객체에 영향을 줄 수 있습니다.