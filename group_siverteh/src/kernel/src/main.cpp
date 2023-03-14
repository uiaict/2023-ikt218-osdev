#include <stdbool.h>
#include <stddef.h>
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "drivers/keyboard.h"
#include "drivers/screen.h"
#include "ports.h"

// Define entry point in asm to prevent C++ mangling
extern "C"
{
    void kernel_main();
}

void kernel_main() 
{
	//Loads the GDT and the IDT.
    load_gdt();
	load_idt();
	load_timer(1);
	asm volatile("sti");
	load_keyboard();


	while(1){}
} 