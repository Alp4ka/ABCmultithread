cmake_minimum_required(VERSION 3.21)
project(ABC5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

add_executable(ABC5 main.cpp semaphore.cpp semaphore.h jar.cpp jar.h chef.cpp chef.h cannibal.cpp cannibal.h utils.cpp utils.h)
