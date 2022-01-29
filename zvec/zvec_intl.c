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

