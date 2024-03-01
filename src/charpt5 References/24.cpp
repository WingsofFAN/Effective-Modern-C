#include<iostream>
#include<vector>


/*

区分万能引用和右值引用:

1.万能引用: 严格符合该形式的才有可能为万能引用 T&&

2.右值引用:


void f(Widget&& param);            //右值引用
Widget&& varl = Widget();          //右值引用
auto&& var2 = van;                 //非右值引用

template<typename T>
void f(std::vector<T>&& param);    //右值引用

template<typename T>
void f(T&& param);                 //非右值引用


*/

template<typename T>
void f1(std::vector<T>&& param)    //右值引用,不涉及完整的型别推导
{
    std::cout << "std::vector<T>&& " << "is_rvalue_reference == " << std::boolalpha << std::is_rvalue_reference<std::vector<T>&&>::value << std::endl; 
}

template<typename T>
void f2(T&& param)                 //万能引用,涉及型别推导
{
    std::cout << "T&& " << "is_rvalue_reference == " << std::boolalpha << std::is_rvalue_reference<T&&>::value << std::endl; 
}


int main()
{
    int i = 0;
    std::vector<int> vec = {1,2,3,4,5};

    f1(std::move(vec));    //右值引用
    // f1(vec);            //左值引用,错误

    f2(i);                 //左值引用
    f2(std::move(i));      //右值引用

    return 0;
}