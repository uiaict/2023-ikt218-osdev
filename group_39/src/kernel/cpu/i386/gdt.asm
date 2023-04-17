; Written by IKT218 Group 39 spring 2023

; This assembly code loads the GDT using the 'lgdt' x86 instruction. 
; The following code is rewritten from both James Molloy OS development examples
; and our lecturer's examples.



[GLOBAL gdt_load] ;; This allows the function to be called from C code. 

gdt_load: ;; This is the name of the function, which we can use to call the function from C code.

