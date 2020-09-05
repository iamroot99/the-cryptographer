#include <math.h>
#include <stdlib.h>

#include "../wav_utils/wavfile.h"
#include "obfuscator.h"

#define NO_DIGITS 10
#define NUM_SAMPLES (WAVFILE_SAMPLES_PER_SECOND * 4)
#define START_SIZE 4

#define FREQUENCY 440.0
#define VOLUME 32000

void read_encodings(char *input, double *encodings) {
  FILE *file = fopen(input, "r");
  if (!file) {
    printf("Error while opening encodings file\n");
    return;
  }

  for (int i = 0; i < NO_DIGITS; i++) {
    fscanf(file, "%lf", &encodings[i]);
  }

  fclose(file);
}

int *get_digits(int x) {
  int noDigits = log10(x) + 1;
  int *digits = calloc(noDigits, sizeof(int));

  for (int i = noDigits - 1; i >= 0; i--) {
    digits[i] = x % 10;
    x /= 10;
  } 

  return digits;
}

void create_wav(int *values, char *outputFile, int n, char *encInput) {
  double *encodings = calloc(NO_DIGITS, sizeof(double));
  read_encodings(encInput, encodings);

  FILE *audio = wavfile_open(outputFile);
  if (!audio) {
    printf("Error while opening wav file\n.");
  }

  int size = START_SIZE;
  int index = 0;  
  short *waveform = calloc(size, sizeof(short));

  for (int i = 0; i < START_SIZE - 1; i++) {
    waveform[index++] = VOLUME * sin(0);
  }

  for (int i = 0; i < n; i++) {
    int *digits = get_digits(values[i]);
    int length = log10(values[i]) + 1;

    for (int j = 0; j < length; j++) {
      waveform[index] = VOLUME * sin(FREQUENCY * encodings[digits[j]] * 2 * M_PI);
      index++;

      if (index == size) { // reached end of array
        size *= 2;
        waveform = realloc(waveform, size * sizeof(int));
      }
    }

    waveform[index++] = VOLUME * sin(0); // separate two encoded ints
    if (index == size) {
      size *= 2;
      waveform = realloc(waveform, size * sizeof(int));
    }

    free(digits);
  }

  for (int i = 0; i <= 1; i++) { // mark end of encoded data
    waveform[index++] = VOLUME * sin(0);
    if (index == size) {
      size *= 2;
      waveform = realloc(waveform, size * sizeof(int));
    }
  } 

  size = index;
  waveform = realloc(waveform, size * sizeof(int));
  wavfile_write(audio, waveform, size);

  // add more data to make valid audio file
  short obfuscateSeq[NUM_SAMPLES];
  obfuscate(obfuscateSeq, NUM_SAMPLES, VOLUME, FREQUENCY);
  wavfile_write(audio, obfuscateSeq, NUM_SAMPLES);

  wavfile_close(audio);
  printf ("Your wav file was created in %s.\n", outputFile);

  free(waveform);
  free(encodings);
}
