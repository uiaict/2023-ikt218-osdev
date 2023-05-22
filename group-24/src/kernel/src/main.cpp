#include <stdio.h>
#include <system.h>
#include "../include/screen.h"
#include "../gdt/gdt.h"




extern "C"{
    void kernal_main();
}
void kernal_main()
{
    init_gdt();
    clear_screen();
    print("hello world!");
}
