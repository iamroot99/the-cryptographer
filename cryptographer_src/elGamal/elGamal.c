#include <time.h>
#include <stdlib.h>

#include "elGamal.h"

long long gcd(long long x, long long y) {
  if (!y) {
    return x;
  }

  return gcd(y, x % y);
}

long long get_random_long(long long begin, long long end) {
  return (rand() % (end - begin + 1) + begin);
}

long long gen_key(long long q) {
  long long key = get_random_long(RANGE_BEGIN, q);

  while (gcd(q, key) != 1) {
    key = get_random_long(RANGE_BEGIN, q);
  }

  return key;
}

long long log_power(long long a, long long b, long long mod) {
  long long res = 1;
  long long v = a;

  while (b > 0) {
    if (!(b & 1)) {
      res = (res * v) % mod;
    }

    v = (v * v) % mod;
    b /= 2;
  }

  return (res % mod);
}

int *encrypt(char *message, int n, long long q, long long h, long long g, long long *pubKey) {
  int *encMsg = calloc(n, sizeof(int));
  long long privKey = gen_key(q); 

  long long encFunc = log_power(h, privKey, q);
  *pubKey = log_power(g, privKey, q);

  for (int i = 0; i < n; i++) {
    encMsg[i] = encFunc * message[i];
  }

  return encMsg;
}

char *decrypt(int *encMsg, int n, long long p, long long privKey, long long q) {
  char *decMsg = calloc(n, sizeof(char));

  long long h = log_power(p, privKey, q);
  for (int i = 0; i < n; i++) {
    decMsg[i] = (char) (encMsg[i] / h);
  } 

  return decMsg;
}

