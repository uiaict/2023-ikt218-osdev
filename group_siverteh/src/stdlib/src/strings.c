#include "strings.h"

//Function that gets the length of a string.
size_t strlen(const char *str)
{
    //Sets up a variable length that keeps track of the length of the string.
    size_t length = 0;

    //While loop that loops through every character in the string and icrements the length for every character.
    while(*str++)
    {
        length++;
    }
    //Returns the length of the string.
    return length;
}

//Function that turns an integer into a string.
void int_to_string(char* str, int num)
{
    //Sets up the variable length that keeps track of the number of digits, and a variable temp that is equal to the num parameter.
    int end_index = 0;
    int temp = num;

    //If the number is 0 turn the string to 0.
    if(num == 0)
    {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    //While loop that gets the number of digits in the integer and stores it in the digits variable.
    while (temp != 0) 
    {
        end_index++;
        temp /= 10;
    }

    //If the number is negative add a minus at the start of the string and turn the number positive. Also increment the digits and i variables.
    if (num < 0) 
    {
        str[0] = '-';
        num = -num;
        end_index++;
    }

    //Set the variable length as the number of digits -1, a.k.a as the length of the number.
    int length = end_index - 1;

    //While the num varieble is not 0
    while (num != 0) 
    {
        //Calculates the remainder of num divided by 10, which gives the rightmost digit of num.
        //Then adds the ASCII value of the character '0' to the remainder to convert it to the corresponding ASCII character.
        str[length--] = num % 10 + '0';
        
        //Updates num by dividing it by 10, which effectively removes the rightmost digit of num.
        num /= 10;
    }

    //Set the character at the end of the string as \0.
    str[end_index] = '\0';
}

//Function that turns a float into a string.
void float_to_string(char* str, float f, int precision) 
{
    //Declares the variable n and sets it as the integer part of the float
    int integer_part = (int) f;
    //Declares the variable frac and sets it as the fractional part of the float
    float fractional_part = f - integer_part;  
    //Declares the variable pow10 that is needed for the fractional part conversion
    int power = 1;  

    //If the float is less than zero it sets the first character of the string to '-', then increments the string.
    if (f < 0) 
    {
        str[0] = '-';
        str++;
    }

    //Computes the power of 10 needed for the fractional part conversion based on the chosen precision.
    for (int p = 0; p < precision; p++) 
    {
        power *= 10;
    }

    //Declares the variable i that keeps track of the length of the integer part of the number.
    int i = 0;

    //If the integer part of the float is equal to 0, the next character in the string is set to 0.
    if (integer_part == 0) 
    {
        str[i++] = '0';
    } 
    //Else the integer part of the float is any number other than 0.
    else 
    {
        //While loop that loops while the integer part of the float is not 0.
        while (integer_part != 0) 
        {
            //Calculates the remainder of integer_part divided by 10, which gives the rightmost digit of the integer_part, then stores it in an int rem.
            int rem = integer_part % 10;

            //Adds the ASCII value of the character '0' to the remainder to convert it to the corresponding ASCII character, and adds it to the string.
            str[i++] = rem + '0';

            //Updates integer_part by dividing it by 10, which effectively removes the rightmost digit of integer_part.
            integer_part /= 10;
        }
   }  

    //For loop that reverses the current string.
    for (int j = 0, int k = i - 1; j < k; j++, k--) 
    {
        //Sets a new char temp equal to the current character in the string.
        char temp = str[j];

        //Sets the character at string position j to the character at string position k.
        str[j] = str[k];

        //Sets the character at the string position k to the character held by temp, a.k.a the original character at string position j.
        str[k] = temp;
    }

    //If the float has a fractional part higher than 0, and the user want a precision higher than 0.
    if (fractional_part > 0 && precision > 0) 
    {
        //Adds a . to the next index in the string.
        str[i++] = '.';

        //Converts the fractional part of the float into integer by multiplying it by the correct power.
        //Then stores it in the variable fractional_part_integer. Adds 0.5 to round it to the nearest integer.
        int fractional_part_integer = (int) (fractional_part * power + 0.5);

        //While loop that loops while the precision is higher than 0, and is used to extract each digit from the fractional part of the float.
        while (precision > 0) 
        {
            //Sets the power as itself divided by 10.
            power /= 10;
            //Sets the variable digit equal to the fractional_part_integer divided by the power.
            int digit = fractional_part_integer / power;
            //Adds the ASCII value of the character '0' to the current digit to convert it to the corresponding ASCII character, and adds it to the string.
            str[i++] = digit + '0';
            //Sets the fractional_part_integer to itself minus the current digit multiplied by the power.
            fractional_part_integer -= digit * power;
            //Decreases the precision.
            precision--;
        }
    }
    //Sets the character at the end of the string to \0.
    str[i] = '\0';
}

int isalnum(int c)
{
    if((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
    {
        return 1;
    }
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

//Function for turning a string into lowercase.
void to_lower(char* str)
{
    //While loop that loops through every character in the string.
    while(*str != '\0')
    {
        //If the current character is between 65 and 90 it is an uppercase letter.
        if(*str >= 65 && *str <= 90)
        {
            //Add 32 to the ascii value of the character to turn it into a lowercase character.
            *str += 32;
        }
        *str++;
    }
}

//Function that checks if a character is uppercase.
int isupper(int c)
{
    //If the ascii value is between 65 and 90 it is an uppercase letter so we return 1 for true.
    if(c >= 65 && c <= 90)
    {
        return 1;
    }
    //Else return 0 for false;
    return 0;
}

//Function that checks if a character is lowercase.
int islower(int c)
{
    //If the ascii value is between 65 and 90 it is a lowercase letter so we return 1 for true.
    if(c >= 97 && c <= 122)
    {
        return 1;
    }
    //Else return 0 for false;
    return 0;
}