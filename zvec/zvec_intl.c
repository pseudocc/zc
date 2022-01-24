#include <string.h>
#include "./zvec_intl.h"

void zvec_intl_rar(zvec_t* this, int32_t unit) {
  int32_t size, sweep, remain;
  zvec_it src, tgt;

  size = zvec_size(this);
  sweep = size / unit;
  remain = size % unit;
  tgt = src = zvec_begin(this);
  zvec_mov(this, &tgt, -unit);
  while (sweep--) {
    memcpy(tgt, src, unit * this->soe);
    tgt = src;
    zvec_mov(this, &src, unit);
  }

  if (remain)
    memcpy(tgt, src, remain * this->soe);

  this->lrem -= unit;
  this->rrem += unit;
}

