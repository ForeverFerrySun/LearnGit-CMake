# 设置将其中的所有内容进行编译，并生成可执行文件

cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(ThirdProject 
    VERSION 1.0.1 
    DESCRIPTION "Four sorting algorithms" 
    HOMEPAGE_URL "https://github.com/ForeverFerrySun/LearnGit-CMake"
    LANGUAGES CXX
)

# 添加子目录
add_subdirectory(CMakeProject-1)
# add_subdirectory(CMakeProject-2) 待实现
