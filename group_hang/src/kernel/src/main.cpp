
#include "system.h"
#include "gdt.h"
// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void kernel_main()
{
    uint8_t target[8];
    struct GDT gdt = {0x100000, 0xFFFFF, 0x9A, 0xC};

    encodeGdtEntry(target, gdt);

    // Do something with the encoded GDT entry...

}