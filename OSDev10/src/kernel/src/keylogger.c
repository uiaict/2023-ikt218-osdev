#include "keylogger.h"
#include "monitor.h"
#include "isr.h"
#include "scancode.h"

static void logger_callback(){
    asm volatile ("cli");
    char key = scancode_to_ascii(inb(0x60));
    monitor_put(key);
    asm volatile ("sti");
}

void init_keylogger(){
    register_interrupt_handler(IRQ1, &logger_callback);

}