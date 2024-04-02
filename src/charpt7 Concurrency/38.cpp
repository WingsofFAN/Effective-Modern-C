#include <iostream>
#include <future>
#include <thread>


// 对变化多端的线程句柄析构函数行为保持关注


class MyClass
{
public:
    MyClass()
    {
        std::cout << "MyClass()" << std::endl;
    }
    ~MyClass()    //可能在析构函数中发生阻塞
    {
        std::cout << "~MyClass()" << std::endl;
    }

private:
    std::shared_future<int> p;
};
int calcValue(){return 1;}

int main()
{

    std::packaged_task<int()> task(calcValue);    // 给calcValue()加上一个包装,使得他可以被异步执行
    std::future<int> f = task.get_future();       // 获取task的期望值
    // 已知期值对象没有指涉std::async产生的共享状态,所以为常规的行为

    // std::cout << f.get() << std::endl;
    std::thread t(std::move(task));

    // 未对t实施任何操作。在这种情况下，t在作用域结束点是可联结的，而这将导致程序终止（参见条款 37)
    

    // 针对 t 实施了join。在此情况下，fut 无须在析构函数中阻塞，因为在调用的代码已经有过 join
#if 1 
    t.detach();
#else
    // 针对 t 实施了detach。在此情况下，fut 无须在析构函数中实施detach，因为在调用的代码已经做过这件事
    t.join();
#endif
    std::cout << " finished " << std::endl;
    return 0;
}