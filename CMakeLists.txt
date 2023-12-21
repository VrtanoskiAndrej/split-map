cmake_minimum_required(VERSION 3.1)

include(CMakePrintHelpers)

project(
    DistributedKVS
    VERSION 1.0
    LANGUAGES CXX
)

file(GLOB PROJECT_FILES src/*.cpp)
cmake_print_variables(PROJECT_FILES)

add_subdirectory(src/proto)
add_subdirectory(src/server)

add_executable( run src/main.cpp )