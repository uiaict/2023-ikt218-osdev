// Written by group 39, IKT218 prosjekt, spring 2023

// Implements memory functions such as memset.

void * memset(void * target, int value, unsigned int length)
{
    unsigned char * pointer = (unsigned char *)target;

    while (length--)
    {
        *pointer++ = (unsigned char)value;
    }
    return target;
}