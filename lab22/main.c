#include <stdio.h>
#include "mpich/mpi.h"

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Status status;
    MPI_Request request;

    for (int i = 1; i < size; i++)
    {
        MPI_Isend(&rank, 1, MPI_INT, (rank + i) % size, rank, MPI_COMM_WORLD, &request);
    }

    int recieved;
    int source;
    
    for (int i = 1; i < size; i++)
    {
        source = (rank + i) % size;
        MPI_Irecv(&recieved, 1, MPI_INT, source, MPI_ANY_TAG, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
        printf("[%d] recieved `%d` from %d\n", rank, recieved, source);
    }

    MPI_Finalize();
    return 0;
}