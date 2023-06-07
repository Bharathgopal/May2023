# Date String to Structure conversion
* In a application, the date is stored as a string and for computations, converting the string to number is required.
* Write a function to convert the string formated date to a structure as per the below code
* Return appropriate error values if the conversion is not successful

## Inptu string format
```
    DD/MM/YYYY
```

## Output Structure format
```
typedef struct my_date_t
{
    uint8_t date;       /*<<< date */
    uint8_t month;      /*<<< month */
    uint16_t year;      /*<<< year   */
}my_date_t;
```

### Conversion status 
```
typedef enum status_t
{
    SUCCESS,                    /**< Function has successfully converted the string to structure */
    NULL_PTR,                   /**< Function is given NULL pointers to work with */
    INCORRECT                   /**< Incorrect values for date or month or year */
}status_t;

```

### Function prototype
```
/**
 * @brief Function to convert string of the format DD/MM/YYYY to my_date_t structure
 * 
 * @param input_string String which needs to be converted
 * @param result_time Resultant structure to hold the converted string
 * @return status_t SUCCESS if conversion is done, status_t code otherwise.
 */
status_t string_to_date_converter(char* input_string, my_date_t* result_date);
```
## Solution

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct my_date_t
{
    uint8_t date;       /* date */
    uint8_t month;      /* month */
    uint16_t year;      /* year */
} my_date_t;

typedef enum status_t
{
    SUCCESS,        /* Function has successfully converted the string to structure */
    NULL_PTR,       /* Function is given NULL pointers to work with */
    INCORRECT       /* Incorrect values for date or month or year */
} status_t;

status_t string_to_date_converter(char* input_string, my_date_t* result_date)
{
    if (input_string == NULL || result_date == NULL)
        return NULL_PTR;

    size_t string_length = strlen(input_string);
    if (string_length != 10)
        return INCORRECT;

    char* day_str = strtok(input_string, "/");
    char* month_str = strtok(NULL, "/");
    char* year_str = strtok(NULL, "/");

    if (day_str == NULL || month_str == NULL || year_str == NULL)
        return INCORRECT;

    int day = atoi(day_str);
    int month = atoi(month_str);
    int year = atoi(year_str);

    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1)
        return INCORRECT;

    result_date->date = (uint8_t)day;
    result_date->month = (uint8_t)month;
    result_date->year = (uint16_t)year;

    return SUCCESS;
}

int main()
{
    char input_string[] = "16/06/2022";
    my_date_t result_date;
    status_t status = string_to_date_converter(input_string, &result_date);

    if (status == SUCCESS)
    {
        printf("Conversion successful.\n");
        printf("Day: %d\n", result_date.date);
        printf("Month: %d\n", result_date.month);
        printf("Year: %d\n", result_date.year);
    }
    else if (status == NULL_PTR)
    {
        printf("Error: NULL pointers.\n");
    }
    else if (status == INCORRECT)
    {
        printf("Error: Incorrect date format.\n");
    }

    return 0;
}

```
