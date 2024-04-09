#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

// 基于标志位的线程间通信

std::mutex mtx;
std::condition_variable cv;
std::queue<int> buffer;
const int kMaxBufferSize = 5;

void producer() {
    int count = 0;
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return buffer.size() < kMaxBufferSize; });

        buffer.push(count);
        std::cout << "Produced: " << count << std::endl;
        count++;

        lock.unlock();
        cv.notify_all();
    }
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !buffer.empty(); });

        int value = buffer.front();
        buffer.pop();
        std::cout << "Consumed: " << value << std::endl;

        lock.unlock();
        cv.notify_all();
    }
}

int main() {
    std::thread producer_thread(producer);
    std::thread consumer_thread(consumer);

    producer_thread.join();
    consumer_thread.join();

    return 0;
}
