#include <print>
#include <thread>
#include <vector>

using std::print, std::println;

#include "1_hello_concurrent_world.cpp"
#include "2_managing_threads.cpp"
#include "3_sharing_data_between_threads.cpp"

using std::print, std::println;

#define RUN_DEMO(func)               \
    println("Running " #func "():"); \
    func();                          \
    println();

#define SKIP_DEMO(func)              \
    println("Skipping " #func "()"); \
    println();

int main() {
    { // DEMO
        println("Running demos!\n");
        RUN_DEMO(hello_concurrent_world);
        RUN_DEMO(managing_threads);
        RUN_DEMO(sharing_data_between_threads);
    } // DEMO
}