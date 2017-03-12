#ifndef MATRIXOPP_H
#define MATRIXOPP_H

#include <string.h>

#include "utils.h"

double OnMult(int size);

double OnMultLine(int size);

double OnMultParallel(int size, int nThreads);

double OnMultLineParallel(int size, int nThreads);

#endif
