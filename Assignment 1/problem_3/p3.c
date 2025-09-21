#include <stdio.h>

typedef struct complex {
    float real,imag;
} complex;

// Function for Addition
//(a + bi) + (c + di)=(a+c) + (b+d)i
complex add(complex n1, complex n2) {
    complex temp;
    temp.real = n1.real + n2.real;
    temp.imag = n1.imag + n2.imag;
    return temp;
}

// Function for subtraction
//(a + bi) - (c + di)=(a-c) + (b-d)i
complex sub(complex n1, complex n2) {
    complex temp;
    temp.real = n1.real - n2.real;
    temp.imag = n1.imag - n2.imag;
    return temp;
}

// Function for multiply
// (a + bi) * (c + di) = ac - bd + (ad + bc)i
complex mult(complex n1, complex n2) {
    complex temp;
    temp.real = n1.real * n2.real - n1.imag * n2.imag;  
    temp.imag = n1.real * n2.imag + n1.imag * n2.real;
    return temp;
}

// Function for conjugate 
// (a+bi)=(a-bi)
complex conjugate(complex n) {
    complex temp;
    temp.real = n.real;
    temp.imag = -n.imag;  
    return temp;
}

int main() {
    complex n1, n2, result;

    // FIRST COMPLEX NUMBER
    printf("FIRST COMPLEX NUMBER\n");
    printf(".......................\n");
    printf("Enter real and imaginary parts res:\n");
    scanf("%f %f", &n1.real, &n1.imag);

    // SECOND COMPLEX NUMBER
    printf("SECOND COMPLEX NUMBER\n");
    printf(".......................\n");
    printf("Enter real and imaginary parts res:\n");
    scanf("%f %f", &n2.real, &n2.imag);
    printf("...............................................................................\n");

    printf("First complex number: %.1f + %.1fi\n",n1.real,n1.imag);
    printf("Second complex number: %.1f + %.1fi\n",n2.real,n2.imag);

    result = add(n1, n2);
    printf("Sum = %.1f + %.1fi\n", result.real, result.imag);

    result = sub(n1, n2);
    printf("Difference = %.1f + %.1fi\n", result.real, result.imag);

    result = mult(n1, n2);
    printf("Product = %.1f + %.1fi\n", result.real, result.imag);

    result = conjugate(n1);
    printf("Conjugate of first complex number = %.1f + %.1fi\n", result.real, result.imag);

    result = conjugate(n2);
    printf("Conjugate of second complex number = %.1f + %.1fi\n", result.real, result.imag);

    return 0;
}

