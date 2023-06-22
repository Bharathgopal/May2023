#include <stdio.h>

int findLargestNumber(int num);

int main() {
    int num;
    printf("Enter a 4-digit number: ");
    scanf("%d", &num);

    int largestNumber = findLargestNumber(num);

    printf("Largest number by deleting a single digit: %d\n", largestNumber);

    return 0;
}

int findLargestNumber(int num) {
    int largest = 0;
    int divisor = 1000;

    while (divisor > 0) {
        int newNumber = (num / divisor / 10) * divisor + num % divisor;

        if (newNumber > largest) {
            largest = newNumber;
        }

        divisor /= 10;
    }

    return largest;
}