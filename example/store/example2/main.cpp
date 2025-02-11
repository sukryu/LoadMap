#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <memory>

class Course; // 전방 선언

class StudentValidationError : public std::runtime_error {
public:
    StudentValidationError(const std::string& message) 
        : std::runtime_error(message) {}
};

class Student : public std::enable_shared_from_this<Student> {
private:
    int _id;
    std::string _name;
    std::string _major;
    float _gpa;
    std::vector<std::shared_ptr<Course>> _lecture_list;

public:
    Student(int id, std::string name, std::string major, float gpa)
        : _id(id), _name(name), _major(major), _gpa(gpa) {
            if (gpa < 0.0f || gpa > 100.0f) {
                throw StudentValidationError("invalid input");
            }
        }

    // 기본 getter
    int getId() const { return _id; }
    std::string getName() const { return _name; }
    std::string getMajor() const { return _major; }
    float getGpa() const { return _gpa; }
    const std::vector<std::shared_ptr<Course>>& getLectureList() const { return _lecture_list; }

    // 수강 신청 관련 메서드
    bool addCourse(const std::shared_ptr<Course>& course) {
        if (std::find(_lecture_list.begin(), _lecture_list.end(), course) == _lecture_list.end()) {
            _lecture_list.push_back(course);
            return true;
        }
        return false;
    }

    bool removeCourse(const std::shared_ptr<Course>& course) {
        auto it = std::find(_lecture_list.begin(), _lecture_list.end(), course);
        if (it != _lecture_list.end()) {
            _lecture_list.erase(it);
            return true;
        }
        return false;
    }
};

class CourseValidationError : public std::runtime_error {
public:
    CourseValidationError(const std::string& message) 
        : std::runtime_error(message) {}
};

class Course : public std::enable_shared_from_this<Course> {
private:
    std::string _code;
    std::string _title;
    int _maxCapacity;
    std::vector<std::shared_ptr<Student>> _student_list;
    std::vector<TimeSlot> _time_slots;

public:
    Course(std::string code, std::string title, int maxCapacity) {
        setCode(code);
        setTitle(title);
        setMaxCapacity(maxCapacity);
    };

    // 기본 getter/setter
    std::string getCode() const { return _code; }
    std::string getTitle() const { return _title; }
    int getMaxCapacity() const { return _maxCapacity; }
    const std::vector<std::shared_ptr<Student>>& getStudentList() const { return _student_list; };
    const std::vector<TimeSlot>& getTimeSlots() const { return _time_slots; };

    void setCode(const std::string& code) {
        if (code.empty()) {
            throw CourseValidationError("Course code cannot be empty");
        }
        this->_code = code;
    }

    void setTitle(const std::string& title) {
        if (title.empty()) {
            throw CourseValidationError("Course title cannot be empty");
        }
        this->_title = title;
    }

    void setMaxCapacity(int maxCapacity) {
        if (maxCapacity <= 0) {
            throw CourseValidationError("Maximum capacity must be greater than 0");
        }
        if (_student_list.size() > maxCapacity) {
            throw CourseValidationError("New capacity cannot be less than current number of students");
        }
        this->_maxCapacity = maxCapacity;
    }

    // 수강 신청 관련 함수들
    bool addStudent(std::shared_ptr<Student>& student) {
        try {
            // 1. 수강생이 가득 찼는지 확인
            if (isFull()) {
                throw CourseValidationError("The maximum number of people allowed has been reached");
            }

            // 2. 이미 해당 강의에 등록이 되어 있는지 확인
            if (hasStudent(student)) {
                throw CourseValidationError("You are already registered for this course");
            }

            // 3. 시간 충돌 확인
            for (const auto& timeSlot : _time_slots) {
                for (const auto& enrolledCourse : student->getLectureList()) {
                    for (const auto& enrolledTimeSlot : enrolledCourse->getTimeSlots()) {
                        if (timeSlot.isConflict(enrolledTimeSlot)) {
                            throw CourseValidationError("Time slot conflict with existing course");
                        }
                    }
                }
            }

            // 4. 모든 검증을 통과했으므로 학생을 등록
            _student_list.push_back(student);
            student->addCourse(shared_from_this());  // 학생 객체에도 이 강의를 추가
            return true;

        } catch(const std::invalid_argument&) {
            throw CourseValidationError("Invalid Student Arguments");
        }
    };
    bool removeStudent(std::shared_ptr<Student>& student) {
        try {
            // 1. 해당 학생이 강의에 등록되어 있는지 확인
            if (!hasStudent(student)) {
                throw CourseValidationError("You are not registered for this course");
            }

            // 2. 학생을 강의에서 삭제
            auto iter = std::find_if(_student_list.begin(), _student_list.end(),
                [&student](const std::shared_ptr<Student>& enrolled) {
                    return enrolled->getId() == student->getId();
                });

            if (iter != _student_list.end()) {
                // 학생의 수강 목록에서도 이 강의를 제거
                student->removeCourse(shared_from_this());
                // 강의의 학생 목록에서 학생을 제거
                _student_list.erase(iter);
                return true;
            }

            return false;

        } catch (const std::invalid_argument&) {
            throw CourseValidationError("Invalid Student Arguments");
        }
    };
    bool isFull() const {
        return _student_list.size() >= _maxCapacity;
    };
    bool hasStudent(const std::shared_ptr<Student>& student) const {
        return std::find_if(_student_list.begin(), _student_list.end(),
        [&student](const std::shared_ptr<Student>& enrolled) {
            return enrolled->getId() == student->getId();
        }) != _student_list.end();
    };

    // 시간표 관련 함수들
    void addTimeSlot(const TimeSlot& slot) {
        for (const auto& existing_slot : _time_slots) {
            if (existing_slot.isConflict(slot)) {
                throw CourseValidationError("Time slot conflicts with existing schedule");
            }
        }
        _time_slots.push_back(slot);
    }
    bool hasTimeConflict(const TimeSlot& slot) const {
        for (const auto& existing_slot : _time_slots) {
            if (existing_slot.isConflict(slot)) {
                return true;
            }
        }
        return false;
    }

    // 학생 목록 정렬 및 출력 관련 함수
    std::vector<std::shared_ptr<Student>> getStudentsSortedByGPA() const {
        std::vector<std::shared_ptr<Student>> sorted_list = _student_list;
        std::sort(sorted_list.begin(), sorted_list.end(), 
            [](const std::shared_ptr<Student>& a, const std::shared_ptr<Student>& b) {
                return a->getGpa() > b->getGpa();  // 내림차순 정렬
            });
        return sorted_list;
    }
    void printCourseInfo() const {
        // 강의 기본 정보 출력
        std::cout << _code << " " << _title << std::endl;
        
        // 등록된 학생이 없는 경우
        if (_student_list.empty()) {
            std::cout << "Registered Students: None" << std::endl;
            return;
        }

        // 등록된 학생이 있는 경우, GPA 기준 내림차순으로 정렬하여 출력
        std::cout << "Registered Students: ";
        auto sorted_students = getStudentsSortedByGPA();
        
        for (size_t i = 0; i < sorted_students.size(); ++i) {
            std::cout << sorted_students[i]->getName();
            if (i < sorted_students.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
};

class TimeValidationError : public std::runtime_error {
public:
    TimeValidationError(const std::string& message) 
        : std::runtime_error(message) {}
};

class TimeSlot {
private:
    std::string _day;
    int _start;
    int _end;

    static bool isValidDay(const std::string& day) {
        static const std::vector<std::string> validDays = 
            {"Mon", "Tue", "Wed", "Thu", "Fri"};
        return std::find(validDays.begin(), validDays.end(), day) != validDays.end();
    }

    static bool isValidTimeFormat(const std::string& time) {
        if (time.length() != 5) return false;
        if (time[2] != ':') return false;
        return std::all_of(time.begin(), time.begin() + 2, ::isdigit) &&
               std::all_of(time.begin() + 3, time.end(), ::isdigit);
    }

public:
    TimeSlot(std::string day, std::string start, std::string end) {
        if (!isValidDay(day)) {
            throw TimeValidationError("Invalid day format. Use Mon, Tue, Wed, Thu, or Fri");
        }

        if (!isValidTimeFormat(start) || !isValidTimeFormat(end)) {
            throw TimeValidationError("Invalid time format.");
        }
        
        _day = day;
        _start = convertTimeToMinutes(start);
        _end = convertTimeToMinutes(end);
    }

    bool isConflict(const TimeSlot& other) const {
        if (_day != other._day) return false;
        return _start < other._end && other._start < _end;
    }

    static int convertTimeToMinutes(const std::string& time) {
        try {
            if (!isValidTimeFormat(time)) {
                throw TimeValidationError("Invalid time format. Use HH:MM");
            }

            std::string hours = time.substr(0, 2);
            std::string minutes = time.substr(3, 2);
            
            int hour = std::stoi(hours);
            int minute = std::stoi(minutes);
            
            if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
                throw TimeValidationError("Time values out of range");
            }
            
            return (hour * 60) + minute;
        } catch (const std::invalid_argument&) {
            throw TimeValidationError("Invalid time format");
        } catch (const std::out_of_range&) {
            throw TimeValidationError("Time value out of range");
        }
    }

    std::string getDay() const { return _day; }
    int getStartTime() const { return _start; }
    int getEndTime() const { return _end; }

    // 시간을 문자열로 변환하는 유틸리티 메서드
    std::string TimeSlot::getTimeString() const {
        std::ostringstream oss;
        oss << _day << " " 
            << std::setw(2) << std::setfill('0') << (_start / 60) << ":" 
            << std::setw(2) << std::setfill('0') << (_start % 60) << "-" 
            << std::setw(2) << std::setfill('0') << (_end / 60) << ":" 
            << std::setw(2) << std::setfill('0') << (_end % 60);
        return oss.str();
    }
};

void input_student(std::vector<std::shared_ptr<Student>>& st_list, int len) {
    for (int i = 0; i < len; i++) {
        int id = 0;
        std::string name, major;
        float gpa = 0.0f;

        std::cin >> id >> name >> major >> gpa;
        st_list[i] = std::make_shared<Student>(id, name, major, gpa);
    }
}

void input_course(std::vector<std::shared_ptr<Course>>& course_list, int len) {
    std::string line;
    std::getline(std::cin, line); // 버퍼 비우기

    for (int i = 0; i < len; i++) {
        std::getline(std::cin, line);
        std::stringstream ss(line);
        
        std::string code, title;
        int maxCapacity;
        
        ss >> code;
        
        char quote;
        ss >> quote;  // 첫 따옴표 읽기
        std::getline(ss, title, '"');  // 따옴표까지 읽기
        ss >> maxCapacity;
        
        course_list[i] = std::make_shared<Course>(code, title, maxCapacity);
    }
}

int main() {
    int n = 0, m = 0, s = 0, r = 0;
    
    // 1. Student 입력받기
    std::cin >> n;
    std::vector<std::shared_ptr<Student>> st_list(n);
    input_student(st_list, n);

    // 2. Course 입력받기
    std::cin >> m;
    std::vector<std::shared_ptr<Course>> cs_list(m);
    input_course(cs_list, m);

    // 3. 강의 스케줄 정보 입력받기
    std::cin >> s;
    for (int i = 0; i < s; i++) {
        std::string course_code, day, start, end;
        std::cin >> course_code >> day >> start >> end;

        try {
            auto cs_iter = std::find_if(cs_list.begin(), cs_list.end(),
                [&course_code](const std::shared_ptr<Course>& course) {
                    return course->getCode() == course_code;
                });

            if (cs_iter != cs_list.end()) {
                TimeSlot newSlot(day, start, end);
                (*cs_iter)->addTimeSlot(newSlot);
            } else {
                throw CourseValidationError("Course not found");
            }
        } catch (const TimeValidationError& e) {
            std::cout << "Failed to add time slot: " << course_code << " - " << e.what() << std::endl;
        } catch (const CourseValidationError& e) {
            std::cout << "Failed to add time slot: " << course_code << " - " << e.what() << std::endl;
        }
    }

    // 4. 수강 신청 등록
    std::cin >> r;
    for (int i = 0; i < r; i++) {
        int student_id = 0;
        std::string course_code;
        std::cin >> student_id >> course_code;
        try {
            // 학생 찾기
            auto st_iter = std::find_if(st_list.begin(), st_list.end(),
                [student_id](const std::shared_ptr<Student>& student) {
                    return student->getId() == student_id;
                });

            // 강의 찾기
            auto cs_iter = std::find_if(cs_list.begin(), cs_list.end(),
                [&course_code](const std::shared_ptr<Course>& course) {
                    return course->getCode() == course_code;
                });

            // 학생과 강의가 모두 존재하는지 확인
            if (st_iter != st_list.end() && cs_iter != cs_list.end()) {
                if ((*cs_iter)->addStudent(*st_iter)) {
                    std::cout << "Registration successful: " << student_id << " " << course_code << std::endl;
                }
            } else {
                std::cout << "Registration failed: " << student_id << " " << course_code 
                        << " - Student or course not found" << std::endl;
            }
        } catch (const CourseValidationError& e) {
            std::cout << "Registration failed: " << student_id << " " << course_code 
                    << " - " << e.what() << std::endl;
        }
    }

    // 5. print
    std::cout << "Course Summary: " << std::endl;
    for (int i = 0; i < cs_list.size(); i++) {
        cs_list[i]->printCourseInfo();
    }

    return 0;
}