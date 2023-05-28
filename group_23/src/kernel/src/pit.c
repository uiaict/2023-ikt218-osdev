#include "../include/pit.h"
#include "../include/isr.h"
#include "../include/monitor.h"

uint32_t tick = 0;
uint32_t start_tick=0;
uint32_t tics_to_wait= 0;
static void timer_callback(registers_t regs)
{
   tick++;
   monitor_write("Tick: ");
   monitor_write_dec(tick);
   monitor_write("\n");
}

void init_timer(uint32_t frequency)
{
   // Firstly, register our timer callback.
   register_interrupt_handler(IRQ0, &timer_callback);

   // The value we send to the PIT is the value to divide it's input clock
   // (1193180 Hz) by, to get our required frequency. Important to note is
   // that the divisor must be small enough to fit into 16-bits.
   uint32_t divisor = 1193180 / frequency;

   // Send the command byte.
   outb(0x43, 0x36);

   // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
   uint8_t l = (uint8_t)(divisor & 0xFF);
   uint8_t h = (uint8_t)( (divisor>>8) & 0xFF );

   // Send the frequency divisor.
   outb(0x40, l);
   outb(0x40, h);
}
void sleep_busy(uint32_t milliseconds)
{
    start_tick = get_current_tick();
    tics_to_wait= TICKS_PER_MS * milliseconds;
    uint32_t elapsed_ticks=0;
    while(elapsed_ticks < tics_to_wait)
    {
      while(get_current_tick() == start_tick + elapsed_ticks)
      {
        //do nothing
      }
      elapsed_ticks++;
    }
}
void sleep_interrupt(uint32_t milliseconds)
{

   uint32_t current_tick = get_current_tick();
   tics_to_wait= TICKS_PER_MS * milliseconds;
    
    uint32_t end_tics=current_tick + tics_to_wait;
    while(current_tick < end_tics)
    {
      asm volatile("sti");                          // enable interrupts
      asm volatile("hlt");                          // halt the cpu
      
      current_tick = get_current_tick();
    }
}