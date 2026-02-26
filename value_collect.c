#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, nprocs,value, total = 0,recv_value, i;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    value = rank * rank;
    if (rank != 0)
    {
        // Workers send to master
        MPI_Send(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        printf("Process %d sent value %d\n", rank, value);
    }
    else{
        for (i = 1; i < nprocs; i++)
        {
            MPI_Recv(&recv_value, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total += recv_value;
        }

        printf("Total sum = %d\n", total);
    }
    MPI_Finalize();
    return 0;
}

//with map_reduce function
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, nprocs;
    int value, total;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    value = rank * rank;
    MPI_Reduce(&value, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        printf("Total sum using MPI_Reduce = %d\n", total);
    }
    MPI_Finalize();
    return 0;
}