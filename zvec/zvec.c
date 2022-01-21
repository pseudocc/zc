#include <stdio.h>
#include "./zvec_intl.h"

#define MIN_CAPACITY 16

static inline
void zvec_priv_clear(zvec_t* this, int32_t cap) {
  this->lrem = cap >> LREM_RATIO_ORDER;
  this->rrem = cap - this->lrem;
  this->cap = cap;
}

zvec_t* zvec_new(int32_t cap, uint32_t soe) {
  zvec_t* inst;
  if (cap < MIN_CAPACITY)
    cap = MIN_CAPACITY;

  inst = malloc(sizeof(zvec_t));
  inst->head = malloc(cap * soe);

  if (inst->head == NULL) {
    fprintf(stderr, "Out of memory, require %d bytes", cap * soe);
    free(inst);
    return NULL;
  }

  inst->soe = n_bytes;
  inst->cap = cap;
  zvec_priv_clear(inst, cap);

  return inst;
}

void zvec_free(zvec_t* this) {
  free(this->head);
  free(this);
}

void zvec_clear(zvec_t* this) {
  int32_t cap = this->cap;
  if (cap > MIN_CAPACITY) {
    cap = MIN_CAPACITY;
    this->head = realloc(this->head, cap * this->soe);
  }
  zvec_priv_clear(this, cap);
}
