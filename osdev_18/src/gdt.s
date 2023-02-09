.type loadGdt, @function
.global loadGdt

loadGdt:
	mov +4(%esp), %eax           // Fetch the gdt register
	lgdt (%eax)                  // Load the new GDT
    ljmp $0x08, $reloadSegments  // Reload segments

reloadSegments:
    mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
    ret
