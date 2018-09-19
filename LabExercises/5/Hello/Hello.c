/* Include the MPI library definitons: */
#include <mpi.h>
#include <string.h>
#include <stdio.h>

int main (int argc, char *argv[])
{
  int i, id, np;
  char name[MPI_MAX_PROCESSOR_NAME];
  int namelen;

  /* Initialize the MPI library: */
  MPI_Init (&argc, &argv);

  /* Get the number of processors this job is using: */
  MPI_Comm_size (MPI_COMM_WORLD, &np);

  /* Get the rank of the processor this thread is running on.  (Each
     processor has a unique rank.) */
  MPI_Comm_rank (MPI_COMM_WORLD, &id);

  /* Get the name of this processor (usually the hostname).  We call
     memset to ensure the string is null-terminated.  Not all MPI
     implementations null-terminate the processor name since the MPI
     standard specifies that the name is *not* supposed to be
     returned null-terminated.  */
  memset(name,0,MPI_MAX_PROCESSOR_NAME);
  MPI_Get_processor_name (name, &namelen);
  memset(name+namelen,0,MPI_MAX_PROCESSOR_NAME-namelen);

  printf ("hello_parallel.c: Number of tasks=%d My rank=%d My name=\"%s\".\n",
          np, id, name);
  /* Tell the MPI library to release all resources it is using: */
  MPI_Finalize ();

  return 0;
}
