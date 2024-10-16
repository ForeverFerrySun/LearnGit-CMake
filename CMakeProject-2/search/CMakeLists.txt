cmake_minimum_required(VERSION 3.25)

project(Search)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 搜索指定目录下源文件
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR} main.cpp)

# # 静态库连接
# # 包含头文件路径
# include_directories(${PROJECT_SOURCE_DIR}/src/include)
# # 包含静态库路径
# link_directories(${PROJECT_SOURCE_DIR}/src/lib/Debug)
# # 链接静态库
# link_libraries(search)
# add_executable(${PROJECT_NAME} ${SRC_LIST})

# 动态库连接
# 包含头文件路径
include_directories(${PROJECT_SOURCE_DIR}/src/include)
# 包含动态库路径
link_directories(${PROJECT_SOURCE_DIR}/src/lib/Debug)

add_executable(${PROJECT_NAME} ${SRC_LIST})
# 链接动态库
target_link_libraries(${PROJECT_NAME} search)