#include <stdio.h>
#include <math.h>

int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } 
    else {
        int fact = 1;
        for (int i = 2; i <= n; i++) {
            fact *= i;
        }
        return fact;
    }
}

double sine_taylor(double x, int terms) {
    double sin_x = 0.0;
    for (int n = 0; n < terms; n++) {
        double term = pow(-1, n) * (pow(x, 2*n + 1) / factorial(2*n + 1));
        sin_x += term;
    }
    return sin_x;
}

double rel_error(double approx_value, double true_value) {
    return fabs((approx_value - true_value) / true_value);
}

int main() {
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Error for opening file.\n");
        return 1;  
    }
    double x;
    printf("Enter the value of x (in radians): ");
    scanf("%lf", &x);
    double true_value = sin(x);
    double result = sine_taylor(x, 6);
    printf("Approximate value of sin(x)  %.5lf\n", result);
    printf("True value of sin(x): %.5lf\n", true_value);
    printf("\n");
    printf("Terms\tsinx(approx)\t\tRelative Error\n");
    fprintf(file,"Terms\tRelative Error\n");
    printf("..............................................\n");
    fprintf(file,".....................\n");
    
    for (int i = 1; i <= 10; i++) {
        double approx_value = sine_taylor(x, i);
        double error = rel_error(approx_value, true_value);
        printf("%d\t%.10f\t\t%.10lf\n", i, approx_value, error);
        fprintf(file,"%d\t\t%.10lf\n", i, error);        
    }
    fclose(file);
    return 0;
}
