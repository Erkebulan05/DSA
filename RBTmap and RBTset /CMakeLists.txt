cmake_minimum_required(VERSION 3.27)
project(RBTmap_and_RBTset_)

set(CMAKE_CXX_STANDARD 17)

add_executable(RBTmap_and_RBTset_ main.cpp
        cmake-build-debug/BST.h
        BST.cpp)
