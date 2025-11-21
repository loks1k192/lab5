#include <iostream>
#include <memory_resource>

#include "allocator.h"
#include "stack.h"

struct Foo
{
    int a;
    double b;

    Foo() = default;
    Foo(int aa, double bb) : a(aa), b(bb) {}
};

int main()
{
    try
    {
        Allocator vmr(16 * 1024);

        Stack<Foo> st(&vmr);

        st.push(Foo{1, 3.14});
        st.push(Foo{2, 2.71});
        st.push(Foo{3, 1.41});

        std::cout << "Stack size: " << st.size() << "\n";

        for (const auto &f : st)
        {
            std::cout << "Foo: a=" << f.a << " b=" << f.b << "\n";
        }

        st.pop();
        std::cout << "After pop, size: " << st.size() << "\n";
        std::cout << "Top: a=" << st.top().a << " b=" << st.top().b << "\n";

        Stack<int> si(&vmr);
        si.push(10);
        si.push(20);
        si.push(30);

        std::cout << "Ints: ";
        for (int x : si)
            std::cout << x << " ";
        std::cout << "\n";
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "bad_alloc: " << e.what() << "\n";
        return 2;
    }
    catch (const std::exception &e)
    {
        std::cerr << "exception: " << e.what() << "\n";
        return 3;
    }

    return 0;
}