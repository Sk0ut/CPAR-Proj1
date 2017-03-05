#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <papi.h>

#include "matrixopr.h"

using namespace std;
 

int main (int argc, char *argv[])
{

	int lin, col;
	int op;
	
	int EventSet = PAPI_NULL;
  		
	printCPUInformation();
	papi_InitEvents(EventSet);
	
	op=1;
	do {
		cout << endl << "1. Multiplication" << endl;
		cout << "2. Line Multiplication" << endl;
		cout << "3. Parallel Multiplication" << endl;
		cout << "4. Parallel Line Multiplication" << endl;
		cout << "Selection?: ";
		cin >>op;
		if (op == 0)
			break;
		printf("Dimensions: lins cols ? ");
   		cin >> lin >> col;

		// Start counting
		papi_StartCount(EventSet);

		switch (op){
			case 1: 
				OnMult(lin, col);
				break;
			case 2:
				OnMultLine(lin, col);    
				break;
			case 3:
				OnMultParallel(lin, col, omp_get_max_threads());    
				break;
			case 4:
				OnMultLineParallel(lin, col, omp_get_max_threads());     //mudar
				break;
		}

  		papi_StopCount(EventSet);
		papi_ResetCount(EventSet);		

	}while (op != 0);

	papi_RemoveEvents(EventSet);
}
