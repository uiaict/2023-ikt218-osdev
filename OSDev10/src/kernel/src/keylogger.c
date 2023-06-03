#include "keylogger.h"
#include "print.h"
#include "isr.h"
#include "scancode.h"

static void keylogger(){
    // Disable interupt to prevent other interupts to interfere.
    asm volatile ("cli");
    char key = scancode_to_ascii(inb(0x60));
    print_char(key);
    // Re-enable interupts.
    asm volatile ("sti");
}

void init_keylogger(){
    register_interrupt_handler(IRQ1, &keylogger);
}