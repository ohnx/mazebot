#include "SigmoidNeuron.h"

SigmoidNeuron SigmoidNeuron_new(const List inweights, double bias) {
    SigmoidNeuron sn = calloc(sizeof(SigmoidNeuron_nonptr), 1);
    sn->inweights = List_dup(inweights);
    sn->bias = bias;
    return sn;
}

void *_SigmoidNeuron_copier(void *a) {
    SigmoidNeuron n = calloc(sizeof(SigmoidNeuron_nonptr), 1);
    n->inweights = List_dup(((SigmoidNeuron)a)->inweights);
    n->bias = ((SigmoidNeuron)a)->bias;
    return n;
}

double SigmoidNeuron_calc(const SigmoidNeuron sn, const double *indata, int indatalen) {
    double z, r; int i; ListElem curr;
    if (indatalen != List_length(sn->inweights)) {
        error("In values do not match number of weights");
    }
    z = -sn->bias;
    curr = List_startElem(sn->inweights);
    for (i = 0; i < indatalen; i++) {
        z += indata[i] * *((double *)ListElem_value(curr));
        curr = ListElem_next(curr);
    }
    r = 1/(1+pow(M_E, -3.1*z));
    return r;
}

/* mating sigmoid neuron has 0 relation to inputs */
SigmoidNeuron SigmoidNeuron_mate(const SigmoidNeuron a, const SigmoidNeuron b, double threshold) {
    int i; SigmoidNeuron n; ListElem currn, currb;
    if (threshold < 0) threshold = 0.51337;
    if (List_length(a->inweights) != List_length(b->inweights)) {
        error("Incompatible parents");
    }
    /* completely new copy of a */
    n = SigmoidNeuron_new(List_copy(a->inweights, &_Double_copier), a->bias);
    currn = List_startElem(n->inweights);
    currb = List_startElem(b->inweights);
    for (i = 0; i < List_length(a->inweights); i++) {
        if (randdouble() > threshold) {
            /* replace the old value */
            free(ListElem_value(currn));
            ListElem_value(currn) = _Double_new(*(double *)ListElem_value(currb));
        }
        currn = ListElem_next(currn);
        currb = ListElem_next(currb);
    }
    if (randdouble() > threshold) {
        n->bias = b->bias;
    }
    return n;
}

/* mutate does not rely on old values at all! can free() old neuron after calling */
SigmoidNeuron SigmoidNeuron_mutate(const SigmoidNeuron a, double threshold, double maxweight, double maxbias) {
    int i; SigmoidNeuron m; ListElem curra, currm;
    m = SigmoidNeuron_new(a->inweights, a->bias);
    curra = List_startElem(a->inweights);
    currm = List_startElem(m->inweights);
    for (i = 0; i < List_length(a->inweights); i++) {
        if (randdouble() > threshold) {
            ListElem_value(currm) = _Double_new(randWithMaxDouble(maxweight)); /* not evenly distributed, whoops TODO fix this */
        } else {
            ListElem_value(currm) = _Double_new(*(double *)ListElem_value(curra));
        }
        curra = ListElem_next(curra);
        currm = ListElem_next(currm);
    }
    if (randdouble() > threshold) {
        m->bias = randWithMaxDouble(maxbias);
    }
    return m;
}

void SigmoidNeuron_delete(SigmoidNeuron sn) {
    List_delete(sn->inweights, &free);
    free(sn);
}
