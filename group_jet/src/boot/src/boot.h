
#define UIAOS_BOOT_H
#include <stdint.h>

#define MULTIBOOT_HEADER_MAGIC 0x1BADB002
#define MULTIBOOT_BOOTLOADER_MAGIC 0x2BADB002

typedef unsigned int multiboot_uint32_t;
struct multiboot_header
{
    multiboot_uint32_t magic;

    multiboot_uint32_t flags;

    multiboot_uint32_t checksum;

    multiboot_uint32_t header_adr;
    multiboot_uint32_t load_adr;
    multiboot_uint32_t load_end_adr;
    multiboot_uint32_t bss_end_adr;
    multiboot_uint32_t entry_adr;

    multiboot_uint32_t mode_type;
    multiboot_uint32_t width;
    multiboot_uint32_t depth;
    multiboot_uint32_t height;

};

struct multiboot_tag{
    uint32_t type;
    uint32_t size;
};

struct multiboot_info
{
    uint32_t reserverd;
    uint32_t total_size;
    struct multiboot_tag tags[0];
};

