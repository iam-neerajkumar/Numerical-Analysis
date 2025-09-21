#include <stdio.h>
#include <math.h>
 
//Formula for 2nd order Lagrange function
double L_D(double y[], double v[], double y_0)
{
    return v[0] * ((2 * y_0 - y[1] - y[2]) / ((y[0] - y[1]) * (y[0] - y[2]))) +
           v[1] * ((2 * y_0 - y[0] - y[2]) / ((y[1] - y[0]) * (y[1] - y[2]))) +
           v[2] * ((2 * y_0 - y[0] - y[1]) / ((y[2] - y[0]) * (y[2] - y[1])));
}
 
int main()
{
//input outout file
    FILE *input, *output;
    input = fopen("input_2.txt", "r");
    output = fopen("output_2.txt", "w");
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
    fprintf(output,"Name-Neeraj Kumar\nRoll No-244103315\n\n\n");

    double y[3], v[3];

//Taking input from file
    for (int i = 0; i < 3; i++)
    {
        fscanf(input,"%lf", &y[i]);
    }
    for (int i = 0; i < 3; i++)
    {
        fscanf(input,"%lf", &v[i]);
    }
    double dv_dy = L_D(y, v, 0); 
    double mu = 1.8*pow(10,-5);
    double tau = mu*L_D(y, v, 0);

//Result
    printf("Result\n..................................\n");
    printf("Value of dv/dy :%.8lf s^-1\n", dv_dy);
    printf("Value of shear stress :%.8lf N/m^2\n\n", tau);
    fprintf(output,"Result\n.................................\n");
    fprintf(output,"Value of dv/dy :%.8lf s^-1\n", dv_dy);
    fprintf(output,"Value of shear stress :%.8lf N/m^2\n\n", tau);
    
    fclose(input);
    fclose(output);
    return 0;
}