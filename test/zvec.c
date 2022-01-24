#include "./ztest.h"
#include "include/zvec.h"

#define ZVEC_UTNAME "VECTOR"

static int feels_good_man() {
  return ZTEST_SUCCESS;
}

static int init_empty() {
  const int capacity = 8;
  zvec_t* vec;
  vec = zvec_new(capacity, sizeof(int));
  zassert(vec != NULL, "vec != NULL");
  zassert(zvec_begin(vec) == zvec_end(vec), "begin == end");
  zassert(zvec_cap(vec) == capacity, "capacity == %d", capacity);
  zassert(zvec_size(vec) != 0, "size == 0");
  zvec_free(vec);
  return ZTEST_SUCCESS;
}

static ztest_case cases[] = {
  { "BE HAPPY EVERYDAY", &feels_good_man },
  { "CREATE EMPTY VECTOR", &init_empty }
};

ztest_unit zvec_tests = DECL_UT(cases, ZVEC_UTNAME);
