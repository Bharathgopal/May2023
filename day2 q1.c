#include <stdio.h>

void printExponent(double x) {
    unsigned long long *ptr = (unsigned long long *)&x;
    unsigned long long exponentMask = 0x7FF0000000000000ULL;
    unsigned long long exponent = (*ptr & exponentMask) >> 52;

    printf("Exponent in hexadecimal: 0x%llX\n", exponent);
    
    printf("Exponent in binary: 0b");
    for (int i = 11; i >= 0; i--) {
        unsigned long long bit = (exponent >> i) & 1;
        printf("%llu", bit);
    }
    printf("\n");
}

int main() {
    double x = 0.7;
    printExponent(x);

    return 0;
}