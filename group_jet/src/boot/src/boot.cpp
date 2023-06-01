#include "boot.h"
#include "system.h"


extern "C" {
    void init_multiboot(uint32_t magic /*eax*/, multiboot_info* info /*ebx*/);
};
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer; 

void init_multiboot(uint32_t magic /*eax*/, multiboot_info* info /*ebx*/){
    terminal_initialize();
    

    char* eax_buf;
    char* mb_magic_buf;
    int32_to_str(eax_buf, magic);
    int32_to_str(mb_magic_buf, MULTIBOOT_BOOTLOADER_MAGIC);
    
    if (magic != (multiboot_uint32_t)MULTIBOOT_BOOTLOADER_MAGIC){
        while(1){
            terminal_writestring("Magic number is invalid\n");
        };
    }
    terminal_writestring("Multiboot check went OK.\n");
}