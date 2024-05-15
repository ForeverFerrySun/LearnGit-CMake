project(MainProject)

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