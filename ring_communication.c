#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, nprocs;
    int send_data, recv_data;
    int next, prev;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    next = (rank + 1) % nprocs;
    prev = (rank - 1 + nprocs) % nprocs;
    send_data = rank;
    // Even ranks send first, odd ranks receive first
    if (rank % 2 == 0)
    {
        MPI_Send(&send_data, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
        MPI_Recv(&recv_data, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    else
    {
        MPI_Recv(&recv_data, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(&send_data, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
    }

    printf("Rank %d received %d\n", rank, recv_data);

    MPI_Finalize();

    return 0;
}