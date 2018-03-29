cmake_minimum_required(VERSION 3.5)

file(GLOB_RECURSE LASSLIB_FILES
"Parser.*")
add_library(lass_cpp_utils ${LASSLIB_FILES})
target_compile_features(lass_cpp_utils PRIVATE cxx_auto_type)

target_include_directories(lass_cpp_utils PUBLIC .)