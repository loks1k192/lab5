#include <gtest/gtest.h>

#include "stack.h"
#include "allocator.h"

// ---- Структура для проверки ----
struct Foo
{
    int a;
    double b;

    Foo() = default;
    Foo(int aa, double bb) : a(aa), b(bb) {}
    bool operator==(const Foo &other) const { return a == other.a && b == other.b; }
};

// ---- Тесты для Stack<int> ----
TEST(StackIntTest, PushAndSize)
{
    Allocator alloc(1024);
    Stack<int> s(&alloc);

    EXPECT_TRUE(s.empty());
    s.push(10);
    EXPECT_EQ(s.size(), 1);
    s.push(20);
    EXPECT_EQ(s.size(), 2);
}

TEST(StackIntTest, PopAndTop)
{
    Allocator alloc(1024);
    Stack<int> s(&alloc);

    s.push(1);
    s.push(2);
    s.push(3);

    EXPECT_EQ(s.top(), 3);
    s.pop();
    EXPECT_EQ(s.top(), 2);
    s.pop();
    s.pop();
    EXPECT_TRUE(s.empty());
}

// ---- Тесты для Stack<Foo> ----
TEST(StackFooTest, PushAndTop)
{
    Allocator alloc(1024);
    Stack<Foo> s(&alloc);

    s.push(Foo{1, 3.14});
    s.push(Foo{2, 2.71});

    EXPECT_EQ(s.size(), 2);
    Foo top = s.top();
    EXPECT_EQ(top.a, 2);
    EXPECT_EQ(top.b, 2.71);
}

TEST(StackFooTest, IteratorTraversal)
{
    Allocator alloc(1024);
    Stack<Foo> s(&alloc);

    s.push(Foo{1, 1.0});
    s.push(Foo{2, 2.0});
    s.push(Foo{3, 3.0});

    int expected = 3;
    for (auto &f : s)
    {
        EXPECT_EQ(f.a, expected);
        --expected;
    }
}

// ---- Тест на pop из пустого стека ----
TEST(StackTest, PopEmptyDoesNotThrow)
{
    Allocator alloc(1024);
    Stack<int> s(&alloc);
    EXPECT_NO_THROW(s.pop());
}