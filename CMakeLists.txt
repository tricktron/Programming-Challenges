cmake_minimum_required(VERSION 3.8)
project(uva)
set(CMAKE_CXX_STANDARD 11)
set (CMAKE_C_COMPILER "/usr/local/Cellar/gcc@5/5.4.0_1/bin/gcc-5")
set (CMAKE_CXX_COMPILER "/usr/local/Cellar/gcc@5/5.4.0_1/bin/g++-5")
set(CMAKE_C_FLAGS "-lm -O2 -pipe -ansi -DONLINE_JUDGE")
set(CMAKE_CXX_FLAGS "-lm -O2 -std=c++11 -pipe -DONLINE_JUDGE")


add_subdirectory(10041_vitos_family)
add_subdirectory(10189_minesweeper)
