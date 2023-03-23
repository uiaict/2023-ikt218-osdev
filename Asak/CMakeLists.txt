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
### Asak OS: Variables
###
########################################
# Defines which architecture our operating system is using. We will be using i386, which is a 32-bit architecture
set(OS_ARCH_TARGET i386)  # x86_64
# The operating system name.
set(OS_NAME "Asak Operating System")
# CMake target name for our operating system
set(OS_KERNEL_NAME "asak-os")
# Predefined list for our application targets
set(OS_APPLICATIONS)
# Predefined list for our libraries
set(OS_LIBRARIES)

# Path to the root directory
set(ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
# Path to the arch directory
set(ARCH_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/arch/${OS_ARCH_TARGET})
# Path to the stdlib directory
set(STDLIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/stdlib)

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
### Asak Module: stdlib
########################################
add_subdirectory(src/stdlib)

########################################
###
### Asak Module: Boot
########################################
add_subdirectory(src/boot)


########################################
###
### Asak Module: Kernel
########################################
add_subdirectory(src/kernel)

########################################
###
### Grub
# Configure a bootable image of our operating system
########################################
add_subdirectory(grub)

