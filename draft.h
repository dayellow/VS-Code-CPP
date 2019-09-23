#pragma once
#include<stdio.h>
#include<stdbool.h>
#define STACK_SIZE 100
extern int contents[STACK_SIZE];
extern int top;
extern void make_empty(void);
extern bool is_empty(void);
extern bool is_full(void);
extern void push(int i);
extern int pop(void);

