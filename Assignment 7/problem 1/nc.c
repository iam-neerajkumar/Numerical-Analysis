#include<stdio.h>
#include<math.h>

double f(double x)
{
    return exp(-x)-x;
}

double f_d(double x, double h)
{
    return (f(x+h)-f(x))/h;
}

int main()
{
    double x;
    double h=10e-10;
    double tol=10e-10;
    double x_new=x+1;

    printf("Enter the initial guess:");
    scanf("%lf",&x);

    while (fabs(x_new-x)>tol)
    {
        x=x_new;
        x_new=x-f(x)/f_d(x,h);
    }
    printf("Result:%lf",x_new);

    return 0;
}
