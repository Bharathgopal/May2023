#include <stdio.h>

int main() {
    int rollNo;
    char name[50];
    float physics, math, chemistry, total, percentage;

    printf("Enter the Roll No: ");
    scanf("%d", &rollNo);

    printf("Enter the Name: ");
    scanf(" %[^\n]", name);

    printf("Enter the marks of Physics: ");
    scanf("%f", &physics);

    printf("Enter the marks of Math: ");
    scanf("%f", &math);

    printf("Enter the marks of Chemistry: ");
    scanf("%f", &chemistry);

    total = physics + math + chemistry;
    percentage = (total / 300) * 100;

    printf("\n----- Student Summary -----\n");
    printf("Roll No: %d\n", rollNo);
    printf("Name: %s\n", name);
    printf("Physics: %.2f\n", physics);
    printf("Math: %.2f\n", math);
    printf("Chemistry: %.2f\n", chemistry);
    printf("Total Marks: %.2f\n", total);
    printf("Percentage: %.2f%%\n", percentage);

    return 0;
}