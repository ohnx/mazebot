#include "NeuralNet.h"

NodeConnection NodeConnection_new(int a, int b) {
    NodeConnection nc = calloc(sizeof(NodeConnection), 1);
    nc->a = a;
    nc->b = b;
    return nc;
}

void *_NodeConnection_copier(void *a) {
    NodeConnection n = calloc(sizeof(NodeConnection_nonptr), 1);
    n->a = ((NodeConnection)a)->a;
    n->b = ((NodeConnection)a)->b;
    return n;
}

NeuralNet NeuralNet_new(const List nodes) {
    NeuralNet nn = calloc(sizeof(NeuralNet_nonptr), 1);
    /* Copy the nodes as well */
    nn->nodes = List_copy(nodes, &_SigmoidNeuron_copier);
    nn->nodeconnections = List_new();
    return nn;
}

void NeuralNet_addNode(NeuralNet nn, const SigmoidNeuron node) {
    /* make a copy of node weights */
    List_add(nn->nodes, _SigmoidNeuron_copier(node));
}

void NeuralNet_addConnection(NeuralNet nn, int ia, int ib) {
    int max = List_length(nn->nodes);
    if (ia > max || ib > max) {
        error("Node ID provided is invalid");
    }
    List_add(nn->nodeconnections, NodeConnection_new(ia, ib));
}

double *NeuralNet_run(const NeuralNet nn, const double *input) {
    /* nodedata is an array of lists of doubles */
    ListArray nodedata; List outputs, nodedatatemp; ListElem curra, currn;
    NodeConnection nodeconnect;
    double *storedvalues, *deps, *results;
    int i, j, dontuse, didProcess, *calculatedvalues;
    nodedata = ListArray_new(List_length(nn->nodes));
    outputs = List_new();
    storedvalues = calloc(sizeof(double), List_length(nn->nodes));
    calculatedvalues = calloc(sizeof(int), List_length(nn->nodes));
    
    curra = List_startElem(nn->nodeconnections);
    /* stick everything in the format <element> relies on <elements> */
    for (i = 0; i < List_length(nn->nodeconnections); i++) {
        nodeconnect = ((NodeConnection)(ListElem_value(curra)));
        if (nodeconnect->b == 0) {
            List_add(outputs, &nodeconnect->a);
            goto cont1;
        }
        /* already preallocated */
        nodedatatemp = nodedata[nodeconnect->b];
        List_add(nodedatatemp, _Double_new(nodeconnect->a));
        /* mutated in place, so no need to replace like in matlab*/
        cont1:
        curra = ListElem_next(curra);
    }
    
    dontuse = 0;
    currn = List_startElem(nn->nodes);
    /* process the nodes with no other nodes needed */
    for (i = 0; i < List_length(nn->nodes); i++) {
        nodedatatemp = nodedata[i];
        curra = List_startElem(nodedatatemp);
        for (j = 0; j < List_length(nodedatatemp); j++) {
            if (*((double *)ListElem_value(curra)) > 0) {
                dontuse = 1;
                goto cont2;
            }
            curra = ListElem_next(curra);
        }
        if (dontuse) { dontuse = 0; continue; }
        /* this is all negative numbers */
        /* build the list of input values */
        curra = List_startElem(nodedatatemp);
        deps = calloc(sizeof(double), List_length(nodedatatemp));
        for (j = 0; j < List_length(nodedatatemp); j++) {
            deps[j] = input[(int)abs(*((double *)ListElem_value(curra)))];
            curra = ListElem_next(curra);
        }
        storedvalues[i] = SigmoidNeuron_calc((SigmoidNeuron)(currn->value), deps, List_length(nodedatatemp));
        calculatedvalues[i] = 1;
        cont2:
        currn = ListElem_next(currn);
    }
    
    didProcess = 1;
    /* process nodes that have stuff */
    while (didProcess) {
        didProcess = 0;
        currn = List_startElem(nn->nodes);
        for (i = 0; i < List_length(nn->nodes); i++) {
            /* check if value already calculated */
            if (calculatedvalues[i]) continue;
            
            /* check all dependencies satisfied */
            nodedatatemp = nodedata[i];
            curra = List_startElem(nodedatatemp);
            for (j = 0; j < List_length(nodedatatemp); j++) {
                /* if there is a value where it is positive AND the value has not been calculated, then skip this node*/
                if (*((double *)ListElem_value(curra)) > 0 && calculatedvalues[(int)*((double *)ListElem_value(curra))] == 0) {
                    goto cont3;
                }
                curra = ListElem_next(curra);
            }
            
            /* build the list of input values */
            curra = List_startElem(nodedatatemp);
            deps = calloc(sizeof(double), List_length(nodedatatemp));
            for (j = 0; j < List_length(nodedatatemp); j++) {
                deps[j] = input[abs(*((double *)ListElem_value(curra)))];
                curra = ListElem_next(curra);
            }
            storedvalues[i] = SigmoidNeuron_calc((SigmoidNeuron)(currn->value), deps, List_length(nodedatatemp));
            calculatedvalues[i] = 1;
            didProcess = 1;
            cont3:
            currn = ListElem_next(currn);
        }
    }
    
    /* save results */
    results = calloc(sizeof(double), List_length(outputs));
    curra = List_startElem(outputs);
    for (i = 0; i < List_length(outputs); i++) {
        results[i] = storedvalues[*((int *)ListElem_value(curra))];
        curra = ListElem_next(curra);
    }
    
    /* free memory */
    ListArray_delete(nodedata, NULL);
    List_delete(outputs, NULL);
    free(storedvalues);
    free(calculatedvalues);
    
    return results;
}

NeuralNet NeuralNet_mate(const NeuralNet a, const NeuralNet b, double threshold) {
    NeuralNet n; int i; ListElem curra, currb;
    if (threshold < 0) threshold = 0.51337;
    if (List_length(a->nodes) != List_length(b->nodes)) {
        error("Incompatible parents");
    }
    if (List_length(a->nodeconnections) != List_length(a->nodeconnections)) {
        error("Mating node connections is not supported.");
    }
    
    n = NeuralNet_new(List_new());
    n->nodeconnections = List_copy(a->nodeconnections, &_NodeConnection_copier);
    
    curra = List_startElem(a->nodes);
    currb = List_startElem(b->nodes);
    for (i = 0; i < List_length(a->nodes); i++) {
        List_add(n->nodes, SigmoidNeuron_mate(
            (SigmoidNeuron)(ListElem_value(curra)),
            (SigmoidNeuron)(ListElem_value(currb)),
            threshold
        ));
        curra = ListElem_next(curra);
        currb = ListElem_next(currb);
    }
    /* node connections are not changed */
    return n;
}

NeuralNet NeuralNet_mutate(const NeuralNet nn, double threshold, double maxweight, double maxbias) {
    NeuralNet nouveau; int i; ListElem curr;

    nouveau = NeuralNet_new(List_new());
    nouveau->nodeconnections = List_copy(nn->nodeconnections, &_NodeConnection_copier);

    curr = List_startElem(nn->nodes);
    for (i = 0; i < List_length(nn->nodes); i++) {
        List_add(nouveau->nodes, SigmoidNeuron_mutate(
            (SigmoidNeuron)(ListElem_value(curr)),
            threshold,
            maxweight,
            maxbias
        ));
        curr = ListElem_next(curr);
    }
    /* node connections not changed */
    return nouveau;
}

void NeuralNet_delete(NeuralNet nn) {
    
}