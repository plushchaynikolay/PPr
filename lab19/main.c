#include <stdio.h>
#include "mpich/mpi.h"

int main(int argc, char * argv[]){
    MPI_Init(&argc, &argv);
    
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    if (rank == 0){ 
        MPI_Status status;
        int recieved;
        for (int i = 1; i<size; i++){
            MPI_Recv(&recieved, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            printf("recieved: %d\n", recieved);
        }
    } else {
        MPI_Send(&rank, 1, MPI_INT, 0, rank, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}