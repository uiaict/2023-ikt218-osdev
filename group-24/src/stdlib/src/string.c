#include <cstring>

// Function that gets the length of a string.
int strlen(const char *str)
{
    // Sets up a variable length that keeps track of the length of the string.
    int length = 0;

    // While loop that loops through every character in the string and increments the length for every character.
    while (*str++)
    {
        length++;
    }
    // Returns the length of the string.
    return length;
}

// Function that turns an integer into a string.
void int_to_string(char* str, int num)
{
    // Sets up the variable length that keeps track of the number of digits, and a variable temp that is equal to the num parameter.
    int end_index = 0;
    int temp = num;

    // If the number is 0, turn the string to "0" and return.
    if (num == 0)
    {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    // While loop that gets the number of digits in the integer and stores it in the digits variable.
    while (temp != 0)
    {
        end_index++;
        temp /= 10;
    }

    // If the number is negative, add a minus at the start of the string and turn the number positive. Also increment the end_index variable.
    if (num < 0)
    {
        str[0] = '-';
        num = -num;
        end_index++;
    }

    // Set the variable length as the number of digits -1, a.k.a as the length of the number.
    int length = end_index - 1;

    // While the num variable is not 0
    while (num != 0)
    {
        // Calculates the remainder of num divided by 10, which gives the rightmost digit of num.
        // Then adds the ASCII value of the character '0' to the remainder to convert it to the corresponding ASCII character.
        str[length--] = num % 10 + '0';

        // Updates num by dividing it by 10, which effectively removes the rightmost digit of num.
        num /= 10;
    }

    // Set the character at the end of the string as '\0'.
    str[end_index] = '\0';
}

// Function that turns a float into a string.
void float_to_string(char* str, float f, int precision)
{
    // Converts the float to a string using sprintf.
    sprintf(str, "%.*f", precision, f);
}

// Function that checks if the character is a number or alphabetic letter.
int isalnum(int c)
{
    // If the ASCII value corresponds to 0-9, a-z, or A-Z return 1 for true.
    if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
    {
        return 1;
    }
    // Else return 0 for false.
    return 0;
}

// Function that checks if the character is an alphabetic letter.
int isalpha(int c)
{
    // If the ASCII value corresponds to a-z or A-Z return 1 for true.
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
    {
        return 1;
    }
    // Else return 0 for false.
    return 0;
}
//Function for turning a string into uppercase.
void to_upper(char* str)
{
    //While loop that loops through every character in the string.
    while(*str != '\0')
    {
        //If the current character is between 97 and 122 it is a lowercase letter.
        if(*str >= 97 && *str <= 122)
        {
            //Take away 32 from the ascii value of the character to turn it into a uppercase character.
            *str -= 32;
        }
        *str++;
    }
}

// Function for turning a string into uppercase.
void to_upper(char* str)
{
    // While loop that loops through every character in the string.
    while (*str)
    {
        // If the character is a lowercase letter, subtract 32 from the ASCII value to convert it to uppercase.
        if (*str >= 'a' && *str <= 'z')
        {
            *str -= 32;
        }
        // Moves to the next character in the string.
        str++;
    }
}

// Function for turning a character into uppercase.
char to_upper_char(char c)
{
    // If the character is a lowercase letter, subtract 32 from the ASCII value to convert it to uppercase.
    if (c >= 'a' && c <= 'z')
    {
        c -= 32;
    }
    // Returns the uppercase character.
    return c;
}

// Function for turning a string into lowercase.
void to_lower(char* str)
{
    // While loop that loops through every character in the string.
    while (*str)
    {
        // If the character is an uppercase letter, add 32 to the ASCII value to convert it to lowercase.
        if (*str >= 'A' && *str <= 'Z')
        {
            *str += 32;
        }
        // Moves to the next character in the string.
        str++;
    }
}

// Function that checks if the character is uppercase.
int isupper(int c)
{
    // If the ASCII value corresponds to A-Z return 1 for true.
    if (c >= 65 && c <= 90)
    {
        return 1;
    }
    // Else return 0 for false.
    return 0;
}

// Function that checks if the character is lowercase.
int islower(int c)
{
    // If the ASCII value corresponds to a-z return 1 for true.
    if (c >= 97 && c <= 122)
    {
        return 1;
    }
    // Else return 0 for false.
    return 0;
}

// Function that compares two strings.
int strcmp(char s1[], char s2[])
{
    // While loop that compares each character in the strings until a difference is found or the end of one of the strings is reached.
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }

    // Returns the difference in ASCII values of the differing characters.
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

// Function that appends a character to a string.
void append(char* s, char n)
{
    // Gets the length of the string using strlen.
    int length = strlen(s);

    // Sets the character at the end of the string as n and adds a null terminator.
    s[length] = n;
    s[length + 1] = '\0';
}