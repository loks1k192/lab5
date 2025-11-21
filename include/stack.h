#pragma once
#include <memory_resource>
#include <cstddef>
#include <iterator>

#include "allocator.h"

template <class T, class Alloc = std::pmr::polymorphic_allocator<T>>
class Stack
{
    using traits = std::allocator_traits<Alloc>;
    struct Node
    {
        T value;
        Node *next = nullptr;
    };

    Node *head = nullptr;
    std::size_t cnt = 0;
    Alloc alloc;

public:
    class iterator
    {
        Node *ptr;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using reference = T &;
        using pointer = T *;
        using difference_type = std::ptrdiff_t;

        iterator(Node *p = nullptr) : ptr(p) {}
        reference operator*() const { return ptr->value; }
        pointer operator->() const { return &ptr->value; }
        iterator &operator++()
        {
            ptr = ptr->next;
            return *this;
        }
        iterator operator++(int)
        {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        bool operator==(const iterator &o) const { return ptr == o.ptr; }
        bool operator!=(const iterator &o) const { return ptr != o.ptr; }
    };
    using const_iterator = iterator;

public:
    explicit Stack(std::pmr::memory_resource *r = std::pmr::get_default_resource());
    explicit Stack(const Alloc &a);
    ~Stack();

    void push(const T &v);
    void push(T &&v);
    void pop();

    T &top();
    const T &top() const;

    bool empty() const noexcept { return head == nullptr; }
    std::size_t size() const noexcept { return cnt; }

    iterator begin() noexcept { return iterator(head); }
    iterator end() noexcept { return iterator(nullptr); }

    const_iterator begin() const noexcept { return iterator(head); }
    const_iterator end() const noexcept { return iterator(nullptr); }
};

#include "stack.ipp"