cmake_minimum_required(VERSION 3.22)

project(bubble_sort)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(bubble_sort STATIC bubble_sort.cpp bubble_sort.h)
