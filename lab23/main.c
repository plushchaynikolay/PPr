#include <stdio.h>
#include "mpich/mpi.h"
#include <stdlib.h>

#define CH_IN_ABC 26
#define READLINE_BUFFER 32


// Чтение строки произвольного размера:
// invite - текст приглашения ко вводу
// strSize - ссылка в которую передается размер прочитанной строки
// return str - считанный массив символов размера strSize
char *readLine(const char *invite, int *strSize)
{
    int sLength = READLINE_BUFFER;
    char ch, *str = (char *)malloc(sLength * sizeof(char));
    int nChar = 0;
    printf("%s:\n", invite);
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
    *strSize = nChar;
    str = (char *)realloc(str, (nChar + 1) * sizeof(char));
    return str;
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Status status;
    MPI_Request request;

    char *str;
    int strSize;
    int results[CH_IN_ABC];

    // // рассылка точка-точка
    // if (rank == 0)
    // {
    //     str = readLine("Enter line", &strSize);
    //     for (int i = 1; i < size; i++)
    //     {
    //         MPI_Isend(&strSize, 1, MPI_INT, i, i, MPI_COMM_WORLD, &request);
    //         MPI_Isend(str, strSize, MPI_CHAR, i, i, MPI_COMM_WORLD, &request);
    //     }
    // }
    // else
    // {
    //     MPI_Recv(&strSize, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
    //     str = (char*)malloc(strSize * sizeof(char));
    //     MPI_Recv(str, strSize, MPI_CHAR, 0, rank, MPI_COMM_WORLD, &status);
    // }

    // рассылка MPI_Bcast
    if (rank == 0)
    {
        str = readLine("Enter line", &strSize);
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