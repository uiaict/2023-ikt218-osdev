extern "C"{
    #include "system.h"
    #include "../include/gdt.h"
    #include "../include/common.h"
[[noreturn]] void kernel_main();
}

extern "C" void test_gdt();

[[noreturn]] void kernel_main()
{
    clear_screen();
    init_descriptor_tables();
    /*asm volatile ("int $0x28");
    asm volatile ("int $0x1");*/
    while(true){}
}
