cmake_minimum_required(VERSION 3.15)
project(HUFF)

set(CMAKE_CXX_STANDARD 14)

add_executable(HUFF main.cpp MinHeap.cpp MinHeap.h HUFF.cpp HUFF.h)