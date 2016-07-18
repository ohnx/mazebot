#ifndef __STOUFFE_MATRIX_H_INC
#define __STOUFFE_MATRIX_H_INC
#include "util.h"

#define Matrix_getAt(m,x,y) *(m->d + y*(m->r) + x)

typedef struct _Matrix_nonptr {
    int r, c;
    int *d;
} Matrix_nonptr;

typedef Matrix_nonptr* Matrix;

#endif