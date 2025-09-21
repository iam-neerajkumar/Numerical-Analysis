#include <stdio.h>
#include <math.h>
 
//function for f(x).
double f(double x)
{
    //return (x*x*x - 2*x - 5);
    //return x*sin(x)-1;
      return exp(-x)-x;
}
 
//function for f(x) derivative.
double f_derivative(double x, double h)
{
    return (f(x + h) - f(x)) / h;
}
 
int main()
{
//Result print to file.
    FILE *file = fopen("output_1c.txt","w");
    if (file==NULL)
    {
        printf("Error to open the file.");
        return 1 ;
    }
    
    double x;
    double h = 10e-10;
    double tolerance = 10e-10;
    double x_new;
    int iteration = 1;
    printf("Enter initial guess value: ");
    scanf("%lf", &x);

    x_new = x + 1;

    fprintf(file,"Name-Neeraj Kumar\nRoll No-244103315\n\n");
    printf("Iterations\tx\t\tEvaluation\n");
    printf("...............................................\n");
    fprintf(file,"Iterations\tx\t\tfunction evaluation\n");
    fprintf(file,"...............................................\n");
 
    while (fabs(x_new - x) > tolerance)
    {
        x = x_new;
        x_new = x - f(x) / f_derivative(x, h);
//Result
        printf("%d\t\t%lf\t%lf\n", iteration, x_new, f(x_new));
        fprintf(file,"%d\t\t%lf\t%lf\n", iteration, x_new, f(x_new));
        iteration++;
    }
    printf("Root: %.5f\n", x_new);
    fprintf(file,"Root: %.5f\n", x_new);
    printf("Converged at %d iterations.\n",iteration);
    fprintf(file,"Converged at %d iterations.\n",iteration);

    fclose(file);
    return 0;
}