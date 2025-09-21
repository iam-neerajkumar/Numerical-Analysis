#include<stdio.h>
#include<math.h>

# define N 6  // No of coefficient.

//function
double F(double coeff[], int degree, double x)
{
    double result = 0.0;
    for (int i = 0; i <= degree; i++)
    {
        result += coeff[i]*pow(x,i);
    }
    return result;
    
}

//derivative
double derivative(double coeff[], int degree, double x)
{
    double result = 0.0;
    for (int i = 1; i <= degree; i++)
    {
        result += i*coeff[i]*pow(x,i-1);
    }
    return result;
    
}

//Forward Difference
double F_D(double coeff[], int degree, double x, double h)
{
    return  (F(coeff,degree,x+h)-F(coeff,degree,x))/h;
}

//Backward Difference
double B_D(double coeff[], int degree, double x, double h)
{
    return  (F(coeff,degree,x)-F(coeff,degree,x-h))/h;
}

//Centered Difference
double C_D(double coeff[], int degree, double x, double h)
{
    return  (F(coeff,degree,x+h)-F(coeff,degree,x-h))/(2*h);
}

int main()
{
    int degree = N-1;

//input file and output file    
    FILE *input, *output;
    input = fopen("input_1.txt", "r");
    output = fopen("output_1.txt","w");
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

    double coeff[N];
    for (int i = 0; i < N; i++)
    {
        fscanf(input,"%lf",&coeff[i]);
    }
    
    double x, h[3];
    fscanf(input,"%lf",&x);
    for (int i = 0; i < 3; i++)
    {
        fscanf(input,"%lf",&h[i]);
    }

    //result
    double True_value = derivative(coeff, degree, x);
    printf("True vaue:%.8lf\n",True_value);
    fprintf(output,"True Value:%.8lf\n",True_value);

    for (int i = 0; i < 3; i++)
    {
        double FD=F_D(coeff,degree,x,h[i]);
        double BD=B_D(coeff,degree,x,h[i]);
        double CD=C_D(coeff,degree,x,h[i]);

        printf("\nStep size (h): %.2lf\n",h[i]);
        printf("...........................................................\n");
        printf("Forward Difference  : %.8lf\t Error : %.8lf\n",FD,fabs(FD-True_value));
        printf("Backward difference : %.8lf\t Error : %.8lf\n",BD,fabs(BD-True_value));
        printf("Centered Difference : %.8lf\t Error : %.8lf\n",CD,fabs(CD-True_value));

        fprintf(output,"\nStep size (h): %.2lf\n",h[i]);
        fprintf(output,".............................................................\n");
        fprintf(output,"Forward Difference   : %.8lf\t Error : %.8lf\n",FD,fabs(FD-True_value));
        fprintf(output,"Backward difference  : %.8lf\t Error : %.8lf\n",BD,fabs(BD-True_value));
        fprintf(output,"Centered Difference  : %.8lf\t Error : %.8lf\n",CD,fabs(CD-True_value));
    }
    fclose(input);
    fclose(output);
    return 0;   
}