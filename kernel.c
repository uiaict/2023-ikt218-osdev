
#include <system.h>
#include <gdt.h>/* Check if the compiler thinks you are targeting the wrong operating system. */
#include <idt.h>
#include <isr.h>
#include <terminal.h>
#include <pit.h>
#include <keyboard.h>

#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
 
void test_interrupt(){

	asm volatile("int $0x3");

}



void isr_handler(registers_t regs)
{
   terminal_writestring("recieved interrupt ");
   
   monitor_write_dec(regs.int_no);

   
 

  
} 


extern void testassembly(){

terminal_writestring("TESTTTTTT!\n");
}
void kernel_main(void) 
{
	init_gdt();
	init_idt();

	terminal_initialize();
	// terminal_writestring("Hello World!\n");
    // test_interrupt();
   
	

  
	init_keyboard();



	

// int counter=0;
// 	init_pit(100);
// 	asm volatile("sti");
// 	while(true){
		
// 		terminal_writestring("sleep_busy:");
// 		terminal_write_dec(counter++);
// 		terminal_writestring("\n");
//         sleep_busy(100000000000);
// 		terminal_writestring("sleep_interrupt:");
// 		terminal_write_dec(counter++);
// 		terminal_writestring("\n");
//         sleep_interrupt(100);
		 
	
// 	}

asm volatile("sti");

  
	
    
	

for(;;){
	asm("hlt");
};
	
	
	
	

}

//https://samypesse.gitbook.io/how-to-create-an-operating-system/chapter-6
//https://www.codeproject.com/Articles/43179/Beginning-Operating-System-Development-Part-Three
//http://www.osdever.net/bkerndev/Docs/gdt.htm
//https://stackoverflow.com/questions/718105/how-to-translate-nasm-push-byte-to-gas-syntax


