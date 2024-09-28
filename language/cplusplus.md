# C++ 언어 #

## C++의 기초 ##

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