#include "pit.h"
#include "interrupts.h"
#include "common.h"


#include <stdint.h>
#include <stdbool.h>


uint32_t tick = 0;

static void timer_callback(registers_t regs)
{
   tick++;
}

void init_pit(){
 register_interrupt_handler(IRQ0, &timer_callback);

  // Send the command byte.
   outb(0x43, 0x36);

   // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
   uint8_t l = (u8int)(DIVIDER & 0xFF);
   uint8_t h = (u8int)( (DIVIDER>>8) & 0xFF );

   // Send the frequency divisor.
   outb(0x40, l);
   outb(0x40, h);
}

uint8_t get_current_tick(){
    return tick;
}


void sleep_busy(uint32_t milliseconds){
    int start_tick = get_current_tick();
    int ticks_to_wait = milliseconds * TICKS_PER_MS;
    int elapsed_ticks = 0;

    while (elapsed_ticks < ticks_to_wait)
    {
        while (get_current_tick() == start_tick + elapsed_ticks)
        {
           //i. Do nothing (busy wait)
        }
        elapsed_ticks++
    }
    
}

void sleep_interrupt(uint32_t milliseconds){
    int current_tick = get_current_tick();
    int ticks_to_wait = milliseconds * TICKS_PER_MS;
    int end_ticks = current_tick + ticks_to_wait;

    while (current_tick < end_ticks)
    {
        asm volatile("sti")
        asm volatile("hlt")

        current_tick = get_current_tick()
    }
    
}