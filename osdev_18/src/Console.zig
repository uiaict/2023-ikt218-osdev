const utils = @import("utils.zig");
const inb = utils.inb;
const outb = utils.outb;

var row: u16 = 0;
var column: u16 = 0;
var color: u16 = 0x0F;
var buffer = @intToPtr([*]volatile u16, 0xB8000);

fn newLine() void {
    row += 1;
    column = 0;
}

fn incrementCursor() void {
    column += 1;
    if (column >= 80)
        newLine();
}

const Color = enum(u8) {
    black,
    blue,
    green,
    cyan,
    red,
    magenta,
    brown,
    light_grey,
    dark_grey,
    light_blue,
    light_green,
    light_cyan,
    light_red,
    light_magenta,
    light_brown,
    white,
};

pub fn init() void {
    var i: usize = 0;
    while (i < 80 * 25) : (i += 1)
        buffer[i] = color << 8 | ' ';
}

pub fn write(text: []const u8) void {
    for (text) |byte| {
        if (byte == '\n')
            newLine()
        else {
            const i = row * 80 + column;
            buffer[i] = color << 8 | @as(u16, byte);
            incrementCursor();
        }
    }
    moveCursor(row, column);
}

pub fn setColor(foreground: Color, background: Color) void {
    color = @enumToInt(background) << 4 | @enumToInt(foreground);
}

pub fn moveCursor(cursor_row: u16, cursor_column: u16) void {
    const position = cursor_row * 80 + cursor_column;
    outb(0x3D4, 0x0F);
    outb(0x3D5, @truncate(u8, position));
    outb(0x3D4, 0x0E);
    outb(0x3D5, @truncate(u8, position >> 8));
}
