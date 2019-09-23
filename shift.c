#include <stdio.h>

int main()
{
    int a = 0x6a,   //00000000000000000000000001101010, 106
        b = 0xFFFFFF6a;  //11111111111111111111111101101010, -150
    int c, d, e, f;
    
    c = a >> 1;
    d = b >> 1;
    e = a << 2;
    f = b << 2;
    printf("a=%d,b=%d,c=%d,d=%d,e=%d,f=%d哈哈哈\n", a, b, c, d, e, f);

    return 0;
}
