#include "gdt.h"
#include "terminal.h"
#include "system.h"
#include "../interrupts/idt.h"
#include "../interrupts/isr.h"
#include "../interrupts/irq/irq.h"

//assignment 4
#include "../include/paging/paging.h"     // Assuming init_paging() is declared in this header file
#include "../include/memory/memory.h"     // Assuming print_memory_layout() and init_kernel_memory() are declared in this header file
#include "../include/pit/pit.h"        // Assuming init_pit() is declared in this header file


//assignment 4
extern uint32_t end; // This is defined in linker.ld


/*
// Overload the new operator for single object allocation
void* operator new(size_t size) {
return malloc(size); // Call the C standard library function malloc() to allocate memory of the given size and return a pointer
}
// Overload the delete operator for single object deallocation
void operator delete(void* ptr) noexcept {
free(ptr); // Call the C standard library function free() to deallocate the memory pointed to by the given pointer
}
// Overload the new operator for array allocation
void* operator new[](size_t size) {
return malloc(size); // Call the C standard library function malloc() to allocate memory of the given size and return a pointer
}
// Overload the delete operator for array deallocation
void operator delete[](void* ptr) noexcept {
free(ptr); // Call the C standard library function free() to deallocate the memory pointed to by the given pointer
}

*/












// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}


void delay(int count) {
    volatile int temp;
    for (int i = 0; i < count * 100000; ++i) {
        temp = i;
    }
}


void enable_interrupts() {
    asm volatile ("sti");
}

// Initialize the PS/2 keyboard
void init_keyboard() {
    // Disable devices
    outb(0x64, 0xAD);
    outb(0x64, 0xA7);

    // Flush output buffer
    while(inb(0x64) & 0x1) {
        inb(0x60);
    }

    // Enable first PS/2 port
    outb(0x64, 0xAE);

    // Enable scanning, but first check if keyboard is ready to receive a command
    //while(inb(0x64) & 0x2); // Wait until bit 1 of status register is 0
    outb(0x60, 0xF4); // Send command to keyboard command port
}





void kernel_main()
{

// Initialize kernel memory manager with the end of the kernel image
//init_memory(); // <------ THIS IS PART OF THE ASSIGNMENT

init_gdt();
terminal_initialize();
remap_pic();
// Enable keyboard
//outb(0x60, 0xF4);
idt_init(); // Initialize the IDT for interrupt
init_keyboard();



// Initialize Paging
//init_paging(); // <------ THIS IS PART OF THE ASSIGNMENT
// Print memory layout
//print_memory_layout(); // <------ THIS IS PART OF THE ASSIGNMENT


// Setup PIT
//init_pit(); // <------ THIS IS PART OF THE ASSIGNMENT
// Allocate some memory using kernel memory manager
// THIS IS PART OF THE ASSIGNMENT


/*
void* block1 = malloc(123);
void* block2 = malloc(123);

char buffer[50];
int size = print_int(buffer, (int)block2);
terminal_write(buffer, size);
terminal_write("\n\n", 3);

free(block2);

void* block3 = malloc(123);
size = print_int(buffer, (int)block3);
terminal_write(buffer, size);



void* some_memory = malloc(12345);
void* memory2 = malloc(54321);
void* memory3 = malloc(13331);
char* memory4 = new char[1000]();

*/





scancode_to_ascii[0x1E] = 'a';
scancode_to_ascii[0x30] = 'b';
scancode_to_ascii[0x2E] = 'c';
scancode_to_ascii[0x20] = 'd';
scancode_to_ascii[0x12] = 'e';
scancode_to_ascii[0x21] = 'f';
scancode_to_ascii[0x22] = 'g';
scancode_to_ascii[0x23] = 'h';
scancode_to_ascii[0x17] = 'i';
scancode_to_ascii[0x24] = 'j';
scancode_to_ascii[0x25] = 'k';
scancode_to_ascii[0x26] = 'l';
scancode_to_ascii[0x32] = 'm';
scancode_to_ascii[0x31] = 'n';
scancode_to_ascii[0x18] = 'o';
scancode_to_ascii[0x19] = 'p';
scancode_to_ascii[0x10] = 'q';
scancode_to_ascii[0x13] = 'r';
scancode_to_ascii[0x1F] = 's';
scancode_to_ascii[0x14] = 't';
scancode_to_ascii[0x16] = 'u';
scancode_to_ascii[0x2F] = 'v';
scancode_to_ascii[0x11] = 'w';
scancode_to_ascii[0x2D] = 'x';
scancode_to_ascii[0x15] = 'y';
scancode_to_ascii[0x2C] = 'z';



terminal_write("\nHello World!\n", 15);

terminal_write("Press a key...\n", 15);

enable_interrupts();

//asm volatile("int $0x21");

/*
// Free allocated memory
    free(some_memory);
    free(memory2);
    free(memory3);
    delete[] memory4;

*/


//This is for testing the PIT
/*
int counter = 0;
while(true){
    printfun("[%d]: Sleeping with busy-waiting (HIGH CPU).\n", counter);
    sleep_busy(1000);
    printfun("[%d]: Slept using busy-waiting.\n", counter++);
    printfun("[%d]: Sleeping with interrupts (LOW CPU).\n", counter);
    sleep_interrupt(1000);
    printfun("[%d]: Slept using interrupts.\n", counter++);
};
*/





// Manually trigger interrupts
    //asm volatile ("int $0");   // Divide by Zero Exception

    //asm volatile ("int $3");   // Software Breakpoint Exception

    //asm volatile ("int $4");   // User-defined Software Interrupt  

}
