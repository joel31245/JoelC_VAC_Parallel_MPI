#include <stdio.h>
#include <stdbool.h>
#include "mpi.h"
#include <math.h>
#include <time.h>

int main(int argv, char **argc){

	int n=1000;


	bool A[n+1];
	int i,j,k, rank,size;
	double tstart, tfinish;

    // Variable sizes for the limits of the loops within the processes
//	int N[size+1];
//	N[0] = 0;
//	for( i=1; i<size+1; i++){
//        N[i] = N[i-1] + n/size;
//	}
//	N[0]+=2;
    for( i=0; i<n+1; i++ ){
        A[i] = true;
	}



	MPI_Init(&argv, &argc);
	MPI_Comm_rank( MPI_COMM_WORLD, &rank);
	MPI_Comm_size( MPI_COMM_WORLD, &size);


 	/*Let A be an array of Boolean values, indexed by integers 2 to n,
 	initially all set to true.*/
// 	for( k=0; k<size; k++){
//
//        if( rank == k){
//            for (i = N[k]; i<sqrt(N[k+1]); i++){
//                if (A[i] == true){
//                    for (j = pow(i,2); j<N[k+1]; j+=i ){
//                        A[j] = false;
//                    }
//                }
//
//                if(A[i] == true){
//                    printf("%d is a prime number.\n", i);
//                }
//            }
//        }// End of rank
//
//    }
    tstart = MPI_Wtime();

    for( i=rank*n/size; i<(rank+1)*n/size; i++){
        if( i==0 ){
            i+=2;
        }
        for(j=2; j<=i/2; j++){
            if( i%j == 0 )
                A[i] = false;
        }
        if(A[i]==true)
            printf("%d is a Prime Number (Rank: %d)\n", i,rank);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    tfinish = MPI_Wtime();
    printf("(Rank %d) took %lf seconds\n", rank,tfinish-tstart);

	MPI_Finalize();


	return 0;
}
