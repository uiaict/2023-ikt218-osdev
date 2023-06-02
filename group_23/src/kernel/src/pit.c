#include "../include/pit.h"
#include "../include/isr.h"
#include "../include/monitor.h"
#include "../include/common.h"
#include "../include/descriptor_tables.h"

u32int tick = 0;
void timer_phase(uint32_t frequency)
{
   // The value we send to the PIT is the value to divide it's input clock
    // (1193180 Hz) by, to get our required frequency. Important to note is
    // that the divisor must be small enough to fit into 16-bits.
    u32int divisor = 1193180 / frequency;
   
   //command byte 0x36 (mode 3: square wave generator) sent to 0x43 port
   outb(0x43, 0x36);

    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    u8int low = (u8int)(divisor & 0xFF);                           
    u8int hight = (u8int)( (divisor>>8) & 0xFF );

   

    // Send the frequency divisor.
    outb(0x40, low);
    outb(0x40, hight);

}

static void timer_callback(registers_t regs)
{
   tick++;
   if(tick % 100 == 0)
   {
      monitor_put('\n');
      monitor_write("Tick");
      monitor_put("\n");
   }
   
}



void init_timer()
{
   
    // register our timer callback.
    register_interrupt_handler(IRQ0, &timer_callback);

   
}
void sleeping_busy(uint32_t sleep_tick)
{
   uint32_t start_tick = tick + sleep_tick;
   while(tick < start_tick)                 // loop until input sleep_tick is reached
   {
      monitor_write("Sleeping");
   }
}
// sleeping with interrupts
void sleeping_interrupts(uint32_t interrupt_tick)
{
   uint32_t start_tick = tick + interrupt_tick;
   while(tick < start_tick)                 // loop until input sleep_tick is reached
   {
      asm volatile("sti");                  // enable interrupts
      asm volatile("hlt");                  // halt CPU until next interrupt
      monitor_write("Sleeping");
   }
}
