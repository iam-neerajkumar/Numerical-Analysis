#include<stdio.h>
#include<math.h>

double Gauss_lagendre_formula(double x_d)
{
    double a_0 = 1.0;
    double a_1 = 1.0;
    double x = a_0 + a_1*x_d;

    return (exp(x) * sin(x)) / (1 + x * x);
}

int main()
{
    FILE *output;
    output = fopen("output_2.txt", "w");
    if (output == NULL) 
    {
        printf("Error opening output file.\n");
        return 1;
    }
    fprintf(output,"Name-Neeraj Kumar\nRoll no-244103315\n\n\n");

    double f_2_0 = Gauss_lagendre_formula(-0.5773);
    double f_2_1 = Gauss_lagendre_formula(0.5773);

    double f_3_0 = Gauss_lagendre_formula(-0.7745);
    double f_3_1 = Gauss_lagendre_formula(0.0);
    double f_3_2 = Gauss_lagendre_formula(0.7745);

    double f_4_0 = Gauss_lagendre_formula(-0.33998);
    double f_4_1 = Gauss_lagendre_formula(0.33998);
    double f_4_2 = Gauss_lagendre_formula(-0.86114);
    double f_4_3 = Gauss_lagendre_formula(0.86114);
    
    double f_2 = f_2_0+f_2_1;
    double f_3 = 0.5556*f_3_0+0.8889*f_3_1+0.5556*f_3_2;
    double f_4 = 0.65215*f_4_0+0.65215*f_4_1+0.34785*f_4_2+.34785*f_4_3;
    double error, eaxct_value;
    eaxct_value = 1.94013;

    printf("Exact value : %.6lf\n",eaxct_value);
    printf("Value of integration by two-point Gauss-Legendre formula : %.6lf Error : %.6lf\n",f_2,fabs(f_2-eaxct_value));
    printf("Value of integration by three-point Gauss-Legendre formula : %.6lf Error : %.6lf\n",f_3,fabs(f_3-eaxct_value));
    printf("Value of integration by four-point Gauss-Legendre formula : %.6lf Error : %.6lf\n",f_4,fabs(f_4-eaxct_value));
    fprintf(output,"Exact value : %.6lf\n",eaxct_value);
    fprintf(output,"Value of integration by two-point Gauss-Legendre formula : %.6lf Error : %.6lf\n",f_2,fabs(f_2-eaxct_value));
    fprintf(output,"Value of integration by three-point Gauss-Legendre formula : %.6lf Error : %.6lf\n",f_3,fabs(f_3-eaxct_value));
    fprintf(output,"Value of integration by four-point Gauss-Legendre formula : %.6lf Error : %.6lf\n",f_4,fabs(f_4-eaxct_value));

    fclose(output);
    return 0;
}
