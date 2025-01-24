#include <stdlib.h>
#include <stdarg.h>
#include "printf.h"

int puts(const char *s)
{
    while(*s)
    {
        putchar(*s);
        s++;
    }

    return 0;   // non-standard
}

#define MAXDIGITS (10+1+2)
static void putnum(unsigned int d, int base, int prec)
{
    char hex[] = "0123456789abcdef";
    char *p, str[MAXDIGITS+1];
    int dp = 0;

    if (d == 0)
    {
        putchar('0');
        return;
    }

    p = str + MAXDIGITS;        // end of the string
    *p = '\0';
    while (d > 0)
    {
        p--;                    // create space
        *p = hex[d % base];     // write the digit
        dp++;

        if (dp == prec)
        {
            p--;
            *p = '.';
        }
        d /= base;
    }
    puts(p);

    return;
}

void putd(int d)
{
    if (d >= 0)
    {
        putnum(d, 10, 0);
    }
    else
    {
        putchar('-');
        putnum(-d, 10, 0);
    }

    return;
}

void putx(unsigned int x)
{
    puts("0x");
    putnum(x, 16, 0);

    return;
}

void putf(float f)
{
    if (f > 0)
    {
        putnum(f*100, 10, 2);
    }
    else
    {
        putchar('-');
        putnum(-f*100, 10, 2);
    }

    return;
}

void putlf(double lf)
{
    if (lf > 0)
    {
        putnum(lf*100, 10, 2);
    }
    else
    {
        putchar('-');
        putnum(-lf*100, 10, 2);
    }

    return;
}

int printf(char *type_string, ...)
{
    char *p = type_string;
    char c_val;
    int i_val;
    float f_val;
    char *p_val;
    va_list args;
    va_start(args, type_string);

    while (*p != '\0')
    {
        if (*p == '%')
        {
            p++;
            if (*p == '\0')
                break;

            switch (*p)
            {
                case 'c':
                    c_val = (char) va_arg(args, int);
                    putchar(c_val);
                    break;
                case 'd':
                    i_val = (int) va_arg(args, int);
                    putd(i_val);
                    break;
                case 'x':
                    i_val = (int) va_arg(args, int);
                    putx(i_val);
                    break;
                case 'f':
                    f_val = (float) va_arg(args, double);
                    putf(f_val);
                    break;
                case 's':
                    p_val = (char *) va_arg(args, char *);
                    puts(p_val);
                    break;
                default:
                    putchar('%'); // not a format
                    putchar(*p);
                    break;
            }
        }
        else
            putchar (*p);

        p++;
    }

    va_end(args);

    return 0;   // non-standard return
}
