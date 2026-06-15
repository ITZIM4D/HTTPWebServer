cmake_minimum_required(VERSION 4.0.0)
project(WebServer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(WebServer
    src/main.cpp
    src/ThreadPool.cpp
    src/SocketServer.cpp
    src/HTTPMessage.cpp
)

include_directories(
    include
)
