#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int my_strlen(char* s);
char* converter(int d, int base);
char* converter_u(unsigned int d, int base);
char* converter_lu(unsigned long d, int base);
int my_printf(char *fmt, ...);
int read_args(char* fmt, va_list ap, int* i);

// int main()
// {
//     char* test = "test1";
//     my_printf("This is first test: %s\n", test);

//     return 0;
// }

int my_printf(char *fmt, ...)
{
    int sum = 0;
    va_list ap;
    int i = 0;
    va_start(ap, fmt);
    while (fmt[i])
    {
        if (fmt[i] == '%')
        {
            i++;
            sum += read_args(fmt, ap, &i);
        }
        else
        {
            write(1, &fmt[i], 1);
            i++;
            sum++;
        }
    }
    va_end(ap);
    return sum;
}

int read_args(char* fmt, va_list ap, int* i)
{
    int d;
    unsigned int o, x, u;
    void* p;
    char c;
    char *s;
    int sum = 0;
    switch (fmt[*i++])
    {
        case 's':
            s = va_arg(ap, char *);
            sum += write(1, s, my_strlen(s));
            break;
        case 'd':
            d = va_arg(ap, int);
            if (d < 0)
            {
                write(1, "-", 1);
                d = -d;
            }
            s = converter(d, 10);
            sum += write(1, s, my_strlen(s));
            free(s);
            break;
        case 'o':
            o = va_arg(ap, unsigned int);
            s = converter_u(o, 8);
            sum += write(1, s, my_strlen(s));
            free(s);
            break;
        case 'u':
            u = va_arg(ap, unsigned int);
            s = converter_u(u, 10);
            sum += write(1, s, my_strlen(s));
            free(s);
            break;
        case 'x':
            x = va_arg(ap, unsigned int);
            s = converter_u(x, 16);
            sum += write(1, s, my_strlen(s));
            free(s);
            break;
        case 'p':
            p = va_arg(ap, void*);
            unsigned long longVal = (unsigned long)p;
            s = converter_lu(longVal, 16);
            sum += write(1, "0x", 2);
            sum += write(1, s, my_strlen(s));
            free(s);
            break;
        case 'c':              /* char */
            /* need a cast here since va_arg only
                takes fully promoted types */
            c = (char) va_arg(ap, int);
            write(1, &c, 1);
            sum++;
            break;
    }
    return sum;
}

int my_strlen(char* s)
{
    return strlen(s);
}

char* converter(int d, int base)
{
    int tmp;
    char* s = malloc(sizeof(char) * 13);
    int i = 0;
    if (d == 0)
    {
        s[0] = '0';
        s[1] = '\0';
        return s;
    }
    for ( ; d > 0; i++)
    {
        tmp = d % base;
        d = d / base;
        if (tmp < 10)
        {
            s[i] = '0' + tmp;
        }
        else
        {
            s[i] = 'a' + tmp - 10;
        }
    }
    s[i] = '\0';
    int len = my_strlen(s);
    i--;
    for ( ; i >= len / 2; i--)
    {
        char c = s[i];
        s[i] = s[len-i-1];
        s[len-i-1] = c;
    }
	return s;
}

char* converter_u(unsigned int d, int base)
{
    int tmp;
    char* s = malloc(sizeof(char) * 13);
    int i = 0;
    if (d == 0)
    {
        s[0] = '0';
        s[1] = '\0';
        return s;
    }
    for ( ; d > 0; i++)
    {
        tmp = d % base;
        d = d / base;
        if (tmp < 10)
        {
            s[i] = '0' + tmp;
        }
        else
        {
            s[i] = 'a' + tmp - 10;
        }
    }
    s[i] = '\0';
    int len = my_strlen(s);
    i--;
    for ( ; i >= len / 2; i--)
    {
        char c = s[i];
        s[i] = s[len-i-1];
        s[len-i-1] = c;
    }
	return s;
}

char* converter_lu(unsigned long d, int base)
{
    int tmp;
    char* s = malloc(sizeof(char) * 15);
    int i = 0;
    if (d == 0)
    {
        s[0] = '0';
        s[1] = '\0';
        return s;
    }
    for ( ; d > 0; i++)
    {
        tmp = d % base;
        d = d / base;
        if (tmp < 10)
        {
            s[i] = 48 + tmp;
        }
        else
        {
            s[i] = 97 + tmp - 10;
        }
    }
    s[i] = '\0';
    int len = strlen(s);
    i--;
    for ( ; i >= len / 2; i--)
    {
        char c = s[i];
        s[i] = s[len-i-1];
        s[len-i-1] = c;
    }
	return s;
}
