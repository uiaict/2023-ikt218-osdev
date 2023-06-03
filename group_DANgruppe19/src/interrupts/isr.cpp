#include "isr.h"
#include "../kernel/include/terminal.h"

extern "C" {
    void divide_by_zero_handler() {
        terminal_write("1. Divide by zero exception occurred!\n", 39);
    }

    void isr0() {
        //terminal_write("isr0 called\n", 12);
        divide_by_zero_handler();
    }

/*
    void isr1() {
        terminal_write("Invalid opcode exception occurred!\n", 36);
        // handle invalid opcode exception here, or halt system
    }

    void isr2() {
        terminal_write("General protection fault occurred!\n", 36);
        // handle general protection fault here, or halt system
    }


*/
    

    void isr3() {
    terminal_write("2. Software breakpoint (INT 3) triggered!\n", 43);
    // Continue with normal program execution after handling the interrupt.
}

void isr4() {
    terminal_write("3. User-defined software interrupt (INT 4) triggered!\n", 55);
    // Continue with normal program execution after handling the interrupt.
}



    void test_output() {
    terminal_write("Testing output from isr.cpp", 27);
}

}
