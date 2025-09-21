#include <stdio.h>
#include <math.h>

#define N 10

// Gauss-Seidel method
void gauss_seidel_method(double A[N][N], double b[N], double x[N], int n, double eps, FILE *file)
{
    double norm_diff;
    double norm_x;
    int iter = 0;
    int fun_eval = 0;

    while (1)
    {
        norm_diff = 0.0;
        norm_x = 0.0;

        for (int i = 0; i < n; i++)
        {
            double sum1 = 0.0;  
            double sum2 = 0.0;  

            for (int j = 0; j < i; j++)
            {
                sum1 += A[i][j] * x[j];  
            }

            for (int j = i + 1; j < n; j++)
            {
                sum2 += A[i][j] * x[j]; 
            }
            double x_new = (b[i] - sum1 - sum2) / A[i][i];

            double diff = fabs(x_new - x[i]);
            if (diff > norm_diff)
            {
                norm_diff = diff; //norm_2
            }
            double value = fabs(x_new);
            if (value > norm_x)
            {
                norm_x = value; //norm infinite
            }

            x[i] = x_new;
            fun_eval++;
        }

        printf("%d\t\t", iter + 1);
        fprintf(file, "%d\t\t", iter + 1);
        for (int i = 0; i < n; i++)
        {
            printf("%lf\t", x[i]);
            fprintf(file, "%lf\t", x[i]);
        }
        printf("\n");
        fprintf(file, "\n");

        iter++;

        if (norm_diff / norm_x <= eps)
        {
            break;
        }
    }

    printf("Converged at %d iteration(s).\n", iter);
    printf("Exact function of evaluation: %d \n", fun_eval);
    fprintf(file, "Converged at %d iteration(s).\n", iter);
    fprintf(file, "Exact function of evaluation: %d \n", fun_eval);
}

// Jacobi method
void jacobi_method(double A[N][N], double b[N], double x[N], int n, double eps, FILE *file)
{
    double x_new[N];
    double norm_diff;
    double norm_x;
    int iter = 0;
    int fun_eval = 0;

    while (1)
    {
        norm_diff = 0.0;
        norm_x = 0.0;

        for (int i = 0; i < n; i++)
        {
            double sum = 0.0;
            for (int j = 0; j < n; j++)
            {
                if (i != j)
                {
                    sum += A[i][j] * x[j];
                }
            }
            x_new[i] = (b[i] - sum) / A[i][i];
        }

        for (int i = 0; i < n; i++)
        {
            double diff = fabs(x_new[i] - x[i]);
            if (diff > norm_diff)
            {
                norm_diff = diff;  //norn 2
            }
            double value = fabs(x_new[i]);
            if (value > norm_x)
            {
                norm_x = value;    //norm infinite
            }
        }

        for (int i = 0; i < n; i++)
        {
            x[i] = x_new[i];
            fun_eval++;
        }

        printf("%d\t\t", iter + 1);
        fprintf(file, "%d\t\t", iter + 1);

        for (int i = 0; i < n; i++)
        {
            printf("%lf\t", x[i]);
            fprintf(file, "%lf\t", x[i]);
        }
        printf("\n");
        fprintf(file, "\n");

        iter++;

        if (norm_diff / norm_x <= eps)
        {
            break;
        }
    }

    printf("Converged at %d iteration(s).\n", iter);
    fprintf(file, "Converged at %d iteration(s).\n", iter);
    printf("Exact function of evaluation: %d \n", fun_eval);
    fprintf(file, "Exact function of evaluation: %d \n", fun_eval);
}

// Check for diagonal dominance
double diagonal_dominant(double A[N][N], int n)
{
    double sum;
    for (int i = 0; i < n; i++)
    {
        sum = 0.0;
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                sum += A[i][j];
            }
        }

        if (fabs(A[i][i]) < sum)
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    int n;
    double eps;
    double A[N][N], b[N], x[N];
    int method_choice;

// Result print to a file
    FILE *file = fopen("output.txt", "w");
    if (file == NULL)
    {
        printf("Error for opening file.\n");
        return 1;
    }

//user input 
    printf("Enter the size of matrix: ");
    scanf("%d", &n);
    printf("Enter the augmented matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%lf", &A[i][j]);
        }
        scanf("%lf", &b[i]);
    }

    double is_diagonal_dominant = diagonal_dominant(A, n);

    if (!is_diagonal_dominant)
    {
        printf("Matrix is not diagonally dominant.\n");
        fprintf(file, "Matrix is not diagonally dominant.\n");
        printf("The method might still work, but it is not guaranteed to converge.\n");
    }
    else
    {
        printf("Matrix is diagonally dominant.\n");
        fprintf(file, "Matrix is diagonally dominant.\n");
    }

    printf("Enter the tolerance value: ");
    scanf("%lf", &eps);
    fprintf(file, "Entered tolerance value: %lf\n\n", eps);

    for (int i = 0; i < n; i++)
    {
        x[i] = 0.0; 
    }

    printf("Select method:\n1. Gauss-Seidel\n2. Jacobi\n");
    scanf("%d", &method_choice);

    printf("Iteration\t");
    fprintf(file, "Iteration\t");
    for (int i = 0; i < n; i++)
    {
        printf("x%d\t\t", i + 1);
        fprintf(file, "x%d\t\t", i + 1);
    }
    printf("\n");
    printf("--------------------------------------------------------------------------------------------------\n");
    fprintf(file,"\n------------------------------------------------------------------------------------------\n");

    if (method_choice == 1)
    {
        gauss_seidel_method(A, b, x, n, eps, file);
    }
    else if (method_choice == 2)
    {
        jacobi_method(A, b, x, n, eps, file);
    }
    else
    {
        printf("Invalid choice.\n");
    }

    fclose(file);

    return 0;

}
