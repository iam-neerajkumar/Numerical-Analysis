#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double f(double x) 
{
    return (x * x) / (1 + x * x);
}

int main() 
{
    int n, i, j;
    double h[10], a, b, c, d, sum, x[10], f_values[10], F[10], s[10] = {0}, p, m[10][10] = {0}, ratio, exact_value, error;
    FILE *file, *output;

    file = fopen("data_1.txt", "r");
    output = fopen("output_1a.txt","w");
    if (file == NULL) 
    {
        printf("Error opening file.\n");
        return 1;
    }

    if (output == NULL) 
    {
        printf("Error opening file.\n");
        return 1;
    }

    fprintf(output,"Name-Neeraj kumar\nRoll No-244103315\n\n\n");

    fscanf(file, "%d", &n);
    printf("Number of data-points: %d\n", n);

    for (i = 0; i < n; i++) 
    {
        fscanf(file, "%lf %lf", &x[i], &f_values[i]);
        printf("x = %.6lf, f(x) = %.6lf\n", x[i], f_values[i]);
    }

    for (i = n - 1; i > 0; i--) 
    {
        F[i] = (f_values[i] - f_values[i - 1]) / (x[i] - x[i - 1]);
        h[i - 1] = x[i] - x[i - 1];
    }

// System of equations
    for (i = 1; i < n - 1; i++) 
    {
        m[i][i] = 2 * (h[i - 1] + h[i]);
        if (i != 1) 
        {
            m[i][i - 1] = h[i - 1];
            m[i - 1][i] = h[i - 1];
        }
        m[i][n - 1] = 6 * (F[i + 1] - F[i]);
    }

// Gaussian elimination
    for (i = 1; i < n - 1; i++) 
    {
        ratio = m[i + 1][i] / m[i][i];
        for (j = i; j < n; j++) 
        {
            m[i + 1][j] -= ratio * m[i][j];
        }
    }

// Back substitution
    for (i = n - 2; i > 0; i--) 
    {
        sum = 0;
        for (j = i; j < n - 1; j++) 
        {
            sum += m[i][j] * s[j];
        }
        s[i] = (m[i][n - 1] - sum) / m[i][i];
    }

    printf("Enter x to interpolate: ");
    scanf("%lf", &p);
    fprintf(output,"Enter x to interpolate: %.2lf \n",p);

    for (i = 0; i < n - 1; i++) 
    {
        if (x[i] <= p && p <= x[i + 1]) 
        {
            a = (s[i + 1] - s[i]) / (6 * h[i]);
            b = s[i] / 2;
            c = (f_values[i + 1] - f_values[i]) / h[i] - (2 * h[i] * s[i] + s[i + 1] * h[i]) / 6;
            d = f_values[i];
            sum = a * pow((p - x[i]), 3) + b * pow((p - x[i]), 2) + c * (p - x[i]) + d;
            break;
        }
    }

    printf("Coefficients:\n.....................\n a = %.5lf\n b = %.5lf\n c = %.5lf \nd = %.5lf\n\n", a, b, c, d);
    printf("Interpolated value: f (%.2lf) = %.5lf\n", p, sum);
    fprintf(output,"Coefficients:\n.....................\n a = %.5lf\n b = %.5lf\n c = %.5lf \nd = %.5lf\n\n", a, b, c, d);
    fprintf(output,"Interpolated value: f (%.2lf) = %.5lf\n", p, sum);

    exact_value = f(p);
    error = fabs((exact_value - sum)/exact_value)*100;
    printf("Exact value: f(%.2lf) =%.5lf\n", p, exact_value);
    printf("Absolute error = %.5lf %% \n", error);
    fprintf(output,"Exact value: f(%.2lf) =%.5lf\n", p, exact_value);
    fprintf(output,"Absolute error = %.5lf %% \n", error);


    fclose(file);
    fclose(output);

    return 0;
}
