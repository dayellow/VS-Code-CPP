#include <stdio.h>

struct bit_field //压缩在一个unsigned里
{
	unsigned optr : 2;
	unsigned lhs : 3;
	unsigned rhs : 3;
    unsigned reserved: 24;
};

typedef union
{
    struct bit_field instruction_bf;
    unsigned instruction_word;
} instruction;

int main()
{
    instruction i;
    i.instruction_word = 0x74; //01110100
    unsigned result;

    switch (i.instruction_bf.optr)
    {
        case 0x00: result = i.instruction_bf.lhs + i.instruction_bf.rhs; break;
        case 0x01: result = i.instruction_bf.lhs - i.instruction_bf.rhs; break;
        case 0x02: result = i.instruction_bf.lhs * i.instruction_bf.rhs; break;
        case 0x03: result = i.instruction_bf.lhs / i.instruction_bf.rhs; break;
    }

    printf("the result is %u\n", result);

    return 0;
}
