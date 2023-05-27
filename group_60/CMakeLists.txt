########################################
###
### The University of Agder Operating System: UiAOS
### We will be using C, C++ and NASM Assembly
### Visual studio code: ctrl+shift+p to get started in CMake.
########################################
# These CMAKE flags makes the compiler skip self-tests.
# (Saves time, and avoids error for some cross compilers)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

if(APPLE)
    set(IS_MACOS "yes")
endif()

set(CMAKE_SYSTEM_NAME Linux)

# This defines which is the lowest supported CMake version for this project
cmake_minimum_required(VERSION 3.22.1)

# This sets the name for our CMake project, and defines which languages we will be using.
project(UiAOS LANGUAGES C CXX ASM_NASM)

# This line creates a lock file to prevent parallell run of CMake.
file(LOCK ${CMAKE_SOURCE_DIR} DIRECTORY GUARD FILE)

########################################
###
### CMake: Import Plugins
###
########################################
# FetchContent is useful for when you wish to pull external projects / codebases. E.g., LUA, LIBC.
include(FetchContent)

########################################
###
### UiAOS: Variables
###
########################################
# Defines which architecture our operating system is using. We will be using i386, which is a 32-bit architecture
set(OS_ARCH_TARGET i386)  # x86_64
# The operating system name.
set(OS_NAME "UiA Operating System")
# CMake target name for our operating system
set(OS_KERNEL_NAME "uia-os")
# Predefined list for our application targets
set(OS_APPLICATIONS)
# Predefined list for our libraries
set(OS_LIBRARIES)

########################################
###
### Compiler Configuration
# We are using cross-compilation to ensure that the binary are compatible on other computers
# Arch: yay -S i386-elf-gcc
# Ubuntu: sudo apt -y install build-essential binutils gcc-multilib
########################################
# Set the C++ Version
set(CMAKE_CXX_STANDARD 20)
# Set the C Version
set(CMAKE_C_STANDARD 99)
# GCC Warning Flags
set(WARNING_FLAGS "-Wall -Wextra -Wshadow -Wconversion -Wsign-conversion")
# Common compiler flags for both C and C++
set(COMMON_COMPILER_FLAGS "-ffreestanding -O0 -g")
# Common include paths for external libraries
set(COMMON_INCLUDE_PATHS)
# Conditional based on which architecture we are building. We should use -m32 for i386 and -m64 for x86_64
if(OS_ARCH_TARGET STREQUAL i386)
    set(COMMON_COMPILER_FLAGS "${COMMON_COMPILER_FLAGS} -m32")
elseif(OS_ARCH_TARGET STREQUAL x86_64)
    set(COMMON_COMPILER_FLAGS "${COMMON_COMPILER_FLAGS} -m64")
else()
    message(FATAL_ERROR "Could not find the specified OS architecture: ${OS_ARCH_TARGET}")
endif()
# Set C Compiler Flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_COMPILER_FLAGS} ${WARNING_FLAGS}")
# Set C++ Compiler Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_COMPILER_FLAGS} ${WARNING_FLAGS} -fno-exceptions -fno-rtti")
# Set NASM Compiler Flags
set(CMAKE_ASM_NASM_FLAGS "${CMAKE_ASM_FLAGS} -g -O0")



# Set C++ Linker flags
set(CXX_LINKER_FLAGS  "-nostdlib -ffreestanding")
# Print out flags for the different compilers
message("CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}")
message("CMAKE_C_FLAGS=${CMAKE_C_FLAGS}")
message("CMAKE_ASM_FLAGS=${CMAKE_ASM_FLAGS}")

########################################
###
### Assembly configuration
# We use the nasm compiler
# And we must set the correct elf format
########################################
# Specifies that .s and .S extension belongs to the ASM compiler
set(CMAKE_ASM_NASM_SOURCE_FILE_EXTENSIONS ${CMAKE_ASM_NASM_SOURCE_FILE_EXTENSIONS} s S asm)
# Conditional for setting object format to ELF32. Currently we only support elf32
if(OS_ARCH_TARGET STREQUAL i386)
    set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)
else()
    message(FATAL_ERROR "Currently, we do not support other than elf32")
endif()
# Some CMake magic to get the NASM compiler working fine!
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE>")

########################################
###
### UiAOS Module: stdlib
# The standard library for our operating system. It is some mutilated attempt at doing some libc implementation, but we probably void
# all existing standards.
########################################
set(OS_MODULE_STDLIB_NAME ${OS_KERNEL_NAME}-module-stdlib)
set(OS_MODULE_STDLIB_SOURCES
        src/stdlib/src/system.c
)
add_library(${OS_MODULE_STDLIB_NAME} ${OS_MODULE_STDLIB_SOURCES})
target_include_directories(${OS_MODULE_STDLIB_NAME} 
    PUBLIC src/stdlib/include

)
target_link_libraries(${OS_MODULE_STDLIB_NAME} PUBLIC
        ${OS_LIBRARIES}
)
set(OS_LIBRARIES ${OS_LIBRARIES} ${OS_MODULE_STDLIB_NAME})


########################################
###
### UiAOS Module: Boot
# The boot module takes care of booting the operating system
# it is written in assembler language and does the following
# 1. define the multiboot header variables
# 2. define the multiboot header section.
# 3. defines the .bss section. https://en.wikipedia.org/wiki/.bss
# 4. defines the .text section (code segment) https://en.wikipedia.org/wiki/Code_segment
# 5. defines the start routine which finally starts our kernel
########################################
# Currently, we only support x86 booting
if(NOT OS_ARCH_TARGET STREQUAL "i386")
    message(FATAL_ERROR "No boot definition exists for ${OS_ARCH_TARGET}")
endif()
# Sets the module name for the boot library
set(OS_MODULE_BOOT_NAME ${OS_KERNEL_NAME}-boot)
# Defines all source-files that are related to the bootloader
set(OS_MODULE_BOOT_SOURCES
        #${ARCH_TARGET}/boot.asm
        src/boot/src/boot.cpp
)
# Creates a library for our multi-boot section
add_library(${OS_MODULE_BOOT_NAME} ${OS_MODULE_BOOT_SOURCES})
# Defines the include directories for the boot library
target_include_directories(${OS_MODULE_BOOT_NAME} PUBLIC
    src/boot/include/
)
# Defines the linking between boot and the boot library
target_link_libraries(${OS_MODULE_BOOT_NAME} PRIVATE ${OS_MODULE_KERNEL_NAME} ${OS_LIBRARIES})
set(OS_LIBRARIES ${OS_LIBRARIES} ${OS_MODULE_BOOT_NAME})

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
        src/kernel/src/*.cpp
        src/kernel/src/*.c
)
# Set the output binary name
set(OS_MODULE_KERNEL_BINARY kernel.bin)
# Defines the linker location
set(OS_MODULE_KERNEL_LINKER ${CMAKE_CURRENT_SOURCE_DIR}/src/arch/${OS_ARCH_TARGET}/linker.ld)
# Define custom linker flags for the kernel
set(OS_MODULE_KERNEL_LINK_FLAGS "-T ${OS_MODULE_KERNEL_LINKER} ${CXX_LINKER_FLAGS}")
# Add executable for the kernel.
# Tutorial: the add_executable creates a 'executable target' in CMake, in contrast to add_library, which creates a library target.
# A target is a recipe for building a component. For example, the uiaos-boot target is a recipe for building the boot source code.
add_executable(${OS_MODULE_KERNEL_NAME} ${OS_MODULE_KERNEL_SOURCES})
# Defines which include directories to usefor the kernel.
target_include_directories(
        ${OS_MODULE_KERNEL_NAME} PUBLIC
        src/kernel/include
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
)

########################################
###
### Grub
# Configure a bootable image of our operating system
########################################
add_subdirectory(grub)

########################################
###
### Add a target called 'build', which will build all other targets.
###
########################################
add_custom_target(build)
add_dependencies(build ${GRUB_TARGET})