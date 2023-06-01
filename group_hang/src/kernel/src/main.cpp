extern "C" {
    #include "common.h"
    #include "monitor.h"
    #include "descriptor_tables.h"
    #include "isr.h"
    #include "pit.h"
    #include "paging.h"
    void kernel_main();
}

void kernel_main()
{
    init_descriptor_tables();                 // Initialize the GDT and IDT

    //init_keyboard();
    monitor_clear();


    asm volatile("sti"); 

    init_pit();


    //initialise_paging();
    //monitor_write("Hello, paging world!\n");

    //u32int *ptr = (u32int*)0xA0000000;
    //u32int do_page_fault = *ptr;
    monitor_write("Hello, world!");
    monitor_put('\n');
    
    while (1){
        sleep_interrupt(2);
    }
}
