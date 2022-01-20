#include <string.h>
#include "./zvec_intl.h"

void zvec_intl_rar(zvec_t* this, int32_t unit) {
  int32_t cap, sweep, remain;
  zvec_it src, tgt;

  cap = zvec_cap(this);
  sweep = this->n_items / unit;
  remain = this->n_items % unit;
  src = zvec_begin(this);
  tgt = zvec_mov(this, src, -unit);
  while (sweep--) {
    memcpy(tgt, src, unit * this->n_bytes);
    tgt = src;
    src = zvec_mov(this, src, unit);
  }

  if (remain)
    memcpy(tgt, src, remain * this->n_bytes);

  this->lrem -= unit;
  this->rrem += unit;
}

