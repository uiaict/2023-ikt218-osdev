
#include "system.h"


// VGA Text mode buffer starting address
//uint16_t *vga_buffer = (uint16_t *)0xB8000;

// Define a function to write a single character to the VGA buffer
//void vga_putc(char c, uint8_t color, size_t x, size_t y) {
    // Calculate the index in the VGA buffer for the given x and y
 //   size_t index = (y * 80) + x;
//
    // Combine the character with the color attribute
  //  uint16_t vga_char = ((uint16_t)color << 8) | (uint16_t)c;

    // Write the combined value to the VGA buffer
    //vga_buffer[index] = vga_char;
//}


// Define entry point in asm to prevent C++ mangling

extern "C"{
    void kernel_main();
}

void kernel_main()
{
int a = 2;


a = a + 2;
while(1000){
    a = a + 1;
}
a = 2;

// Set the color you want to use for the text
    //uint8_t color = 0x0F; // White text on black background

    // Write "Hello, World!" to the screen
    //const char *str = "Hello, World!";
   // for (size_t i = 0; str[i] != '\0'; ++i) {
//vga_putc(str[i], color, i, 0);
    }

    // Halt the CPU
    //for (;;) {
    //    __asm__("hlt");
    //}
//}
