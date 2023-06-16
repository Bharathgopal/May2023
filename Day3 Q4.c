#include <stdio.h>

int findLargestNumber(int number) {
    int largest = 0;
    int divisor = 1;
    int temp = number;

    // Iterate through each digit position
    for (int i = 0; i < 4; i++) {
        temp = number;
        int deletedNumber = 0;

        // Delete the digit at the current position
        for (int j = 0; j < 4; j++) {
            int digit = temp % 10;
            temp /= 10;
            
            if (j != i) {
                deletedNumber += digit * divisor;
                divisor *= 10;
            }
        }

        // Check if the deleted number is larger than the current largest
        if (deletedNumber > largest) {
            largest = deletedNumber;
        }

        divisor = 1;
    }

    return largest;
}

int main() {
    int number;
    printf("Enter a 4-digit number: ");
    scanf("%d", &number);

    int largestNumber = findLargestNumber(number);
    printf("The largest number by deleting a single digit: %d\n", largestNumber);

    return 0;
}