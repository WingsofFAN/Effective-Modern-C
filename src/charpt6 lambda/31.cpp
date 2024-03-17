#include <iostream>
#include <vector>
#include <functional>

/*
lambda表达式 是以[]引导的一种表达式

std::find_if(container.begin(), container.end(),
             [](int val){return 0<val && val<10;});   //lambda表达式

闭包: 是lambdas式创建的运行期对象,根据不同的捕获模式,闭包会持有数据的副本或引用.

闭包类就是实例化闭包的类.每个lambda式都会触发编译器生成一个独一无二的闭包类.
*/

/*

避免默认捕获模式



*/

using FilterContainer =                                                   //  关于 “using" 参见条款
       std::vector<std::function<bool(int)>>; 

template<typename T>
T* computeDivisor(T a, T b)
{
    T divisor = 0;
    if(abs(b -0) > 1e-8)
    {
        divisor = a / b;
    }    
    return &divisor;
}   

class Widget
{
public:
    void addFilter() ;
private:
    FilterContainer filters; 
    int m_divisor;
    static int s_divisor;
};

void Widget::addFilter() 
{
    // filters.emplace_back([](int value) { return value % m_divisor == 0;});            // 错误,没有m_divisor的捕获
    // filters.emplace_back([m_divisor](int value) { return value % m_divisor == 0;});   // 错误,局部变量没有可捕获的m_divisor
    filters.emplace_back([=](int value) { return value % m_divisor == 0;});              // 正确,实际上是捕获到this指针,进而捕获到this->m_divisor
}

/*
void Widget::addFilter() const
{
    auto divisor = m_divisor;
    filters.emplace_back([divisor](int value) { return value % divisor == 0;});           // 正确,将成员变量变为局部变量进行捕获
}

void Widget::addFilter() const
{
    filters.emplace_back([=](int value) { return value % s_divisor == 0;});               // 正确,但是实际没有捕获任何东西,因为s_divisor直接指射到静态变量
}
*/

int main()
{
    int calc1 = 1;
    int calc2 = 2;
    auto divisor = computeDivisor(calc1, calc2); 

    FilterContainer filters;
    filters.emplace_back([&](int value) { return value % *divisor == 0; });   
    // 以引用的方式默认捕获,危险,对divisor的指射为空
    filters.emplace_back([&divisor](int value) { return value % *divisor== 0;});
    // 以引用的方式显示捕获,危险,对divisor的指射为空,但可以明确lambda表达式依赖divisor
    filters.emplace_back([=](int value) { return value % *divisor == 0;});
    // 以拷贝的方式默认捕获,安全,divisor不会悬空
    filters.emplace_back([divisor](int value) { return value % *divisor == 0;});
    // 以拷贝的方式默认捕获,安全,divisor不会悬空,且可以明确lambda表达式依赖divisor

    return 0;

}

