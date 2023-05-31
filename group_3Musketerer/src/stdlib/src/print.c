#include "print.h"

static const size_t COL_SIZE = 80;
static const size_t ROW_SIZE = 25;

struct Char {
    uint8_t character;
    uint8_t color;
};

size_t column = 0;
size_t row = 0;
struct Char* terminal_buffer = (struct Char*) 0xB8000;
uint8_t color = COLOR_WHITE | COLOR_BLACK;


void clear_row(size_t Row){
    struct Char empty = (struct Char) {
        character: ' ',
        color: color,
    };

    for(size_t col = 0; col < COL_SIZE; col++){
        terminal_buffer[col + COL_SIZE * Row] = empty;
    }
}

void newline(){
    column = 0;

    if(row < ROW_SIZE - 1){
        row++;
        return;
    }
    
    for(size_t Row = 1; Row < ROW_SIZE; Row++){
        for(size_t col = 0; col < COL_SIZE; col++){
            struct Char character = terminal_buffer[col + COL_SIZE * Row];
            terminal_buffer[col + COL_SIZE * (Row - 1)] = character;
        }
    }

    clear_row(COL_SIZE - 1);
}

void print_char(const char c){
    if(c == '\n'){
        newline();
        return;
    }

    if(column > COL_SIZE){
        newline();
    }

    terminal_buffer[column + COL_SIZE * row] = (struct Char){
        character: (uint8_t) c,
        color: color,
    };

    column++;
}


size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

void print_str(const char* str){
    for(size_t i = 0; i < strlen(str); i++){
        char character = (uint8_t) str[i];

        if(character == '\0'){
            return;
        }

        print_char(character);
    }
}



void print_clear(){
    for(size_t i = 0; i < ROW_SIZE; i++){
        clear_row(i);
    }
}