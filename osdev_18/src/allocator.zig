// Get end of kernel from linker
extern const end: u32;

pub var address: u32 = undefined;

const Alignment = enum {
    page,
    type,
    none,
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
        .type => if (address % size != 0) {
            address += (address % size);
        },
        .none => {},
    }

    // Set physical address if it's set
    if (physical_address) |value|
        value.* = address;

    // Increment address with size
    defer address += size;
    return address;
}

pub fn create(comptime T: type, alignment: Alignment, physical_address: ?*u32) *T {
    const bytes = malloc(@sizeOf(T), alignment, physical_address);
    return @intToPtr(*T, bytes);
}

pub fn alloc(comptime T: type, n: usize, alignment: Alignment, physical_address: ?*u32) []T {
    const bytes = malloc(@sizeOf(T) * n, alignment, physical_address);
    const items = @intToPtr([*]T, bytes);
    return items[0..n];
}
