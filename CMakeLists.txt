cmake_minimum_required(VERSION 3.26)
project(AVLTree_complete)

set(CMAKE_CXX_STANDARD 14)

Include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.0.1
)
FetchContent_MakeAvailable(Catch2)

add_library(AVL STATIC 
    src/AVL.cpp 
    src/AVL.h
)

add_executable(AVLTree_complete 
    src/main.cpp
)
target_link_libraries(AVLTree_complete AVL)

add_executable(Tests 
    testing/test.cpp
)
target_link_libraries(Tests AVL Catch2::Catch2WithMain)

# Set the include path for Catch2
target_include_directories(Tests PRIVATE ${Catch2_SOURCE_DIR}/single_include)