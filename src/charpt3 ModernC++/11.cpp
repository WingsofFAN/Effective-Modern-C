#include <iostream>

/*
优先选用删除函数，而非 private 未定义函数

1.删除函数可以在类内和类外定义，而 private 未定义函数只能在类内定义

2.如果是类内部函数模板时,由于模板特化是必须写在名字空间作用域而非类作用域, 所以private的方式会失效

class Widget {
public:
    template<typename T>
    void processPointer(T* ptr)
    {... }
private:
    template<>                           // 错误, 在外部仍然可以用 void* 调用模板
    void processPointer<void>(void*);
}



使用删除函数
class Widget {
public:
    template<typename T>
    void processPointer(T* ptr)
    {... }
    ...
}

template<>
void Widget::processPointer<void>(void*) = delete;  // 仍然具备 public 访问层级但陂删除了

*/


bool islucky(int number)
{
    return number % 3 == 0 || number % 5 == 0;
}

bool islucky(char number) = delete;    // 无意义
bool islucky(bool number) = delete;    // 无意义
bool islucky(double number) = delete;  // 无意义




template<typename T>
void processPointer(T* ptr){} 

template<>
void processPointer<void>(void*) = delete;  // 不许传入空指针
template<>
void processPointer<char>(char*) = delete;  // 不许传入字符指针

int main()
{

    islucky(123);
    // islucky(123.456);     // 编译错误      
    // islucky(true);        // 编译错误
    // islucky('a');         // 编译错误

    int num = 100;
    processPointer(&num);
    // processPointer(nullptr);  // 编译错误
    // processPointer("hello");  // 编译错误

    return 0;
}