#include <stdio.h>
#include <math.h>

#define N 10

void gauss_seidel_method(double A[N][N], double b[N], double x[N], int n, double eps)
{
    double norm_diff, norm_x;
    int iter = 0;

    // Initial guess
    for (int i = 0; i < n; i++) 
    {
        x[i] = 0.0;
    }

    printf("Iteration\t");
    for (int i = 0; i < n; i++) 
    {
        printf("x[%d]\t\t", i);
    }
    printf("\n");

    while (1)
    {
        norm_diff = 0.0;
        norm_x = 0.0;

        for (int i = 0; i < n; i++)
        {
            double sum1 = 0.0, sum2 = 0.0;

            for (int j = 0; j < i; j++)
                sum1 += A[i][j] * x[j];  // Updated values

            for (int j = i + 1; j < n; j++)
                sum2 += A[i][j] * x[j];  // Old values

            double x_old = x[i];
            x[i] = (b[i] - sum1 - sum2) / A[i][i];

            double diff = fabs(x[i] - x_old);
            if (diff > norm_diff)
                norm_diff = diff;

            double val = fabs(x[i]);
            if (val > norm_x)
                norm_x = val;
        }

        iter++;

        printf("%d\t\t", iter);
        for (int i = 0; i < n; i++) 
        {
            printf("%lf\t", x[i]);
        }
        printf("\n");

        if (norm_diff / norm_x <= eps)
            break;

        if (iter > 10000) 
        {
            printf("Method did not converge.\n");
            break;
        }
    }
}

int main()
{
    FILE *input = fopen("input.txt", "r");
    if (input == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    int n;
    double eps;
    double A[N][N], b[N], x[N];

    fscanf(input, "%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(input, "%lf", &A[i][j]);
        }
        fscanf(input, "%lf", &b[i]);
    }
    fscanf(input, "%lf", &eps);

    fclose(input);

    gauss_seidel_method(A, b, x, n, eps);

    return 0;
}
  