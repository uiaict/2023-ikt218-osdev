#include pit.h


void init_pit(){

}

void get_current_tick(){
    
}


void sleep_busy(uint32_t milliseconds){
    int start_tick = get_current_tick()
    int ticks_to_wait = milliseconds * TICKS_PER_MS
    int elapsed_ticks = 0

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
    int current_tick = get_current_tick()
    int ticks_to_wait = milliseconds * TICKS_PER_MS
    int end_ticks = current_tick + ticks_to_wait

    while (current_tick < end_ticks)
    {
        /* code */
        // 	a. Execute the following assembly instructions:
	// 		i. Enable interrupts (sti)
	// 		ii. Halt the CPU until the next interrupt (hlt)

        current_tick = get_current_tick()
    }
    
}