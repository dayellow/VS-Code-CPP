#include "list.h"

void init(list_ptr l)
{
    l->head = l->tail = '\0';
}

void push_back(list_ptr l, value_type v)
{
    node_ptr p = (node_ptr)malloc(sizeof(node));
    p->data = v;
    p->next = '\0';

    !l->head ? (l->head = p) : (l->tail->next = p); 
    l->tail = p;
}

void clear(list_ptr l)
{
    node_ptr p = l->head, q;

    while (p)
    {
        q = p;
        p = p->next;
        free(q);
    }
}

void foreach(list_ptr l, callback f)
{
    node_ptr p = l->head;

    while (p)
    {
        f(p->data);
        p = p->next;
    }
}

void reverse(list_ptr l)
{
    node_ptr p, q, t;

    p = l->head;
    if (!p) return;
    
    l->tail = l->head;
    q = p->next;
    l->tail->next ='\0';

    while (q)
    {
        t = q;
        q = q->next;
        t->next = p;
        p = t;
    }
    l->head = p;
}