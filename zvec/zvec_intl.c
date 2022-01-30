#include <string.h>
#include "./zvec_intl.h"

void zvec_intl_rar(zvec_t* this, int32_t unit) {
  zvec_it src, tgt;
  
  tgt = src = zvec_begin(this);
  zvec_mov(this, &tgt, -unit);
  memmove(tgt, src, zvec_size(this) * this->soe);
  
  this->lrem -= unit;
  this->rrem += unit;
}

void zvec_intl_shrink(zvec_t* this) {
  if (this->cap > MAX_RESERVED) {
    this->cap = MAX_RESERVED;
    this->head = realloc(this->head, (this->cap + 1) * this->soe);
  }
}

int32_t zvec_intl_grow(zvec_t* this) {
  int32_t more = this->cap >> 1;
  int32_t ncap;
  void* nhead;

  if (!more)
    more++;
  ncap = more + this->cap;
  nhead = realloc(this->head, (ncap + 1) * this->soe);
  if (nhead == NULL)
    return 0;

  this->head = nhead;
  this->rrem += more;
  this->cap = ncap;
  return more;
}
