#include <iostream>
#include <typeinfo>
#include <memory>
#include <utility>
#include <boost/type_index.hpp>

/*
std::move 只做一件事,就是把实参强制转换成右值,强调的是转换而不是移动
称为移动是因为转换为右值后,右值可以移动

std::forward 仅单传入的实参被绑定到右值时,它才针对该实参实施向右值型别的强制型别转换
否则就按原型别返回

std::move 和 std::forward 在运行期不会做任何操作
*/

 
struct A
{
    A(int&& n) { std::cout << "rvalue overload, n=" << n << '\n'; }
    A(int& n)  { std::cout << "lvalue overload, n=" << n << '\n'; }
};
 
class B
{
public:
    template<class T1, class T2, class T3>
    B(T1&& t1, T2&& t2, T3&& t3) :
        a1_{std::forward<T1>(t1)},
        a2_{std::forward<T2>(t2)},
        a3_{std::forward<T3>(t3)}
    {}
 
private:
    A a1_, a2_, a3_;
};
 
template<class T, class U>
std::unique_ptr<T> make_unique1(U&& u)
{
    return std::unique_ptr<T>(new T(std::forward<U>(u)));
}
 
template<class T, class... U>
std::unique_ptr<T> make_unique2(U&&... u)
{
    return std::unique_ptr<T>(new T(std::forward<U>(u)...));
}
 
auto make_B(auto&&... args) // since C++20
{
    return B(std::forward<decltype(args)>(args)...);
}
 
int main()
{
    auto p1 = make_unique1<A>(2); // rvalue
    int i = 1;
    auto p2 = make_unique1<A>(i); // lvalue
 
    std::cout << "B\n";
    auto t = make_unique2<B>(2, i, 3);
 
    std::cout << "make_B\n";
    [[maybe_unused]] B b = make_B(4, i, 5);

    std::cout << " i : " << std::boolalpha << std::is_rvalue_reference<decltype(i)>::value << std::endl;
    std::cout << " move(i) : " << std::boolalpha << std::is_rvalue_reference<decltype(std::move(i))>::value << std::endl;
    std::cout << " move(10) : " << std::boolalpha << std::is_rvalue_reference<decltype(std::move(10))>::value << std::endl;

}