cmake_minimum_required(VERSION 3.0)
project(DAG)

set(CMAKE_CXX_STANDARD 11)

# enable testing
enable_testing()

add_subdirectory(src)
add_subdirectory(tests)