#include <stdio.h>

int findBiggest(int num1, int num2) {
    if (num1 > num2) {
        return num1;
    } else {
        return num2;
    }
}

int main() {
    int a, b;
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);

    int biggest = findBiggest(a, b);
    printf("The biggest number is: %d\n", biggest);

    return 0;
}