#include <stdio.h>
#include <stdlib.h>

int compareBoxes(int A[], int B[], int size)
{
   int i, j, found;
   int *visited = (int *)malloc(size * sizeof(int)); // allocate the visited array

   // Initialize visited array
   for (i = 0; i < size; i++)
   {
      visited[i] = 0;
   }

   // Iterate over items in Box A
   for (i = 0; i < size; i++)
   {
      found = 0;

      // Search for the current item in Box B
      for (j = 0; j < size; j++)
      {
         if (A[i] == B[j] && visited[j] == 0)
         {
            visited[j] = 1; // Mark the item as visited
            found = 1;
            break;
         }
      }

      // If the item was not found in Box B, return 0
      if (found == 0)
      {
         free(visited); // Free the allocated memory
         return 0;
      }
   }

   // Check if any items in Box B were not visited
   for (i = 0; i < size; i++)
   {
      if (visited[i] == 0)
      {
         free(visited);
         return 0;
      }
   }

   free(visited);
   // All items in Box A are matched with items in Box B
   return 1;
}

int main()
{
   int size;

   printf("Enter the size of the boxes: ");
   scanf("%d", &size);

   int *A = (int *)malloc(size * sizeof(int));
   int *B = (int *)malloc(size * sizeof(int));

   printf("Enter the items in Box A:\n");
   for (int i = 0; i < size; i++)
   {
      printf("Item %d: ", i + 1);
      scanf("%d", &A[i]);
   }

   printf("Enter the items in Box B:\n");
   for (int i = 0; i < size; i++)
   {
      printf("Item %d: ", i + 1);
      scanf("%d", &B[i]);
   }

   int result = compareBoxes(A, B, size);

   printf("Result: %d\n", result);

   free(A);
   free(B);

   return 0;
}