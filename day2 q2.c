#include <stdio.h>

void swap(void *a, void *b, size_t size) {
    char temp[size];
    
    // Copy the contents of 'a' to 'temp'
    char *tempPtr = (char *)a;
    for (size_t i = 0; i < size; i++) {
        temp[i] = *(tempPtr + i);
    }
    
    // Copy the contents of 'b' to 'a'
    char *aPtr = (char *)a;
    char *bPtr = (char *)b;
    for (size_t i = 0; i < size; i++) {
        *(aPtr + i) = *(bPtr + i);
    }
    
    // Copy the contents of 'temp' to 'b'
    for (size_t i = 0; i < size; i++) {
        *(bPtr + i) = temp[i];
    }
}

int main() {
    int a = 5;
    int b = 10;
    printf("Before swap: a = %d, b = %d\n", a, b);
    swap(&a, &b, sizeof(int));
    printf("After swap: a = %d, b = %d\n", a, b);

    double x = 3.14;
    double y = 2.71;
    printf("Before swap: x = %lf, y = %lf\n", x, y);
    swap(&x, &y, sizeof(double));
    printf("After swap: x = %lf, y = %lf\n", x, y);

    return 0;
}