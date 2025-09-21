#include <stdio.h>
#include <math.h>

#define N 4  
#define TOL 1e-6  
#define MAX_ITER 100  

// function f
void f(double X[N], double f_val[N]) 
{
    f_val[0] = X[0] + 10 * X[1];
    f_val[1] = sqrt(5) * (X[2] - X[3]);
    f_val[2] = (X[1] - X[2]) * (X[1] - X[2]);
    f_val[3] = sqrt(10) * (X[0] - X[3]) * (X[0] - X[3]);
}

// Jacobian matrix J
void J(double X[N], double J_matrix[N][N]) 
{
    J_matrix[0][0] = 1;     J_matrix[0][1] = 10;  J_matrix[0][2] = 0;       J_matrix[0][3] = 0;
    J_matrix[1][0] = 0;     J_matrix[1][1] = 0;   J_matrix[1][2] = sqrt(5); J_matrix[1][3] = -sqrt(5);
    J_matrix[2][0] = 0;     J_matrix[2][1] = 2 * (X[1] - X[2]);  J_matrix[2][2] = -2 * (X[1] - X[2]);  J_matrix[2][3] = 0;
    J_matrix[3][0] = 2 * sqrt(10) * (X[0] - X[3]);  J_matrix[3][1] = 0;  J_matrix[3][2] = 0;  J_matrix[3][3] = -2 * sqrt(10) * (X[0] - X[3]);
}

// Inverse of a matrix using Gauss-Jordan elimination
void inverse_matrix(double A[N][N], double invA[N][N]) 
{
    int i, j, k;
    double ratio, aug[N][2 * N];

    for (i = 0; i < N; i++) 
    {
        for (j = 0; j < N; j++) 
        {
            aug[i][j] = A[i][j];
        }
        for (j = N; j < 2 * N; j++) 
        {
            aug[i][j] = (i == j - N) ? 1.0 : 0.0;
        }
    }

// Gauss-Jordan elimination
    for (i = 0; i < N; i++) 
    {
        double diagElement = aug[i][i];
        if (fabs(diagElement) < 1e-10) 
        {
            printf("Jacobian Matrix is singular.\n");
        }
        for (j = 0; j < 2 * N; j++) 
        {
            aug[i][j] /= diagElement;
        }
        for (k = 0; k < N; k++) 
        {
            if (k != i) {
                ratio = aug[k][i];
                for (j = 0; j < 2 * N; j++) 
                {
                    aug[k][j] -= ratio * aug[i][j];
                }
            }
        }
    }

//Inverse
    for (i = 0; i < N; i++) 
    {
        for (j = 0; j < N; j++) 
        {
            invA[i][j] = aug[i][j + N];
        }
    }
}

// Multiply matrix and vector
void matVecMult(double A[N][N], double B[N], double result[N]) 
{
    for (int i = 0; i < N; i++) 
    {
        result[i] = 0;
        for (int j = 0; j < N; j++) 
        {
            result[i] += A[i][j] * B[j];
        }
    }
}

void Newton_Method(double X[N]) 
{
    double f_val[N], J_matrix[N][N], invJ_matrix[N][N], s[N];
    int iter = 0;

    FILE *file = fopen("output_2b.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n"); 
    }

    fprintf(file,"Name-Neeraj Kumar\nRoll No-244103315\n\n\n");

    printf("Initial guess:\n");
    fprintf(file, "Initial guess:\n");
    for (int i = 0; i < N; i++) 
    {
        printf("x[%d] = %lf\n", i + 1, X[i]);
        fprintf(file, "x[%d] = %lf\n", i + 1, X[i]);
    }

// Check if Jacobian is singular at the initial guess
    J(X, J_matrix);
    double determinant = J_matrix[0][0] * (J_matrix[1][1] * J_matrix[2][2] * J_matrix[3][3] - J_matrix[1][1] * J_matrix[2][3] * J_matrix[3][2]) - 
                        J_matrix[0][1] * (J_matrix[1][0] * J_matrix[2][2] * J_matrix[3][3] - J_matrix[1][2] * J_matrix[2][0] * J_matrix[3][3]) + 
                        J_matrix[0][2] * (J_matrix[1][0] * J_matrix[2][1] * J_matrix[3][3] - J_matrix[1][1] * J_matrix[2][0] * J_matrix[3][2]) - 
                        J_matrix[0][3] * (J_matrix[1][0] * J_matrix[2][1] * J_matrix[3][2] - J_matrix[1][2] * J_matrix[2][0] * J_matrix[3][1]);
    if (fabs(determinant) < 1e-10) 
    {
        printf("Jacobian Matrix is singular at the initial guess.\n");
        fprintf(file, "Jacobian Matrix is singular at the initial guess.\n");
        fclose(file);
        return ;
    }

// Output 
    printf("\nIterations\t\t\tx\t\t\t Function evaluation\n");
    printf("---------------------------------------------------------------------------------------\n");
    printf("\tx[1]\tx[2]\tx[3]\tx[4] \t\tf[1]\tf[2]\tf[3]\tf[4]\n\n");

    fprintf(file, "\nIterations\t\t\tx\t\t\t Function evaluation\n");
    fprintf(file, "---------------------------------------------------------------------------------\n");
    fprintf(file, "\tx[1]\tx[2]\tx[3]\tx[4]\t\tf[1]\tf[2]\tf[3]\tf[4]\n\n");

    while (iter < MAX_ITER) 
    {
        f(X, f_val);   
        J(X, J_matrix);   
        inverse_matrix(J_matrix, invJ_matrix); 

//s = -inv(J) * f
        for (int i = 0; i < N; i++) 
        {
            s[i] = 0;
            for (int j = 0; j < N; j++) 
            {
                s[i] += -invJ_matrix[i][j] * f_val[j];
            }
        }

//Check convergence
        double norm_s = 0;
        for (int i = 0; i < N; i++) 
        {
            norm_s += s[i] * s[i]; 
        }
        norm_s = sqrt(norm_s); 

        printf("%d\t", iter);
        fprintf(file,"%d\t", iter);
        for (int i = 0; i < N; i++) 
        {
            printf("%lf ", X[i]);
            fprintf(file,"%lf ", X[i]);
        }
        printf("\t%lf %lf %lf %lf\n", f_val[0], f_val[1], f_val[2], f_val[3]);
        fprintf(file,"\t%lf %lf %lf %lf\n", f_val[0], f_val[1], f_val[2], f_val[3]);

        if (norm_s < TOL) 
        {
            break;
        }

        for (int i = 0; i < N; i++) 
        {
            X[i] += s[i];
        }

        iter++;
    }

    printf("\nSolutions:\n");
    fprintf(file,"\nSolutions:\n");
    printf("------------------------\n");
    fprintf(file,"---------------------\n");

    for (int i = 0; i < N; i++) 
    {
        printf("x[%d] = %lf\n", i + 1, X[i]);
        fprintf(file,"x[%d] = %lf\n", i + 1, X[i]);
    }

    printf("Converged at %d iterations.\n",iter);
    fprintf(file,"Converged at %d iterations.\n",iter);


    fclose(file);
}

int main() {
    double X[N] = {1, 2, 1, 1};  

    Newton_Method(X);  
    
    return 0;
}
