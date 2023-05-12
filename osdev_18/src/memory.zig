pub extern const placement_address: u32;

fn kernelMalloc(size: u32, alignment: u32, physical_address: ?*u32) u32 {
    // If the address is not already page-aligned
    if (alignment == 1 and (placement_address & 0x00000FFF != 0)) {
        // Align it
        placement_address &= 0xFFFFF000;
        placement_address += 0x1000;
    }
    if (physical_address) |address|
        address.* = placement_address;
    const temporary = placement_address;
    placement_address += size;
    return temporary;
}

pub fn malloc(size: u32) u32 {
    return kernelMalloc(size, 0, null);
}

pub fn mallocAligned(size: u32) u32 {
    return kernelMalloc(size, 1, null);
}

pub fn mallocPhysical(size: u32) u32 {
    return kernelMalloc(size, 1, null);
}

pub fn mallocAlignedPhysical(size: u32, physical_address: *u32) u32 {
    return kernelMalloc(size, 1, physical_address);
}
