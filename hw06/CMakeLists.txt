cmake_minimum_required(VERSION 3.8)
project(hw06)

set(CMAKE_C_STANDARD 99)
SET(CMAKE_C_FLAGS "-pthread -g -Wall -Iinclude")

set(SOURCE_FILES main.c buffers.c buffers.h job_provider.h global.h job_provider.c workplace_chain.c workplace_chain.h commands.c commands.h workplace_provider.c workplace_provider.h worker.c worker.h worker_provider.c worker_provider.h)
add_executable(hw06 ${SOURCE_FILES})