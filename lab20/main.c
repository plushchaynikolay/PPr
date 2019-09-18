#include <stdio.h>
#include "mpich/mpi.h"

int main(int argc, char * argv[]){
    MPI_Init(&argc, &argv);
    
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Status status;
    MPI_Request request;
    
    if (rank == 0){ 
        MPI_Isend(&rank, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
    } else if (rank == 1){
        MPI_Isend(&rank, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &request);
    }

    int recieved;
    MPI_Irecv(&recieved, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &request);
    MPI_Wait(&request, &status);
    printf("[%d] recieved %d\n", rank, recieved);

    MPI_Finalize();
    return 0;
}