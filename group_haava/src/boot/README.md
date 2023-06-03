# Boot

## Multiboot

We're using GRUB with [Multiboot](https://www.gnu.org/software/grub/manual/multiboot/)
(not Multiboot2). Before giving control over to the kernel, GRUB has switched
the CPU to "protected mode". GRUB has also set up its own GDT, but we can't use
that one.

Verify Multiboot signature, this is a silent command, but a valid signature has
an exit code of `0`, while an invalid signature will have exit code `1`.
```
grub-file --is-x86-multiboot <kernel.bin>
```
