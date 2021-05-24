#ifndef _BST_H
#define _BST_H

#include "sub/BST.c"
void BST_insert(bst **root, int key);
bst *BST_find(bst *root, int key);

#endif