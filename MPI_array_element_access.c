#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, processes;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &processes);
    int sizes[3] = {10000, 100000, 1000000};
    for(int s = 0; s < 3; s++)
    {
        int N = sizes[s];
        int *array = malloc(N * sizeof(int));
        for(int i = 0; i < N; i++)
            array[i] = i;
        int chunk = N / processes;
        int start = rank * chunk;
        int end = (rank == processes - 1) ? N - 1 : start + chunk - 1;

        MPI_Barrier(MPI_COMM_WORLD);
        double local_start = MPI_Wtime();
        for(int i = start; i <= end; i++)
        {
            int temp = array[i];
        }
        double local_time = MPI_Wtime() - local_start;
        if(rank == 0)
            printf("\nArray Size: %d\n", N);
        for(int i = 0; i < processes; i++)
        {
            MPI_Barrier(MPI_COMM_WORLD);
            if(rank == i)
            {
                printf("Process %d handled elements %d to %d ; Time Taken: %f seconds\n",
                       rank, start, end, local_time);
                fflush(stdout);
            }
        }
        MPI_Barrier(MPI_COMM_WORLD);
        double actual_time;
        MPI_Reduce(&local_time, &actual_time, 1,
                   MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        if(rank == 0)
        {
            printf("Actual Parallel Execution Time: %f seconds\n", actual_time);
            fflush(stdout);
        }
        free(array);
    }
    MPI_Finalize();
    return 0;
}
