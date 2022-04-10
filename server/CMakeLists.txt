cmake_minimum_required(VERSION 3.15)

add_executable(SeqServer SeqServer.cpp)
target_link_libraries(SeqServer client)
target_link_libraries(SeqServer socket)
set_target_properties(SeqServer PROPERTIES CXX_STANDARD 17)
