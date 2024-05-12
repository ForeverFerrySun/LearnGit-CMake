cmake_minimum_required(VERSION 3.20)
project(test_cmake)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
# 设置MSVC的编码
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /source-charset:utf-8 /execution-charset:utf-8")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
aux_source_directory(. DIR_SRCS)
add_executable(test_cmake ${DIR_SRCS})