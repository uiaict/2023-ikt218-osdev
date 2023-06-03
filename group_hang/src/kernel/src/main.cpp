extern "C" {
    #include "common.h"
    #include "monitor.h"
    #include "descriptor_tables.h"
    #include "isr.h"
    #include "pit.h"
    void kernel_main();
}

void kernel_main()
{
    init_descriptor_tables();                 // Initialize the GDT and IDT

    monitor_clear();
    init_pit();


    asm volatile("sti"); 


    monitor_write("Hello, world!");
    monitor_put('\n');
    while (1){
        monitor_write("Sleep with busy wait:)\n");
        sleep_busy(200);
        monitor_write("Slept with busy wait:)\n");
        sleep_busy(200);
        monitor_write("Sleep with interrupt:)\n");
        sleep_interrupt(200);
        monitor_write("Slept with interrupt:)\n");
    }
}
