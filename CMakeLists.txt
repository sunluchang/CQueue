cmake_minimum_required(VERSION 3.6)
project(CQueue)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp CQueue.h)
add_executable(CQueue ${SOURCE_FILES})