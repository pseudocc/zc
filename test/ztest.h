#ifndef Z_UNIT_TEST_H
#define Z_UNIT_TEST_H

#include <stdio.h>
#include <stdlib.h>

enum {
  ZTEST_SUCCESS,
  ZTEST_PARTIAL,
  ZTEST_FAILURE
};

typedef int (*ztest_method)(void);
typedef struct {
  char name[64];
  ztest_method entry;
} ztest_case;

typedef struct {
  char name[64];
  ztest_case* cases;
  unsigned n_cases;
} ztest_unit;

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) sizeof(arr)/sizeof(arr[0])
#endif

#define DECL_UT(cases, name) { name, cases, ARRAY_SIZE(cases) }

#define ERR_BUF_SIZE 1024
#define ERR_INDENT "\t\t"
extern char zerrbuf[ERR_BUF_SIZE];
extern ztest_unit zvec_tests;

#endif
