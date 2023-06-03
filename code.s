      .global _start

        .text
_start:
        # write(1, message, 13)
        movw     $1, %rax                # system call 1 is write
        movw     $1, %rdi                # file handle 1 is stdout
        movw     $message, %rsi          # address of string to output
        movw     $13, %rdx               # number of bytes
        syscall                         # invoke operating system to do the write

        # exit(0)
        movw     $60, %rax               # system call 60 is exit
        add     $5,   %rdi 
        sub     $3,   %rdi 
        movw     $9,   %rdi
        add     $2,   %rdi
        add     $2,   %rdi
        add     $2,   %rdi
        add     $2,   %rdi
        add     $2,   %rdi
        add     $2,   %rdi
        add     $2,   %rdi
        add     $2,   %rdi
        add     $2,   %rdi
        add     $2,   %rdi
        add     $2,   %rdi
        syscall                         # invoke operating system to exit
message:
        .ascii  "Hello, world\n"