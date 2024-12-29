/**
 * @file MyVector.h
 * @brief A custom dynamic array (similar to std::vector) implementation in C++.
 *
 * Rules / Guidelines:
 * 1. No direct usage of std::vector or other advanced containers.
 * 2. Memory reallocation is handled manually (reallocate function).
 * 3. Provide basic exception safety (throw std::out_of_range for invalid index).
 * 4. Implement copy/move constructors & operators to manage resource ownership.
 * 5. Keep interface similar to std::vector where possible (size(), capacity(), operator[], etc.).
 */

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <cstddef>        // for size_t
#include <stdexcept>      // for std::out_of_range
#include <initializer_list>
#include <utility>        // for std::move, std::swap (if needed)

/**
 * @namespace mydsa
 * Custom namespace to avoid name collisions with other libraries.
 */
namespace mydsa {

    /**
     * @class MyVector
     * @tparam T The element type stored in the dynamic array.
     *
     * MyVector is a custom dynamic array implementation, mimicking some features
     * of std::vector but written from scratch to practice memory management,
     * resource ownership, and C++ class design.
     */
    template <typename T>
    class MyVector {
    public:
         /* ------------------------------------------------
         *  1. 이터레이터 타입 정의
         * ------------------------------------------------ */
         // (a) iterator
        class iterator {
        public:
            // 타입 정의 (iterator_traits에서 사용)
            using value_type        = T;
            using pointer           = T*;
            using reference         = T&;
            using difference_type   = std::ptrdiff_t;
            using iterator_category = std::random_access_iterator_tag;

            iterator() : mPtr(nullptr) {}
            explicit iterator(pointer ptr) : mPtr(ptr) {}

            // * 연산자
            reference operator*() const { return *mPtr; }
            pointer operator->() const { return mPtr; }

            // ++, -- 연산자 (전위)
            iterator& operator++() {
                ++mPtr;
                return *this;
            }
            iterator& operator--() {
                --mPtr;
                return *this;
            }

            // 후위 ++, --
            iterator& operator++(int) {
                iterator tmp(*this);
                ++(*this);
                return tmp;
            }
            iterator operator--(int) {
                iterator tmp(*this);
                --(*this);
                return tmp;
            }

            // +, - 연산자 (random_access_iterator 특성)
            iterator operator+(difference_type n) const {
                return iterator(mPtr + n);
            }
            iterator operator-(difference_type n) const {
                return iterator(mPtr - n);
            }
            iterator& operator+=(difference_type n) {
                mPtr += n;
                return *this;
            }
            iterator& operator-=(difference_type n) {
                mPtr -= n;
                return *this;
            }

            difference_type operator-(const iterator& other) const {
                return mPtr - other.mPtr;
            }

            // 비교 연산자
            bool operator==(const iterator& other) const { return mPtr == other.mPtr; }
            bool operator!=(const iterator& other) const { return !(*this == other); }
            bool operator<(const iterator& other)  const { return mPtr < other.mPtr; }
            bool operator>(const iterator& other)  const { return other < *this; }
            bool operator<=(const iterator& other) const { return !(other < *this); }
            bool operator>=(const iterator& other) const { return !(*this < other); }

        private:
            pointer mPtr;
        };

         // (b) const_iterator
        class const_iterator {
        public:
            using value_type        = T;
            using pointer           = const T*;
            using reference         = const T&;
            using difference_type   = std::ptrdiff_t;
            using iterator_category = std::random_access_iterator_tag;

            const_iterator() : mPtr(nullptr) {}
            explicit const_iterator(pointer ptr) : mPtr(ptr) {}

            // const 버전의 * 연산자
            reference operator*() const { return *mPtr; }
            pointer operator->() const { return mPtr; }

            // ++, -- 연산자 (전위)
            const_iterator& operator++() {
                ++mPtr;
                return *this;
            }
            const_iterator& operator--() {
                --mPtr;
                return *this;
            }

            // 후위 ++, --
            const_iterator operator++(int) {
                const_iterator tmp(*this);
                ++(*this);
                return tmp;
            }
            const_iterator operator--(int) {
                const_iterator tmp(*this);
                --(*this);
                return tmp;
            }

            // +, - 연산자 
            const_iterator operator+(difference_type n) const {
                return const_iterator(mPtr + n);
            }
            const_iterator operator-(difference_type n) const {
                return const_iterator(mPtr - n);
            }
            const_iterator& operator+=(difference_type n) {
                mPtr += n;
                return *this;
            }
            const_iterator& operator-=(difference_type n) {
                mPtr -= n;
                return *this;
            }

            difference_type operator-(const const_iterator& other) const {
                return mPtr - other.mPtr;
            }

            // 비교 연산자
            bool operator==(const const_iterator& other) const { return mPtr == other.mPtr; }
            bool operator!=(const const_iterator& other) const { return !(*this == other); }
            bool operator<(const const_iterator& other)  const { return mPtr < other.mPtr; }
            bool operator>(const const_iterator& other)  const { return other < *this; }
            bool operator<=(const const_iterator& other) const { return !(other < *this); }
            bool operator>=(const const_iterator& other) const { return !(*this < other); }

            // MyVector<T>::iterator로부터 const_iterator로의 변환 (암시적 가능)
            const_iterator(const iterator& it) : mPtr(it.operator->()) {}

        private:
            pointer mPtr; 
        };

        // (c) reverse_iterator, const_reverse_iterator
        //     보통은 std::reverse_iterator<T*> 등을 이용하거나
        //     별도 클래스로 구현하지만, 여기서는 간단히 typedef만
        //     예시로 보여줍니다.
        using reverse_iterator       = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        /**
         * @brief Default constructor
         * @param capacity Initial capacity to allocate (default = 0)
         *
         * - If capacity > 0, allocate that much space.
         * - Otherwise, wait until first push_back to allocate (lazy).
         */
        explicit MyVector(std::size_t capacity = 0);

        /**
         * @brief Construct from an initializer list
         *        e.g. MyVector<int> v = {1, 2, 3, 4};
         */
        MyVector(std::initializer_list<T> init);

        /**
         * @brief Copy constructor
         *        Performs deep copy of other's data
         */
        MyVector(const MyVector& other);

        /**
         * @brief Move constructor
         *        Transfers ownership of other's resources to *this
         */
        MyVector(MyVector&& other) noexcept;

        /**
         * @brief Destructor
         *        Release allocated memory
         */
        ~MyVector();

        /**
         * @brief Copy assignment operator
         *        Deep copies other's data
         */
        MyVector& operator=(const MyVector& other);

        /**
         * @brief Move assignment operator
         *        Transfers ownership of other's resources
         */
        MyVector& operator=(MyVector&& other) noexcept;

        /* ---------------------------
        *  Capacity-related methods
        * --------------------------- */

        /**
         * @return The number of elements stored in this vector
         */
        std::size_t size() const noexcept;

        /**
         * @return The current allocated capacity
         */
        std::size_t capacity() const noexcept;

        /**
         * @return true if size() == 0
         */
        bool empty() const noexcept;

        /**
         * @brief Requests that the capacity be at least newCapacity
         * @param newCapacity Desired capacity
         *
         * If newCapacity > current capacity, reallocate to expand storage.
         * If newCapacity <= capacity(), does nothing.
         */
        void reserve(std::size_t newCapacity);

        /**
         * @brief Reduce capacity() to match size()
         *
         * If capacity() > size(), it shrinks the allocated memory to exactly size().
         */
        void shrink_to_fit();

        /**
         * @brief Erase all elements (size=0), but does not reduce capacity
         */
        void clear();

        /**
         * @brief Resize vector spaces *2
         */
        void resize(std::size_t newSize);
        void resize(std::size_t newSize, const T& value);

        /* ---------------------------
        *  Element access
        * --------------------------- */

        /**
         * @brief Bracket operator for non-const access
         * @param index Zero-based index
         * @return Reference to the element
         * @warning No bounds checking (like std::vector::operator[])
         */
        T& operator[](std::size_t index);

        /**
         * @brief Bracket operator for const access
         */
        const T& operator[](std::size_t index) const;

        /**
         * @brief at() with bounds checking
         * @throw std::out_of_range if index >= size()
         */
        T& at(std::size_t index);

        /**
         * @brief at() for const access with bounds checking
         */
        const T& at(std::size_t index) const;

        T& front();
        const T& front() const;

        T& back();
        const T& back() const;

        T& data();
        const T& data() const;

        /* ---------------------------
        *  Modifiers (insertion, deletion)
        * --------------------------- */

        /**
         * @brief Adds a copy of value to the end of the vector
         * @param value The element to add
         */
        void push_back(const T& value);

        /**
         * @brief Adds an rvalue reference (moved) value to the end
         */
        void push_back(T&& value);

        /**
         * @brief Removes the last element
         * @warning Undefined if the vector is empty
         */
        void pop_back();

        /**
         * @brief Insert a copy of value at position index
         *        Elements after index are shifted right
         * @param index The position to insert (0 <= index <= size())
         * @param value The element to insert
         * @throw std::out_of_range if index > size()
         */
        void insert(std::size_t index, const T& value);

        /**
         * @brief Insert an rvalue reference (moved) value at position index
         */
        void insert(std::size_t index, T&& value);

        /**
         * @brief Erase the element at position index
         *        Elements after index are shifted left
         * @throw std::out_of_range if index >= size()
         */
        void erase(std::size_t index);

        /* ------------------------------------------------
         *  이터레이터 관련 메서드
         * ------------------------------------------------ */
        iterator begin() noexcept {
            return iterator(mData);
        }
        iterator end() noexcept {
            return iterator(mData + mSize);
        }

        const_iterator begin() const noexcept {
            return const_iterator(mData);
        }
        const_iterator end() const noexcept {
            return const_iterator(mData + mSize);
        }

        const_iterator cbegin() const noexcept {
            return const_iterator(mData);
        }
        const_iterator cend() const noexcept {
            return const_iterator(mData + mSize);
        }

        reverse_iterator rbegin() noexcept {
            return reverse_iterator(end());
        }
        reverse_iterator rend() noexcept {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rbegin() const noexcept {
            return const_reverse_iterator(end());
        }
        const_reverse_iterator rend() const noexcept {
            return const_reverse_iterator(begin());
        }

        const_reverse_iterator crbegin() const noexcept {
            return const_reverse_iterator(cend());
        }
        const_reverse_iterator crend() const noexcept {
            return const_reverse_iterator(cbegin());
        }

    private:
        /**
         * @brief Pointer to dynamically allocated array of T
         */
        T* mData;

        /**
         * @brief Current number of elements
         */
        std::size_t mSize;

        /**
         * @brief Allocated capacity (the actual memory size)
         */
        std::size_t mCapacity;

        /**
         * @brief Reallocate storage to newCapacity
         *        Moves or copies existing elements to new storage.
         * @param newCapacity The new capacity
         */
        void reallocate(std::size_t newCapacity);
    };

    /* ============================================================
      Below: Implementation of each member function (in header)
      ============================================================ */

    // 1) Default constructor
    template<typename T>
    MyVector<T>::MyVector(std::size_t capacity) 
        : mData(nullptr), mSize(0), mCapacity(0)
    {
        if (capacity > 0) {
            mData = new T[capacity];
            mCapacity = capacity;
        }
    }

    // 2) Construct from initializer list
    template<typename T>
    MyVector<T>::MyVector(std::initializer_list<T> init)
        : mData(nullptr), mSize(0), mCapacity(0)
    {
        if (!init.empty()) {
            mData = new T[init.size()];
            mCapacity = init.size();
        }

        // copy elements
        for (auto &elem : init) {
            new (&mData[mSize]) T(elem); // placement new or just mData[mSize] = elem;
            mSize++;
        }
    }

    // 3) Copy constructor
    template <typename T>
    MyVector<T>::MyVector(const MyVector& other)
        : mData(nullptr), mSize(0), mCapacity(0)
    {
        if (other.mCapacity > 0) {
            mData = new T[other.mCapacity];
            mCapacity = other.mCapacity;
        }
        for (std::size_t i = 0; i < other.mSize; i++) {
            new (&mData[i]) T(other.mData[i]);
        }
        mSize = other.mSize;
    }

    // 4) Move constructor
    template <typename T>
    MyVector<T>::MyVector(MyVector&& other) noexcept
        : mData(other.mData), mSize(other.mSize), mCapacity(other.mCapacity)
    {
        other.mData = nullptr;
        other.mSize = 0;
        other.mCapacity = 0;
    }

    // 5) Destructor
    template <typename T>
    MyVector<T>::~MyVector()
    {
        // destroy elements
        for (std::size_t i = 0; i < mSize; i++) {
            mData[i].~T(); // call destructor explicitly if needed
        }
        delete[] mData;
        mData = nullptr;
        mSize = 0;
        mCapacity = 0;
    }

    // Copy assignment operator
    template <typename T>
    MyVector<T>& MyVector<T>::operator=(const MyVector& other)
    {
        if (this == &other) return *this; // self-assignment check

        // 1) old data cleanup
        for (std::size_t i = 0; i < mSize; i++) {
            mData[i].~T();
        }
        delete[] mData; 
        mData = nullptr;
        mSize = 0;
        mCapacity = 0;

        // 2) allocate new space
        if (other.mCapacity > 0) {
            mData = new T[other.mCapacity];
            mCapacity = other.mCapacity;
        }
        // 3) copy construct elements
        for (std::size_t i = 0; i < other.mSize; i++) {
            new (&mData[i]) T(other.mData[i]);
        }
        mSize = other.mSize;

        return *this;
    }

    // Move assignment operator
    template <typename T>
    MyVector<T>& MyVector<T>::operator=(MyVector&& other) noexcept
    {
        if (this == &other) return *this; // self-assignment check

        // clean up current data
        for (std::size_t i = 0; i < mSize; i++) {
            mData[i].~T();
        }
        delete[] mData;

        // steal other's data
        mData = other.mData;
        mSize = other.mSize;
        mCapacity = other.mCapacity;

        // nullify other
        other.mData = nullptr;
        other.mSize = 0;
        other.mCapacity = 0;

        return *this;
    }

    /* ------------------------------------------------
     *  Capacity-related methods
     * ------------------------------------------------ */
    template<typename T>
    std::size_t MyVector<T>::size() const noexcept {
        return mSize;
    }

    template<typename T>
    std::size_t MyVector<T>::capacity() const noexcept {
        return mCapacity;
    }

    template<typename T>
    bool MyVector<T>::empty() const noexcept {
        return (mSize == 0);
    }

    template<typename T>
    void MyVector<T>::reserve(std::size_t newCap)
    {
        if (newCap <= mCapacity) return;
        reallocate(newCap);
    }

    template<typename T>
    void MyVector<T>::shrink_to_fit()
    {
        if (mCapacity > mSize) {
            reallocate(mSize);
        }
    }

    template<typename T>
    void MyVector<T>::clear() {
        for (size_t i = 0; i < mSize; ++i) {
            mData[i].~T();
        }
        mSize = 0;
    }

    template<typename T>
    void MyVector<T>::resize(std::size_t newSize) {
        resize(newSize, T());
    }

    template<typename T>
    void MyVector<T>::resize(std::size_t newSize, const T& value) {
        if (newSize > mSize) {
            if (newSize > mCapacity) {
                reserve(newSize);
            }
            // 새로운 요소들을 value로 초기화
            for (std::size_t i = mSize; i < newSize; i++) {
                new (&mData[i]) T(value);
            }
        } else if (newSize < mSize) {
            // 초과 요소들 소멸
            
        }
    }
    /* ------------------------------------------------
     *  Element access
     * ------------------------------------------------ */
    template<typename T>
    T& MyVector<T>::operator[](std::size_t index) {
        return mData[index];
    }

    template<typename T>
    const T& MyVector<T>::operator[](std::size_t index) const {
        return mData[index];
    }

    // at() with range check
    template <typename T>
    T& MyVector<T>::at(std::size_t index)
    {
        if (index >= mSize) {
            throw std::out_of_range("MyVector::at - index out of range");
        }
        return mData[index];
    }

    template <typename T>
    const T& MyVector<T>::at(std::size_t index) const
    {
        if (index >= mSize) {
            throw std::out_of_range("MyVector::at (const) - index out of range");
        }
        return mData[index];
    }

    template <typename T>
    T& MyVector<T>::front() {
        if (empty()) {
            throw std::out_of_range("MyVector::front - vector is empty");
        }
        return mData[0];
    }

    template <typename T>
    const T& MyVector<T>::front() const {
        if (empty()) {
            throw std::out_of_range("MyVector::front - vector is empty");
        }
        return mData[0];
    }

    template <typename T>
    T& MyVector<T>::back() {
        if (empty()) {
            throw std::out_of_range("MyVector::back - vector is empty");
        }
        return mData[mSize - 1];
    }

    template <typename T>
    const T& MyVector<T>::back() const {
        if (empty()) {
            throw std::out_of_range("MyVector::back - vector is empty");
        }
        return mData[mSize - 1];
    }

    template <typename T>
    T& MyVector<T>::data() {
        if (empty()) {
            throw std::out_of_range("MyVector::data - vector is empty");
        }
        return mData;
    }

    template <typename T>
    const T& MyVector<T>::data() const {
        if (empty()) {
            throw std::out_of_range("MyVector::data - vector is empty");
        }
        return mData;
    }
    /* ------------------------------------------------
     *  Modifiers
     * ------------------------------------------------ */

    // push_back
    template <typename T>
    void MyVector<T>::push_back(const T& value)
    {
        if (mSize >= mCapacity) {
            std::size_t newCap = (mCapacity == 0) ? 1 : mCapacity * 2;
            reallocate(newCap);
        }
        new (&mData[mSize]) T(value); 
        mSize++;
    }

    // push_back (rvalue)
    template <typename T>
    void MyVector<T>::push_back(T&& value)
    {
        if (mSize >= mCapacity) {
            std::size_t newCap = (mCapacity == 0) ? 1 : mCapacity * 2;
            reallocate(newCap);
        }
        new (&mData[mSize]) T(std::move(value));
        mSize++;
    }

    template <typename T>
    void MyVector<T>::pop_back()
    {
        if (mSize == 0) {
            // optional: throw or just ignore
            return;
        }
        mSize--;
        mData[mSize].~T(); // destruct last element
    }

    // insert
    template <typename T>
    void MyVector<T>::insert(std::size_t pos, const T& value)
    {
        if (pos > mSize) {
            throw std::out_of_range("MyVector::insert - pos out of range");
        }
        // if no space, reallocate
        if (mSize >= mCapacity) {
            std::size_t newCap = (mCapacity == 0) ? 1 : mCapacity * 2;
            reallocate(newCap);
        }
        // shift elements right
        for (std::size_t i = mSize; i > pos; i--) {
            mData[i] = std::move(mData[i - 1]);
        }
        // construct new element
        mData[pos] = value; 
        mSize++;
    }

    // insert rvalue
    template <typename T>
    void MyVector<T>::insert(std::size_t pos, T&& value)
    {
        if (pos > mSize) {
            throw std::out_of_range("MyVector::insert (rvalue) - pos out of range");
        }
        if (mSize >= mCapacity) {
            std::size_t newCap = (mCapacity == 0) ? 1 : mCapacity * 2;
            reallocate(newCap);
        }
        for (std::size_t i = mSize; i > pos; i--) {
            mData[i] = std::move(mData[i - 1]);
        }
        mData[pos] = std::move(value);
        mSize++;
    }

    // erase
    template <typename T>
    void MyVector<T>::erase(std::size_t pos)
    {
        if (pos >= mSize) {
            throw std::out_of_range("MyVector::erase - pos out of range");
        }
        // shift left
        for (std::size_t i = pos; i < mSize - 1; i++) {
            mData[i] = std::move(mData[i + 1]);
        }
        mSize--;
        mData[mSize].~T(); // destruct the last 'moved-from' slot
    }

    // private reallocate
    template <typename T>
    void MyVector<T>::reallocate(std::size_t newCap)
    {
        // allocate new block
        T* newData = new T[newCap];

        // move or copy existing elements
        for (std::size_t i = 0; i < mSize; i++) {
            new (&newData[i]) T(std::move(mData[i]));
            mData[i].~T(); // destroy old
        }

        // delete old storage
        delete[] mData;

        mData = newData;
        mCapacity = newCap;
    }

} // namespace mydsa

#endif // MY_VECTOR_H
