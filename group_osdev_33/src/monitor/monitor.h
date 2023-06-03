//
// Created by per on 12/30/22.
//

#ifndef IKT218_ADVANCED_OPERATING_SYSTEM_DISPLAY_DEFS_H
#define IKT218_ADVANCED_OPERATING_SYSTEM_DISPLAY_DEFS_H

enum vga_color {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    GREY,
    DARK_GREY,
    BRIGHT_BLUE,
    BRIGHT_GREEN,
    BRIGHT_CYAN,
    BRIGHT_RED,
    BRIGHT_MAGENTA,
    YELLOW,
    WHITE,
};

#if defined(OS_MODULE_IO_DISPLAY_VERSION)
    #if (OS_MODULE_IO_DISPLAY_VERSION == 1)
        #include "../display_1.h"
    #elif (OS_MODULE_IO_DISPLAY_VERSION == 2)
        #include "monitor_2.h"
    #endif
#else
    #include "../monitor_1.h"
#endif


#endif //IKT218_ADVANCED_OPERATING_SYSTEM_DISPLAY_DEFS_H
