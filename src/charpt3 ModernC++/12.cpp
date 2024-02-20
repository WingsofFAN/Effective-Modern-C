#include<iostream>
#include<vector>

// 为意在改写的函数添加 override 声明

// override 改写, overload 重载 

class Base {
public:
    virtual void mf1() const{std::cout << "Base::mf1" << std::endl;};
    virtual void mf2(int x){std::cout << "Base::mf2" << std::endl;};
    virtual void mf3 () &{std::cout << "Base::mf3" << std::endl;};
    void mf4() const{std::cout << "Base::mf4" << std::endl;};
};

// 以下情况皆不是重载,但是编译器不会报错:
class Derived: public Base {
public:
    virtual void mf1(){std::cout << "Derived::mf1" << std::endl;};                      // 没有const
    virtual void mf2(unsigned int x){std::cout << "Derived::mf2" << std::endl;};        // 行参改变
    virtual void mf3 () &&{std::cout << "Derived::mf3" << std::endl;};                  // 返回右值引用
    void mf4() const{std::cout << "Derived::mf4" << std::endl;};                        // 没有virtual
} ;

//加上override关键字后,类会强制检查代码是否胡合override的规则
// class DerivedO: public Base {
// public:
//     virtual void mf1() override{std::cout << "Derived::mf1" << std::endl;};                      // 没有const
//     virtual void mf2(unsigned int x) override{std::cout << "Derived::mf2" << std::endl;};        // 行参改变
//     virtual void mf3() && override{std::cout << "Derived::mf3" << std::endl;};                  // 返回右值引用
//     void mf4() const override{std::cout << "Derived::mf4" << std::endl;};                        // 没有virtual
// } ;

class Widget {

public:
    using DataType = std::vector<double>;
    DataType& data() &{ return values; }             // 对于左值 Widgets 型别，返回左伯
    DataType data() &&{ return std::move(values); }  // 对于右值 Widgets 型别，返回右值

private:
    DataType values;

}; 


int main()
{
    Widget w;
 
    auto vals1 = w.data();
    auto vals2 = std::move(w).data();



    return 0;
}