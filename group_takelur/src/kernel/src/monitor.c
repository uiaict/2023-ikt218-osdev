#include "common.h"
#include "monitor.h"

// Monitor setup
// Set up VGA width and height
static const int MONITOR_WIDTH = 80;
static const int MONITOR_HEIGHT = 25;

// Size of the video memory
static const int MONITOR_SIZE = 2 * MONITOR_WIDTH * MONITOR_HEIGHT;     // (2 bytes per char, 80 columns and 25 rows)

// VGA ports
static const u16int MONITOR_COMMAND_PORT = 0x3D4;
static const u16int MONITOR_DATA_PORT = 0x3D5;

// VGA commands
static const u8int MONITOR_HIGH_BYTE_COMMAND = 14;  // Sets high byte of cursor position (= row)
static const u8int MONITOR_LOW_BYTE_COMMAND = 15;   // Sets low byte of cursor position (= column)

// Cursor position variables
static u8int cursor_column = 0;
static u8int cursor_row = 0;

// Video memory address
u16int *video_memory = (u16int *)0xB8000;
