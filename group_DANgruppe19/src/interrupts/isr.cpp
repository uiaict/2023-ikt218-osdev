#include "isr.h"
#include "../kernel/include/terminal.h"

extern "C" {
    void divide_by_zero_handler() {
        terminal_write("Divide by zero exception occurred!", 33);
    }

    void isr0() {
        terminal_write("isr0 called\n", 12);
        divide_by_zero_handler();
    }


    void non_maskable_interrupt_handler() {
        terminal_write("isr1 called\n", 12);
        terminal_write("Non-Maskable Interrupt occurred!", 31);
    }

    void isr1() {
        non_maskable_interrupt_handler();
    }


    void debug_handler() {
        terminal_write("Debug exception occurred!", 24);
    }

    void isr2() {
        debug_handler();
    }

    void test_output() {
    terminal_write("Testing output from isr.cpp", 27);
}

}
