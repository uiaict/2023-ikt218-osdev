//
// isr.c -- High level interrupt service routines and interrupt request handlers.
// Part of this code is modified from Bran's kernel development tutorials.
// Rewritten for JamesM's kernel development tutorials.
// http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html

#include "common.h"
#include "isr.h"
#include "monitor.h"
#include "print.h"
#include "isr.h"
#include "isr_handlers.h"

isr_t interrupt_handlers[256];

// Function that registers a handler for a given interrupt
void register_interrupt_handler(u8int n, isr_t handler)
{
    interrupt_handlers[n] = handler;
}

