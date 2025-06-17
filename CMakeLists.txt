cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "/opt/homebrew/opt/llvm/bin/clang")
set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")

project(ConcurrencyInAction VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES src/main.cpp)

add_executable(ConcurrencyInAction src//main.cpp)

target_include_directories(ConcurrencyInAction PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src) 