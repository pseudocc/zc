#ifndef Z_LINKEDLIST_INTERNAL_H
#define Z_LINKEDLIST_INTERNAL_H

#include <stdlib.h>

struct zlist {
  void* head;
  void* tail;
  uint32_t soe;
  uint32_t size;
};

void* zlnode_new(zlist_t*);
void zlnode_free(void*);

#endif
