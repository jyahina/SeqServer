cmake_minimum_required(VERSION 3.15)

add_library(socket STATIC 
	Socket.h
	SocketException.h
	SocketFactory.h
	Socket.cpp
	SocketException.cpp
	SocketFactory.cpp)

