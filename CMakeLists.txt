cmake_minimum_required(VERSION 3.6)
project(giterdone)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

set(SOURCE_FILES main.cpp)
add_executable(giterdone ${SOURCE_FILES})