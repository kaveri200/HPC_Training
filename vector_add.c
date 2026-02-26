#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[])
{
    int rank,nprocs,A[8],B[8],C[8],l_A[2],l_B[2],l_c[2];
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
    if (rank==0){
        int tempA[8]={1,2,3,4,5,6,7,8};
        int tempB[8]={8,7,6,5,4,3,2,1};
        for (int i=0;i<8;i++){
            A[i]=tempA[i];
            B[i]=tempB[i];
        }
    }
    MPI_Scatter(A,2,MPI_INT,l_A,2,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scatter(B,2,MPI_INT,l_B,2,MPI_INT,0,MPI_COMM_WORLD);
    for(int i=0;i<2;i++){
        l_c[i]=l_A[i]+l_B[i];
    }
    printf("Process %d local result:%d %d\n",rank,l_c[0],l_c[1]);
    MPI_Gather(l_c,2,MPI_INT,C,2,MPI_INT,0,MPI_COMM_WORLD);
    if(rank == 0)
    {
        printf("\nFinal Vector C:\n");

        for(int i=0;i<8;i++)
            printf("%d ", C[i]);
    }
    MPI_Finalize();
    return 0;
}


//if input=n
/*#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, nprocs, N;

    int *A=NULL, *B=NULL, *C=NULL;
    int *local_A, *local_B, *local_C;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    if(rank == 0)
    {
        printf("Enter vector size N: ");
        scanf("%d", &N);

        A = malloc(N*sizeof(int));
        B = malloc(N*sizeof(int));
        C = malloc(N*sizeof(int));

        printf("Enter vector A:\n");
        for(int i=0;i<N;i++)
            scanf("%d",&A[i]);

        printf("Enter vector B:\n");
        for(int i=0;i<N;i++)
            scanf("%d",&B[i]);
    }

    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int local_n = N / nprocs;
    local_A = malloc(local_n*sizeof(int));
    local_B = malloc(local_n*sizeof(int));
    local_C = malloc(local_n*sizeof(int));

    MPI_Scatter(A, local_n, MPI_INT, local_A, local_n, MPI_INT, 0, MPI_COMM>
    MPI_Scatter(B, local_n, MPI_INT, local_B, local_n, MPI_INT, 0, MPI_COMM>

    for(int i=0;i<local_n;i++)
        local_C[i] = local_A[i] + local_B[i];

    printf("Process %d result: ", rank);
    for(int i=0;i<local_n;i++)
        printf("%d ", local_C[i]);
    printf("\n");

    MPI_Gather(local_C, local_n, MPI_INT, C, local_n, MPI_INT, 0, MPI_COMM_>

    if(rank == 0)
    {
        printf("\nFinal Vector C:\n");
        for(int i=0;i<N;i++)
            printf("%d ", C[i]);
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}*/
