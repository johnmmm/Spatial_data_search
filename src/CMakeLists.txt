cmake_minimum_required(VERSION 3.6)
project(Spatial_search)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp GPTree.cpp GPTree.h)

set(CMAKE_BUILD_TYPE Release)

link_directories(/usr/local/lib)
include_directories(/usr/local/include)

add_executable(searching ${SOURCE_FILES})