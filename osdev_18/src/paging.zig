const std = @import("std");
const isr = @import("isr.zig");
const memory = @import("memory.zig");
const Console = @import("driver/Console.zig");
const BitSet = std.bit_set.IntegerBitSet(32);

// https://wiki.osdev.org/Paging#32-bit_Paging_.28Protected_Mode.29
const Page = packed struct {
    present: u1,
    read_write: u1,
    user: u1,
    accessed: u1,
    dirty: u1,
    unused: u7,
    frame: u20,
};

const Table = struct {
    pages: [1024]Page,
};

const Directory = struct {
    tables: [1024]?*Table,
    physical_tables: [1024]u32,
    physical_address: u32,
};

// State for paging
var kernel_directory: *Directory = undefined;
var current_directory: *Directory = undefined;

var frames: [*]BitSet = undefined;
var frames_len: u32 = 0;

fn firstFrame() ?u32 {
    const amount = frames_len / 32;
    for (frames[0..amount]) |*frame, i| {
        var j: usize = 0;
        while (j < 32) : (j += 1) {
            if (!frame.isSet(j)) {
                frame.set(j);
                return i * 32 + j;
            }
        }
    }
    return null;
}

fn allocateFrame(page: *Page, is_kernel: bool, is_writeable: bool) void {
    if (page.frame == 0) {
        if (firstFrame()) |index| {
            page.present = 1;
            page.read_write = if (is_writeable) 1 else 0;
            page.user = if (is_kernel) 0 else 1;
            page.frame = @truncate(u20, index);
        } else {
            @panic("No free frames!");
        }
    } else return;
}

fn freeFrame(page: *Page) void {
    if (page.frame > 0) {
        // Clear the specific bit in our bitmap
        frames[page.frame / 32].unset(page.frame % 32);
        page.frame = 0;
    }
}

pub fn switchPageDirectory(directory: *Directory) void {
    current_directory = directory;
    asm volatile ("mov %[physical_tables], %%cr3"
        :
        : [physical_tables] "r" (&directory.physical_tables),
    );
    var cr0: u32 = 0;
    asm volatile ("mov %%cr0, %[cr0]"
        : [cr0] "=r" (cr0),
    );
    cr0 |= 0x80000000; // Enable paging!
    asm volatile ("mov %[input], %%cr0"
        :
        : [input] "r" (cr0),
    );
}

pub fn getPage(address: u32, create: bool, directory: *Directory) ?*Page {
    const page_address = address / 0x1000;
    const table_index = page_address / 1024;
    if (directory.tables[table_index]) |table| {
        var page = table.pages[page_address % 1024];
        return &page;
    } else if (create) {
        var temporary: usize = 0;
        const bytes = memory.mallocAlignedPhysical(@sizeOf(Table), &temporary);
        const table = @intToPtr(*Table, bytes);
        directory.tables[table_index] = table;
        directory.physical_tables[table_index] = temporary | 0x7;
        return &table.pages[page_address % 1024];
    } else return null;
}

pub fn handler(_: isr.Registers) void {
    Console.write("\nPage fault occurred!");
}

pub fn init() void {
    // Size of physical memory
    memory.placement_address = @ptrToInt(&memory.end);
    const end_page = 0x1000000;
    const paddr: u32 = memory.placement_address;
    _ = paddr;

    // Initialize frames set to 0
    frames_len = end_page / 0x1000;
    frames = @intToPtr([*]BitSet, memory.mallocAligned(frames_len));
    const amount = frames_len / 32;
    for (frames[0..amount]) |*frame|
        frame.* = BitSet.initEmpty();

    // Create page directory
    const directory = memory.mallocAligned(@sizeOf(Directory));
    kernel_directory = @intToPtr(*Directory, directory);
    for (kernel_directory.tables) |*table|
        table.* = null;
    current_directory = kernel_directory;

    // Identity map physical address to virtual address from 0x0 to end of used memory
    var i: usize = 0;
    while (i < memory.placement_address) : (i += 0x1000) {
        if (getPage(i, true, kernel_directory)) |page|
            allocateFrame(page, false, false);
    }

    // Register page fault handler, then enable paging
    isr.setHandler(isr.IRQ14, handler);
    switchPageDirectory(kernel_directory);
}
