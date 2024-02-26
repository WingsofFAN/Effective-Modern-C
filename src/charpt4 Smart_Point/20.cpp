#include <iostream>
#include <memory>

/*

std::weak_ptr来代替可能悬空的 std::shared_ptr
std::weak_ptr是std::shared_ptr的一种扩充
std::weak_ptr指涉的对象，但影响指涉对象的引用计数


std::weak_ptr可能的用武之地:
1.缓存
2.观察者列表
3.避免指针环路

*/


int main()
{
    // std::shared_ptr
    
    auto p1 = std::make_shared<int>(10);
    std::weak_ptr<int> wp(p1);

    if(!wp.expired())std::cout << "wp is unexpired" << std::endl;

    std::cout << wp.use_count() << std::endl; // 1

    std::cout << p1.use_count() << std::endl; // 1

    p1 = nullptr;    

    if(wp.expired())std::cout << "wp is expired" << std::endl;


    // 但是在多线程操作中是不安全的
    // 即在 expired() 和 真正的操作之间存在时间间隙,指针的状态可能会被改变
    // 解决此类情况有两种方法:
    // 1.使用 std::shared_ptr::lock()
    // 2 用std::weak_ptr作为实参来构造std::shared_ptr

    std::shared_ptr<int> p2 = wp.lock(); // 若wp失效,则p2为空指针
    // std::shared_ptr<int> p3(wp);         // 若wp失效,则抛出异常std::bad_weak_ptr型别的异常

    //  A --shared_ptr-->  B  <--shared_ptr-- C
    //  A --shared_ptr-->  B  <--shared_ptr-- C 
    //  个------????-------|

    //  裸指针:若A被析构,C仍然指涉到B,B将保存着指涉到A的悬空指针.
    //  std::shared_ptr: A和B相互保存着指涉到对方的shared_ptr,这种shared_ptr环路阻止了A和B的析构.
    //  std::weak_ptr:这就避免了上述两个问题.假如A被析构,那么B的回指指针将会悬空,但是B能够检测到这一点.


    return 0;
}