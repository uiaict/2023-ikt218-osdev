#include <pit.h>
#include <system.h>
#include <terminal.h>
#include <isr.h>

uint32_t tick = 0;

static void timer_callback(registers_t regs)
{
 

   tick++;
//    terminal_writestring("Tick: ");
//   terminal_write_dec(tick);
//   terminal_writestring("\n");
  
  

}
void init_pit()
{



   register_interrupt_handler(IRQ0, &timer_callback);


  
   uint32_t divisor = PIT_DEFAULT_DIVISOR ;


   outb(PIT_CMD_PORT, 0x36);

  
   outb(PIT_CHANNEL0_PORT, divisor & 0xFF);
   outb(PIT_CHANNEL0_PORT, divisor>>8);
 
  
} 


uint32_t get_current_tick(){
   return tick; 
}
void sleep_busy(uint32_t milliseconds){

    uint32_t start_tick = get_current_tick();

   uint32_t ticks_to_wait = milliseconds * TICKS_PER_MS;
   uint32_t elapsed_ticks =0;

   while(elapsed_ticks<ticks_to_wait){
      if(get_current_tick()==start_tick+elapsed_ticks){
      asm("nop");
     
     
      }
      else { 
      
         elapsed_ticks++;
         
      }
       
   }
 
}

void sleep_interrupt(uint32_t milliseconds){

 uint32_t current_tick = get_current_tick();
 uint32_t ticks_to_wait= milliseconds * TICKS_PER_MS;
 uint32_t end_ticks= current_tick+ticks_to_wait ;
 while (current_tick<end_ticks ){

   asm volatile("sti");
   asm volatile("hlt");
   current_tick = get_current_tick();
  
 }

}