cmake_minimum_required(VERSION 3.15)

add_library(client SHARED 
	ClientHandler.h
	ClientHandler.cpp)

target_link_libraries(client)