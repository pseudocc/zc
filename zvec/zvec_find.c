#include <string.h>
#include "./zvec_intl.h"

zvec_it zvec_find(zvec_t* this, zvec_it it, const void* val) {
  zvec_it e;
  if (it < zvec_begin(this))
    return NULL;
  e = zvec_end(this);
  while (it < e && memcmp(it, val, this->soe))
    zvec_inc(&it);
  return it == e ? NULL : it;
}

zvec_it zvec_rfind(zvec_t* this, zvec_it it, const void* val) {
  zvec_it b;
  if (it >= zvec_end(this))
    return NULL;
  b = zvec_begin(this);
  rvec_dec(&b);
  while (it > b && memcmp(it, val, this->soe))
    zvec_dec(&it);
  return it == b ? NULL : it;
}
