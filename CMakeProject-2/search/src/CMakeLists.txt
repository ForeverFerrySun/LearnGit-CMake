cmake_minimum_required(VERSION 3.25)

project(search)

# windows系统动态库生成lib文件命令
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 编译器设置：针对 MSVC 处理 UTF-8 编码和警告
if(MSVC)
    add_compile_options("/utf-8" "/W3" "/Zc:__cplusplus" "/EHsc")
endif()

# 设置生成库
add_library(${PROJECT_NAME}
    SHARED
    # STATIC
    BinarySearch.cpp
    InsertionSearch.cpp
    SequentialSearch.cpp
)

# 设定动态链接库的存储路径
set_target_properties(${PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib
    # static静态库
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib
    )

# 将头文件粘贴到指定目录
file(GLOB HEARD "*.h")
file(COPY ${HEARD} DESTINATION ${CMAKE_BINARY_DIR}/../include)

# 使用target_include_directories() 命令将库的头文件路径公开给需要使用该库的目标。
target_include_directories(${PROJECT_NAME} 
    PUBLIC
    ${Search_DIR}
)
