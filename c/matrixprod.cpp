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

	int size;
	int op;
	int n_threads;
	
	int EventSet = PAPI_NULL;
  		
	printCPUInformation();
	papi_InitEvents(EventSet);
	
	op=1;
	do {
		cout << endl << "1. Multiplication" << endl;
		cout << "2. Line Multiplication" << endl;
		cout << "3. Parallel Multiplication" << endl;
		cout << "4. Parallel Line Multiplication" << endl;
		cout << "Selection? ";
		cin >>op;
		if (op == 0)
			break;
		printf("Size? ");
   		cin >> size;

		// Start counting
		papi_StartCount(EventSet);

		switch (op){
			case 1: 
				OnMult(size);
				break;
			case 2:
				OnMultLine(size);    
				break;
			case 3:
				cout << "Num threads? ";
				cin >> n_threads;
				OnMultParallel(size, n_threads);    
				break;
			case 4:
				cout << "Num threads? ";
				cin >> n_threads;
				OnMultLineParallel(size, n_threads); 
				break;
		}

  		papi_StopCount(EventSet);
		papi_ResetCount(EventSet);		

	}while (op != 0);

	papi_RemoveEvents(EventSet);
}
