#ifndef _LIST_H
#include "../list.h"
#endif
#define MAX_HASH 1000000
typedef struct hash hash;

struct hash{
    list **head;
    list *find;
};

int hashmod(int key){
    return key % MAX_HASH;
}

void H_init(hash *h){
    h->head = (list **)malloc(sizeof(list *) * MAX_HASH);
    for (int i = 0; i < MAX_HASH; i++){
        h->head[i] = NULL;
    }
}

void H_insert(hash *h, int key){
    int r = hashmod(key);
    L_insert(&h->head[r], key);
}

void H_find(hash *h, int key){
    int r = hashmod(key);
    h->find =  L_find(h->head[r], key);
}