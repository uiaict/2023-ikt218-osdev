// Define entry point in asm to prevent C++ mangling
extern "C" {
    #include "common.h"
    #include "system.h"
    #include "monitor.h"
    void kernel_main();
}

void kernel_main() {
    //monitor_clear();
    //monitor_write((const char*)"Hello, world!"); 
    monitor_put('K', 0, 15);
}