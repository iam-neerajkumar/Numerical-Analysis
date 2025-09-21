#include<stdio.h>
#include<math.h>

int main()
{
    int n;
    double X[100], F[100];
    double sum = 0, L;
    double x;

    FILE *file, *output;
    file = fopen("data_3.txt", "r");
    output = fopen("Output_3.txt", "w");

    if (file == NULL) 
    {
        printf("Error opening the file.\n");
        return 1;
    }
    if (output == NULL) 
    {
        printf("Error opening the file.\n");
        return 1;
    }
    fprintf(output,"Name-Neeraj Kumar\n Roll No-244103315\n\n\n");

    fscanf(file, "%d", &n);

    for (int i = 0; i < n; i++) 
    {
        fscanf(file, "%lf", &X[i]);
    }

    for (int i = 0; i < n; i++) 
    {
        fscanf(file, "%lf", &F[i]);
    }

    fscanf(file, "%lf", &x);

    fclose(file);

    for (int i = 0; i < n; i++) 
    {
        L = 1;
        for (int j = 0; j < n; j++) 
        {
            if (i != j) 
            {
                L = L * ((x - X[j]) / (X[i] - X[j]));
            }
        }
        sum = sum + L * F[i];
    }

    printf("f(%lf) = %lf\n", x, sum);
    printf("Absolute Error:\n ");
    printf("..................\n");

    fprintf(output,"f(%lf) = %lf\n", x, sum);
    fprintf(output,"Absolute Error:\n ");
    fprintf(output,"..................\n");
    
    for (int k = 0; k < n; k++)
    {
        double f_x = 0.0;
        for (int i = 0; i < n; i++) 
        {
            L = 1;
            for (int j = 0; j < n; j++) 
            {
                if (i != j) 
                {
                    L = L * ((X[k] - X[j]) / (X[i] - X[j]));
                }
            }
            f_x = f_x + L * F[i];
        }
        
        double Error = fabs((F[k] - f_x)/F[k])*100;
        printf("at X(%d) = %lf\n",k,Error);
        fprintf(output,"at X(%d) = %lf\n",k,Error);
    }
    fclose(output);
    return 0;
}
