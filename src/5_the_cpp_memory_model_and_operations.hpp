
#pragma once

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <list>
#include <mutex>
#include <print>
#include <ranges>
#include <thread>

namespace _5 {
std::list<int> list;
std::mutex mutex;

using std::print, std::println;
using namespace std::chrono_literals;
using std::views::iota;

class SpinlockMutex {
public:
    SpinlockMutex() : flag(ATOMIC_FLAG_INIT) {}
    void lock() {
        while (flag.test_and_set(std::memory_order_acquire))
            ;
    }
    void unlock() {
        flag.clear(std::memory_order_release);
    }

private:
    std::atomic_flag flag;
};

void the_cpp_memory_model_and_operations() {
}
} // namespace _5