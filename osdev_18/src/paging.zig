const std = @import("std");
const isr = @import("../isr.zig");
const IntegerBitSet = std.bit_set.IntegerBitSet;

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
    tables: *[1024]Table,
    physical_tables: [1024]u32,
    physical_address: u32,
};

const frames: [10]IntegerBitSet(u32) = .{IntegerBitSet(32).initEmpty()} ** 10;

fn firstFrame() ?u32 {
    for (frames) |frame, i| {
        if (frame.findFirstSet()) |j| return i * 32 + j;
    }
    return null;
}

fn allocateFrame(page: *Page, is_kernel: bool, is_writeable: bool) void {
    if (page.frame == 0) {
        if (firstFrame()) |index| {
            page.present = 1;
            page.read_write = if (is_writeable) 1 else 0;
            page.user = if (is_kernel) 0 else 1;
            page.frame = index;
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

pub fn switchPageDirectory() void {}

pub fn getPage(address: u32, create: bool, directory: *Directory) *Page {}

pub fn handler(_: isr.Registers) void {}

pub fn init() void {}
