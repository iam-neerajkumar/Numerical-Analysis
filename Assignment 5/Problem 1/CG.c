#include <stdio.h>
#include <math.h>
#include <stdlib.h>  

#define N 50
#define MAX_ITER 10000

typedef struct 
{
    double residuals[MAX_ITER];
} ResidualData;

//Matrix vector multiplication
double Matrix_Vect_Multi(double A[N][N], double x[N], double result[N], int n, int *mul_count) 
{
    for (int i = 0; i < n; i++)
    {
        result[i] = 0.0;
        for (int j = 0; j < n; j++)
        {
            result[i] += A[i][j] * x[j];
            (*mul_count) += 1;
        }
    }
}

//Vector subtraction
double Vect_Subtraction(double a[N], double b[N], double result[N], int n) 
{
    for (int i = 0; i < n; i++) 
    {
        result[i] = a[i] - b[i];
    }
}

//Vector addition
double Vect_Add(double a[N], double b[N], double result[N], int n) 
{
    for (int i = 0; i < n; i++) 
    {
        result[i] = a[i] + b[i];
    }
}

//Vector scale
double Vect_Scale(double a[N], double alpha, double result[N], int n, int *mul_count) 
{
    for (int i = 0; i < n; i++) 
    {
        result[i] = alpha * a[i];
        (*mul_count) += 1;
    }
}

//Dot product
double Dot_Product(double a[N], double b[N], int n, int *mul_count) 
{
    double result = 0.0;
    for (int i = 0; i < n; i++) 
    {
        result += a[i] * b[i];
        (*mul_count) += 1;
    }
    return result;
}

//Function for Conjugate Gradient
double conjugate_Gradient(double A[N][N], double b[N], double x[N], int n, int Max_Iter, double Tol, FILE *file)
{
    double r[N], s[N], As[N], alpha, beta, rs_Old, rs_new;
    int k = 0, mul_count = 0, div_count = 0;
    ResidualData residual_data;

    for (int i = 0; i < n; i++) 
    {
        x[i] = 0.0;
    }

    Matrix_Vect_Multi(A, x, r, n, &mul_count);
    Vect_Subtraction(b, r, r, n);

    for (int i = 0; i < n; i++) 
    {
        s[i] = r[i];
    }

    rs_Old = Dot_Product(r, r, n, &mul_count);

    while (k < Max_Iter) 
    {
        Matrix_Vect_Multi(A, s, As, n, &mul_count);
        double dot_sAs = Dot_Product(s, As, n, &mul_count);
        if (dot_sAs == 0.0) break;

        alpha = rs_Old / dot_sAs;
        div_count += 1;

        double temp[N];
        Vect_Scale(s, alpha, temp, n, &mul_count);
        Vect_Add(x, temp, x, n);

        Vect_Scale(As, alpha, temp, n, &mul_count);
        Vect_Subtraction(r, temp, r, n);

        rs_new = Dot_Product(r, r, n, &mul_count);
        residual_data.residuals[k] = sqrt(rs_new);

        if (sqrt(rs_new) <= Tol) 
        {
            printf("Converged in %d iteration(s).\n", k + 1);
            fprintf(file, "Converged in %d iteration(s).\n", k + 1);
            break;
        } 
        
        beta = rs_new / rs_Old;
        div_count += 1;

        Vect_Scale(s, beta, s, n, &mul_count);
        Vect_Add(r, s, s, n);
        rs_Old = rs_new;
        k++;
    }

    if (k >= Max_Iter) 
    {
        printf("Not Converged within %d iterations.\n", Max_Iter);
        fprintf(file, "Not Converged within %d iterations.\n", Max_Iter);
        fclose(file);  
        exit(1);

    }

    printf("Multiplications: %d, Divisions: %d\n", mul_count, div_count);
    fprintf(file, "Multiplications: %d, Divisions: %d\n", mul_count, div_count);

    FILE *file1 = fopen("iterationVSresidual.txt", "w");
    if (file1 == NULL)
    {
        printf("Error opening file.\n");
        return 1; 
    }
    for (int i = 0; i <= k; i++) 
    {
        fprintf(file1, "%d\t\t %lf\n", i + 1, residual_data.residuals[i]);
    }

    fclose(file1);
}

int main() 
{
    FILE *file = fopen("output.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    int n;
    printf("Enter the size of the matrix: ");
    scanf("%d", &n);

    if (n > N) {
        printf("Error: Matrix size exceeds the limit of %d\n", N);
        return 1;
    }

    double A[N][N], b[N], x[N];

    printf("Enter the augmented matrix [A | b]:\n");
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            scanf("%lf", &A[i][j]);
        }
        scanf("%lf", &b[i]);
    }

    double eps;
    printf("Enter the tolerance value: ");
    scanf("%lf", &eps);
    fprintf(file, "Entered the tolerance value: %lf\n", eps);

    int Max_Iter = MAX_ITER;

    conjugate_Gradient(A, b, x, n, Max_Iter, eps, file);
    
    printf("\nFinal solution x:\n");
    fprintf(file, "\nFinal solution x:\n");
    for (int i = 0; i < n; i++) {
        printf("%f\n", x[i]);
        fprintf(file, "%f\n", x[i]);
    }

    fclose(file);
    return 0;
}
