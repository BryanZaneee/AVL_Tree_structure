cmake_minimum_required(VERSION 3.26)
project(AVLTree_complete)

set(CMAKE_CXX_STANDARD 14)

add_executable(AVLTree_complete src/main.cpp
        src/AVL.h
        test-unit/test.cpp)
