#include <stdbool.h>
#include <stddef.h>
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "drivers/keyboard.h"
#include "drivers/screen.h"

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
	asm volatile("sti");
	//load_timer(50);
	load_keyboard();


	//asm volatile ("int $0x3");
	//asm volatile ("int $0x4");

	while(1)
	{

	}
} 