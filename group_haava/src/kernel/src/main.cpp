#include "system.h"


#define MULTIBOOT_BOOTLOADER_MAGIC 0x2BADB002


// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main(unsigned long magic);
}

void kernel_main(unsigned long magic)
{
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        // Invalid multiboot signature
        return;
    }
}
