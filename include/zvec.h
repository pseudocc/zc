#ifndef Z_VECTOR_H
#define Z_VECTOR_H

#include <inttypes.h>

typedef struct zvec zvec_t;
typedef void* zvec_it;

zvec_t* zvec_new(int32_t, uint32_t);
void zvec_free(zvec_t*);
void zvec_clear(zvec_t*);

int32_t zvec_fit(zvec_t*);
int32_t zvec_push(zvec_t*, const void*);
int32_t zvec_pop(zvec_t*, void*);
int32_t zvec_shift(zvec_t*, void*);
int32_t zvec_purge(zvec_t*, const void*);
void zvec_rm(zvec_t*, zvec_it);
int32_t zvec_add(zvec_t*, zvec_it, const void*);

zvec_it zvec_find(zvec_t*, zvec_it, const void*);
zvec_it zvec_rfind(zvec_t*, zvec_it, const void*);

zvec_it zvec_begin(zvec_t*);
zvec_it zvec_end(zvec_t*);
zvec_it zvec_at(zvec_t*, int32_t);
int32_t zvec_index(zvec_t*, zvec_it*);

void zvec_inc(zvec_t*, zvec_it*);
void zvec_dec(zvec_t*, zvec_it*);
void zvec_mov(zvec_t*, zvec_it*, int32_t);

uint32_t zvec_size(zvec_t*);
uint32_t zvec_cap(zvec_t*);

typedef int (*cmpf)(const void*, const void*);
void zvec_sort(zvec_t*, zvec_it, zvec_it, cmpf);

#endif