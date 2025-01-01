#ifndef MYDSA_SINGLY_LINKED_LIST_H
#define MYDSA_SINGLY_LINKED_LIST_H

#include "ILinkedList.h"

namespace mydsa {

    /**
     * @brief 단일 연결 리스트(Singly Linked List) 구현
     * 
     * ILinkedList<T>를 상속받아,
     * 모든 순수 가상 함수를 override하여 실제 로직을 제공.
     */
    template <typename T>
    class SinglyLinkedList : public ILinkedList<T> {
    private:
        // 내부 노드 구조
        struct Node {
            T data;
            Node* next;
            explicit Node(const T& val) : data(val), next(nullptr) {}
            explicit Node(T&& val) : data(std::move(val)), next(nullptr) {}
        };

        Node* head;        // 첫 번째 노드
        Node* tail;        // 마지막 노드 (push_back 시 O(1) 목적으로)
        std::size_t mSize; // 원소 개수

    public:

        // 전방 반복자 정의
        class iterator {
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = T*;
            using reference = T&;

            // 생성자
            iterator() : current(nullptr) {}
            explicit iterator(Node* ptr) : current(ptr) {}

            // 접근 연산자
            reference operator*() const {
                if (!current) {
                    throw std::runtime_error("Iterator: dereferencing null pointer.");
                }
                return current->data;
            }

            pointer operator->() const {
                if (!current) {
                    throw std::runtime_error("Iterator: accessing null pointer.");
                }
                return &(current->data);
            }

            // 증가 연산자
            iterator& operator++() { //전위 중가
                if (current) {
                    current = current->next;
                }
                return *this;
            }
            iterator operator++(int) { // 후위 증가
                iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            // 비교 연산자
            bool operator==(const iterator& other) const {
                return current == other.current;
            }
            bool operator!=(const iterator& other) const {
                return !(*this == other);
            }

        private:
            Node* current;
            friend class SinglyLinkedList;
        };

        // const_iterator 정의 (상수 반복자)
        class const_iterator {
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = const T*;
            using reference = const T&;

            const_iterator() : current(nullptr) {}
            explicit const_iterator(const Node* ptr) : current(ptr) {}
            const_iterator(const iterator& it) : current(it.current) {}

            reference operator*() const {
                if (!current) {
                    throw std::runtime_error("Const_Iterator: dereferencing null pointer");
                }
                return current->data;
            }
            pointer operator->() const {
                if (!current) {
                    throw std::runtime_error("Const_Iterator: accessing null pointer");
                }
                return &(current->data);
            }

            const_iterator& operator++() {
                if (current) {
                    current = current->next;
                }
                return *this;
            }
            const_iterator operator++(int) {
                const_iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            bool operator==(const const_iterator& other) const {
                return current == other.current;
            }
            bool operator!=(const const_iterator& other) const {
                return !(*this == other);
            }

        private:
            const Node* current;
            friend class SinglyLinkedList;
        };

        // iterator 관련 메서드들
        iterator begin() noexcept { return iterator(head); }
        iterator end() noexcept { return iterator(nullptr); }
        const_iterator begin() const noexcept { return const_iterator(head); }
        const_iterator end() const noexcept { return const_iterator(nullptr); }
        const_iterator cbegin() const noexcept { return const_iterator(head); }
        const_iterator cend() const noexcept { return const_iterator(nullptr); }

        // 기본 생성자
        SinglyLinkedList() 
            : head(nullptr), tail(nullptr), mSize(0) {}

        // 소멸자
        ~SinglyLinkedList() override {
            clear(); // 모든 노드 삭제
        }

        // 복사 생성자
        SinglyLinkedList(const SinglyLinkedList& other)
            : head(nullptr), tail(nullptr), mSize(0) 
        {
            // 다른 리스트의 노드를 순회하며 push_back
            Node* cur = other.head;
            while (cur) {
                push_back(cur->data);
                cur = cur->next;
            }
        }

        // 복사 대입 연산자
        SinglyLinkedList& operator=(const SinglyLinkedList& other) {
            if (this == &other) return *this; // 자기 자신
            clear();
            Node* cur = other.head;
            while (cur) {
                push_back(cur->data);
                cur = cur->next;
            }
            return *this;
        }

        // 이동 생성자
        SinglyLinkedList(SinglyLinkedList&& other) noexcept
            : head(other.head), tail(other.tail), mSize(other.mSize)
        {
            other.head = nullptr;
            other.tail = nullptr;
            other.mSize = 0;
        }

        // 이동 대입 연산자
        SinglyLinkedList& operator=(SinglyLinkedList&& other) noexcept {
            if (this == &other) return *this;
            clear();
            head = other.head;
            tail = other.tail;
            mSize = other.mSize;
            other.head = nullptr;
            other.tail = nullptr;
            other.mSize = 0;
            return *this;
        }

        /* ---------------------------------------------------------
         * 구현 (ILinkedList 인터페이스)
         * --------------------------------------------------------- */

        // 용량/상태 관련
        std::size_t size() const noexcept override {
            return mSize;
        }

        bool empty() const noexcept override {
            return (mSize == 0);
        }

        void clear() override {
            while (!empty()) {
                pop_front();
            }
        }

        // 접근 (front/back)
        T& front() override {
            if (empty()) {
                throw std::out_of_range("SinglyLinkedList::front() - empty list");
            }
            return head->data;
        }
        const T& front() const override {
            if (empty()) {
                throw std::out_of_range("SinglyLinkedList::front() const - empty list");
            }
            return head->data;
        }

        T& back() override {
            if (empty()) {
                throw std::out_of_range("SinglyLinkedList::back() - empty list");
            }
            return tail->data;
        }
        const T& back() const override {
            if (empty()) {
                throw std::out_of_range("SinglyLinkedList::back() const - empty list");
            }
            return tail->data;
        }

        // push_front
        void push_front(const T& value) override {
            Node* newNode = new Node(value);
            newNode->next = head;
            head = newNode;
            if (mSize == 0) {
                tail = newNode;
            }
            ++mSize;
        }
        void push_front(T&& value) override {
            Node* newNode = new Node(std::move(value));
            newNode->next = head;
            head = newNode;
            if (mSize == 0) {
                tail = newNode;
            }
            ++mSize;
        }

        // push_back
        void push_back(const T& value) override {
            Node* newNode = new Node(value);
            if (empty()) {
                head = tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
            ++mSize;
        }
        void push_back(T&& value) override {
            Node* newNode = new Node(std::move(value));
            if (empty()) {
                head = tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
            ++mSize;
        }

        // pop_front
        void pop_front() override {
            if (empty()) {
                throw std::out_of_range("SinglyLinkedList::pop_front() - empty list");
            }
            Node* temp = head;
            head = head->next;
            delete temp;
            --mSize;
            if (mSize == 0) {
                tail = nullptr;
            }
        }

        // pop_back
        void pop_back() override {
            if (empty()) {
                throw std::out_of_range("SinglyLinkedList::pop_back() - empty list");
            }
            if (mSize == 1) {
                delete head;
                head = tail = nullptr;
                mSize = 0;
                return;
            }
            // tail 직전 노드 찾기
            Node* cur = head;
            while (cur->next != tail) {
                cur = cur->next;
            }
            delete tail;
            tail = cur;
            tail->next = nullptr;
            --mSize;
        }

        // 인덱스 기반 접근
        T& at(std::size_t pos) override {
            if (pos >= mSize) {
                throw std::out_of_range("SinglyLinkedList::at - index out of range");
            }
            return getNodeAt(pos)->data;
        }

        const T& at(std::size_t pos) const override {
            if (pos >= mSize) {
                throw std::out_of_range("SinglyLinkedList::at const - index out of range");
            }
            return getNodeAt(pos)->data;
        }

        // 삽입 (pos 위치) [0 <= pos <= size()]
        // insert 메서드 예외 안전성 개선
        void insert(std::size_t pos, const T& value) override {
            if (pos > mSize) {
                throw std::out_of_range("SinglyLinkedList::insert(pos) - out of range");
            }
            
            try {
                if (pos == 0) {
                    push_front(value);
                } else if (pos == mSize) {
                    push_back(value);
                } else {
                    Node* prev = getNodeAt(pos - 1);
                    Node* newNode = new Node(value);  // 예외가 발생할 수 있는 부분
                    // 이 이후는 예외 발생하지 않음
                    newNode->next = prev->next;
                    prev->next = newNode;
                    ++mSize;
                }
            } catch (const std::bad_alloc& e) {
                // new 연산자 실패 시 현재 상태 유지
                throw;  // 예외 재전파
            }
        }

        // 이동 버전의 insert도 비슷하게 수정
        void insert(std::size_t pos, T&& value) override {
            if (pos > mSize) {
                throw std::out_of_range("SinglyLinkedList::insert(pos, rvalue) - out of range");
            }
            
            try {
                if (pos == 0) {
                    push_front(std::move(value));
                } else if (pos == mSize) {
                    push_back(std::move(value));
                } else {
                    Node* prev = getNodeAt(pos - 1);
                    Node* newNode = new Node(std::move(value));
                    newNode->next = prev->next;
                    prev->next = newNode;
                    ++mSize;
                }
            } catch (const std::bad_alloc& e) {
                throw;
            }
        }

        // 삭제 (pos 위치) [0 <= pos < size()]
        void erase(std::size_t pos) override {
            if (pos >= mSize) {
                throw std::out_of_range("SinglyLinkedList::erase(pos) - out of range");
            }
            if (pos == 0) {
                pop_front();
            } else if (pos == mSize - 1) {
                pop_back();
            } else {
                Node* prev = getNodeAt(pos - 1);
                Node* cur = prev->next;
                prev->next = cur->next;
                delete cur;
                --mSize;
            }
        }

    private:
        /**
         * @brief pos 위치의 노드 포인터를 반환 (0 <= pos < mSize)
         *        내부에서만 사용, 범위는 외부에서 검사 완료했다고 가정.
         */
        Node* getNodeAt(std::size_t pos) const {
            Node* cur = head;
            for (std::size_t i = 0; i < pos; i++) {
                cur = cur->next;
            }
            return cur;
        }
    };

} // namespace mydsa

#endif // MYDSA_SINGLY_LINKED_LIST_H
