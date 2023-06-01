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
    init_pit();


    asm volatile("sti"); 



    //initialise_paging();
    //monitor_write("Hello, paging world!\n");

    //u32int *ptr = (u32int*)0xA0000000;
    //u32int do_page_fault = *ptr;
    monitor_write("Hello, world!");
    monitor_put('\n');
    int counter = 0;
    while (1){
        monitor_write("Sleep with busy wait:)\n");
        sleep_busy(200);
        monitor_write("Slept with busy wait:)\n");
        sleep_busy(200);
        counter++;
        monitor_write("Sleep with interrupt:)\n");
        sleep_interrupt(200);
        monitor_write("Slept with interrupt:)\n");
        counter++;
    }
}
