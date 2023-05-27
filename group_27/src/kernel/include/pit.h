#ifndef PIT_H
#define PIT_H

#include <stdint.h>
#include <stdbool.h>

// PIT (Programmable Interval Timer) related macros
#define PIT_CMD_PORT 0x43
#define PIT_CHANNEL0_PORT 0x40
#define PIT_CHANNEL1_PORT 0x41
#define PIT_CHANNEL2_PORT 0x42
#define PC_SPEAKER_PORT 0x61
#define PIT_DEFAULT_DIVISOR 0x4E20 // 20000, which gives about 18.2 Hz (1193180 / 20000)

// IRQ0 related macros
#define PIC1_CMD_PORT 0x20
#define PIC1_DATA_PORT 0x20
#define PIC_EOI		0x20		/* End-of-interrupt command code */
 

// Custom sleep function constants
#define PIT_BASE_FREQUENCY 1193180
#define TARGET_FREQUENCY 1000 // 1000 Hz
#define DIVIDER (PIT_BASE_FREQUENCY / TARGET_FREQUENCY)
#define TICKS_PER_MS (TARGET_FREQUENCY / TARGET_FREQUENCY)


void sleep_busy(){

}
	// Set start_tick to get_current_tick()
	// Set ticks_to_wait to milliseconds * TICKS_PER_MS
	// Set elapsed_ticks to 0
	// While elapsed_ticks is less than ticks_to_wait
	// 	a. While get_current_tick() is equal to start_tick + elapsed_ticks
	// 		i. Do nothing (busy wait)
	// 	b. Increment elapsed_ticks


void sleep_interrupt(){

}
	// Set current_tick to get_current_tick()
	// Set ticks_to_wait to milliseconds * TICKS_PER_MS
	// Set end_ticks to current_tick + ticks_to_wait
	// While current_tick is less than end_ticks
	// 	a. Execute the following assembly instructions:
	// 		i. Enable interrupts (sti)
	// 		ii. Halt the CPU until the next interrupt (hlt)
	// 	b. Set current_tick to get_current_tick()


void init_pit();
void sleep_interrupt(uint32_t milliseconds);
void sleep_busy(uint32_t milliseconds);

#endif