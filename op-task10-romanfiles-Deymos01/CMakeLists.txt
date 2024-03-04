cmake_minimum_required(VERSION 3.23)
project(op_task10_romanfiles_Deymos01)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(romancalc romancalc.cpp romanNumb.hpp stack.hpp)
add_executable(toroman toroman.cpp romanNumb.hpp)
