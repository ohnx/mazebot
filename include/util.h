#ifndef __STOUFFE_UTIL_H_INC
#define __STOUFFE_UTIL_H_INC
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define error(x) do {fprintf(stderr, x); exit(91337);} while(0)
#define randdouble() (double)rand()/(double)RAND_MAX
#define randWithMaxDouble(x) rand()%((int)x) + ((double)((int)(((double)rand()/(double)RAND_MAX)*1000) % ((int)(x*1000)-((int)x)*1000)))/1000.0
double *_Double_new(double v);
void *_Double_copier(void *a);
#define function
#endif