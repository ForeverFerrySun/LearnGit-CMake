project(search)

add_library(${PROJECT_NAME}
    SHARED
    BinarySearch.cpp
    InsertionSearch.cpp
    SequentialSearch.cpp
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
    ${Search_DIR}
)