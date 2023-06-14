#include <stdio.h>

int bitOperations(int num, int oper_type) {
    switch (oper_type) {
        case 1:
            num |= 1;  // Set 1st bit
            break;
        case 2:
            num &= ~(1 << 31);  // Clear 31st bit
            break;
        case 3:
            num ^= (1 << 15);  // Toggle 16th bit
            break;
        default:
            printf("Error: Invalid operation type\n");
            break;
    }
    return num;
}

int main() {
    int num, oper_type;

    printf("Enter the 32-bit integer: ");
    scanf("%d", &num);

    printf("Enter the operation type (1, 2, or 3): ");
    scanf("%d", &oper_type);

    int result = bitOperations(num, oper_type);

    printf("Modified number: %d\n", result);

    return 0;
}
