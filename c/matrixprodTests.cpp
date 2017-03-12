#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <papi.h>
#include <fstream>

#include "matrixopr.h"

using namespace std;

#define SEP '|'

int main (int argc, char *argv[])
{

	int size;
	int op;
	int n_threads;
	double processingTime;
	ifstream in("test.in");
	ofstream out("test.out");	

	int EventSet = PAPI_NULL;
	long long l1DCM;
	long long l2DCM;
  		
	printCPUInformation();
	papi_InitEvents(EventSet);


	out << "sep=" << SEP << endl;
	out << "Algo" << SEP << "Size" << SEP << "Time (s)" << SEP << "L1DCM" << SEP << "L2DCM" << endl;
	
	op=1;
	do {
		in >> op;
		if (op == 0)
			break;
   		in >> size;

		// Start counting
		papi_StartCount(EventSet);

		switch (op){
			case 1: 
				out << "Mult";
				processingTime = OnMult(size);
				break;
			case 2:
				out << "MultLine";
				processingTime = OnMultLine(size);    
				break;
			case 3:
				in >> n_threads;
				out << "MultParallel";
				processingTime = OnMultParallel(size, n_threads);    
				break;
			case 4:
				in >> n_threads;
				out << "MultLineParallel";				
				processingTime = OnMultLineParallel(size, n_threads); 
				break;
		}

  		papi_StopCount(EventSet, l1DCM, l2DCM);
		out << SEP << size << SEP << processingTime << SEP << l1DCM << SEP << l2DCM << endl;
		papi_ResetCount(EventSet);		

	}while (op != 0);

	papi_RemoveEvents(EventSet);
	in.close();
	out.close();
}
