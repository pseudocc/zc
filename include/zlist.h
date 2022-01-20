#ifndef Z_LINKEDLIST_H
#define Z_LINKEDLIST_H

#include <inttypes.h>

typedef struct lnode zlist;

struct lnode {
  int32_t value;
  struct lnode* next;
};

#endif
