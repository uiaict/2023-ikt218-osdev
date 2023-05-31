#include "interrupt_service_routines.h"
#include "keyboard.h"

// Define entry point in asm to prevent C++ mangling
extern "C"
{
#include "system.h"

    void kernel_main();
}

void interrupt_handler_1(registers_t *regs, void * /* context */)
{
    printf("Called Interrupt Handler 1\n");
}

void interrupt_handler_2(registers_t *regs, void * /* context */)
{
    printf("Called Interrupt Handler 2\n");
}

void interrupt_handler_3(registers_t *regs, void * /* context */)
{
    printf("Called Interrupt Handler 3\n");
}

void kernel_main()
{
    // clear_terminal(); <-- moved to boot.asm

    print_logo();

    char str[] = "Hello, Wolrd!";
    printf("%s\n", str);

    // register_interrupt_handler(1, interrupt_handler_1, NULL);
    register_interrupt_handler(2, interrupt_handler_2, NULL);
    register_interrupt_handler(3, interrupt_handler_3, NULL);

    // asm volatile("int $0x1");
    // asm volatile("int $0x2");
    // asm volatile("int $0x3");

    register_interrupt_handler(1, keyboard_handler, NULL);

    asm volatile("int $0x1");
    // printf("End\n");
}
