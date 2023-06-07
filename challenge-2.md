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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct my_date_t {
    uint8_t date;     
    uint8_t month;      
    uint16_t year;    
} my_date_t;

typedef enum status_t {
    SUCCESS,    
    NULL_PTR,   
    INCORRECT   
} status_t;

status_t string_to_date_converter(char* input_string, my_date_t* result_date) {
    if (input_string == NULL || result_date == NULL) {
        return NULL_PTR;
    }
    int d, m, y;
    if (sscanf(input_string, "%d/%d/%d", &d, &m, &y) != 3) {
        return INCORRECT;
    }
    if (d < 1 || d > 31 || m < 1 || m > 12 || y < 0) {
        return INCORRECT;
    }

    result_date->date = (uint8_t)d;
    result_date->month = (uint8_t)m;
    result_date->year = (uint16_t)y;

    return SUCCESS;
}

int main() {
    char date_string[] = "07/06/2023";
    my_date_t result;

    status_t status = string_to_date_converter(date_string, &result);

    if (status == SUCCESS) {
        printf("Conversion successful\n");
        printf("Date: %d\n", result.date);
        printf("Month: %d\n", result.month);
        printf("Year: %d\n", result.year);
    } else if (status == NULL_PTR) {
        printf("Error: NULL pointers\n");
    } else if (status == INCORRECT) {
        printf("Error: Incorrect date format\n");
    }

    return 0;
}
