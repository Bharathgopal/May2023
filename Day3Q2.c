#include <stdio.h>

void printBits(unsigned int num) {
    int i;
    unsigned int mask = 1 << 31; // Start with the leftmost bit (most significant bit)

    for (i = 0; i < 32; i++) {
        // Use bitwise AND to check if the current bit is 1 or 0
        if (num & mask)
            printf("1");
        else
            printf("0");

        // Shift the mask to the right to check the next bit
        mask >>= 1;
    }
}

int main() {
    unsigned int num;
    printf("Enter a 32-bit integer: ");
    scanf("%u", &num);

    printf("Bits: ");
    printBits(num);
    printf("\n");

    return 0;
}