#include <stdio.h>
#include <system.h>
#include "screen.h"
#include "gdt.h"




extern "C"{
    void kernal_main();
}
void kernal_main()
{
    init_gdt();
    print("hello world");

}
