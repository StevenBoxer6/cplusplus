cmake_minimum_required(VERSION 3.8)
project(Assignment3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES BinaryTree.cpp BinaryTree.h ItemType.cpp ItemType.h)
add_library(Assignment3 ${SOURCE_FILES})