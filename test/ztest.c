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

#define RUN_UT(name, objs) \
  run_ut(name, objs, n_##objs)

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"

static void run_ut(const char* name, ztest_object* objs, unsigned n) {
  int success = 0, ztest_state;
  struct timeval tv0, tv1, tv2;
  ztest_object zo;

  printf("Running tests for %s\n", name);
  gettimeofday(&tv0, NULL);

  for (int i = 0; i < n; i++) {
    zo = objs[i];
    gettimeofday(&tv1, NULL);

    switch (zo.entry()) {
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
    printf(" - %s - %s", name, zo.name);
    printf(" - [%lld ms]\n", diff_ms(tv1, tv2));
  }

  printf("\t%d/%d of the tests are passed.\n", success, n);
  printf("Total time elasped %lld ms.\n", diff_ms(tv0, tv2));
}

int main() {
  RUN_UT("VECTOR", zvec_tests);
  return 0; 
}
