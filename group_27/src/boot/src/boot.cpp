#include "boot.h"
#include <libc/system.h>

extern void monitor_initialize();


extern "C" {
    void init_multiboot(uint32_t magic /*eax*/, multiboot_info* info /*ebx*/);
};


void init_multiboot(uint32_t magic /*eax*/, multiboot_info* info /*ebx*/){
    monitor_initialize();
    // print("\n");

    // Convert values to string
    char* eax_buf;
    char* mb_magic_buf;
    int32_to_str(eax_buf, magic);
    int32_to_str(mb_magic_buf, MULTIBOOT_BOOTLOADER_MAGIC);

    if(magic != (multiboot_uint32_t)MULTIBOOT_BOOTLOADER_MAGIC){
        while(1){
            //print("Magic number is invalid. Found: %s != %s\n",eax_buf, mb_magic_buf);
          
        }; // ERROR!
    }

    //print("Multiboot check went OK.\neax=%s, magic=%s\n", eax_buf, mb_magic_buf);
}