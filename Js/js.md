<h1>JavaScript 심화 학습</h1>
<h2>변수와 데이터 타입</h2>
<ol>
  <li>var: 함수 스코프, 재선언 가능, 호이스팅 발생 -> undefined로 초기화.</li>
  <li>let: 블록 스코프, 재선언 불가, 호이스팅 발생하지만 TDZ(Temporal Dead Zone)로 인해 에러 발생.</li>
  <li>const: 블록 스코프, 재선언/재할당 불가, 호이스팅 발생하지만 TDZ로 인해 에러 발생.</li>
  <li>원시타입: 불변하며 값 자체를 저장.
    <ul>
      <li>숫자(number): 정수, 실수를 모두 포함하며 64비트 부동 소수점 형식 사용.</li>
      <li>문자열(string): 작은따옴표, 큰따옴표, 백틱으로 감싸며 유니코드 문자 표현 가능.</li>
      <li>불리언(boolean): true or false의 두 가지 값만 가질 수 있음.</li>
      <li>null: 의도적으로 값이 없음을 나태나는 특별한 값.</li>
      <li>undefined: 값이 할당되지 않은 변수의 기본값.</li>
      <li>symbol: ES6에서 추가된 유일하고 불변한 원시 타입.</li>
    </ul>
  </li>
  <li>참조 타입: 객체의 주소를 저장하며 힙 메모리에 값을 저장.
    <ul>
      <li>객체(object): 키 - 값 쌍으로 구성된 데이터 모음.</li>
      <li>배열(array): 순서가 있는 데이터 모음.</li>
      <li>함수(function): 호출 가능한 객체.</li>
    </ul>
  </li>
  <li>타입 변환: 암묵적 타입 변환(타입 강제)과 명시적 타입 변환(타입 캐스팅)방식 존재.</li>
  <li>타입 체크: typeof, instanceof 연산자 등을 사용하여 데이터 타입 확인.</li>
  <li>타입 단언: as 키워드를 사용하여 컴파일러에게 타입을 명시적으로 알려주는 방법(TypeScript에서 사용).</li>
</ol>
<pre><code class="language-javascript">// var, let, const 예제
var x = 10;
var x = 20; // 재선언 가능.
let y = 30;
// let y = 40; // 재선언 불가.
const z = 50;
// z = 60; // 재할당 불가.

// 원시 타입 예제
const num = 10;
const str = "Hello";
const bool = true;
const nul = null;
const undef = undefined;
const sym = Symbol("unique");

// 참조 타입 예제
const obj = { a: 1, b: 2 };
const arr = [1, 2, 3];
const func = function() {};
</code></pre>
<h2>연산자</h2>
<ol>
  <li>산술 연산자: +, -, *, /, %, ++, -- 등.</li>
  <li>할당 연산자: =, +=, -=, *=, /=, %= 등.</li>
  <li>비교 연산자: ==, !=, ===, !==, >, <, >=, <= 등.</li>
  <li>논리 연산자: &&, ||, ! 등.</li>
  <li>비트 연산자: &, |, ^, ~, <<, >>, >>> 등.</li>
  <li>연산자 우선순위: 단항 > 산술 > 비교 > 논리 > 삼항 > 할당 순서로 적용.</li>
  <li>연산자 결합성: 좌결합성(=, +=, -=, *=, /= 등), 우결합성(단항 연산자, 삼항 연산자 등).</li>
  <li>옵셔널 체이닝 연산자: (?.), null 병합 연산자(??)등 ES2020에 추가된 연산자.</li>
</ol>
<pre><code class="language-javascript">// 산술 연산자 예제
const result1 = 10 + 20;
const result2 = 10 - 20;
const result3 = 10 * 20;
const result4 = 10 / 20;
const result5 = 10 % 20;

// 할당 연산자 예제
let x = 10;
x += 20;
x -= 20;
x *= 20;
x /= 20;
x %= 20;

// 비교 연산자 예제
const result6 = 10 == "10";
const result7 = 10 === "10";
const result8 = 10 > 20;
const result9 = 10 < 20;

// 논리 연산자 예제
const result10 = true && false;
const result11 = true || false;
const result12 = !true;

// 비트 연산자 예제
const result13 = 10 & 20;
const result14 = 10 | 20;
const result15 = 10 ^ 20;
const result16 = ~10;
</code></pre>
<h2>제어문</h2>
<ol>
  <li>if...else: 조건에 따른 분기 처리.</li>
  <li>switch: 다중 분기 처리.</li>
  <li>for: 초기화, 조건 판단, 증감식을 사용한 반복 처리.</li>
  <li>while, do...while: 조건 판단에 따른 반복 처리.</li>
  <li>break: 반복문이나 switch문을 빠져나올 때 사용.</li>
  <li>continue: 반복문의 나머지 부분을 건너뛰고 다음 반복으로 진행.</li>
  <li>label: 중첩된 반복문에서 원하는 곳으로 break, continue 하기 위해 사용.</li>
  <li>단축 평가: &&, || 연산자를 사용하여 불필요한 연산 최소화.</li>
  <li>옵셔널 체이닝을 활용한 조건문 간소화.</li>
</ol>
<pre><code class="language-javascript">// if...else 예제
const x = 10;
if (x > 0) {
  console.log("x는 양수입니다.");
} else if (x < 0) {
  console.log("x는 음수입니다.");
} else {
  console.log("x는 0입니다.");
}

// switch 예제
const fruit = "apple";
switch (fruit) {
  case "apple":
    console.log("사과입니다.");
    break;
  case "banana":
    console.log("바나나입니다.");
    break;
  default:
    console.log("알 수 없는 과일입니다.");
}

// for 예제
for (let i = 0; i < 5; i++) {
  console.log(i);
}

// while 예제
let i = 0;
while (i < 5) {
  console.log(i);
  i++;
}

// break, continue 예제
for (let i = 0; i < 5; i++) {
  if (i === 3) {
    break;
  }
  console.log(i);
}
for (let i = 0; i < 5; i++) {
  if (i === 3) {
    continue;
  }
  console.log(i);
}
</code></pre>
<h2>함수</h2>
<ol>
  <li>함수 선언문: function 키워드를 사용하여 함수를 선언 (호이스팅 발생)</li>
  <li>함수 표현식: 변수에 함수를 할당하는 방식 (호이스팅 발생하지 않음.)</li>
  <li>화살표 함수: => 문법을 사용한 함수 선언 방식. (this 바인딩 방식이 다름.)</li>
  <li>매개변수: 함수 호출 시 전달되는 값을 받는 변수</li>
  <li>인수: 함수 호출 시 전달하는 실제 값.</li>
  <li>반환값: return 키워드를 사용하여 함수의 실행 결과를 반환.</li>
  <li>함수 스코프: 함수 내부에서 선언된 변수는 함수 외부에서 접근 불가.</li>
  <li>콜백 함수: 다른 함수의 매개변수로 전달되어 호출되는 함수.</li>
  <li>고차 함수: 함수를 인수로 받거나 함수를 반환하는 함수.</li>
  <li>재귀 함수: 자기 자신을 호출하는 함수(종료 조건 필수).</li>
  <li>메서드: 객체의 속성으로 할당된 함수.</li>
  <li>this 바인딩: 함수 호출 방식에 따라 this가 가리키는 값이 달라짐.</li>
  <li>프로토타입: 객체의 상위 객체 역할을 하며 하위 객체에게 속성과 메서드를 상속.</li>
</ol>
<pre><code class="language-javascript">// 함수 선언문 예제
function add(a, b) {
  return a + b;
}

// 함수 표현식 예제
const multiply = function (a, b) {
  return a * b;
};

// 화살표 함수 예제
const subtract = (a, b) => {
  return a - b;
};

// 콜백 함수 예제
function calculate(a, b, operation) {
  return operation(a, b);
}
const result1 = calculate(10, 20, add);
const result2 = calculate(10, 20, multiply);

// 고차 함수 예제
function makeAdder(x) {
  return function (y) {
    return x + y;
  };
}
const addFive = makeAdder(5);
const result3 = addFive(10);

// 재귀 함수 예제
function factorial(n) {
  if (n === 0) {
    return 1;
  }
  return n * factorial(n - 1);
}
const result4 = factorial(5);
</code></pre>
<h2>클로저</h2>
<ol>
  <li>클로저: 함수와 그 함수가 선언된 렉시컬 환경의 조합.</li>
  <li>렉시컬 환경: 함수가 선언된 환경을 나타내는 객체(스코프, 외부 변수 등의 정보 포함).</li>
  <li>자유 변수: 클로저 내부에서 사용되는 외부 변수.</li>
  <li>클로저 활용 사례: 정보 은닉, 모듈 패턴, 커링, 메모이제이션 등.</li>
  <li>정보 은닉: 클로저를 사용하여 private 변수와 메서드를 구현.</li>
  <li>모듈 패턴: 클로저를 사용하여 public API와 private 구현을 분리.</li>
</ol>
<pre><code class="language-javascript">// 클로저 예제
function outerFunction(x) {
  return function innerFunction(y) {
    return x + y;
  };
}
const addTen = outerFunction(10);
const result1 = addTen(20);
const result2 = addTen(30);

// 정보 은닉 예제
function counter() {
  let count = 0;
  return {
    increment: function () {
      count++;
    },
    getCount: function () {
      return count;
    },
  };
}
const myCounter = counter();
myCounter.increment();
myCounter.increment();
const result3 = myCounter.getCount();
</code></pre>
<h2>프로미스와 비동기 처리</h2>
<ol>
  <li>비동기 처리: 특정 코드의 실행이 완료될 때까지 기다리지 않고 다음 코드를 실행하는 방식.</li>
  <li>콜백 지옥: 콜백 함수를 중첩하여 사용할 때 발생하는 가독성 저하와 디버깅 어려움.</li>
  <li>프로미스: 비동기 작업의 최종 완료 또는 실패를 나타내는 객체.
    <ul>
      <li>pending: 초기 상태, fulfilled or rejected 상태가 아닌 상태.</li>
      <li>fulfilled: 연산이 성공적으로 완료된 상태.</li>
      <li>rejected: 연산이 실패한 상태.</li>
    </ul>
  </li>
  <li>.then(): fulfilled 상태가 되면 호출되는 메서드 (성공 처리)</li>
  <li>.catch(): rejected 상태가 되면 호출되는 메서드 (실패 처리)</li>
  <li>.finally(): fulfilled or rejected 상태일 때 호출되는 메서드 (항상 실행)</li>
  <li>async/await: 프로미스를 더욱 간편하게 사용할 수 있도록 ES2017에 도입된 문법.</li>
  <li>Promise.all(): 여러 개의 프로미스를 병렬로 실행하고 모든 프로미스가 fulfilled 상태가 되면 결과를 반환.</li>
</ol>
<pre><code class="language-javascript">// 프로미스 예제
function fetchData() {
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      const data = "Hello, Promise!";
      resolve(data);
    }, 1000);
  });
}
fetchData()
  .then((data) => {
    console.log(data);
  })
  .catch((error) => {
    console.error(error);
  });

// async/await 예제
async function fetchDataAsync() {
  try {
    const data = await fetchData();
    console.log(data);
  } catch (error) {
    console.error(error);
  }
}
fetchDataAsync();

// Promise.all 예제
const promise1 = new Promise((resolve) => setTimeout(resolve, 1000, "Promise 1"));
const promise2 = new Promise((resolve) => setTimeout(resolve, 2000, "Promise 2"));
Promise.all([promise1, promise2]).then((results) => {
  console.log(results);
});
</code></pre>
<h2>ES6+ 문법</h2>
<ol>
  <li>화살표 함수: function 키워드 대신 화살표 함수 =&gt; {} 문법 사용, this 바인딩 방식 변경.</li>
  <li>템플릿 리터럴: 백틱(`)을 사용하여 문자열 내 변수 삽입, 여러 줄 문자열 작성 가능.</li>
  <li>구조 분해 할당: 배열이나 객체의 속성을 해체하여 개별 변수에 할당.</li>
  <li>클래스: 객체 지향 프로그래밍의 클래스 문법 지원.</li>
  <li>모듈: 코드를 별도의 파일로 분리하여 관리, import/export 키워드 사용.</li>
  <li>제너레이터: function* 키워드를 사용하며 Iterator 객체 생성, yield 키워드로 값 반환.</li>
  <li>이터레이터: next() 메서드를 가진 객체, Symbol.iterator 메서드를 통해 이터레이터 생성.</li>
  <li>심볼: 유일하고 불변한 원시 타입, 객체의 속성 키로 사용.</li>
  <li>async/await: 프로미스를 더욱 간편하게 사용할 수 있는 문법(ES2017).</li>
  <li>레스트/스프레드 문법: 함수의 매개변수를 배열로 받거나, 배열을 개별 요소로 전개(ES2015).</li>
</ol>
<pre><code class="language-javascript">// 템플릿 리터럴 예제
const name = "John";
const age = 30;
console.log(`My name is ${name} and I'm ${age} years old.`);

// 구조 분해 할당 예제
const obj = { a: 1, b: 2, c: 3 };
const { a, b } = obj;
console.log(a, b);

// 클래스 예제
class Person {
  constructor(name, age) {
    this.name = name;
    this.age = age;
  }
  sayHello() {
    console.log(`Hello, my name is ${this.name} and I'm ${this.age} years old.`);
  }
}
const person = new Person("John", 30);
person.sayHello();

// 모듈 예제
// math.js
export function add(a, b) {
  return a + b;
}
export function subtract(a, b) {
  return a - b;
}

// main.js
import { add, subtract } from "./math.js";
console.log(add(10, 20));
console.log(subtract(10, 20));
</code></pre>
<h2>함수형 프로그래밍과 객체 지향 프로그래밍</h2>
<ol>
  <li>함수형 프로그래밍: 순수 함수를 사용하여 Side effects를 최소화하고 불변성을 유지하는 프로그래밍 패러다임.
    <ul>
      <li>순수 함수: 동일한 입력에 대해 항상 동일한 출력을 반환하며 Side effect가 없는 함수.</li>
      <li>불변성: 데이터가 변경되지 않고 유지되는 성질</li>
      <li>고차 함수: 함수를 인수로 받거나 함수를 반환하는 함수.</li>
      <li>커링: 다중 인수 함수를 단일 인수 함수들의 체인으로 변환하는 기법.</li>
    </ul>
  </li>
  <li>객체 지향 프로그래밍: 객체를 기반으로 프로그램을 구성하는 프로그래밍 패러다임.
    <ul>
      <li>클래스: 객체를 생성하기 위한 템플릿</li>
      <li>인스턴스: 클래스를 통해 생성된 객체</li>
      <li>상속: 상위 클래스의 속성과 메서드를 하위 클래스에서 사용할 수 있도록 하는 기능.</li>
      <li>다형성: 동일한 메서드가 클래스에 따라 다르게 행동할 수 있는 능력</li>
      <li>캡슐화: 객체의 속성과 메서드를 하나로 묶고 외부에서의 접근을 제한하는 것.</li>
    </ul>
  </li>
  <li>함수형 프로그래밍과 객체 지향 프로그래밍의 장단점 비교
    <ul>
      <li>함수형 프로그래밍: 테스트와 디버깅이 용이, 동시성 처리에 유리, 코드 간결성과 재사용성이 높음.</li>
      <li>객체 지향 프로그래밍: 코드 구조화와 모듈화에 유리, 실세계 문제를 모델링하기 용이, 유지보수성이 높음.</li>
    </ul>
  </li>
</ol>
<pre><code class="language-javascript">// 함수형 프로그래밍 예제
function add(a, b) {
  return a + b;
}
function multiply(a, b) {
  return a * b;
}
function calculate(a, b, operation) {
  return operation(a, b);
}
const result1 = calculate(10, 20, add);
const result2 = calculate(10, 20, multiply);

// 객체 지향 프로그래밍 예제
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
const dog = new Dog("Buddy");
dog.speak();
</code></pre>
<h2>예외 처리와 디버깅</h2>
<ol>
  <li>try...catch...finally: 예외 발생 시 처리 흐름을 제어하는 구문.
    <ul>
      <li>try: 예외가 발생할 가능성이 있는 코드 블록</li>
      <li>catch: 예외가 발생했을 때 실행되는 코드 블록</li>
      <li>finally: 예외 발생 여부와 관계없이 항상 실행되는 코드 블록.</li>
    </ul>
  </li>
  <li>throw: 사용자 정의 예외를 발생시키는 키워드</li>
  <li>Error 객체: 예외 정보를 담고 있는 내장 객체.
    <ul>
      <li>name: 에러 이름.</li>
      <li>message: 에러 메시지.</li>
      <li>stack: 에러 발생 위치를 나타내는 스택 트레이스.</li>
    </ul>
  </li>
  <li>커스텀 에러 타입 정의: Error 객체를 상속하여 새로운 에러 타입 생성.</li>
  <li>디버깅 도구: 브라우저 개발자 도구, Node.js 디버거 등.</li>
  <li>중단점: 코드 실행을 일시 중지하고 변수 값을 확인할 수 있는 지점.</li>
  <li>콘솔 출력: console.log(), console.error() 등을 사용하여 디버깅 정보 출력.</li>
  <li>로깅: 프로그램 실행 상태와 에러 정보를 기록하는 작업.</li>
  <li>에러 모니터링: 에러 발생 시 자동으로 에러 정보를 수집하고 알림을 보내는 시스템.</li>
</ol>
<pre><code class="language-javascript">// try...catch...finally 예제
function divideTen(num) {
  if (num === 0) {
    throw new Error("Cannot divide by zero!");
  }
  return 10 / num;
}
try {
  console.log(divideTen(5));
  console.log(divideTen(0));
} catch (error) {
  console.error(error.message);
} finally {
  console.log("Finally block executed.");
}

// 커스텀 에러 타입 예제
class InvalidInputError extends Error {
  constructor(message) {
    super(message);
    this.name = "InvalidInputError";
  }
}
function processInput(input) {
  if (input < 0) {
    throw new InvalidInputError("Input must be a positive number!");
  }
  console.log(`Processing input: ${input}`);
}
try {
  processInput(-10);
} catch (error) {
  if (error instanceof InvalidInputError) {
    console.error(error.message);
  } else {
    throw error;
  }
}
</code></pre>
<h2>코드 최적화</h2>
<ol>
  <li>시간 복잡도: 입력 크기에 따른 알고리즘 실행 시간 증가율.</li>
  <li>O(1) &lt; O(log n) &lt; O(n) &lt; O(n log n) &lt; O(n^2) &lt; O(2^n) &lt; O(n!)</li>
  <li>공간 복잡도: 입력 크기에 따른 알고리즘의 메모리 사용량 증가율.
    <ul>
      <li>O(1): 입력 크기와 관계없이 일정한 메모리 사용 (상수 공간)</li>
      <li>O(n): 입력 크기에 비례하여 메모리 사용량 증가 (선형 공간)</li>
      <li>O(log n): 입력 크기의 로그에 비례하여 메모리 사용량 증가.</li>
    </ul>
    메모리 사용량 최적화 방법
    <ul>
      <li>불필요한 변수 제거</li>
      <li>객체나 배열의 크기 최소화</li>
      <li>가비지 컬렉션 고려</li>
      <li>재귀 호출 대신 반복문 사용</li>
    </ul>
  </li>
</ol>
<pre><code class="language-javascript">// O(1) 예제
function getFirstElement(arr) {
  return arr[0];
}

// O(n) 예제
function findElement(arr, target) {
  for (let i = 0; i < arr.length; i++) {
    if (arr[i] == target) {
      return i;
    }
  }
  return -1;
}

// O(n^2) 예제
function hasDuplicates(arr) {
  for (let i = 0; i < arr.length; i++) {
    for (let j = 0; j < arr.length; j++) {
      if (i !== j && arr[i] === arr[j]) {
        return true;
      }
    }
  }
  return false;
}
</code></pre>
