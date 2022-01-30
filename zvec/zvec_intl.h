#ifndef Z_VECTOR_INTERNAL_H
#define Z_VECTOR_INTERNAL_H

#include <stdlib.h>
#include "include/zvec.h"

#define LREM_RATIO_ORDER 3
#define MAX_RESERVED 8
#define RAR_MIN_UNIT 4

struct zvec {
  void* head;
  int32_t lrem;
  int32_t rrem;
  int32_t cap;
  size_t soe;
};

void zvec_intl_rar(zvec_t*, int32_t);
void zvec_intl_shrink(zvec_t*);
int32_t zvec_intl_grow(zvec_t*);

#endif
