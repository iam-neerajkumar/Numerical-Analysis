#include <stdio.h>

 int main() {
    double precession = 1.0;

    while (1.0 + precession != 1.0) {
        precession /= 2.0;
    }
    
    printf("Machine precession: %e\n", precession);
    
    return 0;
    }