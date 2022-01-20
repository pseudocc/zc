#include <string.h>
#include "./zvec_intl.h"

static const uint32_t MIN_RAR_UNIT = 4;

static inline
int32_t zvec_priv_rar_unit(zvec_t* this) {
  int32_t unit, cap;

  cap = zvec_cap(this);
  if (this->lrem < cap >> (LREM_RATIO_ORDER - 1))
    return 0;

  unit = this->lrem - (cap >> LREM_RATIO_ORDER);
  return unit < MIN_RAR_UNIT ? 0 : unit;
}

int32_t zvec_fit(zvec_t* this) {
  if (this->lrem)
    zvec_intl_rar(this, this->lrem);
  this->head = realloc(this->head, this->n_items * this->n_bytes);
  this->rrem = 0;
  return this->n_items;
}

static inline
int32_t zvec_priv_grow(zvec_t* this) {
  int32_t cap, alloc;
  void* vp;

  cap = zvec_cap(this);
  alloc = cap * 2 < MIN_CAPACITY ? MIN_CAPACITY : cap;
  vp = realloc(this->head, alloc * this->n_bytes);
  if (vp == NULL)
    return 0;

  this->head = vp;
  this->rrem += alloc - cap;
  return 1;
}

int32_t zvec_push(zvec_t* this, const void* val) {
  int32_t unit;
  if (!this->rrem) {
    unit = zvec_priv_rar_unit(this);
    if (unit)
      zvec_intl_rar(this, unit);
    else if (!zvec_priv_grow(this))
      return 0;
  }
  memcpy(zvec_at(this, this->n_items++), &val, this->n_bytes);
  this->rrem--;
  return this->n_items;
}

int32_t zvec_pop(zvec_t* this, void* ref) {
  if (!this->n_items)
    return 0;
  memcpy(ref, zvec_at(this, --this->items), this->n_bytes);
  this->rrem++;
  return this->n_items;
}

int32_t zvec_shift(zvec_t* this, void* ref) {
  if (!this->n_items)
    return 0;
  memcpy(ref, zvec_begin(this), this->n_bytes);
  this->rrem++;
  return --this->n_items;
}

int32_t zvec_purge(zvec_t* this, const void* val) {
  int32_t n_deleted;
  zvec_it c, i, e;

  e = zvec_end(this);
  c = i = zvec_find(this, zvec_begin(this), val);
  n_deleted = 0;

  while (i != e) {
    zvec_inc(this, &i);
    while (i < e && !memcmp(i, val, this->n_bytes)) {
      zvec_inc(this, &i);
      n_deleted++;
    }
    if (i == e)
      break;
    j = i;
    zvec_inc(this, &j);
    while (j < e && memcmp(j, val, this->n_bytes))
      zvec_inc(this, &j);
    
    int32_t n_bytes, unit, sweeps, remain;
    n_bytes = j - i;
    unit = c - i;
    sweeps = n_bytes / unit;
    remain = n_bytes % unit;

    while (sweeps--) {
      memcpy(c, i, unit);
      c = i;
      i += unit;
    }

    if (remain) {
      memcpy(c, i, remain);
      c += remain;
    }

    i = j;
  }

  return n_deleted;
}

void zvec_rm(zvec_t* this, zvec_it it) {
  zvec_it b, e;

  b = zvec_begin(this);
  e = zvec_end(this);

  if (it < b || it >= e)
    return;
  
  b = it;
  zvec_inc(this, &it);
  while (it < e) {
    memcpy(b, it, this->n_bytes);
    zvec_inc(this, &b);
    zvec_inc(this, &it);
  }
  
  this->n_items--;
  this->rrem++;
}

int32_t zvec_add(zvec_t* this, zvec_it it, const void* val) {
  zvec_it b, e;

  b = zvec_begin(this);
  e = zvec_end(this);

  if (it < b || it >= e || !zvec_push(this, val))
    return 0;

  b = e;
  zvec_dec(this, &e);
  while (it < b) {
    memcpy(b, e, this->n_bytes);
    zvec_dec(this, &b);
    zvec_dec(this, &e);
  }
  memcpy(b, val, this->n_bytes);

  return this->n_items;
}