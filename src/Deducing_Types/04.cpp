#include <iostream>
#include <typeinfo>
#include <boost/type_index.hpp>


/*
很多型别推导使用，在实际使用时比较复杂，单靠规则记忆和推导较为困难，因此更多时候需要我们去查询具体型别：
1.通过IDE来查看，根具IDE的提示来判断具体的型别
2.通过编译器报错来查看，手动设计一些错误来出发错误获得编译器信息
3.在运行时，通过 typeinfo 来输出具体的类型名称 
4.在运行时，借用第三方的 Boost 库来输出具体的类型名称
*/

template<typename T>  // 只声明TD，而不定义
class TD; // TD 是型别显示类 (Type Displayer) 的缩写

template<typename T> 
void f(const T& param) 
{ 
    using std::cout; 
    cout << "T = "<< typeid(T).name() << '\n';         // 显示 T 的型别
    cout << "param = "<< typeid(param).name() << '\n'; // 显示 param 的型别
}


template<typename T> 
void fb(const T& param)
{
    using std::cout; 
    using boost::typeindex::type_id_with_cvr; 
    
    cout <<  "T = " << type_id_with_cvr<T>().pretty_name()  << "\n"; // 显示 T 的型别
    cout << "param = " <<  type_id_with_cvr<decltype(param)>().pretty_name() << '\n'; 
} 


int main()
{

    const int theAnswer = 42; 
    auto x = theAnswer; 
    auto y = &theAnswer; 

    // 通过编译器报错来查看，手动设计一些错误来出发错误获得编译器信息
    // TD<decltype(x)> xType; 
    // TD<decltype(y)> yType; 


    // 在运行时，通过 typeinfo 来输出具体的类型名称, 会有不准确的时候
    std::cout << typeid(x).name() << std::endl; 
    std::cout << typeid(y).name() << std::endl; 

    f(x);
    f(y);

    /*
    [指针]：若是指针则输出P。

    [名称空间]：若是std则输出St，若是自定义的名称空间则输出字符数及它的名字，并在开头加N，在结尾加E。

    [类别]：若是自定义的名称空间则输出字符数及它的名字，若内建类型输出如下：
    　　bool:                     b
    　　char:                     c
    　　signed char:              a
    　　unsigned char:            h
    　　(signed) short (int):     s
    　　unsigned short (int):     t
    　　(signed) (int):           i
    　　unsigned (int):           j
    　　(signed) long (int):      l
    　　unsigned long (int):      m
    　　(signed) long long (int): x
    　　unsigned long long (int): y
    　　float:                    f
    　　double:                   d
    　　long double:              e


    F代表函数，
    PF代表函数指针，函数类型以E结尾，中间的内容分别是：函数的返回值类型，函数的参数类型；
    PK代表常量指针，即“pointer to konst const" （指涉到常址的指针）
    A代表数组，紧接着的数字是数组长度，再后面的下划线内容是(_×××)元素类型
    */

    //  在运行时，借用第三方的 Boost 库来输出具体的类型名称， 会有不准确的时候
    fb(x);
    fb(y);

}