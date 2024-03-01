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


    return 0;
}