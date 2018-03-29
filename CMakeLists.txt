cmake_minimum_required(VERSION 3.5)
project(lass VERSION 0.0.1 LANGUAGES CXX C)

add_executable(lass src/main)

add_subdirectory(src)


target_link_libraries(lass lasslib)