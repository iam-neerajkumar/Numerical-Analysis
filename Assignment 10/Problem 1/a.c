#include<stdio.h>
#include<math.h>
 
#define N 100  
 
double Trapezoidal(double x[], double F[], int n)
{
    double I = 0.0;
    for (int i = 1; i < n; i++)  
    {
        I += ((x[i] - x[i-1]) / 2) * (F[i] + F[i-1]);  
    }
    return I;
}
 
int main()
{
    FILE *input, *output;
    input = fopen("input_1.txt", "r");
    output = fopen("output_1a.txt", "w");
    if (input == NULL) 
    {
        printf("Error opening input file.\n");
        return 1;
    }
    if (output == NULL) 
    {
        printf("Error opening output file.\n");
        return 1;
    }
    fprintf(output,"Name-Neeraj Kumar\nRoll no-244103315\n\n\n");

    int n;
    double x[N], F[N], exact_value;  

    fscanf(input,"%d", &n);
 
    for (int i = 0; i < n; i++)  
    {
        fscanf(input,"%lf", &x[i]);  
    }
    
    for (int i = 0; i < n; i++)  
    {
        fscanf(input,"%lf", &F[i]);  
    }

    fscanf(input,"%lf",&exact_value);

    double result = Trapezoidal(x, F, n);
    double error;
    error=(fabs(exact_value-result)/exact_value)*100 ;

    printf("\nIntegration value by trapezoidal rule: %.5lf\n", result);
    printf("Exact value: %.5lf\n", exact_value);
    printf("Relative error value: %.2lf %%\n\n", error);
    fprintf(output,"\nIntegration value by trapezoidal rule: %.5lf\n", result);
    fprintf(output,"Exact value: %.5lf\n", exact_value);
    fprintf(output,"Relative error value: %.2lf %%\n\n", error);

    fclose(input);
    fclose(output);
    return 0;
}