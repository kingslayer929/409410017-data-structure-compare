#ifndef _HASH_H
#define _HASH_H

#include "sub/hash.c"
void H_init(hash *h);
void H_insert(hash *h, int key);
void H_find(hash *h, int key);

#endif