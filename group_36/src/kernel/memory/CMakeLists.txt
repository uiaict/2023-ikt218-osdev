

set(OS_MODULE_MEMORY_NAME ${OS_KERNEL_NAME}-memory)
set(OS_MODULE_MEMORY_SOURCES
        paging.cpp
        kmalloc.cpp
        ../../stdlib/stdlib/cpp/bitset.cpp
)

add_library(${OS_MODULE_MEMORY_NAME} ${OS_MODULE_MEMORY_SOURCES})
target_link_libraries(${OS_MODULE_MEMORY_NAME} PRIVATE ${OS_MODULE_KERNEL_NAME} ${OS_LIBRARIES})
target_include_directories(${OS_MODULE_MEMORY_NAME} PUBLIC include)
target_compile_definitions(${OS_MODULE_MEMORY_NAME} PUBLIC
        ARCH_TARGET=i386
)



set(OS_MODULE_MEMORY_NAME ${OS_KERNEL_NAME}-memory PARENT_SCOPE)
set(OS_LIBRARIES ${OS_LIBRARIES} ${OS_MODULE_MEMORY_NAME} PARENT_SCOPE)