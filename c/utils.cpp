#include "utils.h"

using namespace std;


void printMatrixResult(int size, double **matrix)
{
	int i, j; 
	
	cout << "Result matrix: " << endl;
	for(i=0; i<1; i++)
	{	for(j=0; j<min(10,size); j++)
			cout << (*matrix)[j] << " ";
	}
	cout << endl;
}

void printProcessingTime(double timeMs) 
{
	char st[100];

	sprintf(st, "Time: " KGRN " %3.3f seconds\n" RESET, timeMs);	
	cout << st;
}

void printCPUInformation() 
{	
	cout << BLU "CPU(s) available(s): "  << omp_get_num_procs() << RESET << endl;
	cout << BLU "Thread(s) available(s): " << omp_get_max_threads() << RESET << endl;
}

void handle_error(int retval)
{
  cerr << "PAPI error " << retval << ": " << PAPI_strerror(retval) << endl;
  exit(1);
}


void init_papi() 
{
  int retval = PAPI_library_init(PAPI_VER_CURRENT);
  if (retval != PAPI_VER_CURRENT && retval < 0) {
    cerr << "PAPI library version mismatch!" << endl;
    exit(1);
  }
  if (retval < 0) handle_error(retval);

  cout << "PAPI Version Number: MAJOR: " << PAPI_VERSION_MAJOR(retval)
            << " MINOR: " << PAPI_VERSION_MINOR(retval)
            << " REVISION: " << PAPI_VERSION_REVISION(retval) << "\n";
}

void papi_InitEvents(int &EventSet) 
{
	int ret;	

	ret = PAPI_library_init( PAPI_VER_CURRENT );
	if ( ret != PAPI_VER_CURRENT )
		cerr << "FAIL" << endl;


	ret = PAPI_create_eventset(&EventSet);
	if (ret != PAPI_OK) cerr << "ERRO: create eventset" << endl;


	ret = PAPI_add_event(EventSet,PAPI_L1_DCM );
	if (ret != PAPI_OK) cerr << "ERRO: PAPI_L1_DCM" << endl;


	ret = PAPI_add_event(EventSet,PAPI_L2_DCM);
	if (ret != PAPI_OK) cerr << "ERRO: PAPI_L2_DCM" << endl;
}

void papi_StartCount(int &EventSet) 
{
	int ret;

	ret = PAPI_start(EventSet);
	if (ret != PAPI_OK) cerr << "ERRO: Start PAPI" << endl;
}

void papi_StopCount(int &EventSet, long long &l1DCM, long long &l2DCM)
{
	int ret;
	long long values[2];

	ret = PAPI_stop(EventSet, values);
	if (ret != PAPI_OK) cerr << "ERRO: Stop PAPI" << endl;
	l1DCM = values[0];
	l2DCM = values[1];
}

void papi_PrintCount(long long l1DCM, long long l2DCM) {
	printf("L1 DCM: " KYEL "%lld \n" RESET, l1DCM);
	printf("L2 DCM: " KYEL "%lld \n" RESET, l2DCM);
}

void papi_ResetCount(int &EventSet)
{
	int ret;

	ret = PAPI_reset(EventSet);
	if ( ret != PAPI_OK ) cerr << "FAIL reset" << endl; 
}

void papi_RemoveEvents(int &EventSet) 
{
	int ret;

	ret = PAPI_remove_event( EventSet, PAPI_L1_DCM );
	if ( ret != PAPI_OK )
		cerr << "FAIL remove event" << endl; 

	ret = PAPI_remove_event( EventSet, PAPI_L2_DCM );
	if ( ret != PAPI_OK )
		cerr << "FAIL remove event" << endl; 

	ret = PAPI_destroy_eventset( &EventSet );
	if ( ret != PAPI_OK )
		cerr << "FAIL destroy" << endl;
}
