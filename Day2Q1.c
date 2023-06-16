#include <stdio.h>

void printExponent(double num) {
    unsigned long long *ptr = (unsigned long long *)&num;
    unsigned long long exponent = (*ptr >> 52) & 0x7FF;
    
    printf("Hexadecimal exponent: 0x%llX\n", exponent);
    
    printf("Binary exponent: ");
    for (int i = 11; i >= 0; i--) {
        printf("%d", (exponent >> i) & 1);
    }
    printf("\n");
}

int main() {
    double x = 0.7;
    printExponent(x);
    return 0;
}