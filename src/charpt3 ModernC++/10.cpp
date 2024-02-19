#include<iostream>
#include<tuple>


/*优先选用限定作用域的枚举型别，而非不限作用域的枚举型别
1. 限定作用域的枚举型别，不会污染命名空间

不限作用域的枚举
enum Color {black, white, red};
auto white = false;                     // 错误,white已经被污染了

限定作用域的枚举
enum class Color { black, white, red};  // black white red 所在作用域被限定在
auto white= false;                      // 没问题令范围内并无其他 white
Color c = white;                        // 错误,范围内井无名为 white 的枚举量
Color c = Color::white;                 // 没问题
auto c = Color::white;                  // 没问题,且符合条款5

2. 限定作用域的枚举型别，可以避免隐式转换

不限范围的枚举型别:

enum Color {black ,white ,red};                            // 定义颜色
std::vector<std::size_t>  primeFactors(std::size_t x);     // 求解质因子
Color c = red;

if(c < 14. 5) {                                            // c 被隐式转换为 double 类型
    auto factors = primeFactors(c);                        // c 被用于质因子计算
} 


限范围的枚举型别:

enum class Color{black ,white ,red };                     // 不限作用域的枚举型别
Color c = Color::red;                                     // 同前，但现在要加上范围限定饰词
if (c < 14.5) {                                           // 错误，c 无法被隐式转换为 double 类型
    ...
    auto factors = primeFactors(c);                       // 错误，c 无法被隐式转换为 std::size_t 类型
    ...
}

3. 使用范围的枚举型别在使用前置声明时,可以减少编译依赖

enum class Status;                  // 前置声明
void continueProcessing(Status s);  // 取用前置声明的枚举型别

若头文件中包含了这些声明，则 Status 定义发生了修订时，就不会要求重新编译。
犹有进者，即使 Status 被修改了（例如，加了一个 audited 枚举量），但是continueProcessing 的行为未受影响
（例如，由于 continueProcessing 并未使用audited )，则 continueProcessing 实现也同样无须重新编译。

编译器在实现枚举变量时,为了节约使用内存，编译器通常会为枚举型别选用足够表示枚举扯取值的最小底层型别。
在某些情况下，编译器会用空间来换取时间，而在这样的情况下，它们可能会不选择只具备最小可容尺寸的型别，但是它们当然需要具备优化空间的能力。
这么一来，编译器就可能在枚举型别被使用前，逐个地确定其底层型别选择哪种。
此时前置声明可能就会增加编译依赖了,只要基础型别发生了改变,则整个系统都需要重新编译。此时,可以指定枚举型别的底层型别:

enum class Status; // 默认底层型别是int 如果默认型别不合你意，你可以推翻它：
enum class Status: std::uint32_t;

enum Color: std: :uint8_t;  // 不限范围的枚举型别的也可以指定底层型别
                            // 底层型别是 std::uint8_t

*/

// 4. 型别的取用,

template<typename E> // C++14
constexpr auto       // constexpr 函数为常量表达式
toUType(E enumerator) noexcept  //函数中不会发生异常,这有利于编译器对程序做更多的优化
{
    return static_cast<std::underlying_type_t<E>>(enumerator);  //std::underlying_type_t,提取取出E的基础型别,并进行强制转换   
}


int main()
{
    using Userlnfo =                // 型别别名
    std::tuple< std::string,    // 名字
                std::string,    // 邮件
                std::size_t> ;  // 年龄

    Userlnfo uInfo;                  // std::tuple 型别对象
    auto val1 = std::get<1>(uInfo);  // 取用域1的值 , 语义不够明晰

    // 使用无限制的枚举型别

    enum UserlnfoFields { uiName, uiEmail, uiReputation };
    auto val2 = std::get<uiEmail>(uInfo);                  // 语义明晰.但是不是限定范围的枚举型别


    enum class UserinfoFieldsS {uiName, uiEmail, uiReputation };
    auto val3 =std::get<static_cast<std::size_t> (UserinfoFieldsS::uiEmail)>(uInfo);   // 语义明晰.并且是限定范围的枚举型别,但太罗嗦

    auto val4 = std::get<toUType(UserinfoFieldsS::uiEmail)>(uInfo);                    // 语义明晰.并且是限定范围的枚举型别

}