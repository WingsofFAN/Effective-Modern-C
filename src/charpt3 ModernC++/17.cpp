#include <iostream>

/*
Rule of Three:如果你声明了复制构造函数、赋值运算符或者析构函数的任何一个，那么你必须声明所有三个函数。

推论：
1.在一种复制操作中进行的任何资源管理,也极有可能在另一种复制操作中进行。
2.该类的析够函数也会参与到该资源的管理中(通常为释放资源)。

实际上,没有被严格遵循:
即使用户声明了析构函数,也不会影响编译器生成复制操作的意愿.

在c++11中,简化为只要用户没有声明任何析构函数,复制操作,移动操作,编译器才会生成默认移动操作.

不同编译器具体实现可能不同.具体情况具体分析,但是最好是在定义了其中一个后,若其他操作不具体实现,那么最好将其显示声明出来
*/






class Base1{
public:
    void fuc()
    {
        std::cout<<"Base1::fuc():" << i <<std::endl;
        std::cout << &(this->i) << std::endl;
    }
    Base1(int i):
        i{i}
        {
            std::cout<<"Base1::Base1()"<<std::endl;
        }
    Base1(const Base1&) = default;
    Base1(Base1&&) = default;

    int i{};
};


class Base2{
public:
    Base2(int i):
        i{i}
        {
            std::cout<<"Base2::Base1()"<<std::endl;
        }

    Base2(const Base2& b2)
        {
            std::cout<<"Base2::Base2(const Base2& b2)"<<std::endl;
        }


    Base2(Base2&& b2)
        {
            std::cout<<"Base2::Base2(Base2&& b2)"<<std::endl;
        }

    ~Base2()
        {
            std::cout << "Base2::~Base2()"<<std::endl;
        }

    
    void fuc()
    {
        std::cout<<"Base2::fuc():" << i <<std::endl;
        std::cout << &(this->i) << std::endl;
    }
    int i{};

    
};



int main(){
    Base1 b1(8);
    Base1 b3(std::move(b1));
    b1.i += 3;
    b1.fuc();
    b3.fuc();


    Base2 b4(18);
    Base2 b6(std::move(b4));
    b4.fuc();
    b6.fuc();    
}