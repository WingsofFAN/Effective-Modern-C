#include<iostream>
#include<typeinfo>
#include <type_traits>
#include <array>

/*
定义：
template<typename T> 
void f(ParamType param); 
调用：
f(expr);
在编译期，编译器会通过 expr 推导两个型别： 
1.首先是 T 的型别
2.然后根据 T，推导出ParamType的型别

因此，在模板推导时可能回存在者3种情况：
1. ParamType 具有指针或引用型别，但不是个万能引用
2. ParamType 是个万能引用
3. ParamType 既非指针，也非万能引用

*/


//情况一：
template<typename T> 
void f1(T& param)              // param 是个引用
{
    std::cout << "is_const == " << std::boolalpha << std::is_const<T>::value << std::endl;
    std::cout << "is_int == " << std::boolalpha << std::is_integral<T>::value << std::endl;
    std::cout << "is_volatile  == " << std::boolalpha << std::is_volatile<T>::value << std::endl;
    std::cout << "is_pointer == " << std::boolalpha << std::is_pointer<T>::value << std::endl;
    std::cout << "is_reference == " << std::boolalpha << std::is_reference<T>::value << std::endl;
    std::cout << "is_rvalue_reference == " << std::boolalpha << std::is_rvalue_reference<T>::value << std::endl;
    std::cout << "is_lvalue_reference == " << std::boolalpha << std::is_lvalue_reference<T>::value << std::endl;
    std::cout << "is_function == " << std::boolalpha << std::is_function<T>::value << std::endl;
}

template<typename T> 
void f2(const T& param)        // param 现在是个 const 引用了
{
    std::cout << "is_const == " << std::boolalpha << std::is_const<T>::value << std::endl;
    std::cout << "is_int == " << std::boolalpha << std::is_integral<T>::value << std::endl;
    std::cout << "is_volatile  == " << std::boolalpha << std::is_volatile<T>::value << std::endl;
    std::cout << "is_pointer == " << std::boolalpha << std::is_pointer<T>::value << std::endl;
    std::cout << "is_reference == " << std::boolalpha << std::is_reference<T>::value << std::endl;
    std::cout << "is_rvalue_reference == " << std::boolalpha << std::is_rvalue_reference<T>::value << std::endl;
    std::cout << "is_lvalue_reference == " << std::boolalpha << std::is_lvalue_reference<T>::value << std::endl;
    std::cout << "is_function == " << std::boolalpha << std::is_function<T>::value << std::endl;
}

template<typename T> 
void f3(T* param)        // param 现在是个指针了
{
    std::cout << "is_const == " << std::boolalpha << std::is_const<T>::value << std::endl;
    std::cout << "is_int == " << std::boolalpha << std::is_integral<T>::value << std::endl;
    std::cout << "is_volatile  == " << std::boolalpha << std::is_volatile<T>::value << std::endl;
    std::cout << "is_pointer == " << std::boolalpha << std::is_pointer<T>::value << std::endl;
    std::cout << "is_reference == " << std::boolalpha << std::is_reference<T>::value << std::endl;
    std::cout << "is_rvalue_reference == " << std::boolalpha << std::is_rvalue_reference<T>::value << std::endl;
    std::cout << "is_lvalue_reference == " << std::boolalpha << std::is_lvalue_reference<T>::value << std::endl;
    std::cout << "is_function == " << std::boolalpha << std::is_function<T>::value << std::endl;
    std::cout << "is_bounded_array == " << std::boolalpha << std::is_bounded_array<T>::value << std::endl;
    std::cout << "is_unbounded_array == " << std::boolalpha << std::is_unbounded_array<T>::value << std::endl;
    std::cout << "is_array == " << std::boolalpha << std::is_array<T>::value << std::endl;
}

//情况二：
template<typename T> 
void f4(T&& param)        // param 现在是个万能引用
{
    std::cout << "is_const == " << std::boolalpha << std::is_const<T>::value << std::endl;
    std::cout << "is_int == " << std::boolalpha << std::is_integral<T>::value << std::endl;
    std::cout << "is_volatile  == " << std::boolalpha << std::is_volatile<T>::value << std::endl;
    std::cout << "is_pointer == " << std::boolalpha << std::is_pointer<T>::value << std::endl;
    std::cout << "is_reference == " << std::boolalpha << std::is_reference<T>::value << std::endl;
    std::cout << "is_rvalue_reference == " << std::boolalpha << std::is_rvalue_reference<T>::value << std::endl;
    std::cout << "is_lvalue_reference == " << std::boolalpha << std::is_lvalue_reference<T>::value << std::endl;
    std::cout << "is_function == " << std::boolalpha << std::is_function<T>::value << std::endl;
    std::cout << "is_bounded_array == " << std::boolalpha << std::is_bounded_array<T>::value << std::endl;
    std::cout << "is_unbounded_array == " << std::boolalpha << std::is_unbounded_array<T>::value << std::endl;
    std::cout << "is_array == " << std::boolalpha << std::is_array<T>::value << std::endl;

}

//情况三：
template<typename T> 
void f5(T param)        // param 仍按值传递
{
    std::cout << "is_const == " << std::boolalpha << std::is_const<T>::value << std::endl;
    std::cout << "is_int == " << std::boolalpha << std::is_integral<T>::value << std::endl;
    std::cout << "is_volatile  == " << std::boolalpha << std::is_volatile<T>::value << std::endl;
    std::cout << "is_pointer == " << std::boolalpha << std::is_pointer<T>::value << std::endl;
    std::cout << "is_reference == " << std::boolalpha << std::is_reference<T>::value << std::endl;
    std::cout << "is_rvalue_reference == " << std::boolalpha << std::is_rvalue_reference<T>::value << std::endl;
    std::cout << "is_lvalue_reference == " << std::boolalpha << std::is_lvalue_reference<T>::value << std::endl;
    std::cout << "is_function == " << std::boolalpha << std::is_function<T>::value << std::endl;
    std::cout << "is_bounded_array == " << std::boolalpha << std::is_bounded_array<T>::value << std::endl;
    std::cout << "is_unbounded_array == " << std::boolalpha << std::is_unbounded_array<T>::value << std::endl;
    std::cout << "is_array == " << std::boolalpha << std::is_array<T>::value << std::endl;

}


// 其他情况：
// 数组实参：
//  以编译期常灶形式返回数组尺寸
// （该数组形参未起名字，因为我们只关心共含行的元素个数）
template<typename T, std:: size_t N> 
constexpr std::size_t arraySize(T (&)[N]) noexcept 
{
    return N;
}
//将该函数声明为constexpr，能够使得返回值在编译期间就可用


// 函数实参：

void someFunc(int,double){};

int main()
{
    int x = 27;             // x的型别是 int
    const int ex= x;        // ex 的型别是 const int 
    const int &rx = x;      // rx 的型别为 const int 的引用
    const int *px = &x;     // px 的类型为 const int *

    //情况一：
    std::cout <<  "void f1(T& param) : " << std::endl;
    std::cout <<  "f1(x):" << std::endl; f1(x);   //T 的型别是  int, param 的型别是 int&
    std::cout <<  "f1(ex):" << std::endl;f1(ex);  //T 的型别是 const int, param 的型别是 const int&
    std::cout <<  "f1(rx):" << std::endl;f1(rx);  //T 的型别是 const int, param 的型别是 const int&

    std::cout <<  "void f2(T& param) : " << std::endl;
    std::cout <<  "f2(x):" << std::endl;f2(x);    //T 的型别是  int, param 的型别是 const int&
    std::cout <<  "f2(ex):" << std::endl;f2(ex);  //T 的型别是  int, param 的型别是 const int&
    std::cout <<  "f2(rx):" << std::endl;f2(rx);  //T 的型别是  int, param 的型别是 const int&

    std::cout <<  "void f3(T& param) : " << std::endl;
    std::cout <<  "f3(&x) :" << std::endl; f3(&x) ; //T 的型别是 int, param 的型别是 int*
    std::cout <<  "f3(px):"  << std::endl;f3(px);   //T 的型别是 const int, param 的型别是 const int*

    //情况二：
    std::cout <<  "void f4(T&& param) : " << std::endl;
    std::cout <<  "f4(x):" << std::endl;  f4(x);   // T是个左值，所以T的型别是 int&, param 型别也是 int&
    std::cout <<  "f4(ex):" << std::endl; f4(ex);  // cx 是个左值，所以T的型别是 const int&, param 的型别也是 const int& 
    std::cout <<  "f4(rx):" << std::endl; f4(rx);  // rx 是个左值，所以T的型别是 const int&, param 型别也是 const int& 
    std::cout <<  "f4(27):" << std::endl; f4(27);  // 27 是个右值，所以T的型别是 int,那么param 型别就成 int&&
    
    //情况三：
    std::cout <<  "void f5(T param) : " << std::endl;
    std::cout <<  "f5(x):" << std::endl; f5(x);    //param和T的型别别都是 int
    std::cout <<  "f5(ex):" << std::endl;f5(ex);   //param和T的型别别都是 int 
    std::cout <<  "f5(rx):" << std::endl;f5(rx);   //param和T的型别别都是 int 

    //数组实参：
    const char name [] = "J. P. Briggs" ;    // name 的型别是 const char[13] 
    const char * ptrToName = name;           // 数组退化成指针 const char *


    //与书中记录结果不相符合
    std::cout <<  "void f3(T& param) : " << std::endl;
    std::cout <<  "f3(name):" << std::endl; f3(name);             // T的型别推导结果是 const char 
    std::cout <<  "f3(ptrToName):" << std::endl;f3(ptrToName);    // T的型别推导结果是 const char 


    std::cout <<  "void f5(T param) : " << std::endl;
    std::cout <<  "f5(name):" << std::endl; f5(name);             // T 被推导为 const char*
    std::cout <<  "f5(ptrToName):" << std::endl;f5(ptrToName);    // T 被推导为 const char*

    int keyVals[] = {1,2,3,4,5};
    // int mappedVals[arraySize(keyVals)];
    std::array<int,arraySize(keyVals)> mappedVals;

    //函数实参：
    std::cout <<  "void f3(T& param) : " << std::endl;
    std::cout <<  "f3(smoeFunc):" << std::endl; f3(someFunc);             // T 被推导为 void (&)(int, double)
  
    std::cout <<  "void f5(T param) : " << std::endl;
    std::cout <<  "f5(smoeFunc):" << std::endl; f5(someFunc);             // T 被推导为 void (*)(int, double)

    return 0;
}