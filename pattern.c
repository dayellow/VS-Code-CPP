#include <stdio.h>

#define SCANLINE    8
#define PIXEL       8
#define DOT         '#'
#define SPACE       ' '

unsigned char pattern[] = { 0x7c, 0x02, 0x02, 0x7e, 0x82, 0x82, 0x7c, 0x00 };

int main()
{
    int i, j;
    unsigned char p;

    for (i = 0; i < SCANLINE; ++i)
    {
        p = pattern[i];
        for (j = 0; j < PIXEL; ++j)
        {
            putchar(p & 0x01 ? DOT : SPACE);
            p >>= 1;
        }
        putchar('\n');
    }

    return 0;
}