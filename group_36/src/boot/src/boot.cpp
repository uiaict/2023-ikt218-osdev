// #include <stdint.h>
// // #include <boot.h>

// extern "C" void init_multiboot(void* mboot_ptr) {
//     // Get a pointer to the multiboot_info structure
//     uint32_t mboot_magic = 0;
//     uint32_t* mboot_info_ptr = (uint32_t*) mboot_ptr;
//     mboot_magic = *mboot_info_ptr;
//     if (mboot_magic != 0x2BADB002) {
//         // Invalid magic number, cannot proceed
//         return;
//     }
//     // Enable paging
//     asm volatile ("movl %%cr0, %%eax; orl $0x80000000, %%eax; movl %%eax, %%cr0" : : : "eax");
//     // Jump to the kernel entry point
//     asm volatile ("jmp kernel_main");
//     // Pop the function arguments off the stack
//     asm volatile ("addl $8, %%esp" : : : "esp");
// }
