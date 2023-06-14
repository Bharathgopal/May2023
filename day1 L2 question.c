/*
Task 4
Write a function to accept an integer (32 bits) and operation type to do the following and return the result to main function.
    - Set 2 bits from nth bit position, if operation type is 1
    - Clear 3 bits from nth bit position, if operation type is 2
    - Toggle MSB, if operation type is 3
   You can consider the below function prototype,
    - bit_operations(int num, int oper_type, int pos);
*/

#include <stdio.h>

int bit_operations(int num, int oper_type, int pos)
{
   if (oper_type == 1)
   {
      // Set 2 bits from nth bit position
      int mask = (1 << 2) - 1; // Create a mask with the lowest 2 bits set (0b11)
      mask = mask << pos;      // Shift the mask to the desired position
      return num | mask;       // Set the corresponding bits in num using bitwise OR
   }
   else if (oper_type == 2)
   {
      // Clear 3 bits from nth bit position
      int mask = (1 << 3) - 1; // Create a mask with the lowest 3 bits set (0b111)
      mask = mask << pos;      // Shift the mask to the desired position
      mask = ~mask;            // Invert the mask to clear the corresponding bits
      return num & mask;       // Clear the bits in num using bitwise AND
   }
   else if (oper_type == 3)
   {
      // Toggle MSB (Most Significant Bit)
      int mask = 1 << 31; // Create a mask with only the MSB set (0x80000000)
      return num ^ mask;  // Toggle the MSB in num using bitwise XOR
   }
   else
   {
      // Invalid operation type
      printf("Invalid operation type\n");
      return num; // Return the original number unchanged
   }
}

int main()
{
   int num, oper_type, pos;
   printf("Enter the number: ");
   scanf("%d", &num);
   printf("Enter the operation type (1, 2, or 3): ");
   scanf("%d", &oper_type);
   printf("Enter the position: ");
   scanf("%d", &pos);

   int result = bit_operations(num, oper_type, pos);
   printf("Result: %d\n", result);

   return 0;
}