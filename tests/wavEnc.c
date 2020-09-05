/*
 * Source: http://www.nd.edu/~dthain/courses/cse20211/fall2013/example.c
 *
 * This work is made available under the Creative Commons Attribution license.
 * https://creativecommons.org/licenses/by/4.0/
 */

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <errno.h>

#include "../../extension/wav_utils/wavfile.h"

//#define NUM_SAMPLES (WAVFILE_SAMPLES_PER_SECOND * 2)
#define NUM_SAMPLES 12

int main() {
  short waveform[NUM_SAMPLES];
  double frequency = 440.0;
  int volume = 32000;
  int length = NUM_SAMPLES;

  int i;
  waveform[0] = waveform[1] = volume * sin(0);

  double t = 2000000000;
  for(i = 2; i < length; i++) {
    //double t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
    waveform[i] = volume * sin(frequency*t*2*M_PI);
    t += 200000000;
  }

  FILE * f = wavfile_open("sound.wav");
  if(!f) {
    printf("couldn't open sound.wav for writing: %s",strerror(errno));
    return 1;
  }

  wavfile_write(f,waveform,length);
  wavfile_close(f);

  return 0;
}
