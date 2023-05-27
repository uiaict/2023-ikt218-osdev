#include "boot.h"
#include "multiboot.h"

#include <memory.h>

extern "C" {
void init_multiboot(UiAOS::Boot::multiboot_header* mboot);
};

void init_multiboot(UiAOS::Boot::multiboot_header* mboot) {

    UiAOS::Boot::multiboot_address = reinterpret_cast<uint32_t>(mboot->header_addr);
    memcpy(UiAOS::Boot::multiboot, &mboot, sizeof (*mboot));

    if (UiAOS::Boot::multiboot->magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        return; // TODO get some error msg
        /*
         * UiAOS::IO::Monitor::print_string("Invalid magic number: ");
        UiAOS::IO::Monitor::print_int((unsigned) mboot->magic);
        UiAOS::IO::Monitor::print_string(". Should be: ");
        UiAOS::IO::Monitor::print_int((unsigned) MULTIBOOT_BOOTLOADER_MAGIC);
        UiAOS::IO::Monitor::print_new_line();
         */
    }
}
