#include <stdio.h>
#include <math.h>

int main() {
     FILE *file;
     file = fopen("output_c_1.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
     }
    int n, i, j, k;
    float a[10][10], c, d[10] = {0}, temp;

    printf("Enter number of equations: ");
    scanf("%d", &n);
    printf("Enter the coefficients of all variables (constant term also):\n");

// Input augmented matrix
    for(i = 0; i < n; i++) {
        printf("Equation %d: ", i + 1);
        for(j = 0; j <= n; j++) {
            scanf("%f", &a[i][j]);
        }
    }

// Partial Pivoting: Loop through each column for the pivoting
    for(k = 0; k < n - 1; k++) {
        int max_row = k;
        for(i = k + 1; i < n; i++) {
            if(fabs(a[i][k]) > fabs(a[max_row][k])) {
                max_row = i;
            }
        }

// Swap rows if necessary
    if(max_row != k) {
        for(j = 0; j <= n; j++) {
                temp = a[k][j];
                a[k][j] = a[max_row][j];
                a[max_row][j] = temp;
            }
        }

// Display the matrix after pivoting operation
    printf("Matrix after pivoting (Step %d):\n", k + 1);
    fprintf(file, "Matrix after pivoting (Step %d):\n", k + 1);
    for(i = 0; i < n; i++) {
         for(j = 0; j <= n; j++) {
                printf("%6.1f", a[i][j]);
                fprintf(file,"%6.1f", a[i][j]);
         }
         printf("\n");
         fprintf(file,"\n");
     }

// Forward elimination 
     for(i = k + 1; i < n; i++) {
         c = a[i][k] / a[k][k];
         for(j = k; j <= n; j++) {
                a[i][j] -= c * a[k][j];
         }
     }
  }

// Display the matrix after forward elimination
    printf("Matrix after forward elimination:\n");
    fprintf(file, "Matrix after forward elimination:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j <= n; j++) {
            printf("%6.1f", a[i][j]);
            fprintf(file,"%6.1f", a[i][j]);
        }
        printf("\n");
        fprintf(file,"\n");
    }

// Back substitution operation
    for(i = n - 1; i >= 0; i--) {
        d[i] = a[i][n];
        for(j = i + 1; j < n; j++) {
            d[i] -= a[i][j] * d[j];
        }
        d[i] /= a[i][i];
    }

// Display the solution
    printf("The solution is:\n");
    fprintf(file,"The solution is:\n");
    for(i = 0; i < n; i++) {
        printf("x%d = %6.2f\n", i + 1, d[i]);
        fprintf(file,"x%d = %6.2f\n", i + 1, d[i]);
    }
    fclose(file);
    printf("Results have been saved to 'output_c_1.txt'.\n");
    return 0;
}
