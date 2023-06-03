// Based on JamesM's kernel development tutorials.

#include "timer.h"
#include "print.h"
#include "isr.h"

int tick = 0;
int ticks = 0;

static void tickTack_callback(){
    // tick tack every 1000 ticks.
    if (ticks >= 1000){
        if (tick <= 0){
            print_string("Tick...\n");
            tick++;
        } else {
            print_string("Tack...\n");
            tick--;
        }
        ticks = 0;
    }
    ticks++;
}

void init_ticktack(u32int freq){
    register_interrupt_handler(IRQ0, &tickTack_callback);
    u32int divider = 1193180 / freq;

    // Split divider into two bytes
    u8int l = (u8int)(divider & 0xFF);
    u8int h = (u8int)((divider >> 8) & 0xFF);

    // Tell the timer to restart each time it reaches zero.
    outb(0x43, 0x36);
    // Set frequenzy
    outb(0x40, l);
    outb(0x40, h);
}