#include <iostream>
#include <string>
#include <cassert>
#include "singly_linked_list.h"

// 테스트용 클래스
class TestClass {
public:
    TestClass(int v = 0) : value(v) { 
        std::cout << "Constructor: " << value << std::endl; 
    }
    TestClass(const TestClass& other) : value(other.value) { 
        std::cout << "Copy Constructor: " << value << std::endl; 
    }
    TestClass(TestClass&& other) noexcept : value(other.value) {
        other.value = 0;
        std::cout << "Move Constructor: " << value << std::endl;
    }
    ~TestClass() { 
        std::cout << "Destructor: " << value << std::endl; 
    }
    
    int getValue() const { return value; }
    
    bool operator==(const TestClass& other) const {
        return value == other.value;
    }
private:
    int value;
};

void test_basic_operations() {
    std::cout << "\n=== Testing Basic Operations ===\n";
    
    mydsa::SinglyLinkedList<int> list;
    
    // 비어있는 상태 테스트
    assert(list.empty());
    assert(list.size() == 0);
    
    // push_back 테스트
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    assert(list.size() == 3);
    assert(list.front() == 1);
    assert(list.back() == 3);
    
    // push_front 테스트
    list.push_front(0);
    assert(list.size() == 4);
    assert(list.front() == 0);
    
    // pop_front 테스트
    list.pop_front();
    assert(list.front() == 1);
    assert(list.size() == 3);
    
    // pop_back 테스트
    list.pop_back();
    assert(list.back() == 2);
    assert(list.size() == 2);
    
    std::cout << "Basic operations test passed!\n";
}

void test_iterators() {
    std::cout << "\n=== Testing Iterators ===\n";
    
    mydsa::SinglyLinkedList<int> list;
    for (int i = 1; i <= 5; ++i) {
        list.push_back(i);
    }
    
    // 정방향 반복자 테스트
    std::cout << "Forward iteration: ";
    for (const auto& value : list) {
        std::cout << value << " ";
    }
    std::cout << "\n";
    
    // iterator를 사용한 값 수정
    for (auto& value : list) {
        value *= 2;
    }
    
    // const_iterator 테스트
    const mydsa::SinglyLinkedList<int>& const_list = list;
    std::cout << "After doubling (using const_iterator): ";
    for (auto it = const_list.begin(); it != const_list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    std::cout << "Iterator tests passed!\n";
}

void test_memory_management() {
    std::cout << "\n=== Testing Memory Management ===\n";
    
    mydsa::SinglyLinkedList<TestClass> list;
    
    // push_back 테스트
    std::cout << "Testing push_back:\n";
    list.push_back(TestClass(1));
    list.push_back(TestClass(2));
    list.push_back(TestClass(3));
    
    // 복사 생성자 테스트
    std::cout << "\nTesting copy constructor:\n";
    auto list2 = list;
    
    // 이동 생성자 테스트
    std::cout << "\nTesting move constructor:\n";
    auto list3 = std::move(list2);
    
    // clear 테스트
    std::cout << "\nTesting clear:\n";
    list3.clear();
    assert(list3.empty());
    
    std::cout << "Memory management tests passed!\n";
}

void test_insert_erase() {
    std::cout << "\n=== Testing Insert/Erase Operations ===\n";
    
    mydsa::SinglyLinkedList<int> list;
    
    // 삽입 테스트
    list.insert(0, 1);  // 맨 앞 삽입
    list.insert(1, 3);  // 맨 뒤 삽입
    list.insert(1, 2);  // 중간 삽입
    
    // 결과 확인
    std::cout << "After insertions: ";
    for (const auto& value : list) {
        std::cout << value << " ";
    }
    std::cout << "\n";
    assert(list.size() == 3);
    
    // 삭제 테스트
    list.erase(1);  // 중간 삭제
    assert(list.size() == 2);
    assert(list.front() == 1);
    assert(list.back() == 3);
    
    std::cout << "Insert/Erase tests passed!\n";
}

void test_exception_safety() {
    std::cout << "\n=== Testing Exception Safety ===\n";
    
    mydsa::SinglyLinkedList<TestClass> list;
    
    // 범위 검사 테스트
    try {
        list.at(0);  // empty list
        assert(false);  // shouldn't reach here
    } catch (const std::out_of_range&) {
        std::cout << "Successfully caught out_of_range exception for at()\n";
    }
    
    try {
        list.insert(1, TestClass(1));  // invalid position
        assert(false);  // shouldn't reach here
    } catch (const std::out_of_range&) {
        std::cout << "Successfully caught out_of_range exception for insert()\n";
    }
    
    std::cout << "Exception safety tests passed!\n";
}

int main() {
    try {
        test_basic_operations();
        test_iterators();
        test_memory_management();
        test_insert_erase();
        test_exception_safety();
        
        std::cout << "\nAll tests passed successfully!\n";
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}