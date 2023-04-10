#include "system.h"
#include "vga.h"


#define MULTIBOOT_BOOTLOADER_MAGIC 0x2BADB002


// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main(unsigned long magic);
}

void kernel_main(unsigned long magic)
{
    vga_init();
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        printf("Invalid magic number\n");
        return;
    }
}
