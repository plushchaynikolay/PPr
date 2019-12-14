#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpich/mpi.h"

#define CH_IN_ABC 26


// Чтение строки произвольного размера
char *readLine()
{
    int len = 32;
    char ch, *str = (char *)malloc(len * sizeof(char));
    int n = 0;
    while ((ch = getchar()) != '\n')
    {
        str[n] = ch;
        n++;
        if (n >= len - 1)
        {
            len = len + len;
            str = (char *)realloc(str, len * sizeof(char));
        }
    }
    str = (char *)realloc(str, (n + 1) * sizeof(char));
    return str;
}

// рассылка точка-точка
int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Status status;
    MPI_Request request;

    char *str;
    int strSize;

    if (rank == 0)
    {
        printf("Enter line\n");
        str = readLine();
        strSize = strlen(str);
        for (int i = 1; i < size; i++)
        {
            MPI_Isend(&strSize, 1, MPI_INT, i, i, MPI_COMM_WORLD, &request);
            MPI_Isend(str, strSize, MPI_CHAR, i, i, MPI_COMM_WORLD, &request);
        }
    }
    else
    {
        MPI_Recv(&strSize, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
        str = (char*)malloc(strSize * sizeof(char));
        MPI_Recv(str, strSize, MPI_CHAR, 0, rank, MPI_COMM_WORLD, &status);
    }


    int count;
    char ch, a = 'a';
    for (int i = rank; i < CH_IN_ABC; i = i + size)
    {
        ch = (char)((int)a + i);
        count = 0;
        for (int j = 0; j < strSize; j++) if (str[j]==ch) count++;
        if (count > 0) printf("%c = %d\n", ch, count);
    }

    MPI_Finalize();
    return 0;
}