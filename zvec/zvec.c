#include <stdio.h>
#include <string.h>
#include "./zvec_intl.h"

static inline
void zvec_priv_clear(zvec_t* this, int32_t cap) {
  this->lrem = cap >> LREM_RATIO_ORDER;
  this->rrem = cap - this->lrem;
  this->cap = cap;
}

zvec_t* zvec_new(size_t soe) {
  zvec_t* inst;

  inst = malloc(sizeof(zvec_t));
  inst->head = NULL;
  inst->soe = soe;
  inst->cap = 0;
  inst->lrem = inst->rrem = 0;

  return inst;
}

zvec_t* zvec_from(const void* arr, int32_t n, size_t soe) {
  zvec_t* inst;
  int32_t cap;
  size_t n_bytes;

  n_bytes = n * soe;
  inst = malloc(sizeof(zvec_t));
  inst->head = malloc(n_bytes + soe);

  if (inst->head == NULL) {
    fprintf(stderr, "Out of memory, "
      "%ld bytes are required", n_bytes + soe);
    free(inst);
    return NULL;
  }

  inst->soe = soe;
  inst->cap = n;
  inst->lrem = inst->rrem = 0;
  
  if (arr == NULL)
    memset(inst->head, 0, n_bytes);
  else
    memcpy(inst->head, arr, n_bytes);

  return inst;
}

void zvec_free(zvec_t* this) {
  free(this->head);
  free(this);
}

void zvec_clear(zvec_t* this) {
  zvec_intl_shrink(this);
  zvec_priv_clear(this, this->cap);
}

int32_t zvec_reserve(zvec_t* this, int32_t cap) {
  void* nhead;
  int32_t more;
  if (cap <= this->cap)
    return 0;

  nhead = realloc(this->head, (cap + 1) * this->soe);
  if (nhead == NULL)
    return 0;

  this->head = nhead;
  this->rrem += more = cap - this->cap;
  this->cap = cap;
  return more; 
}

int32_t zvec_size(zvec_t* this) {
  return this->cap - this->lrem - this->rrem;
}

int32_t zvec_cap(zvec_t* this) {
  return this->cap;
}
