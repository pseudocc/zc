#include "./ztest.h"
#include "include/zvec.h"

#define ZVEC_UTNAME "VECTOR"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wint-conversion"

static zvec_t* zvec_from(const int* nums, int n) {
  zvec_t* vec = zvec_new(0, sizeof(int));
  for (int i = 0; i < n; i++)
    zvec_push(vec, nums[i]);
  return vec;
}

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
  zvec_push(vec, nums[2]);
  zvec_push(vec, nums[3]);
  zvec_unshift(vec, nums[0]);
  it = zvec_begin(vec);
  zvec_inc(vec, &it);
  zvec_add(vec, it, nums[1]);

  it = zvec_begin(vec);
  for (i = 0; i < ARRAY_SIZE(nums); i++) {
    z = zvec_get(it, int);
    zassert_eq(z, nums[i], "vec[%d]", "%d", i);
    zvec_inc(vec, &it);
  }
  
  zvec_free(vec);
  return ZTEST_SUCCESS;
}

static int remove_items() {
  const int nums[] = { 10, 2, 5, 6, 2, 2, 7, 2, 11 };
  const int purge_num = 2;
  int actual, i;
  zvec_it it;
  zvec_t* vec = zvec_from(nums, ARRAY_SIZE(nums));

  zvec_shift(vec, &actual);
  zassert_eq(nums[0], actual, "shift", "%d");

  zvec_pop(vec, &actual);
  zassert_eq(nums[ARRAY_SIZE(nums) - 1], actual, "last", "%d");

  zvec_purge(vec, purge_num);
  it = zvec_begin(vec);
  for (i = 1; i < ARRAY_SIZE(nums) - 1; i++) {
    if (nums[i] == purge_num)
      continue;
    actual = zvec_get(it, int);
    zassert_eq(nums[i], actual,
      "vec[%d]", "%d", zvec_index(vec, it));
    zvec_inc(vec, &it);
  }

  zvec_free(vec);
  return ZTEST_SUCCESS;
}

#pragma GCC diagnostic pop

static ztest_case cases[] = {
  { "BE HAPPY EVERYDAY", &feels_good_man },
  { "CREATE EMPTY VECTOR", &init_empty },
  { "PUSH & UNSHIFT", &insert_items }
};

ztest_unit zvec_tests = DECL_UT(cases, ZVEC_UTNAME);
