#include <math.h>

#include "obfuscator.h"

#define WAVFILE_SAMPLES_PER_SECOND 44100

void obfuscate(short *data, int length, int volume, double frequency) {
  for (int i = 0; i < length; i++) {
    double t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
    data[i] = volume * sin(frequency * t * 2 * M_PI); 
  }  
}
