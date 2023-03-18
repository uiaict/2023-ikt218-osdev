set(OS_MODULE_CPU_NAME ${OS_KERNEL_NAME}-cpu)
set(OS_MODULE_CPU_SOURCES
        gdt.cpp
        gdtflush.asm
)

add_library(${OS_MODULE_CPU_NAME} ${OS_MODULE_CPU_SOURCES})
target_link_libraries(${OS_MODULE_CPU_NAME} PRIVATE ${OS_MODULE_KERNEL_NAME} ${OS_LIBRARIES})
target_include_directories(
        ${OS_MODULE_CPU_NAME} PUBLIC include
        ${STDLIB_PATH}/include
    )
target_compile_definitions(${OS_MODULE_CPU_NAME} PUBLIC
        ARCH_TARGET=${ARCH_TARGET}
)

set(OS_MODULE_CPU_NAME ${OS_KERNEL_NAME}-cpu PARENT_SCOPE)
set(OS_LIBRARIES ${OS_LIBRARIES} ${OS_MODULE_CPU_NAME} PARENT_SCOPE)
