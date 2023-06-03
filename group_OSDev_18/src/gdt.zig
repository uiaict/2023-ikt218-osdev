const std = @import("std");

const GdtEntry = packed struct {
    limit_low: u16,
    base_low: u16,
    base_middle: u8,
    access: u8,
    granularity: u8,
    base_high: u8,

    fn init(base: u32, limit: u32, access: u8, granularity: u8) GdtEntry {
        return .{
            .base_low = @truncate(u16, base & 0xFFFF),
            .base_middle = @truncate(u8, (base >> 16) & 0xFF),
            .base_high = @truncate(u8, (base >> 24) & 0xFF),
            .limit_low = @truncate(u16, limit & 0xFFFF),
            .granularity = @truncate(u8, ((limit >> 16) & 0x0F) | (granularity & 0xF0)),
            .access = access,
        };
    }
};

const GdtRegister = packed struct {
    limit: u16,
    base: *[5]GdtEntry,

    fn init(table: *[5]GdtEntry) GdtRegister {
        return .{
            .limit = @as(u16, @sizeOf(@TypeOf(table.*))) - 1,
            .base = table,
        };
    }
};

extern fn loadGdt(register: *const GdtRegister) void;

var gdt_table: [5]GdtEntry = undefined;
var gdt_register: GdtRegister = undefined;

pub fn init() void {
    gdt_table = [5]GdtEntry{
        GdtEntry.init(0, 0x00000000, 0x00, 0x00), // Null Descriptor
        GdtEntry.init(0, 0xFFFFFFFF, 0x9A, 0xCF), // Kernel Mode Code Segment
        GdtEntry.init(0, 0xFFFFFFFF, 0x92, 0xCF), // Kernel Mode Data Segment
        GdtEntry.init(0, 0xFFFFFFFF, 0xFA, 0xCF), // User Mode Code Segment
        GdtEntry.init(0, 0xFFFFFFFF, 0xF2, 0xCF), // User Mode Data Segment
    };
    gdt_register = GdtRegister.init(&gdt_table);
    loadGdt(&gdt_register);
}
