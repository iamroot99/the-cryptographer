/*
 * Source: http://www.nd.edu/~dthain/courses/cse20211/fall2013/wavfile.c
 *
 * This work is made available under the Creative Commons Attribution license.
 * https://creativecommons.org/licenses/by/4.0/
 */

#include "wavfile.h"

#include <stdio.h>
#include <string.h>

typedef struct {
  char	riff_tag[4];
  int	riff_length;
  char	wave_tag[4];
  char	fmt_tag[4];
  int	fmt_length;
  short	audio_format;
  short	num_channels;
  int	sample_rate;
  int	byte_rate;
  short	block_align;
  short	bits_per_sample;
  char	data_tag[4];
  int	data_length;
} wavfile_header_t;

FILE * wavfile_open(const char *filename) {
  wavfile_header_t header;

  int samples_per_second = WAVFILE_SAMPLES_PER_SECOND;
  int bits_per_sample = 16;

  memcpy(header.riff_tag, "RIFF", 4);
  memcpy(header.wave_tag, "WAVE", 4);
  memcpy(header.fmt_tag, "fmt ", 4);
  memcpy(header.data_tag, "data", 4);
  //strncpy(header.riff_tag,"RIFF",4);
  //strncpy(header.wave_tag,"WAVE",4);
  //strncpy(header.fmt_tag,"fmt ",4);
  //strncpy(header.data_tag,"data",4);

  header.riff_length = 0;
  header.fmt_length = 16;
  header.audio_format = 1;
  header.num_channels = 1;
  header.sample_rate = samples_per_second;
  header.byte_rate = samples_per_second*(bits_per_sample / 8);
  header.block_align = bits_per_sample / 8;
  header.bits_per_sample = bits_per_sample;
  header.data_length = 0;

  FILE * file = fopen(filename,"wb+");
  if(!file) return 0;

  fwrite(&header,sizeof(header),1,file);

  fflush(file);

  return file;
}

void wavfile_write(FILE *file, short data[], int length) {
  fwrite(data,sizeof(short),length,file);
}

void wavfile_close(FILE *file) {
  int file_length = ftell(file);

  int data_length = file_length - sizeof(wavfile_header_t);
  fseek(file,sizeof(wavfile_header_t) - sizeof(int),SEEK_SET);
  fwrite(&data_length,sizeof(data_length),1,file);

  int riff_length = file_length - 8;
  fseek(file,4,SEEK_SET);
  fwrite(&riff_length,sizeof(riff_length),1,file);

  fclose(file);
}