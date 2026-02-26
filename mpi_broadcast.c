#include<stdio.h>
#include <mpi.h>

int main(int argc , char **argv)
{
    int i,nprocs,arr[8],rank;
    MPI_Init(&argc , &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    if(rank==0){
        int arr1[8]={1,2,3,4,5,6,7,8};
        for(i=0;i<8;i++){
            arr[i]=arr1[i];
        }
        printf("Master Process %d initialized the array.\n",rank);
    }
    MPI_Bcast(arr,8,MPI_INT,0,MPI_COMM_WORLD);
    int sum=0;
    for(i=0;i<8;i++){
        sum+=arr[i];
    }
    printf("Process %d calculated sum=%d\n",rank,sum);
    MPI_Finalize();
    return 0;
}