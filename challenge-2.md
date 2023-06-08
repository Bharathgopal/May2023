#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct my_date_t {
    uint8_t date;   /**< date */
    uint8_t month;  /**< month */
    uint16_t year;  /**< year */
} my_date_t;

typedef enum status_t {
    SUCCESS,    /**< Function has successfully converted the string to structure */
    NULL_PTR,   /**< Function is given NULL pointers to work with */
    INCORRECT   /**< Incorrect values for date or month or year */
} status_t;

status_t string_to_date_converter(char* input_string, my_date_t* result_date) {
    if (input_string == NULL || result_date == NULL) {
        return NULL_PTR;
    }

    // Parsing the input string
    char* endptr;
    result_date->date = strtol(input_string, &endptr, 10);
    if (*endptr != '/' || result_date->date < 1 || result_date->date > 31) {
        return INCORRECT;
    }

    result_date->month = strtol(endptr + 1, &endptr, 10);
    if (*endptr != '/' || result_date->month < 1 || result_date->month > 12) {
        return INCORRECT;
    }

    result_date->year = strtol(endptr + 1, &endptr, 10);
    if (*endptr != '\0') {
        return INCORRECT;
    }

    return SUCCESS;
}
