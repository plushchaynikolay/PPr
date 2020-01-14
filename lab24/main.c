#include <stdio.h>
#include "mpich/mpi.h"

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size, root = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Status status;
    MPI_Request request;

    int N;
    if (rank == root)
        scanf("%d", &N);

    MPI_Bcast(&N, 1, MPI_INT, root, MPI_COMM_WORLD);

    double x, result, part = 0;
    for (int i = rank; i < N; i += size)
    {
        x = (0.5 + i) / N;
        part += (4 / (1 + x * x)) / N;
    }

    MPI_Reduce(&part, &result, 1, MPI_DOUBLE, MPI_SUM, root, MPI_COMM_WORLD);

    if (rank == root) 
        printf("%.15f\n", result);

    MPI_Finalize();
    return 0;
}
