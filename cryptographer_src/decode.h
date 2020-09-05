#ifndef DECODE_H
#define DECODE_H

#include <stdio.h>

// decode a wav file using decodings map and prints the text to stdout
void decode_data(long long privKey, long long privKeyP, long long q, char *wavFileName, char *decodings);

#endif
