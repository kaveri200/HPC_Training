#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, nprocs;

    int matrix[4][4];
    int row[4];

    int local_max;
    int global_max;

    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
    if(rank == 0)
    {
        int temp[4][4] =
        {
            {1,8,3,4},
            {5,6,17,8},
            {9,10,11,12},
            {13,14,15,16}
        };

        for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            matrix[i][j] = temp[i][j];
    }
    MPI_Scatter(matrix, 4, MPI_INT,
                row, 4, MPI_INT,
                0, MPI_COMM_WORLD);
    local_max = row[0];
    for(int i=1;i<4;i++)
    {
        if(row[i] > local_max)
            local_max = row[i];
    }

    printf("Process %d local max = %d\n",
            rank, local_max);
    MPI_Reduce(&local_max, &global_max,
               1, MPI_INT, MPI_MAX,
               0, MPI_COMM_WORLD);
    if(rank == 0)
    {
        printf("\nGlobal Maximum = %d\n",
                global_max);
    }

    MPI_Finalize();

    return 0;
}