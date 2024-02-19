#include<iostream>
#include<mutex>
#include<memory>
/*

1. 常见的零指针表示:
0         int
NULL      特化为某个整形, long int等
nullptr   std::nullptr_t,可以转换为任意型别的空指针
*/
struct  Widget
{
    /* data */
};


void f(int x)
{
    std::cout << "f(int x)" << std::endl;
}

void f(bool x)
{
    std::cout << "f(bool x)" << std::endl;
}

void f(long x)
{
    std::cout << "f(long x)" << std::endl;
}

void f(void* x)
{
    std::cout << "f(void* x)" << std::endl;
}



/*
2. 避免代码歧义:
auto result= findRecord( ／＊实参＊／） ;
if (result == o)
{
    ...
}

auto result= findRecord( ／＊实参＊／） ;
if (result== nullptr) 
{
    ...
}
*/


// 3. 解决多义性问题:

std::mutex f1m, f2m, f3m; // fl f2 f3 对应的信息牡
using MuxGuard =  //c++11 中的 typedef; 参见条炊
std:: lock_guard<std::mutex>; 

/*此段代码可以统一换为模板:*/
void f1(std::shared_ptr<Widget> spw)
{
    MuxGuard g(f1m);          // 为f1锁定
    f(0);      // 为f1传人0作为空指针
}                             // 解除互斥锁

void f2(std::unique_ptr<Widget> upw)
{
    MuxGuard g(f2m);          // 为f2锁定
    f(NULL);   // 为f2传人NULL作为空指针
}                             // 解除互斥锁

void f3(Widget* pw) 
{
    MuxGuard g(f3m);          // 为f3锁定
    f(nullptr);// 为f3传人nullptr作为空指针
}                             // 解除互斥锁


template<typename FuncType,
typename MuxType,
typename PtrType>
auto lockAndCall(FuncType func,
MuxType& mutex,
PtrType ptr) -> decltype(func(ptr))
{
    MuxGuard g(mutex);
    return func(ptr); 
}



int main()
{

    f(0);
    f(NULL);
    f(nullptr);
    f((void*)0);
    f((void*)NULL);
    f((void*)nullptr);

    // lockAndCall(f1, f1m, 0);     // 错误,0 传入模板类型为 int
    // lockAndCall(f2, f2m, NULL);  // 错误,NULL 传入模板类型为 long
    lockAndCall(f3, f3m, nullptr);
}