#include <stdint.h>

void clear_screen();
void write_string( int line, int column, int colour, const char *string );
void print_pattern(const char* pattern[], int num_lines, int start_pos);