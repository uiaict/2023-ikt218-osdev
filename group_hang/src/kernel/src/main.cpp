extern "C" {
    #include "common.h"
    #include "monitor.h"
    #include "descriptor_tables.h"
    #include "isr.h"
    void kernel_main();
}

void kernel_main()
{
    init_descriptor_tables();                 // Initialize the GDT and IDT

    //init_keyboard();
    monitor_clear();

    asm volatile("sti"); 
    monitor_write("Hello, world!");
    monitor_put('\n');

    
    while (1) { }
}
