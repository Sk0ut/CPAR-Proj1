#ifndef UTILS_H
#define UTILS_H

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <papi.h>

#define SYSTEMTIME clock_t
#define BLU   "\x1B[34m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define RESET "\x1B[0m"

void printMatrixResult(int m_br, double **phc);

void printProcessingTime(double timeMs);

void printCPUInformation();

void init_papi();

void papi_InitEvents(int &EventSet);

void papi_StartCount(int &EventSet);

void papi_StopCount(int &EventSet); 

void papi_ResetCount(int &EventSet);

void papi_RemoveEvents(int &EventSet);

#endif
