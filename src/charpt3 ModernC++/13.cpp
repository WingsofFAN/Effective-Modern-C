#include<iostream>
#include<algorithm>
#include<vector>

//优先选用 const_iterator, 而非 iterator


// C++14中完全可以正常个运行,C++11中没有非成员的cbegin和cend
template<typename C, typename V>
void findAndinsert(C& container,       //在容器中查找 targetVal
                   const V& targetVal, //第一次出现的位置．
                   const V& insertVal) //然后在彼处插入 insertVal
{
    using std::cbegin;
    using std::cend;
    auto it = std::find(cbegin(container),cend(container),targetVal);
    container.insert(it, insertVal); 
}

int main()
{

    std::vector<int> values = {1,2,3,4,1983,5,6,7,8,9};

    // 简单使用 iterator
    std::vector<int>::iterator it = std::find(values.begin(), values.end(), 1983);

    // 使用 const_iterator 
    auto it1 = std::find(values.cbegin(),values.cend(), 1983);    // 使用cbegin 和 cend


    values.insert(it, 1998); 

    findAndinsert(values, 1998,1988);

    return 0;

}