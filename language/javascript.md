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