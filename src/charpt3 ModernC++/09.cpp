#include <iostream>
#include <type_traits>
#include <array>

/*
1.  在声明处理涉及函数指针的型别时,使用别名比typedef更清楚:

// FP的型别是一个指涉到函数的指针，该函数形参包括:
// －个 int con st std : : string& 没有返回伯
typedef void (*FP)(int , canst std::string&);  // 使用 typedef

// 与上一句意义相同
using FP = void (*)(int, canst std::string&);  // 使用别名声明

2. 方便使用模板:
template<typename T> //MyAllocList<T>
using MyAllocList = std:: list<T, MyAlloc <T>>;  // std::list<T, MyAlloc<T>>的同义词
MyAllocList<Widget> lw;                          // 客户代码

如果使用 typedef 的话，你几乎肯定要从头自己动手了
template<typename T>                             // MyAllocList<T>::type
struct MyAlloclist {                             // std::list<T, MyAlloc<T>> 同义词
    typedef std::list<T, MyAlloc<T>> type;
};
MyAllocList<Widget>::type lw;                    // 客户代码


3. 型别特征变换:
std::remove_const<T>::type                  // C++11 const T -> T
std::remove_const_t<T>                      // C++14 中的等价物

std::remove_reference<T>::type              // C++11 T&/T&& · T
std::remove reference_t<T>                  // C++14 的等价物

std::add_lvalue_reference<T>::type          // C++11 T&
std::add_lvalue_reference_t<T>              // C++14 中的等价物

*/

using myarray = const std::array<std::string, 5>;

int main()
{
    myarray a = {"hell","world","!"};
    std::remove_const_t<myarray>  b =  {"hell","world","!"};
    b[1] = "universe";
    // a[1] = "universe";


    for(auto str : a)
        std::cout << str << std::endl;

    for(auto str : b)
        std::cout << str << std::endl;

    return 0;
}