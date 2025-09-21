#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-6

void M_V_Multiplication(int n, double A[n][n], double x[n], double result[n]) 
{
    for (int i = 0; i < n; i++) 
    {
        result[i] = 0;
        for (int j = 0; j < n; j++) 
        {
            result[i] += A[i][j] * x[j];
        }
    }
}

double normalize(int n, double x[n]) 
{
    double norm_inf = 0;
    for (int i = 0; i < n; i++) 
    {
        if (fabs(x[i]) > norm_inf)
        {
            norm_inf = fabs(x[i]);
        }
    }
    if (norm_inf == 0)
    {
         return 0;
    }
    for (int i = 0; i < n; i++) 
    {
        x[i] /= norm_inf;
    }
    return norm_inf;
}


void N_P_I_Method(int n, double A[n][n], double eigenvector[n], double *eigenvalue, double x[n], FILE *file1)
{
    double Ax[n];
    double lambda_old = 0;
    *eigenvalue = 0;

    printf("\nNormalized Power Iteration Method\n");
    printf("Iteration\tEigen Value\tEigen Vector\n");
    printf(".......................................................................\n");
    fprintf(file1, "\nNormalized Power Iteration Method\n");
    fprintf(file1, "Iteration\tEigen Value\tEigen Vector\n");
    fprintf(file1, "................................................................\n");

    int iter = 0;

    while (1) 
    {
        M_V_Multiplication(n, A, x, Ax);
        *eigenvalue = normalize(n, Ax);

        printf("%d\t\t%lf\t", iter+1, *eigenvalue);
        fprintf(file1, "%d\t\t%lf\t", iter+1, *eigenvalue);
        for (int i = 0; i < n; i++)
        {
            printf("%lf ", Ax[i]);
            fprintf(file1, "%lf ", Ax[i]);
        }
        printf("\n");
        fprintf(file1, "\n");

        double diff = fabs(*eigenvalue - lambda_old);
        if (diff < EPSILON)
        {
             break;
        }

        for (int i = 0; i < n; i++)
        {
            x[i] = Ax[i];
        }
        lambda_old = *eigenvalue;
        iter++;
    }
    for (int i = 0; i < n; i++)
    {
        eigenvector[i] = x[i];
    }
}

void gaussian_elimination(int n, double A[n][n], double b[n], double x[n]) 
{
    double tempA[n][n], tempB[n];
    for (int i = 0; i < n; i++)
     {
        for (int j = 0; j < n; j++) 
        {
            tempA[i][j] = A[i][j];
        }
        tempB[i] = b[i];
    }

    for (int i = 0; i < n; i++) 
    {
        if (fabs(tempA[i][i]) < EPSILON) 
        {
            printf("Matrix is singular or nearly singular.\n");
            exit(1);
        }
        for (int j = i + 1; j < n; j++) 
        {
            double factor = tempA[j][i] / tempA[i][i];
            for (int k = 0; k < n; k++)
            {
                tempA[j][k] -= factor * tempA[i][k];
            }
            tempB[j] -= factor * tempB[i];
        }
    }

    for (int i = n - 1; i >= 0; i--) 
    {
        x[i] = tempB[i];
        for (int j = i + 1; j < n; j++) 
        {
            x[i] -= tempA[i][j] * x[j];
        }
        x[i] /= tempA[i][i];
    }
}


void Inverse_Iteration_Method(int n, double A[n][n], double eigenvector[n], double *eigenvalue, double x[n], FILE *file1) 
{
    double y[n], lambda_old = 0;
    *eigenvalue = 0;

    printf("\nInverse Iteration Method\n");
    printf("Iteration\tEigen Value\tEigen Vector\n");
    printf("......................................................................................................\n");
    fprintf(file1, "\nInverse Iteration Method\n");
    fprintf(file1, "Iteration\tEigen Value\tEigen Vector\n");
    fprintf(file1, "...............................................................................................\n");

    int iter = 0;
    while (1) {
        gaussian_elimination(n, A, x, y);
        double norm = normalize(n, y);
        if (norm == 0)
        { 
            break;
        }
        *eigenvalue = 1 / norm;

        printf("%d\t\t%lf\t", iter+1, *eigenvalue);
        fprintf(file1, "%d\t\t%lf\t", iter+1, *eigenvalue);
        for (int i = 0; i < n; i++)
        {
            printf("%lf ", y[i]);
            fprintf(file1, "%lf ", y[i]);
        }
        printf("\n");
        fprintf(file1, "\n");

        double diff = fabs(*eigenvalue - lambda_old);
        if (diff < EPSILON)
        {
             break;
        }

        for (int i = 0; i < n; i++)
        {
            x[i] = y[i];
        }
        lambda_old = *eigenvalue;
        iter++;
    }
    for (int i = 0; i < n; i++)
    {
        eigenvector[i] = x[i];
    }
}

int main() {
    int n;
    printf("Enter the size of the matrix: ");
    scanf("%d", &n);

    double A[n][n], x[n], max_eigenvector[n], min_eigenvector[n];
    double max_eigenvalue, min_eigenvalue;

    FILE *file2 = fopen("2_Result.txt", "w");
    FILE *file1 = fopen("2_Iteration_EV_table.txt", "w");
    if (file2 == NULL || file1 == NULL)
    {
        printf("Error for opening file.\n");
        return 1;
    }

    printf("Enter the %dx%d matrix:\n", n, n);
    for (int i = 0; i < n; i++)
     {
        for (int j = 0; j < n; j++) 
        {
            scanf("%lf", &A[i][j]);
        }
    }

    printf("Enter the initial guess vector:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%lf", &x[i]);
    }

    N_P_I_Method(n, A, max_eigenvector, &max_eigenvalue, x, file1);
    Inverse_Iteration_Method(n, A, min_eigenvector, &min_eigenvalue, x, file1);

    printf("\nLargest Eigen Value: %lf\n", max_eigenvalue);
    printf("Eigen Vector:[");
    fprintf(file2, "Largest Eigen Value: %lf\n", max_eigenvalue);
    fprintf(file2, "Eigen Vector:[");

    for (int i = 0; i < n; i++)
    {
         printf("%lf ", max_eigenvector[i]);
         fprintf(file2, "%lf ", max_eigenvector[i]);
    }
    printf("]\n");
    fprintf(file2, "]\n");

    printf("\nSmallest Eigen Value: %lf\n", min_eigenvalue);
    printf("Eigen Vector: [");
    fprintf(file2, "Smallest Eigen Value: %lf\n", min_eigenvalue);
    fprintf(file2, "Eigen Vector: [");

    for (int i = 0; i < n; i++) 
    {
        printf("%lf ", min_eigenvector[i]);
        fprintf(file2, "%lf ", min_eigenvector[i]);
    }
    printf("]\n");
    fprintf(file2, "]\n");

    fclose(file2);
    fclose(file1);

    return 0;
}
