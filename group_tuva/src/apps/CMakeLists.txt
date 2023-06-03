# Definition for lowest supported CMake version for this project
cmake_minimum_required(VERSION 3.22.1)

# Sets up the name for our CMake project, defines which languages we will be using.
project(UiAOS-song LANGUAGES C CXX ASM_NASM)


add_library(${PROJECT_NAME} src/song.cpp)
target_include_directories(
        ${PROJECT_NAME} PUBLIC include
        ${PROJECT_NAME} PRIVATE include
)
target_link_libraries(${PROJECT_NAME} PRIVATE kernel-headers)