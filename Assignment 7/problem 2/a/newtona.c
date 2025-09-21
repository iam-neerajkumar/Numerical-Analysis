#include <stdio.h>
#include <math.h>

#define N 3
#define TOL 1e-6
#define MAX_ITER 100

//function f(x)
void f(double x[N], double f[N]) 
{
    f[0] = 16 * pow(x[0], 4) + 16 * pow(x[1], 4) + pow(x[2], 4) - 16;
    f[1] = pow(x[0], 2) + pow(x[1], 2) + pow(x[2], 2) - 3;
    f[2] = pow(x[0], 3) - x[1];
}

//Jacobian Matrix
void J(double x[N], double J[N][N]) 
{
    J[0][0] = 64 * pow(x[0], 3);
    J[0][1] = 64 * pow(x[1], 3);
    J[0][2] = 4 * pow(x[2], 3);

    J[1][0] = 2 * x[0];
    J[1][1] = 2 * x[1];
    J[1][2] = 2 * x[2];

    J[2][0] = 3 * pow(x[0], 2);
    J[2][1] = -1;
    J[2][2] = 0;
}

//inverse matrix
void inverse_matrix(double J[N][N], double invJ[N][N]) 
{
    double det = J[0][0] * (J[1][1] * J[2][2] - J[1][2] * J[2][1]) -
                 J[0][1] * (J[1][0] * J[2][2] - J[1][2] * J[2][0]) +
                 J[0][2] * (J[1][0] * J[2][1] - J[1][1] * J[2][0]);

    if (fabs(det) < 1e-10) 
    {
        printf("Matrix is singular.\n");
        return;
    }

    invJ[0][0] = (J[1][1] * J[2][2] - J[1][2] * J[2][1]) / det;
    invJ[0][1] = (J[0][2] * J[2][1] - J[0][1] * J[2][2]) / det;
    invJ[0][2] = (J[0][1] * J[1][2] - J[0][2] * J[1][1]) / det;

    invJ[1][0] = (J[1][2] * J[2][0] - J[1][0] * J[2][2]) / det;
    invJ[1][1] = (J[0][0] * J[2][2] - J[0][2] * J[2][0]) / det;
    invJ[1][2] = (J[0][2] * J[1][0] - J[0][0] * J[1][2]) / det;

    invJ[2][0] = (J[1][0] * J[2][1] - J[1][1] * J[2][0]) / det;
    invJ[2][1] = (J[0][1] * J[2][0] - J[0][0] * J[2][1]) / det;
    invJ[2][2] = (J[0][0] * J[1][1] - J[0][1] * J[1][0]) / det;
}

int main() {
    FILE *file = fopen("output_2a.txt","w");
    if (file==NULL)
    {
        printf("Error to open the file.");
        return 1 ;
    }

    double x[N] = {1, 1, 1}; //initial guess
    double f_val[N], J_matrix[N][N], invJ_matrix[N][N], s[N];
    int iter = 0;

    fprintf(file,"Name-Neeraj Kumar\nRoll No-244103315\n\n\n\n");

//print initial guess
    printf("Initial guess:\n");
    fprintf(file,"Initial guess:\n");
    for (int i = 0; i < N; i++) 
    {
        printf("x[%d] = %f\n", i, x[i]);
        fprintf(file,"x[%d] = %f\n", i, x[i]);
    }

//print result
    printf("\nIterations\t\tx\t\t function evaluation\n");
    printf("------------------------------------------------------------------------\n");
    printf("\tx[1] \tx[2] \tx[3]\t\tf[1] \tf[2] \tf[3]\n\n");
    fprintf(file,"\nIterations\t\tx\t\t function evaluation\n");
    fprintf(file,"------------------------------------------------------------------------\n");
    fprintf(file,"\tx[1] \tx[2] \tx[3]\t\tf[1] \tf[2] \tf[3]\n\n");


    while (iter < MAX_ITER) 
    {
        f(x, f_val);
        J(x, J_matrix);
        inverse_matrix(J_matrix, invJ_matrix);

        double norm_f = 0;
        for (int i = 0; i < N; i++) 
        {
            norm_f += fabs(f_val[i]); //norm for convergence criteria.
        }

        printf("%d\t", iter);
        fprintf(file,"%d\t", iter);
        for (int i = 0; i < N; i++) 
        {
            printf("%lf ", x[i]);
            fprintf(file,"%lf ", x[i]);
        }
        printf("\t%lf %lf %lf\n", f_val[0], f_val[1], f_val[2]);
        fprintf(file,"\t%lf %lf %lf\n", f_val[0], f_val[1], f_val[2]);

        if (norm_f < TOL) 
        {
            break;
        }

        for (int i = 0; i < N; i++) 
        {
            s[i] = 0;
            for (int j = 0; j < N; j++) 
            {
                s[i] += -invJ_matrix[i][j] * f_val[j];
            }
        }

        for (int i = 0; i < N; i++) 
        {
            x[i] += s[i];
        }

        iter++;
    }

    printf("\nSolutions\n");
    printf("-------------\n");
    fprintf(file,"\nSolutions\n");
    fprintf(file,"-------------\n");
    for (int i = 0; i < N; i++) 
    {
        printf("x[%d] = %f\n", i+1, x[i]);
        fprintf(file,"x[%d] = %f\n", i+1, x[i]);
    }
    printf("converged at %d Iterations.\n", iter);
    fprintf(file,"converged at %d Iterations.\n", iter);

    fclose(file);

    return 0;
}


