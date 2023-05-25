// Get end of kernel from linker
extern const end: u32;

pub var address: u32 = undefined;

const Alignment = enum {
    page,
    regular,
};

pub fn init() void {
    address = @ptrToInt(&end);
}

pub fn malloc(size: u32, alignment: Alignment, physical_address: ?*u32) u32 {
    // Align the address based on mode
    switch (alignment) {
        .page => if (address & 0x00000FFF != 0) {
            address &= 0xFFFFF000;
            address += 0x1000;
        },
        .regular => if (address % 4 != 0) {
            address += 4 - (address % 4);
        },
    }

    // Set physical address if it's set
    if (physical_address) |value|
        value.* = address;

    // Increment address with size
    defer address += size;
    return address;
}
