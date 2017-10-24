cmake_minimum_required(VERSION 3.8)
project(cv04)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES forkpipe.c)
add_executable(cv04 ${SOURCE_FILES})