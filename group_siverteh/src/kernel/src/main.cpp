#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "gdt.h"
#include "idt.h"



// Define entry point in asm to prevent C++ mangling
extern "C"
{
	#include "system.h"
	#include "print.h"
	#include "strings.h"
    void kernel_main();
}

 
void kernel_main() 
{
	//Loads the GDT and the IDT.
    load_gdt();
	//load_idt();
	
	print("Hello, World!");
}