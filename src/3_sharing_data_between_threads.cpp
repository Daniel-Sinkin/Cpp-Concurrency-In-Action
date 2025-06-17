#include <algorithm>
#include <array>
#include <chrono>
#include <list>
#include <mutex>
#include <print>
#include <ranges>

std::list<int> list;
std::mutex mutex;

using std::print, std::println;
using namespace std::chrono_literals;
using std::views::iota;

constexpr int n_threads = 6;

constexpr size_t n_iter = 5;

void add_to_list(int new_value) {
    std::scoped_lock<std::mutex> _(mutex);
    list.push_back(new_value);
}

void add_to_list_mutex_manual(int new_value) {
    mutex.lock();
    list.push_back(new_value);
    mutex.unlock();
}

void print_list() {
    std::scoped_lock<std::mutex> _(mutex);
    print("List contents: [");
    for (int value : list) {
        print("{}, ", value);
    }
    println("]");
}

void sharing_data_between_threads() {
    std::array<std::thread, n_threads> threads;
    for (int i : iota(0, n_threads)) {
        threads[i] = std::thread([i] {
            for (size_t j = 0; j < n_iter; ++j) {
                add_to_list(i);
                std::this_thread::sleep_for(700ms);
                println("{} added for the {}. time.", i, j + 1);
            }
        });
    }

    for (auto &thread : threads) {
        thread.join();
    }

    print_list();
}