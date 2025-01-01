#ifndef MYDSA_ILINKEDLIST_H
#define MYDSA_ILINKEDLIST_H

#include <cstddef>       // for size_t
#include <stdexcept>     // for std::out_of_range
#include <utility>       // for std::move
#include <initializer_list>

namespace mydsa {

    /**
     * @brief 추상(abstract) LinkedList 인터페이스
     *
     * 공통으로 필요한 메서드들을 순수 가상 함수로 선언.
     * SinglyLinkedList, DoublyLinkedList, CircularLinkedList 등이
     * 이를 상속받아 실제 구현을 제공한다.
     */
    template <typename T>
    class ILinkedList {
    public:
        virtual ~ILinkedList() = default;

        // 용량/상태 관련
        virtual std::size_t size() const noexcept = 0;
        virtual bool empty() const noexcept = 0;
        virtual void clear() = 0;

        // 앞/뒤 접근
        virtual T& front() = 0;
        virtual const T& front() const = 0;
        virtual T& back() = 0;
        virtual const T& back() const = 0;

        // 삽입(앞/뒤)
        virtual void push_front(const T& value) = 0;
        virtual void push_front(T&& value)      = 0;
        virtual void push_back(const T& value)  = 0;
        virtual void push_back(T&& value)       = 0;

        // 삭제(앞/뒤)
        virtual void pop_front() = 0;
        virtual void pop_back()  = 0;

        // 인덱스 기반 삽입/삭제
        virtual void insert(std::size_t pos, const T& value) = 0;
        virtual void insert(std::size_t pos, T&& value)      = 0;
        virtual void erase(std::size_t pos)                  = 0;

        // 인덱스 기반 접근 (단일 연결리스트는 O(n)임 주의)
        virtual T& at(std::size_t pos) = 0;
        virtual const T& at(std::size_t pos) const = 0;
    };

} // namespace mydsa

#endif // MYDSA_ILINKEDLIST_H
