cmake_minimum_required(VERSION 3.13)
project(untitled36)

set(CMAKE_CXX_STANDARD 14)
add_executable(untitled36 main.cpp test.cpp)
add_subdirectory(googletest)
target_link_libraries(untitled36 gtest gtest_main)