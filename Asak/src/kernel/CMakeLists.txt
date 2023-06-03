########################################
###
### OS Module: Kernel
# The operating system kernel
# 1. Sets compiler and linker configuration
# 2. Locate and build sources of the kernel
# 3. Link boot object with the kernel
# 4. copy compiled binary to the root of the cmake build directory.
########################################

# Define kernel module name
set(OS_MODULE_KERNEL_NAME ${OS_KERNEL_NAME}-kernel)
# Define custom compile flags for the kernel
set(OS_MODULE_KERNEL_COMPILE_FLAGS)
# Scan the src/kernel directory for source files (c/cpp)
file(GLOB_RECURSE OS_MODULE_KERNEL_SOURCES
        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        src/*.cpp
        src/*.c
)

# Set the output binary name
set(OS_MODULE_KERNEL_BINARY kernel.bin)
# Defines the linker location
set(OS_MODULE_KERNEL_LINKER ${ARCH_PATH}/linker.ld)
# Define custom linker flags for the kernel
set(OS_MODULE_KERNEL_LINK_FLAGS "-T ${OS_MODULE_KERNEL_LINKER} ${CXX_LINKER_FLAGS}")

########################################
###
### OS Module: CPU
# All CPU specific operations are performed in this module. IRQ, ISR, GDT, IDT and other hardware glue components.
########################################
add_subdirectory(cpu)

########################################
###
### OS Module: Drivers
# All drivers for example keyboards etc is in this module.
########################################
add_subdirectory(drivers)


########################################
###
### OS Module: Memory
# All memory specific operation such as malloc, paging etc.
########################################
add_subdirectory(memory)

# Add executable for the kernel.
# Tutorial: the add_executable creates a 'executable target' in CMake, in contrast to add_library, which creates a library target.
# A target is a recipe for building a component. For example, the uiaos-boot target is a recipe for building the boot source code.
add_executable(${OS_MODULE_KERNEL_NAME} ${OS_MODULE_KERNEL_SOURCES})

# Defines which include directories to usefor the kernel.
target_include_directories(
        ${OS_MODULE_KERNEL_NAME} PUBLIC
        include
        ${STDLIB_PATH}/include
        ${SONG_PATH}
)

# Defines which libraries to link against. Linking is where the compiler "glues" together libraries and code pieces.
target_link_libraries(
        ${OS_MODULE_KERNEL_NAME} PUBLIC
        ${OS_LIBRARIES}
        ${OS_APPLICATIONS}
)

# Defines properties for the specific target. In our case, we have some custom linker flags and a custom output name
set_target_properties(
        ${OS_MODULE_KERNEL_NAME} PROPERTIES
        OUTPUT_NAME ${OS_MODULE_KERNEL_BINARY}
        LINK_FLAGS "${OS_MODULE_KERNEL_LINK_FLAGS}"
        RUNTIME_OUTPUT_DIRECTORY "${BUILD_PATH}"
)

