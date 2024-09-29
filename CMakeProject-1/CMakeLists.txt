# CMake 最低版本
cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

# 项目信息
project(CMakeProject
    VERSION 1.0.0
    DESCRIPTION "An example C++ project using CMake"
    LANGUAGES CXX)

# 设置 C++17 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 编译器设置：针对 MSVC 处理 UTF-8 编码和警告
if(MSVC)
    add_compile_options("/utf-8" "/W3" "/Zc:__cplusplus" "/EHsc")
endif()

# 源文件和头文件
set(include
    include/8queenF.h
)
set(src
    main.cpp
    src/8queenF.cpp
)

# 生成可执行文件
add_executable(${PROJECT_NAME} ${include} ${src})