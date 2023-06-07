#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct my_date_t
{
   uint8_t date;  // date
   uint8_t month; // month
   uint16_t year; // year
} my_date_t;

typedef enum status_t
{
   SUCCESS,  // Function has successfully converted the string to structure
   NULL_PTR, // Function is given NULL pointers to work with
   INCORRECT // Incorrect values for date or month or year
} status_t;

status_t string_to_date_converter(char *input_string, my_date_t *result_date)
{
   if (input_string == NULL || result_date == NULL)
   {
      return NULL_PTR;
   }

   int day, month, year;
   if (sscanf(input_string, "%d/%d/%d", &day, &month, &year) != 3)
   {
      return INCORRECT;
   }

   if (day < 1 || day > 31 || month < 1 || month > 12)
   {
      return INCORRECT;
   }

   result_date->date = (uint8_t)day;
   result_date->month = (uint8_t)month;
   result_date->year = (uint16_t)year;

   return SUCCESS;
}

int main()
{
   char input_string[12]; // Max length for "DD/MM/YYYY" is 10 characters, plus 1 for null terminator
   printf("Enter a date (DD/MM/YYYY): ");
   fgets(input_string, sizeof(input_string), stdin);

   if (input_string[strlen(input_string) - 1] == '\n') // Remove the trailing newline character from the input string
   {
      input_string[strlen(input_string) - 1] = '\0';
   }

   my_date_t result_date;
   status_t conversion_status = string_to_date_converter(input_string, &result_date);

   if (conversion_status == SUCCESS)
   {
      printf("Conversion successful\n");
      printf("Date: %d\n", result_date.date);
      printf("Month: %d\n", result_date.month);
      printf("Year: %d\n", result_date.year);
   }
   else if (conversion_status == NULL_PTR)
   {
      printf("Error: NULL pointers\n");
   }
   else if (conversion_status == INCORRECT)
   {
      printf("Error: Incorrect date format\n");
   }

   return 0;
}