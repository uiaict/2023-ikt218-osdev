; Define the flush_gdt function to allow it to be called from C code
[GLOBAL flush_gdt]

; Implementation of the flush_gdt function
flush_gdt:
    ; Get the pointer to the new GDT, which is passed as a parameter to the function
    ; and store it in the eax register
    mov eax, [esp + 4]

    ; Load the new GDT pointer into the GDTR register using the lgdt instruction
    lgdt [eax]

    ; Load the new data segment selector into all the data segment registers
    ; by setting the ax register to 0x10 and then moving its value into each segment register
    mov ax, 0x10        ; 0x10 is the offset in the GDT to our data segment
    mov ds, ax          ; Load data segment selector into ds
    mov es, ax          ; Load data segment selector into es
    mov fs, ax          ; Load data segment selector into fs
    mov gs, ax          ; Load data segment selector into gs
    mov ss, ax          ; Load data segment selector into ss

    ; Perform a far jump to the new code segment by setting the cs register to 0x08
    ; and jumping to the .update label using the jmp instruction
    jmp 0x08:.update    ; 0x08 is the offset to our code segment: Far jump!

.update:
    ; Return from the function using the ret instruction
    ret
    