#include <stdio.h>
#include "mpich/mpi.h"

int main(int argc, char * argv[]){
    MPI_Init(&argc, &argv);
    
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Status status;
    int recieved;

    if (rank == 0){ 
        MPI_Send(&rank, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&recieved, 1, MPI_INT, size-1, size-1, MPI_COMM_WORLD, &status);
        printf("[%d] recieved: %d\n", rank, recieved);
    } else {
        MPI_Recv(&recieved, 1, MPI_INT, (rank-1)%size, (rank-1)%size, MPI_COMM_WORLD, &status);
        printf("[%d] recieved: %d\n", rank, recieved);
        MPI_Send(&rank, 1, MPI_INT, (rank+1)%size, rank, MPI_COMM_WORLD);

    }

    MPI_Finalize();
    return 0;
}