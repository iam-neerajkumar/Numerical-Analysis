#include <stdio.h>
#include <math.h>
 
#define N 100  
 
double multiple_rule(double x[], double F[])
{
    double I_1, I_2, I_3;

    I_1=((x[1]-x[0])/2)*(F[0]+F[1]);
    I_2=((x[4]-x[1])/8)*(F[1]+3*F[2]+3*F[3]+F[4]);
    I_3=((x[6]-x[4])/6)*(F[4]+4*F[5]+F[6]);
 
    return I_1 + I_2 + I_3;
}
 
int main()
{
    FILE *input, *output;
    input = fopen("input_1.txt", "r");
    output = fopen("output_1b.txt", "w");
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

    fscanf(input,"%lf", &exact_value);

    double result = multiple_rule(x, F);
    double error;
    error=(fabs(exact_value-result)/exact_value)*100 ;

    printf("\nIntegration value by combination of Trapezoidal rule and Simpsons rules: %.5lf\n", result);
    printf("Exact value: %.5lf\n", exact_value);
    printf("Relative error value: %.2lf %%\n\n", error);
    fprintf(output,"\nIntegration value by combination of Trapezoidal rule and Simpsons rules: %.5lf\n", result);
    fprintf(output,"Exact value: %.5lf\n", exact_value);
    fprintf(output,"Relative error value: %.2lf %%\n\n", error);

    fclose(input);
    fclose(output);
    return 0;
}