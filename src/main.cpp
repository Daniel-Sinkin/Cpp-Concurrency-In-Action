#include <print>
#include <thread>
#include <vector>

using std::print, std::println;

#include "1_hello_concurrent_world.cpp"
#include "2_managing_threads.cpp"

using std::print, std::println;

#define RUN_DEMO(func)               \
    println("Running " #func "():"); \
    func();                          \
    println();

#define SKIP_DEMO(func)              \
    println("Skipping " #func "()"); \
    println();

int main() {
    if (false) {
        println("Running demos!\n");
        SKIP_DEMO(hello_concurrent_world);
        SKIP_DEMO(managing_threads);
    }
}