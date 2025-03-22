#include <stdlib.h>
#include <stdarg.h>
#include "printf.h"

static int putstr(const char *s)
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
        if (prec > 0) {
            putchar('0');
            putchar('.');
            while (prec--)
                putchar('0');
        } else {
            putchar('0');
        }
        return;
    }

    p = str + MAXDIGITS;  // End of the string
    *p = '\0';

    while (d > 0 || dp < prec) // Include leading zeros for precision
    {
        if (prec > 0 && dp == prec)  // Add decimal point when required
        {
            p--;
            *p = '.';
        }
        p--;  // Create space for next digit
        *p = hex[d % base];  // Write the digit
        dp++;
        d /= base;
    }

    // Add leading zeros for precision if necessary
    if (dp <= prec)
    {
        while (dp < prec) {
            p--;
            *p = '0';
            dp++;
        }
        p--;
        *p = '.';
        p--;
        *p = '0';
    }

    putstr(p);
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
    putstr("0x");
    putnum(x, 16, 0);

    return;
}

void putf(float f)
{
    if ((int) (100*f) >= 0)
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
    if ((int) (100*lf) >= 0)
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

int puts(const char *s)
{
    putstr(s);
    putchar('\n');

    return 0;   // non-standard return
}

int printf(const char *type_string, ...)
{
    const char *p = type_string;
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
            {
                putchar('%');   // trailing '%'
                break;
            }

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
                    putstr(p_val);
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
