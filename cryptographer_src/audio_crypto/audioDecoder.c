#include <stdlib.h>
#include <stdio.h>

#include "audioDecoder.h"

#define NO_DIGITS 10
#define HEADER_SIZE 25

int decodings[NO_DIGITS];

int get_decoding(int x) {
  for (int i = 0; i < NO_DIGITS; i++) {
    if (decodings[i] == x) {
      return i;
    }
  }

  return 0;
}

int *decode_audio(char *input, char *decInput, int *n) {  
  FILE *decIn = fopen(decInput, "r");
  if (!decIn) {
    printf("Unable to open decodings file\n");
    return NULL;
  }

  for (int i = 0; i < NO_DIGITS; i++) {
    fscanf(decIn, "%d\n", &decodings[i]);
  }
  fclose(decIn);

  FILE *fin = fopen(input, "rb");
  if (!fin) {
    printf("Unable to open input file\n");
  }

  int x;

  int size = 1;
  int index = 0;
  int *data = calloc(1, sizeof(long long));  

  // Read Header
  for (int i = 0; i < HEADER_SIZE; i++) {
    fread(&x, 2, 1, fin);
  } 

  int prev = -1;
  long long val = 0;

  while(!feof(fin)) {
    fread(&x, 2, 1, fin);

    if (x == 0) {
      if (prev == 0) {
        break;
      } else {
        data[index++] = val;
        
        if (index == size) {
          size *= 2;
          data = realloc(data, size * sizeof(long long));
        }

        val = 0;
      }
    } else {
      val = val * 10 + get_decoding(x);
    }

    prev = x;
  }

  size = index;
  data = realloc(data, size * sizeof(long long)); 
  *n = size;

  return data;
}
