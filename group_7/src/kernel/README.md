This is the readme for all files contained in the *kernel* subdirectory.

# Kernel Main
In the *kernel_main()* function in *main.cpp*, all tables and the os gets initialized after the bootloader has booted uia os.

It does the following:
- initialize the global description table
- prints Hello


# Global Description Table
The files gdt.h and gdt.c contains the source code for implementing the global description table.
Most of the source code in this folder has been borrowed from the lecture notes "Lecture 4 - Global description tables" by Per-Arne, and the repository by Per-Arne.

## Definition of global description table.
The purpose of the Global Description Table (GDT) is to divide the memory into different sections that may have different access levels. It used by the computer MMU, its memory management unit, which is a hardware component used to map virtual addresses to physical addresses.  The Global Description Table is usually implemented as part of the OS to start the \textbf{protected mode}, and allows the OS to “protect” certain memory areas, like where the kernel is located etc.

## Layout of the description table
A GDT entry consists of a \textbf{number} which is the entry number, a *base* which is a 32-bit address value describing where the segment begins, a *limit* which is an address that describes where the segment ends, a *access* is 8 bit that configures the segment and a *gran* short for granularity, which is a flag that indicates the size the limit is scaled by, either 1 bit (gran = 0) or 4 KiB.

The access bits will determine the protection level of the area, what type of area it is (code or data or system), if it is allowed to read and or write in it and whether it has been accessed or not.

We will implement a memory area or segment for *code*, *data*, *user mode code*  and *user mode data*. In addition, a *null* segment is needed. 

The null segment is required by certain emulators, and should contain no data. Sometimes this 8 bit long segment is used to store the pointer to the GDT itself. The code segment is used to store your kernel. It is not allowed to write to this segment. As it is not allowed to write to the code segment, the kernel must write to the data segment when processing variables etc.

## Use
The gdt is initialized upon startup, i.e. in *kernel_main()* in *main.cpp*.