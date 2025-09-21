#include <stdio.h>
#include <math.h>

double f(double y)
{
    return -0.06*sqrt(y);
}

void euler(double t_0, double y_0, double y_n, double h)
{
    double t = t_0;
    double y = y_0;
    
    printf("Euler Method\n");
    printf("Time \t\t Func eval (y) \t Comparison \t Truncation error Percentage relative error\n");
    printf(".....................................................................................................\n");
    while (y >= 0)
    {
        printf("%.5lf \t %.5lf \t %.5lf \t %.5lf \t %.5lf\n", t, y, (57.73502692-t), (-0.03*h*h)/(2*sqrt(y)), ((57.73502692-t)*100)/57.73502692);
        y = y + f(y) * h;
        t = t + h;
    }
    printf("Taking Time: %.5lf minutes.\n\n", t);
}

void heun(double t_0, double y_0, double y_n, double h)
{
    double t = t_0;
    double y = y_0;

    printf("Heun Method\n");
    printf("Time \t\t Func eval (y) \t Comparison \t Truncation error Percentage relative error\n");
    printf(".............................................................................................\n");
    while (y >= 0)
    {
        printf("%.5lf \t %.5lf \t %.5lf \t %.5lf \t %.5lf\n", t, y, (57.73502692-t), (-0.03*h*h)/(2*sqrt(y)), ((57.73502692-t)*100)/57.73502692);
        double f1 = f(y);
        double y_predict = y + h * f1;
        double f2 = f(y_predict);

        y = y + (h / 2.0) * (f1 + f2);
        t = t + h;
    }
    printf("Taking time: %.5lf minutes.\n", t);
}

int main()
{
    FILE *input, *output;
    input = fopen("input.txt", "r");
    
    if (input == NULL) 
    {
        printf("Error opening output file.\n");
        return 1;
    }

    double t_0, y_n, y_0, h;
    
    fscanf(input,"%lf", &t_0);

    fscanf(input,"%lf", &y_0);
    
    fscanf(input,"%lf", &y_n);

    fscanf(input,"%lf", &h);

    euler(t_0, y_0, y_n, h);
    heun(t_0, y_0, y_n, h);

    fclose(input);
    return 0;
}

