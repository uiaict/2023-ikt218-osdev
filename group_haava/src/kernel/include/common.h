#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

/** Master PIC - Command */
#define PIC1_CMD    0x20
/** Master PIC - Data */
#define PIC1_DATA   0x21
/** Slave PIC - Command */
#define PIC2_CMD    0xA0
/** Slave PIC - Data */
#define PIC2_DATA   0xA1
/** End-of-interrupt command code */
#define PIC_EOI     0x20

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Write @c value to @c port.
 *
 * @param port Port to write to.
 * @param value Value to write.
 */
void output_to_port(uint16_t port, uint8_t value);

/**
 * @brief Read @c AL register from @c port.
 *
 * @param port Port to read from.
 * @return Value in byte from @c port.
 */
uint8_t input_from_port(uint16_t port);

#ifdef __cplusplus
};
#endif

#endif /* COMMON_H */
