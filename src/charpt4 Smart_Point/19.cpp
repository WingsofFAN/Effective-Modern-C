#include <iostream>
#include <memory>

/*
1.std::shared_ptr 的尺寸是裸指针的两倍，因为内部维护了引用计数器，所以会占用额外的内存空间。

2.引用计数器的实现方式是，使用一个 std::atomic<int> 来实现，也保证了线程安全。
所以 std::shared_ptr 的大小是 sizeof(std::atomic<int>) + sizeof(T)

3.引用计数器的内存必须动态分配.

std::shared_ptr<T>

指涉到T型别的对象的指针 ---> T型别的对象
指涉到控制块的指针     --->  控制块
                    1.引用计数
                    2.弱计数
                    3.其他数据(自定义删除器,分配器等)

1.std::make_shared() 总是创建一个控制块.
2.从具备专属所有权的指针(即 std::unique_ptr 或 std::shared_ptr 指针)出发构造一个std::shared_ptr时，会先创建一个控制块,
3.当std::shared_ptr 构造函数使用裸指针作为实参来调用时,它会创建一个控制块.

为了避免过多的创造控制块

*/


class Widget {
public:
    Widget() { std::cout << "Widget(" << this << ")" << std::endl; }
    ~Widget() { std::cout << "~Widget(" << this << ")" << std::endl; }
};

void makeLogentry(Widget *pw) { std::cout << "Log entry for " << pw << "." << std::endl; }

auto loggingDel = [](Widget *pw)        // custom deleter
                  {                     // (as in Item 19)
                    makeLogentry(pw);
                    delete pw;
                  };

int main()
{
    std::shared_ptr<int> p1 =  std::make_shared<int>(42);
    std::shared_ptr<int> p2 =  p1;
    
    std::cout << "p1: " << p1.use_count() << std::endl;
    std::cout << "p2: " << p2.use_count() << std::endl;
    std::cout << "sizeof(p1) : "   <<    sizeof(p1)  << std::endl;    // shared_pt 是普通指针的两倍
    std::cout << "sizeof(void) : " <<    sizeof(void*)  << std::endl; // 


    // 问题代码:pw创建了两个控制块,会导致在管理内存时出错
    // Widget* pw = new Widget;
    // std::shared_ptr<Widget> p3(pw,loggingDel);
    // std::shared_ptr<Widget> p4(pw,loggingDel);
    // std::cout << "p4.use_count: " << p4.use_count() << std::endl;
    

    //正确的创建方法为
    // 1. 直接在创建时,使用new直接创建,避免一个指针有多个控制块,从书写上避免此中错误
    std::shared_ptr<Widget> p3(new Widget,loggingDel);
    std::shared_ptr<Widget> p4(new Widget,loggingDel);
    std::cout << "p3.use_count: " << p3.use_count() << std::endl;
    std::cout << "p4.use_count: " << p4.use_count() << std::endl;


    // 2. 使用std::make_shared()创建,避免一个指针有多个控制块,从书写上避免此中错误
    // 弊端无法使用自定义析构器
    Widget w ;

    std::shared_ptr<Widget> p5 = std::make_shared<Widget>(w);  
    std::shared_ptr<Widget> p6 = std::make_shared<Widget>(w);  // 还是会有两个控制块
    std::shared_ptr<Widget> p7(p6) ;


    std::cout << "p5.use_count: " << p5.use_count() << std::endl;
    std::cout << "p6.use_count: " << p6.use_count() << std::endl;
    std::cout << "p7.use_count: " << p7.use_count() << std::endl;

    // 3.为了弥补2中的不足,希望在定义Widget时,可以将this指针设置为智能指针,
    // 即使用 基类模板 std::enable_shared_from_this<T> 来实现

    // class Widget2 : public std::enable_shared_from_this<Widget2> {
    // public:
    //     Widget2() { std::cout << "Widget2(" << this << ")" << std::endl; }
    //     ~Widget2() { std::cout << "~Widget2(" << this << ")" << std::endl; }
    // };
    //为了避免用户在std::shared_ptr指涉到该对象前就调用了引发shared_ptr的成员函数,
    //继承自std::enable_shared_from_this的类通常会将其构造函数声明为private访问层级,
    //并且只允许用户通过调用返回std::shared_ptr的工厂函数来创建对象.
    /*class Widget: public std::enable_shared_from_this<Widget> {
        public:
        // 将实参完美转发给 private 构造函数的工厂函数
        template<typename... Ts>
        static std::shared_ptr<Widget> create(Ts&&... params);
        ...
        void process();   //同前
        ...
        private:
        ...               //构造由数
        };
    */


    return 0;   
}