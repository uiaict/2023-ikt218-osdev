/**
 * @file
 * @brief Handles VGA text mode.
*/


/** VGA text mode color constants. */
enum vga_color {
    vga_color_black,
    vga_color_blue,
    vga_color_green,
    vga_color_cyan,
    vga_color_red,
    vga_color_magenta,
    vga_color_brown,
    vga_color_light_grey,
    vga_color_dark_grey,
    vga_color_light_blue,
    vga_color_light_green,
    vga_color_light_cyan,
    vga_color_light_red,
    vga_color_light_magenta,
    vga_color_light_brown,
    vga_color_white,
};


#ifdef __cplusplus
extern "C" {
#endif

/** Initialize variables and clear screen. */
void vga_init(void);

/**
 * @brief Set new VGA color.
 * @param fg Foreground color
 * @param bg Background color
 */
void vga_set_color(enum vga_color fg, enum vga_color bg);

/**
 * @brief Write the character @c c to VGA
 * @param c The character to write
 */
void vga_putchar(char c);

/**
 * @brief Write data to VGA
 * @param data The data to write.
*/
void vga_writestring(const char* data);

#ifdef __cplusplus
}
#endif
