#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef int value_type;

typedef void callback(value_type);

typedef struct _node
{
    value_type data;
    struct _node *next;
} node, *node_ptr;

typedef struct 
{
    node_ptr head, tail;
} list, *list_ptr;

extern void init(list_ptr);
extern void push_back(list_ptr, value_type);
extern void clear(list_ptr);
extern void foreach(list_ptr, callback);
extern void reverse(list_ptr);