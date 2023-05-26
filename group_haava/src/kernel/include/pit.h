/**
 * @file
 * @brief Programmable Interval Timer (PIT).
 */

#ifndef PIT_H
#define PIT_H

#include <stdint.h>


/** PIT command register - Write. */
#define PIT_CMD_PORT 0x43
/** PIT channel 0 - Connected to IRQ0. */
#define PIT_CHANNEL0_PORT 0x40
/** PIT channel 2 - Controls PC speaker. */
#define PIT_CHANNEL2_PORT 0x42
#define PC_SPEAKER_PORT 0x61
/** Base frequency of PIT. */
#define PIT_BASE_FREQUENCY 1193180
#define TARGET_FREQUENCY 100
#define PIT_DIVISOR (PIT_BASE_FREQUENCY / TARGET_FREQUENCY)


#ifdef __cplusplus
extern "C" {
#endif

void pit_init();
void sleep_interrupt(uint32_t milliseconds);
void sleep_busy(uint32_t milliseconds);

#ifdef __cplusplus
};
#endif

#endif /* PIT_H */
