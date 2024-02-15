#include<iostream>

/*
auto推导规则与模板推导规则大致类似，只是在使用{}时，会有轻微的区别
*/

void someFunc(int, double){};             // someFunc 是个函数，型别是 void(int, double) 

/*注意：

auto createlnitlist() 
{ 
    return { 1, 2, 3 };    // ！！错误！！ 无法为{ 1, 2, 3} 完成型别推导
}


emplate<typename T>        //  带有形参的模板
void f(T param);           //  与x的声明等价的声明式
f({ 11, 23, 9 });          //  ！！错误！！ 无法推导T的型别

*/


int main()
{
    //情况一：型别饰词是指针或引用，但不是万能引用。
    auto x = 27;        //情况 (x 既非指针也非引用）
    const auto ex= x;   //情况 (ex 同样既非指针也非引用）
    const auto& rx = x; //情况 (rx 是个引用，但不是力能引用）
    //情况二：型别饰词是万能引用。
    auto&& urefl = x;   // x  的型别是 int, 且是左值，所以 urefl 的型别是 int&
    auto&& uref2 = ex;  // ex 的型别是 eonst int, 且是左值，所以uref2 的型别是 const int& 
    auto&& uref3 = 27;  // 27 的型别是 int, 且是右值，所以uref3的型别是 int&&
    //情况三：型别饰词既非指针，非引用。
    const char name[] = "R. N. Briggs" ;    // name 的型别是 canst char[13] 
    auto arrl = name;                       // arrl 的型别是 canst char* 
    auto& arr2 = name;                      // arr2 的型别是 const char (&)[13] 
    auto funcl = someFunc;                  // funcl 的型别是 void (*)(int, double)


    //特殊地，
    auto arrayNum = {1,2,3,4,5};           // 推导型别为 std::initializer_list<T>
    std::initializer_list<int>  arrayNumP = {1,2,3,4,5};
    std::cout << "auto arrayNum = {1,2,3,4,5} 与 std::initializer_list<int>  arrayNumP = {1,2,3,4,5}是否类型相同：" << std::endl;
    std::cout << std::is_same<decltype(arrayNum), decltype(arrayNumP)>() << std::endl;

    return 0;
}