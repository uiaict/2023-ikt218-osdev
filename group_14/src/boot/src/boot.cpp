#include "boot.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

extern "C" {
    void init_multiboot(uint32_t magic /*eax*/, multiboot_info* info /*ebx*/);
};

void init_multiboot(uint32_t magic /*eax*/, multiboot_info* info /*ebx*/){
    
}