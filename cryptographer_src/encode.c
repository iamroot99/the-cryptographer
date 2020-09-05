#include <time.h>

#include "encode.h"
#include "elGamal/elGamal.h"
#include "audio_crypto/audioEncoder.h"

#define FIRST_INT 2

void encode_data(char *plaintext, int n, char *outputFile, char *encInput) {
  srand(time(NULL));

  long long q = get_random_long(RANGE_BEGIN, RANGE_END);
  long long g = get_random_long(FIRST_INT, q);

  long long privKey = gen_key(q);
  long long privKeyP = 0;
  long long h = log_power(g, privKey, q);

  int *enMsg = encrypt(plaintext, n, q, h, g, &privKeyP);
  for (int i = 0; i < n; i++) {
    printf("%d ", enMsg[i]);
  }
  printf("\n");

  create_wav(enMsg, outputFile, n, encInput);

  printf("Your wav was generated successfully in %s\n", outputFile);
  printf("Your key for decryption is: \
         \n privKey = %lld \
         \n privKeyP = %lld \
         \n q        = %lld\n",
          privKey, privKeyP, q);
}
