#include <stdio.h>
#include <stdbool.h>

typedef unsigned char   STATUS;

STATUS clear_mask = 0xEF; //11101111
STATUS set_mask = 0x10;   //00010000

void toggle_device(STATUS s)
{
    printf("The device is switched %s.\n", s & set_mask ? "on" : "off"); 
}

int main()
{
    bool not_end = true;
    STATUS s = 0x9b; //10011011
    int choice;
    while (not_end)
    {
        printf("1. switch on\n2. switch off\n3. quit\nplease select:");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1: s |= set_mask; toggle_device(s); break;
            case 2: s &= clear_mask; toggle_device(s); break;
            default: not_end = false;
        }
    }

    return 0;
}