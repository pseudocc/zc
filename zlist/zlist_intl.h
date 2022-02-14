#ifndef Z_LINKEDLIST_INTERNAL_H
#define Z_LINKEDLIST_INTERNAL_H

#include <stdlib.h>
#include "include/zvec.h"

#define PRESRV_RATIO_ORDER 1
#define MIN_PRESRV 4

struct zlist {
  void* head;
  size_t soe;
  size_t size;
  zvec_t psrv;
};

void* zlnode_new(zlist_t);
void zlnode_free(zlist_t, void*);

#endif
