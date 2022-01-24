#include "./ztest.h"
#include "include/zvec.h"

#define ZVEC_UTNAME "VECTOR"

static int feels_good_man() {
  return ZTEST_SUCCESS;
}

static ztest_case cases[] = {
  { "BE HAPPY EVERYDAY", &feels_good_man }
};

ztest_unit zvec_tests = DECL_UT(cases, ZVEC_UTNAME);
