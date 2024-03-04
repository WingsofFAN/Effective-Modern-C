#include <iostream>
#include <chrono>
#include <set>


// 熟悉依万能引用型别进行重载的替代方案

/*
规避开万能引用:
1.舍弃重载                                     
2.const T&型别的行参, 即使用左值常量来代替万能引用
3.传值

利用完美转发改善:
4.标签分配
5.对接受万能引用的模板加以限制

如何权衡:
*/ 

std::multiset<std::string> names;

void log(std::chrono::system_clock::time_point now, const char* msg)
{
    std::cout << std::chrono::system_clock::to_time_t(now) << ": " << msg << std::endl;
}

template<typename T>
void logAndAddimpl(T&& name, std::false_type)     // 非整型实参：用false_type区分开
{
    auto now = std::chrono::system_clock::now();
    log(now, "logAndAdd");
    names.emplace(std::forward<T>(name));
}

std::string nameFromidx(int idx)
{
    return "name" + std::to_string(idx);
}

void logAndAddimpl(int idx, std::true_type)      
{
    auto now = std::chrono::system_clock::now();
    log(now, "logAndAdd");
    names.emplace("names_"+std::to_string(idx));
} 

template<typename T>
void logAndAdd(T&& name)
{
    logAndAddimpl(std::forward<T>(name),
                  std::is_integral<typename std::remove_reference<T>::type>());
}


/* 对接受万能引用的模板加以限制:

class Person {
public:
    template<typename T,
    typename = typename std::enable_if<condition>::type>
    explicit Person(T&& n);
}

class Person {
public:
template<
        typename T,
        typename = typename std::enable_if<
                    !std::is_same<Person, typename std::decay<T>::type >::value
                    >::type
        >
explicit Person(T&& n);
...
}



class Person {
public:
    template<
        typename T,
        typename = std::enable_if_t<
                        !std::is_base_of<Person, std::decay_t<T>>::value
                        &&
                        !std::is_integral<std::remove_reference_t<T>>::value
                        >
        explicit Person(T&& n)
        :name(std: :forward <T>(n))  // 接受std::string 和其他可以转换为std::string 的型别
        {...}

        explicit Person(int idx)     // 接收整型实参
        :name(nameFromidx(idx))
        {... }

private:
    std::string name;
};




*/





int main()
{
    

    logAndAdd("name1");    //
    logAndAdd(22);

    for(auto p: names) std::cout << p << " ";
    std::cout << std::endl;

    return 0;
}
