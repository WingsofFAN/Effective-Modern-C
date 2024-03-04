#include<iostream>
#include<set>
#include<chrono>

/*
避免依赖万能引用型别进行重载

*/


//基础实现,效率稍差
std::multiset<std::string> names;

void logAndAdd(const std::string& name)
{
    auto now = std::chrono::system_clock::now();
    names.emplace(name);
}

//万能引用
template<typename T>
void logAndAdd1(T&& name)
{
    auto now = std::chrono::system_clock::now();
    names.emplace(std::forward<T>(name));
}

std::string nameFromIdx(int idx)
{
    return "name_" + std::to_string(idx);
}

void logAndAdd1(int idx)
{
    auto now = std::chrono::system_clock::now();
    names.emplace(nameFromIdx(idx));
}



int main()
{
    std::string petName("Darla");

    logAndAdd(petName);                           //传递左值std::string
    logAndAdd(std::string("Persephone"));         //传递右值std::string
    logAndAdd("Dolly");                           //传递字符串字面常量


    for(auto p: names) std::cout << p << " ";
    std::cout << std::endl;

    logAndAdd1(petName);                          //传递左值std::string
    logAndAdd1(std::string("Persephone"));        //对右值实施移动而非复制
    logAndAdd1("Dolly");                          //在multiset中直接构造一个std::string对象

    logAndAdd1(2);                                //正确,调用重载

    short id = 22;
    // logAndAdd1(id);                               //c错误,调用万能引用


    //所以在使用万能引用时,应该避免使用重载,否则会难以分清调用的方式

    for(auto p: names) std::cout << p << " ";
    std::cout << std::endl;
}