# OS


## Assembly

All the assembly used in this project will be using a dialect called Netwide
Assembler (NASM), this is based on the Intel assembly syntax. NASM was designed
to be simple and easy to understand (there exists multiple dialects for
assembly). Some key-points with this dialect is that we do not need to use `$`
or `%` in front of registers, values and the like, and the operand order is from
right to left (this also differs between dialects).

This example assembly code moves the value `9` into the register `eax`.
```assembly
mov eax, 9
```
NASM's main site and documentation can be found at <https://www.nasm.us/>
