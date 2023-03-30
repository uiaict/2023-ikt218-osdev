# 🧠 Kernel
This module of the os contains the source code for the kernel and tables the kernel rely upon
to function. The different tables are described below. For a thourough documentation of the 
source code, see the code files, as all functions are documented and explained there. This
readme presents a short overview of the concepts that have been implemented in the kernel module.


## 🌐 Global Description Table
The files gdt.h and gdt.c contains the source code for implementing the global description table.
Most of the source code in this folder has been borrowed from the lecture notes "Lecture 4 - Global description tables" by Per-Arne.


## 🆘 Interupt Descriptor table
IDT is a binary data structure that tells the CPU where the interupt service routines(ISR) are located. A global desciption table is required in order for the IDT to work.
<!-- source: https://wiki.osdev.org/Interrupt_Descriptor_Table -->

The files idt.h, idt.cpp and idt.asm implement the IDT. In order to have a functional IDT, some 
interupt service routines needs to be defined as well. This is done in the interupt.h, interupt.cpp, isr.cpp and isr.asm files.
