cmake_minimum_required(VERSION 3.17)
project(Server)

set(CMAKE_CXX_STANDARD 17)

add_executable(Server Socket.cpp Socket.h SocketException.h ServerSocket.cpp ServerSocket.h main.cpp Server.cpp Server.h)