#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define MAXSIZE 100

int main(int argc, char **argv)
{
	int myid, numprocs;
	int data[MAXSIZE], i, x, low, high, myresult=0, result;
	char fn[255];
	FILE *fp;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	if(0 == myid) {
		/* open input file and intialize data */
		strcpy(fn, getenv("PWD"));
		strcat(fn, "/rand_data.txt");
		if( NULL == (fp = fopen(fn, "r")) ) {
			printf("Can't open the input file: %s\n\n", fn);
			exit(1);
		}
		for(i=0; i<MAXSIZE; i++) {
			fscanf(fp, "%d", &data[i]);
		}
	}

	/* broadcast data */
	MPI_Bcast(data, MAXSIZE, MPI_INT, 0, MPI_COMM_WORLD);
	
	/* add portion of data */
	x = MAXSIZE/numprocs;	/* must be an integer */
	low = myid * x;
	high = low + x;
	for(i=low; i<high; i++) {
		myresult += data[i];
	}
	printf("I got %d from %d\n", myresult, myid);

	/* compute global sum */
	MPI_Reduce(&myresult, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if(0 == myid) {
		printf("The sum is %d.\n", result);
	}

	MPI_Finalize();
}

	