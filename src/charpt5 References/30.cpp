#include <iostream>
#include <vector>
#include <typeinfo>
#include <boost/type_index.hpp>

/*

完美转发的失败情形:
1. 打括号出初始物
2. 0和NULL用作空指针
3. 仅有声明的整型 static const 成员变量
4. 重载的函数名字和模板名字
5. 位域
位域: 是由机器字的若干任意部分组成的（例如， 32位int 的第 3到第 5个比特),但是这样的实体是不可能有
办法对其直接取址的。我前面曾经提及，在硬件层次，引用和指针本是同 事物。这
来，既然没有办法创建指涉到任意比特的指针 (C++硬性规定，可以指涉的最小
实体是单个 char) ，那自然也就没有办法把引用绑定到任意比特了。
要将完美转发位域的不可能化为可能，也简单不过。 旦你意识到接受位域实参的任
何函数都实际上只会收到位域值的副本。毕竟，没有函数可以把位域绑定到引用，也
不可能有函数接受指涉到位域的指针，因为根本不存在指涉到位域的指针。可以传递
位域的仅有的形参种类就只有按值传递，以及，有点匪夷所思的常县引用 (reference-to-const).
在按值传递行参的这种情况下,被调用的函数显然收到的是位域内的副本;
而在常量引用形参下,标准要求这时引用实际绑定到存储在某种标准整型的位域副本上。
*/

template<typename T>
void f(T&& param)
{
}

template<typename... Ts>
void f(Ts&&... param)
{
}


template<typename T>
void fwd(T&& param)            //接受任意实参
{
    using std::cout; 
    using boost::typeindex::type_id_with_cvr; 
    
    cout <<  "T = " << type_id_with_cvr<T>().pretty_name()  << "\n"; // 显示 T 的型别
    cout << "params = " <<  type_id_with_cvr<decltype(param)>().pretty_name() << '\n';
    f(std::forward<T>(param)); //转发该实参到f
}

template<typename... Ts>
void fwd(Ts&&... params)
{
    f(std::forward<Ts>(params)...); //转发所有实参到f
}

class Widget
{
public:
 /*
    有这么一个普适的规定: 不需要给出类中的整型static,const成员变量的定义,仅需要声明它即可.
*/

    static const std::size_t MinVals = 18;
};

void fp2(std::size_t val){}; 
void fp3(int (*pf)(int)){};


int processVal(int value){};
int processVal(int value, int priority){}; 

void fp(const std::vector<int>& v){}; 
int main()
{
    fp({1,2,3});
    // f({1,2,3});        //编译错误
    // fwd({1,2,3});      //编译错误
    //原因: 编译器在对{1,2,3}进行推导时, 由于模板的存在,编译器不会对推导出的类型做限定,而在转发时才发现与f的实现不匹配
    // 1.编译器无法为一个或多个fwd的行参推导出型别
    // 2.编译器为一个或多个fwd的推导出错误的型别
    std::vector<int> v = {1,2,3};

    fp(v);     //正确
    f(v);      //正确
    fwd(v);    //正确


    fwd(NULL);  //推导为long
    fwd(0);     //推导为int

    fp2(Widget::MinVals);      //没有问题
    // fwd(Widget::MinVals);      //无法编译
   

    fp3(processVal);    //正确
    // fwd(processVal);    //错误  
    // 因为模板没有关于型别要求,因此编译器无法推导出该传参给哪个processVal的重载版本



    return 0;
}