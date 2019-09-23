#include <stdio.h>

#include "list.h"

void print(value_type v)
{
    printf("%4d", v);
}

int main()
{
    list l;
    int i;

    init(&l);
    for (i = 0; i < 10; ++i) push_back(&l, i);
    foreach(&l, print);
    putchar('\n');
    reverse(&l);
    foreach(&l, print);

    return 0;
}