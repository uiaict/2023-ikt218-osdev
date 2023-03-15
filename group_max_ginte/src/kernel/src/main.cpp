#include "system.h"
#include "descriptor_tables.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void kernel_main()
{
    printf("Hello World!");
    printf("    Hello World!");


    init_gdt();
    
    printf("        Hello World!");
    /*printf("SYSTEM COMPROMISED.\n"
           "SHUTTING DOWN... SHUTTING DOWN... \tSHUTTING DOWN... SHUTTING DOWN... SHUTTI\tN\n"
           "G DOWN... SHUTTING DOWN... SHUTTING\t\t DOWN... SHUTTING DOWN... \n"
           "SHUTTING DOWN...\n"
           "SHUTTING DOWN...\n"
           "SHUTTING DOWN...\n"c
           "SHUTTING DOWN...\n");*/
}
