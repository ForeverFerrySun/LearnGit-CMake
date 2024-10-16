cmake_minimum_required(VERSION 3.25)
project(sortTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# # 包含头文件路径
# include_directories(${PROJECT_SOURCE_DIR}/src/include)
# # 包含动态库路径
# link_directories(${PROJECT_SOURCE_DIR}/src/lib/Debug)

# set(SOURCES ${QtAVPlayer_SOURCES} main.cpp)

# set(LIBS ${QtAVPlayer_LIBS})

# set(EXECUTABLE_OUTPUT_PATH ${EXEC_PATH})
add_subdirectory(src)

add_executable(${PROJECT_NAME} PUBLIC main.cpp)

# target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBS})

