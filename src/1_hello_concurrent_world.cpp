#include <print>
#include <thread>
#include <vector>

using std::print, std::println;

void hello() {
    std::print("Hello, World!\n");
}

void hello_with_arg(int i) {
    std::print("Hello, World with arg {}!\n", i);
}

void hello_concurrent_world() {
    std::vector<std::thread> threads;

    threads.emplace_back(hello);
    threads.emplace_back(hello_with_arg, 2);

    print("There are {} threads active: ", threads.size());
    for (auto &thread : threads) {
        print("{}, ", thread.get_id());
    }
    println();

    println("Joining threads now.");
    for (auto &thread : threads) {
        println("Joing thread {}", thread.get_id());
        thread.join();
    }

    println("Finished joining threads.");
}