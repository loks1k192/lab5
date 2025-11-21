#include <stdexcept>

#include "stack.h"

template <class T, class Alloc>
Stack<T, Alloc>::Stack(std::pmr::memory_resource *r)
    : alloc(r) {}

template <class T, class Alloc>
Stack<T, Alloc>::Stack(const Alloc &a)
    : alloc(a) {}

template <class T, class Alloc>
Stack<T, Alloc>::~Stack()
{
    while (!empty())
        pop();
}

template <class T, class Alloc>
void Stack<T, Alloc>::push(const T &v)
{
    using NodeAlloc = std::pmr::polymorphic_allocator<Node>;
    NodeAlloc node_alloc(alloc.resource()); // создаём аллокатор для Node
    Node *n = node_alloc.allocate(1);
    try
    {
        new (&n->value) T(v);
        n->next = head;
        head = n;
        ++cnt;
    }
    catch (...)
    {
        node_alloc.deallocate(n, 1);
        throw;
    }
}

template <class T, class Alloc>
void Stack<T, Alloc>::push(T &&v)
{
    using NodeAlloc = std::pmr::polymorphic_allocator<Node>;
    NodeAlloc node_alloc(alloc.resource());
    Node *n = node_alloc.allocate(1);
    try
    {
        new (&n->value) T(std::move(v));
        n->next = head;
        head = n;
        ++cnt;
    }
    catch (...)
    {
        node_alloc.deallocate(n, 1);
        throw;
    }
}

template <class T, class Alloc>
void Stack<T, Alloc>::pop()
{
    if (empty())
        return;
    Node *n = head;
    head = n->next;
    n->value.~T();
    using NodeAlloc = std::pmr::polymorphic_allocator<Node>;
    NodeAlloc node_alloc(alloc.resource());
    node_alloc.deallocate(n, 1);
    --cnt;
}
template <class T, class Alloc>
T &Stack<T, Alloc>::top()
{
    if (empty())
        throw std::out_of_range("Stack is empty");
    return head->value;
}

template <class T, class Alloc>
const T &Stack<T, Alloc>::top() const
{
    if (empty())
        throw std::out_of_range("Stack is empty");
    return head->value;
}