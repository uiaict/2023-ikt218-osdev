// Written by the IKT218 Group 39 in the spring 2023.

#include "gdt.h" // Include our GDT header file.




// Create an array of 3 GDT entries (NULL, Data and Text) 
// as well as a GDT pointer on stack.
gdt_entry gdt_entries[3];
gdt_pointer gdt_ptr; 