cmake_minimum_required(VERSION 3.15)

add_library(client SHARED 
	Socket.h
	SocketException.h
	SocketFactory.h
	Socket.cpp
	SocketException.cpp
	SocketFactory.cpp)

target_link_libraries(socket)