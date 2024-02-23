#include<iostream>
#include<memory>


/*
std::unique_ptr:
1. 足够快,足够小
2. 不允许复制,复制时源指针会被释放
3. 可以使用自定义的删除器

对托管资源实施专属所有权语义

*/

class Investment {
public:

                                // essential
  virtual ~Investment() {}      // design
                                // component
  
};

class Stock:
  public Investment { };

class Bond:
  public Investment { };

class RealEstate:
  public Investment { };


bool needStock = true;
bool needBond = false;
bool needRealEstate = false;

//在外部定义一个删除器
/*auto delInvmt = [](Investment* pInvestment)   // custom 
                {                             // deleter
                  makeLogEntry(pInvestment);  // (a lambda
                  delete pInvestment;         // expression)
                };

Variant 1
template<typename... Ts>          // return std::unique_ptr
std::unique_ptr<Investment>       // to an object created
 makeInvestment(Ts&&... args);   // from the given args

Variant 2
template<typename... Ts>                         // revised
std::unique_ptr<Investment, decltype(delInvmt)>  // return type
makeInvestment(Ts&&... args)
{
    std::unique_ptr<Investment, decltype(delInvmt)>  // ptr to be
        pInv(nullptr, delInvmt);                       // returned

    if ( needStock )
    {
        pInv.reset(new Stock(std::forward<Ts>(args)...));
    }
    else if ( needBond )
    {
        pInv.reset(new Bond(std::forward<Ts>(args)...));
    }
    else if ( needRealEstate )
    {
        pInv.reset(new RealEstate(std::forward<Ts>(args)...));
    }

    return pInv;
}*/

void makeLogEntry(Investment* pInvestment)
{
    std::cout << "makeLogEntry()" << std::endl;
}

template<typename... Ts>
auto makeInvestment(Ts&&... args)                  // C++14
{

    //自定义删除器
    auto delInvmt = [](Investment* pInvestment)    // this is now
                    {                              // inside
                        makeLogEntry(pInvestment);  // make-
                        delete pInvestment;         // Investment
                    };

    std::unique_ptr<Investment, decltype(delInvmt)>  // as
        pInv(nullptr, delInvmt);                       // before

    if ( needStock )            // as before
    {
        pInv.reset(new Stock(std::forward<Ts>(args)...));
    }
    else if ( needBond )         // as before
    {
        pInv.reset(new Bond(std::forward<Ts>(args)...));
    }
    else if ( needRealEstate )  // as before
    {
        pInv.reset(new RealEstate(std::forward<Ts>(args)...));
    }

    return pInv;                                             // as before
}



int main()
{

    // ...

    auto pInvestment =                  // pInvestment is of type
    makeInvestment( /* arguments */ );  // std::unique_ptr<Investment>

    std::cout << "pInvestment : " << sizeof(pInvestment) << std::endl;
    std::cout << "void*: " << sizeof(void*) << std::endl;
    std::cout << "Investment.get() " << pInvestment.get() << std::endl;

    // ...

    std::shared_ptr<Investment> sp =      // converts std::unique_ptr
    makeInvestment( /* arguments */ );    // to std::shared_ptr


    std::cout << "sp.get() " << sp.get() << std::endl;
    std::cout << "Investment.get() " << pInvestment.get() << std::endl;


    auto pInvestment2 =                 // pInvestment is of type
    makeInvestment( /* arguments */ );  // std::unique_ptr<Investment>

    std::cout << "Investment.get() " << pInvestment.get() << std::endl;
    std::cout << "Investment.get() " << pInvestment2.get() << std::endl;


    std::unique_ptr<int> sp1 = std::make_unique<int>(10);
    auto sp2 = sp1 ;                                     // 调用不了
    auto sp2 = std::move(sp1);                
    std::cout << "sp1.get() " << sp1.get() << std::endl;
    std::cout << "sp2.get() " << sp2.get() << std::endl;

    return 0;
}