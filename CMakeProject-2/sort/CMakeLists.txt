project(sort)

add_library(${PROJECT_NAME}
    SHARED
    BucketSort.cpp
    CountSort.cpp
    QuickSort.cpp
    SelectionSort.cpp
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
    ${Sort_DIR}
)