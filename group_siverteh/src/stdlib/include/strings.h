#include "system.h"

//Function for getting the length of a string.
size_t strlen(const char *s);
//Function for turning an int into a string.
void int_to_string(char* str, int num);
//Function for turning a float into a string.
void float_to_string(char* str, float f, int precision);
//Function to check if a character is a number or letter of the alphabet.
int isalnum(int c);
//Function for turning a string to uppercase.
void to_upper(char* str);
//Function for turning a string to lowercase.
void to_lower(char* str);
//Function that checks if a character is uppercase.
int isupper(int c);
//Function that checks if a character is lowercase.
int islower(int c);