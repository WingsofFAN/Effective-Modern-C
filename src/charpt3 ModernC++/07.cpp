#include<iostream>
#include<vector>

class Widget
{
public:
    Widget()
    {
        std::cout << "无参构造函数" << std::endl;
    }

    Widget(int x_, double y_, bool z_)
    {
        std::cout << "int,double,bool 构造函数" << std::endl;
    }

    Widget(int x_, bool z_, double y_)
    {
        std::cout << "int,bool,double 构造函数" << std::endl;
    }

    Widget(int x_, std::string z_, double y_)
    {
        std::cout << "int, std::string, double 构造函数" << std::endl;
    }

    Widget(std::initializer_list<int> il)
    {
        std::cout << "std::initializer_list<int> il" << std::endl;
    }

};




int main()
{
    Widget x;
    Widget y(1,true,2.0F);
    Widget z{1,false,2};        // 实际上是 false 被隐式转换为 int ，然后调用了std::initializer_list<int>
    Widget j = {1,false,2};     // 实际调用结果同上
    Widget w(1,2.0F,true);
    Widget v(1,std::string("hello"),2);
    Widget u{1,std::string("hello"),2};  // 使用 {} 实在无法调用 std::initializer_list<int> 之后 ，然后迫不得已调用了类型相匹配的构造函数
    // Widget k{5.0,5.0,5.0};               // 编译不通过，{}禁止窄化数据类型

    //特殊的vector

    std::vector<int> v1(10, 20); //调用了形参中没有任何一个具备std::initializer list 刑别的构造函数，结果是：创建了个含有10个元素的std::vector所有的兀素的值都是 20
    std::vector<int> v2{10, 20}; //调用了形参中含有std: :initializer_list 型别的构造由数，结果是：创建了个含有2个元素的std::vector元素的值分别为 10 20

    std::cout << "v1:" << "\n";
    for(auto& p : v1) std::cout << p <<" ";

    std::cout << "\nv2:" << "\n";
    for(auto& p : v2) std::cout << p <<" ";


    return 0;
}