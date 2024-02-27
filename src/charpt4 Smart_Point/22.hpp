#include <memory>

//所有和Widget相关的操作仅在这里声明,定义必须严格放到cpp文件中

class Widget
{

public:
    Widget();
    ~Widget();
    void Pirnter();

    Widget(Widget&&);
    Widget& operator=(Widget&&);

private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;
    
};


