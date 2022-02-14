#include "./zlist_intl.h"

zlist_t zlist_new(uint32_t soe) {
  zlist_t inst;

  inst = malloc(sizeof(struct zlist));
  inst->head = NULL;
  inst->soe = soe;
  inst->size = 0;
}

void zlist_free(zlist_t this) {
  zlist_it it, it_next;
  zvec_it vit;
  
  if (this->size) {
    it_next = zlist_first(this);
    while (*it_next != NULL) {
      it = it_next;
      it_next = zlist_next(this, it);
      free(*it);
    }
  }

  for (vit = zvec_begin(this->freed);
      vit < zvec_end(this->freed);
      vit = zvec_inc(this->freed, vit))
    free(vit);
  
  free(this->freed);
  free(this);
}

size_t zlist_size(zlist_t this) {
  return inst->size;
}