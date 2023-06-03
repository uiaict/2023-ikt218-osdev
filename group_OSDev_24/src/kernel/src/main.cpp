#include <stdio.h>
#include "system.h"
#include "screen.h"
#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "common.h"
#include "keyboard.h"

extern uint32_t end;



extern "C"{
    void kernel_main();
}


void kernel_main()
{
    //init_gdt();
    init_idt();
    init_irq();
    clear_screen();
    print("hello world!");
    
    asm volatile("sti");

	//Initialize the keyboard.
	init_keyboard();
    while(1){};

 
}
