#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpich/mpi.h"

#define CH_IN_ABC 26


// Чтение строки произвольного размера:
char *readLine()
{
    int sLength = 32;
    char ch, *str = (char *)malloc(sLength * sizeof(char));
    int nChar = 0;
    while ((ch = getchar()) != '\n')
    {
        str[nChar] = ch;
        nChar++;
        if (nChar >= sLength - 1)
        {
            sLength = sLength + sLength;
            str = (char *)realloc(str, sLength * sizeof(char));
        }
    }
    str = (char *)realloc(str, (nChar + 1) * sizeof(char));
    return str;
}

// рассылка MPI_Bcast
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
        MPI_Bcast(&strSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(str, strSize, MPI_CHAR, 0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Bcast(&strSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
        str = (char*)malloc(strSize * sizeof(char));
        MPI_Bcast(str, strSize, MPI_CHAR, 0, MPI_COMM_WORLD);
    }

    char a = 'a';
    char ch;
    int count;
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