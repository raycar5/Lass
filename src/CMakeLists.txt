cmake_minimum_required(VERSION 3.5)

file(GLOB_RECURSE LASSLIB_FILES "Types.*")
add_library(lasslib ${LASSLIB_FILES})
target_compile_features(lasslib PRIVATE cxx_auto_type)

find_package(LLVM REQUIRED CONFIG)

target_include_directories(lasslib PUBLIC ${LLVM_INCLUDE_DIRS} .)
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(llvm_libs support core irreader)

target_link_libraries(lasslib ${llvm_libs})