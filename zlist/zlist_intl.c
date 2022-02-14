#include "./zlist_intl.h"

inline void* zlnode_new(zlist_t* this) {
  size = this->soe + sizeof(void*);
  return malloc(size);
}
