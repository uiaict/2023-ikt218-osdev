[bits 32]

section .data
    message db 'Hello, world!', 0

section .text
global test_gdt ; Export the test_gdt function

test_gdt:
    ; Load the data segment selector into DS
    mov ax, 0x10
    mov ds, ax
    
    ; Load the code segment selector into CS
    mov ax, 0x08
    mov cs, ax
    jmp main
    
null_segment:
    ; Attempt to access memory using the null segment selector
    mov eax, [0x0]
    ret
    
main:
    ; Print the message using the data segment selector
    mov eax, 4
    mov ebx, 1
    mov ecx, message
    mov edx, 13
    int 0x80
    
    ; Call a function using the code segment selector
    call code_function
    
    ; Attempt to access memory using the null segment selector
    call null_segment
    
    ; Exit the program
    mov eax, 1
    xor ebx, ebx
    int 0x80
    
code_function:
    ; Print a message using the data segment selector
    push ebx
    mov eax, 4
    mov ebx, 1
    mov ecx, message
    mov edx, 13
    int 0x80
    pop ebx
    ret
