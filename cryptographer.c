#include <stdio.h>
#include <string.h>

#include "cryptographer_src/encode.h"
#include "cryptographer_src/decode.h"

#define MAX_SIZE 10000
#define FIRST_INT 2

#define NO_ARGS 4

void print_usage() {
  printf("Usage: \n \
          ./cryptographer enc outputFile encodings \
          ./cryptographer dec wavFile decodings");
}

int main(int argc, char **argv) {
  if (argc < 2) {
    print_usage();
    return EXIT_SUCCESS;
  }
  
  char *opCode = argv[1];
  if (argc != NO_ARGS) {
    print_usage();
    return EXIT_SUCCESS;
  }

  if (strcmp(opCode, "enc") == 0) {
    // Encode operation
    char *outputFile = argv[2];
    char *encInput = argv[3];

    int n;
    char plaintext[MAX_SIZE];

    printf("Enter message to encrypt:\n");
    fgets(plaintext, sizeof(plaintext), stdin);
    n = strlen(plaintext);

    encode_data(plaintext, n, outputFile, encInput);
  } else if (strcmp(opCode, "dec") == 0) {
    // Decode operation
    char *wavFile = argv[2];
    char *decodings = argv[3];

    long long privKey;
    long long privKeyP;
    long long q;

    printf("Enter privKey, privkeyP and q below (separated by spaces)\n");
    scanf("%lld %lld %lld", &privKey, &privKeyP, &q);

    decode_data(privKey, privKeyP, q, wavFile, decodings);
  } else {
    print_usage();
  }
 
  printf("Cryptographer terminated\n"); 
  return EXIT_SUCCESS;
}
