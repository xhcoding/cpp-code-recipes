cmake_minimum_required(VERSION 3.24)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(cpp-code-recipes CXX)
find_package(Catch2 3 REQUIRED)

add_subdirectory(performance)
