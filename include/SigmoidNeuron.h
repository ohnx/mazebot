#ifndef __SIGMOIDNEURON_H_INC
#define __SIGMOIDNEURON_H_INC
#include "util.h"
#include "List.h"

#define SigmoidNeuron_dup(x) 

typedef struct _SigmoidNeuron_nonptr {
    List inweights;
    double bias;
} SigmoidNeuron_nonptr;

typedef SigmoidNeuron_nonptr* SigmoidNeuron;

SigmoidNeuron SigmoidNeuron_new(const List inweights, double bias);
void *_SigmoidNeuron_copier(void *a);
double SigmoidNeuron_calc(const SigmoidNeuron sn, const double *indata, int indatalen);
SigmoidNeuron SigmoidNeuron_mate(const SigmoidNeuron a, const SigmoidNeuron b, double threshold);
SigmoidNeuron SigmoidNeuron_mutate(const SigmoidNeuron a, double threshold, double maxweight, double maxbias);
void SigmoidNeuron_delete(SigmoidNeuron sn);
#endif