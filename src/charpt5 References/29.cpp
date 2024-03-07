#include <iostream>
#include <vector>
#include <array>
#include <chrono>


/*
移动操作: 使用std::move()进行移动赋值或着移动构造
在一些情况下,使用移动操作更加减省时间,
但是在某些情况下,移动操作会退化成复制操作
*/

struct data
{
    int nums[64];
};



int main()
{
    std::vector<data> v(1000);

    auto start2 = std::chrono::system_clock::now();
    std::vector<data> v3 = v;
    auto timeend2 = std::chrono::system_clock::now();
    std::cout << "time: " << std::chrono::duration_cast<std::chrono::microseconds>(timeend2 - start2).count() << "us" << std::endl;

    auto start1 = std::chrono::system_clock::now();
    std::vector<data> v2 = std::move(v);
    auto timeend1 = std::chrono::system_clock::now();
    std::cout << "move time: " << std::chrono::duration_cast<std::chrono::microseconds>(timeend1 - start1).count() << "us" << std::endl;


    
    // 由于array的固有特性,所以array的移动操作相对较慢
    std::array<data, 1000> arr;

    auto start4 = std::chrono::system_clock::now();
    std::array<data, 1000> arr3 = arr;
    auto timeend4 = std::chrono::system_clock::now();
    std::cout << "time: " << std::chrono::duration_cast<std::chrono::microseconds>(timeend4 - start4).count() << "us" << std::endl;


    auto start3 = std::chrono::system_clock::now();
    std::array<data, 1000> arr2 = std::move(arr);
    auto timeend3 = std::chrono::system_clock::now();
    std::cout << "move time: " << std::chrono::duration_cast<std::chrono::microseconds>(timeend3 - start3).count() << "us" << std::endl;


    // 失效情况, 

    /*std::string 型别提供的是常数时间的移动和线性时间的复制。这听起来
    像是在说，它的移动比复制更快，但可能并非如此。许多 string 的实现都采用了小型
    字符串优化 (s mall string optimization, SSO) 。采用了 sso 以后，“小型”字符串（例
    如，容最不超过 15 个字符的字符串）会存储在的 std: : string 对象内的某个缓冲区内，
    而不去使用在堆上分配的存储。在使用了基千 sso 的实现的前提下，对小型字符串实施移动并不会比复制要快。*/
    std::string vs = "Do"; // not go gentle into that good night,Old age should burn and rave at close of day;Rage, rage against the dying of the light.Though wise men at their end know dark is right,Because their words had forked no lightning theyDo not go gentle into that good night.Good men, the last wave by, crying how bright.Their frail deeds might have danced in a green bay,Rage, rage against the dying of the light.Wild men who caught and sang the sun in flight,And learn, too late, they grieved it on its way,Do not go gentle into that good night.Grave men, near death, who see with blinding sightBlind eyes could blaze like 4 meteors and be gay, Rage, rage against the dying of the light.And you, my father, there on the sad height,Curse, bless, me now with your fierce tears, I pray.Do not go gentle into that good night.Rage, rage against the dying of the light.";
 
    auto start5 = std::chrono::system_clock::now();
    std::string vs1 = vs;
    auto timeend5 = std::chrono::system_clock::now();
    std::cout << "time: " << std::chrono::duration_cast<std::chrono::microseconds>(timeend5 - start5).count() << "us" << std::endl;

    auto start6 = std::chrono::system_clock::now();
    std::string vs2 = std::move(vs);
    auto timeend6 = std::chrono::system_clock::now();
    std::cout << "move time: " << std::chrono::duration_cast<std::chrono::microseconds>(timeend6 - start6).count() << "us" << std::endl;


    /* 移动操作不适用的情况
    1. 没有移动操作,会退化成复制操作
    2. 移动操作没有更优,具体的对象在具体情况下讨论
    3. 移动操作不可用,要求移动操作不可发射异常,但该操作为加上noexcept声明
    */

    return 0;
}