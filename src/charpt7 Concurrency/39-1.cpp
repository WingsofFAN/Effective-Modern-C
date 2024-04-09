#include <iostream>
#include <string>

// 基于条件变量实现的线程间通信


#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;  // 定义一个互斥量
std::condition_variable cv;  // 定义一个条件变量
int shared_resource = 0;  // 共享资源

void thread_function_1() {
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);  // 获取互斥量
        shared_resource++;
        std::cout << "Thread 1: " << shared_resource << std::endl;
        lock.unlock();  // 释放互斥量
        cv.notify_one();  // 通知其他线程
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // 让出CPU
    }
}

void thread_function_2() {
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);  // 获取互斥量
        cv.wait(lock, [&](){ return shared_resource > 0; });  // 等待条件满足
        shared_resource--;
        std::cout << "Thread 2: " << shared_resource << std::endl;
        lock.unlock();  // 释放互斥量
    }
}

int main() {
    std::thread t1(thread_function_1);
    std::thread t2(thread_function_2);

    t1.join();
    t2.join();

    std::cout << "Final shared resource value: " << shared_resource << std::endl;

    return 0;
}



