# This defines which is the lowest supported CMake version for this project
cmake_minimum_required(VERSION 3.22.1)

# This sets the name for our CMake project, and defines which languages we will be using.
project(UiAOS-song LANGUAGES C CXX ASM_NASM)



add_library(${PROJECT_NAME} src/song.cpp)
target_include_directories(
        ${PROJECT_NAME} PUBLIC include
        ${PROJECT_NAME} PRIVATE include/song
)
target_link_libraries(${PROJECT_NAME} PRIVATE kernel-headers)