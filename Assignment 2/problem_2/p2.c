#include <stdio.h>
#include <math.h>

double sin_horner(double x) {
    double result = 0.0;
    double term = x;
    for (int i = 1; i <= 6; i++) {
        result += term;
        term *= -(x * x) / ((2 * i) * (2 * i + 1));
    }
    return result;
}

int main() {
    FILE *file = fopen("output.txt","w");
    if (file == NULL)
    {
        printf("Error to open for this file \n");
    }
    
    double x;
    printf("Enter the value of x (in radians): ");
    scanf("%lf", &x);
    
    double approx_value = sin_horner(x);
    double true_value = sin(x);
    
    printf("\nApproximate value of sin(x) (up to 6 terms): %.10lf\n", approx_value);
    printf("True value of sin(x): %.10lf\n", true_value);
    printf("Relative Error: %.10lf\n\n", fabs(approx_value - true_value) / true_value);

    fprintf(file,"Approximate value of sin(x) (up to 6 terms): %.10lf\n", approx_value);
    fprintf(file,"True value of sin(x): %.10lf\n", true_value);
    fprintf(file,"Relative Error: %.10lf\n\n", fabs(approx_value - true_value) / true_value);
    
    fclose(file);
    return 0;
}
