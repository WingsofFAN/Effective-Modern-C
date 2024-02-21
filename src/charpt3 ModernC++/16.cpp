#include <iostream>
#include <mutex>
#include <thread>
#include <atomic>
#include <unistd.h>
#include <cstdlib>
#include <chrono>
// 保证 const 成员函数的线程安全性


// 计算多项式
/* 互斥量
class Polynomial {
public:
    using RootsType = std::vector<double>;
    RootsType roots() const
    {
        std::lock_guard<std::mutex> g(m);  //加上互斥量
        if (!rootsAreValid)                //若缓存无效则计算／存储 roots
        { 
            ...
            rootsAreValid = true;
        }

        return rootVals;
    }

private:
    mutable std::mutex m;          //互斥量,设为 mutable, 是因为其在 const 函数中被使用,而又需要被修改
    mutable bool rootsAreValid{ false};
    mutable RootsType rootVals{}; 

};


原子操作:

class Point {                              // 表示 2D
public:
    double distanceFrornOrigin() const noexcept
    {                                     // noexcept 的信息参见条款 14
        ++callCount;                      // 带原子性的自增操作
        return std::sqrt((x * x) + (y * y));
    }
private:
    mutable std::atomic<unsigned> callCount{ 0 };
    double x, y; 
};

*/


//  原子操作是否能替代互斥量:

class Widget {
public:
    int magicValue() const
    {
        if (cacheValid) return cachedValue;
        else {
            auto vall = expensiveComputation1();
            auto val2 = expensiveComputation2();
            sleep(std::rand() % 10);
            cachedValue = vall + val2;
            cacheValid = true;
            std::cout << __LINE__ << " magicValue: " << cachedValue << std::endl;
            return cachedValue;
        } 
    }
    /* 隐患:
    1.一个线程调用 Widget::magicValue 时，观察到 cacheValid 值为 false, 于是执行了两个大开销的计算，并将其和赋值给了 cacheValue
    2.与此同时，另一个线程也在调用 Widget::magicValue, 也看到了 cacheValid 值为 false, 于是执行了第一个线程个哪敢完成的两个大开销的计算
    */




    int magicValue2() const
    {
        if (cacheValid) return cachedValue;
        else {
            auto vall = expensiveComputation1();
            auto val2 = expensiveComputation2();
            sleep(std::rand() % 10);
            cacheValid = true;
            std::cout << __LINE__ <<"  magicValue2: " << vall + val2 << std::endl;
            return vall + val2;
        } 
    }

    /* 隐患:
    1. 一个线程调用 Widget::magicValue 并执行到了 cacheValid 值被置为 true 的时刻
    2. 在这一时刻，另一个线程在调用 Widget::magicValue 并检视 cacheValid 的值观察到其值为 true 后，
    该线程就把 cacheValid 的值给返回了，即使此时第一个线程还没有执行对 cacheValid 的赋值。因此，返回值是不正确的。
    */



/* 正确写法：
    1. 对于单个要求同步的变量或内存区域，使用 std::atomic足够了。
    2. 但是如果有两个或更多个变量或内存区域需要作为一整个单位进行操作时，就要动用互斥量了。

    mutable std::mutex m;                  // 用互斥量来保证线程安全。
    mutable int cachedValue;
    mutable bool cacheValid{ false};
*/

private:
    mutable std::atomic<bool> cacheValid{false} ;   
    mutable std::atomic<int> cachedValue;           

    int expensiveComputation1() const
    {
        std::cout << "expensiveComputation1" << std::endl; 
        return 1;
    }

    int expensiveComputation2() const
    {
        std::cout << "expensiveComputation2" << std::endl; 
        return 2;
    }
};


int main()
{
    Widget w1;
    Widget w2;


    std::thread t1([&w1](){w1.magicValue();});
    std::thread t2([&w2](){w2.magicValue();});
    std::thread t1p([&w1](){w1.magicValue();});
    std::thread t2p([&w2](){w2.magicValue();});
    
    t1.detach();t2.detach();t1p.detach();t2p.detach();
    



    std::thread t3([&w1](){w1.magicValue2();});
    std::thread t4([&w2](){w2.magicValue2();});
    t3.detach();t4.detach();

    sleep(10);

    return 0;
}

