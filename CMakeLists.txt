cmake_minimum_required(VERSION 3.5)
project(lass VERSION 0.0.1 LANGUAGES CXX)

add_executable(lass src/main)
target_compile_features(lass PRIVATE cxx_auto_type cxx_std_17)

add_subdirectory(src)


target_link_libraries(lass lasslib)