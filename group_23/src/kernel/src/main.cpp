#include "system.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "gdt.h"
//#include "monitor/monitor.h"

void clear_screen(int background_color) {
    volatile char *video = (volatile char *)0xB8000; //pointer to video memory adress 0xB8000
    const int screen_size = 80 * 25; // total number of characters on screen

    for (int i = 0; i < screen_size; i++) { //loop through all characters
        *video++ = ' '; // Fill with space
        *video++ = background_color; // Fill with background color
    }
}
void write_string( int colour, const char *string )
{
    volatile char *video = (volatile char*)0xB8000;
    while( *string != 0 )
    {
        *video++ = *string++;
        *video++ = colour;
    }
}


// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}
extern "C"{
    void gdt_init();
}
extern "C"{
    bool check_gdt_init();
}

void kernel_main()
{
    
    int terminal_colors = 0x0F; //  black background (0x0) and white text (0xF)
    clear_screen(terminal_colors);
    write_string(terminal_colors, "Hello, World!");
	
    gdt_init();
    check_gdt_init(); 
    while (true);
    
}