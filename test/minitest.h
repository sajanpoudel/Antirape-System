#ifndef MINITEST_H
#define MINITEST_H
#include <stdio.h>
#include <stdlib.h>

// A tiny assertion helper so the tests need no external framework.
#define CHECK(cond) \
  do { \
    if (!(cond)) { \
      printf("FAILED %s:%d: %s\n", __FILE__, __LINE__, #cond); \
      exit(1); \
    } \
  } while (0)

#endif
