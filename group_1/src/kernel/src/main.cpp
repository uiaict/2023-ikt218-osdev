extern "C"{
    #include "system.h"
    #include "../include/gdt.h"
    #include "../include/common.h"
    #include "../include/isr.h"
[[noreturn]] void kernel_main();
}

extern "C" void test_gdt();

[[noreturn]] void kernel_main()
{
    clear_screen();
    init_descriptor_tables();
    initialize_interrupt_handlers();
    asm volatile ("int $0x28");
    while(true){}
}
