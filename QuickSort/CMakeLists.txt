cmake_minimum_required(VERSION 3.22)

project(QuickSort)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(QuickSort STATIC QuickSort.cpp QuickSort.h)
