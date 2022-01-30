#ifndef Z_VECTOR_H
#define Z_VECTOR_H

#include <inttypes.h>
#include "./zcmp.h"

typedef struct zvec zvec_t;
typedef void* zvec_it;

zvec_t* zvec_new(size_t);
zvec_t* zvec_from(const void*, int32_t, size_t);
zvec_t* zvec_slice(zvec_t*, zvec_it, zvec_it);
void zvec_free(zvec_t*);
void zvec_clear(zvec_t*);
int32_t zvec_reserve(zvec_t*, int32_t);
int32_t zvec_size(zvec_t*);
int32_t zvec_cap(zvec_t*);

int32_t zvec_fit(zvec_t*);
int32_t zvec_push(zvec_t*, const void*);
int32_t zvec_pop(zvec_t*, void*);
int32_t zvec_shift(zvec_t*, void*);
int32_t zvec_unshift(zvec_t*, const void*);
int32_t zvec_purge(zvec_t*, const void*);
void zvec_rm(zvec_t*, zvec_it);
int32_t zvec_add(zvec_t*, zvec_it, const void*);

int32_t zvec_rm_range(zvec_t*, zvec_it, zvec_it);
int32_t zvec_add_range(zvec_t*, zvec_it, zvec_it, zvec_it);

zvec_it zvec_find(zvec_t*, zvec_it, const void*);
zvec_it zvec_rfind(zvec_t*, zvec_it, const void*);

zvec_it zvec_begin(zvec_t*);
zvec_it zvec_end(zvec_t*);
zvec_it zvec_last(zvec_t*);
zvec_it zvec_at(zvec_t*, int32_t);
int32_t zvec_index(zvec_t*, zvec_it);
int32_t zvec_count(zvec_t*, zvec_it, zvec_it);

void zvec_inc(zvec_t*, zvec_it*);
void zvec_dec(zvec_t*, zvec_it*);
void zvec_mov(zvec_t*, zvec_it*, int32_t);

void zvec_sort(zvec_t*, zvec_it, zvec_it, cmpf);
void zvec_swap(zvec_t*, zvec_it, zvec_it);
void zvec_reverse(zvec_t*, zvec_it, zvec_it);

#define zvec_get(it, ty) *(ty*)it
#define zvec_set(it, val, ty) zvec_get(it, ty) = val

#endif
