#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpich/mpi.h"


int main(int argc, char * argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size, root = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int i;
    char * name;
    char a = 'a';

    for (i = 1; i < argc; i++)
    {
        if (i == 1){
            name = (char*)malloc(strlen(argv[i]));
            strcpy(name, argv[i]);
        }
        else 
        {
            name = (char*)realloc(name, strlen(name) + strlen(argv[i]));
            strcat(name, argv[i]);
        }
    }
    int name_size = (int)strlen(name);

    int result, part = 0;
    for (i = rank; i < name_size; i += size)
        part += (int)(name[i] - a);
    MPI_Reduce(&part, &result, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);

    if (rank == root) printf("sum = %d\n", result);

    MPI_Finalize();
    return 0;
}