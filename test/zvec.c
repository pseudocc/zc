#include "./ztest.h"
#include "include/zvec.h"

#define ZVEC_UTNAME "VECTOR"

static int feels_good_man() {
  zassert_eq(11, 11, "November", "%d");
  return ZTEST_SUCCESS;
}

static int init_empty() {
  const int capacity = 8;
  zvec_t* vec;
  vec = zvec_new(capacity, sizeof(int));
  zassert(vec != NULL, "vec should not be NULL");
  zassert(zvec_begin(vec) == zvec_end(vec),
    "begin and end should be the same");
  zassert_eq(zvec_cap(vec), capacity, "capacity", "%d");
  zassert_eq(zvec_size(vec), 0, "size", "%d");
  zvec_free(vec);
  return ZTEST_SUCCESS;
}

static int insert_items() {
  const int nums[] = { 19, 92, 11, 29 };
  zvec_t* vec;
  zvec_it it;
  int i, z;

  vec = zvec_new(0, sizeof(int));
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wint-conversion"
  zvec_push(vec, nums[2]);
  zvec_push(vec, nums[3]);
  zvec_unshift(vec, nums[0]);
  it = zvec_begin(vec);
  zvec_inc(vec, &it);
  zvec_add(vec, it, nums[1]);
#pragma GCC diagnostic pop
  it = zvec_begin(vec);

  for (i = 0; i < ARRAY_SIZE(nums); i++) {
    z = zvec_get(it, int);
    zassert_eq(z, nums[i], "vec[%d]", "%d", i);
    zvec_inc(vec, &it);
  }
  
  return ZTEST_SUCCESS;
}

static ztest_case cases[] = {
  { "BE HAPPY EVERYDAY", &feels_good_man },
  { "CREATE EMPTY VECTOR", &init_empty },
  { "PUSH & UNSHIFT", &insert_items }
};

ztest_unit zvec_tests = DECL_UT(cases, ZVEC_UTNAME);
