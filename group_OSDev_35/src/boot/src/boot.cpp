//
// Created by per on 1/4/23.
// https://github.com/perara/ikt218-advanced-operating-systems/blob/1ce6e0b734968ad952275b8bbff049b8b690c5fb/src/boot/src/boot.cpp
//
#include "boot.h"
//#include "multiboot.h"

#include <memory.h>



// make it avalibale in the asm file
void init_multiboot() asm ("init_multiboot");

extern "C" {
void init_multiboot(UiAOS::Boot::multiboot_header* mboot);
};

void init_multiboot(UiAOS::Boot::multiboot_header* mboot) {

    UiAOS::Boot::multiboot_address = reinterpret_cast<uint32_t>(mboot->header_addr);
    // memcpy(UiAOS::Boot::multiboot, &mboot, sizeof (*mboot));

    if (UiAOS::Boot::multiboot->magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        return;
    }
}