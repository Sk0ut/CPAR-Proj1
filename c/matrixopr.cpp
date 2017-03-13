#include "matrixopr.h"

void initMatrices(int size, double **pha, double **phb, double **phc) 
{
	int i, j;

	*pha = (double *)malloc((size * size) * sizeof(double));
	*phb = (double *)malloc((size * size) * sizeof(double));
	*phc = (double *)malloc((size * size) * sizeof(double));

	for(i=0; i<size; i++)
		for(j=0; j<size; j++)
			(*pha)[i*size + j] = (double)1.0;


	for(i=0; i<size; i++)
		for(j=0; j<size; j++)
			(*phb)[i*size + j] = (double)(i+1);
}

void freeMatrices(double **pha, double **phb, double **phc)
{
	free(*pha);
	free(*phb);
	free(*phc);
}

void mult(int size, double *pha, double *phb, double *phc) {
	double temp;
	int i, j, k;
	
	for(i=0; i<size; i++)
	{	
		for( j=0; j<size; j++)
		{	
			temp = 0;
			for( k=0; k<size; k++)
			{	
				temp += pha[i*size+k] * phb[k*size+j];
			}
			phc[i*size+j]=temp;
		}
	}
}


double OnMult(int size) 
{	
	SYSTEMTIME Time1, Time2;

	double *pha, *phb, *phc;
	double processingTime;
	
	initMatrices(size, &pha, &phb, &phc);
	
    	Time1 = clock();

	mult(size, pha, phb, phc);

	Time2 = clock();
	
	processingTime = (double)(Time2 - Time1) / CLOCKS_PER_SEC;
	printProcessingTime(processingTime);	
	
	printMatrixResult(size, &phc);
	freeMatrices(&pha, &phb, &phc);

	return processingTime;
}

void multLine(int size, double *pha, double *phb, double *phc) {

	int i, j, k;	
	memset(phc, 0, (size * size) * sizeof(double));

	for(i=0; i<size; i++)
	{	
		for( j=0; j<size; j++) 
		{
			for( k=0; k<size; k++)
			{	
				phc[i*size+k] += pha[i*size+j] * phb[j*size+k];
			}
		}
	}

}

double OnMultLine(int size)
{
    	SYSTEMTIME Time1, Time2;


	double *pha, *phb, *phc;
	double processingTime;	

    	initMatrices(size, &pha, &phb, &phc);
	
    	Time1 = clock();

	multLine(size, pha, phb, phc);
	
    	Time2 = clock();

	processingTime = (double)(Time2 - Time1) / CLOCKS_PER_SEC;
	printProcessingTime(processingTime);	
	
	printMatrixResult(size, &phc);
	freeMatrices(&pha, &phb, &phc);

	return processingTime;
}

double OnMultParallel(int size, int nThreads) 
{	
	double Time1, Time2;
		
	double temp;
	int i, j, k;

	double *pha, *phb, *phc;
	
	initMatrices(size, &pha, &phb, &phc);

    	Time1 = omp_get_wtime();


	#pragma omp parallel for private(i,j,k) num_threads(nThreads) reduction(+:temp)
	for(i=0; i<size; i++)
	{			
		for( j=0; j<size; j++)
		{	
			temp = 0;
			for( k=0; k<size; k++)
			{	
				temp += pha[i*size+k] * phb[k*size+j];
			}
			phc[i*size+j]=temp;
		}
	}

	Time2 = omp_get_wtime();
	
	double processingTime = Time2 - Time1;

	printProcessingTime(processingTime);	
	printMatrixResult(size, &phc);
	freeMatrices(&pha, &phb, &phc);

	return processingTime;
}

double OnMultLineParallel(int size, int nThreads)
{
    	double Time1, Time2;
	
	int i, j, k;

	double *pha, *phb, *phc;
			
    	initMatrices(size, &pha, &phb, &phc);
	
	Time1 = omp_get_wtime();
	
	memset(phc, 0, (size * size) * sizeof(double));	

	#pragma omp parallel for private(i, j, k) num_threads(nThreads)
	for(i=0; i<size; i++)
	{	
		for( j=0; j<size; j++) 
		{
			for( k=0; k<size; k++)
			{	
				phc[i*size+k] += pha[i*size+j] * phb[j*size+k];
			}
		}
	}
	
	Time2 = omp_get_wtime();

	double processingTime = Time2 - Time1;

	printProcessingTime(processingTime);			
	printMatrixResult(size, &phc);
	freeMatrices(&pha, &phb, &phc);	
	
	return processingTime;
}

float produtoInterno(float *v1, float *v2, int col)
{
	int i;
	float soma=0.0;	

	for(i=0; i<col; i++)
		soma += v1[i]*v2[i];
	
	return(soma);

}
