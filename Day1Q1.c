#include <stdio.h>

int findMax(int num1, int num2) {
    // Using if-else statement
    if (num1 > num2) {
        return num1;
    } else {
        return num2;
    }

    // Using ternary operator
    // return (num1 > num2) ? num1 : num2;
}

int main() {
    int a, b;
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);

    int max = findMax(a, b);
    printf("The biggest number is: %d\n", max);

    return 0;
}