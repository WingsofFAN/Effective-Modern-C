#include<iostream>
#include<vector>
/*
decltype 一般只会鹦鹉学舌，返回给定的名字或表达式的确切型别而已，
decltype 主要用途大概就在千声明那些返回值型别依赖千形参型别的函数模板。
*/


/*
它只为说明这里使用了C++ll 中的返回值型别尾序语法 (trailing return type syntax) ，
即该函数的返回值型别将在形参列表之后（在“-＞”之后）。
返回的是局部变量的引用，会导致未定义行为
template<typename Container, typename Index>   // 能运作，但是
auto authAndAccess(Container& c, Index i )     // 亟须改进
-> decltype(c[i]) 
{
    authenticateUser(); 
    return c[i]; 
} 
*/

/*
大多数含有型别T的对象的容器的operator[] 会返回 T& ，
但是条款一解释说，模板型别推导过程中，初始化表达的引用性会被忽略。
返回的是局部变量的引用，会导致未定义行为
template<typename Container, typename Index>  // C++14 
auto authAndAccess(Container& c, Index i)     // 不甚正确
{ 
    authenticateUser(); 
    return c[i];                              // 返回值型别是根据 [i] 推导出来
}

现在， authAndAccess 的返回值型别真的和 c[i] 返回的型别一致了。
具体地说，一般情况下 c[i] 返回 T&, authAndAccess 会返回 T& 。
而对于少见情况， c[i] 返回 一个对象型别， authAndAccess 会亦步亦趋地返回对象型别。

template<typename Container, typename Index>   // C++14 ；能够运作，
decltype(auto)                                 // 但仍亟须改进
authAndAccess(Container& c, Index i) 
{
    authenticateUser(); 
    return c[i]; 
}
*/

// 万能引用
/* forward用法留待后续解析
template<typename Container, typename Index>  // c++11 最终版
auto 
authAndAccess(Container&& c, Index i) 
-> decltype(std::forward<Container>(c)[i])    // 用decltype获取模板元素的
{
    authenticateUser(); 
    return std::forward<Container>(c)[i]; 
}
*/

template<typename Container, typename Index>  // c++14 最终版
decltype(auto) 
authAndAccess(Container&& c, Index i) 
{ 
    // authenticateUser(); 
    return std::forward<Container>(c)[i]; 
}

/*
decltype(auto) fl() 
{ 
    int x = 0;
    ... 
    return x; 
}
decltype(x) 是 int, 所以 fl 返回的是 int

decltype(auto) f2() 
{ 
    int X = 0;

    return (x); 
}
decltype((x)）是 int& ，所以 f2 返回的是 int&
*/

struct Point
{
    /* data */
    int x,y;
};


int main()
{

    const int x = 0;

    // decltype(x) -> int 
    std::cout << "decltype(x) : " << std::endl;
    std::cout << "is_int == " << std::boolalpha << std::is_integral<decltype(x)>::value << std::endl;
    std::cout << "is_volatile  == " << std::boolalpha << std::is_volatile<decltype(x)>::value << std::endl;
    std::cout << "is_pointer == " << std::boolalpha << std::is_pointer<decltype(x)>::value << std::endl;
    std::cout << "is_reference == " << std::boolalpha << std::is_reference<decltype(x)>::value << std::endl;
    std::cout << "is_rvalue_reference == " << std::boolalpha << std::is_rvalue_reference<decltype(x)>::value << std::endl;
    std::cout << "is_lvalue_reference == " << std::boolalpha << std::is_lvalue_reference<decltype(x)>::value << std::endl;
   
    // decltype((x)) -> int&  左值引用
    std::cout << "decltype((x)) : " << std::endl;
    std::cout << "is_int == " << std::boolalpha << std::is_integral<decltype((x))>::value << std::endl;
    std::cout << "is_volatile  == " << std::boolalpha << std::is_volatile<decltype((x))>::value << std::endl;
    std::cout << "is_pointer == " << std::boolalpha << std::is_pointer<decltype((x))>::value << std::endl;
    std::cout << "is_reference == " << std::boolalpha << std::is_reference<decltype((x))>::value << std::endl;
    std::cout << "is_rvalue_reference == " << std::boolalpha << std::is_rvalue_reference<decltype((x))>::value << std::endl;
    std::cout << "is_lvalue_reference == " << std::boolalpha << std::is_lvalue_reference<decltype((x))>::value << std::endl;


    std::vector<int> v1 = {1,1,1,1};
    std::cout << "decltype(v1[2]) : " << std::endl;
    std::cout << "is_int == " << std::boolalpha << std::is_integral<decltype(v1[2]) >::value << std::endl;
    std::cout << "is_volatile  == " << std::boolalpha << std::is_volatile<decltype(v1[2]) >::value << std::endl;
    std::cout << "is_pointer == " << std::boolalpha << std::is_pointer<decltype(v1[2]) >::value << std::endl;
    std::cout << "is_reference == " << std::boolalpha << std::is_reference<decltype(v1[2]) >::value << std::endl;
    std::cout << "is_rvalue_reference == " << std::boolalpha << std::is_rvalue_reference<decltype(v1[2]) >::value << std::endl;
    std::cout << "is_lvalue_reference == " << std::boolalpha << std::is_lvalue_reference<decltype(v1[2]) >::value << std::endl;


    return 0;
}