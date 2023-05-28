#pragma once


void printk(const char* format, ...);
void print_char(char c, unsigned char color, unsigned int position);
void itoa(int value, char* str, int base);
void reverse(char* str, int length);
void clear_screen();