#include "NeuralNetManager.h"

NeuralNetManager NeuralNetManager_new(NeuralNetManager_ratingFunc rF,
                                      double mutateThreshold,
                                      double breedThreshold,
                                      double maxWeight, double maxBias) {
    NeuralNetManager nnm = calloc(sizeof(NeuralNetManager_nonptr), 1);
    nnm->nets = List_new();
    nnm->ratingFunc = rF;
    nnm->bestNet = NULL;
    nnm->mutateThreshold = mutateThreshold;
    nnm->breedThreshold = breedThreshold;
    nnm->maxWeight = maxWeight;
    nnm->maxBias = maxBias;
}

