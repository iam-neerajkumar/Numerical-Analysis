#include<stdio.h>
#include<stdlib.h>

#define M 10
#define N 10

void rand_matrix(int A[M][N]){

    for ( int row = 0; row < M; row++){
    for (int col = 0; col < N; col++){

   A[row][col]=rand()%10 ; 
    }
   } 
}

void print_matrix(int A[M][N]){

    for ( int row = 0; row < M; row++){
    for (int col = 0; col < N; col++){

   printf("%d\t",A[row][col]) ; 
    }
   printf("\n");
    }
   
}

int cal_trace(int A[M][N]) {
    int trace = 0;
    for (int row = 0; row < M; row++) {
        trace += A[row][row];  
    }
    return trace;

}
int main()
{   
    int A[M][N];
    rand_matrix(A);
    printf("Matrix\n");
    print_matrix(A);
    int trace=cal_trace(A);
    printf("\nTrace of matrix=%d\n",trace);

    return 0;
}

