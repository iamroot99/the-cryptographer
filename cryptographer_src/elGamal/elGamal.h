#include <stdio.h>
#include <stdlib.h>

#define RANGE_BEGIN 1 << 20
#define RANGE_END 1 << 23

long long get_random_long(long long begin, long long end);

long long gen_key(long long q);

long long log_power(long long a, long long b, long long mod);

int *encrypt(char *message, int n, long long q, long long h, long long g, long long *privKey);

char *decrypt(int *encMsg, int n, long long p, long long privKey, long long q);
