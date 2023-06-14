#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct my_date_t {
    uint8_t date;    /*< date */
    uint8_t month;   /*< month */
    uint16_t year;   /*< year */
} my_date_t;

typedef enum status_t {
    SUCCESS,     /*< Function has successfully converted the string to structure */
    NULL_PTR,    /*< Function is given NULL pointers to work with */
    INCORRECT    /*< Incorrect values for date or month or year */
} status_t;

status_t string_to_date_converter(char* input_string, my_date_t* result_date) {
    if (input_string == NULL || result_date == NULL) {
        return NULL_PTR;
    }

    // Extract day, month, and year from the input string
    int num_fields = sscanf(input_string, "%2hhu/%2hhu/%4hu", &(result_date->date), &(result_date->month), &(result_date->year));

    if (num_fields != 3) {
        return INCORRECT;
    }

    // Validate the parsed values
    if (result_date->date < 1 || result_date->date > 31 ||
        result_date->month < 1 || result_date->month > 12 ||
        result_date->year < 1) {
        return INCORRECT;
    }

    return SUCCESS;
}
int main() {
    char input_string[] = "14/06/2023";
    my_date_t result_date;

    status_t conversion_status = string_to_date_converter(input_string, &result_date);
    if (conversion_status == SUCCESS) {
        printf("Conversion successful: %02d/%02d/%04d\n", result_date.date, result_date.month, result_date.year);
    } else if (conversion_status == NULL_PTR) {
        printf("Error: NULL pointers.\n");
    } else if (conversion_status == INCORRECT) {
        printf("Error: Incorrect values for date or month or year.\n");
    }

    return 0;
}

