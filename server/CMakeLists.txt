cmake_minimum_required(VERSION 3.15)

add_executable(${MAIN_TARGET} SeqServer.cpp)

target_include_directories(${MAIN_TARGET} PRIVATE 
	${CMAKE_SOURCE_DIR})
