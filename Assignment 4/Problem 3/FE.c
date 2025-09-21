#include <stdio.h>
#include <math.h>

#define N 10

int gauss_eval_count = 0;
int jacobi_eval_count = 0;

// Gauss-Seidel method
void gauss_seidel_method(double A[N][N], double b[N], double x[N], int n, double eps, FILE *file) {
    double norm_diff;
    double norm_x;
    int iter = 0;

    gauss_eval_count = 0;

    while (1) {
        norm_diff = 0.0;
        norm_x = 0.0;

        for (int i = 0; i < n; i++) {
            double sum1 = 0.0;
            double sum2 = 0.0;

            for (int j = 0; j < i; j++) {
                sum1 += A[i][j] * x[j];
            }

            for (int j = i + 1; j < n; j++) {
                sum2 += A[i][j] * x[j];
            }
            double x_new = (b[i] - sum1 - sum2) / A[i][i];

            double diff = fabs(x_new - x[i]);
            if (diff > norm_diff) {
                norm_diff = diff;
            }
            double value = fabs(x_new);
            if (value > norm_x) {
                norm_x = value;
            }

            x[i] = x_new;
            gauss_eval_count++;
        }

        iter++;

        if (norm_diff / norm_x <= eps) {
            break;
        }
    }

// Show the correct function evaluations
    printf("Gauss-Seidel Method - Function evaluations: %d\n", gauss_eval_count);
    fprintf(file, "Gauss-Seidel Method - Function evaluations: %d\n", gauss_eval_count);
}

// Jacobi method
void jacobi_method(double A[N][N], double b[N], double x[N], int n, double eps, FILE *file) {
    double x_new[N];
    double norm_diff;
    double norm_x;
    int iter = 0;

    jacobi_eval_count = 0;

    while (1) {
        norm_diff = 0.0;
        norm_x = 0.0;

        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    sum += A[i][j] * x[j];
                }
            }
            x_new[i] = (b[i] - sum) / A[i][i];
        }

        for (int i = 0; i < n; i++) {
            double diff = fabs(x_new[i] - x[i]);
            if (diff > norm_diff) {
                norm_diff = diff;
            }
            double value = fabs(x_new[i]);
            if (value > norm_x) {
                norm_x = value;
            }
        }

        for (int i = 0; i < n; i++) {
            x[i] = x_new[i];
            jacobi_eval_count++;
        }

        iter++;

        if (norm_diff / norm_x <= eps) {
            break;
        }
    }

// Show the correct function evaluations 
    printf("Jacobi Method - Function evaluations: %d\n", jacobi_eval_count);
    fprintf(file, "Jacobi Method - Function evaluations: %d\n", jacobi_eval_count);
}

// Check for diagonal dominance
double diagonal_dominant(double A[N][N], int n) {
    double sum;
    for (int i = 0; i < n; i++) {
        sum = 0.0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                sum += A[i][j];
            }
        }

        if (fabs(A[i][i]) < sum) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int n;
    double eps;
    double A[N][N], b[N], x[N];

// Fixed tolerance values
    double tolerances[] = {0.1, 0.01, 0.001, 0.0001, 0.00001};
    int num_tolerances = sizeof(tolerances) / sizeof(tolerances[0]);

    FILE *file = fopen("function_eva_copa.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

// User input
    printf("Enter the size of matrix: ");
    scanf("%d", &n);
    printf("Enter the augmented matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
        scanf("%lf", &b[i]);
    }

    double is_diagonal_dominant = diagonal_dominant(A, n);

    if (!is_diagonal_dominant) {
        printf("Matrix is not diagonally dominant.\n\n");
        fprintf(file, "Matrix is not diagonally dominant.\n\n");
        printf("The method might still work, but it is not guaranteed to converge.\n");
    } else {
        printf("Matrix is diagonally dominant.\n");
        fprintf(file, "Matrix is diagonally dominant.\n");
    }

 // Initialize solution vector
    for (int i = 0; i < n; i++) {
        x[i] = 0.0;
    }

    for (int i = 0; i < num_tolerances; i++) {
        printf("\nTolerance: %.5lf\n", tolerances[i]);
        fprintf(file, "\nTolerance: %.5lf\n", tolerances[i]);

        gauss_eval_count = 0;
        jacobi_eval_count = 0;

        gauss_seidel_method(A, b, x, n, tolerances[i], file);

 // Reset solution vector for next method
        for (int j = 0; j < n; j++) {
            x[j] = 0.0;
        }

        jacobi_method(A, b, x, n, tolerances[i], file);
    }

    fclose(file);
    return 0;
}
