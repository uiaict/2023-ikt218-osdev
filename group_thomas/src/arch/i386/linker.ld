ENTRY(_start)

SECTIONS
{
	. = 1M;

	.text BLOCK(4K) : ALIGN(4K)
	{
		KEEP(*(.multiboot))
		KEEP(*(.text.load_gdt))
		KEEP(*(.text))
	}

	.data BLOCK(4K) : ALIGN(4K)
	{
		KEEP(*(.data.gdt))
		KEEP(*(.data))
	}

	.bss BLOCK(4K) : ALIGN(4K)
	{
		KEEP(*(COMMON))
		KEEP(*(.bss))
	}

	.rodata BLOCK(4K) : ALIGN(4K)
	{
		KEEP(*(.rodata.text))
		KEEP(*(.rodata))
	}

	end = .; _end = .; __end = .;
}
