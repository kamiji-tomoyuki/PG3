#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready1 = true, ready2 = false, ready3 = false;

void thread1() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return ready1; });

    std::cout << "thread 1" << std::endl;

    ready1 = false;
    ready2 = true;
    cv.notify_all();
}

void thread2() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return ready2; });

    std::cout << "thread 2" << std::endl;

    ready2 = false;
    ready3 = true;
    cv.notify_all();
}

void thread3() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return ready3; });

    std::cout << "thread 3" << std::endl;

    ready3 = false;
    cv.notify_all();
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);
    std::thread t3(thread3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}