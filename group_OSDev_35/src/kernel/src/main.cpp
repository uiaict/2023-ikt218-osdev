#include "interrupt_service_routines.h"
#include "keyboard.h"
#include "common.h"

// Define entry point in asm to prevent C++ mangling
extern "C"
{
#include "system.h"

    void kernel_main();
}

void interrupt_handler_4(registers_t *regs, void * /* context */)
{
    printf("Called Interrupt Handler 4\n");
}

void interrupt_handler_5(registers_t *regs, void * /* context */)
{
    printf("Called Interrupt Handler 5\n");
}

void interrupt_handler_6(registers_t *regs, void * /* context */)
{
    printf("Called Interrupt Handler 6\n");
}

void kernel_main()
{
    // clear_terminal(); <-- moved to boot.asm

    print_logo();

    char str[] = "Hello, Wolrd!";
    printf("%s\n", str);

    register_interrupt_handler(4, interrupt_handler_4, NULL);
    register_interrupt_handler(5, interrupt_handler_5, NULL);
    register_interrupt_handler(6, interrupt_handler_6, NULL);

    

    asm volatile("int $0x4");
    asm volatile("int $0x5");
    asm volatile("int $0x6");

    printf("\n------------------------\n\n");

    
    init_keyboard();


    // printf("End\n");
}
