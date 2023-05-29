#include "system.h"
#include "../cpu/gdt.h"
#include "../screen/screen.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
    void init_gdt();
}

void kernel_main() {
    
    write_string(0xF, "Hello, world!");
    write_string(0xF, "Hello, world!");
    write_string(0xF, "Hello, world!");
    write_string(0xF, "Hello, world!");
    write_string(0xF, "Hello, world!");
    write_string(0xF, "Hello, world!");
    write_string(0xF, "Hello, world!");
    write_string(0xF, "Hello, world!");
    write_string(0xF, "Hello, world!");
    write_string(0xF, "Hello, world!");
    write_string(0xF, "Hello, world!");
    write_string(0xF, "Hello, world!");
    write_string(0xF, "Hello, world!");
    write_string(0xF, "Hello, world!");
    write_string(0xF, "Hello, world!");
    write_string(0xF, "Hello, world!");
    

    
}
