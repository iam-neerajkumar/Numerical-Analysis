#include <stdio.h>
#include <math.h>

double f(double y)
{
    return -0.06 * sqrt(y);
}

void rk4(double t_0, double y_0, double y_n, double h)
{
    double t = t_0;
    double y = y_0;
    int function_evaluation = 0;

    printf("\nRunge-Kutta 4th Order Method (RK4)\n");
    printf("Time \t\t Height(y)\n");
    printf("..........................\n");

    while (y >= 0)
    {
        printf("%.5lf \t %.5lf\n", t, y);

        double k1 = f(y);
        function_evaluation++;

        double k2 = f(y + 0.5 * h * k1);
        function_evaluation++;

        double k3 = f(y + 0.5 * h * k2);
        function_evaluation++;

        double k4 = f(y + h * k3);
        function_evaluation++;

        y = y + (h / 6.0) * (k1 + 2*k2 + 2*k3 + k4);
        t = t + h;
    }
    
    printf("Taking time: %.5lf minutes.\n", t);
    printf("Percentage relative error: %lf %%\n", (((57.73502692-t)*100)/57.73502692));
    printf("Function evaluation: %d\n", function_evaluation);
}

int main()
{
    FILE *input;
    input = fopen("input.txt", "r");

    if (input == NULL)
    {
        printf("Error opening input file.\n");
        return 1;
    }

    double t_0, y_n, y_0, h;

    fscanf(input, "%lf", &t_0);
    fscanf(input, "%lf", &y_0);
    fscanf(input, "%lf", &y_n);
    fscanf(input, "%lf", &h);

    // heun(t_0, y_0, y_n, h); // Optional: comment or uncomment as needed
    rk4(t_0, y_0, y_n, h);

    fclose(input);
    return 0;
}
