const std = @import("std");
const utils = @import("../utils.zig");

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

pub fn log(message: []const u8, comptime source: std.builtin.SourceLocation) void {
    write(source.fn_name ++ ": ");
    write(message);
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

pub fn writeHex(value: u8) void {
    const index = [16]u8{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    write(&.{ '0', 'x', index[(value & 0xF0) >> 4], index[(value & 0x0F)] });
}

pub fn setColor(foreground: Color, background: Color) void {
    color = @enumToInt(background) << 4 | @enumToInt(foreground);
}

pub fn moveCursor(cursor_row: u16, cursor_column: u16) void {
    row = cursor_row;
    column = cursor_column;
    const position = row * 80 + column;
    utils.outb(0x3D4, 0x0F);
    utils.outb(0x3D5, @truncate(u8, position));
    utils.outb(0x3D4, 0x0E);
    utils.outb(0x3D5, @truncate(u8, position >> 8));
}

pub fn moveBackwards() void {
    if (column > 9) moveCursor(row, column - 1);
}

pub fn moveForwards() void {
    moveCursor(row, column + 1);
}

pub fn deleteBackwards() void {
    // Don't delete prompt
    if (column > 9) {
        moveCursor(row, column - 1);
        buffer[(row * 80 + column)] = color << 8 | ' ';
    }
}

pub fn showPrompt() void {
    setColor(.green, .black);
    write("kernel ");
    setColor(.light_blue, .black);
    write("> ");
    setColor(.white, .black);
}
