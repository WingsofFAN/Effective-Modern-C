#include<iostream>
#include<thread>
#include<chrono>
#include<future>

/*
1.硬件线程是实际执行计算的线程。现代计算机体系结构会为每个 CPU 内核提供个或多个硬件线程。
2.软件线程（又称操作系统线程或系统线程）是操作系统注＇用以实施跨进程的管理，以及进行硬件线程调度的线程。
通常，能够创建的软件线程会比硬件线程要多，因为当一个软件线程阻塞了（例如，阻塞在I/0操作上，或者需要等待互斥鼠或条件变量等），运行另外的非阻塞线程能够提升吞吐率。
3.std::thread 是C++进程里的对象，用作底层软件线程的句柄。有些 std::thread 对象表示为 “null" 句柄，对应于“无软件线程”，可能的原因有：
它们处千默认构造状态（因此没有待执行的函数），或者被移动了（作为移动目的的 std::thread 对象成为了底层线程的句柄） ，或者被联结了（待运行的函数
己运行结束），或者被分离了 (std::thread 对象与其底层软件线程的连接被切断了）。
*/


#define THREAD
int mythread2() //线程入口函数
{
	std::cout << "mythread start" << "threadid= " << std::this_thread::get_id() << std::endl; //打印线程id
 
	std::chrono::milliseconds dura(5000); //定一个5秒的时间
	std::this_thread::sleep_for(dura);  //休息一定时常

	std::cout << "mythread end" << "threadid= " << std::this_thread::get_id() << std::endl; //打印线程id
 
	return 5;
}

                          
#ifdef THREAD
// std::thread 基于线程实现的并发，无法直接接受函数返回值

void mythread1(std::promise<int> &promise) //线程入口函数
{
	std::cout << "mythread start" << "threadid= " << std::this_thread::get_id() << std::endl; //打印线程id
 
	std::chrono::milliseconds dura(5000); //定一个5秒的时间
	std::this_thread::sleep_for(dura);  //休息一定时常

	std::cout << "mythread end" << "threadid= " << std::this_thread::get_id() << std::endl; //打印线程id
	promise.set_value(5);
	return ;
}

int main()
{
	//没法直接返回线程返回值，所以使用std::promise来包装返回值
	std::promise<int> promise;
	std::future<int> future = promise.get_future();
	std::thread t(mythread1, std::ref(promise)); //传递std::ref(promise)引用
	t.detach(); //分离线程，不使用join()

	std::cout << "main" << "threadid= " << std::this_thread::get_id() << std::endl;

	std::cout << "future.get() = " << future.get() << std::endl; //获取future返回值
	std::cout << "Hello World!" << std::endl;

    return 0;
}
#else
// std::async 基于任务实现的并发，不一定创建新线程
int main()
{
    std::future<int> result = std::async(mythread2); // 用future来接收异步返回值
    std::cout << "main" << "threadid= " << std::this_thread::get_id() << std::endl;

	// 等待异步任务的完成，最多等待 0 秒。
	// 如果任务在 0 秒内未完成，则返回 std::future_status::ready 状态。
    std::future_status status = result.wait_for(std::chrono::seconds(0));

    if (status == std::future_status::deferred)  // 表示异步任务还没开始执行
	{
		//线程被延迟执行了，系统资源紧张
		std::cout << result.get() << std::endl; //此时采取调用mythread()
	}
	else if (status == std::future_status::timeout) // 表示异步任务在指定的时间内未完成
	{
		//超时：表示线程还没执行完；我想等待你1秒，希望你返回，你没有返回，那么 status = timeout
		//线程还没执行完
		std::cout << "超时：表示线程还没执行完!" << std::endl;
	}
	else if (status == std::future_status::ready)  // 表示异步任务已完成
	{
		//表示线程成功返回
		std::cout << "线程成功执行完毕，返回!" << std::endl;
		std::cout << result.get() << std::endl;
	}
 
	std::cout << "Hello World!" << std::endl;

    return 0;
}
#endif