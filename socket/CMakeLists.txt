cmake_minimum_required(VERSION 3.15)

add_library(socket STATIC 
	Socket.h
	SocketException.h
	SocketFactory.h
	Socket.cpp
	SocketException.cpp
	SocketFactory.cpp)

target_link_libraries(${MAIN_TARGET} socket)

target_include_directories(${MAIN_TARGET} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR})