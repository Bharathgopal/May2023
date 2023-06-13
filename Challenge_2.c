#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct my_date_t 
{
    uint8_t date; //date
    uint8_t month; // Month
    uint16_t year;// year
} my_date_t;
typedef enum status_t 
{
    SUCCESS, // Conversion successful
    NULL_PTR, //null pointer argument
    INCORRECT // incorrect values for date, month, or year
} 
status_t;
status_t string_to_date_converter(char* input_string, my_date_t* result_date) 
{
    if (input_string == NULL || result_date == NULL) 
    {
        return NULL_PTR;
    }
    uint8_t day, month;
    uint16_t year;
    if (sscanf(input_string, "%2hhu/%2hhu/%4hu", &day, &month, &year) != 3) 
    {
        return INCORRECT;
    }
    if (day < 1 || day > 31 || month < 1 || month > 12) 
    {
        return INCORRECT;
    }
    result_date->date = day;
    result_date->month = month;
    result_date->year = year;
    return SUCCESS;
}
int main() 
{
    char input_string[] = "11/06/2023";
    my_date_t result_date;
    status_t conversion_status = string_to_date_converter(input_string, &result_date);
    if (conversion_status == SUCCESS) 
    {
        printf("Conversion successful:\n");
        printf("Date: %u\n", result_date.date);
        printf("Month: %u\n", result_date.month);
        printf("Year: %u\n", result_date.year);
    } 
    else if (conversion_status == NULL_PTR) 
    {
        printf("Error: NULL pointer passed as argument.\n");
    } 
    else if (conversion_status == INCORRECT) 
    {
        printf("Error: Incorrect values for date, month, or year.\n");
    }
    return 0;
}