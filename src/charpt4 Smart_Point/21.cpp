#include <iostream>
#include <memory>

/*
优先选用std::make_unique和std::make_shared，而非直接使用new:



*/

class Widget
{
public:
    Widget()
    {
        std::cout << "Widget():" << this << std::endl;
    };
    ~Widget()
    {
        std::cout << "~Widget()" << this << std::endl;
    };

};

/*
make_unique() 只是进行了一次完美的转发

template<typename T, typename... Ts>
std: :unique_ptr<T> make_unique(Ts&&... params)
return std::unique_ptr<T>(new T(std::forward<Ts>(params)...)); 

*/




int main()
{
    // 效率问题: 
    // 1. 通过new创建的对象，需要写两遍型别名，而make只需要写一次
    // 2. 通过new创建的对象，会引发两次内存分配:1)一次为new构造对象时,2)一次为shared_ptr构造控制块时。
    //    而通过make_unique创建的对象时，对象和构造块合并在一起只会进行一次内存分配。 
    
    auto upw1(std::make_unique<Widget>());
    std::unique_ptr<Widget> upw2(new Widget());  //

    auto spw1(std::make_shared<Widget>());
    std::shared_ptr<Widget> spw2(new Widget());  //

    // 异常安全问题:
    // 2. 通过new创建的对象，如果new抛出异常，那么对象将无法被释放

    /*
    
    processWidget(std::shared_ptr<Widget>(new Widget),computePriority());  // 存在潜在的内存泄漏风险
    
    1. 实施 "new Widget"
    2. 执行 computePriority
    3. 运行 std::shared_ptr 构造函数。

    如果在第二步发生异常，那么在第三步，std::shared_ptr构造函数将无法执行，从而导致内存泄漏。
    
    processWidget (std::make_shared<Widget>(),computePriority());           // 不会发生潜在的内存泄漏风险
    
    */

    // 弊端: 1.使用make无法传入自定义的析构函数,解决方式见19
    //      2.内存紧张的系统,非常大的对象,以及存在比指涉到相同对象的std::shared_ptr生存期更久的std::weak_ptr
    /*
    
    class ReallyBigType { ·· } ;
    auto pBigObj = std::make_shared<ReallyBigType> (); 

    创建指涉到大对象的多个 std::shared_ptr和std::weak_ptr
    并使用这些智能指针来操作该对象
    最后一个指涉到该对象的 std::shared_ptr 在此被析构，
    但指涉到该对象的若干 std::weak_ptr 仍然存在
    
    在此阶段，前述大对象所占用的内存仍处干分配未回收状态    // 泄漏风险
    
    最后一个指涉到该对象的 std::weak_ptr 在此被析构，
    控制块和对象所占用的同一内存块在此被释放
    
    class ReallyBigType {... } ; /／同前
    std::shared_ptr<ReallyBigType> pBigObj(new ReallyBigType);
    //通过 new 及达式创建颇大的对象
    //同前，创建指涉到大对象的
    
    //创建多个 std::shared_ptr和std::weak_ptr,并使用这些智能指针来操作该对象

    //最后－个指涉到该对象的 std::shared_ptr 在此被析构
    //但指涉到该对象的若干 std::weak_ptr 仍然存在，
    //前述大对象所占用的内存在此被回收

    //在此阶段，仅控制块所占用的内存仍处千分配未回收状态   风险消除
    
    //最后一个指涉到该对象的 std::weak_ptr 在此被析构，
    //控制块所占用的内存在此得到释放

    由于 std::weak_ptr 指涉到某个控制块（即，弱计数大于零），该控制块肯定会持续存在。
    而由于控制块存在，包含它的内存肯定会持续存在。这么一来，通过对应千std::shared_ptr 
    make 系列函数所分配的内存在最后一个 std::shared_ptr和最后一个指涉到它的std::weak_ptr都被析构之前，无法得到释放。

    void processWidget(std::shared_ptr<Widget> spw,int priority);
    void cusDel(Widget *ptr);

    下面就是那条非异常安全的调用语句，根据这次修订作了相应调整：
    processWidget(std::shared_ptr<Widget>(new Widget, cusDel),computePriority());  
    存在潜在的资源泄漏风险

    std::shared_ptr<Widget> spw(new Widget, cusDel);
    processWidget(spw,computePriority());            // 正确,但是并非最有化的写法

    processWidget(std::move(spw),computePriority()); // 既有效率,又异常安全 

    */


    return 0;
}