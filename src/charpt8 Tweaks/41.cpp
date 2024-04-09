#include <iostream>
#include <thread>
#include <vector>
#include <string>

class Wedight
{
public:
    Wedight(std::string name)     // 按值传递
    {
        names.push_back(name);
        std::cout << "Constructor called" << std::endl;
    }

    // // 基于重载方式的实现,需要维护两段代码,十分麻烦
    // void addName( const std::string& newName )
    // {
    //     names.push_back(newName);
    // }

    // void addName( const std::string&& newName )
    // {
    //     names.push_back(std::move(newName));
    // }

    // // 基于万能模板实现
    // template <typename T>
    // void addName( T&& newName )
    // {
    //     names.push_back(std::forward<T>(newName));
    // }

    // 按值传递
    void addName( std::string newName )
    {
        names.push_back(std::move(newName));
    }

    ~Wedight()
    {
        std::cout << "Destructor called" << std::endl;
    }

private:
    std::vector<std::string> names;

};

/*
三种方式代价对比:
1.重载: 对于左值是一次复制,对于右值是一次移动
2.万能引用：对于左值是一次复制,对于右值是一次移动,甚至更少
3.按值传递：对于左值是一次复制和一次移动,对于右值是两次移

然而对可以复制的形参,在移动成本低并且一定会被复制的前提下,考虑将其按值传递:
1.只用考虑按值传递的情况,只需要写一个函数
2.对于可以复制的形参,才考虑按值传递,减少不必要的移动
3.按值传递仅在形参移动成本低廉的前提下,才值得考虑.
4.移动可以避免一定程度上的内存切片


*/

int main()
{
    Wedight w("test");
    w.addName("name1");
    return 0;
}   