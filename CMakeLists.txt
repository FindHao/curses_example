cmake_minimum_required(VERSION 3.6)
project(embedded_system)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_FLAGS "-lncursesw -lssl -lcrypto")
set(SOURCE_FILES main.c)
add_executable(embedded_system ${SOURCE_FILES})