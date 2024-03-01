#include<iostream>
#include<string>
#include<memory>

struct someData
{
    /* data */
};


class A
{
public:
    A(A&& rhs)                    //rhs 是个右值引用
    :name(std::move(rhs.name)),   //移动
     data(std::move(rhs.data))    //移动
    {
    }

    A(std::string name_,someData data_)
    :name(name_)
    {
        data = std::make_shared<someData>(data_);
    }

    void printName()
    {
        std::cout << name << std::endl;
    }

    template<typename T>
    void setName(T&& newName)                  //万能引用
    { name= std::forward<T>(newName); }        //有条件转换,为左值
    

private:
    std::string name;
    std::shared_ptr<someData> data;
};

class B
{
public:
    B(B&& rhs)                    //rhs 是个右值引用
    :name(std::move(rhs.name)),   //移动
     data(std::move(rhs.data))    //移动
    {
    }

    B(std::string name_,someData data_)
    :name(name_)
    {data = std::make_shared<someData>(data_);}
    
    template<typename T>
    void setName(T&& newName)                 //万能引用
    { name= std::move<T>(newName); }          //无条件转换,为右值

    void printName()
    { std::cout << name << std::endl; }

private:
    std::string name;
    std::shared_ptr<someData> data;
};

class C
{
public:
    C(C&& rhs)                    //rhs 是个右值引用
    :name(std::move(rhs.name)),   //移动
     data(std::move(rhs.data))    //移动
    {}

    C(std::string name_,someData data_)
    :name(name_)
    {data = std::make_shared<someData>(data_);}
    
    void setName(const std::string& newName)   
    {name= newName;}                           //从常量左值取得赋值

    void setName(std::string&& newName)     
    {name= std::move(newName); }               //从右值取得赋值

    void printName()
    { std::cout << name << std::endl; }

private:
    std::string name;
    std::shared_ptr<someData> data;
};

/*
c++ 自身有返回值优化,return value optimization RVO

Widget makeWidget()
{
    Widget w;
    return w;
}

手动优化
Widget makeWidget()
{
    Widget w; ...
    return std::move(w);  // w会作为右值处理,原来是复制省略却没有实施
}

与一以下代码效果相同:

Widget makeWidget()
{
    Widget w; ...
    return w;
}

事实上:针对函数中按值返回的局部对象实施std::move的操作,不能给编译器帮上忙
(如果不执行复制省略,就必须将局部对象作为右值处理,效果一样),却可以帮倒忙(可能会排除掉RVO的实施机会)

*/


int main()
{
    someData adata;
    std::string Name1 = "Name1";

    A a(Name1, adata);
    a.printName();

    A b(std::move(a));
    a.printName() ;      //移动后，a.name为空   
    b.printName() ;
    

    B c("name2", adata);

    std::string Name2 = "Name2";

    b.setName(Name1);                    //
    b.printName();                       //
    std::cout << Name1 << std::endl;     //局部变量不会消失


    c.setName(Name2);                    //局部变量消失
    c.printName();                       //

    std::cout << Name2 << std::endl;     //局部变量会消失

    std::string Name3 = "Name3";         //
    C d("name3", adata);                 //
    d.setName(Name3);                    //
    d.printName();
    d.setName("name4");                  //
    d.printName();







    return 0;
}