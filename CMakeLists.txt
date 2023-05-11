cmake_minimum_required(VERSION 3.24)
project(StringSort)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

include_directories(.)

add_executable(StringSort
        OneginUnitTest/SortUnitTest.cpp)
