#pragma once
#include <stdint.h>

// A very simplified scancode to ASCII table. You'll need to complete this with all keys you want to support.
extern char scancode_to_ascii[128];


extern "C" {
    void irq0();
    void irq1();
    void irq2();
    void irq3();
    void irq4();
    void irq5();
    void irq6();
    void irq7();
    void irq8();
    void irq9();
    void irq10();
    void irq11();
    void irq12();
    void irq13();
    void irq14();
    void irq15();
}

