#ifndef UIAOS_BOOT_H
#define UIAOS_BOOT_H

// Include standard library for fixed width integer types
#include <stdint.h>

// Define multiboot bootloader magic number, a constant often used in bootloader code
#define MULTIBOOT_BOOTLOADER_MAGIC 0x2BADB002

namespace UiAOS::Boot{

    // Define a new type alias for unsigned integer
    typedef unsigned int multiboot_uint32_t;

    struct multiboot_header
    {
        // Magic number for the multiboot header
        multiboot_uint32_t magic;

        // Flags for various options and configurations
        multiboot_uint32_t flags;

        // Checksum, used to verify data integrity
        multiboot_uint32_t checksum;

        // Header address of the multiboot bootloader
        multiboot_uint32_t header_addr;

        // Start of load address in memory
        multiboot_uint32_t load_addr;

        // End of load address in memory
        multiboot_uint32_t load_end_addr;

        // End of BSS (Block Started by Symbol) segment
        multiboot_uint32_t bss_end_addr;

        // Entry address where control is transferred from the bootloader
        multiboot_uint32_t entry_addr;

        // Mode type for the display
        multiboot_uint32_t mode_type;

        // Width of the display in pixels
        multiboot_uint32_t width;

        // Height of the display in pixels
        multiboot_uint32_t height;

        // Depth of the display (color depth) in bits per pixel
        multiboot_uint32_t depth;
    };

    // Static variable for the multiboot address
    static uint32_t multiboot_address;

    // Static variable for the multiboot header
    static multiboot_header* multiboot;
}

// End of prevention for multiple inclusions of this header file
#endif
