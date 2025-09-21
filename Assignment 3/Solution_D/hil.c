#include <stdio.h>
#include<math.h>

// Hilbert matrix
void Hilbert_matrix(int n, double H[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            H[i][j] = 1.0 / ((i + 1) + (j + 1) - 1.0);
        }
    }   
}

// Vector b
void Vector_b(int n, double H[n][n], double b[n]) {
    for (int i = 0; i < n; i++) {
        b[i] = 0.0;
        for (int j = 0; j < n; j++) {
            b[i] += H[i][j];
        }
    }
}

// Print matrix
void print_matrix(int n, double H[n][n], FILE *file) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.5lf ", H[i][j]);
            fprintf(file, "%.5lf ", H[i][j]);
    }
        printf("\n");
        fprintf(file, "\n");
   }
}

// Print vector
void print_vector_b(int n, double b[n], FILE *file) {
    for (int i = 0; i < n; i++) {
        printf("%.5lf\n", b[i]);
        fprintf(file, "%.5lf\n", b[i]);
    }
}

int main() {
    int n;
    printf("Enter the size of Hilbert matrix (n): ");
    scanf("%d", &n);

    double H[n][n];  
    double b[n];   

    Hilbert_matrix(n, H);
    Vector_b(n, H, b);

    FILE *file = fopen("output_d.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    fprintf(file, "Hilbert Matrix (H):\n");
    printf("Hilbert Matrix (H):\n");
    print_matrix(n, H, file);

    fprintf(file, "\nVector b:\n");
    printf("\nVector b:\n");
    print_vector_b(n, b, file);

    fclose(file);
    printf("Results have been saved to 'output_d.txt'.\n");

    return 0;
}

