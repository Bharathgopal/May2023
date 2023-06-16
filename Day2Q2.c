#include <stdio.h>

void swap(void *a, void *b, size_t size) {
    char *ptrA = (char *)a;
    char *ptrB = (char *)b;

    for (size_t i = 0; i < size; i++) {
        char temp = ptrA[i];
        ptrA[i] = ptrB[i];
        ptrB[i] = temp;
    }
}

int main() {
    int num1 = 10;
    int num2 = 20;

    printf("Before swap: num1 = %d, num2 = %d\n", num1, num2);

    swap(&num1, &num2, sizeof(int));

    printf("After swap: num1 = %d, num2 = %d\n", num1, num2);

    double pi = 3.14159;
    double e = 2.71828;

    printf("Before swap: pi = %f, e = %f\n", pi, e);

    swap(&pi, &e, sizeof(double));

    printf("After swap: pi = %f, e = %f\n", pi, e);

    return 0;
}