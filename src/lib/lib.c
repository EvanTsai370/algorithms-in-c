// Library of shared functions for algorithm implementations.

#include "lib.h"
#include <stdbool.h>
#include <string.h>

#define FNV_PRIME_32 16777619
#define FNV_BASIS_32 2166136261

// Comparison functions
bool less_int(void *v, void *w) { return compare_int(v, w) < 0; }

bool less_uint(void *v, void *w) { return compare_uint(v, w) < 0; }

bool less_float(void *v, void *w) { return compare_float(v, w) < 0; }

bool less_double(void *v, void *w) { return compare_double(v, w) < 0; }

bool less_char(void *v, void *w) { return compare_char(v, w) < 0; }

bool less_str(void *v, void *w) { return compare_str(v, w) < 0; }

// Return -1 if v < 1, +1 if v > w, and 0 if v == w
int compare_int(void *v, void *w) {
  int x = *(int *)v;
  int y = *(int *)w;

  if (x < y)
    return -1;
  if (x > y)
    return 1;
  return 0;
}

int compare_uint(void *v, void *w) {
  unsigned int x = *(unsigned int *)v;
  unsigned int y = *(unsigned int *)w;

  if (x < y)
    return -1;
  if (x > y)
    return 1;
  return 0;
}

int compare_float(void *v, void *w) {
  float x = *(float *)v;
  float y = *(float *)w;

  if (x < y)
    return -1;
  if (x > y)
    return 1;
  return 0;
}

int compare_double(void *v, void *w) {
  double x = *(double *)v;
  double y = *(double *)w;

  if (x < y)
    return -1;
  if (x > y)
    return 1;
  return 0;
}

int compare_char(void *v, void *w) {
  char x = *(char *)v;
  char y = *(char *)w;

  if (x < y)
    return -1;
  if (x > y)
    return 1;
  return 0;
}

int compare_str(void *v, void *w) {
  char *x = *(char **)v;
  char *y = *(char **)w;

  if (strcmp(x, y) < 0)
    return -1;
  if (strcmp(x, y) > 0)
    return 1;
  return 0;
}

// Computes a 32-bit FNV-1a hash value for a given input value and size.
// Reference:
// https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV-1a_hash
uint32_t fnv_hash_32(void *input, size_t size) {
  uint32_t hash = FNV_BASIS_32;
  uint8_t *bytes = (uint8_t *)input;

  for (size_t i = 0; i < size; i++) {
    uint8_t byte = bytes[i];
    hash ^= byte;
    hash *= FNV_PRIME_32;
  }

  return hash;
}
