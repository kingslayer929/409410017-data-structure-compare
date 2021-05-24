#ifndef _LIST_H
#define _LIST_H

#include "sub/list.c"
void L_insert(list **head, int key);
list *L_find(list *head, int key);

#endif