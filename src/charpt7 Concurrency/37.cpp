#include <iostream>
#include <thread>
#include <vector>

// std::thread 型别对象在所有路径皆不可联结
/*

联接状态: 是否能通过join()和detach()等操作来处理线程,
通常我们可以使用joinable方法来检查std::thread对象是否可联结状态.

不可联接的状态:
1.默认构造函数的std::thread.此类std::thread对象没有可以执行的函数,因此也没有对应的底层执行线程
2.std::thread对象被std::move()转移,则原来的std::thread对象变为不可联结状态.
3.std::thread已经被联接,std::thread型别对象不再对应至已结束运行的底层执行线程.
4.std::thread已经被分离,分离会将std::thread型别对象与对应的底层执行线程的链接断开.

可见,线程一创建几乎就是不可联接的状态,其中的原因是如果可以联接,那么线程内执行状态会影响主线程.
进而难以对线程对象进行正常的析构,因为无法保证线程内执行状态的是可控的
所以规定可联接的线程的析构函数会导致程序终止.

这样一来,我们在操作线程时得确保,离开作用域时线程是不可链接的,但是离开一个作用域的出口很多,return,break,goto等.
此处,我们习惯采用 “Resource Acquisition Is Initialization" RAII模式来管理线程资源.
*/

class ThreadRAII{

public:
    enum class DtorAction { join, detach};
    ThreadRAII(std::thread&& t, DtorAction a) 
    : action(a), t(std::move(t)) {
        std::cout << "ThreadRAII()" << std::endl;
    };

    ~ThreadRAII()
    {
        if(t.joinable()) {
            if(action == DtorAction::join) {
                t.join();
            } 
            else 
            {
                t.detach(); 
            }
        }

        std::cout << "~ThreadRAII()" << std::endl;
    }
 
    ThreadRAII(ThreadRAII&&) = default; 
    ThreadRAII& operator=(ThreadRAII&&) = default; //移动操作
    std::thread& get() { return t; } //同前

private:
    DtorAction action;
    std::thread t;      //在成员列表的最后声明 std::thread 型别对象
};



bool is_prime(int n)
{
    if (n <= 1)
        return false;
    for (int i = 2; i < n; ++i)
        if (n % i == 0)
            return false;
    return true;
}


int main()
{
    auto filter = is_prime;
    int maxVal = 100;
    std::vector<int> ans;
    ThreadRAII t(
            std::thread([&filter,maxVal,&ans]
                {
                    for(int i = 2; i < maxVal; ++i)
                    {if (filter(i))ans.push_back(i);}
                }
            ),
            ThreadRAII::DtorAction::join
        );
    
    std::cout << "main thread is running" << std::endl;
    t.get().join();

    for(auto p:ans)std::cout <<  p  << std::endl;

    return 0;
}