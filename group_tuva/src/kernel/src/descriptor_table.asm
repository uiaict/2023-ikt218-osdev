[GLOBAL gdt_flush]   ; Allows the C code to call gdt_flush().

gdt_flush:           ; Defines the function, entry point for this code
   mov eax, [esp+4]  ; Moves the GDT pointer into the EAX register, passed as a parameter
   lgdt [eax]        ; Load the new GDT pointer into the GDTR register

   mov ax, 0x10      ; Moves 0x10 into AX register, represents the offset of the data segment in GDT
   
   mov ds, ax        ; These lines load the data segment selector
   mov es, ax        ; (0x10, stored in the AX register) into the
   mov fs, ax        ; DS, ES, FS, GS, and SS segment registers
   mov gs, ax        ;
   mov ss, ax        ;

   jmp 0x08:.flush   ; Performs a far jump to the .flush label, 0x08 is the offset of the code segment in the GDT. Jump updates the CS register to use the new code segment selector

.flush:              ; Defines the .flush label, target of the far jump

   ret               ; Returns from the gdt_flush function to the calling C code

[GLOBAL idt_flush]
idt_flush:
   mov eax, [esp+4]  ; Get the pointer to the IDT, passed as a parameter.
   lidt [eax]        ; Load the IDT pointer.
   ret