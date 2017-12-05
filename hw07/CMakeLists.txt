cmake_minimum_required(VERSION 3.8)
project(hw07)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES hexconv.c test.c basic.c)
add_executable(hw07 ${SOURCE_FILES})