#include "pit.h"
#include "../../GDT/isr.h"
uint32_t start_tick = 0;
uint32_t get_current_tick = 0;
uint32_t current_tick = 0;
uint32_t end_tick = 0;


void init_pit(){
    
    UiAOS::CPU::ISR::register_interrupt_handler(IRQ0,[] (UiAOS::CPU::ISR::registers_t* regs, void* context){
        current_tick = current_tick + 55;
        
        
       
    },NULL);

   
}
void sleep_busy(uint32_t milliseconds){
    uint32_t elapsed_ticks = 0;
    start_tick = current_tick;
    uint32_t ticks_to_wait = TICKS_PER_MS * milliseconds;
    while (1)
    {
        elapsed_ticks = ticks_to_wait;
        if (ticks_to_wait < (current_tick-start_tick)){
            break;
        }
    }
    
}

void sleep_interrupt(uint32_t milliseconds){


    uint32_t ticks_to_wait = milliseconds * TICKS_PER_MS; // local varible to be seen in debugger
    end_tick = current_tick + ticks_to_wait; // tick at end of waiting period equals ticks to wait + current tick

    while (current_tick < end_tick)
    {
        asm("sti"); // enable interupts
      asm("hlt");   // wait for interupt 
      
    }
    
}