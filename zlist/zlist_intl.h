#ifndef Z_LINKEDLIST_INTERNAL_H
#define Z_LINKEDLIST_INTERNAL_H

#include <stdlib.h>

struct zlist {
  void* head;
  size_t soe;
  size_t size;
};

inline void* zlnode_new(zlist_t*);
inline void zlnode_free(void*);

#endif
