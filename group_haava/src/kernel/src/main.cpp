#include "gdt.h"
#include "interrupts.h"
#include "keyboard.h"
#include "memory.h"
#include "pit.h"
#include "system.h"
#include "vga.h"


#define MULTIBOOT_BOOTLOADER_MAGIC 0x2BADB002

// Defined in 'linker.ld'
extern uint32_t end;

void* operator new(size_t size)
{
    return malloc(size);
}

// Overload the delete operator for single object deallocation
void operator delete(void* ptr) noexcept
{
    free(ptr);
}

// Overload the new operator for array allocation
void* operator new[](size_t size)
{
    return malloc(size);
}

// Overload the delete operator for array deallocation
void operator delete[](void* ptr) noexcept
{
    free(ptr);
}

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main(unsigned long magic);
}

void kernel_main(unsigned long magic)
{
    vga_init();
    kernel_memory_init(&end);
    gdt_init();
    idt_init();
    irq_init();
    paging_init();
    print_memory_layout();
    keyboard_init();
    pit_init();

    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        printf("Invalid magic number\n");
        return;
    }

    void* some_memory = malloc(12345);
    void* memory2 = malloc(54321);
    void* memory3 = malloc(13331);
    char* memory4 = new char[1000]();

    printf("Hello world\n");

    register_interrupt_handler(3,[](struct registers* regs){
        printf("Interrupt 3 - OK\n");
    });

    register_interrupt_handler(4,[](struct registers* regs){
        printf("Interrupt 4 - OK\n");
    });

    __asm__ __volatile__("int $0x3");
    __asm__ __volatile__("int $0x4");
    __asm__ __volatile__("int $0x7");

    // Print a message and enter an infinite loop to wait for interrupts
    int counter = 0;
    printf("Waiting...\n");
    while(true) {
        printf("[%d]: Sleeping with busy-waiting (HIGH CPU).\n", counter);
        sleep_busy(2000);
        printf("[%d]: Slept using busy-waiting.\n", counter++);

        printf("[%d]: Sleeping with interrupts (LOW CPU).\n", counter);
        sleep_interrupt(2000);
        printf("[%d]: Slept using interrupts.\n", counter++);
    }
}
