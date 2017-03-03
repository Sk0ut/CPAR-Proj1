#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <papi.h>
#include <string.h>

using namespace std;

#define SYSTEMTIME clock_t
#define BLU   "\x1B[34m"
#define RESET "\x1B[0m"
#define OMP 1


void initMatrices(int m_ar, int m_br, double **pha, double **phb, double **phc) 
{
	int i, j;

	*pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
	*phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
	*phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

	for(i=0; i<m_ar; i++)
		for(j=0; j<m_ar; j++)
			(*pha)[i*m_ar + j] = (double)1.0;


	for(i=0; i<m_br; i++)
		for(j=0; j<m_br; j++)
			(*phb)[i*m_br + j] = (double)(i+1);
}

void freeMatrices(double **pha, double **phb, double **phc)
{
	free(*pha);
	free(*phb);
	free(*phc);
}

void printMatrixResult(int m_br, double **phc)
{
	int i, j; 
	
	cout << "Result matrix: " << endl;
	for(i=0; i<1; i++)
	{	for(j=0; j<min(10,m_br); j++)
			cout << (*phc)[j] << " ";
	}
	cout << endl;
}
 
void OnMult(int m_ar, int m_br) 
{	
	SYSTEMTIME Time1, Time2;
		
	double temp;
	char st[100];
	int i, j, k;

	double *pha, *phb, *phc;
	
	initMatrices(m_ar, m_br, &pha, &phb, &phc);
	
    	Time1 = clock();

	for(i=0; i<m_ar; i++)
	{	for( j=0; j<m_br; j++)
		{	temp = 0;
			for( k=0; k<m_ar; k++)
			{	
				temp += pha[i*m_ar+k] * phb[k*m_br+j];
			}
			phc[i*m_ar+j]=temp;
		}
	}

	Time2 = clock();
	
	sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1) / CLOCKS_PER_SEC);	
	cout << st;
	
	printMatrixResult(m_br, &phc);
	freeMatrices(&pha, &phb, &phc);
}


void OnMultLine(int m_ar, int m_br)
{
    	SYSTEMTIME Time1, Time2;
	
	char st[100];
	int i, j, k;

	double *pha, *phb, *phc;
	
    	initMatrices(m_ar, m_br, &pha, &phb, &phc);
	
    	Time1 = clock();

	for(i=0; i < m_ar; ++i)
		for(j = 0; j < m_br; ++j)
			phc[i*m_ar+j] = 0;

	for(i=0; i<m_ar; i++)
	{	
		for( j=0; j<m_ar; j++) 
		{
			for( k=0; k<m_br; k++)
			{	
				phc[i*m_ar+k] += pha[i*m_ar+k] * phb[j*m_br+k];
			}
		}
	}
	
    	Time2 = clock();

	sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1) / CLOCKS_PER_SEC);	
	cout << st;
	
	printMatrixResult(m_br, &phc);
	freeMatrices(&pha, &phb, &phc);
}

void OnMultLineParallel(int m_ar, int m_br, int nThreads)
{
    	double Time1, Time2;
	
	char st[100];
	int i, j, k;

	double *pha, *phb, *phc;
			
    	initMatrices(m_ar, m_br, &pha, &phb, &phc);
	
	//omp_set_num_threads(nThreads);

	Time1 = omp_get_wtime();

	memset(phc, 0, (m_ar * m_ar) * sizeof(double));

	#pragma omp parallel for num_threads(nThreads)
	for(i=0; i<m_ar; i++)
	{	
		for( j=0; j<m_ar; j++) 
		{
			for( k=0; k<m_br; k++)
			{	
				phc[i*m_ar+k] += pha[i*m_ar+k] * phb[j*m_br+k];
			}
		}
	}
	
	Time2 = omp_get_wtime();

	sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1));	
	cout << st;
	
	printMatrixResult(m_br, &phc);
	freeMatrices(&pha, &phb, &phc);	
}


float produtoInterno(float *v1, float *v2, int col)
{
	int i;
	float soma=0.0;	

	for(i=0; i<col; i++)
		soma += v1[i]*v2[i];
	
	return(soma);

}

void handle_error (int retval)
{
  printf("PAPI error %d: %s\n", retval, PAPI_strerror(retval));
  exit(1);
}

void init_papi() {
  int retval = PAPI_library_init(PAPI_VER_CURRENT);
  if (retval != PAPI_VER_CURRENT && retval < 0) {
    printf("PAPI library version mismatch!\n");
    exit(1);
  }
  if (retval < 0) handle_error(retval);

  std::cout << "PAPI Version Number: MAJOR: " << PAPI_VERSION_MAJOR(retval)
            << " MINOR: " << PAPI_VERSION_MINOR(retval)
            << " REVISION: " << PAPI_VERSION_REVISION(retval) << "\n";
}


int main (int argc, char *argv[])
{

	char c;
	int lin, col, nt=1;
	int op;
	
	int EventSet = PAPI_NULL;
  	long long values[2];
  	int ret;
	

	cout << "CPU(s) available(s): " BLU << omp_get_num_procs() << RESET << endl;
	cout << "Thread(s) available(s): " BLU << omp_get_max_threads() << RESET << endl;


	ret = PAPI_library_init( PAPI_VER_CURRENT );
	if ( ret != PAPI_VER_CURRENT )
		std::cout << "FAIL" << endl;


	ret = PAPI_create_eventset(&EventSet);
		if (ret != PAPI_OK) cout << "ERRO: create eventset" << endl;


	ret = PAPI_add_event(EventSet,PAPI_L1_DCM );
	if (ret != PAPI_OK) cout << "ERRO: PAPI_L1_DCM" << endl;


	ret = PAPI_add_event(EventSet,PAPI_L2_DCM);
	if (ret != PAPI_OK) cout << "ERRO: PAPI_L2_DCM" << endl;


	op=1;
	do {
		cout << endl << "1. Multiplication" << endl;
		cout << "2. Line Multiplication" << endl;
		cout << "3. Parallel Line Multiplication" << endl;
		cout << "Selection?: ";
		cin >>op;
		if (op == 0)
			break;
		printf("Dimensions: lins cols ? ");
   		cin >> lin >> col;



		// Start counting
		ret = PAPI_start(EventSet);
		if (ret != PAPI_OK) cout << "ERRO: Start PAPI" << endl;

		switch (op){
			case 1: 
				OnMult(lin, col);
				break;
			case 2:
				OnMultLine(lin, col);    
				break;
			case 3:
				OnMultLineParallel(lin, col, omp_get_max_threads());     //mudar
				break;
		}

  		ret = PAPI_stop(EventSet, values);
  		if (ret != PAPI_OK) cout << "ERRO: Stop PAPI" << endl;
  		printf("L1 DCM: %lld \n",values[0]);
  		printf("L2 DCM: %lld \n",values[1]);

		ret = PAPI_reset( EventSet );
		if ( ret != PAPI_OK )
			std::cout << "FAIL reset" << endl; 



	}while (op != 0);

		ret = PAPI_remove_event( EventSet, PAPI_L1_DCM );
		if ( ret != PAPI_OK )
			std::cout << "FAIL remove event" << endl; 

		ret = PAPI_remove_event( EventSet, PAPI_L2_DCM );
		if ( ret != PAPI_OK )
			std::cout << "FAIL remove event" << endl; 

		ret = PAPI_destroy_eventset( &EventSet );
		if ( ret != PAPI_OK )
			std::cout << "FAIL destroy" << endl;

}
