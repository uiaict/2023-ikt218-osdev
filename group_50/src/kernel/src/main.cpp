#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "gdt.h"
#include "idt.h"
#include <cstdlib>
#include <cstdint>
#include "terminal.h"
#include "pit.h"

#ifdef __cplusplus
extern "C" {
#endif
    // Pointer to the memory-mapped VGA buffer that represents the screen
    volatile uint16_t* const VGA_BUFFER = (uint16_t*) 0xB8000;

    // Constants to define the dimensions of the text module
    const size_t VGA_WIDTH = 80;
    const size_t VGA_HEIGHT = 25;

    // Initialize terminal
    void terminal_init() {
        
        for (size_t i = 0; i < VGA_HEIGHT; i++) {
            
            for (size_t j = 0; j < VGA_WIDTH; j++) {
                const size_t index = i * VGA_WIDTH + j; // Calculate index of current character
                VGA_BUFFER[index] = ' ' | 0x0700;
            }
        }
    }

    // Print string to terminal
    void terminal_write(const char* str) {
        
        size_t index = 0; // Index to keep track of current character

        while (str[index]) { // Loop until null
            
            const size_t row = index / VGA_WIDTH; // Calculate row of current character
            const size_t col = index % VGA_WIDTH; // Calculate column of current character
            const size_t vga_index = row * VGA_WIDTH + col; // Calculate index in VGA buffer for current character
            
            VGA_BUFFER[vga_index] = ((uint16_t) str[index]) | 0x0700; // Write current character to the buffer
            index++;
        }
    }

    size_t terminal_row = 0;
    size_t terminal_col = 0;

    void terminal_write_char(char c) {
        
        if (c == '\b') { // Backspace
            if (terminal_col > 0) {
                terminal_col--;
            } 
            else if (terminal_row > 0) {
                terminal_row--;
                terminal_col = VGA_WIDTH - 1;
            }
            
            const size_t index = terminal_row * VGA_WIDTH + terminal_col;
            VGA_BUFFER[index] = ((uint16_t) ' ') | 0x0700; // Overwrite with a space
        } 
        else if (c == '\n') { // Newline
            terminal_col = 0;
            terminal_row++;
        } 
        else { // Regular character
            const size_t index = terminal_row * VGA_WIDTH + terminal_col;
            VGA_BUFFER[index] = ((uint16_t) c) | 0x0700; // Write current character to the buffer

            terminal_col++;

            if (terminal_col == VGA_WIDTH) {
                terminal_col = 0;
                terminal_row++;
            }
        }

        if (terminal_row > VGA_HEIGHT) {
            terminal_init(); 
            terminal_row = 0;
            terminal_col = 0;
        }
    }
#ifdef __cplusplus
}
#endif

// Define entry point in asm to prevent C++ mangling
extern "C"{
    #include "memory.h"
    #include <system.h>
    void kernel_main();
}


extern uint32_t end; // This is defined in linker.ld

// Overload the new operator for single object allocation
void* operator new(std::size_t size) {
    return malloc(size);   // Call the C standard library function malloc() to allocate memory of the given size and return a pointer to it
}

// Overload the delete operator for single object deallocation
void operator delete(void* ptr) noexcept {
    free(ptr);             // Call the C standard library function free() to deallocate the memory pointed to by the given pointer
}

// Overload the new operator for array allocation
void* operator new[](std::size_t size) {
    return malloc(size);   // Call the C standard library function malloc() to allocate memory of the given size and return a pointer to it
}

// Overload the delete operator for array deallocation
void operator delete[](void* ptr) noexcept {
    free(ptr);             // Call the C standard library function free() to deallocate the memory pointed to by the given pointer
}

void kernel_main()
{
    terminal_init();
    terminal_write("Hello World");

    asm volatile("int $0x3");
    asm volatile("int $0x4");
    //asm volatile("int $0x5");

    init_pit();

    int counter = 0;
    
    while (true) {
        printf("[%d]: Sleeping with busy-waiting (HIGH CPU).\n", counter);
        sleep_busy(1000);
        printf("[%d]: Slept using busy-waiting.\n", counter++);

        printf("[%d]: Sleeping with interrupts (LOW CPU).\n", counter);
        sleep_interrupt(1000);
        printf("[%d]: Slept using interrupts.\n", counter++);
        
        if (counter == 20) {
            terminal_init(); 
            terminal_row = 0;
            terminal_col = 0;
            break;
        }
    };

    init_kernel_memory(&end);

    init_paging();
    
    print_memory_layout();

    void* some_memory = malloc(12345);
    void* memory2 = malloc(54321);
    void* memory3 = malloc(13331);
    char* memory4 = new char[1000]();
    
    while(true){};
}
