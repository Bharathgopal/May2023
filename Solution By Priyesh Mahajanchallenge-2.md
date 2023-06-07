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


CODE
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct my_date_t {
    uint8_t date;    /* date */
    uint8_t month;   /* month */
    uint16_t year;   /* year */
} my_date_t;

typedef enum status_t {
    SUCCESS,    /* Function has successfully converted the string to structure */
    NULL_PTR,   /* Function is given NULL pointers to work with */
    INCORRECT   /* Incorrect values for date or month or year */
} status_t;

status_t string_to_date_converter(char* input_string, my_date_t* result_date) {
    if (input_string == NULL || result_date == NULL) {
        return NULL_PTR;
    }

    // Check if the string length is valid (expected length: 10, DD/MM/YYYY)
    size_t input_length = strlen(input_string);
    if (input_length != 10) {
        return INCORRECT;
    }

    // Extract day, month, and year from the input string
    char* token = strtok(input_string, "/");
    if (token == NULL) {
        return INCORRECT;
    }
    result_date->date = atoi(token);

    token = strtok(NULL, "/");
    if (token == NULL) {
        return INCORRECT;
    }
    result_date->month = atoi(token);

    token = strtok(NULL, "/");
    if (token == NULL) {
        return INCORRECT;
    }
    result_date->year = atoi(token);

    // Perform additional validation if required
    // ...

    return SUCCESS;
}

int main() {
    char input_string[] = "07/06/2023";
    my_date_t result_date;

    status_t conversion_status = string_to_date_converter(input_string, &result_date);

    if (conversion_status == SUCCESS) {
        printf("Conversion successful: %02d/%02d/%04d\n", result_date.date, result_date.month, result_date.year);
    } else if (conversion_status == NULL_PTR) {
        printf("NULL pointers were given.\n");
    } else if (conversion_status == INCORRECT) {
        printf("Incorrect values for date or month or year.\n");
    }

    return 0;
}

```
