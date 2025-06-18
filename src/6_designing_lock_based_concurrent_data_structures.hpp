
#pragma once

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <exception>
#include <list>
#include <mutex>
#include <print>
#include <stack>
#include <thread>

namespace _5 {
struct empty_stack : std::exception {
    const char *what() const throw();
};

template <typename T>
class AtomicStack {
public:
    AtomicStack() {}
    AtomicStack(const AtomicStack &other) {
        std::lock_guard<std::mutex> _(other.m);
        data = other.data;
    }
    AtomicStack &operator=(const AtomicStac &) = delete;
    void push(T new_value) {
        std::lock_guard<std::mutex> lock(m);
        data.push(std::move(new_value));
    }
    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> _(m);
        if (data.empty()) throw empty_stack();
        std::shared_ptr<T> const res(std::make_shared<T>(std::move(data.top())));
        data.pop();
        return res;
    }
    bool empty() const {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }

private:
    std::stack<T> data;
    mutable std::mutex m;
};

void designing_lock_based_concurrent_data_structures() {
}
} // namespace _5