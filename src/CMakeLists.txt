cmake_minimum_required(VERSION 3.10)
project(ztl_src)
add_library(ztl_src INTERFACE
        include/allocator.h
        include/ztl_concepts/_allocator.h
        include/iterator.h include/vector.h)
target_include_directories(ztl_src INTERFACE include)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)


