# C++ 언어 #

## C++의 기초

1. C++과 C의 차이점

    - C++는 C언어를 기반으로 만들어진 언어로, C의 모든 기능을 포함하면서 추가적인 기능을 제공합니다. 주요 차이점은 다음과 같습니다.

    1. 객체 지향 프로그래밍 지원:
        - C++는 클래스와 객체를 사용한 객체 지향 프로그래밍을 지원합니다. 이를 통해 데이터와 그 데이터를 처리하는 함수를 하나의 단위로 묶을 수 있습니다.

        - 예시:
            ```cpp
            class Person {
            private:
                string name;
                int age;
            public:
                void setName(string n) { name = n; }
                string getName() { return name; }
            };
            ```

    2. 함수 오버로딩:
        - C++에서는 같은 이름의 함수를 매개변수의 타입이나 개수를 다르게 하여 여러 개 정의할 수 있습니다.

        - 예시:
            ```cpp
            int add(int a, int b) { return a + b; }
            double add(double a, double b) { return a + b; }
            ```

    3. 참조 변수:
        - C++는 참조 변수를 지원하여 변수의 별명을 만들 수 있습니다.

        - 예시:
            ```cpp
            int x = 10;
            int& ref = x;  // ref는 x의 참조
            ref = 20;  // x의 값도 20으로 변경됨
            ```

    4. 디폴트 매개변수:
        - 함수 선언 시 매개변수에 기본값을 지정할 수 있습니다.

        - 예시:
            ```cpp
            void printMessage(string msg = "Hello") {
                cout << msg << endl;
            }
            ```

    5. 인라인 함수:
        - `inline`키워드를 사용하여 함수 호출 오버헤드를 줄일 수 있습니다.

        - 예시:
            ```cpp
            inline int max(int a, int b) {
                return (a > b) ? a : b;
            }
            ```

    6. 동적 메모리 할당:
        - C++에서는 `new`와 `delete` 연산자를 사용하여 더 안전하고 편리한 동적 메모리 할당을 지원합니다.

        - 예시:
            ```cpp
            int* p = new int(10);  // 동적으로 정수 할당
            delete p;  // 메모리 해제
            ```

2. 입출력 스트림 (iostream)
    - C++는 C의 `printf`와 `scanf`대신 `iostream`라이브러리를 통한 입출력을 주로 사용합니다.

    1. 출력 스트림 (cout)
        ```cpp
        #include <iostream>
        using namespace std;

        int main() {
            int age = 25;
            cout << "My age is " << age << endl;
            return 0;
        }
        ```

    2. 입력 스트림 (cin)
        ```cpp
        #include <iostream>
        using namespace std;

        int main() {
            int number;
            cout << "Enter a number: ";
            cin >> number;
            cout << "You entered: " << number << endl;
            return 0;
        }
        ```

    3. 조작자 (manipulators):
        - 입출력 형식을 제어하는 데 사용됩니다.

        ```cpp
        #include <iostream>
        #include <iomanip>
        using namespace std;

        int main() {
            double pi = 3.14159;
            cout << fixed << setprecision(2) << pi << endl;  // 출력: 3.14
            return 0;
        }
        ```

3. 네임스페이스 (namespaces)
    - 네임스페이스는 이름 충돌을 방지하고 코드를 논리적으로 그룹화하는 데 사용됩니다.

    1. 네임스페이스 정의:
        ```cpp
        namespace MyMath {
            const double PI = 3.14159;
            double square(double x) { return x * x; }
        }
        ```

    2. 네임스페이스 사용:
        ```cpp
        #include <iostream>
        using namespace std;

        int main() {
            cout << MyMath::PI << endl;
            cout << MyMath::square(5) << endl;
            return 0;
        }
        ```

    3. using 지시문:
        ```cpp
        using namespace MyMath;
        cout << PI << endl;  // MyMath:: 접두사 없이 사용 가능
        ```

4. 참조 변수 (reference variables)
    - 참조 변수는 기존 변수의 별명으로, 포인터와 유사하지만 사용이 더 간단합니다.

    1. 참조 변수 선언:
        ```cpp
        int x = 10;
        int& ref = x;  // ref는 x의 참조
        ```

    2. 함수 매개변수로 참조 사용:
        ```cpp
        void swap(int& a, int& b) {
            int temp = a;
            a = b;
            b = temp;
        }

        int main() {
            int x = 5, y = 10;
            swap(x, y);
            cout << "x: " << x << ", y: " << y << endl;  // 출력: x: 10, y: 5
            return 0;
        }
        ```

    3. const 참조:
        ```cpp
        void printValue(const int& val) {
            cout << "Value: " << val << endl;
            // val = 10;  // 컴파일 에러: const 참조는 수정 불가
        }
        ```

### 객체 지향 프로그래밍 (OOP) ###

- 객체 지향 프로그래밍은 C++의 핵심 패러다임 중 하나로, 데이터와 그 데이터를 조작하는 함수를 하나의 단위(객체)로 묶어 프로그래밍하는 방식입니다.

1. 클래스와 객체

    1. 클래스 정의:
        - 클래스는 객체의 청사진 또는 템플릿입니다.
        ```cpp
        class Car {
        private:
            string brand;
            int year;

        public:
            void setBrand(string b) { brand = b; }
            void setYear(int y) { year = y; }
            string getBrand() { return brand; }
            int getYear() { return year; }
        };
        ```

    2. 객체 생성:

        ```cpp
        Car myCar;
        myCar.setBrand("Toyota");
        myCar.setYear(2022);
        ```

    3. 생성자와 소멸자:
        - 생성자는 객체가 생성될 때, 소멸자는 객체가 파괴될 때 자동으로 호출됩니다.

        ```cpp
        class Car {
        public:
            Car(string b, int y) : brand(b), year(y) {
                cout << "Car created" << endl;
            }
            ~Car() {
                cout << "Car destroyed" << endl;
            }
        private:
            string brand;
            int year;
        };
        ```

2. 캡슐화
    - 캡슐화는 데이터와 그 데이터를 처리하는 함수를 하나로 묶고, 외부에서의 접근을 제한하는 것 입니다.

    1. 접근 제어자:
        - public: 어디서나 접근 가능
        - private: 클래스 내부에서만 접근 가능
        - protected: 해당 클래스와 상속받은 클래스에서 접근 가능

        ```cpp
        class BankAccount {
        private:
            double balance;

        public:
            void deposit(double amount) {
                if (amount > 0) {
                    balance += amount;
                }
            }
            
            double getBalance() {
                return balance;
            }
        };
        ```

3. 상속
    - 상속은 기존 클래스의 특정을 새로운 클래스가 물려받는 것입니다.

    ```cpp
    class Vehicle {
    protected:
        string brand;

    public:
        void setBrand(string b) { brand = b; }
    };

    class Car : public Vehicle {
    private:
        int doors;

    public:
        void setDoors(int d) { doors = d; }
    };

    int main() {
        Car myCar;
        myCar.setBrand("Toyota");  // Vehicle 클래스로부터 상속받은 메소드
        myCar.setDoors(4);         // Car 클래스의 고유 메소드
        return 0;
    }
    ```

4. 다형성
    - 다형성은 같은 이름의 함수나 연산자가 다른 클래스에서 다르게 동작하는 것을 말합니다.

    1. 함수 오버라이딩:

        ```cpp
        class Animal {
        public:
            virtual void makeSound() {
                cout << "The animal makes a sound" << endl;
            }
        };

        class Dog : public Animal {
        public:
            void makeSound() override {
                cout << "The dog barks" << endl;
            }
        };

        int main() {
            Animal* animal = new Dog();
            animal->makeSound();  // 출력: "The dog barks"
            delete animal;
            return 0;
        }
        ```

    2. 순수 가상 함수와 추상 클래스

        ```cpp
        class Shape {
        public:
            virtual double getArea() = 0;  // 순수 가상 함수
        };

        class Circle : public Shape {
        private:
            double radius;

        public:
            Circle(double r) : radius(r) {}
            
            double getArea() override {
                return 3.14 * radius * radius;
            }
        };
        ```

5. 연산자 오버로딩
    - 연산자 오버로딩을 통해 사용자 정의 타입에 대해 연산자의 동작을 정의할 수 있습니다.

    ```cpp
    class Complex {
    private:
        double real, imag;

    public:
        Complex(double r = 0, double i = 0) : real(r), imag(i) {}
        
        Complex operator+(const Complex& other) {
            return Complex(real + other.real, imag + other.imag);
        }
        
        void display() {
            cout << real << " + " << imag << "i" << endl;
        }
    };

    int main() {
        Complex c1(3, 2), c2(1, 7);
        Complex c3 = c1 + c2;
        c3.display();  // 출력: 4 + 9i
        return 0;
    }
    ```

### 표준 템플릿 라이브러리 (STL) ###

- STL은 C++의 강력한 기능 중 하나로, 재사용 가능한 컴포넌트들의 집합입니다. STL은 크게 컨테이너, 반복자, 알고리즘으로 구성됩니다.

1. 컨테이너 (Containers)
    - 컨테이너는 객체들을 저장하고 관리하는 자료구조입니다. 주요 컨테이너는 다음과 같습니다:

        1. 시퀀스 컨테이너:
            - vector: 동적 배열
            - list: 양방향 연결 리스트
            - deque: 양쪽에서 삽입/삭제가 가능한 큐

            - 예시(vector):

                ```cpp
                #include <vector>
                #include <iostream>
                using namespace std;

                int main() {
                    vector<int> vec = {1, 2, 3, 4, 5};
                    vec.push_back(6);  // 끝에 6 추가
                    
                    for(int num : vec) {
                        cout << num << " ";
                    }
                    // 출력: 1 2 3 4 5 6

                    return 0;
                }
                ```

        2. 연관 컨테이너:
            - set: 정렬된 고유 원소들의 집합
            - multiset: 정렬된 원소들의 집합 (중복 허용)
            - map: 키 - 값 쌍을 저장하는 정렬된 연관 배열
            - multimap: 키 - 값 쌍을 저장하는 정렬된 연관 배열 (중복 키 허용)

            - 예시(map):

                ```cpp
                #include <map>
                #include <string>
                #include <iostream>
                using namespace std;

                int main() {
                    map<string, int> ages;
                    ages["Alice"] = 30;
                    ages["Bob"] = 25;

                    for(const auto& pair : ages) {
                        cout << pair.first << ": " << pair.second << endl;
                    }
                    // 출력:
                    // Alice: 30
                    // Bob: 25

                    return 0;
                }
                ```

        3. 컨테이너 어댑터:
            - stack: LIFO (Last In First Out)구조
            - queue: FIFO (First In First Out)구조
            - priority_queue: 우선순위 큐

            - 예시(stack):

                ```cpp
                #include <stack>
                #include <iostream>
                using namespace std;

                int main() {
                    stack<int> s;
                    s.push(1);
                    s.push(2);
                    s.push(3);

                    while(!s.empty()) {
                        cout << s.top() << " ";
                        s.pop();
                    }
                    // 출력: 3 2 1

                    return 0;
                }
                ```

2. 반복자 (Iterators)
    - 반복자는 컨테이너의 원소들을 순회하는 데 사용되는 객체입니다.

    1. 반복자 유형:
        - 입력 반복자: 읽기 전용, 한 방향 이동
        - 출력 반복자: 쓰기 전용, 한 방향 이동
        - 순방향 반복자: 읽기/쓰기, 한 방향 이동
        - 양방향 반복자: 읽기/쓰기, 양 방향 이동
        - 임의 접근 반복자: 읽기/쓰기, 임의 접근

        
    2. 반복자 사용 예:

        ```cpp
        #include <vector>
        #include <iostream>
        using namespace std;

        int main() {
            vector<int> vec = {1, 2, 3, 4, 5};

            for(vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
                cout << *it << " ";
            }
            // 출력: 1 2 3 4 5

            return 0;
        }
        ```

3. 알고리즘 (Algorithms)
    - STL은 다양한 알고리즘을 제공하여 컨테이너의 원소들을 처리합니다.

    1. 주요 알고리즘:
        - sort: 정렬
        - find: 원소 검색
        - count: 특정 값의 개수 세기
        - copy: 컨테이너 간 복사
        - transform: 원소들에 함수 적용

    2. 알고리즘 사용 예:

        ```cpp
        #include <algorithm>
        #include <vector>
        #include <iostream>
        using namespace std;

        int main() {
            vector<int> vec = {5, 2, 8, 1, 9};

            // 정렬
            sort(vec.begin(), vec.end());

            // 출력
            for(int num : vec) {
                cout << num << " ";
            }
            // 출력: 1 2 5 8 9

            // 원소 찾기
            auto it = find(vec.begin(), vec.end(), 5);
            if(it != vec.end()) {
                cout << "\nFound 5 at position: " << (it - vec.begin()) << endl;
            }

            return 0;
        }
        ```

4. 함수 객체 (Functors)
    - 함수 객체는 함수처럼 동작하는 객체로, STL 알고리즘과 함께 자주 사용됩니다.

    ```cpp
    #include <algorithm>
    #include <vector>
    #include <iostream>
    using namespace std;

    class IsOdd {
    public:
        bool operator()(int num) {
            return num % 2 != 0;
        }
    };

    int main() {
        vector<int> vec = {1, 2, 3, 4, 5};

        int count = count_if(vec.begin(), vec.end(), IsOdd());
        cout << "Number of odd elements: " << count << endl;
        // 출력: Number of odd elements: 3

        return 0;
    }
    ```

### 메모리 관리와 스마트 포인터 ###

- C++에서 메모리 관리는 매우 중요한 주제입니다. 적절한 메모리 관리는 프로그램의 성능과 안정성에 큰 영향을 미칩니다.

1. 동적 메모리 할당
    - C++에서는 `new`와 `delete`연산자를 사용하여 동적으로 메모리를 할당하고 해제합니다.

    1. new 연산자:

        ```cpp
        int* ptr = new int;  // 단일 정수 할당
        int* arr = new int[10];  // 10개의 정수 배열 할당
        ```

    2. delete 연산자:

        ```cpp
        delete ptr;  // 단일 객체 해제
        delete[] arr;  // 배열 해제
        ```

    3. 주의사항:
        - 메모리 누수: `new`로 할당한 메모리를 `delete`로 해제하지 않으면 메모리 누수가 발생합니다.
        - 댕글링 포인터: 이미 해제된 메모리를 가리키는 포인터를 사용하면 위험합니다.

2. 스마트 포인터
    - 스마트 포인터는 자동으로 메모리를 관리해주는 객체로, C++11부터 도입되었습니다. 주요 스마트 포인터 유형은 다음과 같습니다.

    1. unique_ptr:
        - 객체에 대한 단독 소유권을 가집니다.
        - 복사할 수 없고, 이동만 가능합니다.

        ```cpp
        #include <memory>
        #include <iostream>
        using namespace std;

        int main() {
            unique_ptr<int> ptr1(new int(10));
            cout << *ptr1 << endl;  // 10 출력

            // unique_ptr<int> ptr2 = ptr1;  // 컴파일 에러: 복사 불가능
            unique_ptr<int> ptr2 = move(ptr1);  // 이동은 가능

            if (!ptr1) {
                cout << "ptr1 is empty" << endl;
            }

            cout << *ptr2 << endl;  // 10 출력

            return 0;
        }
        ```

    2. shared_ptr:
        - 여러 포인터가 하나의 객체를 공유할 수 있습니다.
        - 참조 카운트를 사용하여 마지막 포인터가 소멸될 때 자동으로 메모리를 해제합니다.

        ```cpp
        #include <memory>
        #include <iostream>
        using namespace std;

        int main() {
            shared_ptr<int> ptr1 = make_shared<int>(20);
            shared_ptr<int> ptr2 = ptr1;

            cout << *ptr1 << ", " << *ptr2 << endl;  // 20, 20 출력
            cout << "Count: " << ptr1.use_count() << endl;  // 2 출력

            ptr1.reset();  // ptr1 해제
            cout << "Count: " << ptr2.use_count() << endl;  // 1 출력

            return 0;
        }
        ```

    3. weak_ptr:
        - shared_ptr의 순환 참조 문제를 해결하기 위해 사용됩니다.
        - 객체의 수명에 영향을 주지 않으면서 shared_ptr이 관리하는 객체에 접근할 수 있습니다.

        ```cpp
        #include <memory>
        #include <iostream>
        using namespace std;

        int main() {
            shared_ptr<int> shared = make_shared<int>(30);
            weak_ptr<int> weak = shared;

            if (auto observe = weak.lock()) {
                cout << "Value: " << *observe << endl;  // 30 출력
            } else {
                cout << "Weak ptr is expired" << endl;
            }

            shared.reset();

            if (auto observe = weak.lock()) {
                cout << "Value: " << *observe << endl;
            } else {
                cout << "Weak ptr is expired" << endl;  // 이 메시지 출력
            }

            return 0;
        }
        ```

3. RAII(Resource Acquistion Is Initialization)
    - RAII는 C++의 핵심 개념 중 하나로, 리소스의 수명을 객체의 수명과 연결시키는 기법입니다.

    ```cpp
    class FileHandler {
    private:
        FILE* file;

    public:
        FileHandler(const char* filename, const char* mode) {
            file = fopen(filename, mode);
            if (!file) throw runtime_error("Could not open file");
        }

        ~FileHandler() {
            if (file) {
                fclose(file);
            }
        }

        // 파일 조작 메서드들...
    };

    int main() {
        try {
            FileHandler fh("example.txt", "w");
            // 파일 사용...
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
        // FileHandler의 소멸자가 자동으로 호출되어 파일을 닫음
        return 0;
    }
    ```

4. 메모리 관리 최적화 기법
    1. 메모리 풀:
        - 자주 할당/해제되는 작은 객체들을 위해 미리 큰 메모리 블록을 할당하고 관리합니다.

    2. 객체 재사용:
        - 객체를 삭제하는 대신 재사용하여 할당/해제 비용을 줄입니다.

    3. 맞춤 할당자:
        - 특정 용도에 최적화된 사용자 정의 할당자를 사용합니다.

### 예외 처리 ###

- 예외 처리는 프로그램 실행 중 발생할 수 있는 오류 상황을 관리하는 메커니즘입니다. C++에서는 try, catch, throw 키워드를 사용하여 예외를 처리합니다.

1. 기본 예외 처리 구문

    ```cpp
    #include <iostream>
    #include <stdexcept>

    using namespace std;

    int main() {
        try {
            // 예외가 발생할 수 있는 코드
            throw runtime_error("An error occurred");
        }
        catch (const exception& e) {
            // 예외 처리
            cout << "Caught exception: " << e.what() << endl;
        }
        return 0;
    }
    ```

2. 다중 catch 블록
    - 여러 종류의 예외를 처리할 수 있습니다.

    ```cpp
    try {
        // 예외 발생 가능 코드
    }
    catch (const invalid_argument& e) {
        cout << "Invalid argument: " << e.what() << endl;
    }
    catch (const runtime_error& e) {
        cout << "Runtime error: " << e.what() << endl;
    }
    catch (...) {
        cout << "Unknown exception occurred" << endl;
    }
    ```

3. 사용자 정의 예외
    - 자신만의 예외 클래스를 정의할 수 있습니다.

    ```cpp
    class MyException : public exception {
    public:
        const char* what() const noexcept override {
            return "My custom exception";
        }
    };

    try {
        throw MyException();
    }
    catch (const MyException& e) {
        cout << e.what() << endl;
    }
    ```

4. 함수에서 예외 던지기
    - 함수가 던질 수 있는 예외를 명시할 수 있습니다.

    ```cpp
    void riskyFunction() throw(runtime_error) {
        // 함수 내용
        if (/* 오류 조건 */) {
            throw runtime_error("An error in riskyFunction");
        }
    }

    // C++11 이후 권장 방식
    void modernRiskyFunction() noexcept(false) {
        // 함수 내용
    }
    ```

5. 예외 재던지기
    - catch 블록에서 예외를 다시 던질 수 있습니다.

    ```cpp
    try {
        // 코드
    }
    catch (const exception& e) {
        // 일부 처리
        cout << "Exception caught, but rethrowing" << endl;
        throw; // 같은 예외를 다시 던짐
    }
    ```

6. 스택 풀기
    - 예외가 발생하면 스택에서 적절한 catch 블록을 찾을 때까지 함수 호출을 역순으로 되돌립니다.
    이 과정에서 지역 객체들의 소멸자가 호출됩니다.

    ```cpp
    class Resource {
    public:
        ~Resource() {
            cout << "Resource cleaned up" << endl;
        }
    };

    void function() {
        Resource r;
        throw runtime_error("Error in function");
    }

    int main() {
        try {
            function();
        }
        catch (const exception& e) {
            cout << e.what() << endl;
        }
        return 0;
    }
    ```

7. noexcept 지정자
    - 함수가 예외를 던지지 않음을 보장합니다.

    ```cpp
    void safeFunction() noexcept {
        // 이 함수는 예외를 던지지 않음을 보장
    }
    ```

8. 예외 처리 모범 사례
    1. 구체적인 예외를 사용하세요. std::exception을 상속받아 더 구체적인 예외 클래스를 만들어 사용하는 것이 좋습니다.
    2. 예외는 진짜 예외적인 상황에서만 사용하세요. 일반적인 흐름 제어에는 사용하지 마세요.
    3. 예외 안정성을 고려하세요. 예외가 발생해도 리소스 누수가 없어야 합니다.
    4. catch 블록에서는 의미 있는 복구 작업을 수행하세요.
    5. 전역 예외 핸들러를 사용하여 처리되지 않은 예외를 잡을 수 있습니다.

    ```cpp
    #include <exception>
    #include <iostream>

    void myTerminate() {
        std::cerr << "Uncaught exception!" << std::endl;
        std::abort();
    }

    int main() {
        std::set_terminate(myTerminate);
        // 프로그램 코드...
        return 0;
    }
    ```

### 템플릿 프로그래밍 ###

- 템플릿은 C++의 강력한 기능 중 하나로, 제네릭 프로그래밍을 가능하게 합니다. 이를 통해 타입에 독립적인 코드를 작성할 수 있습니다.

1. 함수 템플릿
    - 함수 템플릿은 여러 타입에 대해 동작하는 함수를 정의할 수 있게 해줍니다.

    ```cpp
    template <typename T>
    T max(T a, T b) {
        return (a > b) ? a : b;
    }

    int main() {
        cout << max(10, 20) << endl;  // int 버전
        cout << max(10.5, 20.7) << endl;  // double 버전
        cout << max('a', 'z') << endl;  // char 버전
        return 0;
    }
    ```

2. 클래스 템플릿
    - 클래스 템플릿을 사용하면 여러 타입에 대해 동작하는 클래스를 정의할 수 있습니다.

    ```cpp
    template <typename T>
    class Stack {
    private:
        vector<T> elements;

    public:
        void push(const T& element) {
            elements.push_back(element);
        }

        T pop() {
            if (elements.empty()) {
                throw out_of_range("Stack is empty");
            }
            T top = elements.back();
            elements.pop_back();
            return top;
        }
    };

    int main() {
        Stack<int> intStack;
        intStack.push(10);
        intStack.push(20);
        cout << intStack.pop() << endl;  // 20

        Stack<string> stringStack;
        stringStack.push("Hello");
        stringStack.push("World");
        cout << stringStack.pop() << endl;  // World

        return 0;
    }
    ```

3. 템플릿 특수화
    - 특정 타입에 대해 템플릿의 특별한 구현을 제공할 수 있습니다.

    ```cpp
    template <typename T>
    void print(T value) {
        cout << "Generic: " << value << endl;
    }

    template <>
    void print<char>(char value) {
        cout << "Char: " << value << " (ASCII: " << static_cast<int>(value) << ")" << endl;
    }

    int main() {
        print(10);  // Generic: 10
        print('A');  // Char: A (ASCII: 65)
        return 0;
    }
    ```

4. 가변 인자 템플릿
    - C++11부터는 임의의 개수의 템플릿 인자를 받을 수 있습니다.

    ```cpp
    template<typename... Args>
    void printAll(Args... args) {
        (cout << ... << args) << endl;
    }

    int main() {
        printAll(1, 2, 3, 4, 5);  // 12345
        printAll("Hello", ' ', "World", '!');  // Hello World!
        return 0;
    }
    ```

5. SFINAE (Substitution Failure is Not An Error)
    - 템플릿 인스턴스화 과정에서 실패가 발생해도 컴파일러가 다른 오버로드를 찾도록 하는 기법입니다.

    ```cpp
    #include <type_traits>

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
    void foo(T t) {
        cout << "Integer version: " << t << endl;
    }

    template <typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
    void foo(T t) {
        cout << "Floating point version: " << t << endl;
    }

    int main() {
        foo(10);    // Integer version: 10
        foo(3.14);  // Floating point version: 3.14
        return 0;
    }
    ```

6. 템플릿 메타 프로그래밍
    - 컴파일 시간에 계산을 수행하는 기법입니다.

    ```cpp
    template <int N>
    struct Factorial {
        static const int value = N * Factorial<N-1>::value;
    };

    template <>
    struct Factorial<0> {
        static const int value = 1;
    };

    int main() {
        cout << Factorial<5>::value << endl;  // 120
        return 0;
    }
    ```

7. 타입 특성 (Type Traits)
    - C++11부터 `<type_traits>`헤더를 통해 타입에 대한 정보를 컴파일 시간에 얻을 수 있습니다.

    ```cpp
    #include <type_traits>

    template <typename T>
    void checkType(T value) {
        if (is_integral<T>::value) {
            cout << "Integral type" << endl;
        } else if (is_floating_point<T>::value) {
            cout << "Floating point type" << endl;
        } else {
            cout << "Other type" << endl;
        }
    }

    int main() {
        checkType(10);    // Integral type
        checkType(3.14);  // Floating point type
        checkType("Hello");  // Other type
        return 0;
    }
    ```


### C++11 이후의 새로운 기능 ###

1. 람다 표현식
    - 람다는 익명 함수를 생성하는 간편한 방법을 제공합니다.

    ```cpp
    #include <iostream>
    #include <vector>
    #include <algorithm>

    int main() {
        std::vector<int> v = {1, 2, 3, 4, 5};
        
        std::for_each(v.begin(), v.end(), [](int n) {
            std::cout << n * n << " ";
        });
        // 출력: 1 4 9 16 25

        return 0;
    }
    ```

2. auto 키워드
    - `auto`는 컴파일러가 변수의 타입을 추론하도록 합니다.

    ```cpp
    auto i = 42;  // int
    auto d = 3.14;  // double
    auto s = "Hello";  // const char*

    std::vector<int> v;
    auto it = v.begin();  // std::vector<int>::iterator
    ```

3. 범위 기반 for 루프
    - 컨테이너의 모든 요소를 간단히 순회할 수 있습니다.

    ```cpp
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    // 출력: 1 2 3 4 5
    ```

4. nullptr
    - 널 포인터를 나타내는 키워드입니다. 0또는 NULL보다 타입 안전합니다.

    ```cpp
    int* p = nullptr;
    ```

5. enum class
    - 강한 타입의 열거형을 제공합니다.

    ```cpp
    enum class Color { Red, Green, Blue };
    Color c = Color::Red;
    ```

6. move 의미론과 rvalue 참조
    - 효율적인 리소스 관리를 위한 기능입니다.

    ```cpp
    std::string s1 = "Hello";
    std::string s2 = std::move(s1);  // s1의 내용을 s2로 이동
    ```

7. constexpr
    - 컴파일 시간 상수 표현식을 정의합니다.

    ```cpp
    constexpr int square(int x) { return x * x; }
    constexpr int result = square(5);  // 컴파일 시간에 계산됨
    ```

8. 초기화 리스트
    - 객체를 초기화하는 일관된 방법을 제공합니다.

    ```cpp
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::map<std::string, int> m = {{"apple", 1}, {"banana", 2}};
    ```

9. decltype
    - 표현식의 타입을 추론합니다.

    ```cpp
    int i = 42;
    decltype(i) j = i * 2;  // j는 int 타입
    ```

10. 스마트 포인터 (C++11)
    - 메모리 관리를 자동화하는 포인터 타입입니다.

    ```cpp
    #include <memory>

    std::unique_ptr<int> p1(new int(42));
    std::shared_ptr<int> p2 = std::make_shared<int>(42);
    ```

11. 스레드 지원 라이브러리 (C++11)
    - 멀티스레딩을 위한 표준 라이브러리를 제공합니다.

    ```cpp
    #include <thread>

    void func() { /* ... */ }
    std::thread t(func);
    t.join();
    ```

12. 튜플 (C++11)
    - 여러 값을 그룹화할 수 있는 템플릿 클래스입니다.

    ```cpp
    #include <tuple>

    std::tuple<int, std::string, double> t(42, "Hello", 3.14);
    std::cout << std::get<1>(t) << std::endl;  // "Hello" 출력
    ```

13. std::array(C++11)
    - 고정 크기 배열을 위한 컨테이너입니다.

    ```cpp
    #include <array>

    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    ```

14. 가변 템플릿 (C++11)
    - 임의의 개수의 템플릿 인자를 받을 수 있습니다.

    ```cpp
    template<typename... Args>
    void print(Args... args) {
        (std::cout << ... << args) << std::endl;
    }

    print(1, 2, 3, "Hello");  // "123Hello" 출력
    ```

15. std::optional(C++17)
    - 값이 있을 수도 있고 없을 수도 있는 객체를 표현합니다.

    ```cpp
    #include <optional>

    std::optional<int> divide(int a, int b) {
        if (b == 0) return std::nullopt;
        return a / b;
    }
    ```

### 동시성 프로그래밍 ###

- C++11부터 표준 라이브러리에 동시성 프로그래밍을 위한 도구들이 추가되었습니다. 이를 통해 멀티스레드 프로그래밍이 더욱 쉬워졌습니다.

1. std::thread
    - `std::thread`는 새로운 스레드를 생성하고 관리하는 데 사용됩니다.

    ```cpp
    #include <iostream>
    #include <thread>

    void foo() {
        std::cout << "Hello from thread!" << std::endl;
    }

    int main() {
        std::thread t(foo);
        t.join();  // 스레드가 완료될 때까지 대기
        return 0;
    }
    ```

2. 뮤텍스와 락
    - `std::mutex`는 공유 자원에 대한 동기화를 제공합니다.

    ```cpp
    #include <iostream>
    #include <thread>
    #include <mutex>

    std::mutex mtx;
    int shared_data = 0;

    void increment() {
        std::lock_guard<std::mutex> lock(mtx);
        ++shared_data;
    }

    int main() {
        std::thread t1(increment);
        std::thread t2(increment);
        t1.join();
        t2.join();
        std::cout << "shared_data: " << shared_data << std::endl;
        return 0;
    }
    ```

3. 조건 변수
    - `std::condition_variable`은 스레드 간 통신을 위해 사용됩니다.

    ```cpp
    #include <iostream>
    #include <thread>
    #include <mutex>
    #include <condition_variable>

    std::mutex mtx;
    std::condition_variable cv;
    bool ready = false;

    void print_id(int id) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []{ return ready; });
        std::cout << "Thread " << id << std::endl;
    }

    int main() {
        std::thread threads[10];
        for (int i = 0; i < 10; ++i)
            threads[i] = std::thread(print_id, i);

        {
            std::lock_guard<std::mutex> lock(mtx);
            ready = true;
        }
        cv.notify_all();

        for (auto& th : threads) th.join();
        return 0;
    }
    ```

4. future와 promise
    - `std::future`와 `std::promise`는 비동기 작업의 결과를 주고받는 데 사용됩니다.

    ```cpp
    #include <iostream>
    #include <future>

    int compute() {
        return 42;
    }

    int main() {
        std::future<int> f = std::async(std::launch::async, compute);
        std::cout << "The answer is: " << f.get() << std::endl;
        return 0;
    }
    ```

5. atomic 타입
    - `std::atomic`은 원자적 연산을 제공하여 락 없이도 안전한 동시성 프로그래밍을 가능하게 합니다.

    ```cpp
    #include <iostream>
    #include <thread>
    #include <atomic>

    std::atomic<int> counter(0);

    void increment() {
        for (int i = 0; i < 1000; ++i) {
            ++counter;
        }
    }

    int main() {
        std::thread t1(increment);
        std::thread t2(increment);
        t1.join();
        t2.join();
        std::cout << "Counter: " << counter << std::endl;
        return 0;
    }
    ```

6. 메모리 모델과 메모리 순서
    - C++11은 멀티스레드 프로그램의 동작을 정의하는 메모리 모델을 도입했습니다.

    ```cpp
    #include <atomic>
    #include <thread>

    std::atomic<int> x(0), y(0);
    std::atomic<int> z(0);

    void write_x_then_y() {
        x.store(1, std::memory_order_relaxed);
        y.store(1, std::memory_order_release);
    }

    void read_y_then_x() {
        while (!y.load(std::memory_order_acquire));
        if (x.load(std::memory_order_relaxed) == 0)
            ++z;
    }

    int main() {
        std::thread a(write_x_then_y);
        std::thread b(read_y_then_x);
        a.join();
        b.join();
        return 0;
    }
    ```

7. 스레드 로컬 저장소
    - `thread_local`키워드를 사용하여 각 스레드마다 고유한 변수를 만들 수 있습니다.

    ```cpp
    #include <iostream>
    #include <thread>

    thread_local int counter = 0;

    void increment() {
        ++counter;
        std::cout << "Counter: " << counter << " in thread " << std::this_thread::get_id() << std::endl;
    }

    int main() {
        std::thread t1(increment);
        std::thread t2(increment);
        t1.join();
        t2.join();
        increment();
        return 0;
    }
    ```

8. 병렬 알고리즘
    - C++17부터는 많은 표준 라이브러리 알고리즘에 병렬 실행 정책을 지정할 수 있습니다.

    ```cpp
    #include <algorithm>
    #include <execution>
    #include <vector>

    int main() {
        std::vector<int> v(1000000);
        std::iota(v.begin(), v.end(), 0);

        std::sort(std::execution::par, v.begin(), v.end());
        return 0;
    }
    ```

### 파일 입출력과 스트림 ###

- C++에서는 파일 입출력과 다양한 형태의 스트림을 처리하기 위한 풍부한 라이브러리를 제공합니다.

1. 파일 스트림(fstream)
    - `<fstream>`헤더는 파일 입출력을 위한 클래스들을 제공합니다.

    1. 파일 쓰기(ofstream)
        ```cpp
        #include <fstream>
        #include <iostream>

        int main() {
            std::ofstream outFile("example.txt");
            
            if (outFile.is_open()) {
                outFile << "Hello, World!" << std::endl;
                outFile << "This is a test." << std::endl;
                outFile.close();
            }
            else {
                std::cout << "Unable to open file" << std::endl;
            }

            return 0;
        }
        ```

    2. 파일 읽기 (ifstream)
        ```cpp
        #include <fstream>
        #include <iostream>
        #include <string>

        int main() {
            std::ifstream inFile("example.txt");
            std::string line;

            if (inFile.is_open()) {
                while (std::getline(inFile, line)) {
                    std::cout << line << std::endl;
                }
                inFile.close();
            }
            else {
                std::cout << "Unable to open file" << std::endl;
            }

            return 0;
        }
        ```

2. 문자열 스트림 (stringstream)
    - `<sstream>`헤더는 문자열을 스트림으로 처리할 수 있게 해줍니다.

    ```cpp
    #include <sstream>
    #include <iostream>

    int main() {
        std::stringstream ss;
        ss << "Hello " << 42 << " " << 3.14;
        
        std::string word;
        int number;
        double pi;
        
        ss >> word >> number >> pi;
        
        std::cout << word << " " << number << " " << pi << std::endl;

        return 0;
    }
    ```

3. 이진 파일 입출력
    - 이진 파일을 읽고 쓰기 위해서는 ios::binary 플래그를 사용합니다.

    ```cpp
    #include <fstream>
    #include <iostream>

    struct Person {
        char name[50];
        int age;
    };

    int main() {
        Person p1 = {"John Doe", 30};

        // 이진 파일 쓰기
        std::ofstream outFile("person.dat", std::ios::binary);
        if (outFile.is_open()) {
            outFile.write(reinterpret_cast<char*>(&p1), sizeof(Person));
            outFile.close();
        }

        // 이진 파일 읽기
        Person p2;
        std::ifstream inFile("person.dat", std::ios::binary);
        if (inFile.is_open()) {
            inFile.read(reinterpret_cast<char*>(&p2), sizeof(Person));
            inFile.close();
        }

        std::cout << p2.name << ", " << p2.age << std::endl;

        return 0;
    }
    ```

4. 파일 포지션 조작
    - 파일 내에서 읽기/쓰기 위치를 이동할 수 있습니다.

    ```cpp
    #include <fstream>
    #include <iostream>

    int main() {
        std::fstream file("example.txt", std::ios::in | std::ios::out);
        
        if (file.is_open()) {
            file << "Hello, World!";
            
            file.seekg(7);  // 읽기 위치를 7번째 문자로 이동
            char c;
            file.get(c);
            std::cout << "Character at position 7: " << c << std::endl;

            file.seekp(0, std::ios::end);  // 쓰기 위치를 파일 끝으로 이동
            file << " Appended text.";

            file.close();
        }

        return 0;
    }
    ```

5. 파일 상태 확인
    - 파일 조작 중 오류를 확인할 수 있습니다.

    ```cpp
    #include <fstream>
    #include <iostream>

    int main() {
        std::ifstream file("nonexistent.txt");
        
        if (file.fail()) {
            std::cout << "Failed to open file" << std::endl;
        }

        int number;
        file >> number;
        if (file.bad()) {
            std::cout << "I/O error while reading" << std::endl;
        }
        else if (file.eof()) {
            std::cout << "End of file reached" << std::endl;
        }
        else if (file.fail()) {
            std::cout << "Non-integer data encountered" << std::endl;
        }

        return 0;
    }
    ```

6. 사용자 정의 조작자
    - 스트림의 동작을 사용자가 정의할 수 있습니다.

    ```cpp
    #include <iostream>
    #include <iomanip>

    std::ostream& currency(std::ostream& os) {
        os << "$ ";
        return os;
    }

    int main() {
        double price = 19.99;
        std::cout << currency << std::fixed << std::setprecision(2) << price << std::endl;
        return 0;
    }
    ```

### 고급 주제 ###

1. 가상 함수와 추상 클래스
    - 가상 함수는 다형성을 구현하는 핵심 메커니즘입니다.

    ```cpp
    class Animal {
    public:
        virtual void makeSound() = 0;  // 순수 가상 함수
        virtual ~Animal() {}  // 가상 소멸자
    };

    class Dog : public Animal {
    public:
        void makeSound() override {
            std::cout << "Woof!" << std::endl;
        }
    };

    class Cat : public Animal {
    public:
        void makeSound() override {
            std::cout << "Meow!" << std::endl;
        }
    };

    int main() {
        Animal* animals[] = {new Dog(), new Cat()};
        for(auto animal : animals) {
            animal->makeSound();
            delete animal;
        }
        return 0;
    }
    ```

2. 다중 상속과 가상 상속
    - C++는 다중 상속을 지원하지만, 다이아몬드 문제를 해결하기 위해 가상 상속을 사용합니다.

    ```cpp
    class A {
    public:
        int a;
    };

    class B : virtual public A {
    public:
        int b;
    };

    class C : virtual public A {
    public:
        int c;
    };

    class D : public B, public C {
    public:
        int d;
    };

    int main() {
        D obj;
        obj.a = 1;  // 모호성 없음
        return 0;
    }
    ```

3. RTTI (Run-Time Type Information)
    - RTTI를 사용하면 런타임에 객체의 타입 정보를 얻을 수 있습니다.

    ```cpp
    #include <iostream>
    #include <typeinfo>

    class Base {
    public:
        virtual ~Base() {}
    };

    class Derived : public Base {};

    int main() {
        Base* b = new Derived();
        
        if(typeid(*b) == typeid(Derived)) {
            std::cout << "b is pointing to a Derived object" << std::endl;
        }
        
        delete b;
        return 0;
    }
    ```

4. 이동 의미론 (Move Semantics)
    - 이동 의미론은 불필요한 복사를 피하고 성능을 향상시킵니다.

    ```cpp
    #include <iostream>
    #include <vector>

    class BigObject {
        std::vector<int> data;
    public:
        BigObject(size_t size) : data(size) {}
        BigObject(const BigObject& other) = delete;
        BigObject(BigObject&& other) noexcept : data(std::move(other.data)) {}
    };

    int main() {
        BigObject obj1(1000000);
        BigObject obj2 = std::move(obj1);  // 이동 생성자 호출
        return 0;
    }
    ```

5. 완벽한 전달 (Perfect Forwarding)
    - 템플릿과 rvalue 참조를 사용하여 인자를 그대로 전달합니다.

    ```cpp
    #include <iostream>
    #include <utility>

    void processValue(int& x) { std::cout << "lvalue" << std::endl; }
    void processValue(int&& x) { std::cout << "rvalue" << std::endl; }

    template<typename T>
    void forwardValue(T&& x) {
        processValue(std::forward<T>(x));
    }

    int main() {
        int a = 5;
        forwardValue(a);  // 출력: lvalue
        forwardValue(5);  // 출력: rvalue
        return 0;
    }
    ```

6. 컴파일 시간 계산과 type traits
    - 컴파일 시간에 계산된 타입 조작을 수행할 수 있습니다.

    ```cpp
    #include <iostream>
    #include <type_traits>

    template<int N>
    struct Factorial {
        static constexpr int value = N * Factorial<N-1>::value;
    };

    template<>
    struct Factorial<0> {
        static constexpr int value = 1;
    };

    template<typename T>
    void checkType() {
        if constexpr (std::is_integral<T>::value) {
            std::cout << "T is an integral type" << std::endl;
        } else {
            std::cout << "T is not an integral type" << std::endl;
        }
    }

    int main() {
        std::cout << Factorial<5>::value << std::endl;  // 120
        checkType<int>();  // T is an integral type
        checkType<double>();  // T is not an integral type
        return 0;
    }
    ```

7. 멤버 함수 포인터
    - 클래스의 멤버 함수를 가리키는 포인터를 사용할 수 있습니다.

    ```cpp
    #include <iostream>

    class MyClass {
    public:
        void foo() { std::cout << "foo" << std::endl; }
        void bar() { std::cout << "bar" << std::endl; }
    };

    int main() {
        void (MyClass::*ptr)() = &MyClass::foo;
        MyClass obj;
        (obj.*ptr)();  // 출력: foo
        return 0;
    }
    ```

### 최신 표준 (C++17, C++20) ###

C++는 계속해서 발전하고 있으며, 최신 표준들은 언어를 더욱 강력하고 사용하기 쉽게 만들어졌습니다.

1. C++17의 주요 기능
    1. 구조화된 바인딩 (Structured Bindings)
        ```cpp
        #include <map>
        #include <string>

        int main() {
            std::map<std::string, int> myMap = {{"apple", 1}, {"banana", 2}};
            for (const auto& [key, value] : myMap) {
                // key와 value를 직접 사용
            }
            return 0;
        }
        ```

    2. if문과 switch 문에서의 초기화 구문
        ```cpp
        if (auto it = myMap.find("apple"); it != myMap.end()) {
            // it를 사용
        }
        ```

    3. 내장 std::variant, std::optional, std::any
        ```cpp
        #include <optional>
        #include <variant>
        #include <any>

        std::optional<int> divide(int a, int b) {
            if (b == 0) return std::nullopt;
            return a / b;
        }

        std::variant<int, std::string> v = 10;
        std::any a = 1;
        a = 3.14;
        a = std::string("hello");
        ```

    4. 접힘 표현식 (Fold Expression)
        ```cpp
        template<typename... Args>
        auto sum(Args... args) {
            return (args + ...);
        }
        ```

2. C++20의 주요 기능
    1. 개념 (Concepts)
        ```cpp
        #include <concepts>

        template<typename T>
        concept Numeric = std::is_arithmetic_v<T>;

        template<Numeric T>
        T add(T a, T b) {
            return a + b;
        }
        ```

    2. 범위 (Ranges)
        ```cpp
        #include <ranges>
        #include <vector>

        int main() {
            std::vector<int> v = {1, 2, 3, 4, 5};
            auto even = v | std::views::filter([](int n) { return n % 2 == 0; });
            for (int n : even) {
                // 짝수만 출력
            }
            return 0;
        }
        ```

    3. 코루틴 (Coroutines)
        ```cpp
        #include <coroutine>
        #include <iostream>

        generator<int> range(int start, int end) {
            for (int i = start; i < end; ++i) {
                co_yield i;
            }
        }

        int main() {
            for (int i : range(0, 5)) {
                std::cout << i << ' ';
            }
            return 0;
        }
        ```

    4. 3방향 비교 연산자 (Spaceship Operator)
        ```cpp
        class Point {
            int x, y;
        public:
            auto operator<=>(const Point&) const = default;
        };
        ```

    5. 모듈 (Modules)
        ```cpp
        // math.cpp
        export module math;

        export int add(int a, int b) {
            return a + b;
        }

        // main.cpp
        import math;

        int main() {
            int result = add(5, 3);
            return 0;
        }
        ```

    6. constexpr 가상 함수와 union
        ```cpp
        struct Base {
            constexpr virtual int f() const { return 0; }
        };

        struct Derived : Base {
            constexpr int f() const override { return 1; }
        };

        constexpr int g() {
            Derived d;
            Base& b = d;
            return b.f();  // 컴파일 시간에 1을 반환
        }
        ```

    7. 문자열 리터럴에 대한 constexpr
        ```cpp
        constexpr auto str = "Hello, World!";
        constexpr char c = str[0];  // 컴파일 시간에 'H'
        ```

### 디자인 패턴과 최적화 ###

1. 디자인 패턴
    - 디자인 패턴은 소프트웨어 설계에서 자주 발생하는 문제들에 대한 일반적인 해결책입니다. C++에서 자주 사용되는 몇 가지 패턴을 살펴보겠습니다.

    1. 싱글톤 패턴 (Singletone Pattern)
        ```cpp
        class Singleton {
        private:
            static Singleton* instance;
            Singleton() {}
        public:
            static Singleton* getInstance() {
                if (instance == nullptr) {
                    instance = new Singleton();
                }
                return instance;
            }
        };

        Singleton* Singleton::instance = nullptr;
        ```

    2. 팩토리 패턴 (Factory Pattern)
        ```cpp
        class Animal {
        public:
            virtual void makeSound() = 0;
        };

        class Dog : public Animal {
        public:
            void makeSound() override { std::cout << "Woof!" << std::endl; }
        };

        class Cat : public Animal {
        public:
            void makeSound() override { std::cout << "Meow!" << std::endl; }
        };

        class AnimalFactory {
        public:
            static Animal* createAnimal(std::string type) {
                if (type == "Dog") return new Dog();
                if (type == "Cat") return new Cat();
                return nullptr;
            }
        };
        ```

    3. 옵저버 패턴 (Observer Pattern)
        ```cpp
        #include <vector>
        #include <algorithm>

        class Observer {
        public:
            virtual void update(int value) = 0;
        };

        class Subject {
        private:
            std::vector<Observer*> observers;
            int value;
        public:
            void attach(Observer* obs) { observers.push_back(obs); }
            void detach(Observer* obs) {
                observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
            }
            void notify() {
                for (auto obs : observers) {
                    obs->update(value);
                }
            }
            void setValue(int v) {
                value = v;
                notify();
            }
        };
        ```

2. 성능 최적화 기법
    1. 인라인 함수 사용
        ```cpp
        inline int max(int a, int b) {
            return a > b ? a : b;
        }
        ```

    2. 불필요한 복사 피하기
        ```cpp
        void processVector(const std::vector<int>& vec) {
            // vec를 참조로 받아 불필요한 복사를 피함
        }
        ```

    3. 이동 의미론 활용
        ```cpp
        std::vector<int> createVector() {
            std::vector<int> result(1000000);
            // ... 벡터 초기화
            return result;  // 이동 의미론 활용
        }
        ```
    
    4. 캐시 친화적인 데이터 구조 사용
        ```cpp
        struct SoA {  // Structure of Arrays
            std::vector<int> x, y, z;
        };

        struct AoS {  // Array of Structures
            struct Point { int x, y, z; };
            std::vector<Point> points;
        };
        ```

    5. 컴파일 시간 계산 활용
        ```cpp
        template<int N>
        struct Factorial {
            static constexpr int value = N * Factorial<N-1>::value;
        };

        template<>
        struct Factorial<0> {
            static constexpr int value = 1;
        };

        constexpr int fact5 = Factorial<5>::value;
        ```

    6. 메모리 풀 사용
        ```cpp
        class MemoryPool {
            // ... 메모리 풀 구현
        public:
            void* allocate(size_t size);
            void deallocate(void* p);
        };

        MemoryPool pool;
        ```

    7. 병렬 알고리즘 활용 (C++17 이상)
        ```cpp
        #include <algorithm>
        #include <execution>

        std::vector<int> vec(1000000);
        std::sort(std::execution::par, vec.begin(), vec.end());
        ```

    8. 프로파일링 도구 사용
        - gprof, Valgrind, Visual Studio Profiler 등을 사용하여 병목 지점 식별

    9. 컴파일러 최적화 옵션 활용
        ```bash
        g++ -O3 -march=native program.cpp -o program
        ```

### 프로젝트 구조와 빌드 시스템 ###

- CMake는 크로스 플랫폼 빌드 시스템 생성기입니다. 다양한 운영 체제와 컴파일러에서 동작하는 빌드 파일을 생성할 수 있어 널리 사용됩니다.

1. CMake의 기본 개념
    1. CMakeLists.txt:
        - CMake 프로젝트의 핵심 파일로, 프로젝트 구조와 빌드 방법을 정의합니다.
        
    2. 빌드 디렉토리:
        - 소스 디렉토리와 별도로 빌드 파일을 생성하는 디렉토리입니다.

    3. 생성기(Generator):
        - CMake는 다양한 빌드 시스템 (예: Make, Ninja, Visual Studio)을 위한 파일을 생성할 수 있습니다.

2. 기본 CMakeLists.txt 구조
    ```cmake
    cmake_minimum_required(VERSION 3.10)
    project(MyProject)

    add_executable(MyExecutable main.cpp)
    ```

3. CMake 주요 명령어
    1. 프로젝트 정의:
        ```cmake
        project(MyProject VERSION 1.0 LANGUAGES CXX)
        ```

    2. 실행 파일 추가:
        ```cmake
        add_executable(MyExecutable main.cpp file1.cpp file2.cpp)
        ```

    3. 라이브러리 추가:
        ```cmake
        add_library(MyLibrary STATIC lib1.cpp lib2.cpp)
        ```

    4. 포함 디렉토리 추가:
        ```cmake
        target_include_directories(MyExecutable PRIVATE include)
        ```

    5. 링크 라이브러리:
        ```cmake
        target_link_libraries(MyExecutable PRIVATE MyLibrary)
        ```

    6. 컴파일 옵션 설정
        ```cmake
        target_compile_options(MyExecutable PRIVATE -Wall -Wextra)
        ```

    7. C++ 표준 설정
        ```cmake
        set(CMAKE_CXX_STANDARD 17)
        set(CMAKE_CXX_STANDARD_REQUIRED ON)
        ```

4. 변수 사용
    - CMake에서 변수를 사용하여 코드를 더 유연하게 만들 수 있습니다.
    ```cmake
    set(SOURCES main.cpp file1.cpp file2.cpp)
    add_executable(MyExecutable ${SOURCES})
    ```

5. 조건문
    ```cmake
    if(UNIX)
        target_compile_definitions(MyExecutable PRIVATE PLATFORM_UNIX)
    elseif(WIN32)
        target_compile_definitions(MyExecutable PRIVATE PLATFORM_WINDOWS)
    endif()
    ```

6. 함수와 매크로
    ```cmake
    function(my_function arg1 arg2)
        message("arg1: ${arg1}, arg2: ${arg2}")
    endfunction()

    my_function("Hello" "World")
    ```

7. 서브 디렉토리 추가
    ```cmake
    add_subdirectory(src)
    add_subdirectory(libs/mylib)
    ```

8. 외부 라이브러리 찾기
    ```cmake
    find_package(Boost REQUIRED COMPONENTS system filesystem)
    target_link_libraries(MyExecutable PRIVATE Boost::system Boost::filesystem)
    ```

9. 설치 규칙
    ```cmake
    install(TARGETS MyExecutable DESTINATION bin)
    install(FILES myheader.h DESTINATION include)
    ```

10. 테스트 추가
    ```cmake
    enable_testing()
    add_test(NAME MyTest COMMAND MyTestExecutable)
    ```

11. CMake 사용 예제:
    - 프로젝트 구조:
    ```
    MyProject/
    ├── CMakeLists.txt
    ├── include/
    │   └── mylib.h
    ├── src/
    │   ├── CMakeLists.txt
    │   ├── main.cpp
    │   └── mylib.cpp
    └── tests/
        ├── CMakeLists.txt
        └── test_mylib.cpp
    ```

    - 루트 CMakeLists.txt

        ```cmake
        cmake_minimum_required(VERSION 3.10)
        project(MyProject VERSION 1.0 LANGUAGES CXX)

        set(CMAKE_CXX_STANDARD 17)
        set(CMAKE_CXX_STANDARD_REQUIRED ON)

        add_subdirectory(src)
        add_subdirectory(tests)

        enable_testing()
        ```

    - src/CMakeLists.txt
        
        ```cmake
        add_library(mylib STATIC mylib.cpp)
        target_include_directories(mylib PUBLIC ${CMAKE_SOURCE_DIR}/include)

        add_executable(MyExecutable main.cpp)
        target_link_libraries(MyExecutable PRIVATE mylib)
        ```

    - tests/CMakeLists.txt

        ```cmake
        add_executable(test_mylib test_mylib.cpp)
        target_link_libraries(test_mylib PRIVATE mylib)
        add_test(NAME MyLibTest COMMAND test_mylib)
        ```

12. CMake 사용 방법
    1. CMakeLists.txt 파일 작성
    2. 빌드 디렉토리 생성. `mkdir build && cd build`
    3. CMake 실행: `cmake ..`
    4. 빌드 실행: `cmake --build .`

13. CMake 고급 기능
    1. 사용자 정의 명령어:
        ```cmake
        add_custom_command(OUTPUT generated_file.cpp
                   COMMAND python ${CMAKE_SOURCE_DIR}/scripts/generate.py
                   DEPENDS ${CMAKE_SOURCE_DIR}/scripts/generate.py)
        add_custom_target(generate_sources DEPENDS generated_file.cpp)
        ```

    2. 프로퍼티 설정:
        ```cmake
        set_target_properties(MyExecutable PROPERTIES
            OUTPUT_NAME "my_program"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        )
        ```

    3. 제너레이터 표현식:
        ```cmake
        target_compile_options(MyExecutable PRIVATE
            $<$<CONFIG:Debug>:-g -O0>
            $<$<CONFIG:Release>:-O3>
        )
        ```

## C++ STL 코딩 테스트 필수 정리

1. 입출력 최적화

    1. 기본 입출력 최적화화
        ```cpp
        // 표준 입출력 동기화를 해제하여 입출력 속도 향상
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        ```

    2. Fast I/O 구현
        ```cpp
        // 빠른 정수 입력 구현
        inline int read() {
            int x = 0;
            bool neg = false;
            char c;
            c = getchar();
            if (c == '-') {
                neg = true;
                c = getchar();
            }
            for (; '0' <= c && c <= '9'; c = getchar())
                x = x * 10 + (c - '0');
            if (neg) x = -x;
            return x;
        }

        // 빠른 문자열 입력
        inline void readString(char* str) {
            int idx = 0;
            char c;
            while ((c = getchar()) != '\n' && c != ' ' && c != EOF)
                str[idx++] = c;
            str[idx] = '\0';
        }
        ```

2. 주요 컨테이너
    1. `vector<T>`
        - 동적 배열로, 연속된 메모리 공간에 원소를 저장합니다.
        - 주요 연산자와와 복잡도
            - 삽입/삭제
                - `push_back()`: O(1) 평균
                - `pop_back()`: O(1)
                - `insert()`, `erase()`: O(n)

            - 접근
                - `operator[]`, `at()`: O(1)
            
            - 크기/용량
                - `size()`, `empty()`: O(1)
                - `resize()`: O(n)
                - `reverse()`: O(n)
        
        ```cpp
        vector<int> v;
        v.push_back(1); // 뒤에 원소 추가
        v.pop_back(); // 마지막 원소 제거
        v.insert(v.begin() + 1, 2); // 특정 위치에 삽입
        v.erase(v.begin()); // 특정 위치의 원소 삭제
        v.clear(); // 모든 원소 제거

        // 초기화
        vector<int> v1(5, 0) // 크기 5, 모든 원소 0으로 초기화
        vector<int> v2 = {1, 2, 3}; // 초기화 리스트 사용

        // 주의사항과 최적화
        // Common Pitfalls 방지
        v.reserve(n);  // push_back 전에 미리 공간 할당
        v.shrink_to_fit();  // 여분 메모리 해제

        // 2차원 벡터 초기화 최적화
        vector<vector<int>> graph(n, vector<int>(m, 0));  // 올바른 방법
        // vector<vector<int>> graph[n][m];  // 잘못된 방법

        // 벡터 내 원소 제거 시 주의사항
        v.erase(remove(v.begin(), v.end(), value), v.end());  // remove-erase 이디엄
        v.erase(unique(v.begin(), v.end()), v.end());  // 중복 제거

        // 벡터 재할당 없이 앞쪽 원소 제거
        v.erase(v.begin());  // O(n) 소요
        // 대안: deque 사용 고려
        ```

    2. `deque<T>`
        - 양쪽 끝에서 삽입/삭제가 효율적인 double-ended queue입니다.
        - 주요 연산자와 복잡도
            - 삽입/삭제
                - `push_back()`, `push_front()`: O(1) 평균
                - `pop_back()`, `pop_front()`: O(1)
                - `insert()`, `erase()`: O(n)

            - 접근
                - `operator[]`, `at()`: O(1)

        ```cpp
        deque<int> dq;
        dq.push_front(1); // 앞에 원소 추가
        dq.push_back(2); // 뒤에 원소 추가
        dq.pop_front(); // 앞 원소 제거
        dq.pop_back(); // 뒤 원소 제거
        ```

    3. `set<T>`, `multiset<T>`
        - 정렬된 상태를 유지하는 균형 이진 트리입니다.
            - set: 중복을 허용하지 않음.
            - multiset: 중복을 허용.

        - 주요 연산자와 복잡도
            - 삽입/삭제/검색: O(log n)
                - `insert()`, `erase()`, `find()`
            
            - 정렬 상태 유지: 자동
            - 특수 연산
                - `lower_bound()`, `upper_bound()`: O(log n)

        ```cpp
        set<int> s;
        s.insert(1);                // 원소 삽입
        s.erase(1);                 // 원소 제거
        auto it = s.find(1);        // 원소 검색
        auto lb = s.lower_bound(1); // 이상인 첫 원소
        auto ub = s.upper_bound(1); // 초과인 첫 원소

        // multiset 특수 사용
        multiset<int> ms;
        ms.insert(1);
        ms.insert(1);      // 중복 허용
        ms.erase(ms.find(1)); // 특정 위치의 원소만 제거
        ms.erase(1);          // 값이 1인 모든 원소 제거

        // 주의사항과 최적화
        // erase 사용 시 주의사항
        s.erase(s.find(value));  // 특정 위치의 원소만 제거
        s.erase(value);          // 해당 값을 가진 모든 원소 제거

        // 커스텀 비교자 사용
        struct Compare {
            bool operator()(const pair<int,int>& a, const pair<int,int>& b) const {
                if (a.first == b.first) return a.second < b.second;
                return a.first < b.first;
            }
        };
        set<pair<int,int>, Compare> custom_set;

        // lower_bound와 upper_bound 활용
        auto it = s.lower_bound(value);
        if (it != s.begin()) {
            --it;  // value보다 작은 최대값
        }
        ```

    4. `map<k, v>`, `multimap<K, V>`
        - 키-값 쌍을 저장하는 균형 이진 트리입니다.
            - map: 키 중복 불가
            - multimap: 키 중복 허용

        - 주요 연산자와 복잡도
            - 삽입/삭제/검색: O(log n)
            - 키를 통한 접근: O(log n)

        ```cpp
        map<string, int> m;
        m["key"] = 1;             // 삽입 또는 수정
        m.insert({"key2", 2});    // 삽입
        m.erase("key");           // 삭제
        auto it = m.find("key2"); // 검색

        // 없는 키 접근 시 기본값 처리
        if(m.count("key3") > 0) {
            cout << m["key3"];
        }
        ```

    5. `unordered_set<T>`, `unordered_map<K, V>`
        - 해시 테이블을 사용하는 컨테이너입니다.
        - 주요 연산자와 복잡도
            - 삽입/삭제/검색: O(1) 평균, O(n) 최악
            - 정렬되지 않음.

        ```cpp
        unordered_set<int> us;
        us.insert(1);       // O(1) 평균
        us.erase(1);        // O(1) 평균
        auto it = us.find(1); // O(1) 평균

        unordered_map<string, int> um;
        um["key"] = 1;      // O(1) 평균
        um.erase("key");    // O(1) 평균

        // 최적화
        // 해시 충돌 최소화를 위한 커스텀 해시 함수
        struct pair_hash {
            template <class T1, class T2>
            size_t operator()(const pair<T1, T2>& p) const {
                auto h1 = hash<T1>{}(p.first);
                auto h2 = hash<T2>{}(p.second);
                return h1 ^ (h2 << 1);
            }
        };
        unordered_map<pair<int,int>, int, pair_hash> map;

        // 버킷 크기 최적화
        unordered_map<int,int> um;
        um.reserve(expected_size);  // 해시 테이블 재해시 횟수 감소
        um.max_load_factor(0.25);   // 로드 팩터 조정으로 성능 최적화
        ```

    6. `priority_queue<T>`
        - 최대 힙 또는 최소 힙을 구현한 우선순위 큐입니다.
        - 주요 연산자와 복잡도
            - 삽입/삭제: O(log n)
            - 최댓값/최솟값 접근: O(1)

        ```cpp
        // 최대 힙 (기본)
        priority_queue<int> pq;

        // 최소 힙
        priority_queue<int, vector<int>, greater<int>> min_pq;

        pq.push(1);    // 원소 삽입
        pq.pop();      // 최댓값 제거
        int top = pq.top(); // 최댓값 확인

        // 구조체/클래스 사용 시 비교 연산자 정의
        struct Point {
            int x, y;
            bool operator<(const Point& p) const {
                return x < p.x;
            }
        };
        priority_queue<Point> pq_point;

        // 최소값을 위한 여러 방법
        priority_queue<int, vector<int>, greater<int>> min_pq;  // 방법 1
        priority_queue<int> max_pq;  // 방법 2: 부호를 반대로 저장

        // 구조체에 대한 우선순위 큐
        struct Item {
            int val, idx;
            bool operator<(const Item& other) const {
                return val > other.val;  // 최소 힙을 위해 부등호 방향 주의
            }
        };
        priority_queue<Item> pq;

        // 다익스트라에서의 활용
        using pii = pair<int,int>;
        priority_queue<pii, vector<pii>, greater<pii>> pq;  // {거리, 정점}
        ```

3. 주요 알고리즘
    1. 정렬 관련
        ```cpp
        vector<int> v = {3,1,4,1,5};

        // 기본 정렬 (오름차순)
        sort(v.begin(), v.end());

        // 내림차순 정렬
        sort(v.begin(), v.end(), greater<int>());

        // 사용자 정의 비교 함수
        sort(v.begin(), v.end(), [](int a, int b) {
            return a > b;
        });

        // 부분 정렬
        partial_sort(v.begin(), v.begin() + 3, v.end());

        // stable 정렬
        stable_sort(v.begin(), v.end());

        // nth_element: n번째 원소를 찾고 해당 위치에 배치
        nth_element(v.begin(), v.begin() + n, v.end());

        // partial_sort 활용 (Top-K 문제)
        partial_sort(v.begin(), v.begin() + k, v.end());  // k번째까지만 정렬

        // stable_partition으로 조건에 따른 안정적 분할
        stable_partition(v.begin(), v.end(), [](int x) {
            return x % 2 == 0;  // 짝수를 앞으로
        });

        // inplace_merge를 이용한 구간 병합
        inplace_merge(v.begin(), v.begin() + mid, v.end());

        // nth_element 활용 (중앙값, k번째 원소)
        nth_element(v.begin(), v.begin() + v.size()/2, v.end());  // 중앙값
        ```

    2. 이진 탐색
        ```cpp
        vector<int> v = {1,2,3,4,5};

        // 원소 존재 여부 확인
        bool exists = binary_search(v.begin(), v.end(), 3);

        // lower_bound: 이상인 첫 원소의 위치
        auto lb = lower_bound(v.begin(), v.end(), 3);

        // upper_bound: 초과인 첫 원소의 위치
        auto ub = upper_bound(v.begin(), v.end(), 3);

        // equal_range: lower_bound와 upper_bound 쌍 반환
        auto range = equal_range(v.begin(), v.end(), 3);

        // lower_bound 직접 구현 (이해와 커스터마이징용)
        template<typename It, typename T>
        It my_lower_bound(It begin, It end, const T& value) {
            It it;
            typename iterator_traits<It>::difference_type count, step;
            count = distance(begin, end);
            
            while (count > 0) {
                it = begin; 
                step = count / 2;
                advance(it, step);
                
                if (*it < value) {
                    begin = ++it;
                    count -= step + 1;
                } else {
                    count = step;
                }
            }
            return begin;
        }

        // 실수 값에 대한 이진 탐색
        double binary_search_real(double left, double right, function<bool(double)> check) {
            const double EPS = 1e-9;
            while (right - left > EPS) {
                double mid = (left + right) / 2;
                if (check(mid)) right = mid;
                else left = mid;
            }
            return left;
        }
        ```

    3. 순열 관련
        ```cpp
        vector<int> v = {1,2,3};

        // 다음 순열
        do {
            // v의 현재 순열 처리
        } while(next_permutation(v.begin(), v.end()));

        // 이전 순열
        while(prev_permutation(v.begin(), v.end()));

        // 조합 생성 최적화 (비트마스크 활용)
        void combinations(int n, int r) {
            for (int mask = 0; mask < (1 << n); mask++) {
                if (__builtin_popcount(mask) == r) {
                    // mask의 1인 비트가 선택된 원소
                }
            }
        }

        // 다음 순열 직접 구현 (이해용)
        bool my_next_permutation(vector<int>& v) {
            int i = v.size() - 2;
            while (i >= 0 && v[i] >= v[i + 1]) i--;
            if (i < 0) return false;
            
            int j = v.size() - 1;
            while (v[j] <= v[i]) j--;
            swap(v[i], v[j]);
            
            reverse(v.begin() + i + 1, v.end());
            return true;
        }
        ```

    4. 기타 유용한 알고리즘
        ```cpp
        vector<int> v = {1,2,3,4,5};

        // 최대/최소 원소
        auto max_it = max_element(v.begin(), v.end());
        auto min_it = min_element(v.begin(), v.end());

        // 원소 개수 세기
        int count_2 = count(v.begin(), v.end(), 2);

        // 조건을 만족하는 원소 개수
        int count_even = count_if(v.begin(), v.end(), 
            [](int x) { return x % 2 == 0; });

        // 범위 내 합계
        int sum = accumulate(v.begin(), v.end(), 0);

        // 원소 채우기
        fill(v.begin(), v.end(), 0);

        // 중복 원소 제거 (정렬 후)
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());

        // 원소 회전
        rotate(v.begin(), v.begin() + 1, v.end());
        ```

4. 유용한 유틸리티
    1. `pair<T1, T2>`
        - 두 값을 묶어서 저장합니다.
        ```cpp
        pair<int, string> p = {1, "one"};
        p = make_pair(2, "two");
        auto [num, str] = p;  // C++17 구조적 바인딩
        ```

    2. `tuple<Types...>`
        - 여러 값을 묶어서 저장합니다.
        ```cpp
        tuple<int, string, double> t = {1, "one", 1.0};
        t = make_tuple(2, "two", 2.0);
        auto [num, str, dbl] = t;  // C++17 구조적 바인딩
        ```

    3. `string`
        - 문자열 처리를 위한 클래스입니다.
        ```cpp
        string s = "hello";
        s += " world";           // 문자열 연결
        s.substr(0, 5);         // 부분 문자열
        s.find("world");        // 문자열 검색
        s.replace(0, 5, "hi");  // 부분 문자열 교체
        ```

5. 자주 사용되는 문제 유형별 STL 활용
    1. 그래프 문제
        ```cpp
        // 인접 리스트
        vector<vector<int>> adj;
        // 또는
        vector<vector<pair<int,int>>> adj;  // 가중치 그래프

        // BFS
        queue<int> q;
        vector<bool> visited;

        // DFS
        stack<int> s;
        // 또는 재귀 사용

        // 다익스트라
        priority_queue<pair<int,int>> pq;
        ```

    2. 문자열 처리
        ```cpp
        // 문자열 파싱
        stringstream ss(input_string);
        string token;
        while(getline(ss, token, ' ')) {
            // 토큰 처리
        }

        // 문자열 변환
        string num_str = to_string(42);
        int num = stoi("42");
        ```

    3. 구간 처리
        ```cpp
        // 누적 합
        vector<int> psum(n + 1);
        partial_sum(arr.begin(), arr.end(), psum.begin() + 1);

        // 슬라이딩 윈도우
        deque<int> window;
        ```

    4. 집합 연산
        ```cpp
        vector<int> v1 = {1,2,3}, v2 = {2,3,4};
        vector<int> result;

        // 교집합
        set_intersection(v1.begin(), v1.end(),
                        v2.begin(), v2.end(),
                        back_inserter(result));

        // 합집합
        set_union(v1.begin(), v1.end(),
                v2.begin(), v2.end(),
                back_inserter(result));

        // 차집합
        set_difference(v1.begin(), v1.end(),
                    v2.begin(), v2.end(),
                    back_inserter(result));
        ```

6. 성능 최적화 팁
    1. 벡터 크기 미리 할당
        ```cpp
        vector<int> v;
        v.reserve(1000000);  // 메모리 재할당 횟수 감소
        ```

    2. 참조로 전달하여 복사 비용 감소
        ```cpp
        void process(const vector<int>& v) {
            // 벡터를 복사하지 않고 참조로 사용
        }
        ```

    3. emplace 계열 함수 사용
        ```cpp
        vector<pair<int,int>> v;
        v.emplace_back(1, 2);  // 임시 객체 생성 없이 직접 생성
        ```

    4. 적절한 컨테이너 선택
        - 랜덤 접근 많음: vector
        - 양끝 삽입/삭제 많음: deque
        - 정렬된 상태 유지 필요: set/map
        - 해시 기반 빠른 검색 필요: unordered_set/map

7. 실전 최적화 테크닉
    1. 메모리 최적화
        ```cpp
        // 메모리 제한이 빡빡할 때
        #pragma GCC optimize("O3")
        #pragma GCC target("avx2")

        // 불필요한 메모리 해제
        vector<int>().swap(v);  // 벡터 메모리 완전 해제

        // 작은 정수형 활용
        using i8 = int8_t;
        using u8 = uint8_t;
        vector<u8> graph;  // 메모리 절약
        ```

    2. 실행 시간 최적화
        ```cpp
        // 입력이 많은 경우
        char buf[1 << 20];
        int idx = 0;

        inline char read_char() {
            if (idx == sizeof(buf)) {
                fread(buf, 1, sizeof(buf), stdin);
                idx = 0;
            }
            return buf[idx++];
        }

        // 상수 시간 최적화
        const int dx[] = {-1, 0, 1, 0};
        const int dy[] = {0, 1, 0, -1};
        ```

    3. 유용한 디버깅 테크닉
        ```cpp
        // 벡터 출력 함수
        template<typename T>
        void print_vector(const vector<T>& v) {
            cout << "size: " << v.size() << ", [";
            for (const auto& x : v) cout << x << " ";
            cout << "]\n";
        }

        // 디버그 매크로
        #define DEBUG
        #ifdef DEBUG
            #define debug(x) cerr << #x << ": " << x << endl
        #else
            #define debug(x)
        #endif
        ```

8. 자주 발생하는 실수와 해결책
    1. 정수 오버플로우
        ```cpp
        // 덧셈에서의 오버플로우
        long long sum = 0LL;
        for (int x : v) {
            sum += x;  // int 대신 long long 사용
        }

        // 곱셈에서의 오버플로우
        long long mul = (long long)a * b;  // 명시적 형변환 필요
        ```

    2. STL 컨테이너의 잘못된 사용
        ```cpp
        // 반복자 무효화
        vector<int> v = {1, 2, 3, 4, 5};
        for (auto it = v.begin(); it != v.end(); ) {
            if (*it % 2 == 0) {
                it = v.erase(it);  // 올바른 방법
            } else {
                ++it;
            }
        }

        // map에서 키 존재 여부 체크
        if (m.find(key) != m.end()) {  // 올바른 방법
            // 키가 존재할 때의 처리
        }
        // m[key]  // 잘못된 방법: 키가 없으면 기본값이 삽입됨
        ```

    3. 메모리 누수 방지
        ```cpp
        // RAII 활용
        class ArrayWrapper {
            int* arr;
        public:
            ArrayWrapper(int n) : arr(new int[n]) {}
            ~ArrayWrapper() { delete[] arr; }
            // 복사 생성자와 대입 연산자 구현 필요
        };
        ```

9. 문제 유형별 접근 전략 및 권장 자료구조/알고리즘
    1. 그래프 이론 문제
        - 유형 예시: 최단 거리 문제, 사이클 탐지, 최소 스패닝 트리, 위상 정렬, 강연결 요소, 이분 매칭 등
        - 대표적인 알고리즘 및 자료구조:
            - 최단 거리(단일 시작점, 가중치 양수): 다익스트라(우선순위 큐), 벨만-포드(음수 가중치), SPFA
            - 최소 스패닝 트리: 크루스칼(유니온 파인드), 프림(우선순위 큐)
            - 위상 정렬: 진입 차수 배열 + 큐
            - 강연결 요소(SCC): Tarjan 또는 Kosaraju 알고리즘 (인접 리스트 + 스택)
            - 이분 매칭/네트워크 플로우: 에드몬드-카프, Dinic 알고리즘 (큐, 인접 리스트)
        - 해결 흐름:
            - 문제에서 "최단 거리"가 언급 -> 다익스트라(양수 가중치), BFS(가중치가 동일할 때), 벨만-포드(음수 가중치)
            - MST 요구 -> 그래프 간선 정렬 후 크루스칼 or 인접 리스트로 프림
            - 위상 정렬 요구 (방향 그래프에서 선행 관계) -> 진입 차수 계산 -> 큐를 이용한 위상 정렬

    2. 트리 문제
        - 유형 예시: 트리의 지름, LCA(최소 공통 조상), 서브트리 합, 경로 관련 쿼리
        - 대표 자료구조 및 알고리즘
            - LCA: 희소 테이블 (Sparse Table), 세그먼트 트리나 RMQ를 이용한 LCA
            - 트리의 지름: 두 번의 BFS/DFS
            - 경로 쿼리: Heavy-Light Decomposition, Centroid Decomposition
        - 해결 흐름:
            - LCA 문제가 나옴 -> 전처리: Sparse Table 구성 (O(NlogN)), 쿼리 O(1) 처리
            - 트리 경로 최대/최소 합 요구 -> Heavy-Light Decomposition으로 경로를 O(log N)에 분해하고 세그먼트 트리로 쿼리 처리

    3. 문자열 처리 문제
        - 유형 예시: 접두사/접미사 일치, 부분 문자열 검색, 문자열 정렬 후 사전순 최소,회문 검사, 접미사 배열, KMP
        - 대표 알고리즘
            - 부분 문자열 검색: KMP(접두사-접미사 테이블), Rabin-Karp(해싱)
            - 가장 긴 접두사/접미사: KMP의 pi배열 활용
            - 접미사 배열/접미사 매열 + LCP: O(N log N)문자열 정렬, LCP 계산 -> 사전순 k번째 부분 문자열 문제 등 해결
        - 해결 흐름:
            - 부분 문자열 존재 여부, 출현 횟수 -> KMP로 O(N) 처리
            - 사전순 k번째 부분문자열 요구 -> 접미사 배열 + LCP 이용
            - 문자열 패턴 매칭 대량 -> Rabin-Karp나 KMP로 효율적 처리

    4. 동적 계획법(DP)
        - 유형 예시: 최대/최소 경로 문제, 배낭 문제, LIS, 분할 정복 DP, DP on Trees
        - 대표 기법:
            - 배낭 문제: O(NW) DP (N: 아이템 수, W: 용량), Bitset 최적화
            - LIS(Longest Increasing Subsequence): O(N log N) 알고리즘 (이진 탐색)
            - 구간 DP: 펠린드롬 분할, 행렬 체인 곱셈
            - Tree DP: 서브트리 DP, DFS로 상태 계산

        - 해결 흐름:
            - 최적 부분 구조 확인 -> DP 정의
            - 상태 정의 후 점화식 세우기
            - 1차원/2차원 배열로 DP 테이블 구성
            - 최적화 필요 시 정렬, 이진 탐색, Sparse Table, 세그먼트 트리, Bitset 등 고려

    5. 정렬/이진 탐색 문제
        - 유형 예시: 특정 조건을 만족하는 최소/최대 값 찾기, 파라메트릭 서치(Parametric Search)
        - 대표 기법:
            - 파라메트릭 서치: 이분 탐색 + 결정 함수(check)
            - 정렬 후 투 포인터(Two Pointers) 사용
        
        - 해결 흐름:
            - "어떤 값을 구할 수 있나?" -> 파라메트릭 서치 고려 (값을 mid로 두고 check 함수)
            - "특정 조건 만족하는 최소 인덱스/최소 값 찾기" -> lower_bound / upper_bound 활용

    6. 그리디 알고리즘
        - 유형 예시: 최소 동전 수, 회의실 배정, 인터벌 스케줄링, 작업 선택 문제
        - 대표 기법:
            - 정렬 후, 현재까지 선택한 것에 최선의 선택(예: 회의실 배정: 끝나는 시간 기준 정렬 후 순차 배정)
        - 해결 흐름:
            - "정렬 후 한 번 스캔으로 결정 가능?" -> 그리디 의심
            - "국소 최적 해 선택으로 전체 최적 가능?" -> 그리디 적용

    7. 수학적 문제 (수론, 조합론)
        - 유형 예시: 최대공약수, 최소공배수, 소인수분해, 페르마 소정리, 모듈러 연산
        - 대표 기법:
            - GCD, LCM: 유클리드 알고리즘
            - 소수 판정: 에라토스테네스의 체
            - 모듈러 연산: (a + b) % M, (a * b) % M
            - 페르마 소정리로 모듈러 역원 구하기(LCM 계산, 이항계수 계산)
        - 해결 흐름:
            - 큰 수 소인수분해 -> 에라토스테네스 + 투 포인터
            - nCr % M 구하기 -> 페르마 소정리, 팩토리얼 전처리, 모듈러 역원 계산

    8. 투 포인터 / 슬라이딩 윈도우
        - 유형 예시: 연속 구간 합, 길이/조건에 맞는 부분 수열/문자열
        - 대표 기법:
            - 투 포인터로 O(N)에 부분합/조건 검사
            - 정렬된 배열에서 두 포인터로 합 특정 값 찾기

        - 해결 흐름:
            - "연속 구간" + "합 또는 조건" -> 투 포인터
            - 조건 만족 시 오른쪽 포인터 이동, 불만족 시 왼쪽 포인터 이동

    9. 힙 / 우선순위 큐 활용 문제
        - 유형 예시: 실시간으로 최대/최소 추출, k번째 최소 원소, 다익스트라, 트림 MST
        - 해결 흐름:
            - 최대/최소를 자주 요구 -> priority_queue 사용
            - k번째 원소 찾기 -> partial_sort 또는 priotiry_queue로 O(n log k)관리

    10. 세그먼트 트리 / 펜윅 트리 (Fenwick Tree)
        - 유형 예시: 구간 합/최대/최소 쿼리, 업데이트 + 쿼리 빈번
        - 대표 자료구조:
            - 세그먼트 트리: O(log n) 업데이트/쿼리
            - 펜윅 트리(BIT): O(log n) 업데이트/쿼리, 구현 간단

        - 해결 흐름:
            - 구간 합/최대/최소를 빈번히 요구 -> 세그먼트 트리 / 펜윅 트리
            - offline으로 정렬 후 이진 탐색과 세그먼트 트리 조합 가능