extern "C"{
    #include "system.h"
    #include "gdt.h"
    #include "common.h"
    void kernel_main();
}

extern "C" void test_gdt();

void kernel_main()
{
    clear_screen();
    init_descriptor_tables();
    
    printk("Hello, %s! The answer \n is %d.", "world", 42);
    printk("%d", 696969420);
    asm volatile ("int $0x28");
    asm volatile ("int $0x1");
}
