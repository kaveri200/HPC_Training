#include<stdio.h>
#include<mpi.h>
int main(int argc, char *argv[])
{
    int i,rank,nprocs,n=8,data[8],local_data[2],local_sum=0,global_sum=0;
    float average;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
    if (rank==0)
    {
        printf("Enter 8 elements:\n");
        for (i=0;i<n;i++){
            scanf("%d",&data[i]);
        }
    }
    MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scatter(data, 2, MPI_INT, local_data, 2, MPI_INT, 0, MPI_COMM_WORLD);
    for(int i = 0; i < 2; i++)
        local_sum += local_data[i];
    printf("Process %d local sum = %d\n", rank, local_sum);
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if(rank == 0)
    {
        average = (float)global_sum / N;
        printf("Global sum = %d\n", global_sum);
        printf("Average = %.2f\n", average);
    }
    MPI_Finalize();
    return 0;
}