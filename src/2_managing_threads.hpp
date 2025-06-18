
#pragma once

#include <chrono>
#include <print>
#include <thread>
#include <utility>
#include <vector>

namespace _2 {
using namespace std::chrono_literals;

using std::print, std::println;

class thread_guard {
public:
    thread_guard(std::thread &t_) : t(t_) {}
    ~thread_guard() {
        if (this->t.joinable()) {
            this->t.join();
        }
    }
    thread_guard(thread_guard const &) = delete;
    thread_guard &operator=(thread_guard const &) = delete;

private:
    std::thread &t;
};

class scoped_thread {
public:
    scoped_thread(std::thread t_) : t(std::move(t_)) {
        if (!t.joinable()) {
            throw std::runtime_error("Thread not joinable!");
        }
    }
    ~scoped_thread() {
        t.join();
    }
    scoped_thread(scoped_thread const &) = delete;
    scoped_thread &operator=(scoped_thread const &) = delete;

private:
    std::thread t;
};

void func(int *ptr) {
    std::this_thread::sleep_for(10ms);
    println("Hello, World with ptr = [{}, {}, {}]!", ptr[0], ptr[1], ptr[2]);
}
void use_after_free() {
    auto ptr = static_cast<int *>(malloc(3 * sizeof(int)));
    ptr[0] = 3;
    ptr[1] = 5;
    ptr[2] = -7;

    int local = 2;
    std::thread t{func, ptr};
    free(ptr);
    t.join();
}

void no_use_after_free() {
    auto ptr = static_cast<int *>(malloc(3 * sizeof(int)));
    ptr[0] = 3;
    ptr[1] = 5;
    ptr[2] = -7;

    int local = 2;
    std::thread t{func, ptr};
    t.join();
    free(ptr);
}

void managing_threads() {
    {
        println("no_use_after_free()");
        no_use_after_free();
        println("use_after_free()");
        use_after_free();

        std::thread t{[] {}};

        std::thread t_guarded{[] { std::this_thread::sleep_for(1500ms); }};
        thread_guard g(t_guarded);

        t.join();
        // t_guarded.join() // Don't have to (and now can't) explicitly join, will be done on leaving scope.
        println("Finished the scope, leaving it now!");
    }
    println("Finally left the scope.");
}
}