#include "pit.h"
#include "isr.h"

extern "C"
{
    #include "ports.h"
    #include "../drivers/screen.h"
}

//Initializes a global variable to store the tick count.
uint32_t tick = 0;

//Defines the timer_handler function to be called by the IRQ0 handler.
static void timer_handler(registers_t regs)
{
    //Increment the tick count
    tick++;

    //Toggle the cursor on and off by XORing the cursor end register with 0x80.
    uint8_t cursor_end = inb(0x3D5);
    //Set the register index to the cursor end register.
    outb(0x3D4, 0x0B);
    //Write the XORed value to the register
    outb(0x3D5, cursor_end ^ 0x80);
}

//Function that initializes the Programmable Interval Timer (PIT) with the specified frequency
void init_pit()
{
    //Registers our timer_handler function as the handler for IRQ0
    register_interrupt_handler(IRQ0, timer_handler);

    //The value we send to the PIT is the value to divide it's input clock
    //(1193180 Hz) by, to get our required frequency. Important to note is
    //that the divisor must be small enough to fit into 16-bits.
    uint32_t divisor = DIVIDER;

    //Send the command byte to the PIT command port.
    outb(PIT_CMD_PORT, 0x36);

    //Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    uint8_t low = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)((divisor>>8) & 0xFF );

    //Send the frequency divisor bytes to the PIT channel 0 data port.
    outb(PIT_CHANNEL0_PORT, low);
    outb(PIT_CHANNEL0_PORT, high);
}

//Function that returns the current tick count.
uint32_t get_current_tick()
{
    return tick;
}

//Sleep using interrupts for the specified number of milliseconds.
void sleep_interrupt(uint32_t milliseconds)
{
    uint32_t current_tick = get_current_tick();
    uint32_t ticks_to_wait = milliseconds * TICKS_PER_MS;
    uint32_t end_ticks = current_tick + ticks_to_wait;

    //Wait for the desired number of ticks to pass
    while (current_tick < end_ticks)
    {
        //Enable interrupts and hald the cpu until the next interrupt occurs.
        asm volatile(
            "sti\n\t" 
            "hlt\n\t" 
        );
        //Update the current tick count.
        current_tick = get_current_tick();
    }
    
}

//Sleep using busy waiting for the specified number of milliseconds.
void sleep_busy(uint32_t milliseconds)
{
    uint32_t start_tick = get_current_tick();
    uint32_t ticks_to_wait = milliseconds * TICKS_PER_MS;
    uint32_t elapsed_ticks = 0;

    //Wait for the desired number of ticks to pass.
    while (elapsed_ticks < ticks_to_wait)
    {
        //Busy wait for the next tick to occur.
        while(get_current_tick() == start_tick + elapsed_ticks)
        {
            //Do nothing (busy wait)
        }
        //Increment the elapsed tick count.
        elapsed_ticks++;
    }
    
}