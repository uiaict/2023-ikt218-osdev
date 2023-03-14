#include "boot.h"
#include "../../kernel/src/drivers/screen.h"

extern "C" {
    void initialize_multiboot(uint32_t magic, multiboot_info info);
    #include "strings.h"
}

void initialize_multiboot(uint32_t magic, multiboot_info info)
{
    //Initilizes the terminal output
    terminal_clear();
    //Declares two char pointers "eax_buf" and "mb_magic_buf"
    char* eax_buf;
    char* mb_magic_buf;
    
    //Gets the eax_buf and magic numbers and converts them to strings, and stores them in the previously declared char pointers.
    int_to_string(eax_buf, magic);
    int_to_string(mb_magic_buf, MULTIBOOT_BOOTLOADER_MAGIC);

    //Checks that the magic number is equal to the MULTIBOOT_BOOTLOADER_MAGIC number.
    if(magic != (multiboot_uint32_t)MULTIBOOT_BOOTLOADER_MAGIC)
    {
        while (1)
        {
            //If they are not equal something is wrong and an error message is printed
            printf("Magic number is invalid. Found: %s != %s\n", eax_buf, mb_magic_buf);
        }//Error
        
    }
    //If they are equal the multiboot check went okay.
    printf("Multiboot check went OK. eax=%s, magic=%s\n", eax_buf, mb_magic_buf);
}