#include <stdio.h>
#include "mpich/mpi.h"

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int dest, source;
    int         recieved [size - 1];
    MPI_Status  statuses [size - 1];
    MPI_Request requests [size - 1];

    for (int i = 1; i < size; i++)
    {
        dest = (rank + i) % size;
        MPI_Isend(&rank, 1, MPI_INT, dest, rank, MPI_COMM_WORLD, &requests[i - 1]);
    }

    for (int i = 1; i < size; i++)
    {
        source = (rank + i) % size;
        MPI_Irecv(&recieved[i - 1], 1, MPI_INT, source, MPI_ANY_TAG, MPI_COMM_WORLD, &requests[i - 1]);
    }

    MPI_Waitall(size - 1, requests, statuses);
    for (int i = 0; i < size - 1; i++){
        source = (&statuses[i]) -> MPI_SOURCE;
        printf("[%d] recieved `%d` from %d\n", rank, recieved[i], source);
    }

    MPI_Finalize();
    return 0;
}