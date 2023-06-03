#ifndef PIT_H
#define PIT_H

#include <stdint.h>


// PIT values 
#define PIT_CMD_PORT 0x43
#define PIT_CHANNEL0_PORT 0x40
#define PIT_CHANNEL1_PORT 0x41
#define PIT_CHANNEL2_PORT 0x42
#define PC_SPEAKER_PORT 0x61
#define PIT_DEFAULT_DIVISOR 0x4E20 


#define PIC1_CMD_PORT 0x20
#define PIC1_DATA_PORT 0x20
#define PIC_EOI		0x20		
 


#define PIT_BASE_FREQUENCY 1193180
#define TARGET_FREQUENCY 1000 
#define DIVIDER (PIT_BASE_FREQUENCY / TARGET_FREQUENCY)
#define TICKS_PER_MS (1)


void init_pit();
void sleep_interrupt(uint32_t milliseconds);
void sleep_busy(uint32_t milliseconds);
#endif

