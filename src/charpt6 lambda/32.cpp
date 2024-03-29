#include<iostream>
#include<vector>
#include<algorithm>
#include <functional>

// c++14 支持初始化捕获将对象移入闭包
// c++11 经由手工实现的类或std::bind去模拟初始化捕获


int main(){

    std::vector<int> v{1,2,3,4,5,6,7,8,9};
    //c++14 使用移动捕获
    auto func = [temp = std::move(v)]() {
        for(auto p:temp)std::cout<<p<<" ";
    };

    func();


    //C++11  使用 std::bind() 替代 
    std::vector<int> v2{1,2,3,4,5,6,7,8,9};
    auto func2 = std::bind(
        [](std::vector<int> v){
            for(auto p:v)std::cout<<p<<" ";
        },
        std::move(v2)
    );
    func2();
    return 0;
}