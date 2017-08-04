#include <stdio.h>
#include <stdbool.h>
#include "mpi.h"
#include <math.h>

int main(){

	int n=0;

	while (n<=1){
		printf("Enter your n: ");
		scanf("%d", &n);
	}


	bool A[n];
	int i,j,k, rank,size;

    // Variable sizes for the limits of the loops within the processes
	int N[size+1];
	N[0] = 0;
	for( i=1; i<size; i++){
        N[i] = N[i-1] + n/size;
	}
	N[0]+=2;

	MPI_Init();
	MPI_Comm_rank( MPI_COMM_WORLD, &rank);
	MPI_Comm_size( MPI_COMM_WORLD, &size);

	for( i=0; i<n; i++ ){
        A[i] = true;
	}


 	/*Let A be an array of Boolean values, indexed by integers 2 to n,
 	initially all set to true.*/
 	for( k=0; k<size; k++){

        if( rank == k){
            for (i = N[k]; i<N[k+1]; i++){
                if (A[i] == true){
                        for (j = pow(i,2); j<N[k+1]; j+=i ){
                            A[j] = false;
                    }
                }

                if(A[i] == true){
                    printf("%d is a prime number.\n", i);
                }
            }
        }// End of rank

    }

	MPI_Finalize();

	return 0;
}
