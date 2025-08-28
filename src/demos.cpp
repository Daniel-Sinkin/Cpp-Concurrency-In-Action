
#include <print>
#include <thread>
#include <vector>

using std::print, std::println;

#include "1_hello_concurrent_world.hpp"
#include "2_managing_threads.hpp"
#include "3_sharing_data_between_threads.hpp"
#include "5_the_cpp_memory_model_and_operations.hpp"

using std::print, std::println;

#define RUN_DEMO(func)                \
    println("Running  " #func "():"); \
    func();                           \
    println();

#define SKIP_DEMO(func)              \
    println("Skipping " #func "()"); \
    println();

int main() {
    { // DEMO
        println("Running demos!\n");
        SKIP_DEMO(_1::hello_concurrent_world);
        SKIP_DEMO(_2::managing_threads);
        SKIP_DEMO(_3::sharing_data_between_threads);
        RUN_DEMO(_5::the_cpp_memory_model_and_operations);
    } // DEMO
}