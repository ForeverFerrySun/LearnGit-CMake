cmake_minimum_required(VERSION 3.20)
project(test_cmake)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
if(MSVC)
# 设置UTF-8编码
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
endif()

# 设置输出目录
# CMAKE_ARCHIVE_OUTPUT_DIRECTORY；
# CMAKE_LIBRARY_OUTPUT_DIRECTORY；
# CMAKE_RUNTIME_OUTPUT_DIRECTORY；

# 源文件目录
# ${PROJECT_SOURCE_DIR}
# 构建目录
# ${PROJECT_BINARY_DIR}

# 设置静态库文件目录
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

# 通过设置CMAKE_LIBRARY_OUTPUT_DIRECTORY变量，可以将生成的库文件（包括静态库和动态库）放置在指定的目录中
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

# 可执行文件目录(全局变量)RUNTIME_OUTPUT_DIRECTORY：用于指定运行时文件的输出路径，包括可执行文件和动态库文件。
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 设置动态库和静态库的后缀
# set(CMAKE_DEBUG_POSTFIX "_d") 
# set(CMAKE_RELEASE_POSTFIX "_r")

# exe文件目录
# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LISTS)
add_library(common STATIC ${SRC_LISTS})# 不能生成动态库，暂时只能生成静态库
target_include_directories(common PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(test_cmake main.cpp)
target_include_directories(test_cmake PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(test_cmake PUBLIC common)
