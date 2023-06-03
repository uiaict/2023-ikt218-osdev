# 🧠 Kernel
This module of the os contains the source code for the kernel and tables the kernel rely upon
to function. The different tables are described below. For a thourough documentation of the 
source code, see the code files, as all functions are documented and explained there. This
readme presents a short overview of the concepts that have been implemented in the kernel module.


## 🌐 Global Description Table
The files gdt.h and gdt.c contains the source code for implementing the global description table.
Most of the source code in this folder has been borrowed from the lecture notes "Lecture 4 - Global description tables" by Per-Arne, and the repository by Per-Arne.

## Definition of global description table.
The purpose of the Global Description Table (GDT) is to divide the memory into different sections that may have different access levels. It used by the computer MMU, its memory management unit, which is a hardware component used to map virtual addresses to physical addresses.  The Global Description Table is usually implemented as part of the OS to start the \textbf{protected mode}, and allows the OS to “protect” certain memory areas, like where the kernel is located etc.

## Layout of the description table
A GDT entry consists of a \textbf{number} which is the entry number, a *base* which is a 32-bit address value describing where the segment begins, a *limit* which is an address that describes where the segment ends, a *access* is 8 bit that configures the segment and a *gran* short for granularity, which is a flag that indicates the size the limit is scaled by, either 1 bit (gran = 0) or 4 KiB.

The access bits will determine the protection level of the area, what type of area it is (code or data or system), if it is allowed to read and or write in it and whether it has been accessed or not.

## 🆘 Interupt Descriptor table
IDT is a binary data structure that tells the CPU where the interupt service routines(ISR) are located. A global desciption table is required in order for the IDT to work.
<!-- source: https://wiki.osdev.org/Interrupt_Descriptor_Table -->

The files idt.h, idt.cpp and idt.asm implement the IDT. In order to have a functional IDT, some 
interupt service routines needs to be defined as well. This is done in the interupt.h, interupt.cpp, isr.cpp and isr.asm files.
