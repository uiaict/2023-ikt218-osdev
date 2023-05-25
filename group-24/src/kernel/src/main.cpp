#include <stdio.h>
#include "system.h"
#include "screen.h"
#include "gdt.h"



extern "C"{
    void kernel_main();
}
void kernel_main()

{
    clear_screen();
    print("hello world!");
    
}
