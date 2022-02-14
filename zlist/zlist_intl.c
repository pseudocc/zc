#include "./zlist_intl.h"

inline void* zlnode_new(zlist_t this) {
  return malloc(sizeof(void*) + this->soe);
}

inline void zlnode_free(zlist_t this, void* lnode) {
  int32_t diff;
  size_t psrv = this->size << PRESRV_RATIO_ORDER;
  if (psrv > INT_MAX)
    psrv = INT_MAX;
  diff = zvec_size(this->psrv) - psrv;
  if (diff < 0) {
    zvec_push(this->psrv, lnode);
    return;
  }
  free(lnode);
  while (diff--) {
    zvec_pop(this->psrv, &lnode);
    free(lnode);
  }
}
