cmake_minimum_required(VERSION 4.1)
project(Labor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic -Wconversion)

add_executable(Labor L3_Gagea_Tiberiu_Problem1_main.cpp
        L3_Gagea_Tiberiu_Problem1_complex.h
        L3_Gagea_Tiberiu_Problem1_complex.cpp)
