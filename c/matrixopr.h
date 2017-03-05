#ifndef MATRIXOPP_H
#define MATRIXOPP_H

#include <string.h>

#include "utils.h"

void OnMult(int m_ar, int m_br);

void OnMultLine(int m_ar, int m_br);

void OnMultParallel(int m_ar, int m_br, int nThreads);

void OnMultLineParallel(int m_ar, int m_br, int nThreads);

#endif
