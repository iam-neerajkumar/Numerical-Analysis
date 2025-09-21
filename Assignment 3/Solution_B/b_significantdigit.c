
#include <stdio.h>
#include <math.h>

double significant_digit(int d, double x) {
    if (x == 0) return 0;
    double scale = pow(10, d - (int)log10(fabs(x)) - 1);
    return round(x * scale) / scale;
}

int multi_count = 0, div_count = 0;

void gauss_elimination(int n, double a[10][11], double x[10], int d) {
    int i, j, k;
    for (k = 0; k < n - 1; k++) {
        for (i = k + 1; i < n; i++) {
            double factor = a[i][k] / a[k][k];
            div_count++;
            for (j = k; j <= n; j++) {
                a[i][j] -= factor * a[k][j];
                multi_count++;
            }
        }
    }
    for (i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (j = i + 1; j < n; j++) {
            sum += a[i][j] * x[j];
            multi_count++;
        }
        x[i] = significant_digit(d, (a[i][n] - sum) / a[i][i]);
        div_count++;
    }
}

void cal_errors(int n, double x[10], double x_star[10], double *norm_2, double *norm_inf) {
    *norm_2 = 0;
    *norm_inf = 0;
    for (int i = 0; i < n; i++) {
        double diff = fabs(x[i] - x_star[i]);
        *norm_2 += diff * diff;
        if (diff > *norm_inf) {
            *norm_inf = diff;
        }
    }
    *norm_2 = sqrt(*norm_2);
}

int main() {
    int n, i, j, d_values[] = {4, 5, 6, 7, 8, 9, 10};
    double a[10][11], x[10], x_star[10], norm_2, norm_inf;

    printf("Enter number of equations: ");
    scanf("%d", &n);
    printf("Enter coefficients of all variables and constants:\n");
    for (i = 0; i < n; i++) {
        printf("Equation %d: ", i + 1);
        for (j = 0; j <= n; j++) {
            scanf("%lf", &a[i][j]);
        }
    }

    double a_copy[10][11];
    for (i = 0; i < n; i++)
        for (j = 0; j <= n; j++)
            a_copy[i][j] = a[i][j];

    gauss_elimination(n, a_copy, x_star, 10);

    FILE *file = fopen("output_b_2.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    fprintf(file, "Exact solution with 10 significant digits:\n");
    for (i = 0; i < n; i++) {
        fprintf(file, "x%d = %.10f\n", i + 1, x_star[i]);
    }
    
    fprintf(file, "\nSignificant digits\t\t");
    for (i = 0; i < n; i++) {
        fprintf(file, "x%d\t\t\t\t", i + 1);
    }

    fprintf(file, "||x - x*||_2 \t\t\t ||x - x*||_∞ \t\t Mul/Div\n");
    fprintf(file, "--------------------------------------------------------------------------------------------------------------------------------\n");

    for (int idx = 0; idx < 7; idx++) {
        int d = d_values[idx];
        multi_count = 0;
        div_count = 0;

        for (i = 0; i < n; i++)
            for (j = 0; j <= n; j++)
                a[i][j] = a_copy[i][j];

        gauss_elimination(n, a, x, d);
        cal_errors(n, x, x_star, &norm_2, &norm_inf);

        fprintf(file, "%10d", d);
        for (i = 0; i < n; i++) {
            fprintf(file, "%15.*f\t", d, x[i]);
        }
        fprintf(file, "\t %.10e\t\t %.10e\t\t %d/%d\n", norm_2, norm_inf, multi_count, div_count);
    }
    
    fclose(file);
    printf("Results have been saved to 'output_b_2.txt'.\n");

    return 0;
}
