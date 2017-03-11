#include "matrixopr.h"

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


void OnMult(int m_ar, int m_br) 
{	
	SYSTEMTIME Time1, Time2;
		
	double temp;
	int i, j, k;

	double *pha, *phb, *phc;
	
	initMatrices(m_ar, m_br, &pha, &phb, &phc);
	
    	Time1 = clock();

	for(i=0; i<m_ar; i++)
	{	
		for( j=0; j<m_br; j++)
		{	
			temp = 0;
			for( k=0; k<m_ar; k++)
			{	
				temp += pha[i*m_ar+k] * phb[k*m_br+j];
			}
			phc[i*m_ar+j]=temp;
		}
	}

	Time2 = clock();
	
	printProcessingTime((double)(Time2 - Time1) / CLOCKS_PER_SEC);	
	printMatrixResult(m_br, &phc);
	freeMatrices(&pha, &phb, &phc);
}


void OnMultLine(int m_ar, int m_br)
{
    	SYSTEMTIME Time1, Time2;
	
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
				phc[i*m_ar+k] += pha[i*m_ar+j] * phb[j*m_br+k];
			}
		}
	}
	
    	Time2 = clock();

	printProcessingTime((double)(Time2 - Time1) / CLOCKS_PER_SEC);	
	
	printMatrixResult(m_br, &phc);
	freeMatrices(&pha, &phb, &phc);
}

void OnMultParallel(int m_ar, int m_br, int nThreads) 
{	
	double Time1, Time2;
		
	double temp;
	int i, j, k;

	double *pha, *phb, *phc;
	
	initMatrices(m_ar, m_br, &pha, &phb, &phc);
	
    	Time1 = omp_get_wtime();

	for(i=0; i<m_ar; i++)
	{			
		for( j=0; j<m_br; j++)
		{	
			temp = 0;
			#pragma omp parallel for num_threads(nThreads) reduction(+:temp)
			for( k=0; k<m_ar; k++)
			{	
				temp += pha[i*m_ar+k] * phb[k*m_br+j];
			}
			phc[i*m_ar+j]=temp;
		}
	}

	Time2 = omp_get_wtime();
	
	printProcessingTime(Time2 - Time1);	
	printMatrixResult(m_br, &phc);
	freeMatrices(&pha, &phb, &phc);
}

void OnMultLineParallel(int m_ar, int m_br, int nThreads)
{
    	double Time1, Time2;
	
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
				phc[i*m_ar+k] += pha[i*m_ar+j] * phb[j*m_br+k];
			}
		}
	}
	
	Time2 = omp_get_wtime();

	printProcessingTime(Time2 - Time1);			
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
