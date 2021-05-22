#include <stdlib.h>
typedef struct list list;

struct list{
    int key;
    list *next;
};

void L_insert(list **head, int key){
    list *p;
    p = (list *)malloc(sizeof(list));
    p->key = key;
    p->next = *head;
    *head = p;
}

list *L_find(list *head, int key){
    list *p = head;
    while(p){
        if(p->key == key)
            return p;
        p = p->next;
    }
    return NULL;
}