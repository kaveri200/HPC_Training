#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, nprocs;

    int matrix[4][4];
    int row[4];

    int local_sum = 0;
    int total_sum = 0;

    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
    if(rank == 0)
    {
        int temp[4][4] =
        {
            {1,2,3,4},
            {5,6,7,8},
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
    for(int i=0;i<4;i++)
        local_sum += row[i];

    printf("Process %d row sum = %d\n", rank, local_sum);
    MPI_Reduce(&local_sum, &total_sum,
               1, MPI_INT, MPI_SUM,
               0, MPI_COMM_WORLD);
    if(rank == 0)
    {
        printf("\nTotal matrix sum = %d\n", total_sum);
    }
    MPI_Finalize();
    return 0;
}