/*
 * Source: http://www.nd.edu/~dthain/courses/cse20211/fall2013/wavfile.h
 *
 * This work is made available under the Creative Commons Attribution license.
 * https://creativecommons.org/licenses/by/4.0/
 */

#ifndef __WAVFILE_H__
#define __WAVFILE_H__

#include <stdio.h>
#include <inttypes.h>

#define WAVFILE_SAMPLES_PER_SECOND 44100

FILE * wavfile_open(const char *filename);
void wavfile_write(FILE *file, short data[], int length);
void wavfile_close(FILE * file);

#endif
