cmake_minimum_required(VERSION 3.20)
# cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(ThirdProject 
    VERSION 1.0.1 
    DESCRIPTION "Four sorting algorithms" 
    HOMEPAGE_URL "https://github.com/ForeverFerrySun/LearnGit-CMake"
    LANGUAGES CXX
)

# C++版本
set(CMAKE_CXX_STANDARD 17)
# C++标准库
set(CMAKE_CXX_STANDARD_REQUIRED True)


# 变量和目录设置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(Search_DIR ${CMAKE_SOURCE_DIR}/CMakeProject-2/search)
set(Sort_DIR ${CMAKE_SOURCE_DIR}/CmakeProject-2/sort)

# 添加子目录
add_subdirectory(CMakeProject-2)
add_subdirectory(CMakeProject-1)

