#ifndef Z_VECTOR_INTERNAL_H
#define Z_VECTOR_INTERNAL_H

#include <stdlib.h>
#include "include/zvec.h"

#define LREM_RATIO_ORDER 3
#define MIN_CAPACITY 16
#define RAR_MIN_UNIT 4

struct zvec {
  void* head;
  int32_t lrem;
  int32_t rrem;
  int32_t cap;
  uint32_t soe;
};

void zvec_intl_rar(zvec_t*, int32_t);

#endif
