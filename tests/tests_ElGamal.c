#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../../extension/elGamal/elGamal.h"

#define MAX_SIZE 10000
#define FIRST_PRIME 2

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: ./tests_ElGamal file.txt\n");
    return 0;
  }

  FILE *input = fopen(argv[1], "r");

  int n;
  char plaintext[MAX_SIZE];
  
  int totalTests = 0;
  int passedTests = 0;

  while (!feof(input)) {
    fgets(plaintext, sizeof(plaintext), input);
    n = strlen(plaintext);
    
    if (n > 0) {
      plaintext[--n] = '\0';
    }

    ll q = get_random_long(RANGE_BEGIN, RANGE_END);
    ll g = get_random_long(FIRST_PRIME, q);

    ll privKey = gen_key(q);
    ll privKeyP = 0;

    ll h = log_power(g, privKey, q);

    int *enMsg = encrypt(plaintext, n, q, h, g, &privKeyP);
    char *decMsg = decrypt(enMsg, n, privKeyP, privKey, q);

    if (strcmp(plaintext, decMsg) != 0) {
      printf("%s and %s do not match\n", plaintext, decMsg);
    } else {
      passedTests++;
    }

    memset(plaintext, '\0', sizeof(plaintext));
    totalTests++;
  }

  printf("%d / %d tests passed\n", passedTests, totalTests);
}
