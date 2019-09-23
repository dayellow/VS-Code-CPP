#include"draft.h"
int contents[STACK_SIZE];
int top=-1;
void make_empty(void)
{
    top=-1;
}
bool is_empty(void)
{
    return top==-1;
}
bool is_full(void)
{
    return top==STACK_SIZE;
}
void push(int i)
{
    if(!is_full())
        contents[++top]=i;
}
int pop(void)
{
    if(!is_empty())
        return contents[top--];
}