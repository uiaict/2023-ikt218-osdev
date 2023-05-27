extern "C"{
    #include "system.h"
    #include "../include/descriptor_tables.h"
    #include "../include/common.h"
    #include "../include/monitor.h"
    #include "../include/isr.h"

}




// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void kernel_main()
{
    monitor_clear();
    
    init_descriptor_tables();
    monitor_write("Hello, World!\n");
   
    

    asm volatile ("int $0x3");
    asm volatile ("int $0x4");



    
    
    //clear_screen();
    //write_string("Hello, World!");
	
    

    
}