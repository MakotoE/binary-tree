project(tests)

add_subdirectory(googletest)

add_compile_options(-Wall -Wextra -pedantic)

add_executable(tests tree.cpp)
target_link_libraries(tests gtest gtest_main binary-tree)