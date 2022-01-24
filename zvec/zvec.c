#include <stdio.h>
#include "./zvec_intl.h"

static inline
void zvec_priv_clear(zvec_t* this, int32_t cap) {
  this->lrem = cap >> LREM_RATIO_ORDER;
  this->rrem = cap - this->lrem;
  this->cap = cap;
}

zvec_t* zvec_new(int32_t cap, uint32_t soe) {
  zvec_t* inst;
  if (cap < 0)
    return NULL;
  cap = cap ? cap : MIN_CAPACITY;

  inst = malloc(sizeof(zvec_t));
  inst->head = malloc((cap + 1) * soe);

  if (inst->head == NULL) {
    fprintf(stderr, "Out of memory, require %d bytes", (cap + 1) * soe);
    free(inst);
    return NULL;
  }

  inst->soe = soe;
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
    this->head = realloc(this->head, (cap + 1) * this->soe);
  }
  zvec_priv_clear(this, cap);
}

int32_t zvect_size(zvec_t* this) {
  return this->cap - this->lrem - this->rrem;
}

int32_t zvec_cap(zvec_t* this) {
  return this->cap;
}
