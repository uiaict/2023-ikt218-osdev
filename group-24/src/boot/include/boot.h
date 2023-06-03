#ifndef UIAOS_BOOT_H
#define UIAOS_BOOT_H


#include <stdint.h>
/* The magic field should contain this.  */
#define MULTIBOOT_HEADER_MAGIC			0x1BADB002

/* This should be in %eax.  */
#define MULTIBOOT_BOOTLOADER_MAGIC		0x2BADB002

typedef unsigned int multiboot_uint32_t;
struct multiboot_header
{
    /* Must be MULTIBOOT_MAGIC - see above.  */
    multiboot_uint32_t magic;

    /* Feature flags.  */
    multiboot_uint32_t flags;

    /* The above fields plus this one must equal 0 mod 2^32. */
    multiboot_uint32_t checksum;

    /* These are only valid if MULTIBOOT_AOUT_KLUDGE is set.  */
    multiboot_uint32_t header_addr;
    multiboot_uint32_t load_addr;
    multiboot_uint32_t load_end_addr;
    multiboot_uint32_t bss_end_addr;
    multiboot_uint32_t entry_addr;

    /* These are only valid if MULTIBOOT_VIDEO_MODE is set.  */
    multiboot_uint32_t mode_type;
    multiboot_uint32_t width;
    multiboot_uint32_t height;
    multiboot_uint32_t depth;
};

struct multiboot_tag {
    uint32_t type;
    uint32_t size;
};

struct multiboot_info {
    uint32_t total_size;
    uint32_t reserved;
    struct multiboot_tag tags[0];
};

extern multiboot_header multiboot;

#endif //UIAOS_BOOT_H