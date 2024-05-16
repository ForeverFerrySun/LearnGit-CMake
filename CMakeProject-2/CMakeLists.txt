cmake_minimum_required(VERSION 3.20) # 设置CMake的最低版本要求
project(MainProject)

if(MSVC)
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/execution-charset:gbk>")
endif()

add_subdirectory(search)
add_subdirectory(sort)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
    ${Search_DIR}
    ${Sort_DIR}
)
target_link_libraries(${PROJECT_NAME} 
    PUBLIC
    search
    sort
)