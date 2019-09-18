#include <stdio.h>
#include "mpich/mpi.h"

int main(int argc, char * argv[]){
    MPI_Init(&argc, &argv);
    
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Status status;
    MPI_Request request;
    
    MPI_Isend(&rank, 1, MPI_INT, (rank+1)%size, rank, MPI_COMM_WORLD, &request);

    int recieved;
    MPI_Irecv(&recieved, 1, MPI_INT, (rank+size-1)%size, MPI_ANY_TAG, MPI_COMM_WORLD, &request);
    MPI_Wait(&request, &status);
    printf("[%d] recieved %d\n", rank, recieved);

    MPI_Finalize();
    return 0;
}