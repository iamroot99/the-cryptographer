#include <stdlib.h>

#include "decode.h"
#include "audio_crypto/audioDecoder.h"
#include "elGamal/elGamal.h"

void decode_data(long long privKey, long long privKeyP, long long q, char *wavFileName,
            char *decodings) {
  int n;
  int *encMsg = decode_audio(wavFileName, decodings, &n);

  char *decMsg = decrypt(encMsg, n, privKeyP, privKey, q);

  printf("Your decoded message is:\n%s", decMsg);
}
