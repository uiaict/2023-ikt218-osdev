
#include "system.h"
#include "gdt.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}
 
static const size_t VGA_WIDTH = 80; // defalut columns
static const size_t VGA_HEIGHT = 25; // defalut rows
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
// Code from https://wiki.osdev.org/Bare_Bones#Writing_a_kernel_in_C

void clear_terminal(void) 
{
	terminal_row = 0;  // start in the upper left corner in the canvas/terminal
	terminal_column = 0; // start in the upper left corner
	terminal_color = 7;     // 7 = VGA_COLOR_LIGHT_GREY
	terminal_buffer = (uint16_t*) 0xB8000;  // VGA text mode buffer 
	for (size_t y = 0; y < VGA_HEIGHT; y++) {   // looping through terminal window 
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x; // find position 
			terminal_buffer[index] = vga_entry(' ', terminal_color); // coloring 
		}
	}
}

int row = 3; // is 3 instead of 0, becaouse we wanted to have some space in the top of the terminal

void print(char word[80])
{

	int column = 1; 
	int color = 0;

    uint8_t (*fb)[80][2] = (uint8_t (*)[80][2]) 0xb8000; // The text screen video memory for colour monitors

    int wordlen = 0;

    while(word[wordlen] != '\0' ){
        wordlen++; // set wordlength
    }
	

    for(int i = 0; i < wordlen; i++){
	
		if(word[i] == '\n' || column == VGA_WIDTH) { // check if string include new line command and if the column is on max width
			column = 0; 					 // set column at 0 again to start printing from left
			row = row + 1;					// set new row
		} else {

        	fb[row][column][color] = word[i]; // first parameter: row, second: column, third: color.
		}

		column = column + 1;
    }
}

void print_logo() {

print("                         _________ _______    _______  _______\n"
"                |\\     /|\\__   __/(  ___  )  (  ___  )(  ____ \\\n"
"                | )   ( |   ) (   | (   ) |  | (   ) || (    \\/\n"
"                | |   | |   | |   | (___) |  | |   | || (_____ \n"
"                | |   | |   | |   |  ___  |  | |   | |(_____  )\n"
"                | |   | |   | |   | (   ) |  | |   | |      ) |\n"
"                | (___) |___) (___| )   ( |  | (___) |/\\____) |\n"
"                (_______)\\_______/|/     \\|  (_______)\\_______)\n"
"            By Markus Hagli, Charlotte Thorjussen, Nikolai Eidsheim");
}
 
void kernel_main(void) 
{
	clear_terminal();

    print_logo();
}