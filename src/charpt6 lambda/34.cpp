#include <iostream>
#include <vector>
#include <chrono>
#include <functional>
#include <string>

//优先使用lambda,而非 std::bind

using Time= std::chrono::steady_clock::time_point; 

enum class Sound { Beep, Siren, Whistle}; 

using Duration= std::chrono::steady_clock::duration; 

void setAlarm(Time  t , Sound s ,  Duration d )
{
    std::cout << " sound " << std::to_string((int)s) << " duration " << d.count() << "\n";
}


int main()
{

    // lambda实现
    auto setSoundL = [](Sound s){
            using namespace std::chrono; 
            setAlarm(steady_clock::now() + hours(1), // 警报发出时刻为1小时后发出,持续30秒
                     s,
                     seconds(30));
        };
    setSoundL(Sound::Beep);
    
    // bind实现     
    using namespace std::chrono;                      // 同前
    auto setSoundB = std::bind( setAlarm,
                                std::bind(std::plus<>(), steady_clock::now(), hours(1)),
                                std::placeholders::_1,
                                seconds(10) ); 
    setSoundB(Sound::Whistle);

    //无法针对重载进行绑定


    return 0;
}