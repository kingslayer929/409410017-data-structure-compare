#include <stdlib.h>
typedef struct bst bst;

struct bst{
    int key;
    bst *L, *R;
};

void bst_insert(bst **root, int key){
    bst **p = root, *t = *p;
    while((t = *p)){
        if(key < t->key) p = &t->L;
        else if(key > t->key) p = &t->R;
        else return;
    }
    t = *p = (bst *)malloc(sizeof(bst));
    t->key = key;
    t->L = t->R = NULL;
}

bst *bst_find(bst *root, int key){
    bst *p = root;
    while(p){
        if(key < p->key) p = p->L;
        else if(key > p->key) p = p->R;
        else return p;
    }
    return NULL;
}