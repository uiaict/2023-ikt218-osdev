set(OS_MODULE_CPU_NAME ${OS_KERNEL_NAME}-cpu)
set(OS_MODULE_CPU_SOURCES
        i386/gdt.cpp
        i386/idt.cpp
        i386/isr.cpp
        i386/hardware_port.cpp
        i386/hardware.cpp
        i386/timer/timer.cpp
)

set(OS_MODULE_CPU_ASM_SOURCES
        i386/gdt_a.asm
        i386/idt_a.asm
        i386/isr_a.asm
)

add_library(${OS_MODULE_CPU_NAME} ${OS_MODULE_CPU_SOURCES} ${OS_MODULE_CPU_ASM_SOURCES})

target_link_libraries(${OS_MODULE_CPU_NAME} PRIVATE ${OS_MODULE_KERNEL_NAME} ${OS_LIBRARIES})
target_include_directories(${OS_MODULE_CPU_NAME} PUBLIC include)
target_compile_definitions(${OS_MODULE_CPU_NAME} PUBLIC
        ARCH_TARGET=i386
)


set(OS_MODULE_CPU_NAME ${OS_KERNEL_NAME}-cpu PARENT_SCOPE)
set(OS_LIBRARIES ${OS_LIBRARIES} ${OS_MODULE_CPU_NAME} PARENT_SCOPE)