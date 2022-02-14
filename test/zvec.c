#include "./ztest.h"
#include "include/zvec.h"

#define ZVEC_UTNAME "VECTOR"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wint-conversion"

static int feels_good_man() {
  zassert_eq(11, 11, "November", "%d");
  return ZTEST_SUCCESS;
}

static int init_empty() {
  const int capacity = 8;
  zvec_t vec;
  vec = zvec_new(sizeof(int));
  zvec_reserve(vec, capacity);
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
  zvec_t vec;
  zvec_it it;
  int actual, i;
  int* ip;

  vec = zvec_new(sizeof(int));
  zvec_push(vec, nums[3]);
  zvec_unshift(vec, nums[0]);
  it = zvec_begin(vec);
  zvec_inc(vec, &it);
  zvec_add(vec, it, nums[1]);
  zvec_inc(vec, &it);
  ip = zvec_emplace(vec, it);
  *ip = nums[2];

  it = zvec_begin(vec);
  for (i = 0; i < ARRAY_SIZE(nums); i++) {
    actual = zvec_get(it, int);
    zassert_eq(actual, nums[i], "vec[%d]", "%d", i);
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
  zvec_t vec = zvec_from(nums, ARRAY_SIZE(nums), sizeof(int));

  zvec_shift(vec, &actual);
  zassert_eq(actual, nums[0], "shift", "%d");

  zvec_pop(vec, &actual);
  zassert_eq(actual, nums[ARRAY_SIZE(nums) - 1], "last", "%d");

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

static int iterator_ops() {
  const int nums[] = { 4, 5, 9, 1, 0, 7 };
  zvec_t vec;
  zvec_it it;
  int actual, i;

  vec = zvec_from(nums, ARRAY_SIZE(nums), sizeof(int));
  it = zvec_at(vec, i = 2);
  actual = zvec_get(it, int);
  zassert_eq(actual, nums[i], "vec[%d]::get", "%d", i);

  zvec_mov(vec, &it, i);
  zvec_set(it, i, int);
  actual = zvec_get(it, int);
  zassert_eq(actual, i, "vec[%d]::set", "%d", i * 2);

  zvec_dec(vec, &it);
  zassert_eq(zvec_index(vec, it), i * 2 - 1,
    "iterator to index", "%d");

  zassert_eq(zvec_at(vec, -1), zvec_last(vec),
    "vec[-1] should be the last one", "%p");

  zvec_free(vec);
  return ZTEST_SUCCESS;
}

static int find_items() {
  const int nums[] = { 1, 3, 7, 4, 5, 9 };
  zvec_t vec;
  zvec_it it;
  int i;

  i = 2;
  vec = zvec_from(nums, ARRAY_SIZE(nums), sizeof(int));
  it = zvec_find(vec, zvec_begin(vec), nums[i]);
  zassert_eq(zvec_index(vec, it), i,
   "vec[%d] is %d", "%d", i, nums[i]);

  i = 1;
  it = zvec_find(vec, it, nums[i]);
  zassert(it == NULL, "not found should return NULL");

  it = zvec_rfind(vec, zvec_last(vec), nums[i]);
  zassert_eq(zvec_index(vec, it), i,
   "vec[%d] is %d", "%d", i, nums[i]);

  zvec_free(vec);
  return ZTEST_SUCCESS;
}

static int sort_items() {
  int nums[] = { 2, 4, 7, 1, 3, 4, 8, 0 };
  const int n = ARRAY_SIZE(nums);
  zvec_t v1;
  zvec_t v2;
  int actual, i;

  v1 = zvec_from(nums, n, sizeof(int));
  v2 = zvec_from(nums, n, sizeof(int));

  zvec_sort(v1, zvec_begin(v1), zvec_end(v1), zcmp_i32);
  zvec_sort(v2, zvec_end(v2), zvec_begin(v2), zcmp_i32);
  qsort(nums, n, sizeof(int), zcmp_i32);

  for (i = 0; i < n; i++) {
    actual = zvec_get(zvec_at(v1, i), int);
    zassert_eq(actual, nums[i], "sorted vec[%d]", "%d", i);

    actual = zvec_get(zvec_at(v2, i), int);
    zassert_eq(actual, nums[n - i - 1],
      "rsorted vec[%d]", "%d", i);
  }

  zassert(1, "success mark");
  zvec_reverse(v2, zvec_begin(v2), zvec_end(v2));
  for (i = 0; i < n; i++) {
    actual = zvec_get(zvec_at(v2, i), int);
    zassert_eq(actual, nums[i],
      "rrsoted vec[%d]", "%d", i);
  }

  zvec_free(v1);
  zvec_free(v2);
  return ZTEST_SUCCESS;
}

#pragma GCC diagnostic pop

static ztest_case cases[] = {
  { "BE HAPPY EVERYDAY", &feels_good_man },
  { "CREATE EMPTY VECTOR", &init_empty },
  { "PUSH & UNSHIFT", &insert_items },
  { "REMOVE ITEMS", &remove_items },
  { "VECTOR ITERATOR", &iterator_ops },
  { "FIND ITEMS", &find_items },
  { "SORT & REVERSE", &sort_items }
};

ztest_unit zvec_tests = DECL_UT(cases, ZVEC_UTNAME);
