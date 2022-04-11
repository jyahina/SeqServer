cmake_minimum_required(VERSION 3.15)

add_library(client STATIC 
	ClientHandler.h
	ClientHandler.cpp)

target_link_libraries(${MAIN_TARGET} client)

target_include_directories(${MAIN_TARGET} PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(client PRIVATE 
	${CMAKE_SOURCE_DIR})