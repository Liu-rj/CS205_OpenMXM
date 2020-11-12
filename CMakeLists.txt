cmake_minimum_required(VERSION 3.17)
project(Matrix_Multiplication)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-std=c++11 -O3")

add_executable(Matrix_Multiplication main.cpp OpenMXM.h OpenMXM.cpp)