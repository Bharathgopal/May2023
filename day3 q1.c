#include <stdio.h>

void printPattern(int n);

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    
    printPattern(n);
    
    return 0;
}

void printPattern(int n) {
    int i, j;

    for (i = n; i >= 1; i--) {
        for (j = 1; j <= i; j++) {
            printf("%d", j);
        }

        for (j = 1; j <= 2 * (n - i); j++) {
            printf(" ");
        }

        for (j = i; j >= 1; j--) {
            printf("%d", j);
        }
        
        printf("\n");
    }
}