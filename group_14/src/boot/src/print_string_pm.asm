[bits 32]

; Constants
VIDEO_MEMORY equ 0xb8000 ; Sets memory location of video memory
WHITE_ON_BLACK equ 0x0f ; Sets text colour

print_string_pm:
    pusha ; Pushed all GP registers onto the stack
    mov edx, VIDEO_MEMORY ; Sets edx to the start of the video memory

print_string_pm_loop:
    mov al, [ebx] ; Stores the character from ebx in al
    mov ah, WHITE_ON_BLACK ; Sets text colour

    cmp al, 0 ; Compares al register to 0
    je done ; Jumps to done if equals

    mov [edx], ax ; Stores the character and its attributes

    add ebx, 1 ; Increments ebx to the next character
    add edx, 2 ; Moves to next character cell in video memory

    jmp print_string_loop ; Loops back to the start

print_string_pm_done:
    popa ; Restores the registers pushed to the stack
    ret ; Returns from the function