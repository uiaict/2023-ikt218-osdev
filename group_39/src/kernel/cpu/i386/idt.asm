; Written by IKT218 Group 39 spring 2023

; This assembly code loads the IDT using the 'lidt' x86 instruction. 
; The following code is written highly inspired by both James Molloy OS development examples
; and our lecturer's examples.

[GLOBAl idt_load] ; This allows us to call this subroutine from our C code. 

; Defines the label of this subroutine. 
idt_load:
    mov eax, [esp+4] ; Move the parameter passed by the C code into eax register.
    lidt [eax]       ; Load the IDT from the pointer stored in the eax register. 
    ret              ; Return, so that control is passed back to the calling C code. 



