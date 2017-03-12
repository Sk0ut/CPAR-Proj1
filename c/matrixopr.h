#ifndef MATRIXOPP_H
#define MATRIXOPP_H

#include <string.h>

#include "utils.h"

void OnMult(int size);

void OnMultLine(int size);

void OnMultParallel(int size, int nThreads);

void OnMultLineParallel(int size, int nThreads);

#endif
