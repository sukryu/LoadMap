# 데이터 구조 (Data Structure)

데이터 구조는 데이터를 효율적으로 저장하고 관리하기 위한 방법입니다. 적절한 데이터 구조를 선택하면
프로그램의 성능과 효율성을 크게 향상시킬 수 있습니다.

1. 배열 (Array)
    - 정의: 동일한 타입의 데이터를 연속된 메모리 공간에 순서대로 저장하는 자료 구조입니다.

    - 특징:
        - 연속된 메모리 공간: 배열의 모든 요소는 메모리에서 연속적으로 배치됩니다. 이는 인덱스를 통해 요소에 빠르게 접근할 수 있게 해줍니다.
        - 고정된 크기: 대부분의 프로그래밍 언어에서 배열의 크기는 선언 시에 지정되며, 이후에는 변경할 수 없습니다.
        - 동일한 데이터 타입: 배열은 한 가지 데이터 타입의 요소들로만 구성됩니다. 예를 들어, 정수형 배열은 모든 요소가 정수여야 합니다.

    1. 배열의 선언과 초기화
        - 배열을 사용하기 위해서는 먼저 배열을 선언하고 초기화해야 합니다.

        1. JavaScript에서의 배열
            - JavaScript에서는 배열의 크기가 동적으로 조절되며, 다양한 데이터 타입을 혼합하여 저장할 수 있습니다.

            ```javascript
            // 배열 선언 및 초기화
            let fruits = ["사과", "바나나", "체리"];
            console.log(fruits); // 출력: ["사과", "바나나", "체리"]

            // 요소에 접근하기
            console.log(fruits[0]); // 출력: 사과

            // 요소 추가하기
            fruits.push("포도");
            console.log(fruits); // 출력: ["사과", "바나나", "체리", "포도"]

            // 요소 제거하기
            fruits.pop();
            console.log(fruits); // 출력: ["사과", "바나나", "체리"]

            ```

        2. Python에서의 배열 (리스트)
            - Python에서는 배열과 유사한 **리스트(List)**를 사용합니다.

            ```python
            # 리스트 선언 및 초기화
            numbers = [1, 2, 3, 4, 5]
            print(numbers)  # 출력: [1, 2, 3, 4, 5]

            # 요소에 접근하기
            print(numbers[0])  # 출력: 1

            # 요소 추가하기
            numbers.append(6)
            print(numbers)  # 출력: [1, 2, 3, 4, 5, 6]

            # 요소 제거하기
            numbers.remove(3)
            print(numbers)  # 출력: [1, 2, 4, 5, 6]
            ```

        3. C언어에서의 배열
            - C언어에서는 배열의 크기가 고정되어 있으며, 선언 시 지정한 크기를 변경할 수 없습니다.

            ```c
            #include <stdio.h>

            int main() {
                // 배열 선언 및 초기화
                int numbers[5] = {1, 2, 3, 4, 5};

                // 요소에 접근하기
                printf("%d\n", numbers[0]); // 출력: 1

                // 요소 변경하기
                numbers[0] = 10;
                printf("%d\n", numbers[0]); // 출력: 10

                return 0;
            }
            ```

    2. 배열의 주요 연산

        1. 요소 접근 (Access)
            - 배열의 요소는 **인덱스(index)**를 통해 접근합니다. 인덱스는 보통 0부터 시작합니다.
            
            ```javascript
            let arr = [10, 20, 30];
            console.log(arr[1]); // 20
            ```

        2. 탐색 (Search)
            - 배열에서 특정 값을 찾기 위해 **선형 검색(Linear Search)**를 사용합니다.

            ```javascript
            function linearSearch(arr, target) {
                for (let i = 0; i < arr.length; i++) {
                    if (arr[i] == target) return i;
                }
                return -1;
            }

            let index = linearSearch([10, 20, 30], 20);
            console.log(index) // 1
            ```

        3. 삽입 (Insertion)
            - 배열의 특정 위치에 요소를 삽입할 수 있습니다.
            
            ```javascript
            let arr = [10, 20, 30];
            arr.splice(1, 0, 15); // 인덱스 1에 15 삽입
            console.log(arr); // 출력: [10, 15, 20, 30]
            ```

        4. 삭제 (Deletion)
            - 배열의 특정 위치에 있는 요소를 삭제할 수 있습니다.

            ```javascript
            let arr = [10, 15, 20, 30];
            arr.splice(1, 1); // 인덱스 1의 요소 삭제
            console.log(arr); // 출력: [10, 20, 30]
            ```

    3. 배열의 장단점

        1. 장점
            - 빠른 접근 속도: 인덱스를 통해 임의의 요소에 O(1)의 시간 복잡도로 접근할 수 있습니다.
            - 메모리 효율성: 연속된 메모리 공간을 사용하므로 오버헤드가 적습니다.

        2. 단점
            - 고정된 크기: 대부분의 언어에서 배열의 크기는 선언 시 결정되며, 실행 중에 변경할 수 없습니다.
            - 삽입 및 삭제 비효율성: 중간에 요소를 삽입하거나 삭제하면, 이후의 모든 요소를 이동시켜야 하므로 O(n)의 시간이 소요됩니다.

    4. 다차원 배열
        - 배열의 요소로 배열을 가지는 구조로, 2차원 이상으로 확장할 수 있습니다.

        1. 2차원 배열의 예:
            ```javascript
            let matrix = [
                [1, 2, 3],
                [4, 5, 6],
                [7, 8, 9]
            ];

            console.log(matrix[0][1]) // 2
            ```

        2. 활용 분야:
            - 행렬 연산: 수학에서의 행렬 계산에 사용됩니다.
            - 이미지 처리: 픽셀 데이터를 2차원 배열로 관리합니다.
            - 게임 개발: 맵이나 보드의 상태를 저장합니다.

    5. 동적 배열
        - 일부 언어는 실행 중에 크기가 변경될 수 있는 동적 배열을 지원합니다.

        1. 동적 배열의 특징
            - 유연성: 배열의 크기를 미리 알 필요가 없습니다.
            - 자동 확장: 요소를 추가하면 자동으로 크기가 늘어납니다.

        2. JavaScript에서의 동적 배열
            ```javascript
            let arr = [];
            arr.push(10);
            arr.push(20);
            console.log(arr); // [10, 20]
            ```

    6. 배열과 메모리
        - 배열은 연속된 메모리 공간을 사용하므로, 메모리 관리에 주의해야 합니다.
            - 메모리 효율성: 연속된 공간을 사용하므로 캐시 히트율이 높습니다.
            - 메모리 낭비: 선언한 크기보다 적은 요소를 저장하면 메모리가 낭비됩니다.

    7. 배열의 실제 활용 예제

        1. 배열의 모든 요소 합 구하기

            ```javascript
            function sumArray(arr) {
                let sum = 0;
                for (let i = 0; i < arr.length; i++) {
                    sum += arr[i];
                }

                return sum;
            }

            let numbers = [1, 2, 3, 4, 5];
            console.log(sumArray(numbers)) // 15
            ```

        2. 배열에서 최대값 찾기
            
            ```javascript
            function findMax(arr) {
                let max = arr[0];
                for(let i = 1; i < arr.length; i++) {
                    if(arr[i] > max) {
                        max = arr[i];
                    }
                }
                return max;
            }

            let numbers = [10, 5, 8, 22, 15];
            console.log(findMax(numbers)); // 출력: 22
            ```

    8. 배열과 다른 데이터 구조 비교
        1. 배열 vs 연결 리스트
            - 배열: 인덱스를 통한 빠른 접근이 가능하지만, 중간 삽입 및 삭제가 비효율적입니다.
            - 연결 리스트: 중간 삽입 및 삭제가 효율적이지만, 임의의 요소에 접근하기 위해서는 순차적으로 탐색해야 합니다.

        2. 배열을 활용한 스택과 큐 구현
            - 스택 (Stack): 배열의 끝부분을 이용하여 LIFO(Last In First Out)구조를 구현합니다.
                ```javascript
                let stack = [];
                stack.push(1);
                stack.push(2);
                console.log(stack.pop()) // 2
                ```

            - 큐 (Queue): 배열의 시작과 끝을 이용하여 FIFO(First In First Out) 구조를 구현합니다.
                ```javascript
                let queue = [];
                queue.push(1);
                queue.push(2);
                console.log(queue.shift()); // 1
                ```

    9. 배열 사용 시 주의사항

        1. 인덱스 범위 초과
            - 문제점: 배열의 인덱스 범위를 초과하여 접근하면 오류가 발생하거나 예상치 못한 동작이 일어날 수 있습니다.
            - 예시:
                ```javascript
                let arr = [1, 2, 3];
                console.log(arr[3]); // undefined or Error
                ```

        2. 얕은 복사와 깊은 복사
            - 얕은 복사(Shallow Copy): 배열의 참조를 복사하여 원본과 복사본이 동일한 객체를 참조합니다.
                ```javascript
                let original = [1, 2, 3];
                let copy = original;
                copy[0] = 99;
                console.log(original); // [99, 2, 3]
                ```

            - 깊은 복사(Deep Copy): 배열의 모든 요소를 새로 복사하여 원본과 복사본이 독립된 객체가 됩니다.
                ```javascript
                let original = [1, 2, 3];
                let copy = original.slice(); // or [...original];
                copy[0] = 99;
                console.log(original); // [1, 2, 3];
                ```

    10. 배열의 고급 활용

        1. 고차 함수 사용
            - forEach: 배열의 각 요소를 순회하며 함수 실행
                ```javascript
                let arr = [1, 2, 3];
                arr.forEach(function(element) {
                    console.log(element);
                });
                ```

            - map: 배열의 각 요소를 변환하여 새로운 배열 생성
                ```javascript
                let arr = [1, 2, 3];
                let doubled = arr.map(function(element) {
                    return element*2;
                });

                console.log(arr); // [2, 4, 6]
                ```

            - filter: 조건에 맞는 요소만 추출하여 새로운 배열 생성
                ```javascript
                let arr = [1, 2, 3, 4, 5];
                let evenNumbers = arr.filter(function(element) {
                    return element % 2 === 0;
                });
                console.log(evenNumbers); // 출력: [2, 4]

                ```

        2. 다차원 배열의 활용
            - 행렬 곱셈
                ```javascript
                function multiplyMatrices(a, b) {
                    let result = [];
                    for(let i = 0; i < a.length; i++) {
                        result[i] = [];
                        for(let j = 0; j < b[0].length; j++) {
                            result[i][j] = 0;
                            for(let k = 0; k < a[0].length; k++) {
                                result[i][j] += a[i][k] * b[k][j];
                            }
                        }
                    }
                    return result;
                }

                let matrixA = [
                    [1, 2],
                    [3, 4]
                ];

                let matrixB = [
                    [5, 6],
                    [7, 8]
                ];

                let product = multiplyMatrices(matrixA, matrixB);
                console.log(product);
                // 출력: [[19, 22], [43, 50]]
                ```

    11. 배열의 시간 복잡도
        `연산`               | `시간 복잡도`
        접근                 | O(1)
        탐색                 | O(n)
        삽입(끝)             | O(1)
        삽입(중간)           | O(n)
        삭제(끝)             | O(1)
        삭제(중간)           | O(n)

    12. 배열의 한계와 대안
        - 한계점
            - 고정된 크기: 실행 중에 크기 변경이 불가능한 경우가 많음.
            - 비효율적인 중간 삽입/삭제: 요소 이동으로 인한 성능 저하.

        - 대안 데이터 구조
            - 연결 리스트: 중간 삽입/삭제가 빈번한 경우 유용함.
            - 동적 배열(List, Vector): 크기 변경이 가능한 배열을 제공함.