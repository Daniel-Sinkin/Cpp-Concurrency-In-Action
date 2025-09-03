#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>

using std::print, std::println;

class Spinlock {
public:
    void lock() noexcept {
        while (flag.test_and_set(std::memory_order_acquire)) {
        }
    }

    void unlock() noexcept {
        flag.clear(std::memory_order_release);
    }

    bool try_lock() noexcept {
        return !flag.test_and_set(std::memory_order_acquire);
    }

private:
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
};

Spinlock g_Spin;
int g_Counter = 0;

void worker() {
    for (int i = 0; i < 100'000; ++i) {
        std::scoped_lock _(g_Spin);
        ++g_Counter;
    }
}

int main() {
    std::thread t1(worker);
    std::thread t2(worker);

    t1.join();
    t2.join();

    println("Counter = {}", g_Counter);
}