//
// Created by per on 1/4/23.
//

#ifndef UIAOS_BOOT_H
#define UIAOS_BOOT_H


#include <stdint.h>

namespace UiAOS::Boot{
    typedef unsigned int		multiboot_uint32_t;
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


    static uint32_t multiboot_address;
    static multiboot_header* multiboot;
}




#endif //UIAOS_BOOT_H
