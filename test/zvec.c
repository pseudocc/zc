#include "./ztest.h"
#include "include/zvec.h"

#define ZVEC_UTNAME "VECTOR"

static int zvec_nothing() {
  return ZTEST_SUCCESS;
}

static ztest_case cases[] = {
  { "NOTHING", &zvec_nothing }
};

ztest_unit zvec_tests = DECL_UT(cases, ZVEC_UTNAME);
