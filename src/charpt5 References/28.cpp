#include <iostream>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <vector>

/*

理解引用折叠:
1.Widget widgetFactory();  // 返回右值的函数
2.Widget w;                // 变量(左值)
3.func(w);                 // 调用func并传入左值: T的推导结果型别为Widget&
4.func(widgetFactory());   // 调用func并传入右值: T的推导结果型别为Widget

在C++中"引用的引用"是非法的,但是折叠引用是合法的.

template<typename T>
void func(T&& param)            // 同前

func(w)                         // 调用 func 并传入左值: T的推导结果型别为Widget&

即: void func(Widget& && param);   
折叠引用得出: void func(Widget& param);

引用推到:
如果任一引用为左值引用，则结果为左值引用。否则（即两个皆为右值引用），结果为右值引用。

引用折叠规则:
左+左 = 左
左+右 = 左
右+左 = 左
右+右 = 右   --> 引用折叠

引用折叠发生的语境:
1.模板实例化
2.auto型别生成
3.创建和运用typedef和别名声明
4.std::decltype


1.forward的实现:
template<typename T>              
T&& forward(typename remove_reference<T>::type& param)
{
    return static_cast<T&&> (param);
} 

当传入的实参是个左值Widget时,则T会被推导为Widget&型别,
然后对std::forward的调用:
Widget& && forward(typename
                    remove_reference<Widget&>::type& param)
{ return static_cast<Widget& &&>(param); } 

进一步运用,引用折叠规则和remove_reference之后为

Widget& forward(typename
                Widget& param)
{ return static_cast<Widget&>(param); }    //即左值返回左值


当传入的实参是个右值Widget时,则T会被推导为Widget&&型别,最终推导为:
Widget&& forward(typename
                Widget& param)
{ return static_cast<Widget&&>(param); }    //即右值返回右值

2.auto 和 模板推导:

*/

struct Widget
{
    /* data */
};


template<typename T>  
void func(T&& param)
{
    std::cout << "is_rvalue_reference == " << std::boolalpha << std::is_rvalue_reference<decltype(param)>::value << std::endl;
    std::cout << "is_lvalue_reference == " << std::boolalpha << std::is_lvalue_reference<decltype(param)>::value << std::endl;
};     // 万能引用

Widget widgetFactory()
{
    Widget w;
    return w;
};   // 返回右值的函数



int main()
{
    Widget w;                 // 变量左值

    std::cout << "is_rvalue_reference == " << std::boolalpha << std::is_rvalue_reference<decltype(w)>::value << std::endl;
    std::cout << "is_lvalue_reference == " << std::boolalpha << std::is_lvalue_reference<decltype(w)>::value << std::endl;

    func(w);                  // 以左值调用函数,T的型别推导结果为Widget&

    func(widgetFactory());    // 以右值调用函数,T的型别推导结果为Widget

    auto&& w1 = w;            // w1 是左值,因此auto 的型别推导结果为Widget&

    std::cout << "is_rvalue_reference == " << std::boolalpha << std::is_rvalue_reference<decltype(w1)>::value << std::endl;
    std::cout << "is_lvalue_reference == " << std::boolalpha << std::is_lvalue_reference<decltype(w1)>::value << std::endl;

    // Widget& && w1 = w;        // 将auto替换得

    // Widget& w1 = w;           // 引用折叠后得到

    auto&& w2 = widgetFactory() ;    // 以右值调用函数,auto的型别推导结果Widget

    std::cout << "is_rvalue_reference == " << std::boolalpha << std::is_rvalue_reference<decltype(w2)>::value << std::endl;
    std::cout << "is_lvalue_reference == " << std::boolalpha << std::is_lvalue_reference<decltype(w2)>::value << std::endl;


    // widget&& w2 = widgetFactory();  // 最终w2仍为右值
    
    return 0;
}