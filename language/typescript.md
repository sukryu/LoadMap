# TypeScript 언어 #

## TypeScript란? ##

TypeScript는 Microsoft에서 개발하고 유지보수하는 오픈 소스 프로그래밍 언어입니다. 2012년에 처음 공개되었으며,
JavaScript의 상위 집합 (superset)으로 설계되었습니다. 이는 모든 유효한 JavaScript코드가 유요한 TypeScript 코드라는 것을 의미합니다.

## TypeScript의 주요 특징 ##

1. 정적 타입 지원: TypeScript는 JavaScript에 선택적 정적 타입 시스템을 추가합니다. 이를 통해 개발자는 변수, 함수, 함수 매개변수, 반환 값 등에
타입을 명시할 수 있습니다.

2. 객체 지향 프로그래밍 가능: 클래스, 인터페이스, 모듈 등 객체 지향 프로그래밍을 위한 다양한 기능을 제공합니다.

3. 컴파일 시간 오류 검출: TypeScript 컴파일러는 코드를 JavaScript로 변환하는 과정에서 타입 관련 오류를 검출합니다.

4. 향상된 IDE 지원: 타입 정보를 바탕으로 더 나은 코드 자동 완성, 리팩토링, 네비게이션 기능을 제공합니다.

5. ECMAScript 호환성: 최신 ECMAScript 표준을 지원하며, 일부 경우 표준화 이전의 기능도 사용할 수 있습니다.

## TypeScript vs JavaScript ##

TypeScript와 JavaScript의 주요 차이점을 이해하는 것은 중요합니다.

1. 타입 시스템:
    - JavaScript: 동적 타입 언어로, 변수의 타입이 런타임에 결정됩니다.
    - TypeScript: 정적 타입 언어로, 컴파일 시점에 타입을 체크합니다.

2. 오류 검출:
    - JavaScript: 많은 오류가 런타임에만 발견됩니다.
    - TypeScript: 많은 오류를 컴파일 시점에 발견할 수 있습니다.

3. 객체 지향 프로그래밍 지원
    - JavaScript: ES6부터 클래스 문법을 지원하지만, 인터페이스 등의 기능은 없습니다.
    - TypeScript: 인터페이스, 제네릭 등 더 풍부한 객체 지향 프로그래밍 기능을 제공합니다.

4. 도구 지원:
    - JavaScript: 기본적인 IDE 지원을 받습니다.
    - TypeScript: 강력한 타입 추론과 정적 분석 덕분에 더 나은 IDE 지원을 받습니다.

5. 학습 곡선:
    - JavaScript: 상대적으로 배우기 쉽습니다.
    - TypeScript: 타입 시스템과 추가 기능으로 인해 학습 곡선이 더 가파릅니다.

## TypeScript 설치 및 설정 ##

TypeScript를 사용하기 위해서는 Node.js가 설치되어 있어야 합니다.

1. 전역 설치:
    ```bash
    npm install -g typescript
    ```

2. 프로젝트별 설치:
    ```bash
    npm init -y
    npm install typescript --save-dev
    ```

3. TypeScript 설정 파일 (tsconfig.json)생성:
    ```bash
    npx tsx --init
    ```

    이 명령은 기본 `tsconfig.json`파일을 생성합니다. 이 파일에서 TypeScript 컴파일러 옵션을 설정할 수 있습니다.

## 첫 번째 TypeScript 프로그램 ##

간단한 TypeScript 프로그램을 작성하고 실행해 보겠습니다.

1. `hello.ts` 파일 생성:
    ```typescript
    function greet(name: string) {
        return `Hello, ${name}!`;
    }

    let user = "TypeScript Learner";
    console.log(greet(user));
    ```

2. TypeScript 컴파일:
    ```bash
    npx tsx hello.ts
    ```
    이 명령은 hello.js 파일을 생성합니다.

3. 생성된 JavaScript 파일 실행
    ```bash
    node hello.js
    ```
    출력: `Hello, TypeScript Learner!`

## TypeScript 타입 시스템 ##

### 기본 타입 ###

TypeScript는 JavaScript의 타입을 확장하여 더 많은 타입을 제공합니다.

1. boolean: true or false
    ```typescript
    let isDone: boolean = false;
    ```

2. number: 모든 숫자(정수와 실수)
    ```typescript
    let decimal: number = 6;
    let hex: number = 0xf00d;
    let binary: number = 0b1010;
    let octal: number = 0o744;
    ```

3. string: 문자열
    ```typescript
    let color: string = "blue";
    color = 'red';
    ```

4. array: 배열
    ```typescript
    let list: number[] = [1, 2, 3];
    let fruits: Array<string> = ['apple', 'banana', 'orange'];
    ```

5. tuple: 고정된 요소 수와 타입을 가진 배열
    ```typescript
    let x: [string, number];
    x = ["hello", 10]; // OK
    // x = [10, "hello"]; // Error
    ```

6. enum: 열거형
    ```typescript
    enum Color {Red, Green, Blue}
    let c: Color = Color.Green;
    ```

7. any: 어떤 타입이든 허용
    ```typescript
    let notSure: any = 4;
    notSure = "maybe a string instead";
    notSure = false; // 부울값도 OK
    ```

8. void: 주로 함수에서 반환 값이 없음을 나타냄
    ```typescript
    function warnUser(): void {
        console.log("This is my warning message");
    }
    ```

9. null과 undefined
    ```typescript
    let u: undefined = undefined;
    let n: null = null;
    ```

10. never: 절대 발생하지 않는 타입
    ```typescript
    function error(message: string): never {
        throw new Error(message);
    }
    ```

11. object: 원시 타입이 아닌 타입
    ```typescript
    let obj: object = {key: "value"};
    ```

### 타입 추론 ###

TypeScript는 많은 경우 타입을 명시적으로 선언하지 않아도 타입을 추론할 수 있습니다.

```typescript
let x = 3; // x는 number 타입으로 추론됨.
```

### 유니온 타입 ###

변수가 여러 타입 중 하나일 수 있음을 나타냅니다.

```typescript
let multiType: number | string;
multiType = 20; // OK
multiType = "twenty"; // OK
// multiType = true; // Error
```

### 타입 별칭 ###

`type`키워드를 사용하여 타입에 대한 새로운 이름을 만들 수 있습니다.

```typescript
type StringOrNumber = string | number;
let value: StringOrNumber;
value = "hello"; // OK
value = 42; // OK
```

### 인터페이스 ###

객체의 형태를 정의하는 데 사용됩니다.

```typescript
interface Person {
    name: string;
    age: number;
}

let user: Person = {name: "John", age: 30};
```

### 선택적 프로퍼티 ###

프로퍼티 이름 뒤에 `?`를 붙여 선택적 프로퍼티를 정의할 수 있습니다.

```typescript
interface Car {
    make: string;
    model: string;
    year?: number;
}

let myCar: Car = {make: "Toyota", model: "Corolla"};
```

### 읽기 전용 프로퍼티 ###

`readonly` 키워드를 사용하여 프로퍼티를 읽기 전용으로 만들 수 있습니다.

```typescript
interface Point {
    readonly x: number;
    readonly y: number;
}

let p1: Point = { x: 10, y: 20 };
// p1.x = 5; // Error
```

### 함수 타입 ###

함수의 매개변수와 반환 값에 타입을 지정할 수 있습니다.

```typescript
function add(x: number, y: number): number {
    return x + y;
}

let myAdd: (x: number, y: number) => number = 
    function(x: number, y: number): number { return x + y; };
```

### 제네릭 ###

재사용 가능한 컴포넌트를 만들 때 사용됩니다. 다양한 타입에서 작동할 수 있는 컴포넌트를 생성할 수 있습니다.

```typescript
function identity<T>(arg: T): T {
    return arg;
}

let output = identity<string>("myString");
```

### 타입 단언 ###

때로는 개발자가 값의 타입을 컴파일러보다 더 잘 알고 있을 때 사용합니다.

```typescript
let someValue: any = "this is a string";
let strLength: number = (someValue as string).length;
```

### 교차 타입 ###

여러 타입을 하나로 결합합니다.

```typescript
interface ErrorHandling {
    success: boolean;
    error?: { message: string };
}

interface ArtworksData {
    artworks: { title: string }[];
}

type ArtworksResponse = ArtworksData & ErrorHandling;
```

### 조건부 타입 ###

타입 관계 검사에 따라 두 가지 가능한 타입 중 하나를 선택합니다.

```typescript
type TypeName<T> = 
    T extends string ? "string" :
    T extends number ? "number" :
    T extends boolean ? "boolean" :
    T extends undefined ? "undefined" :
    T extends Function ? "function" :
    "object";

type T0 = TypeName<string>;  // "string"
type T1 = TypeName<"a">;  // "string"
type T2 = TypeName<true>;  // "boolean"
```

### 함수 ###

TypeScript에서 함수는 JavaScript와 마찬가지로 프로그램의 기본적인 구성 요소입니다.
하지만 TypeScript는 매개변수와 반환값에 타입을 지정할 수 있어, 더 명확하고 안전한 함수를 작성할 수 있습니다.

1. 함수 선언
    - TypeScript에서 함수를 선언할 때 매개변수와 반환값의 타입을 지정할 수 있습니다.

    ```typescript
    function greet(name: string): string {
        return `Hello, ${name}!`;
    }
    ```

    여기서 `name`은 `string` 타입이어야 하며, 함수는 `string` 타입을 반환해야 합니다.

2. 함수 표현식
    - 함수 표현식에도 타입을 지정할 수 있습니다.

    ```typescript
    let greet: (name: string) => string = function(name: string): string {
        return `Hello, ${name}!`;
    };
    ```

3. 선택적 매개변수와 기본 매개변수
    - TypeScript에서는 선택적 매개변수와 기본 매개변수를 지원합니다.

    ```typescript
    function buildName(firstName: string, lastName?: string): string {
        if (lastName)
            return `${firstName} ${lastName}`;
        else
            return firstName;
    }

    function greet(name: string = "Guest"): string {
        return `Hello, ${name}!`;
    }
    ```

    선택적 매개변수는 매개변수 이름 뒤에 `?`를 붙여 표시합니다. 기본 매개변수는 `=` 기호를 사용하여 기본값을 지정합니다.

4. 나머지 매개변수
    - TypeScript에서도 나머지 매개변수를 사용할 수 있습니다.

    ```typescript
    function sum(...numbers: number[]): number {
        return numbers.reduce((total, n) => total + n, 0);
    }

    console.log(sum(1, 2, 3, 4)); // 출력: 10
    ```

5. 함수 오버로딩
    - TypeScript는 함수 오버로딩을 지원합니다. 이를 통해 같은 이름의 함수를 다양한 매개변수 타입과 반환 타입으로 여러 번 정의할 수 있습니다.

    ```typescript
    function padLeft(value: string, padding: string): string;
    function padLeft(value: string, padding: number): string;
    function padLeft(value: string, padding: string | number): string {
        if (typeof padding === "number") {
            return Array(padding + 1).join(" ") + value;
        }
        if (typeof padding === "string") {
            return padding + value;
        }
        throw new Error(`Expected string or number, got '${padding}'.`);
    }

    console.log(padLeft("Hello", 4));  // 출력: "    Hello"
    console.log(padLeft("Hello", "---"));  // 출력: "---Hello"
    ```

6. this와 화살표 함수
    - TypeScript에서는 `this`의 타입을 명시적으로 지정할 수 있습니다.

    ```typescript
    interface Card {
        suit: string;
        card: number;
    }

    interface Deck {
        suits: string[];
        cards: number[];
        createCardPicker(this: Deck): () => Card;
    }

    let deck: Deck = {
        suits: ["hearts", "spades", "clubs", "diamonds"],
        cards: Array(52),
        createCardPicker: function(this: Deck) {
            return () => {
                let pickedCard = Math.floor(Math.random() * 52);
                let pickedSuit = Math.floor(pickedCard / 13);

                return {suit: this.suits[pickedSuit], card: pickedCard % 13};
            }
        }
    }

    let cardPicker = deck.createCardPicker();
    let pickedCard = cardPicker();

    console.log("card: " + pickedCard.card + " of " + pickedCard.suit);
    ```

7. 제네릭 함수
    - TypeScript의 제네릭을 사용하면 여러 타입에서 작동하는 함수를 만들 수 있습니다.

    ```typescript
    function identity<T>(arg: T): T {
        return arg;
    }

    let output = identity<string>("myString");
    let output2 = identity(42);  // 타입 추론으로 인해 <number>를 명시적으로 지정하지 않아도 됩니다.
    ```

8. 함수의 타입 추론
    - TypeScript는 많은 경우에 함수의 반환 타입을 추론할 수 있습니다.

    ```typescript
    function add(a: number, b: number) {
        return a + b;  // 반환 타입이 number로 추론됩니다.
    }
    ```

9. 고차 함수
    - TypeScript에서도 함수를 인자로 받거나 함수를 반환하는 고차 함수를 작성할 수 있습니다.

    ```typescript
    function greaterThan(n: number): (m: number) => boolean {
        return function(m: number): boolean {
            return m > n;
        }
    }

    let greaterThan10 = greaterThan(10);
    console.log(greaterThan10(11));  // 출력: true
    console.log(greaterThan10(9));   // 출력: false
    ```

### 클래스와 객체 지향 프로그래밍 ###

TypeScript는 클래스 기반의 객체 지향 프로그래밍을 완벽하게 지원합니다. JavaScript의 프로토타입 기반 객체 지향 모델을
확장하여 더 강력하고 안전한 객체 지향 프로그래밍을 가능하게 합니다.

1. 기본 클래스 구문
    - TypeScript에서 기본적인 클래스를 정의하는 방법은 다음과 같습니다.
    
    ```typescript
    class Animal {
        name: string;
        
        constructor(name: string) {
            this.name = name;
        }
        
        move(distanceInMeters: number = 0) {
            console.log(`${this.name} moved ${distanceInMeters}m.`);
        }
    }

    let cat = new Animal("Cat");
    cat.move(10);
    ```

2. 상속
    - TypeScript에서는 클래스 상속을 지원합니다.

    ```typescript
    class Dog extends Animal {
        bark() {
            console.log('Woof! Woof!');
        }
        
        move(distanceInMeters = 5) {
            console.log("Running...");
            super.move(distanceInMeters);
        }
    }

    let dog = new Dog("Dog");
    dog.bark();
    dog.move(10);
    ```

3. 접근 제어자
    - TypeScript는 세 가지 접근 제어자를 제공합니다. `public`, `private`, `protected`

    ```typescript
    class Animal {
        private name: string;
        
        constructor(name: string) { this.name = name; }
        
        public move(distanceInMeters: number) {
            console.log(`${this.name} moved ${distanceInMeters}m.`);
        }
    }
    ```

    - `public`: 어디서나 접근 가능 (기본값)
    - `private`: 해당 클래스 내에서만 접근 가능
    - `protected`: 해당 클래스와 상속받은 클래스에서 접근 가능

4. 읽기 전용 속성
    - `readonly`키워드를 사용하여 읽기 전용 속성을 만들 수 있습니다.

    ```typescript
    class Octopus {
        readonly name: string;
        readonly numberOfLegs: number = 8;
        
        constructor(theName: string) {
            this.name = theName;
        }
    }

    let dad = new Octopus("Man with the 8 strong legs");
    // dad.name = "Man with the 3-piece suit"; // 오류: name은 읽기 전용입니다.
    ```

5. Getter와 Setter
    - TypeScript는 getter와 setter를 통해 객체의 멤버에 대한 접근을 제어할 수 있습니다.

    ```typescript
    class Employee {
        private _fullName: string;

        get fullName(): string {
            return this._fullName;
        }

        set fullName(newName: string) {
            if (newName && newName.length > 3) {
                this._fullName = newName;
            }
            else {
                throw new Error("이름은 3글자보다 길어야 합니다.");
            }
        }
    }

    let employee = new Employee();
    employee.fullName = "Bob Smith";
    ```

6. 정적 속성
    - `static`키워드를 사용하여 클래스의 정적 멤버를 정의할 수 있습니다.

    ```typescript
    class Grid {
        static origin = {x: 0, y: 0};
        
        calculateDistanceFromOrigin(point: {x: number; y: number;}) {
            let xDist = point.x - Grid.origin.x;
            let yDist = point.y - Grid.origin.y;
            return Math.sqrt(xDist * xDist + yDist * yDist) / this.scale;
        }
        
        constructor (public scale: number) { }
    }

    let grid1 = new Grid(1.0);
    let grid2 = new Grid(5.0);
    ```

7. 추상 클래스
    - 추상 클래스는 다른 클래스들이 파생될 수 있는 기본 클래스입니다. 추상 클래스는 직접 인스턴스화할 수 없습니다.

    ```typescript
    abstract class Animal {
        abstract makeSound(): void;
        
        move(): void {
            console.log("roaming the earth...");
        }
    }

    class Dog extends Animal {
        makeSound() {
            console.log("Woof! Woof!");
        }
    }

    // let animal = new Animal(); // 오류: 추상 클래스는 인스턴스화할 수 없습니다
    let dog = new Dog();
    dog.makeSound();
    dog.move();
    ```

8. 인터페이스 구현
    - TypeScript에서 클래스는 인터페이스를 구현할 수 있습니다.

    ```typescript
    interface Pingable {
        ping(): void;
    }

    class Sonar implements Pingable {
        ping() {
            console.log("ping!");
        }
    }
    ```

9. 생성자 매개변수 속성
    - TypeScript에서는 생성자 매개변수에 접근 제어자를 사용하여 자동으로 클래스 속성을 선언하고 초기화할 수 있습니다.

    ```typescript
    class Person {
        constructor(private name: string, public age: number) {}
    }

    // 위 코드는 다음과 동일합니다:
    // class Person {
    //     private name: string;
    //     public age: number;
    //     constructor(name: string, age: number) {
    //         this.name = name;
    //         this.age = age;
    //     }
    // }
    ```

10. 싱글톤 패턴
    - TypeScript에서 싱글톤 패턴을 구현할 수 있습니다.

    ```typescript
    class Singleton {
        private static instance: Singleton;
        private constructor() { }
        
        public static getInstance(): Singleton {
            if (!Singleton.instance) {
                Singleton.instance = new Singleton();
            }
            return Singleton.instance;
        }
    }

    let instance1 = Singleton.getInstance();
    let instance2 = Singleton.getInstance();
    console.log(instance1 === instance2); // true
    ```

### TypeScript 제네릭 ###

제네릭은 TypeScript의 핵심 기능 중 하나로, 타입을 매개변수화하여 재사용 가능하고 유연한 코드를 작성할 수 있게 해줍니다.

1. 제네릭의 기본 개념
    - 제네릭을 사용하면 함수, 클래스, 인터페이스 등에서 사용할 타입을 미리 정하지 않고, 사용 시점에 원하는 타입을 지정할 수 있습니다.

    1. 제네릭 함수
        - 가장 기본적인 제네릭 함수의 예:

        ```typescript
        function identity<T>(arg: T): T {
            return arg;
        }

        let output1 = identity<string>("Hello");  // 타입은 'string'
        let output2 = identity(42);  // 타입 추론으로 'number'
        ```

        여기서 `T`는 타입 변수로, 실제 사용 시 구체적인 타임으로 대체됩니다.

    2. 여러 타입 변수 사용
        - 제네릭은 여러 타입 변수를 사용할 수 있습니다.

        ```typescript
        function pair<T, U>(first: T, second: U): [T, U] {
            return [first, second];
        }

        let p1 = pair<string, number>("hello", 42);  // [string, number]
        let p2 = pair(true, [1, 2, 3]);  // [boolean, number[]]
        ```

2. 제네릭 인터페이스와 타입
    1. 제네릭 인터페이스
        - 인터페이스에도 제네릭을 적용할 수 있습니다.

        ```typescript
        interface Box<T> {
            contents: T;
        }

        let box1: Box<string> = { contents: "hello" };
        let box2: Box<number> = { contents: 42 };
        ```

    2. 제네릭 타입 별칭
        - 타입 별칭에도 제네릭을 사용할 수 있습니다.

        ```typescript
        type Pair<T, U> = {
            first: T;
            second: U;
        };

        let pair: Pair<string, number> = { first: "hello", second: 42 };
        ```

3. 제네릭 클래스
    - 클래스에도 제네릭을 적용할 수 있어, 재사용 가능한 컴포넌트를 만들 수 있습니다.

    ```typescript
    class GenericStack<T> {
        private elements: T[] = [];

        push(element: T): void {
            this.elements.push(element);
        }

        pop(): T | undefined {
            return this.elements.pop();
        }
    }

    let numberStack = new GenericStack<number>();
    numberStack.push(1);
    numberStack.push(2);
    console.log(numberStack.pop());  // 2
    ```

4. 제네릭 제약 조건
    1. extends를 사용한 제약 조건
        - 특정 속성을 가진 타입으로 제네릭을 제한할 수 있습니다.

        ```typescript
        interface Lengthwise {
            length: number;
        }

        function loggingIdentity<T extends Lengthwise>(arg: T): T {
            console.log(arg.length);  // .length 속성이 있음을 보장
            return arg;
        }

        loggingIdentity([1, 2, 3]);  // OK
        loggingIdentity({ length: 10, value: 3 });  // OK
        // loggingIdentity(3);  // Error, number doesn't have a .length property
        ```

    2. 키 제약조건
        - 객체의 속성에 접근할 때 유용한 `keyof` 키워드를 사용한 제약조건

        ```typescript
        function getProperty<T, K extends keyof T>(obj: T, key: K) {
            return obj[key];
        }

        let x = { a: 1, b: 2, c: 3, d: 4 };

        getProperty(x, "a");  // OK
        // getProperty(x, "m");  // Error: Argument of type 'm' isn't assignable to 'a' | 'b' | 'c' | 'd'.
        ```

5. 조건부 타입
    - 조건부 타입을 사용하면 입력 타입에 따라 출력 타입을 결정할 수 있습니다.

    ```typescript
    type TypeName<T> = 
        T extends string ? "string" :
        T extends number ? "number" :
        T extends boolean ? "boolean" :
        T extends undefined ? "undefined" :
        T extends Function ? "function" :
        "object";

    type T0 = TypeName<string>;  // "string"
    type T1 = TypeName<"a">;  // "string"
    type T2 = TypeName<true>;  // "boolean"
    type T3 = TypeName<() => void>;  // "function"
    type T4 = TypeName<string[]>;  // "object"
    ```

    1. 분배 조건부 타입
        - 유니온 타입에 대해 조건부 타입이 분배되어 적용됩니다:

        ```typescript
        type ToArray<T> = T extends any ? T[] : never;

        type StrArrOrNumArr = ToArray<string | number>;  // string[] | number[]
        ```

    2. 매핑된 타입
        - 기존 타입을 바탕으로 새로운 타입을 생성할 수 있습니다.

        ```typescript
        type Readonly<T> = {
            readonly [P in keyof T]: T[P];
        };

        type Partial<T> = {
            [P in keyof T]?: T[P];
        };

        interface Todo {
            title: string;
            description: string;
        }

        type ReadonlyTodo = Readonly<Todo>;
        type PartialTodo = Partial<Todo>;
        ```

7. 제네릭 유틸리티 타입
    - TypeScript는 여러 유용한 제네릭 유틸리티 타입을 제공합니다.

    ```typescript
    // Partial: 모든 속성을 선택적으로 만듦
    type PartialPoint = Partial<{ x: number; y: number }>;  // { x?: number; y?: number; }

    // Required: 모든 속성을 필수로 만듦
    type RequiredPoint = Required<{ x?: number; y?: number }>;  // { x: number; y: number; }

    // Pick: 특정 속성만 선택
    type PickedPoint = Pick<{ x: number; y: number; z: number }, "x" | "y">;  // { x: number; y: number; }

    // Omit: 특정 속성을 제외
    type OmittedPoint = Omit<{ x: number; y: number; z: number }, "z">;  // { x: number; y: number; }

    // Record: 키-값 쌍의 타입 생성
    type PageInfo = { title: string };
    type Page = "home" | "about" | "contact";
    const nav: Record<Page, PageInfo> = {
        home: { title: "Home" },
        about: { title: "About" },
        contact: { title: "Contact" },
    };
    ```

8. 고급 제네릭 패턴
    1. 팩토리 패턴
        - 제네릭을 사용한 팩토리 함수 구현

        ```typescript
        function create<T>(c: { new(): T }): T {
            return new c();
        }

        class Foo {
            constructor() {
                console.log("Foo created");
            }
        }

        let foo = create(Foo);  // "Foo created"
        ```

    2. 믹스인 패턴
        - 제네릭을 사용한 믹스인 구현:

        ```typescript
        type Constructor<T = {}> = new (...args: any[]) => T;

        function Timestamped<TBase extends Constructor>(Base: TBase) {
            return class extends Base {
                timestamp = Date.now();
            };
        }

        class User {
            name: string;
            constructor(name: string) {
                this.name = name;
            }
        }

        const TimestampedUser = Timestamped(User);
        const user = new TimestampedUser("John");
        console.log(user.timestamp);  // Current timestamp
        ```

9. 제네릭의 성능과 최적화
    - 제네릭은 컴파일 시점에 타입 검사를 수행하므로 런타임 성능에는 영향을 주지 않습니다. 그러나 과도한
    사용은 컴파일 시간을 늘릴 수 있으므로 적절히 사용해야 합니다.

10. 제네릭 모범 사례
    1. 명확한 이름 사용: `T`, `U`대신 `TElemnt`, `TKey`등 의미 있는 이름 사용
    2. 제약조건 활용: 가능한 경우 `extends`를 사용하여 타입 제한
    3. 기본 타입 제공: `<T = DefualtType>`와 같이 기본 타입 지정
    4. 과도한 사용 피하기: 간단한 경우에는 유니온 타입 등 다른 방법 고려

### 모듈과 네임스페이스 ###

TypeScript에서 모듈과 네임스페이스는 코드를 구조화하고 관리하는 데 중요한 역할을 합니다.
이들은 코드의 재사용성을 높이고, 이름 충돌을 방지하며, 전체적인 프로젝트 구조를 개선하는 데 도움을 줍니다.

1. 모듈 (Modules)
    - TypeScript의 모듈은 ES6 모듈 시스템을 기반으로 합니다. 각 파일은 자체 스코프를 가진 모듈로 간주됩니다.

    1. 모듈 내보내기 (Exporting)

        ```typescript
        // math.ts
        export function add(x: number, y: number): number {
            return x + y;
        }

        export const PI = 3.14159;

        export interface Circle {
            radius: number;
        }
        ```

    2. 모듈 가져오기 (Importing)

        ```typescript
        // main.ts
        import { add, PI, Circle } from './math';

        console.log(add(2, 3));  // 5
        console.log(PI);  // 3.14159

        const circle: Circle = { radius: 10 };
        ```

    3. 기본 내보내기 (Default Export)

        ```typescript
        // person.ts
        export default class Person {
            constructor(public name: string) {}
        }

        // main.ts
        import Person from './person';

        const john = new Person("John");
        ```

    4. 전체 모듈 가져오기

        ```typescript
        import * as Math from './math';

        console.log(Math.add(2, 3));
        console.log(Math.PI);
        ```

    5. 모듈 재내보내기

        ```typescript
        // index.ts
        export { add, PI } from './math';
        export { default as Person } from './person';
        ```

2. 네임스페이스(Namespaces)
    - 네임스페이스는 TypeScript의 고유 기능으로, 전역 스코프에서 이름 충돌을 방지하는 데 사용됩니다.

    1. 네임스페이스 정의

        ```typescript
        namespace Geometry {
            export interface Point {
                x: number;
                y: number;
            }

            export class Circle {
                constructor(public center: Point, public radius: number) {}

                area(): number {
                    return Math.PI * this.radius ** 2;
                }
            }
        }

        // 사용
        let point: Geometry.Point = { x: 0, y: 0 };
        let circle = new Geometry.Circle(point, 10);
        ```

    2. 네임스페이스 분할
        - 네임스페이스는 여러 파일에 걸쳐 정의될 수 있습니다.

        ```typescript
        // geometry-point.ts
        namespace Geometry {
            export interface Point {
                x: number;
                y: number;
            }
        }

        // geometry-circle.ts
        /// <reference path="geometry-point.ts" />
        namespace Geometry {
            export class Circle {
                constructor(public center: Point, public radius: number) {}

                area(): number {
                    return Math.PI * this.radius ** 2;
                }
            }
        }
        ```

    3. 네임스페이스 별칭

        ```typescript
        import G = Geometry;

        let point: G.Point = { x: 0, y: 0 };
        ```

- 모듈 vs 네임스페이스

    - 모듈은 파일 단위로 동작하며, ES6 모듈 시스템과 호환됩니다.
    - 네임스페이스는 전역 스코프에서 동작하며, TypeScript의 고유 기능입니다.
    - 일반적으로 모던 TypeScript 개발에서는 모듈을 더 많이 사용합니다.

- 모듈 해석 전략
    - TypeScript는 다양한 모듈 해석 전략을 지원합니다.

    1. Classic: Node.js 스타일의 해석 전략
    2. Node: Node.js의 CommonJS 구현을 모방
    3. ESNext: ECMAScript 모듈 해석 알고리즘 사용

    `tsconfig.json`에서 설정할 수 있습니다.

    ```json
    {
        "compilerOptions": {
            "moduleResolution": "node"
        }
    }
    ```

3. 동적 임포트
    - TypeScript2.4 부터 동적 임포트를 지원합니다.

    ```typescript
    async function loadMath() {
        const math = await import('./math');
        console.log(math.add(2, 3));
    }
    ```

4. 모듈 증강 (Module Augumentation)
    - 기존 모듈에 새로운 내용을 추가할 수 있습니다.

    ```typescript
    // 원본 모듈
    declare module "original-module" {
        export function originalFunction(): void;
    }

    // 증강
    declare module "original-module" {
        export function newFunction(): void;
    }

    // 사용
    import { originalFunction, newFunction } from "original-module";
    ```

5. 앰비언트 모듈 선언 (Ambient Module Declarations)
    - TypeScript에서 JavaScript 라이브러리를 사용할 때 유용합니다.

    ```typescript
    // declarations.d.ts
    declare module "some-library" {
        export function doSomething(): void;
    }

    // 사용
    import { doSomething } from "some-library";
    doSomething();
    ```

6. 모범 사례:
    1. 가능한 한 네임스페이스보다는 모듈을 사용하세요.
    2. 하나의 파일에 하나의 모듈만 정의하세요.
    3. 순환 의존성을 피하세요.
    4. 필요한 것만 내보내고 가져오세요.
    5. 상대 경로 대신 절대 경로를 사용하는 것이 좋습니다. (큰 프로젝트의 경우)

### 고급 타입(유니온, 교차 타입, 타입 가드 등) ###

TypeScript는 기본 타입 외에도 복잡한 타입 관계를 표현할 수 있는 고급 타입 기능을 제공합니다.
이러한 고급 타입을 사용하면 더 정확하고 유연한 타입 시스템을 구축할 수 있습니다.

1. 유니온 타입 (Union Types)
    - 여러 타입 중 하나일 수 있는 값을 표현합니다.

    ```typescript
    let result: number | string;
    result = 10;  // OK
    result = "ten";  // OK
    // result = true;  // Error
    ```

2. 교차 타입 (Intersection Types)
    - 여러 타입을 결합합니다.

    ```typescript
    interface Colorful { color: string; }
    interface Circle { radius: number; }

    type ColorfulCircle = Colorful & Circle;

    let cc: ColorfulCircle = {
        color: "red",
        radius: 42
    };
    ```

3. 타입 가드 (Type Guards)
    - 특정 스코프 내에서 타입을 보장합니다.

    ```typescript
    function isString(test: any): test is string {
        return typeof test === "string";
    }

    function example(x: number | string) {
        if (isString(x)) {
            console.log(x.toUpperCase());  // x is treated as string here
        } else {
            console.log(x.toFixed(2));  // x is treated as number here
        }
    }
    ```

4. 조건부 타입 (Conditional Types)
    - 조건에 따라 타입을 결정합니다.

    ```typescript
    type TypeName<T> = 
        T extends string ? "string" :
        T extends number ? "number" :
        T extends boolean ? "boolean" :
        T extends undefined ? "undefined" :
        T extends Function ? "function" :
        "object";

    type T0 = TypeName<string>;  // "string"
    type T1 = TypeName<"a">;  // "string"
    type T2 = TypeName<true>;  // "boolean"
    ```

5. 매핑된 타입 (Mapped Types)
    - 기존 타입을 기반으로 새로운 타입을 생성합니다.

    ```typescript
    type Readonly<T> = {
        readonly [P in keyof T]: T[P];
    };

    interface Point {
        x: number;
        y: number;
    }

    type ReadonlyPoint = Readonly<Point>;
    // { readonly x: number; readonly y: number; }
    ```

6. 인덱스 타입 (Index Types)
    - 객체의 속성 타입을 동적으로 조회합니다.

    ```typescript
    function pluck<T, K extends keyof T>(o: T, names: K[]): T[K][] {
        return names.map(n => o[n]);
    }

    interface Person {
        name: string;
        age: number;
    }

    let person: Person = {
        name: "Jarid",
        age: 35
    };

    let strings: string[] = pluck(person, ['name']);  // ['Jarid']
    ```

7. 제거된 타입 (Exclude, Extract, NonNullable)
    - 유틸리티 타입을 사용하여 타입을 조작합니다.

    ```typescript
    type T0 = Exclude<"a" | "b" | "c", "a">;  // "b" | "c"
    type T1 = Extract<"a" | "b" | "c", "a" | "f">;  // "a"
    type T2 = NonNullable<string | number | null | undefined>;  // string | number
    ```

8. 리터럴 타입 (Literal Types)
    - 특정 문자열, 숫자, 불리언 값을 타입으로 사용합니다.

    ```typescript
    type Easing = "ease-in" | "ease-out" | "ease-in-out";
    type Index = -1 | 0 | 1;
    ```

9. 템플릿 리터럴 타입 (Template Literal Types)
    - 문자열 리터럴 타입을 기반으로 새로운 문자열 타입을 생성합니다.

    ```typescript
    type EmailLocaleIDs = "welcome_email" | "email_heading";
    type FooterLocaleIDs = "footer_title" | "footer_sendoff";

    type AllLocaleIDs = `${EmailLocaleIDs | FooterLocaleIDs}_id`;
    // "welcome_email_id" | "email_heading_id" | "footer_title_id" | "footer_sendoff_id"
    ```

10. 재귀 타입 (Recursive Types)
    - 자기 자신을 참조하는 타입을 정의할 수 있습니다.

    ```typescript
    type JSONValue = string | number | boolean | null | JSONObject | JSONArray;

    interface JSONObject {
        [x: string]: JSONValue;
    }

    interface JSONArray extends Array<JSONValue> { }
    ```

11. 타입 추론 개선 (Improved Type Inference)
    - TypeScript는 복잡한 타입 관계에서도 타입을 정확히 추론합니다.

    ```typescript
    let x = [0, 1, null];  // (number | null)[]

    class Animal { }
    class Rhino extends Animal { }
    class Elephant extends Animal { }
    class Snake extends Animal { }

    let zoo = [new Rhino(), new Elephant(), new Snake()];  // (Rhino | Elephant | Snake)[]
    ```

12. keyof와 typeof 연산자
    - `keyof`는 객체 타입의 키를 유니온 타입으로 추출하고, `typeof`는 값의 타입을 추출합니다.

    ```typescript
    interface Person {
        name: string;
        age: number;
    }

    type PersonKeys = keyof Person;  // "name" | "age"

    const colors = {
        red: "RED",
        blue: "BLUE",
    };

    type Colors = typeof colors;  // { red: string; blue: string; }
    ```

13. 조건부 타입 추론 (Conditional Type Inference)
    - 조건부 타입 내에서 `infer`키워드를 사용하여 타입을 추론할 수 있습니다.

    ```typescript
    type ReturnType<T> = T extends (...args: any[]) => infer R ? R : any;

    function f() {
        return { x: 10, y: 3 };
    }

    type FReturnType = ReturnType<typeof f>;  // { x: number; y: number; }
    ```

### 데코레이터 ###

데코레이터는 클래스 선언, 메서드 접근자, 프로퍼티 또는 매개변수에 첨부할 수 있는 특별한 종류의 선언입니다.
데코레이터는 `@expression`형식을 사용하여, 여기서 `expression`은 데코레이팅 된 선언에 대한 정보화 함께 런타임에 호출되는 함수여야 합니다.

1. 데코레이터 활성화
    - 데코레이터를 사용하려면 `tsconfig.json`파일에서 `exprimentalDecorators` 컴파일러 옵션을 활성화해야 합니다.

    ```json
    {
        "compilerOptions": {
            "experimentalDecorators": true
        }
    }
    ```

2. 클래스 데코레이터
    - 클래스 데코레이터는 클래스 선언 직전에 적용됩니다. 클래스 데코레이터는 클래스 생성자에 적용되며
    클래스 정의를 관찰, 수정, 또는 대체하는 데 사용할 수 있습니다.

    ```typescript
    function sealed(constructor: Function) {
        Object.seal(constructor);
        Object.seal(constructor.prototype);
    }

    @sealed
    class Greeter {
        greeting: string;
        constructor(message: string) {
            this.greeting = message;
        }
        greet() {
            return "Hello, " + this.greeting;
        }
    }
    ```

3. 메서드 데코레이터
    - 메서드 데코레이터는 메서드 선언 직전에 사용됩니다. 이는 메서드의 속성 설명자를 관찰, 수정 또는 대체하는 데 사용될 수 있습니다.

    ```typescript
    function enumerable(value: boolean) {
        return function (target: any, propertyKey: string, descriptor: PropertyDescriptor) {
            descriptor.enumerable = value;
        };
    }

    class Greeter {
        greeting: string;
        constructor(message: string) {
            this.greeting = message;
        }

        @enumerable(false)
        greet() {
            return "Hello, " + this.greeting;
        }
    }
    ```

4. 접근자 데코레이터
    - 접근자 데코레이터는 접근자 선언 직전에 선언됩니다. 접근자 데코레이터는 속성 설명자에 적용되며
    접근자의 정의를 관찰, 수정 또는 대체하는 데 사용될 수 있습니다.

    ```typescript
    function configurable(value: boolean) {
        return function (target: any, propertyKey: string, descriptor: PropertyDescriptor) {
            descriptor.configurable = value;
        };
    }

    class Point {
        private _x: number;
        private _y: number;
        constructor(x: number, y: number) {
            this._x = x;
            this._y = y;
        }

        @configurable(false)
        get x() { return this._x; }

        @configurable(false)
        get y() { return this._y; }
    }
    ```

5. 프로퍼티 데코레이터
    - 프로퍼티 데코레이터는 프로퍼티 선언 직전에 선언됩니다. 프로퍼티 데코레이터는 프로퍼티의 정의를 관찰하거나 수정하는 데 사용할 수 있습니다.

    ```typescript
    function format(formatString: string) {
        return function (target: any, propertyKey: string): any {
            let value = target[propertyKey];

            const getter = function () {
                return `${formatString} ${value}`;
            };

            const setter = function (newVal: string) {
                value = newVal;
            };

            return {
                get: getter,
                set: setter,
                enumerable: true,
                configurable: true
            };
        };
    }

    class Greeter {
        @format("Hello,")
        greeting: string;
    }
    ```

6. 매개변수 데코레이터
    - 매개변수 데코레이터는 매개변수 선언 직전에 선언됩니다. 매개변수 데코레이터는 메서드의 매개변수에 대한 정보를 관찰하는 데 사용할 수 있습니다.

    ```typescript
    function required(target: Object, propertyKey: string | symbol, parameterIndex: number) {
        let existingRequiredParameters: number[] = Reflect.getOwnMetadata("required", target, propertyKey) || [];
        existingRequiredParameters.push(parameterIndex);
        Reflect.defineMetadata("required", existingRequiredParameters, target, propertyKey);
    }

    class Greeter {
        greet(@required name: string) {
            return "Hello " + name;
        }
    }
    ```