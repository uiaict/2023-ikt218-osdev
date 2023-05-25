const paging = @import("paging.zig");
const memory = @import("memory.zig");
const Console = @import("driver/Console.zig");

// State
var start_block: ?*Block = null;

// Header for each block, actual data is allocated after (*Header) + sizeOf(header) which is 8.
const Block = packed struct {
    size: u31,
    used: bool,
    next: ?*Block,

    fn alloc(size: u31) *Block {
        const bytes = memory.malloc(@sizeOf(Block), .regular, null);
        const block = @intToPtr(*Block, bytes);
        block.* = .{
            .size = size,
            .used = true,
            .next = null,
        };
        return block;
    }

    fn fits(self: *Block, size: u31) bool {
        return size <= self.size and !self.used;
    }
};

// Find a block that isn't used, or create one.
// TODO: get frames before
// Note: Block must be set to valid after
fn findOrCreateBlock(size: u31) *Block {
    if (start_block) |first| {
        var current = first;
        while (current.next) |block| {
            if (block.fits(size)) return block;
            if (block.next == null)
                break
            else
                current = block;
        }
        // current is now the last block
        const new_block = Block.alloc(size);
        current.next = new_block;
        return new_block;
    } else {
        const new_block = Block.alloc(size);
        start_block = new_block;
        return new_block;
    }
}

pub fn create(comptime T: type) *T {
    const block = findOrCreateBlock(@sizeOf(T));
    Console.write("\ncreated block at: 0x");
    Console.writeHex(@ptrToInt(block));
    block.used = true;
    const bytes = memory.malloc(@sizeOf(T), .regular, null);
    Console.write("\ncreated ptr at:   0x");
    return @intToPtr(*T, bytes);
}

pub fn destroy(pointer: anytype) void {
    var block = blk: {
        const offset = (@ptrToInt(pointer) - 8);
        break :blk @intToPtr(*Block, offset);
    };
    block.used = false;
    Console.write("\ndisabled block:   0x");
    Console.writeHex(@ptrToInt(block));
}

// pub fn alloc(comptime T: type, n: usize) []T {
//     const bytes = malloc(@sizeOf(T) * n, .regular, null);
//     const items = @intToPtr([*]T, bytes);
//     return items[0..n];
// }

// pub fn free(pointer: anytype) void {
//     const T = @typeInfo(@TypeOf(pointer)).Pointer.child;
//     const bytes = std.mem.sliceAsBytes(pointer);
//     Console.writeHex(@sizeOf(T));
//     _ = T;
//     _ = bytes;
// }

