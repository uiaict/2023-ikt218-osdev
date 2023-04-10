#include "isr.h"
#include "system.h"


void isr_handler(struct registers regs)
{
    uint8_t int_no = regs.int_no & 0xFF;

    // FIXME: When printf() can format numbers, fix it!
    switch (int_no) {
        case 1:
            printf("Received interrupt: 1\n");
            break;
        case 2:
            printf("Received interrupt: 2\n");
            break;
        case 3:
            printf("Received interrupt: 3\n");
            break;
        default:
            printf("Received interrupt\n");
    }
}
