cmake_minimum_required(VERSION 3.17)
project(binary-tree)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic)

add_subdirectory(tests)

add_library(binary-tree STATIC tree.h)
set_target_properties(binary-tree PROPERTIES LINKER_LANGUAGE CXX)