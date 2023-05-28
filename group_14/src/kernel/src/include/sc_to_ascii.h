#ifndef SC_TO_ASCII_H
#define SC_TO_ASCII_H

#define TABLE_SIZE 141

extern unsigned char scancode_table[TABLE_SIZE];
extern unsigned char ascii_table[TABLE_SIZE];

// Convert scancode to ascii
char scancode_to_ascii(unsigned char scancode);
#endif // SC_TO_ASCII_H