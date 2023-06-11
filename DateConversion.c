#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct my_date_t
{
    uint8_t date;  /*< date */
    uint8_t month; /*< month */
    uint16_t year; /*< year */
} my_date_t;

typedef enum status_t
{
    SUCCESS,  /*< Function has successfully converted the string to the structure */
    NULL_PTR, /*< Function is given NULL pointers to work with */
    INCORRECT /*< Incorrect values for date or month or year */
} status_t;

status_t string_to_date_converter(char *input_string, my_date_t *result_date)
{
    if (input_string == NULL || result_date == NULL)
    {
        return NULL_PTR;
    }

    // Check if the string length is valid
    size_t string_length = strlen(input_string);
    if (string_length != 10)
    {
        return INCORRECT;
    }

    // Extract day, month, and year substrings from the input string
    char day_str[3], month_str[3], year_str[5];
    day_str[0] = input_string[0];
    day_str[1] = input_string[1];
    day_str[2] = '\0';

    month_str[0] = input_string[3];
    month_str[1] = input_string[4];
    month_str[2] = '\0';

    year_str[0] = input_string[6];
    year_str[1] = input_string[7];
    year_str[2] = input_string[8];
    year_str[3] = input_string[9];
    year_str[4] = '\0';

    // Convert day, month, and year strings to integers
    int day = atoi(day_str);
    int month = atoi(month_str);
    int year = atoi(year_str);

    // Validate the day, month, and year values
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 0)
    {
        return INCORRECT;
    }

    // Assign the converted values to the result_date structure
    result_date->date = (uint8_t)day;
    result_date->month = (uint8_t)month;
    result_date->year = (uint16_t)year;

    return SUCCESS;
}

// IMPLEMENTATION

int main()
{
    char input_string[] = "15/06/2023";
    my_date_t result_date;

    status_t conversion_status = string_to_date_converter(input_string, &result_date);

    if (conversion_status == SUCCESS)
    {
        printf("Date converted successfully: %d/%d/%d\n", result_date.date, result_date.month, result_date.year);
    }
    else
    {
        printf("Date conversion failed with status: %d\n", conversion_status);
    }

    return 0;
}