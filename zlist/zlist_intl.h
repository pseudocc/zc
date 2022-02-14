#ifndef Z_LINKEDLIST_INTERNAL_H
#define Z_LINKEDLIST_INTERNAL_H

#include <stdlib.h>
#include "include/zvec.h"

struct zlist {
  void* head;
  size_t soe;
  size_t size;
  zvec_t freed;
};

inline void* zlnode_new(zlist_t);
inline void zlnode_free(zlist_t, void*);

#endif
