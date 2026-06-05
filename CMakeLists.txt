cmake_minimum_required(VERSION 4.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(WebServer)

add_executable(WebServer
    src/main.cpp
    src/ThreadPool.cpp
)

include_directories(
    include
)
