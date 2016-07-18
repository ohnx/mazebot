#ifndef __NEURALNET_MANAGER_H_INC
#define __NEURALNET_MANAGER_H_INC
#include "util.h"
#include "NeuralNet.h"

typedef int(*NeuralNetManager_ratingFunc)(NeuralNet n, void *data);
typedef struct _NeuralNetManager_nonptr {
    List nets;
    NeuralNetManager_ratingFunc ratingFunc;
    double mutateThreshold;
    double breedThreshold;
    double maxWeight;
    double maxBias;
    NeuralNet bestNet;
} NeuralNetManager_nonptr;

typedef NeuralNetManager_nonptr* NeuralNetManager;
#endif