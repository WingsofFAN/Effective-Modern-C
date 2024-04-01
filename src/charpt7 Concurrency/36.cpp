#include <iostream>
#include <chrono>
#include <future>
#include <thread>

//如果异步是必要的,则通过指定std::launch::async来实现


int mythread() //线程入口函数
{
	std::cout << "mythread start" << "threadid= " << std::this_thread::get_id() << std::endl; //打印线程id
 
	std::chrono::milliseconds dura(5000);                                                     //定一个5秒的时间
	std::this_thread::sleep_for(dura);                                                        //休息一定时常

	std::cout << "mythread end" << "threadid= " << std::this_thread::get_id() << std::endl;   //打印线程id
 
	return 5;
}

//使用模板将F与F的参数进行完美转发,并设定线程启动为异步
template<typename F, typename... Ts>
inline
auto
reallyAsync(F&& f, Ts&&... params)
{
    return std::async(std::launch::async,
                      std::forward<F>(f),
                      std::forward<Ts>(params)...);
}



int main()
{

    // auto fut1 = std::async(mythread);      //使用默认方式启动
    

    auto fut2 = std::async(std::launch::async, mythread);   // 异步调用  
    //使用异步或者推迟的方式启动

    while(fut2.wait_for(std::chrono::milliseconds(100)) != std::future_status::ready) 
    {
        std::cout << "main waiting fut2" << std::endl;
    } //循环至fut2完成
    

    // auto fut3 = std::async(std::launch::deferred, mythread); // 推迟调用
    // while(fut3.wait_for(std::chrono::milliseconds(100)) != std::future_status::ready) 
    // {
    //     std::cout << "main waiting fut3" << std::endl;
    // } //可能进入死循环,因为无法确认后续是否会调用get或wait来使得fut3进行运行

    
    

    std::future<int> fut1 = std::async(mythread);      //使用默认方式启动

    
    // auto fut2 = std::async(std::launch::async | std::launch::deferred, mythread);
    /*
    1.无法预知mythread是否会和t并行,因为mythread可能会被调度为推迟行为
    2.无法预知mythread是否运行在与调用fut1的get或wait函数的线程不同的线程之上.
    3.连f是否运行这件起码的事情都会是无法预知的,这是因为无法保证在程序的每条路径上,fut1的get或wait都会得到调用.
    */

    if (fut1.wait_for(std::chrono::milliseconds(0)) == std::future_status::deferred) //如果任务被推迟了
    {   
        //则使用 wait或get 以异步的方式调用fut1
        std::cout <<  "fut1 is deferred" << std::endl;
        std::cout << "fut1 result = " << fut1.get() << std::endl;
    }
    else   //任务已经在进行
    {
        std::cout <<  "fut1 is not deferred" << std::endl;
        while(fut1.wait_for(std::chrono::milliseconds(100)) != std::future_status::ready) //不可能死循环
        {
            std::cout << "main waiting fut1" << std::endl;
            //做其他的并行任务,直至fut1完成
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }



    auto fut = reallyAsync(mythread);
    if (fut.wait_for(std::chrono::milliseconds(0)) == std::future_status::deferred) //如果任务被推迟了
    {   
        //则使用 wait或get 以异步的方式调用fut1
        std::cout <<  "fut is deferred" << std::endl;
        std::cout << "fut result = " << fut1.get() << std::endl;
    }
    else   //任务已经在进行
    {
        std::cout <<  "fut is not deferred" << std::endl;
        while(fut1.wait_for(std::chrono::milliseconds(100)) != std::future_status::ready) //不可能死循环
        {
            std::cout << "main waiting fut" << std::endl;
            //做其他的并行任务,直至fut1完成
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }


    return 0;
}