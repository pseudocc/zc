#include <string.h>
#include <errno.h>
#include "./zvec_intl.h"

static const uint32_t MIN_RAR_UNIT = 4;

static inline
int32_t zvec_priv_rar_unit(zvec_t this) {
  int32_t unit, cap;

  cap = zvec_cap(this);
  if (this->lrem < cap >> (LREM_RATIO_ORDER - 1))
    return 0;

  unit = this->lrem - (cap >> LREM_RATIO_ORDER);
  return unit < MIN_RAR_UNIT ? 0 : unit;
}

int32_t zvec_fit(zvec_t this) {
  int32_t size = zvec_size(this);
  if (this->lrem)
    zvec_intl_rar(this, this->lrem);
  this->head = realloc(this->head, (size + 1) * this->soe);
  this->rrem = 0;
  return size; 
}

int32_t zvec_push(zvec_t this, const void* val) {
  int32_t unit, size;
  if (!this->rrem) {
    unit = zvec_priv_rar_unit(this);
    if (unit)
      zvec_intl_rar(this, unit);
    else if (!zvec_intl_grow(this))
      return 0;
  }
  size = zvec_size(this);
  memcpy(zvec_end(this), &val, this->soe);
  this->rrem--;
  return size + 1;
}

int32_t zvec_pop(zvec_t this, void* ref) {
  int32_t size = zvec_size(this);
  if (!size)
    return 0;
  memcpy(ref, zvec_last(this), this->soe);
  this->rrem++;
  return size - 1;
}

int32_t zvec_shift(zvec_t this, void* ref) {
  int32_t size = zvec_size(this);
  if (!size)
    return 0;
  memcpy(ref, zvec_begin(this), this->soe);
  this->lrem++;
  return size - 1;
}

int32_t zvec_unshift(zvec_t this, const void* val) {
  int32_t size;
  zvec_it b = zvec_begin(this);
  if (!this->lrem)
    return zvec_add(this, b, val);
  b = zvec_dec(this, b);
  size = zvec_size(this);
  memcpy(b, &val, this->soe);
  this->lrem--;
  return size + 1;
}

int32_t zvec_purge(zvec_t this, const void* val) {
  int32_t n_deleted, n_bytes;
  zvec_it c, i, j, e;

  e = zvec_end(this);
  c = i = zvec_find(this, zvec_begin(this), val);
  n_deleted = 0;

  while (i != e) {
    i = zvec_inc(this, i);
    while (i < e && !memcmp(i, &val, this->soe)) {
      i = zvec_inc(this, i);
      n_deleted++;
    }
    if (i == e)
      break;

    j = i;
    j = zvec_inc(this, j);
    while (j < e && memcmp(j, &val, this->soe))
      j = zvec_inc(this, j);
 
    n_bytes = j - i;
    memmove(c, i, n_bytes);

    c += n_bytes;
    i = j;
  }

  return n_deleted;
}

void zvec_rm(zvec_t this, zvec_it it) {
  zvec_it b, e;

  b = zvec_begin(this);
  e = zvec_end(this);

  if (it < b || it >= e)
    return;
  
  b = it;
  it = zvec_inc(this, it);
  while (it < e) {
    memcpy(b, it, this->soe);
    b = zvec_inc(this, b);
    it = zvec_inc(this, it);
  }
  
  this->rrem++;
}

int32_t zvec_add(zvec_t this, zvec_it it, const void* val) {
  // 0: out of memory
  // -1: invalid arguments
  if (zvec_emplace(this, it) == NULL)
    return errno == ENOMEM ? 0 : -1;

  memcpy(it, &val, this->soe);
  return zvec_size(this);
}

void* zvec_emplace(zvec_t this, zvec_it it) {
  zvec_it b, e;

  b = zvec_begin(this);
  e = zvec_end(this);

  if (it < b || it > e)
    return NULL;
  if (!this->rrem && !zvec_intl_grow(this))
    return NULL;
  
  if (it == b && this->lrem) {
    b = zvec_dec(this, b);
    this->lrem--;
    return b;
  }

  b = e;
  b = zvec_dec(this, b);
  while (it < e) {
    memcpy(e, b, this->soe);
    b = zvec_dec(this, b);
    e = zvec_dec(this, e);
  }
  this->rrem--;

  return it;
}
