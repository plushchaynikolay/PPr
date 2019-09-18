#include <stdio.h>
#include "mpich/mpi.h"

int main(int argc, char * argv[]){
    MPI_Init(&argc, &argv);
    
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0){ 
        int sent = 45;
        MPI_Send(&sent, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1){
        MPI_Status status;
        int recieved;
        MPI_Recv(&recieved, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        printf("recieved %d\n", recieved);
    }

    MPI_Finalize();
    return 0;
}