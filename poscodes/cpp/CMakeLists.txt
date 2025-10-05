cmake_minimum_required(VERSION 3.10)
project(poscode
VERSION 1.0
LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(COMMON_SOURCES src/utils.cpp src/poscode.cpp src/node.cpp src/queue.cpp)

add_executable(test test.cpp ${COMMON_SOURCES})
target_include_directories(test PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(bench bench.cpp ${COMMON_SOURCES})
target_include_directories(bench PUBLIC ${PROJECT_SOURCE_DIR}/include)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(test PRIVATE -O3 -march=native)
    target_compile_options(bench PRIVATE -O3 -march=native)
    target_compile_definitions(test PRIVATE NDEBUG)
    target_compile_definitions(bench PRIVATE NDEBUG)
endif()