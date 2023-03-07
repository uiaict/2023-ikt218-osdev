#include "boot.asm"
#include "multiboot.h"

#include <memory.h>

extern "C" {
void init_multiboot(UiaOS::Boot::multiboot_header* mboot);
};

void init_multiboot(Asak::Boot::multiboot_header* mboot) {
    Asak::Boot::multiboot_address = reinterpret_cast<uint32_t>(mboot->header_addr);
    memcpy(Asak::Boot::multiboot, &mboot, sizeof (*mboot));

    if (Asak::Boot::multiboot->magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        return;
    }
}