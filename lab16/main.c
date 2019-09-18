#include <stdio.h>
#include "mpich/mpi.h"

int main(int argc, char * argv[]){
    MPI_Init(&argc, &argv);
    
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0){    
        int size;
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        printf("%d Processes.\n", size);
    } else if (rank % 2 != 0){
        printf("I`m %d: FIRST\n", rank);
    } else if (rank % 2 == 0){
        printf("I`m %d: SECOND\n", rank);
    }

    MPI_Finalize();
    return 0;
}