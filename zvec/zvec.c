#include <stdio.h>
#include "./zvec_intl.h"

#define MIN_CAPACITY 16

static inline
void zvec_priv_clear(zvec_t* this, int32_t cap) {
  this->lrem = cap >> LREM_RATIO_ORDER;
  this->rrem = cap - this->lrem;
  this->n_items = 0;
}

zvec_t* zvec_new(int32_t cap, uint32_t n_bytes) {
  zvec_t* inst;
  if (cap < MIN_CAPACITY)
    cap = MIN_CAPACITY;

  inst = malloc(sizeof(zvec_t));
  inst->head = malloc(cap * n_bytes);

  if (inst->head == NULL) {
    fprintf(stderr, "Out of memory, require %d bytes",
      cap * n_bytes);
    free(inst);
    return NULL;
  }

  zvec_priv_clear(inst, cap);
  return inst;
}

void zvec_free(zvec_t* this) {
  free(this->head);
  free(this);
}

void zvec_clear(zvec_t* this) {
  int32_t cap = zvec_cap(this);
  if (cap > MIN_CAPACITY) {
    cap = MIN_CAPACITY;
    this->head = realloc(this->head, cap * this->n_bytes);
  }
  zvec_priv_clear(this, cap);
}