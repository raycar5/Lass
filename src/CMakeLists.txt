cmake_minimum_required(VERSION 3.5)

file(GLOB_RECURSE LASSLIB_FILES
"Reader.*"
"Types.*")
add_library(lasslib ${LASSLIB_FILES})

find_package(LLVM REQUIRED CONFIG)

target_include_directories(lasslib PUBLIC ${LLVM_INCLUDE_DIRS} .)
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(llvm_libs support core irreader)

add_subdirectory(CppUtils)
target_link_libraries(lasslib lass_cpp_utils ${llvm_libs})