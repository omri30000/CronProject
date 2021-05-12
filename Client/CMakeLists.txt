cmake_minimum_required(VERSION 3.17)
project(Client)

set(CMAKE_CXX_STANDARD 17)

add_executable(Client Socket.cpp Socket.h SocketException.h ClientSocket.cpp ClientSocket.h main.cpp Client.cpp Client.h)