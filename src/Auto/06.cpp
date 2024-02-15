#include<iostream>
#include<vector>
#include<boost/type_index.hpp>

/*
在某些情况下，auto推导出来的类型和我们最后期望的类型是不一样的，这种时候需要使用者显式声明类型

例如 vector<bool> 对象执行[]操作时，并不是返回bool类型，而是返回了压缩过的std::_Bit_reference
*/

int main()
{
    std::vector<bool> feature = {true,true,true};

    auto highPriority  = feature[1];
    std::cout << "highPriority :  " << boost::typeindex::type_id_with_cvr<decltype(highPriority)>().pretty_name() << std::endl;
    
    auto highPriorityP = static_cast<bool>(feature[1]);
    std::cout << "highPriorityP :  " << boost::typeindex::type_id_with_cvr<decltype(highPriorityP)>().pretty_name() << std::endl;


    return 0;
}