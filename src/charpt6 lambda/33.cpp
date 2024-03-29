#include<iostream>
#include<vector>
#include <functional>

using namespace std;
// 

template<typename T>
void printArray(const T arr)
{
    for(auto p:arr)std::cout << p << " ";
}


int main()
{

    std::vector<int> v{1,2,3,4,5,6,7,8,9,10};
    std::vector<float> v2{1,2,3,4,5,6,7,8,9,10};

    //万能引用
    auto f = [](auto&& param)
    {   
        return printArray((std::forward<decltype(param)>(param)));   //此处用decltype萃取出类型,再以forward完美转发
    }; 

    f(v);
    f(v2);

    return 0;
}