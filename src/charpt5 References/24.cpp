#include<iostream>
/*

区分万能引用和右值引用:

1.万能引用: 严格符合该形式的才有可能为万能引用 T&&

2.右值引用:

*/

struct A
{
    A(int&& n) { std::cout << "rvalue overload, n=" << n << '\n'; }
    A(int& n)  { std::cout << "lvalue overload, n=" << n << '\n'; }
};



template<typename T>
void f(T&& t)
{
    A a(t);
}










int main()
{
    int i = 0;

    f(i);
    f(std::move(i));

    return 0;
}