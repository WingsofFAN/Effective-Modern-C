#include<iostream>

// 只要函数不会发射异常，就为其加上 noexcept 声明

/*
int f(int x) throw();    // 不会发射异常： c++98 风格 
int f(int x) noexcept;    // 不会发射异常： c++11 风格

c++98: 调用栈会开解至f的调用方,然后执行了一些与本条款无关的动作以后,程序执行终止. 
c++11: 程序执行中止之前,只是可能会开解

抛出异常时，将暂停当前函数的执行，开始查找匹配的 catch 子句。
首先检查 throw 本身是否在 try 块内部，如果是，检查与该 try 相关的 catch 子句，看是否可以处理该异常。
如果不能处理，就退出当前函数，并且释放当前函数的内存并销毁局部对象，继续到上层的调用函数中查找，直到找到一个可以处理该异常的catch。
这个过程称为栈展开(stack unwinding)。当处理该异常的 catch 结束之后，紧接着该 catch 之后的点继续执行.



c++11: 内存释放函数和所有的析够函数都隐式地具备noexcept性质.
*/

void setup(){std::cout << "setup\n";};
void cleanup(){std::cout << "cleanup\n";};

// 由于有着确实的理由使得带有noexcept声明的函数依赖于缺乏noexcept保证的代码,c++允许此类代码通过编译,并且编译器通常不会发出警告.
void f() noexcept
{
    setup();
    try {
        throw std::runtime_error("error");
    } catch (...) {
        cleanup();
    }
}


void doWork () noexcept
{
    setup();                                      // 建立要做的工作
    
    std::cout << "doWork\n";                      // 完成要做的工作
    
    cleanup();                                    // 执行清理工作
}

int main()
{
    doWork();
    return 0; 
}