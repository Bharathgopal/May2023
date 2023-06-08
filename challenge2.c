#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct my_date_t
{
    uint8_t date;   /* date */
    uint8_t month;  /* month */
    uint16_t year;  /* year */
} my_date_t;

typedef enum status_t
{
    SUCCESS,     /* Function has successfully converted the string to structure */
    NULL_PTR,    /* Function is given NULL pointers to work with */
    INCORRECT    /* Incorrect values for date or month or year */
} status_t;

status_t string_to_date_converter(char* input_string, my_date_t* result_date)
{
    if (input_string == NULL || result_date == NULL)
        return NULL_PTR;

    // Check the string length
    size_t len = strlen(input_string);
    if (len != 10)
        return INCORRECT;

    // Check the delimiter positions
    if (input_string[2] != '/' || input_string[5] != '/')
        return INCORRECT;

    // Extract the day, month, and year as strings
    char day_str[3] = {input_string[0], input_string[1], '\0'};
    char month_str[3] = {input_string[3], input_string[4], '\0'};
    char year_str[5] = {input_string[6], input_string[7], input_string[8], input_string[9], '\0'};

    // Convert the day, month, and year strings to integers
    int day = atoi(day_str);
    int month = atoi(month_str);
    int year = atoi(year_str);

    // Validate the day, month, and year values
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 9999)
        return INCORRECT;

    // Store the converted values in the result_date structure
    result_date->date = (uint8_t)day;
    result_date->month = (uint8_t)month;
    result_date->year = (uint16_t)year;

    return SUCCESS;
}
