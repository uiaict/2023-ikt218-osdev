//
// Created by per on 12/30/22.
//
#include "monitor.h"
#include <math.h>



static uint32_t next_line_index = 1;
uint8_t g_fore_color = WHITE, g_back_color = BLUE;

UiAOS::IO::VGA::VGA(vga_color color){
    init_vga(WHITE, color);
}


uint16_t UiAOS::IO::VGA::vga_entry(unsigned char ch, uint8_t fore_color, uint8_t back_color)
{
    uint16_t ax = 0;
    uint8_t ah = 0, al = 0;

    ah = back_color;
    ah <<= 4;
    ah |= fore_color;
    ax = ah;
    ax <<= 8;
    al = ch;
    ax |= al;

    return ax;
}

void UiAOS::IO::VGA::clear_vga_buffer(uint16_t **buffer, uint8_t fore_color, uint8_t back_color)
{
    uint32_t i;
    for(i = 0; i < BUFSIZE; i++){
        (*buffer)[i] = vga_entry(0, fore_color, back_color);
    }
    next_line_index = 1;
    vga_index = 0;
}



void UiAOS::IO::VGA::init_vga(uint8_t fore_color, uint8_t back_color)
{
    vga_buffer = (uint16_t*)VGA_ADDRESS;
    clear_vga_buffer(&vga_buffer, fore_color, back_color);
    g_fore_color = fore_color;
    g_back_color = back_color;
}

void UiAOS::IO::VGA::clear_screen(uint8_t fore_color, uint8_t back_color)
{
    clear_vga_buffer(&vga_buffer, fore_color, back_color);
}

void UiAOS::IO::VGA::print_new_line()
{
    if(next_line_index >= 55){
        next_line_index = 0;
        clear_vga_buffer(&vga_buffer, g_fore_color, g_back_color);
    }
    vga_index = 80*next_line_index;
    next_line_index++;
}

void UiAOS::IO::VGA::print_char(char ch)
{
    vga_buffer[vga_index] = vga_entry(ch, g_fore_color, g_back_color);
    vga_index++;
}

void UiAOS::IO::VGA::print_string(char *str)
{
    uint32_t index = 0;
    while(str[index]){
        print_char(str[index]);
        index++;
    }
}

void UiAOS::IO::VGA::print_color_string(char *str, uint8_t fore_color, uint8_t back_color)
{
    uint32_t index = 0;
    uint8_t fc, bc;
    fc = g_fore_color;
    bc = g_back_color;
    g_fore_color = fore_color;
    g_back_color = back_color;
    while(str[index]){
        print_char(str[index]);
        index++;
    }
    g_fore_color = fc;
    g_back_color = bc;
}

void UiAOS::IO::VGA::print_int(int num)
{

}