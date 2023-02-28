cmake_minimum_required(VERSION 3.10)
project(ztl_src)
add_library(ztl_src STATIC
        Allocator.cpp
        include/allocator.h
        include/ztl_concepts/_allocator.h)
target_include_directories(ztl_src PUBLIC include)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)


