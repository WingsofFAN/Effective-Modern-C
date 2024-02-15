#include<iostream>
#include<vector>
#include<functional>
#include <memory>

/*
template<typename It> // dwim （做我所想， do what I mean) 钉法
void dwim(It b, It e) // 应用范围是从b 到 e 的所有元素
{ 
    while (b != e) { 
        typename std::iterator_traits<lt>::value_type 
        currValue = *b; 
    }
}
*/

// 1.可以替换掉啰嗦的定义
template<typename It> // dwim （做我所想， do what I mean) 钉法
void dwim(It b, It e) // 应用范围是从b 到 e 的所有元素
{ 
    while (b != e) { 
        auto currValue = *b; 
    }
}

struct Widget
{
    /* data */
    int x,y;
    bool operator<(const Widget& p1)
    {
        return this->x < p1.x;
    }    
};


int main()
{
// 2. 规避掉定义时的可能出现的未定行为

    int X1;      // 有潜在的未初始化风险
    // auto x2;     // 编译错误！必须有初始化物
    auto x3 = 0; //没问题， x的值有合式定义

// 3. 在lambda表达式，函数对象使用时，方便闭包
    auto derefless = [](const auto& pl, const auto& p2) { return *pl < *p2; }; 
    // 就意味着，在 C++ll 中，不用 auto 也可以声明 derefUPLess 如下：
    // std::function<bool(const std::unique_ptr<Widget>&, const std::unique_ptr<Widget>&)>  c++11
    auto derefUPLess = [](const std::unique_ptr<Widget>& pl, const std::unique_ptr<Widget>& p2) 
    { return *pl < *p2; } ;

    return 0;
}