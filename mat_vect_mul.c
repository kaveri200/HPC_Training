#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, nprocs;
    int matrix[4][4];
    int vector[4],row[4],local_result,result[4];
    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
    if(rank == 0)
    {
        int temp_matrix[4][4] =
        {
            {1,2,3,4},
            {5,6,7,8},
            {9,10,11,12},
            {13,14,15,16}
        };

        int temp_vector[4] = {1,1,1,1};

        for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            matrix[i][j] = temp_matrix[i][j];

        for(int i=0;i<4;i++)
            vector[i] = temp_vector[i];
    }
    MPI_Scatter(matrix, 4, MPI_INT,
                row, 4, MPI_INT,
                0, MPI_COMM_WORLD);
    MPI_Bcast(vector, 4, MPI_INT,
              0, MPI_COMM_WORLD);
    local_result = 0;
    for(int i=0;i<4;i++)
        local_result += row[i] * vector[i];
    printf("Process %d computed y[%d] = %d\n",
            rank, rank, local_result);
    MPI_Gather(&local_result, 1, MPI_INT,
               result, 1, MPI_INT,
               0, MPI_COMM_WORLD);
    if(rank == 0)
    {
        printf("\nFinal Result Vector:\n");

        for(int i=0;i<4;i++)
            printf("%d ", result[i]);
    }
    MPI_Finalize();
    return 0;
}