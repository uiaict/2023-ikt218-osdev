
#include <system.h>
#include <gdt.h>/* Check if the compiler thinks you are targeting the wrong operating system. */
#include <idt.h>
#include <isr.h>
#include <terminal.h>
#include <pit.h>
#include <keyboard.h>
#include <memory.h>
#include <stddef.h>
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
 

void test_interrupt(){

	asm volatile("int $0x0");
	asm volatile("int $0x1");
	asm volatile("int $0x2");
	asm volatile("int $0x3");
	


}
//Sources: 
//https://samypesse.gitbook.io/how-to-create-an-operating-system/chapter-6
//https://www.codeproject.com/Articles/43179/Beginning-Operating-System-Development-Part-Three
//http://www.osdever.net/bkerndev/Docs/gdt.htm
//https://stackoverflow.com/questions/718105/how-to-translate-nasm-push-byte-to-gas-syntax
//http://www.jamesmolloy.co.uk/tutorial_html/5.-IRQs%20and%20the%20PIT.html
//http://www.jamesmolloy.co.uk/tutorial_html/6.-Paging.html 
//http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html
//http://www.jamesmolloy.co.uk/tutorial_html/3.-The%20Screen.html
// https://perara.notion.site/cc1f1290feed49b0bc2a7d79f0018220?v=0d1123923ce3440cbfbdb33dec867f4f&p=2dbf775240da488299c67828f5ce8e93&pm=s
//https://wiki.osdev.org/Bare_Bones 
//http://www.osdever.net/bkerndev/Docs/idt.htm
//http://www.osdever.net/bkerndev/Docs/gdt.htm 
//http://www.osdever.net/bkerndev/Docs/printing.htm
//http://www.osdever.net/bkerndev/Docs/isrs.htm
//http://www.osdever.net/bkerndev/Docs/irqs.htm
//http://www.osdever.net/bkerndev/Docs/pit.htm
//http://www.osdever.net/bkerndev/Docs/keyboard.htm
//https://github.com/therealdreg/x86osdev





// Overload the new operator for single object allocation
void* operator new(size_t size) {
    return malloc(size);   // Call the C standard library function malloc() to allocate memory of the given size and return a pointer to it
}

// Overload the delete operator for single object deallocation
void operator delete(void* ptr) noexcept {
    free(ptr);             // Call the C standard library function free() to deallocate the memory pointed to by the given pointer
}

// // Overload the new operator for array allocation
void* operator new[](size_t size) {
    return malloc(size);   // Call the C standard library function malloc() to allocate memory of the given size and return a pointer to it
}

// // Overload the delete operator for array deallocation
void operator delete[](void* ptr) noexcept {
    free(ptr);             // Call the C standard library function free() to deallocate the memory pointed to by the given pointer
}

// //   test_interrupt();
extern "C" uint32_t end; 
extern "C" void kernel_main(void) 
{

	terminal_initialize();
	init_kernel_memory(&end); 
	init_gdt();
	init_idt();
	init_irq();
    init_paging();
    // print_memory_layout();
	terminal_initialize();
    test_interrupt();
	

    int* memory1= new int[10];
    void* memory2 = malloc(54321);
    char* memory3 = new char[1000]();
    terminal_writestring("After allocating: \n");
    print_memory_layout();
	// terminal_writestring("After deallocating: \n");
	
    // terminal_initialize();
	// delete [] memory1; 
	// free(memory2); 
	// delete [] memory3;
	// print_memory_layout();

	// // free(memory2);
	// // delete memory3;
	//PIT functions: 
    // int counter=0;
	// init_pit();
	// asm volatile("sti");
	// while(true){
		
	// 	terminal_writestring("[");
	// 	terminal_write_dec(counter);
	// 	terminal_writestring("]: Sleeping with busy-waiting (HIGH CPU).\n");
	// 	sleep_busy(100);
	// 	terminal_writestring("[");
	// 	counter++;
	// 	terminal_write_dec(counter);
	// 	terminal_writestring("]: Slept using busy-waiting.\n");
		
	// 	terminal_writestring("[");
	// 	terminal_write_dec(counter);
	// 	terminal_writestring("]: Sleeping with interrupts (LOW CPU).\n");
	// 	sleep_interrupt(100);
	// 	counter++;
	// 	terminal_writestring("[");
	// 	terminal_write_dec(counter);
	// 	terminal_writestring("]: Slept using interrupts.\n");
	// 	terminal_writestring("\n");
        

	// }
//Keyboard: 
// init_keyboard();

// asm volatile("sti");

  
// for(;;){
// 	asm("hlt");
// };
	
		

}




