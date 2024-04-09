#include <iostream>
#include <thread>
#include <future>

int main() {
    // Create a std::promise object.
    std::promise<int> promise;

    // Launch a new thread that waits for the promise to be set.
    std::thread t([&promise]() {
        int value = promise.get_future().get();
        std::cout << "Received value: " << value << std::endl;
    });

    // Set the value of the promise.
    std::this_thread::sleep_for(std::chrono::seconds(1));
    promise.set_value(42); // 一来这个途径为了共享状态需要使用堆内存，而且仅限于一次性通信

    // Wait for the thread to finish.
    t.join();

    return 0;
}
