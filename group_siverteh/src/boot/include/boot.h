#include <cstdint>

// The magic number is used by the bootloader to identify a valid multiboot header.
#define MULTIBOOT_HEADER_MAGIC 0x1BADB002

#define MULTIBOOT_BOOTLOADER_MAGIC 0x2BADB002

// The flags are used to indicate what information the kernel provides to the bootloader.
#define MULTIBOOT_HEADER_FLAGS 0x00000003 // BIT 0: ALIGNMENT REQUIRED, BIT 1: MEMORY INFO

// The checksum is a 32-bit value that is used to verify the integrity of the header.
#define MULTIBOOT_HEADER_CHECKSUM -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

typedef unsigned int multiboot_uint32_t;
struct multiboot_header {
    multiboot_uint32_t magic;     // The magic number that identifies a valid multiboot header.
    multiboot_uint32_t flags;     // The flags that indicate what information the kernel provides to the bootloader.
    multiboot_uint32_t checksum;  // The checksum used to verify the integrity of the header.

    // Optional fields
    multiboot_uint32_t header_addr;  // The physical address of the header.
    multiboot_uint32_t load_addr;    // The physical address where the kernel image should be loaded.
    multiboot_uint32_t load_end_addr;// The physical address of the end of the kernel image.
    multiboot_uint32_t bss_end_addr; // The physical address of the end of the uninitialized data section.
    multiboot_uint32_t entry_addr;   // The virtual address of the entry point of the kernel.


    multiboot_uint32_t mode_type;    // The video mode to use when booting the kernel.
    multiboot_uint32_t width;        // The width of the video mode.
    multiboot_uint32_t height;       // The height of the video mode.
    multiboot_uint32_t depth;        // The color depth of the video mode.
};

struct multiboot_tag
{
    uint32_t type;
    uint32_t size;
};

struct multiboot_info
{
    uint32_t total_size;
    uint32_t reserved;
};
