#ifndef __NEURALNET_H_INC
#define __NEURALNET_H_INC
#include "List.h"
#include "SigmoidNeuron.h"
#include "util.h"

typedef struct _NodeConnection_nonptr {
    int a, b;
} NodeConnection_nonptr;

typedef NodeConnection_nonptr* NodeConnection;

typedef struct _NeuralNet_nonptr {
    List nodes;
    List nodeconnections;
} NeuralNet_nonptr;

typedef NeuralNet_nonptr* NeuralNet;
#endif