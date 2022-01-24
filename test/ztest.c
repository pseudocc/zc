#include <stdio.h>
#include <sys/time.h>
#include "./ztest.h"

typedef long long ms_t;

ms_t diff_ms(struct timeval tv1, struct timeval tv2) {
  ms_t sec, usec;
  sec = tv2.tv_sec - tv1.tv_sec;
  usec = tv2.tv_usec - tv1.tv_usec;
  return sec * 1000 + usec / 1000;
}

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"

static void run_ut(ztest_unit unit) {
  int success = 0, ztest_state;
  struct timeval tv0, tv1, tv2;
  ztest_case zc;

  printf("Running tests for %s\n", unit.name);
  gettimeofday(&tv0, NULL);

  for (int i = 0; i < unit.n_cases; i++) {
    zc = unit.cases[i];
    gettimeofday(&tv1, NULL);

    switch (zc.entry()) {
    case ZTEST_SUCCESS:
      printf("\t" GREEN "SUCCESS" RESET);
      success++;
      break;
    case ZTEST_PARTIAL:
      printf("\t" YELLOW "PARTIAL" RESET);
      break;
    case ZTEST_FAILURE:
      printf("\t" RED "FAILURE" RESET);
      break;
    }

    gettimeofday(&tv2, NULL);
    printf(" - %s - %s", unit.name, zc.name);
    printf(" - [%lld ms]\n", diff_ms(tv1, tv2));
  }

  printf("\t%d/%d of the tests are passed.\n", success, unit.n_cases);
  printf("Total time elasped %lld ms.\n", diff_ms(tv0, tv2));
}

int main() {
  run_ut(zvec_tests);
  return 0; 
}
