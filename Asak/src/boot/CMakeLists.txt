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
if(OS_ARCH_TARGET STREQUAL i386)
    # Sets the module name for the boot library
    set(OS_MODULE_BOOT_NAME ${OS_KERNEL_NAME}-boot)

    # Defines all source-files that are related to the bootloader
    set(OS_MODULE_BOOT_SOURCES
        src/boot.asm
    )

    # Creates a library for our multi-boot section
    add_library(${OS_MODULE_BOOT_NAME} ${OS_MODULE_BOOT_SOURCES})
    
    # Defines the include directories for the boot library
    target_include_directories(${OS_MODULE_BOOT_NAME} PUBLIC ${ARCH_TARGET}/ include)

    # Defines the linking between boot and the boot library
    target_link_libraries(${OS_MODULE_BOOT_NAME} PRIVATE ${OS_MODULE_KERNEL_NAME} ${OS_LIBRARIES})
    set(OS_LIBRARIES ${OS_LIBRARIES} ${OS_MODULE_BOOT_NAME} PARENT_SCOPE)

else()
    message(FATAL_ERROR "No boot definition exists for ${ARCH_TARGET}")
endif()