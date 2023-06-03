# Same minimum version as the kernel
cmake_minimum_required(VERSION 3.22.1)
# New project: UiAOS-song, uses C and C++
project(UiAOS-song LANGUAGES C CXX)
# Add songs to the project
add_library(${PROJECT_NAME} src/song.cpp)
target_include_directories(
        ${PROJECT_NAME} PUBLIC include
        ${PROJECT_NAME} PRIVATE include/song
)
# Link to kernel-headers
target_link_libraries(${PROJECT_NAME} PRIVATE kernel-headers)