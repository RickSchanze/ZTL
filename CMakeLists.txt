cmake_minimum_required(VERSION 3.10)
project(ZTL)
set(CMAKE_CXX_STANDARD 20)
add_subdirectory(src)
enable_testing()
add_subdirectory(testztl)
add_subdirectory(third_party)

set(ZTL_SRC "${PROJECT_SOURCE_DIR}/src" CACHE STRING "ZTL source directory")

