#include <stdint.h>
#include <stdio.h>

#define STR_SIZE 100
char result_str[STR_SIZE];

// const char format[] - contains the format string
// void *value - is a value to insert instead of %s, %n or %c placeholder
// the function should return the result in C-string format.
const char * sprintf_m(const char format[], const void *value)
{
    unsigned int i = 0; // byte counter

    for (i=0; i<STR_SIZE; i++) // cleanup
        result_str[i] = 0;

    i=0;
    while (i<STR_SIZE)
    {
        if (format[i]=='%') // exit loop in case '%' symbol
            break;
        i++;
    }

    //copy all data which are before %
    int n;
    for (n=0; n<i; n++)
    {
        result_str[n] = format[n];
    }

    uint8_t *ptr = (uint8_t*)value;
    uint8_t nvalue = (uint8_t)(*ptr);
    uint8_t ascii_shift = 48 ;
    n=i; // number where % is located
    switch (format[n+1])
    {
        case 's': // string
        while (((char)(*ptr))!=0)
        {
            result_str[n] = (char) (*ptr);
            ptr++;
            n++;
        }
        break;

        case 'n': // number
        result_str[n] = ( nvalue / 100 ) ; // Nxx
        result_str[n+1] = ( ( nvalue - ( result_str[n] * 100 )  ) / 10 )  ; // xNx
        result_str[n+2] = nvalue - ( ( result_str[n] * 100 ) + (result_str[n+1] * 10)  ); // xxN
        result_str[n] += ascii_shift;
        result_str[n+1] += ascii_shift;
        result_str[n+2] += ascii_shift;
        n = n + 3;
        break;

        case 'c':
        result_str[n] = (char) nvalue;
        n++;
        break;

        default:
            //printf("!!!");
        break;
    }

    //copy all last data which are after %n %c %s
    i=i+2; // shift after %N
    while (format[i]!=0 && n<STR_SIZE)
    {
        result_str[n] = format[i];
        n++; i++;
    }

    return result_str;

}

int main(int argc, char *argv[])
{
    const char *formatS = "Hello %s!";
    const char *world = "World";
    const char *formatN = "Value: %n";
    const uint8_t a = 42;
    const char *formatC = "Char: %c";
    const char c = 'P';
    const char *result;

    result = sprintf_m(formatC, (const void *) &c);
    printf("%s\n", result); //should print: Character: P

    result = sprintf_m(formatN, (const void *) &a);
    printf("%s\n", result); //should print: Value: 42

    result = sprintf_m(formatS, (const void *) world);
    printf("%s\n", result); //should print: Hello World!

    return 0;
}
