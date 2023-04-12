
#include "printing.h"
#include "gdt.h"
#include "idt.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}
 
// Code from https://wiki.osdev.org/Bare_Bones#Writing_a_kernel_in_C
 
void kernel_main(void) 
{
	clear_terminal();
    //print_logo();
	asm volatile ("int $0x3");
	asm volatile ("int $0x4");
}