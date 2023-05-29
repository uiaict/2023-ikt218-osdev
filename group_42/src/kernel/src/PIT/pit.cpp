#include "pit.h"
#include "../../GDT/isr.h"
uint32_t start_tick = 0;
uint32_t get_current_tick = 0;
//uint32_t ticks_to_wait = 0;
uint32_t current_tick = 0;
uint32_t end_tick = 0;

/* 
uint32_t get_current_tick(){
    return current_tick;
} */
void init_pit(){
    
    UiAOS::CPU::ISR::register_interrupt_handler(IRQ0,[] (UiAOS::CPU::ISR::registers_t* regs, void* context){
        current_tick = current_tick + 55;
        
        
       
    },NULL);

    /* 
    void UiAOS::IO::Keyboard::hook_keyboard(keyboard_callback a, void *b) {

    payload = {a, b};

    UiAOS::CPU::ISR::isr_t static_cb = [](UiAOS::CPU::ISR::registers_t *regs, void* cb_ptr){
        auto pay = (payload_t*)cb_ptr;
        uint8_t scancode = inb(0x60);
        if (scancode > SC_MAX) return; // Over SC_MAX is Release (I think)

        pay->cb(scancode, pay->ctx);

    };

    UiAOS::CPU::ISR::register_interrupt_handler(IRQ1, static_cb, &payload);
}
     */
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
    
    /* 	
    Set start_tick to get_current_tick()
	Set ticks_to_wait to milliseconds * TICKS_PER_MS
	Set elapsed_ticks to 0
	While elapsed_ticks is less than ticks_to_wait
		a. While get_current_tick() is equal to start_tick + elapsed_ticks
			i. Do nothing (busy wait)
		b. Increment elapsed_ticks 
        */

}

void sleep_interrupt(uint32_t milliseconds){


    uint32_t ticks_to_wait = milliseconds * TICKS_PER_MS;
    end_tick = current_tick + ticks_to_wait;

    while (current_tick < end_tick)
    {
        asm("sti");
      asm("hlt");
      ticks_to_wait = current_tick;
      
    }
    
 /*    
    Set current_tick to get_current_tick()
	Set ticks_to_wait to milliseconds * TICKS_PER_MS
	Set end_ticks to current_tick + ticks_to_wait
	While current_tick is less than end_ticks
		a. Execute the following assembly instructions:
			i. Enable interrupts (sti)
			ii. Halt the CPU until the next interrupt (hlt)
		b. Set current_tick to get_current_tick() 
        */
}