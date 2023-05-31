#include "terminal.h"

#include "system.h"
#include <cstddef>


static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg){
	return fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color){
	return (uint16_t) uc | (uint16_t) color << 8;
}

void terminal_clear(){
    uint16_t *screen = (uint16_t*)SCREEN_BUFFER;
	const uint8_t clear_color = vga_entry_color(VGA_COLOR_BROWN, VGA_COLOR_BLACK);
    for(size_t i = 0; i < SCREEN_HEIGHT*SCREEN_WIDTH; i++){
        screen[i] = vga_entry(' ', clear_color);
    }
	terminal_column = 0;
	terminal_row = 0;
}

void terminal_newline(){
	terminal_column = 0;
	terminal_row++;
	if(terminal_row >= SCREEN_HEIGHT){
		terminal_newpage();
	}
}

void terminal_write_char(char c){
	const uint8_t color = vga_entry_color(VGA_COLOR_BROWN,VGA_COLOR_BLACK);
	uint16_t *screen = (uint16_t*)SCREEN_BUFFER;
	uint16_t i = terminal_row * SCREEN_WIDTH + terminal_column;

	//Newline
	if(c == '\n' || terminal_column == SCREEN_WIDTH){
		terminal_newline();
		return;
	}

	//Backspace
	if(c == '\b'){
		if(terminal_column > 0){
			terminal_column--;
			i--;
			screen[i] = vga_entry(' ', color);
		}
		return;
	}

	// Write char
	terminal_column++;
	screen[i] = vga_entry(c, color);
}

bool terminal_write(const char *str){
    size_t stringLenght = strlen(str);
    for(size_t i = 0; i < stringLenght; i++ ){
		terminal_write_char(str[i]);
    }
	return true;
}

void terminal_print_title(bool full){
	terminal_write("                _____ __    _ __      ____  _____\n");
    terminal_write("               / ___// /_  (_) /_    / __ \\/ ___/\n");
    terminal_write("               \\__ \\/ __ \\/ / __/   / / / /\\__ \\\n");
    terminal_write("              ___/ / / / / / /_    / /_/ /___/ /\n");
    terminal_write("             /____/_/ /_/_/\\__/____\\____//____/\n");

	if(!full){
    	terminal_write("                             /_____/\n");
		return;
	}
	terminal_write("         ____     _          /_____/       __    _ __\n");
    terminal_write("        /  _/    (_)_  _______/ /_   _____/ /_  (_) /_\n");
    terminal_write("        / /     / / / / / ___/ __/  / ___/ __ \\/ / __/\n");
    terminal_write("      _/ /     / / /_/ (__  ) /_   (__  ) / / / / /_\n");
    terminal_write("     /___/  __/ /\\__,_/____/\\__/  /____/_/ /_/_/\\__/ __\n");
    terminal_write("   __  ____/___/_  __________     ____  ____ _____  / /______\n");
    terminal_write("  / / / / __ \\/ / / / ___/ _ \\   / __ \\/ __ `/ __ \\/ __/ ___/\n");
    terminal_write(" / /_/ / /_/ / /_/ / /  /  __/  / /_/ / /_/ / / / / /_(__  )\n");
    terminal_write(" \\__, /\\____/\\__,_/_/   \\___/  / .___/\\__,_/_/ /_/\\__/____/\n");
    terminal_write("/____/                        /_/\n\n");
}

void terminal_newpage(){
	terminal_row = 0;
	terminal_clear();
	terminal_print_title(false);
}