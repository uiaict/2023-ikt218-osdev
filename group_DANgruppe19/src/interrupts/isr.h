#pragma once

extern "C" {
    void isr0();
    //void isr1();
    //void isr2();
    void isr3();
    void isr4();
}


extern "C" void divide_by_zero_handler();
extern "C" void non_maskable_interrupt_handler();
extern "C" void debug_handler();
extern "C" void test_output();