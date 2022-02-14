#ifndef Z_LINKEDLIST_H
#define Z_LINKEDLIST_H

#include <inttypes.h>
#include "./zcmp.h"

typedef struct zlist zlist_t;
typedef void** zlist_it;

zlist_t* zlist_new(uint32_t);
void zlist_free(zlist_t*);
void zlist_size(zlist_t*);

int32_t zlist_push(zlist_t*, const void*);
int32_t zlist_pop(zlist_t*, void*);
void zlist_rm(zlist_t*, zlist_it)
int32_t zlist_add(zlist_t*, zlist_it, const void*);

zlist_it zlist_find(zlist_t*, zlist_it, const void*);

zlist_it zlist_first(zlist_t*);
zlist_it zlist_at(zlist_t*, int32_t);
int32_t zlist_index(zlist_t*, zlist_it);
void zlist_next(zlist_t*, zlist_it*);

void zlist_sort(zlist_t*, zlist_it, zlist_it, cmpf);
void zlist_swap(zlist_t*, zlist_it, zlist_it);
void zlist_reverse(zlist_t*, zlist_it, zlist_it);

#define zlist_get(it, ty) *(ty*)(*it)
#define zlist_set(it, val, ty) zlist_get(it, ty) = val

#endif
