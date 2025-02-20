아래는 C++의 객체 지향 프로그래밍, STL, 스마트 포인터, 예외 처리 등 여러 고급 기능을 활용하여 풀어야 하는 복잡한 문제입니다.

---

### 문제: 대학 수강 등록 및 스케줄링 시스템

#### 문제 설명
대학의 수강 등록 및 강의 스케줄링 시스템을 C++로 구현하세요. 이 시스템은 학생(Student), 강의(Course), 그리고 강의 시간(TimeSlot) 관리 기능을 포함합니다.  
시스템은 다음의 기능들을 수행해야 합니다.

1. **클래스 설계**
   - **Student 클래스**
     - 멤버 변수:  
       - `id` (int)
       - `name` (std::string)
       - `major` (std::string)
       - `gpa` (float)
       - 등록된 강의에 대한 리스트: `std::vector<std::shared_ptr<Course>>`
   - **Course 클래스**
     - 멤버 변수:  
       - `code` (std::string)
       - `title` (std::string)
       - `maxCapacity` (int)
       - 등록된 학생에 대한 리스트: `std::vector<std::shared_ptr<Student>>`
       - 강의 시간(들): `std::vector<TimeSlot>`  
         (TimeSlot은 별도의 구조체 또는 클래스로 정의)
   - **TimeSlot 구조체 또는 클래스**
     - 멤버 변수:
       - `day` (std::string; 예: "Mon", "Tue", …)
       - `start` (int; 자정 이후 분 단위, 예: "09:00" → 540)
       - `end` (int; 예: "10:30" → 630)
     - 두 시간대가 겹치는지 판단하는 기능을 구현

2. **수강 등록 로직**
   - 학생은 한 강의에 중복 등록할 수 없으며, 강의는 정원이 꽉 찰 경우 등록이 거부되어야 합니다.
   - **시간대 충돌 검사:**  
     학생이 이미 등록한 강의 중 하나라도 새 강의의 시간대와 겹친다면, 해당 등록 요청은 거부되어야 합니다.
   - 등록 요청은 입력 순서대로 처리하며, 각 요청에 대해 성공 또는 실패 메시지를 출력합니다.
   - 실패 사유는 "강의 정원 초과" 또는 "시간대 충돌" 등으로 구체적으로 표시

3. **입력 형식**
   - **학생 정보:**
     - 첫 줄에 학생 수 `N`  
     - 다음 `N`개의 줄:  
       `id name major gpa`
   - **강의 정보:**
     - 다음 줄에 강의 수 `M`  
     - 다음 `M`개의 줄:  
       `code title maxCapacity`  
       (강의명에 공백이 포함될 수 있으므로, 적절한 입력 파싱이 필요)
   - **강의 스케줄 정보:**
     - 다음 줄에 스케줄 항목 수 `S`  
     - 다음 `S`개의 줄:  
       `courseCode day startTime endTime`  
       예: `CS101 Mon 09:00 10:30`  
       → 입력받은 시간을 분 단위로 변환하여 저장
   - **수강 등록 요청:**
     - 다음 줄에 등록 요청 수 `R`  
     - 다음 `R`개의 줄:  
       `studentId courseCode`

4. **출력 형식**
   - 각 등록 요청에 대해 다음 메시지를 출력합니다.
     - 등록 성공 시:  
       `"Registration successful: studentId courseCode"`
     - 등록 실패 시:  
       `"Registration failed: studentId courseCode - [사유]"`
   - 모든 요청 처리 후, 각 강의에 대한 요약을 출력합니다.
     - 강의 코드와 강의명을 출력한 후,  
       등록된 학생 목록(학생 이름을 GPA 내림차순으로 정렬)을 출력합니다.  
       등록 학생이 없으면 `"Registered Students: None"`을 출력

5. **추가 요구사항**
   - **동적 메모리 관리:**  
     - STL 컨테이너와 스마트 포인터(`std::shared_ptr` 또는 `std::unique_ptr`)를 사용하여 메모리 관리를 수행합니다.
   - **예외 처리:**  
     - 잘못된 입력 형식 또는 등록 과정 중 발생 가능한 예외 상황에 대해 적절한 예외 처리를 구현합니다.
   - **모듈화:**  
     - 입력 파싱, 등록 처리, 시간대 충돌 검사, 정렬 및 출력 기능을 각각 별도의 함수나 클래스 메서드로 분리합니다.
   - **시간대 비교:**  
     - 시간을 분 단위로 변환한 후, 두 시간대가 겹치는지 확인하는 함수를 구현합니다.
   - **등록 조건 검사:**  
     - 한 학생이 이미 같은 강의에 등록되어 있는지 여부도 확인합니다.

---

#### 예시 입력

```
3
1001 Alice CS 3.8
1002 Bob EE 3.5
1003 Carol ME 3.9
2
CS101 "Intro to CS" 2
EE202 "Circuits" 2
3
CS101 Mon 09:00 10:30
CS101 Wed 09:00 10:30
EE202 Mon 09:30 11:00
4
1001 CS101
1002 CS101
1003 CS101
1001 EE202
```

#### 예시 출력

```
Registration successful: 1001 CS101
Registration successful: 1002 CS101
Registration failed: 1003 CS101 - Course capacity reached
Registration failed: 1001 EE202 - Time slot conflict

Course Summary:
CS101 Intro to CS
Registered Students: Alice, Bob
EE202 Circuits
Registered Students: None
```

---

#### 구현 힌트
- **시간 파싱:**  
  "09:00"과 같은 문자열을 분 단위 정수(예: 9×60 = 540)로 변환하는 함수를 구현하면 시간대 비교가 쉬워집니다.
- **STL 활용:**  
  - 학생과 강의 정보를 저장할 때 `std::vector`를 사용하고, 등록된 학생 리스트는 정렬 시 `std::sort`와 사용자 정의 비교 함수를 활용하세요.
- **스마트 포인터:**  
  - 객체 소유권을 명확히 하기 위해 `std::shared_ptr<Student>`와 `std::shared_ptr<Course>`를 사용하여 메모리 누수를 방지합니다.
- **시간대 충돌:**  
  - 두 시간대 A와 B가 충돌하는 조건은:  
    `A.start < B.end && B.start < A.end`  
    형태로 구현할 수 있습니다.
- **예외 처리:**  
  - 입력 파싱 및 등록 과정에서 예상치 못한 오류가 발생할 경우, `try-catch` 블록을 활용하여 적절히 처리합니다.

---

이 문제는 객체 지향 설계, STL의 강력한 기능, 스마트 포인터를 통한 안전한 메모리 관리, 그리고 복잡한 조건 검증 및 시간대 비교 등의 다양한 C++ 개념을 종합적으로 연습할 수 있도록 구성되었습니다. 문제의 요구사항을 충실히 반영하면서 모듈화된 코드 작성과 예외 처리, 그리고 효율적인 알고리즘 구현에 중점을 두면 좋은 연습이 될 것입니다.

# 코멘트

전체적으로 코드를 꼼꼼하게 설계하고 구현하신 점이 인상적입니다. C++의 객체 지향 기능, STL, 스마트 포인터, 예외 처리 등 고급 기능들을 잘 활용하여 복잡한 문제를 효과적으로 해결하신 것을 볼 수 있습니다. 아래 몇 가지 긍정적인 점과 함께 개선하면 좋을 사항들을 정리해보았습니다.

---

## 긍정적인 점

- **객체 지향 설계와 모듈화**  
  - Student, Course, TimeSlot 클래스로 역할을 명확하게 분리하고, 각 클래스별로 필요한 기능(예: 수강 등록, 시간 충돌 검사, 정보 출력 등)을 메서드로 구현하여 코드의 응집도를 높였습니다.
  - 예외 클래스를 별도로 정의하여 입력이나 등록 과정에서 발생할 수 있는 오류 상황을 구체적으로 처리한 점도 좋습니다.

- **스마트 포인터와 STL 활용**  
  - `std::shared_ptr`를 사용해 객체의 소유권을 관리하고, `std::vector`를 통해 동적 배열을 손쉽게 관리한 점이 현대 C++ 스타일에 잘 부합합니다.
  - `std::find_if`와 `std::sort` 등 STL 알고리즘을 적극 활용하여 코드를 간결하게 유지하였습니다.

- **예외 처리와 입력 검증**  
  - 각 클래스의 setter나 메서드 내에서 잘못된 입력이 들어올 경우 예외를 던짐으로써, 문제 발생 시 구체적인 오류 메시지를 제공하는 점이 인상적입니다.
  - 시간 형식과 범위, 강의의 최대 수강 인원 등 다양한 제한 사항을 효과적으로 검사하고 있습니다.

- **시간대 충돌 검사 구현**  
  - TimeSlot 클래스에서 두 시간대가 충돌하는지를 비교하는 로직(예: `if (_day != other._day) return false; return _start < other._end && other._start < _end;`)은 명확하고 실용적입니다.

---

## 개선 및 고려할 사항

1. **GPA 유효성 검사 조건**  
   - Student 생성자에서 GPA를 검사할 때 현재 조건은  
     ```cpp
     if (gpa < 0.0f && gpa > 100.0f)
     ```
     로 되어 있는데, 이 조건은 절대 참이 될 수 없습니다.  
     **개선:**  
     ```cpp
     if (gpa < 0.0f || gpa > 100.0f)
     ```
     로 변경하여 GPA가 0 미만이거나 100 초과인 경우 예외를 발생시키도록 수정하세요.

2. **시간 문자열 포맷팅 개선**  
   - TimeSlot의 `getTimeString()`에서 현재 `std::to_string`을 사용한 후 `substr(0, 2)`로 처리하는 방식은, 예를 들어 시간이 9시일 경우 "9"만 출력될 수 있습니다.  
     **대안:**  
     `<iomanip>`의 `std::setw`와 `std::setfill`을 활용하여 두 자리 형식(예: "09")으로 출력하도록 개선하면 보다 정확한 형식의 시간 문자열을 얻을 수 있습니다.
     ```cpp
     std::ostringstream oss;
     oss << _day << " " 
         << std::setw(2) << std::setfill('0') << (_start / 60) << ":" 
         << std::setw(2) << std::setfill('0') << (_start % 60) << "-" 
         << std::setw(2) << std::setfill('0') << (_end / 60) << ":" 
         << std::setw(2) << std::setfill('0') << (_end % 60);
     return oss.str();
     ```
     
3. **전방 선언과 헤더 포함**  
   - 코드 상에서 STL 알고리즘(예: `std::find_if`, `std::sort`)을 사용하고 있는데, 이를 위해 `<algorithm>` 헤더를 포함하는 것이 좋습니다.
   
4. **예외 처리 범위와 세밀함**  
   - 수강 등록이나 시간대 추가 시 예외를 잡아내고 구체적인 메시지를 출력하는 부분은 매우 좋습니다. 다만, 필요에 따라 예외 처리 블록을 세분화하여 어느 부분에서 오류가 발생했는지 더 명확하게 구분할 수도 있습니다.
   
5. **코드 일관성과 주석**  
   - 전체적으로 함수와 메서드에 대해 충분한 주석이 달려 있어 이해하기 쉽습니다. 다만, 향후 유지보수를 위해 각 복잡한 로직(예: 시간 충돌 검사, 등록 시 시간대 비교)의 세부 동작을 간단히 주석으로 보완하면 좋겠습니다.

---

## 종합 의견

문제를 해결하는 데 상당한 시간과 노력을 기울이신 만큼, 코드도 상당히 정교하게 작성되었음을 알 수 있습니다. C++의 최신 기능들을 활용한 설계, 예외 처리, STL 알고리즘 적용 등이 매우 인상적이며, 실제 시스템 개발에서도 활용할 수 있을 만한 수준입니다. 위에서 언급한 몇 가지 개선 사항을 반영하면, 더욱 견고하고 가독성이 높은 코드가 될 것으로 보입니다.

정말 멋진 작업을 하셨고, 앞으로도 이러한 고급 기술들을 계속 발전시켜 나가시길 바랍니다!