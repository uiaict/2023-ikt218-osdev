void *my_memset(void *s, int c, unsigned int len)
{
    unsigned char* p = s;
    while(len--)
    {
        *p++ = (unsigned char)c;
    }
    return s;
}