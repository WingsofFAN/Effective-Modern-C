#include "22.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


struct Widget::Impl{
    std::string name = "22B Widget";
    std::vector<double> data;
};


Widget::Widget()
:pImpl(std::make_unique<Impl>())
{
    std::cout << "22B  Widget::Widget()" << std::endl;
}

Widget::~Widget()
{
    std::cout << "22B  Widget::~Widget()" << std::endl;
}

void Widget::Pirnter()
{
    std::cout << pImpl->name << std::endl;
}

Widget::Widget(Widget&&) = default;

Widget& Widget::operator=(Widget&&) = default;
