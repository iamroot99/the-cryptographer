#ifndef ENCODE_H
#define ENCODE_H

#include <stdlib.h>

// creates a wav file with the encoded text and prints keys to stdout
void encode_data(char *plaintext, int n, char *outputFile, char *encInput);

#endif
