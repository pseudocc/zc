#include <stdio.h>
#include "./zvec_intl.h"

static inline int zvec_cmp(const void* l, const void* r,
    cmpf cmp, int rcmp) {
  return rcmp ? -cmp(l, r) : cmp(l, r);
}

static void zvec_partition(zvec_t* this, zvec_it p, zvec_it r,
    cmpf cmp, int rcmp) {
  zvec_it i, j;
  zvec_dec(this, &r);
  i = p;
  j = p;

  while (j < r) {
    if (zvec_cmp(j, r, cmp, rcmp) <= 0) {
      zvec_swap(this, i, j);
      zvec_inc(this, &i);
    }
    zvec_inc(this, &j);
  }

  return i;
}

static void zvec_qsort(zvec_t* this, zvec_it p, zvec_it r,
    cmpf cmp, int rcmp) {
  zvec_it q;
  if (p < r) {
    q = zvec_partition(this, p, r, cmp, rcmp);
    zvec_qsort(this, p, q - this->soe, cmp, rcmp);
    zvec_qsort(this, q + this->soe, r);
  }
}

void zvec_sort(zvec_t* this, zvec_it begin, zvec_it end, cmpf cmp) {
  size_t count;
  zvec_it tmp = NULL;

  if (begin > end) {
    tmp = begin;
    begin = end;
    end = tmp;
  }

  if (begin < zvec_begin(this) || end > zvec_end(this)) {
    fprintf(stderr, "out of range");
    return;
  }

  cmp = cmp == NULL ? zcmp_obj : cmp;
  count = (end - begin) / this->soe;
  zvec_qsort(this, begin, end, cmp, tmp != NULL);
}

void zvec_swap(zvec_t* this, zvec_it it1, zvec_it it2) {
  zvec_it e;
  if (it1 == it2)
    return;

  e = zvec_end(this);
  memcpy(e, it1, this->soe);
  memcpy(it1, it2, this->soe);
  memcpy(it2, e, this->soe);
}

void zvec_reverse(zvec_t* this, zvec_it begin, zvec_it end) {
  zvec_it tmp;
  
  if (begin > end) {
    tmp = begin;
    begin = end;
    end = tmp;
  }
  
  zvec_dec(this, &end);
  while (begin < end) {
    zvec_swap(this, begin, end);
    zvec_dec(this &end);
    zvec_dec(this &begin);
  }
}
