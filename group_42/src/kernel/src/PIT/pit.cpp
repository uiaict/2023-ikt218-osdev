#include "pit.h"

uint32_t start_tick = 0;
uint32_t get_current_tick = 0;
uint32_t ticks_to_wait = 0;
uint32_t current_tick = 0;

/* 
uint32_t get_current_tick(){
    return current_tick;
} */
void init_pit(){
    
    UiAOS::CPU::ISR::register_interrupt_handler(IRQ0,[] (UiAOS::CPU::ISR::registers_t* regs, void* context){
        current_tick = current_tick + 1;
        for (size_t i = 0; i < 2000; i++)
        {
            *((int*) 0xB8000+i) = current_tick;
        }
        
       
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