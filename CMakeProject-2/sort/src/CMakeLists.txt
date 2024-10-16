cmake_minimum_required(VERSION 3.25)

project(MyLibrary)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIB_DIR     
    BucketSort.cpp
    CountSort.cpp
    QuickSort.cpp
    SelectionSort.cpp
)

# windows系统动态库生成lib文件命令
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# 添加库
add_library(MyLibrary 
    SHARED 
    ${LIB_DIR}
)

# 设置库的头文件路径
target_include_directories(${PROJECT_NAME} 
    PUBLIC
    ${Sort_DIR}
)
