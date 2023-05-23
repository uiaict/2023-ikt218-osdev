//
// Created by per on 12/30/22.
//

#ifndef IKT218_ADVANCED_OPERATING_SYSTEM_TERMINAL2_H
#define IKT218_ADVANCED_OPERATING_SYSTEM_TERMINAL2_H

#include <stdint.h>

#define VGA_ADDRESS 0xB8000
#define BUFSIZE 2200


namespace UiAOS::IO{

    class VGA{
    public:
        VGA(vga_color color);


        void init_vga(uint8_t fore_color, uint8_t back_color);
        void clear_screen(uint8_t fore_color, uint8_t back_color);
        void print_string(char *str);
        void print_new_line();
        void print_color_string(char *str, uint8_t fore_color, uint8_t back_color);
        void print_char(char ch);
        void print_int(int num);

    public:
        uint16_t* vga_buffer;
        uint32_t vga_index;

        void clear_vga_buffer(uint16_t **buffer, uint8_t fore_color, uint8_t back_color);
        uint16_t vga_entry(unsigned char ch, uint8_t fore_color, uint8_t back_color);
    };
}





#endif //IKT218_ADVANCED_OPERATING_SYSTEM_TERMINAL2_H
