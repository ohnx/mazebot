#include "util.h"
#include <time.h>

double *_Double_new(double v) {
    double *d = calloc(sizeof(double), 1);
    *d = v;
    return d;
}

void *_Double_copier(void *a) {
    double *d = calloc(sizeof(double), 1);
    *d = *((double *)a);
    return d;
}

int main() {
    NeuralNet myNN = new NeuralNet_new(NULL);
    myNN.
    srand(time(NULL));
    return 0;
}