cmake_minimum_required(VERSION 3.20)

project(json_writer)

set(CMAKE_CXX_STANDARD 17)

add_executable(json_writer_demo "main.cpp")

enable_testing()
add_subdirectory(test)
