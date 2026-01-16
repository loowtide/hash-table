#include "prime.h"
/*
 Returns:
  1:prime
  0:not a prime
  -1:undefined
*/
int is_prime(const int x) {
  if (x < 2)
    return -1;
  if (x < 4)
    return 1;
  if (!(x & 1))
    return 0;
  for (int i = 3; i * i <= x; i++) {
    if (x % i == 0)
      return 0;
  }
  return 1;
}
/* Find next prime */
int next_prime(int x) {
  while (is_prime(x) != 1) {
    x++;
  }
  return x;
}
