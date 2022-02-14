#include "./zvec_intl.h"

zvec_it zvec_begin(zvec_t this) {
  int64_t offset = this->soe * this->lrem;
  return this->head + offset;
}

zvec_it zvec_end(zvec_t this) {
  int64_t offset = this->soe * (this->cap - this->rrem);
  return this->head + offset;
}

zvec_it zvec_last(zvec_t this) {
  int64_t offset = this->soe * (this->cap - this->rrem - 1);
  return this->head + offset;
}

zvec_it zvec_at(zvec_t this, int32_t index) {
  int64_t offset;
  int32_t from = index >= 0 
    ? this->lrem
    : this->cap - this->rrem;
  offset = (from + index) * this->soe;
  return this->head + offset;
}

int32_t zvec_index(zvec_t this, zvec_it it) {
  if (it == NULL || it >= zvec_end(this))
    return -1;
  return (it - zvec_begin(this)) / this->soe;
}

void zvec_inc(zvec_t this, zvec_it* it) {
  *it += this->soe;
}

void zvec_dec(zvec_t this, zvec_it* it) {
  *it -= this->soe;
}

void zvec_mov(zvec_t this, zvec_it* it, int32_t pace) {
  int64_t move = pace * this->soe;
  *it += move;
}
