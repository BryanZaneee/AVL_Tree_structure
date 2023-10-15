cmake_minimum_required(VERSION 3.26)
project(AVLTree_complete)

set(CMAKE_CXX_STANDARD 14)

##recommended by aman to match test environment, just like GradeScope
#set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

#pull in desired version of catch through cmake automatically, make it available
Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.1 # or a later release
)
FetchContent_MakeAvailable(Catch2)

add_executable(AVLTree_complete src/main.cpp
        src/AVL.cpp)

add_executable(Tests test-unit/test.cpp src/AVL.cpp)

target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain) #link catch to test.cpp file
#if your testing executable is named Project1, change Tests in the line above to Project1