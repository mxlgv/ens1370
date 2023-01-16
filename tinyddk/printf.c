#include <kos_drv.h>
#include <types.h>

static void putchar(char c)
{
    static char str[2]; 
    str[0] = c;
    str[1] = '\0';
    putstring(str);
}

static void putuint(int i)
{
    unsigned int n, d = 1000000000;
    char str[255];
    unsigned int dec_index = 0;

    while ((i / d == 0) && (d >= 10)) {
        d /= 10;
    }
    n = i;

    while (d >= 10) {
        str[dec_index++] = ((char)((int)'0' + n / d));
        n = n % d;
        d /= 10;
    }

    str[dec_index++] = ((char)((int)'0' + n));
    str[dec_index] = 0;
    putstring(str);
}

static void putint(int i)
{
    if (i >= 0) {
        putuint(i);
    } else {
        putchar('-');
        putuint(-i);
    }
}

static void puthex(unsigned i)
{
    const unsigned char hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    unsigned int n, d = 0x10000000;

    putstring("0x");

    while ((i / d == 0) && (d >= 0x10)) {
        d /= 0x10;
    }
    n = i;

    while (d >= 0xF) {
        putchar(hex[n / d]);
        n = n % d;
        d /= 0x10;
    }

    putchar(hex[n]);
}

static void print(char *format, va_list args)
{
    int i = 0;
    char *string;

    while (format[i]) {
        if (format[i] == '%') {
            i++;
            switch (format[i]) {
            case 's':
                string = va_arg(args, char *);
                putstring(string);
                break;
            case 'c':
                // TODO: Fix this! "warning: cast to pointer from integer of different size"
                putchar(va_arg(args, int));
                break;
            case 'd':
                putint(va_arg(args, int));
                break;
            case 'i':
                putint(va_arg(args, int));
                break;
            case 'u':
                putuint(va_arg(args, unsigned int));
                break;
            case 'x':
                puthex(va_arg(args, unsigned int));
                break;
            default:
                putchar(format[i]);
            }
        } else {
            putchar(format[i]);
        }
        i++;
    }
}

void printk(char *text, ...)
{
    va_list args;
    va_start(args, text);
    print(text, args);
}
