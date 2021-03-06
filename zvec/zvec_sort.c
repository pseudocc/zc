#include <stdio.h>
#include <string.h>
#include "./zvec_intl.h"

static inline int zvec_cmp(const void* l, const void* r,
    cmpf cmp, int rcmp) {
  return rcmp ? -cmp(l, r) : cmp(l, r);
}

static zvec_it zvec_partition(zvec_t this, zvec_it p, zvec_it r,
    cmpf cmp, int rcmp) {
  zvec_it i, j;
  r = zvec_dec(this, r);
  i = p;
  j = p;

  while (j < r) {
    if (zvec_cmp(j, r, cmp, rcmp) <= 0) {
      zvec_swap(this, i, j);
      i = zvec_inc(this, i);
    }
    j = zvec_inc(this, j);
  }

  zvec_swap(this, i, j);
  return i;
}

static void zvec_qsort(zvec_t this, zvec_it p, zvec_it r,
    cmpf cmp, int rcmp) {
  zvec_it q;
  if (p < r) {
    q = zvec_partition(this, p, r, cmp, rcmp);
    zvec_qsort(this, p, q, cmp, rcmp);
    zvec_qsort(this, zvec_inc(this, q), r, cmp, rcmp);
  }
}

void zvec_sort(zvec_t this, zvec_it begin, zvec_it end, cmpf cmp) {
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
  zvec_qsort(this, begin, end, cmp, tmp != NULL);
}

void zvec_swap(zvec_t this, zvec_it it1, zvec_it it2) {
  zvec_it e;
  if (it1 == it2)
    return;

  e = zvec_end(this);
  memcpy(e, it1, this->soe);
  memcpy(it1, it2, this->soe);
  memcpy(it2, e, this->soe);
}

void zvec_reverse(zvec_t this, zvec_it begin, zvec_it end) {
  zvec_it tmp;
  
  if (begin > end) {
    tmp = begin;
    begin = end;
    end = tmp;
  }
  
  while (begin < end) {
    end = zvec_dec(this, end);
    zvec_swap(this, begin, end);
    begin = zvec_inc(this, begin);
  }
}
