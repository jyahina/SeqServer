cmake_minimum_required(VERSION 3.15)

add_library(client STATIC 
	ClientHandler.h
	ClientHandler.cpp)

target_link_libraries(${MAIN_TARGET} client)

target_include_directories(client PRIVATE 
	${CMAKE_SOURCE_DIR})