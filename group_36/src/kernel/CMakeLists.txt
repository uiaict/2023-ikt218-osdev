########################################
###
### Set configuration for Kernel Module
###
########################################
set(OS_MODULE_KERNEL_NAME ${OS_KERNEL_NAME}-kernel)
set(OS_MODULE_KERNEL_COMPILE_FLAGS)
file(GLOB_RECURSE OS_MODULE_KERNEL_SOURCES
        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        #src/system/*.cpp
        src/*.cpp
        src/*.c
        src/*.asm
        src/main.cpp
        #src/system/*.c
        ../boot/src/boot.cpp
        # src/gdt.cpp
        src/gdt_flush.asm
        # /include/gdt.h
)
# set(OS_MODULE_KERNEL_BINARY ${OS_KERNEL_NAME}.bin)
# set(OS_MODULE_KERNEL_LINKER ${CMAKE_SOURCE_DIR}/src/arch/i386/linker.ld)
# set(OS_MODULE_KERNEL_LINK_FLAGS "-T ${OS_MODULE_KERNEL_LINKER} ${CXX_LINKER_FLAGS}")

########################################
###
### OS Module: CPU
# All CPU specific operations are performed in this module. IRQ, ISR, GDT, IDT and other hardware glue components.
########################################
add_subdirectory(cpu)

########################################
###
### OS Module: Memory
# All memory related components to the kernel is found here. Examples:
# * Kernel Heap
########################################
add_subdirectory(memory)


########################################
###
### Import all OS Modules
###
########################################
add_subdirectory(drivers)

########################################
###
### Add executable for the kernel
###
########################################
add_executable(${OS_MODULE_KERNEL_NAME} ${OS_MODULE_KERNEL_SOURCES})
target_include_directories(
        ${OS_MODULE_KERNEL_NAME} PUBLIC
        include
        drivers/_include
        drivers/keyboard/keyboard.*
)

########################################
###
### Link libraries with the kernel.
### 1. Boot
########################################
message("Linking kernel with following libraries ${OS_LIBRARIES}")
target_link_libraries(
        ${OS_MODULE_KERNEL_NAME} PUBLIC
        ${OS_LIBRARIES}
        ${OS_APPLICATIONS}
)
########################################
###
### Set name and linker flags for the kernel
###
########################################

set_target_properties(
        ${OS_MODULE_KERNEL_NAME} PROPERTIES
        OUTPUT_NAME ${OS_MODULE_KERNEL_BINARY}
        LINK_FLAGS "${OS_MODULE_KERNEL_LINK_FLAGS}"
)



########################################
###
### Export variables to parent_Scope
###
########################################
set(OS_MODULE_KERNEL_NAME ${OS_MODULE_KERNEL_NAME} PARENT_SCOPE)